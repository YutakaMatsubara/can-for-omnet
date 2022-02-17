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

package inet.examples.can.messagerouter2;

import ned.DatarateChannel;
import inet.util.ThruputMeteringChannel;
import inet.nodes.can.CanSrvHost;
import inet.nodes.can.CanCliHost;
import inet.nodes.can.CanMessageRouterHost;
import inet.linklayer.can.CanBus;

network CanMessageRouter2
{
    @display("bgb=588,495");
    types:
        channel C extends DatarateChannel
        {
            delay = 0.1us;
            datarate = 1Mbps;
        }
    submodules:
        canBus1: CanBus {
            @display("p=435,103;b=,,rect");
        }
        router: CanMessageRouterHost {
            @display("p=480,275");
            gates:
                ethg[6];
        }
        Sender1: CanSrvHost {
            @display("p=390,43");
        }
        Receiver1: CanCliHost {
            @display("p=520,43");
        }
        canBus2: CanBus {
            //       positions = "0 10 20";
            @display("p=131,103");
        }
        Receiver2: CanCliHost {
            @display("p=216,43");
        }
        Sender2: CanSrvHost {
            @display("p=86,43");
        }
        canBus3: CanBus {
            @display("p=131,225");
        }
        Receiver3: CanCliHost {
            @display("p=216,165");
        }
        Sender3: CanSrvHost {
            @display("p=86,165");
        }
        canBus4: CanBus {
            @display("p=131,335;b=,,rect");
        }
        Receiver4: CanCliHost {
            @display("p=216,275");
        }
        Sender4: CanSrvHost {
            @display("p=86,275");
        }
        canBus5: CanBus {
            //      positions = "0 10 20";
            @display("p=131,459");
        }
        Receiver5: CanCliHost {
            @display("p=216,399");
        }
        Sender5: CanSrvHost {
            @display("p=86,399");
        }
        canBus6: CanBus {
            //     positions = "0 10 20";
            @display("p=435,459");
        }
        Receiver6: CanCliHost {
            @display("p=520,399");
        }
        Sender6: CanSrvHost {
            @display("p=390,399");
        }
    connections allowunconnected:
        Sender6.ethg <--> C <--> canBus6.ethg++;
        Receiver6.ethg <--> C <--> canBus6.ethg++;
        Sender1.ethg <--> C <--> canBus1.ethg++;
        Receiver1.ethg <--> C <--> canBus1.ethg++;
        Sender2.ethg <--> C <--> canBus2.ethg++;
        Receiver2.ethg <--> C <--> canBus2.ethg++;
        Sender3.ethg <--> C <--> canBus3.ethg++;
        Receiver3.ethg <--> C <--> canBus3.ethg++;
        Sender4.ethg <--> C <--> canBus4.ethg++;
        Receiver4.ethg <--> C <--> canBus4.ethg++;
        router.ethg[0] <--> C <--> canBus1.ethg++;
        router.ethg[1] <--> C <--> canBus2.ethg++;
        router.ethg[2] <--> C <--> canBus3.ethg++;
        router.ethg[3] <--> C <--> canBus4.ethg++;
        Sender5.ethg <--> C <--> canBus5.ethg++;
        Receiver5.ethg <--> C <--> canBus5.ethg++;
        router.ethg[4] <--> C <--> canBus5.ethg++;
        router.ethg[5] <--> C <--> canBus6.ethg++;
}
