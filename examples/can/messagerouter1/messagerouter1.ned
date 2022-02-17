//
// Copyright (C) 2013 Embedded and Real-Time Systems Laboratory
//             Graduate School of Information Science, Nagoya Univ., JAPAN
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//

package inet.examples.can.messagerouter1;

import ned.DatarateChannel;
import inet.util.ThruputMeteringChannel;
import inet.nodes.can.CanSrvHost;
import inet.nodes.can.CanCliHost;
import inet.nodes.can.CanMessageRouterHost;
import inet.linklayer.can.CanBus;

network CanMessageRouter
{
    types:
        channel C extends DatarateChannel
        {
            delay = 0.1us;
            datarate = 1Mbps;
        }
    submodules:
        Sender1: CanSrvHost {
            parameters:
                @display("p=98,132");
        }
        Sender2: CanSrvHost {
            parameters:
                @display("p=110,267");
        }
        Receiver1: CanCliHost {
            parameters:
                @display("p=231,132");
        }
        Receiver2: CanCliHost {
            @display("p=244,284");
        }
        bus1: CanBus {
            parameters:
                propagationSpeed = 500kbps; // 1us = 200m
                @display("p=250,67;b=400,6;o=#408060");
            gates:
                ethg[3];
        }
        bus2: CanBus {
            parameters:
                propagationSpeed = 500kbps; // 1us = 200m
                @display("p=250,207;b=400,6;o=#408060");
            gates:
                ethg[3];
        }
        router: CanMessageRouterHost {
            parameters:
                @display("p=383,140");
            gates:
                ethg[2];
        }
    connections:
        bus1.ethg[0] <--> C <--> Sender1.ethg;
        bus2.ethg[0] <--> C <--> Sender2.ethg;
        bus1.ethg[1] <--> C <--> Receiver1.ethg;
        bus2.ethg[1] <--> C <--> Receiver2.ethg;
        router.ethg[0] <--> C <--> bus1.ethg[2];
        router.ethg[1] <--> C <--> bus2.ethg[2];
}
