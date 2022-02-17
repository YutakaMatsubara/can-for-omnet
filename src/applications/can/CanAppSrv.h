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

#ifndef __INET_CANAPPSRV_H
#define __INET_CANAPPSRV_H

#include "INETDefs.h"
#include "CanFrame_m.h"
#include <map>

class INET_API CanAppSrv : public cSimpleModule
{
  protected:
	struct SendMessageInfo{
		int ID;
		int DLC;
		double SendInterval;
		std::vector<double> SendTime;
		double Offset;
	};
	std::map<int,SendMessageInfo> SendMessageInfoList; // key: message ID, value: infomation of a sending message

	// send parameters
    cPar *sendInterval;
    double sendIntervaldouble;
    int messageID;
    std::vector<double> sendTimeList;
    int numsendTime;
    double drift;

    // self messages
    cMessage *sendReqMsg;

    // statistics
    long packetsSent;
    long packetsReceived;
    static simsignal_t sentPkSignal;
    static simsignal_t rcvdPkSignal;

  public:
    CanAppSrv();
    ~CanAppSrv();

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void sendMessage(CanFrame *msg);
    virtual void finish();

 private:
	void handleSelfSendRequest(int MessageID);
	void handleCanMessage(cMessage *msg);
	unsigned long ToDec(const char str[ ]);
};

#endif
