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

import inet.linklayer.ICanController;

simple CanController like ICanController
{
    parameters:
        int txQueueLimit = default(1000);   // maximum number of frames queued up for transmission in the internal queue (only used if queueModule==""); additional frames cause a runtime error
        string filterRegs = default("0");
        int queueKind = default(1); // 1=FIFO, 2=Partial-Priority, 3=Full-priority
        int queueLimit = default(100);
        @display("i=block/rxtx");

        @signal[txPk](type=CanFrame);
        @signal[rxPkOk](type=CanFrame);
        @signal[txPausePkUnits](type=long);
        @signal[rxPausePkUnits](type=long);
        @signal[rxPkFromHL](type=CanFrame);
        @signal[dropPkNotForUs](type=CanFrame);
        @signal[dropPkBitError](type=CanFrame);
        @signal[dropPkFromHLIfaceDown](type=CanFrame);
        @signal[dropPkIfaceDown](type=EtherTraffic);        // emitted at begin of receiving
        @signal[packetSentToLower](type=CanFrame);
        @signal[packetReceivedFromLower](type=CanFrame);
        @signal[packetSentToUpper](type=CanFrame);
        @signal[packetReceivedFromUpper](type=CanFrame);
        @signal[collision](type=long);
        @signal[backoff](type=long);
        @signal[busWaitStart](type=CanFrame);
        @signal[busTransmitStart](type=CanFrame);
        @signal[messageID](type=long);
        @signal[dropmessageID](type=long);
        @signal[queueLength](type=long);

        @statistic[txPk](title="packets transmitted"; source=txPk; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[rxPkOk](title="packets received OK"; source=rxPkOk; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[passedUpPk](title="packets passed to higher layer"; source=packetSentToUpper; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[txPausePkUnits](title="pause units sent"; record=count,sum,vector; interpolationmode=none);
        @statistic[rxPausePkUnits](title="pause units received"; record=count,sum,vector; interpolationmode=none);
        @statistic[rxPkFromHL](title="packet bytes from higher layer"; source=rxPkFromHL; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[droppedPkIfaceDown](title="packets dropped/interface down"; source=dropPkIfaceDown; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[droppedPkBitError](title="packets dropped/bit error"; source=dropPkBitError; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[droppedPkNotForUs](title="packets dropped/not for us"; source=dropPkNotForUs; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[collision](title="collision"; record=count,vector; interpolationmode=none);
        @statistic[backoff](title="backoff"; record=count,vector; interpolationmode=none);
		@statistic[busWaitStart](title="bus wait start time"; source=busWaitStart; record="vector(packetBytes)";interpolationmode=none);
		@statistic[busTransmitStart](title="bus transmit start time"; source=busTransmitStart; record="vector(packetBytes)";interpolationmode=none);
		@statistic[messageID](title="message ID"; source=messageID;record=vector;interpolationmode=none);
        @statistic[dropmessageID](title="dropped message ID"; source=dropmessageID; record=vector,count,sum;interpolationmode=none);
		@statistic[queueLength](title="queue length"; source=queueLength; record=vector,histogram;interpolationmode=none);

    gates:
        input upperLayerIn[] @labels(CanFrame);
        output upperLayerOut[] @labels(CanFrame);
        inout phys @labels(CanFrame); // to physical layer or the network
}
