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

#ifndef __INET_CANAPPCLI_H
#define __INET_CANAPPCLI_H

#include "INETDefs.h"
#include "CanFrame_m.h"

class INET_API CanAppCli : public cSimpleModule
{
 protected:
    // receive statistics
    long packetsReceived;
    static simsignal_t rcvdPkSignal;
    static simsignal_t messageIDSignal;
    static simsignal_t DataSignal;

 public:
    CanAppCli();
    ~CanAppCli();

 protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
    virtual void receiveCanFrame(CanFrame *msg);
};

#endif
