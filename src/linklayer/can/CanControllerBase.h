/*
 * Copyright (C) 2013 Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __INET_CAN_CONTROLLER_BASE_H
#define __INET_CAN_CONTROLLER_BASE_H

#include "INETDefs.h"

class CanFrame;
class CanTraffic;

#define FIFO_QUEUE 1
#define PART_PRIORITY_QUEUE 2
#define FULL_PRIORITY_QUEUE 3

/**
 * Base class for CAN Controller implementations.
 */
class INET_API CanControllerBase : public cSimpleModule, public cListener
{
 protected:
    enum CanTransmitState {
        TX_IDLE_STATE = 1,
        TX_WAITING_STATE,
    };

    enum CanReceiveState {
        RX_IDLE_STATE = 1,
        RX_RECEIVING_STATE,
    };

    class MessageQueue {		// Sending message queue of CAN Controller
	protected:
		cQueue queue;
		int queueLimit;			// max queue length

	protected:
		static int packetCompareFifo(cObject *a, cObject *b);;  // FIFO
		static int packetComparePri(cObject *a, cObject *b); // PAUSE frames have higher priority

	public:
		MessageQueue(const char* name = NULL, int limit = 100, int qKind = 1) {
			switch(qKind) {
			case FIFO_QUEUE:
				queue = cQueue(name, packetCompareFifo);
				break;
			case PART_PRIORITY_QUEUE:
			case FULL_PRIORITY_QUEUE:
				queue = cQueue(name, packetComparePri);
				break;
			}
			queueLimit = limit;
		}

		//MessageQueue(const char* name = NULL, int limit = 0) : queue(name), queueLimit(limit) {} // for FIFO queue
		void insertFrame(cObject *obj) { queue.insert(obj); }
		cObject *pop() { return queue.pop(); }
		cObject *getQueueFirst() { return queue.front(); }
		bool empty() const { return queue.empty(); }
		int getQueueLimit() const { return queueLimit; }
		bool isFull() const { return queueLimit != 0 && queue.length() > queueLimit; }
		int length() const { return queue.length(); }
		void insertFrameBefore(cObject *where, cObject *obj) { queue.insertBefore(where, obj);}
		void insertFrameAfter(cObject *where, cObject *obj) { queue.insertAfter(where, obj);}
	};

	// configuration
	bool connected;	// true if connected to a network, set automatically by exploring the network configuration
	bool disabled;	// true if the MAC is disabled, defined by the user

	// gate pointers, etc.
	MessageQueue txQueue;               // the output queue
	cChannel *transmissionChannel;  // transmission channel
	cGate *physInGate;              // pointer to the "phys$i" gate
	cGate *physOutGate;             // pointer to the "phys$o" gate
	cGate *upperLayerInGate;        // pointer to the "upperLayerIn" gate
	int upperLayerInGatebaseId;
	int upperLayerInGatesize;

	// temporal buffer for sending message. That's only used in full priority queue.
	CanFrame *tempFrame;
	// registers for setting message filter
	std::vector<int> filterRegs;
	int filterRegNum;

	// state
	CanTransmitState transmitState; // "transmit state" of the MAC
	CanReceiveState receiveState;   // "receive state" of the MAC
	int queueKind; // kinds of sending message queue
	int queueLimit; // length of sending message queue

	// statistics
	unsigned long numFramesSent;
	unsigned long numFramesReceivedOK;
	unsigned long numBytesSent;        // includes Cannet frame bytes with preamble
	unsigned long numBytesReceivedOK;  // includes Cannet frame bytes with preamble
	unsigned long numFramesPassedToHL; // frames passed to higher layer

	static simsignal_t rxPkOkSignal;
	static simsignal_t packetSentToUpperSignal;
	static simsignal_t packetReceivedFromUpperSignal;
	static simsignal_t busWaitStartSignal;
	static simsignal_t busTransmitStartSignal;
	static simsignal_t messageIDSignal;
	static simsignal_t dropmessageIDSignal;
	static simsignal_t queueLengthSignal;

 public:
	CanControllerBase();
	virtual ~CanControllerBase();

 protected:
	// initialization
	virtual void initialize();
	virtual void initializeStatistics();

	// finish
	virtual void finish();

	// display
	virtual void updateDisplayString();
	virtual void updateConnectionColor(int txState);
};

#endif
