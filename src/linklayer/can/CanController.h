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

#ifndef __INET_CANCONTROLLER_H
#define __INET_CANCONTROLLER_H

#include "INETDefs.h"
#include "CanControllerBase.h"

//class IPassiveQueue;

class INET_API CanController : public CanControllerBase
{
 public:
    CanController();
    virtual ~CanController();

 protected:
    virtual void initialize();
    virtual void initializeStatistics();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

 protected:
    virtual void processFrameFromUpperLayer(CanFrame *msg);
    virtual void processMsgFromNetwork(CanTraffic *msg);
    virtual void printState();

 private:
	void handleSendPermit();
	void handleArbitrationFinish();
	void handleCanMessageFromBus(CanFrame *msg);
};

#endif
