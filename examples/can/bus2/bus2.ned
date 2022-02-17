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

package inet.examples.can.bus2;

import ned.DatarateChannel;
import inet.util.ThruputMeteringChannel;
import inet.nodes.can.CanSrvHost;
import inet.nodes.can.CanCliHost;
import inet.nodes.can.CanMessageRouterHost;
import inet.linklayer.can.CanBus;

network CanBus2
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
                @display("p=100,150");
        }
        Sender2: CanSrvHost {
            parameters:
                @display("p=200,150");
        }
        Receiver: CanCliHost {
            parameters:
                @display("p=300,150");
        }
        bus: CanBus {
            parameters:
                //   positions = "0 10 20";
                //propagationSpeed = 2e8 mps; // 1us = 200m
                @display("p=250,100;b=400,6;o=#408060");
            gates:
                ethg[3];
        }
    connections:
        bus.ethg[0] <--> C <--> Sender1.ethg;
        bus.ethg[1] <--> C <--> Sender2.ethg;
        bus.ethg[2] <--> C <--> Receiver.ethg;
}

