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

#include "CanMessageRouter.h"

Define_Module(CanMessageRouter);

static cEnvir& operator<<(cEnvir& out, cMessage *msg)
{
    out.printf("(%s)%s", msg->getClassName(), msg->getFullName());
    return out;
}

CanMessageRouter::CanMessageRouter()
{
}

CanMessageRouter::~CanMessageRouter()
{
}

void CanMessageRouter::initialize()
{
	// initialize the positions where the hosts connects to the bus
	numGates = gateSize("in");
	inputGateBaseId = gateBaseId("in");
	outputGateBaseId = gateBaseId("out");
	
	createRoutingTable();
}

void CanMessageRouter::handleMessage(cMessage *msg)
{
	EV << "CanMessageRouter: message " << msg << " received\n";

	if (!msg->isSelfMessage()) {
		CanTraffic *can_msg = check_and_cast<CanTraffic *>(msg);
		switch (can_msg->getType()) {
		case CAN_MESSAGE:
			handleCanMessageFromBus(check_and_cast<CanFrame*>(msg));
			break;
		default:
			error("Message with unexpected message type %d", can_msg->getType());
		}
	} else {
		EV << "CanMessageRouter: Self-message " << msg << " received\n";
	}
}



void CanMessageRouter::handleCanMessageFromBus(CanFrame *msg)
{
	int i;
	EV << "CanMessageRouter: Received CAN Frame `" << msg->getName() << "'\n";

	uint messageid = msg->getMessageID();

	// find the bus where msg should be sent according to message ID
	// of msg. then 
	 for (i = 0; i < numGates; i++) {
		 if (routingTable[messageid][i]) {
			 cGate* ogate = gate(outputGateBaseId + i);
			 if (ogate->isConnected()) {
				 // send out on gate
				 cMessage *msg2 = msg->dup();
				 // send the message to a node connected to TAP
				 send(msg2, ogate);
			 }
		 }
	 }
	EV << "CanMessageRouter: Sent CAN Message `" << msg->getName() << "'\n";
	delete msg;
}


/******************************************/
/* Example of routing table
 * <RoutingMap ID="1">
 *   <MessageInfo ID="15a">
 *      <RoutingInfo Name="CGW" Send="0"/>
 *      <RoutingInfo Name="CAN1" Send="0"/>
 *      <RoutingInfo Name="Ethernet" Send="1"/>
 *   </MessageInfo>
 * </RoutingMap>
 */
/******************************************/
void CanMessageRouter::createRoutingTable()
{
	int i, j;

	// initialize
	routingTable = new bool*[MAX_CAN_MESSAGE_ID];
	for (i = 0; i < MAX_CAN_MESSAGE_ID; i++) {
		routingTable[i] = new bool[numGates];
	}

	//	xml routingmap = xmldoc("RoutingMap.xml"); // ned,iniで読み込む
	root = (par("routingmap").xmlValue());

	// list of parent nodes (MessageInfo) which have RoutingInfo as a child node.
	cXMLElementList MessageInfoElements = root->getChildrenByTagName("MessageInfo");
	EV << "Elements : " << (int)MessageInfoElements.size() << endl; // total number of messages

	// generate a table [name : gate number]
	int CGWApps = par("numCGWApps");
	int CanBuses = par("numCanBuses");
	int EthernetBuses = par("numEthernetBuses");
	for (i = 0; i < CGWApps; i++) {
		NGTable.insert( std::map<std::string, int>::value_type( "CGW", i ) ); // gate number of CGW is 0
	}
	// for CAN bus
	for (i = 0; i < CanBuses ; i++) {
		char CanBusName[32];
		sprintf(CanBusName, "CAN%d", i+1);
		NGTable.insert(std::map<std::string, int>::value_type(CanBusName, CGWApps + i)); // CAN1ならCGW数+ゲート番号1
	}
	// for Ethernet bus
	for (i = 0; i < EthernetBuses ; i++) {
		char EtherBusName[32];
		sprintf(EtherBusName, "Ethernet");
		// gate number of Ethernet1 is sum of (number of CGW + number of CAN buses + 1)
		NGTable.insert( std::map<std::string, int>::value_type( EtherBusName, CGWApps + CanBuses + i  ) ); 
	}

	// print element of the generated table
	std::map<std::string,int>::iterator it = NGTable.begin();
	while(it != NGTable.end()) {
		EV << (*it).first << ":" << (*it).second << endl;
		++it;
	}

	// initialization
	for (i = 0; i < MAX_CAN_MESSAGE_ID; i++) {
		for (j = 0; j < numGates; j++) {
			routingTable[i][j] = false;
		}
	}
	// generate routing information

	for (i = 0; i < (int)MessageInfoElements.size(); i++) {
		const char *id = MessageInfoElements[i]->getAttribute("ID");
		unsigned long messageID = ToDec(id); // convert hex values to dec values
		//unsigned long messageID = atoi(id);//xmlで10進数表示されている場合はこちら

		// list of child nodes(RoutingInfo)
		cXMLElementList MessageInfo = MessageInfoElements[i]->getChildren();
		for (j = 0; j < numGates; j++) { 
			// read routing information by 1 line
			cXMLElement *MessageInfoChild = MessageInfo[j];
			// generate a routing table by using Name
			if (atoi(MessageInfoChild->getAttribute("Send")) == 1) {
				int value;
				const char *name = MessageInfoChild->getAttribute("Name");

				// generate iterator
				std::map<std::string, int>::iterator itr;
				// find value from key(Name)
				itr = NGTable.find(name);

				if (itr != NGTable.end()) {
					value = itr->second;
				} else {
					EV << "cannot find value corresponding to " << name << endl;
				}
				routingTable[messageID][value] = true; // ルーティング情報代入
			}
		}
	}

	// print the generated routing table
	char id[32];
	//EV << "MessageID: " << i << " | true/false" ;
	EV << "********************************************\n";
	for (i = 0; i < MAX_CAN_MESSAGE_ID; i++) {
		sprintf(id," 0x%04x ",i);
		EV << "MessageID: " << i << "(" << id << ") | " ;
		for (j = 0; j < numGates; j++) {
			EV << routingTable[i][j] << " ";
		}
		EV << endl;
	}
	EV << "********************************************\n";
}

void CanMessageRouter::finish()
{
    simtime_t t = simTime();
    recordScalar("simulated time", t);
}

// convert a string including hex values to dec values
unsigned long CanMessageRouter::ToDec(const char str[ ])
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
