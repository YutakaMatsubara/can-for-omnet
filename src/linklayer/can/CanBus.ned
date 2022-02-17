//
// Copyright (C) 2013 Embedded and Real-Time Systems Laboratory
//             Graduate School of Information Science, Nagoya Univ., JAPAN
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

package inet.linklayer.can;

simple CanBus
{
    parameters:
        @node();
        @labels(node,can-node);
        @display("b=200,5,,,,1");

        double propagationSpeed @unit(kbps) = default(1000kbps); // signal propagation speed on the bus
        int calcmode = default(1);
        double arbitrationPeriod = default(0.000002); // waiting time for arbitration (default: 2[us] which is time required for sending 1 bits in 500kbps bus)
        double busloadPeriod = default(1); // period for calculating workload of CAN bus (default: 1[s])
        
        @signal[messageID](type=long);
        @signal[busload](type=long);
        
        @statistic[busTransmitStart](title="bus transmit start";source=busTransmitStart;record=count);
  		@statistic[busTransmitStartTime](title="bus transmit start time"; source="messageAge(busTransmitStart)"; record=vector;interpolationmode=none);
		@statistic[messageID](title="message ID"; source=messageID;record=vector;interpolationmode=none);
 		@statistic[busload](title="bus load"; source=busload;record=vector,histogram;interpolationmode=none);
 
    gates:
        inout ethg[] @labels(CanFrame-conn);  // to stations; each one represents a tap
}
