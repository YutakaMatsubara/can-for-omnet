//
// Copyright (C) 2013 Embedded and Real-Time Systems Laboratory
//             Graduate School of Information Science, Nagoya Univ., JAPAN
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package inet.nodes.can;

import inet.linklayer.can.CanController;
import inet.applications.can.CanMessageRouter;

//
// TODO auto-generated type
//
module CanMessageRouterHost
{
    parameters:
        string queueType = default(""); // DropTailQueue, DropTailQoSQueue, REDQueue, or empty to use the internal queue
        @node();
        @labels(node,can-node);
        @display("i=device/pc2");
        int numBuses = default(0);
    gates:
        inout ethg[] @labels(CanFrame-conn);
    submodules:
        router: CanMessageRouter {
            parameters:
                @display("p=200,60,col");       
        }
        ctl[numBuses]: CanController {
            parameters:
                @display("p=200,300,r,100;q=txQueue");
        }
    connections allowunconnected:
        for i=0..numBuses-1 {
            router.out++ --> ctl[i].upperLayerIn++;
            router.in++ <-- ctl[i].upperLayerOut++;
            ctl[i].phys <--> ethg[i];
        }
}
