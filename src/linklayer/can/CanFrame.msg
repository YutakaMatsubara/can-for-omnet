//
// Copyright (C) 2013 Embedded and Real-Time Systems Laboratory
//              Graduate School of Information Science, Nagoya Univ., JAPAN
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

cplusplus {{
#include "Can.h"

}}

class noncobject MessageId;

enum CanTrafficType
{
	CAN_MESSAGE = 0x00;
	CAN_SEND_REQUEST = 0x01;
	CAN_SEND_PERMIT = 0x02;
	CAN_ARBITRATION_FINISH = 0x03;
	CAN_MESSAGES = 0x04;
}

packet CanTraffic
{
    short type enum(CanTrafficType);
}

packet CanFrame extends CanTraffic
{
	  int MessageID;
	  int Data;
      int frameByteLength;
}

packet CanSendRequest extends CanTraffic
{
	  int requestMessageID = 0;
}

packet CanSendPermit extends CanTraffic
{
}

packet CanArbitrationFinish extends CanTraffic
{
}

packet CanFrames extends CanFrame
{
}
