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
* File: /Common/Schedule.cpp
* Author: Renuka Wariyar
* Description:
* Result object contains the attributes which are to be written to the results repository
* The attributes returned from a file transfer are written to Results object
* This component is taken by the LibjingleWrapper and sent to TestHelper to write to repository.

Updates
=======
------------------------------------------------------------------------
| No. | Date |         Author        |          Reason for update       |
------------------------------------------------------------------------
|  1. |      |                       |									|
------------------------------------------------------------------------

*/
#include "StdAfx.h"
#include "Result.h"

/**
 * constructor
 * @param void
 * @return void
 * 
 */
Result::Result(void)
{
	ScheduleId = -1;
	ScenarioId = -1;
	Bandwidth = -1;
	Delay = -1;
	Loss = -1;
	Duplicates = -1;
	FileSize = -1;
	TimeTaken = -1;
	TotalBytesTransferred = -1;
	BytesRetransmitted = 0;
	/* memset buffers */
	memset(SenderHash, 0, sizeof(HASH_MAX));
	memset(ReceiverHash, 0, sizeof(HASH_MAX));
	memset(FileName, 0, sizeof(NAME_MAX));
	memset(Protocol, 0, sizeof(NAME_MAX));
}

/**
 * destructor
 * @param void
 * @return void
 * 
 */
Result::~Result(void)
{

}

/**
 * GetScheduleId:
 * @param void
 * @return int: Scenario id
 * 
 */
int Result::GetScheduleId(){
	return ScheduleId;
}

/**
 * GetScenarioId:
 * @param void
 * @return int: Scenario id
 * 
 */
int Result::GetScenarioId()
{
	return ScenarioId;
}

double Result::GetBandwidth()
{
	return Bandwidth;
}

double Result::GetDelay()
{
	return Delay;
}

double Result::GetLoss()
{
	return Loss;
}

double Result::GetDuplicates()
{
	return Duplicates;
}

char* Result::GetFileName()
{
	return FileName;
}

/**
 * GetFileSize:
 * @param void
 * @return int: Size of file received
 * 
 */
long Result::GetFileSize()
{
	return FileSize;
}

/**
 * GetStartTime:
 * @param void
 * @return long: Start time in milliseconds
 * 
 */
time_t Result::GetStartTime()
{
	return StartTime;
}

/**
 * GetEndTime:
 * @param void
 * @return long: End time in milliseconds
 * 
 */
time_t Result::GetEndTime()
{
	return EndTime;
}

/**
 * GetTimeTaken:
 * @param void
 * @return int: Time taken for file transfer
 * 
 */
long Result::GetTimeTaken()
{
	return TimeTaken;
}

char* Result::GetProtocol()
{
	return Protocol;
}

long Result::GetTotalBytesTransferred()
{
	return TotalBytesTransferred;
}

long Result::GetBytesRetransmitted()
{
	return BytesRetransmitted;
}

char* Result::GetSenderHash()
{
	return SenderHash;
}

char* Result::GetReceiverHash()
{
	return ReceiverHash;
}

/**
 * SetScheduleId:
 * @param: sId (Schedule id)
 * @return void
 * 
 */
void Result::SetScheduleId(int sId)
{
	ScheduleId = sId;
}
/**
 * SetScenarioId:
 * @param: sId (Scenario id)
 * @return void
 * 
 */
void Result::SetScenarioId(int sId)
{
	ScenarioId = sId;
}

void Result::SetBandwidth(double bw)
{
	Bandwidth = bw;
}

void Result::SetDelay(double d)
{
	Delay = d;
}

void Result::SetLoss(double l)
{
	Loss = l;
}

void Result::SetDuplicates(double d)
{
	Duplicates = d;
}

void Result::SetFileName(char* fname)
{
	if (strlen(fname) > NAME_MAX)
		return;

	strcpy (FileName, fname);
}

/**
 * SetFileSize:
 * @param: fSize (File size)
 * @return void
 * 
 */
void Result::SetFileSize(long fSize)
{
	FileSize = fSize;
}

/**
 * SetStartTime:
 * @param: sTime (Start time in milliseconds)
 * @return void
 * 
 */
void Result::SetStartTime(time_t sTime)
{
	StartTime = sTime;
}

/**
 * SetEndTime:
 * @param: eTime (End time in milliseconds)
 * @return void
 * 
 */
void Result::SetEndTime(time_t eTime)
{
	EndTime = eTime;
}

/**
 * SetTimeTaken:
 * @param: tTaken (Time taken for file transfer)
 * @return void
 * 
 */
void Result::SetTimeTaken(long tTaken)
{
	TimeTaken = tTaken;
}

/**
 * SetProtocol:
 * @param: p (protocol used for transfer)
 * @return void
 * 
 */
void Result::SetProtocol(char *p)
{
	if (!p || strlen(p) > NAME_MAX)
		return;
	
	strcpy(Protocol, p);
}

/**
 * SetTotalBytesTransferred:
 * @param: tbytes (transferred bytes)
 * @return void
 * 
 */
void Result::SetTotalBytesTransferred(long tbytes)
{
	TotalBytesTransferred = tbytes;
}

/**
 * SetBytesRetransmitted:
 * @param: bytes (retransmitted bytes)
 * @return void
 * 
 */
void Result::SetBytesRetransmitted(long bytes)
{
	BytesRetransmitted = bytes;
}

/**
 * SetSenderHash:
 * @param: sh (hash of the file at sender)
 * @return void
 * 
 */
void Result::SetSenderHash(char *sh)
{
	if (!sh || strlen(sh) > HASH_MAX)
		return;

	strcpy(SenderHash, sh);
}

/**
 * SetReceiverHash:
 * @param: rh (hash of the file at receiver)
 * @return void
 * 
 */
void Result::SetReceiverHash(char *rh)
{
	if (!rh || strlen(rh) > HASH_MAX)
		return;

	strcpy(ReceiverHash, rh);
}

/**
 * GetInsertQuery:
 * @param: 
 * @return string
 * 
 */
string Result::GetInsertQuery()
{
	string sQuery = "";
	ostringstream partCols, partVals;

	partCols << "INSERT INTO resultmaster (";
	partVals << "VALUES (";
	
	partCols << "ScheduleId" << ", " << "ScenarioId";
	partVals << ScheduleId << ", " << ScenarioId;

	if(Protocol)
	{
		partCols << ", Protocol";
		partVals << ", '" << Protocol << "'";
	}

	if(Bandwidth!=-1)
	{
		partCols << ", Bandwidth";
		partVals << ", " << Bandwidth;
	}

	if(Delay != -1)
	{
		partCols << ", Delay";
		partVals << ", " << Delay;
	}

	if(Loss != -1)
	{
		partCols << ", Loss";
		partVals << ", " << Loss;

	}

	if(Duplicates != -1)
	{
		partCols << ", Duplicates";
		partVals << ", " << Duplicates;
	}

	if(FileName)
	{
		partCols << ", Filename";
		partVals << ", '" << FileName << "'";
	}

	if(FileSize != -1)
	{
		partCols << ", FileSize";
		partVals << ", " << FileSize;
	}

	if(StartTime != NULL)
	{
		struct tm * timeInfo;
		char startTime[40];
		timeInfo = localtime(&StartTime);
		strftime(startTime, 40, "%Y-%m-%d %X", timeInfo);
		partCols << ", StartTime";
		partVals << ", '" << startTime << "'";
	}

	if(EndTime != NULL)
	{
		struct tm * timeInfo;
		char endTime[40];
		timeInfo = localtime(&EndTime);
		strftime(endTime, 40, "%Y-%m-%d %X", timeInfo);
		partCols << ", EndTime";
		partVals << ", '" << endTime << "'";
	}

	if(TimeTaken != -1)
	{
		partCols << ", TimeTaken";
		partVals << ", " << TimeTaken;
	}

	if(BytesRetransmitted != -1)
	{
		partCols << ", BytesRetransmitted";
		partVals << ", " << BytesRetransmitted;
	}

	if(TotalBytesTransferred != -1)
	{
		partCols << ", TotalBytesTransferred";
		partVals << ", " << TotalBytesTransferred;
	}

	if(SenderHash)
	{
		partCols << ", SenderHash";
		partVals << ", '" << SenderHash << "'";
	}

	if(ReceiverHash)
	{
		partCols << ", ReceiverHash";
		partVals << ", '" << ReceiverHash << "'";
	}

	partCols << ") ";
	partVals << ") ";

	sQuery = partCols.str() + partVals.str();

	return sQuery;
}