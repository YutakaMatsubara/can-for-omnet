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

package inet.linklayer;

moduleinterface ICanController
{
    parameters:
        @display("i=block/rxtx");
    gates:
        input upperLayerIn[] @labels(CanFrame);    // to ~CanLLC or ~MACRelayUnitPP
        output upperLayerOut[] @labels(CanFrame);  // to ~CanLLC or ~MACRelayUnitPP
        inout phys @labels(CanFrame); // to physical layer or the network
}
