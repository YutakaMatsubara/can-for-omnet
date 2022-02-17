/*
 * Copyright (C) 2013 Embedded and Real-Time Systems Laboratory
 *             Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __INET_CAN_H
#define __INET_CAN_H

#include "INETDefs.h"

#define MAX_CAN_DATA_BYTES              8
#define MAX_CAN_FRAME_BYTES            14
#define MIN_CAN_FRAME_BYTES             1

#define CAN_TXRATE                      1000000.0   /* 1 Mbit/sec (in bit/s) */

#define CAN_HEADER_FRAME_BYTES        (6+6+2+4) 
#define CAN_SEND_REQUEST_BYTES        (2)
#define CAN_DATA_LENGTH      (8) 

#define MAX_CAN_MESSAGE_ID     2100

#endif
