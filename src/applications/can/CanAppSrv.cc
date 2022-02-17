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

#include "CanAppSrv.h"
#include "CanFrame_m.h"

Define_Module(CanAppSrv);

simsignal_t CanAppSrv::sentPkSignal = SIMSIGNAL_NULL;
simsignal_t CanAppSrv::rcvdPkSignal = SIMSIGNAL_NULL;

CanAppSrv::CanAppSrv()
{
	sendReqMsg = NULL;
}

CanAppSrv::~CanAppSrv()
{
	cancelAndDelete(sendReqMsg);
}

void CanAppSrv::initialize()
{
    // statistics
    packetsSent = packetsReceived = 0;
    sentPkSignal = registerSignal("sentPk");
    rcvdPkSignal = registerSignal("rcvdPk");
	sendInterval = &par("sendInterval");
    drift = par("drift");
    simtime_t startTime = par("startTime");

    WATCH(packetsSent);
    WATCH(packetsReceived);
    WATCH(drift);

    /******************************************/
    /* Example of XML
     *
     * <NodeInfo>
   	 * 	   <Node ID="ECU1">
     *	  	  <SendMessage SendTime="0" ID="15a" DLC="8" SendInterval="10" Offset="1"/>
     *	  	  <SendMessage SendTime="0" ID="20b" DLC="8" SendInterval="2" Offset="1"/>
     *	  	  <SendMessage SendTime="1 10 100" ID="25c" DLC="8" SendInterval="0" Offset="0"/>
   	 * 	   </Node>
   	 * </NodeInfo
   	 *
     */
    /******************************************/
    // read a list of messages sent by myself
    cXMLElementList messages = ((par("message").xmlValue())->getChildrenByTagName("SendMessage"));
    cXMLElement *message;

    // initialize each message to be sent
    for (int i = 0; i < (int)messages.size(); i++) {
    	message = messages[i];

    	// generate info. of a sending message
    	SendMessageInfo smInfo;
    	smInfo.ID = ToDec(message->getAttribute("ID"));
    	smInfo.DLC = atoi(message->getAttribute("DLC"));
    	smInfo.SendInterval = atof(message->getAttribute("SendInterval")) / 1000; // send interval [s]. Unit of input value is ms.
    	smInfo.Offset = atof(message->getAttribute("Offset")) / 1000000; // offset [s]. Unit of input value is us.
    	EV << "ID : " << smInfo.ID << "DLC : " << smInfo.DLC << " SendInterval : " << smInfo.SendInterval;

    	// a list of sending time of each event-driven message is
		// input as string (ex. SendTime="1 10 100"). The list is
		// transformed to an array of int values (ex. 1, 10, 100).
    	const char *SendTimes = message->getAttribute("SendTime");
    	smInfo.SendTime = cStringTokenizer(SendTimes).asDoubleVector();
    	cStringTokenizer tokenizer(SendTimes);

    	// count number of sending time 
    	numsendTime = 0;
    	const char *token;
    	while ((token = tokenizer.nextToken()) != NULL)	{
			numsendTime++;
		}

    	EV << " SendTime : ";
    	for (int j = 0; j < numsendTime; j++) {
    		smInfo.SendTime[j] = smInfo.SendTime[j] / 1000;
    		EV << smInfo.SendTime[j] << " ";
    	}
    	EV << endl;

    	// hash (key: message ID, data: array of sending time) is
    	// inserted to SendMessaageInfoList
    	SendMessageInfoList.insert(std::map<int,SendMessageInfo>::value_type(smInfo.ID,smInfo));

    	// send messages to be sent at t=0
    	if (smInfo.SendInterval == 0) {
			// Case of event-driven message
    		sendReqMsg = new cMessage("SendRequest1", smInfo.ID);
    		for (int j = 0; j < numsendTime; j++) {
    			EV << "time1:" << (1+drift) << endl;
    			EV << "time2:" << startTime << endl;
    			EV << "time3:" << (static_cast<double>(smInfo.SendTime[j])*(1+drift)) << endl;
    			scheduleAt(startTime + (double)((smInfo.SendTime[j])*(1+drift)), sendReqMsg->dup());
    		}
    	} else { 
			// Case of time-driven message
    		sendReqMsg = new cMessage("SendRequest2", smInfo.ID);
			scheduleAt(startTime+(smInfo.Offset)*(1+drift), sendReqMsg);
    	}
    }

	WATCH(numsendTime);
	WATCH(sendIntervaldouble);
    WATCH(messageID);
}

void CanAppSrv::handleMessage(cMessage *msg)
{
	if (!msg->isSelfMessage()) {
		CanFrame *can_msg = check_and_cast<CanFrame *>(msg);
		switch (can_msg->getType()) {
		case CAN_MESSAGE:
			break;		
		default:
			error("Message with unexpected message type %d", can_msg->getType());
		}
	} else {
		EV << "CanAppSrv: Self-message " << msg << " received\n";
		handleSelfSendRequest(msg->getKind());
	}  
	delete msg;
}

void CanAppSrv::handleSelfSendRequest(int MessageID)
{
	// generate a CAN message according to MessageID
	std::map<int,SendMessageInfo>::iterator itr;
	itr = SendMessageInfoList.find(MessageID);
	CanFrame *msg = new CanFrame("hoge");
	SendMessageInfo value;
	
	if (itr != SendMessageInfoList.end()) {
		// マップが end では無い場合（つまりキーにヒットする値が存在し
		// た場合）値も取得します。
		value = itr->second;
		// CANメッセージの生成
		msg->setMessageID(value.ID);
		msg->setData(0); //GW通過フラグに使用する（最初は0で，GWを1つ通過するごとに1ずつインクリメントする）
		msg->setFrameByteLength(value.DLC);
		char msgName[32];
		sprintf(msgName,"0x%04x",msg->getMessageID());
		msg->setName(msgName);
	} else {
		// MessageID is not included in SendMessageInfoList
		EV << "MessageID " << MessageID <<"is not included in SendMessageInfoList." << endl;
	}

	EV << "CanAppSrv: Generating CAN Message `" << msg->getName() <<"("<< msg->getMessageID() << ")'\n";
	sendMessage(msg);
	EV << "CanAppSrv: Sent CAN Message `" << msg->getName() << "'\n";

	// schedule a sending request for next message
	if (value.SendInterval != 0) {
		sendReqMsg = new cMessage("SendRequest3", value.ID);
		scheduleAt(simTime() + (value.SendInterval)*(1+drift), sendReqMsg);
	}
}

void CanAppSrv::handleCanMessage(cMessage *msg)
{
    EV << "CanAppSrv: Received packet `" << msg->getName() << "'\n";
    CanFrame *req = check_and_cast<CanFrame *>(msg);
    packetsReceived++;
    emit(rcvdPkSignal, req);

    long MessageID = req->getMessageID() + 1;
    long Data = req->getData() + 1;
    char msgname[30];
    strcpy(msgname, msg->getName());
    delete msg;
	EV << "CanAppSrv: Generating packet `" << msgname << "'\n";

	CanFrame *new_msg = new CanFrame(msgname);
	new_msg->setMessageID(MessageID);
	new_msg->setData(Data);
	new_msg->setFrameByteLength(2);
	sendMessage(new_msg);
}

void CanAppSrv::sendMessage(CanFrame* msg)
{
	emit(sentPkSignal, msg);
	send(msg, "out");
	packetsSent++;
}

void CanAppSrv::finish()
{
}

// convert a string including hex values to dec values
unsigned long CanAppSrv::ToDec(const char str[ ])
{
   short i = 0;
   short n;
   unsigned long x = 0;
   char c;

   while (str[i] != '\0') {
	   // str[i] is not the tail charactor
       if ('0' <= str[i] && str[i] <= '9') {
		   // from '0' to '9'
           n = str[i] - '0';	// convert to a digit
	   } else if ('a' <= (c = tolower(str[i])) && c <= 'f') {
		   // from 'a' to 'f'
           n = c - 'a' + 10;	// convert to a digit
	   } else {        
		   // others
    	   printf("%s",str);
           printf("invalid charactor \n");
           exit(0);
       }
       i++;
       x = x * 16 + n;
   }
   return (x);
}
