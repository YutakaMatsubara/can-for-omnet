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

#include "CanBus.h"

Define_Module(CanBus);

simsignal_t CanBus::busTransmitStartSignal = SIMSIGNAL_NULL;
simsignal_t CanBus::messageIDSignal = SIMSIGNAL_NULL;
simsignal_t CanBus::busloadSignal = SIMSIGNAL_NULL;

static cEnvir& operator<<(cEnvir& out, cMessage *msg)
{
    out.printf("(%s)%s", msg->getClassName(), msg->getFullName());
    return out;
}

CanBus::CanBus()
{
    tap = NULL;
    arbReqMsg = NULL;
    traEndMsg = NULL;
    maxPriMsg = NULL;
    blReqMsg = NULL;
    sendRequest = NULL;
   	sendRequestCanMessage = NULL;
   	arbitrationFinish = NULL;
   	receiveFinish = NULL;
}

CanBus::~CanBus()
{
    cancelAndDelete(arbReqMsg);
    cancelAndDelete(traEndMsg);
    cancelAndDelete(blReqMsg);

    if (maxPriMsg != NULL) {
		delete maxPriMsg;
	}

    for (int i = 0; i < numTaps; i++) {
		if(sendRequestCanMessage[i]!=NULL) {
			delete sendRequestCanMessage[i];
		}
	}

    delete [] tap;
    delete [] sendRequest;
    delete [] sendRequestCanMessage;
    delete [] arbitrationFinish;
    delete [] receiveFinish;
}

void CanBus::initialize()
{
    numMessages = 0;
    numBits = 0;
    WATCH(numMessages);

    // initialize self messages
    arbReqMsg = new cMessage("ArbitrationRequest", ARBITRATION_REQUEST);
	traEndMsg = new cMessage("TransmitEnd", TRANSMIT_END); 
	blReqMsg = new cMessage("BusloadRequest", BUSLOAD_REQUEST);

	// initialize states
	busState = IDLE_STATE;
    WATCH(busState);

    busTransmitStartSignal = registerSignal("busTransmitStart");
    messageIDSignal = registerSignal("messageID");
    busloadSignal = registerSignal("busload");

    propagationSpeed = par("propagationSpeed").doubleValue();
    arbitration_period = par("arbitrationPeriod").doubleValue();
    busload_period = par("busloadPeriod").doubleValue();
    calcmode = par("calcmode");

    // initialize the positions where the hosts connects to the bus
    numTaps = gateSize("ethg");
    inputGateBaseId = gateBaseId("ethg$i");
    outputGateBaseId = gateBaseId("ethg$o");

    tap = new BusTap[numTaps];
	sendRequest = new uint[numTaps]; // ID of CAN messages to be sent
	sendRequestCanMessage = new cMessage*[numTaps]; // The body of CAN messages to be sent
	arbitrationFinish = new bool[numTaps];
	receiveFinish = new bool[numTaps];
	
	// initialize each connection points on CAN bus
	char msgName[32];
    for (int i = 0; i < numTaps; i++) {
		tap[i].id = i;
		sendRequest[i] = MAX_CAN_MESSAGE_ID;
		sprintf(msgName, "init_tap%d", i);
		sendRequestCanMessage[i] = NULL;
		arbitrationFinish[i] = false;
		receiveFinish[i] = false;
		WATCH(sendRequest[i]);
		WATCH(arbitrationFinish[i]);
		WATCH(receiveFinish[i]);
    }

    WATCH(maxPriMsg);
    // Prints out data of parameters for parameter checking...
    EV << "Parameters of (" << getClassName() << ") " << getFullPath() << "\n";
    EV << "propagationSpeed: " << propagationSpeed << "\n";

    // ensure we receive frames when their first bits arrive
    for (int i = 0; i < numTaps; i++) {
        gate(inputGateBaseId + i)->setDeliverOnReceptionStart(true);
	}
    subscribe(POST_MODEL_CHANGE, this);  // we'll need to do the same for dynamically added gates as well

    scheduleAt(busload_period,blReqMsg);
}

void CanBus::handleMessage(cMessage *msg)
{
	EV << "CanBus: message " << msg << " received\n";

	if (!msg->isSelfMessage()) {
		CanTraffic *can_msg = check_and_cast<CanTraffic *>(msg);
		switch (can_msg->getType()) {
		case CAN_MESSAGE:
			handleCanMessageFromNode(msg);
			break;
		default:
			error("Message with unexpected message type %d", can_msg->getType());
		}
	} else {
		EV << "CanBus: Self-message " << msg << " received\n";
		switch (msg->getKind()) {
		case ARBITRATION_REQUEST:
		    // arbitration is started since delta time elapsed.
			handleArbitrationRequest();
			break;
		case TRANSMIT_END:
		    // transmission of the sending message on CAN bus is finished
			handleTransmitEnd();
			break;
		case BUSLOAD_REQUEST:
		    // calculate workload of CAN bus every 1 sec
			handleBusloadRequest();
			break;
		default:
			error("self-message with unexpected message kind %d", msg->getKind());
		}
	}
}

void CanBus::handleCanMessageFromNode(cMessage *msg)
{
	int nodeid = (((cMessage *)msg)->getArrivalGate())->getIndex();

	EV << "SendRequest " << msg << " arrived on tap " << nodeid << endl;

	// In the case of full-priority queue mode, sending request need
	// to be deleted because messages can be swaped.
	if (sendRequest[nodeid] != MAX_CAN_MESSAGE_ID) {
		delete sendRequestCanMessage[nodeid];
	}

	// sending request and body of msg are stored
	sendRequest[nodeid] = (check_and_cast<CanFrame *>(msg))->getMessageID();
	sendRequestCanMessage[nodeid] = msg;

	printState();

	// When the state of this bus is IDLE, arbitration mechanism is started.
	if (busState == IDLE_STATE) {
		scheduleAt(simTime()+arbitration_period, arbReqMsg);
		busState = ARBITRATING_STATE;
	}
}

void CanBus::handleArbitrationRequest()
{
	uint minID = MAX_CAN_MESSAGE_ID;
	int sendNodeID = INVALID_NODEID;
	EV <<"handleArbitrationRequest:hogehoge"  << endl;

	// specify the node ID where the message with maximum priority
	// (message ID is minimum) would be sent
	for (int i = 0; i < numTaps; i++) {
		if (sendRequest[i] < minID) {
			minID = sendRequest[i];
			sendNodeID = i;
		}
	}

	// send signals for logging start of transmission and message ID
	emit(messageIDSignal,minID);
	emit(busTransmitStartSignal, sendRequestCanMessage[sendNodeID]);

	// send the message with the maximum priority
	if (minID == MAX_CAN_MESSAGE_ID) {
		error("Arbitration Request was received without Send Requests\n");
	} else {
		sendRequest[sendNodeID] = MAX_CAN_MESSAGE_ID;
		receiveFinish[sendNodeID] = true;

		// the message is temporary stored 
		maxPriMsg = sendRequestCanMessage[sendNodeID];
		sendRequestCanMessage[sendNodeID] = NULL;

		// calculate transmission time
		double transmitDelay = calcBitLengthByVenet(calcmode, maxPriMsg) / (propagationSpeed*1000); // byte/bps
		EV << "handleArbitrationRequest:(check_and_cast<CanFrame *>(maxPriMsg))->getFrameByteLength()" << (check_and_cast<CanFrame *>(maxPriMsg))->getFrameByteLength()  << endl;
		EV << "handleArbitrationRequest:propagationSpeed" << propagationSpeed  << endl;
		EV << "handleArbitrationRequest:transmitDelay" << transmitDelay << endl;
		EV << "calcmode : " << calcmode << "calcBitLengthByVenet : " <<calcBitLengthByVenet(calcmode, maxPriMsg) << endl;
		EV << "sendNodeID " << sendNodeID << "messageID " << minID << endl;

		double IFSDelay = 3 / (propagationSpeed*1000); // IFS is 3 bits

		// sent a transmission finish message to all nodes except for
		// the node sending the message.
		scheduleAt(simTime()+transmitDelay+IFSDelay-arbitration_period, traEndMsg);
		busState = TRANSMITTING_STATE;

		// send an arbitration finish message to the node sending the
		// sent message
		CanArbitrationFinish *fin = new CanArbitrationFinish("CAN_ARBITRATION_FINISH");
		fin->setType(CAN_ARBITRATION_FINISH);
		send(fin,"ethg$o",sendNodeID);
	}
}

void CanBus::handleTransmitEnd()
{
	// sent a CAN message to all nodes except for the node sending the
	// message.
	for (int i = 0; i < numTaps; i++) {
		// the CAN message is not sent to the node sending the message.
		if (receiveFinish[i] == true) {
			continue;
		}
		EV <<"send message to node[" << i << "]"<< endl;

		cGate *ogate = gate(outputGateBaseId + i);
		if (ogate->isConnected()) {
			// send out on gate
			cMessage *msg2 = maxPriMsg->dup();
			
			// stop current transmission
			ogate->getTransmissionChannel()->forceTransmissionFinishTime(SIMTIME_ZERO);
			// send the message to the node connected to the TAP
			send(msg2, ogate);
			
			// save the finish to receive the message
			receiveFinish[i] = true;
		}
	}

	// check whether all nodes finished to receive the message
	bool finish_flag = true;
	int i = 0;
	do {
		if (!receiveFinish[i]) {
			finish_flag = false;
		}
		i++;
	} while (i < numTaps && finish_flag);

	// add number of bits for calculating workload of CAN bus
	numBits = numBits + calcBitLengthByVenet(calcmode, maxPriMsg);

	// process when all nodes finished to receive the message
	if (finish_flag) {
 		busState = IDLE_STATE;

		// initialize flags that mean finishing of receiving CAN message
		for (i = 0; i < numTaps; i++) {
			receiveFinish[i] = false;
		}

		// delete the message sent
		delete maxPriMsg;
		maxPriMsg = NULL;

		// When any requests of sending other messages exist, start
		// arbitration for these requests
		for (i = 0; i < numTaps; i++) {
			if (sendRequest[i] !=  MAX_CAN_MESSAGE_ID) {
				scheduleAt(simTime()+arbitration_period, arbReqMsg);
				busState = ARBITRATING_STATE;
				break;
			}
		}
	} else {
		error("MaxPriMsg was not sended to all node\n");
	}
}

void CanBus::handleBusloadRequest()
{
	double bl;

	// calculate workload of CAN bus
	bl = numBits / (busload_period * propagationSpeed * 1000);
	emit(busloadSignal, bl);
	numBits = 0;

	scheduleAt(simTime() + busload_period, blReqMsg);
}

void CanBus::printState()
{
	int i;
	// print a list of requests of sending message
	EV << "***********************************************\n";
	EV << "    nodeID    | ";
	for (i = 0; i < numTaps; i++) {
		EV << i << " ";
	}
	EV << "\nSendRequestID | ";
	for (i = 0; i < numTaps; i++) {
		EV << sendRequest[i] << " ";
	}
	EV << "\n***********************************************\n";
}

double CanBus::calcBitLengthByVenet(int mode, cMessage *msg)
{
	double ans;

	switch (mode) {
	case 1:
	    // estimate size of stuff bits from whole CAN message
		// stuff bits = (44 + ML * 8) * 9/8
		ans = (44 + (check_and_cast<CanFrame *>(msg))->getFrameByteLength()*8) * 9/8;
		break;
	case 2:
	    // estimate size of stuff bits from data area of CAN message
		// stuff bits = (34 + ML * 8 - 1) / 4 + 44 + ML * 8
		ans = (34 + ((check_and_cast<CanFrame *>(msg))->getFrameByteLength()*8) - 1)/4 + 44 + ((check_and_cast<CanFrame *>(msg))->getFrameByteLength()*8);
		break;
	default:
		error("Unexpected calculation mode %d", mode);
		break;
	}

	return ans;
}

void CanBus::finish()
{
    simtime_t t = simTime();
    recordScalar("simulated time", t);
    recordScalar("messages handled", numMessages);

    if (t > 0) {
        recordScalar("messages/sec", numMessages / t);
	}
}
