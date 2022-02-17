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
import inet.applications.can.CanAppSrv;
import inet.applications.can.CanAppCli;

module CanStandardHost
{
    parameters:
//        string queueType = default("");
        @node();
        @labels(node,can-node);
        @display("i=device/pc2");
        xml messageSet;
    gates:
        inout ethg @labels(CanFrame-conn);
    submodules:
        srv: CanAppSrv {
            parameters:
                @display("p=149,77,r");
                message = messageSet;
        }
        rcv: CanAppCli {
            parameters:
                @display("p=269,77,r");
        }
        ctl: CanController {
            parameters:
                @display("p=200,272;q=txQueue");
        }
    connections allowunconnected:
        ctl.phys <--> ethg;
        srv.out --> ctl.upperLayerIn++;
        srv.in <-- ctl.upperLayerOut++;
        rcv.out --> ctl.upperLayerIn++;
		rcv.in <-- ctl.upperLayerOut++;
}
