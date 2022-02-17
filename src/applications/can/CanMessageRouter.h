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

#ifndef __INET_CanMessageRouter_H
#define __INET_CanMessageRouter_H

#include <stdlib.h>
#include <string>
#include "INETDefs.h"
#include "CanFrame_m.h"
#include <map>

#define NUM_MESSAGEID 40
/**
 * Implements the shared coaxial cable in classic Ethernet. See the NED file
 * for more description.
 */
class INET_API CanMessageRouter : public cSimpleModule, cListener
{
  protected:
    // configuration
    int numGates;   // number of bus points on the CAN Message Router
    int inputGateBaseId;  // gate id of in[0]
    int outputGateBaseId; // gate id of out[0]
    bool **routingTable;
    cXMLElement *root;
	std::map<std::string,int> NGTable; // Name-Gate Table

  public:
    CanMessageRouter();
    virtual ~CanMessageRouter();

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

 private:
	void handleCanMessageFromBus(CanFrame *msg);
	void createRoutingTable();
	unsigned long ToDec(const char str[ ]);

};

#endif
