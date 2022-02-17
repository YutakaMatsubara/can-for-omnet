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

#ifndef __INET_CANBUS_H
#define __INET_CANBUS_H

#include <vector>

#include "INETDefs.h"
#include "CanFrame_m.h"

#define ARBITRATION_REQUEST   100
#define TRANSMIT_END          200
#define BUSLOAD_REQUEST 	  300

#define ARBITRATION_PERIOD 0.000002 // required time for arbitration (time to be sent for 1 bit data)
#define INVALID_NODEID  (~(uint)0)

class INET_API CanBus : public cSimpleModule, cListener
{
 protected:
    enum CanBusState
    {
        IDLE_STATE = 1,
		ARBITRATING_STATE,
		TRANSMITTING_STATE
    };
	
    /**
     * Implements the physical locations on the bus where each
     * network entity is connected to on the bus
     */
    struct BusTap
    {
        int id;					// which tap is this
    };

    // configuration
    double  propagationSpeed;  // propagation speed of electrical signals through copper
    BusTap *tap;   // array of BusTaps: physical locations taps where that connect stations to the bus
    int numTaps;   // number of tap points on the bus
    int inputGateBaseId;  // gate id of ethg$i[0]
    int outputGateBaseId; // gate id of ethg$o[0]
    int calcmode; // mode to calculate length of stuff bits. Two modes are implemented.

    // state
    bool dataratesDiffer;
    CanBusState busState;
	uint *sendRequest;
	cMessage **sendRequestCanMessage;
	bool *arbitrationFinish; // flag shows finish of arbitration
	bool *receiveFinish; // flag shows finish of received a message.

    // statistics
    long numMessages;			// number of messages handled
    long numBits; // number of bits processed in the period for calculating bus workload
	
    // self messages
    cMessage *arbReqMsg;		// start of arbitration
    cMessage *traEndMsg;		// finish of transmittion on CAN bus
    cMessage *blReqMsg;	// requirement for starting calculation of workload of CAN bus

    // message sending to CAN bus
    cMessage *maxPriMsg;

    static simsignal_t busTransmitStartSignal;
    static simsignal_t messageIDSignal;
    static simsignal_t busloadSignal;

    double arbitration_period;
    double busload_period;

 public:
    CanBus();
    virtual ~CanBus();

 protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void printState();
    virtual void finish();

 private:
	void handleCanMessageFromNode(cMessage *msg);
	void handleArbitrationRequest();
	void handleTransmitEnd();
	void handleBusloadRequest();
	double calcBitLengthByVenet(int mode, cMessage *msg);
};

#endif
