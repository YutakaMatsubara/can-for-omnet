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
#include <math.h>

#include "CanAppCli.h"
#include "CanApp_m.h"

Define_Module(CanAppCli);

simsignal_t CanAppCli::rcvdPkSignal = SIMSIGNAL_NULL;
simsignal_t CanAppCli::messageIDSignal = SIMSIGNAL_NULL;
simsignal_t CanAppCli::DataSignal = SIMSIGNAL_NULL;

CanAppCli::CanAppCli()
{
}

CanAppCli::~CanAppCli()
{
}

void CanAppCli::initialize()
{
    // statistics
    packetsReceived = 0;
    rcvdPkSignal = registerSignal("rcvdPk");
    messageIDSignal = registerSignal("messageID");
    DataSignal = registerSignal("Data");

    WATCH(packetsReceived);
}

void CanAppCli::handleMessage(cMessage *msg)
{
	receiveCanFrame(check_and_cast<CanFrame*>(msg));
}

void CanAppCli::receiveCanFrame(CanFrame *msg)
{
	EV << "Received CAN Frame `" << msg->getName() << msg->getCreationTime()<< "'\n";
	EV << "msg->getCreationTime: " << msg->getCreationTime() << endl;
    packetsReceived++;
    cPacket *packet = PK(msg);

    emit(rcvdPkSignal, packet);
    emit(messageIDSignal,msg->getMessageID());
    emit(DataSignal,msg->getData());

    delete msg;
}

void CanAppCli::finish()
{
}
