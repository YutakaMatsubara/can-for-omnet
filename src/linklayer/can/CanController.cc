/*
 * Copyright (C) 2013 Embedded and Real-Time Systems Laboratory
 *             Graduate School of Information Science, Nagoya Univ., JAPAN
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <string.h>

#include "CanController.h"
#include "CanFrame_m.h"

static std::ostream& operator<<(std::ostream& out, cMessage *msg)
{
    out << "(" << msg->getClassName() << ")" << msg->getFullName();
    return out;
}


Define_Module(CanController);

CanController::CanController()
{
}

CanController::~CanController()
{
}

void CanController::initialize()
{
    CanControllerBase::initialize();
    EV << getClassName() << " was initialized" << "\n";
}

void CanController::initializeStatistics()
{
    CanControllerBase::initializeStatistics();
}

void CanController::handleMessage(cMessage *msg)
{
	EV << "CanController: hoge\n";

    printState();

    // some consistency check
    if (receiveState != RX_IDLE_STATE) {
	    error("Inconsistent state -- transmitting and receiving at the same time");
	}

    bool upperLayerInGateFlag = false;
    for (int i=0; i<upperLayerInGatesize; i++) {
    	upperLayerInGate = gate(upperLayerInGatebaseId + i);
        if (msg->getArrivalGate() == upperLayerInGate) {
			upperLayerInGateFlag = true;
		}
    }
	
	if (upperLayerInGateFlag) {
		// received messages from upper layer
  	    processFrameFromUpperLayer(check_and_cast<CanFrame *>(msg));
	} else if (msg->getArrivalGate() == physInGate) {
		// received messages from lower layer
	    processMsgFromNetwork(check_and_cast<CanTraffic *>(msg));
	} else {
        throw cRuntimeError("Message received from unknown gate");
	}
    printState();
}

void CanController::processFrameFromUpperLayer(CanFrame *frame)
{
	emit(messageIDSignal,frame->getMessageID());
	emit(busWaitStartSignal, frame);

	// check length of frames
    if (frame->getFrameByteLength() < MIN_CAN_FRAME_BYTES) {
        throw cRuntimeError("CAN frame too short, must be at least 2 bytes.");
	}

    if (frame->getFrameByteLength() > MAX_CAN_FRAME_BYTES) {
		error("Packet from higher layer (%d bytes) exceeds maximum CAN frame size (%d)",
			  (int)(frame->getFrameByteLength()), MAX_CAN_FRAME_BYTES);
	}

	// emit signals when receiving messages succeed.
    EV << "Received frame from upper layer: " << frame << endl;
    emit(packetReceivedFromUpperSignal, frame);

	if (transmitState ==TX_IDLE_STATE) {
		EV << "CanController: didn't send request yet.\n" ;
		tempFrame = frame->dup();

		// send the body of an CAN message
		send((cMessage *)frame, physOutGate);
		transmitState = TX_WAITING_STATE;
	} else {
		EV << "CanController: aleady sent request!\n";
		EV << "tempFrame messageID:  " << tempFrame->getMessageID() <<endl;
		EV << "frame messageID: " << frame->getMessageID() << endl;

		// When full-priority queue is selected and the priority of
		// the received message (frame) is higer than the priority of
		// the temp message, swap the received message for the temp
		// message. Otherwise Msg_current is inserted to the sending
		// queue.
		if (queueKind == FULL_PRIORITY_QUEUE && 
			tempFrame->getMessageID() > frame->getMessageID()) {
			EV << "CanController: swap section\n";

			// insert the temp message to the head of sending queue.
			txQueue.insertFrame(tempFrame); 

			// send the received message to CAN bus.
			tempFrame = frame->dup();
			send((cMessage*)frame,physOutGate);
		} else {
			// insert the received message to the sending queue
			if (!txQueue.isFull()) {
				txQueue.insertFrame(frame);
				emit(queueLengthSignal,txQueue.length()); 
			} else {
				emit(dropmessageIDSignal,frame->getMessageID()); 
				EV << "CanController: send-queue is Full!\n";
				delete frame;
			}
		}
	}
}

void CanController::processMsgFromNetwork(CanTraffic *msg)
{
    EV << "Received frame from network: " << msg << endl;

	switch (msg->getType()) {
	case CAN_ARBITRATION_FINISH:
		handleArbitrationFinish();
		delete msg;
		break;
	case CAN_MESSAGE:
		handleCanMessageFromBus(check_and_cast<CanFrame *>(msg));
		break;
	default:
	  error("Message with unexpected message type %d", msg->getType());
	}
}

void CanController::handleArbitrationFinish()
{
	transmitState = TX_IDLE_STATE;
	delete tempFrame;
	tempFrame = NULL;

	if (!txQueue.empty()) {
		// store the sending request message
		tempFrame = check_and_cast<CanFrame *>(txQueue.getQueueFirst())->dup();

		// send the massage stored at the head of sending message to CAN bus
 		send((cMessage*)txQueue.pop(), physOutGate);
 		transmitState = TX_WAITING_STATE;
	}
}

void CanController::handleCanMessageFromBus(CanFrame *msg)
{
	// strip physical layer overhead (preamble, SFD, carrier
	// extension) from msg
	msg->setFrameByteLength(msg->getFrameByteLength());

	// statistics
	unsigned long curBytes = msg->getFrameByteLength();
	numFramesReceivedOK++;
	numBytesReceivedOK += curBytes;
	emit(rxPkOkSignal, msg);

	numFramesPassedToHL++;
	emit(packetSentToUpperSignal, msg);

	// filtering Messages received from lower layer.  determine
	// whether the received message should be fetched or not (this
	// filtering function is optional).
	if (filterRegs[0] == 0) {
		for (int j = 0; j < gateSize("upperLayerOut"); j++) {
			send(msg->dup(), gateBaseId("upperLayerOut")+j);
		}
	} else {
		for (int i = 0; i < filterRegNum; i++) {
			if (filterRegs[i] == msg->getMessageID()) {
				// fetche the received message and send it to upper
				// layer
				EV << " pass the message filtering. \n";
				for (int j = 0; j < gateSize("upperLayerOut"); j++) {
					send(msg->dup(), gateBaseId("upperLayerOut")+j);
				}
			} else {
				// discard the received message
				EV << " discarded the received message. \n" ;
			}
		}
	}
	delete msg;
}

void CanController::printState()
{
#define CASE(x) case x: EV << #x; break

    EV << "transmitState: ";
    switch (transmitState) {
        CASE(TX_IDLE_STATE);
        CASE(TX_WAITING_STATE);
    }

    EV << ",  receiveState: ";
    switch (receiveState) {
        CASE(RX_IDLE_STATE);
        CASE(RX_RECEIVING_STATE);
    }
	EV << ",  queueLength: " << txQueue.length() << endl;
#undef CASE
}

void CanController::finish()
{
    CanControllerBase::finish();
}
