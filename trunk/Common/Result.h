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
* Relative Path: /Common/Result.h
* This file is the header description of Result
* Result object contains the attributes which are to be written to the results repository
* The attributes returned from a file transfer are written to Results object
* This component is taken by the LibjingleWrapper and sent to TestHelper to write to repository.
*/

#ifndef __results_h
#define __results_h

#pragma once
#include <time.h>
#include <string>
#include <sstream>
#include "QuickHash.h"
#include "Common.h"

using namespace QuickHash;
using namespace std;

#define NAME_MAX	255
#define HASH_MAX	CMD5::HEXDIGESTSIZE

/*
* Class Name: Result
* Purpose: The result object contains all the attributes to be written
*		   to the results repository
* It is a copy of a row in the results repository
* The attributes are private and are accessed or modified using getter and setter methods
*/
class COMMON_API Result
{
public:
	Result(void);
	~Result(void);
	int GetScheduleId();
	int GetScenarioId();
	double GetBandwidth();
	double GetDelay();
	double GetLoss();
	double GetDuplicates();
	char* GetFileName();
	long GetFileSize();
	time_t GetStartTime();
	time_t GetEndTime();
	long GetTimeTaken();
	char* GetProtocol();
	long GetTotalBytesTransferred();
	long GetBytesRetransmitted();
	char* GetSenderHash();
	char* GetReceiverHash();
	string GetInsertQuery();

	void SetScheduleId(int);
	void SetScenarioId(int);
	void SetBandwidth(double);
	void SetDelay(double);
	void SetLoss(double);
	void SetDuplicates(double);
	void SetFileName(char*);
	void SetFileSize(long);
	void SetStartTime(time_t );
	void SetEndTime(time_t );
	void SetTimeTaken(long);
	void SetProtocol(char *);
	void SetTotalBytesTransferred(long);
	void SetBytesRetransmitted(long);
	void SetSenderHash(char*);
	void SetReceiverHash(char*);

private:
	int RunID;
	int ScheduleId;
	int ScenarioId;
	double Bandwidth;
	double Delay;
	double Loss;
	double Duplicates;
	char FileName[NAME_MAX];
	long FileSize;
	time_t StartTime;
	time_t EndTime;
	long TimeTaken;
	char Protocol[NAME_MAX];
	long TotalBytesTransferred;
	long BytesRetransmitted;
	char SenderHash[HASH_MAX];
	char ReceiverHash[HASH_MAX];
};
#endif