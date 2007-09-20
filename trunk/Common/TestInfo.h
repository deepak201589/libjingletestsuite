/*
*   Copyright (C) 2007 Carnegie Mellon University
*   This file is part of the libjingle file transfer  Test Suite.
*
*   The Test Suite is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 3 of the License, or
*   any later version.
*
*   The Test Suite is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*   
*   Contact the original project authors by visiting
*   <http://dogbert.mse.cs.cmu.edu/MSE2007/Projects/Google/team.html>.
*/
/*
* Relative Path: /Common/TestInfo.h
* 
* Test info structure that contains test scenario information.
* This structure is used both by SenderAgent and ReceiverAgent.
*/

#ifndef __testinfo_h
#define __testinfo_h

#include "common.h"
#include <string>
#include "QuickHash.h"

using namespace std;
using namespace QuickHash;

/* OP_CODE declaration */

/* Client side */
#define OP_INFO			1
#define OP_REPORT		2
#define OP_CLOSE		3

/* Server side */
#define OP_INFO_ACK		4
#define OP_REPORT_ACK	5

/* test info structure declaration */

#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT 8000


typedef struct testinfo TestInfo;

struct testinfo {
	int OpCode;
	int SeqID;
	int ScenarioID;
	int ErrorCode;
	char HashCode[ CMD5::HEXDIGESTSIZE ];
	char RecvPath[256];
	string Filename;
};

#endif