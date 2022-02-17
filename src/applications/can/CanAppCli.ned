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

package inet.applications.can;

simple CanAppCli
{
    parameters:
        @display("i=block/app");
        @signal[rcvdPk](type=cPacket);
        @signal[messageID](type=long);
        @signal[Data](type=long);

        @statistic[rcvdPk](title="packets received"; source=rcvdPk; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[endToEndDelay](title="end-to-end delay"; source="messageAge(rcvdPk)"; unit=s; record=histogram,vector; interpolationmode=none);
		@statistic[messageID](title="message ID"; source=messageID;record=vector;interpolationmode=none);
		@statistic[Data](title="Data"; source=Data;record=vector;interpolationmode=none);
    gates:
        input in @labels(CanAppCli/up);
        output out @labels(CanAppCli/down);
}
