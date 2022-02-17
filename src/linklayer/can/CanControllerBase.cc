/*
 * Copyright (C) 2013 Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
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

#include "CanControllerBase.h"

#include "CanFrame_m.h"
#include "Can.h"

simsignal_t CanControllerBase::rxPkOkSignal = SIMSIGNAL_NULL;
simsignal_t CanControllerBase::packetSentToUpperSignal = SIMSIGNAL_NULL;
simsignal_t CanControllerBase::packetReceivedFromUpperSignal = SIMSIGNAL_NULL;
simsignal_t CanControllerBase::busWaitStartSignal = SIMSIGNAL_NULL;
simsignal_t CanControllerBase::busTransmitStartSignal = SIMSIGNAL_NULL;
simsignal_t CanControllerBase::messageIDSignal = SIMSIGNAL_NULL;
simsignal_t CanControllerBase::dropmessageIDSignal = SIMSIGNAL_NULL;
simsignal_t CanControllerBase::queueLengthSignal = SIMSIGNAL_NULL;

CanControllerBase::CanControllerBase()
{
    transmissionChannel = NULL;
    physInGate = NULL;
    physOutGate = NULL;
    upperLayerInGate = NULL;
    tempFrame = NULL;
}

CanControllerBase::~CanControllerBase()
{
	delete transmissionChannel;
	delete tempFrame;
}

void CanControllerBase::initialize()
{
    physInGate = gate("phys$i");
    physOutGate = gate("phys$o");
    upperLayerInGatebaseId = gateBaseId("upperLayerIn");
    upperLayerInGatesize = gateSize("upperLayerIn");

    // change strings specified (ex. "7 12 17") to an integer vector.
    const char *filterReg = par("filterRegs");
    filterRegs = cStringTokenizer(filterReg).asIntVector();

    cStringTokenizer tokenizer(filterReg);
    const char *token;

    // count the number of elements in the filterReg.
    filterRegNum = 0;
    while ((token = tokenizer.nextToken()) != NULL) {
    	filterRegNum++;
	}

    initializeStatistics();

    // initialize states
    transmitState = TX_IDLE_STATE;
    receiveState = RX_IDLE_STATE;
    queueKind = par("queueKind");
    WATCH(transmitState);
    WATCH(receiveState);

    // initialization
    txQueue = CanControllerBase::MessageQueue("CtlSendQueue", par("queueLimit"), queueKind);
   // WATCH(txQueue);

    subscribe(POST_MODEL_CHANGE, this);

    // initialize connected flag
    connected = physOutGate->getPathEndGate()->isConnected();

    if (!connected) {
        EV << "MAC not connected to a network.\n";
	}
    WATCH(connected);

    // TODO: this should be set from the GUI
    // initialize disabled flag
    // Note: it is currently not supported to enable a disabled MAC at runtime.
    // Difficulties: (1) autoconfig (2) how to pick up channel state (free, tx, collision etc)
    disabled = false;
    WATCH(disabled);
}

void CanControllerBase::initializeStatistics()
{
    numFramesSent = numFramesReceivedOK = numBytesSent = numBytesReceivedOK = 0;
	numFramesPassedToHL = 0;

    WATCH(numFramesSent);
    WATCH(numFramesReceivedOK);
    WATCH(numBytesSent);
    WATCH(numBytesReceivedOK);
    WATCH(numFramesPassedToHL);

    rxPkOkSignal = registerSignal("rxPkOk");
    packetSentToUpperSignal = registerSignal("packetSentToUpper");
    packetReceivedFromUpperSignal = registerSignal("packetReceivedFromUpper");
    busWaitStartSignal = registerSignal("busWaitStart");
    busTransmitStartSignal = registerSignal("busTransmitStart");
    messageIDSignal = registerSignal("messageID");
    dropmessageIDSignal = registerSignal("dropmessageID");
    queueLengthSignal = registerSignal("queueLength");
}

void CanControllerBase::finish()
{
    if (!disabled) {
        simtime_t t = simTime();
        recordScalar("simulated time", t);

        if (t > 0) {
            recordScalar("frames/sec sent", numFramesSent / t);
            recordScalar("frames/sec rcvd", numFramesReceivedOK / t);
            recordScalar("bits/sec sent",   (8.0 * numBytesSent) / t);
            recordScalar("bits/sec rcvd",   (8.0 * numBytesReceivedOK) / t);
        }
    }
}

void CanControllerBase::updateDisplayString()
{
    // icon coloring
    const char *color;

	if (receiveState == RX_RECEIVING_STATE) {
        color = "#4040ff";
	} else {
        color = "";
	}

    getDisplayString().setTagArg("i", 1, color);

    if (!strcmp(getParentModule()->getClassName(), "CanInterface")) {
        getParentModule()->getDisplayString().setTagArg("i", 1, color);
	}

    // connection coloring
    updateConnectionColor(transmitState);
}

void CanControllerBase::updateConnectionColor(int txState)
{
    const char *color;

	color = "";
    if (ev.isGUI()) {
        if (connected) {
            transmissionChannel->getDisplayString().setTagArg("ls", 0, color);
            transmissionChannel->getDisplayString().setTagArg("ls", 1, color[0] ? "3" : "1");
        } else {
            // we are not connected: gray out our icon
            getDisplayString().setTagArg("i", 1, "#707070");
            getDisplayString().setTagArg("i", 2, "100");
        }
    }
}

int CanControllerBase::MessageQueue::packetComparePri(cObject *a, cObject *b)
{
	// sort messages in ID (only for full- or partial- priority queue)
	CanFrame *aframe = check_and_cast<CanFrame *>(a);
	CanFrame *bframe = check_and_cast<CanFrame *>(b);

	if ( aframe->getMessageID() < bframe->getMessageID()) {
		return -1;
	} else if (aframe->getMessageID() > bframe->getMessageID()) {
		return 1;
	} else {
		return 0;
	}
}

int CanControllerBase::MessageQueue::packetCompareFifo(cObject *a, cObject *b)
{
	// only used for FIFO queue
	return 1;
}
