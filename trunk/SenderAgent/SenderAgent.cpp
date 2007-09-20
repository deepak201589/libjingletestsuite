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
* Relative Path: /SenderAgent/SenderAgent.cpp
* Author: Kalyan Jakka
* SenderAgent defines the entry point for the console application.
* This component is called from the command line as:
* SenderAgent [sFile] where sFile is the name of the schedule file.
* e.g.: SenderAgent 1.schedule

Updates
=======
------------------------------------------------------------------------
| No. | Date |         Author        |          Reason for update       |
------------------------------------------------------------------------
|  1. |      |                       |									|
------------------------------------------------------------------------
*/

#include <iostream>
#include <string>
#include "stdafx.h"
#include "Common/LibjingleWrapper.h"
#include "Common/ConfigManager.h"
#include "Common/SocketManager.h"
#include "Common/DBWrapper.h"
#include "Common/TestInfo.h"
#include "Common/Scenario.h"
#include "Common/Schedule.h"
#include "Common/Result.h"
#include "Common/Timer.h"
#include "TestHelper/ScenarioManager.h"
#include "TestHelper/ScheduleManager.h"
#include "TestHelper/NISTNetWrapper.h"
#include "Common/debugging.h"
#include "Common/QuickHash.h"

using namespace std;

//Start SenderAgent (SA) with schedule id (e.g.: SenderAgent 1)
//SA calls TestManager (TM) for schedules (e.g.: tm.getSchedule(s))
//TM reads and returns schedule object
//SA calls TM for scenario definition (e.g.: tm.getScenario(sc))
//TM reads and returns scenario object
//Do the following for each scenario
//	SA calls Emulator Wrapper to set network conditions (e.g.: ew.configure(n))
//	Emulator Wrapper sets the network conditions
//	SA calls Libjingle Wrapper to start file transfer (e.g.: lw.doTransfer(sc))
//	Libjingle Wrapper starts the file transfer
//	SA calls Receiver Agent to return results
//	SA calls TM to write test results
//

/**
 * DisplayUsage: This method displays a help to the user, on how to execute the test-suite application.
 * @param pname: Command entered by the user
 * @return void
 * 
 */
static void DisplayUsage(char* pname)
{
	// display usage
	cout << "USAGE: " << pname << " [sFile]" << endl;
	cout << "  " << endl;
	cout << "COMMAND LINE ARGUMENTS" << endl;
	cout << "  sFile	-- schedule File name (no need to specify path)" << endl;
}

/**
 * DisplaySummary: This method displays a short report on the console.
 * @param pname: object containing the result of a test run
 * @return void
 * 
 */
static void DisplaySummary(Result* result)
{
	if (!result) {
		cout << "result object is NULL" << endl;
		return;
	}
	/* Print out test summary */

	cout << "\n\n" << "Results for Test run id: " << "RunID" << "\n";
	cout << "ScenarioID: " << result->GetScenarioId() << "\n";
	cout << "Filename: " << result->GetFileName() << "\n";
	cout << "Filesize (bytes): " << result->GetFileSize() << "\n";
	cout << "Bandwidth (bytes/sec): " << result->GetBandwidth() << "\n";
	cout << "Delay (ms): " << result->GetDelay() << "\n";
	cout << "Loss (%): " << result->GetLoss() << "\n";
	cout << "Duplicates (%): " << result->GetDuplicates() << "\n";
	cout << "\n";
	if (strcmp(result->GetSenderHash(), result->GetReceiverHash()) != 0)
	{
		cout << "Correctness check: FAIL" << "\n";
		cout << "\tSender Hash: " << result->GetSenderHash() << "\n";
		cout << "\tReceiver Hash: " << result->GetReceiverHash() << "\n";
	}
	else
	{
		cout << "Correctness: PASS" << "\n";
	}
	cout << "Time (ms): " << result->GetTimeTaken() << "\n\n";
}

static int SendTestInfo(Scenario* scene)
{
	TestInfo testInfo;
	SocketManager* socketManager = new SocketManager();
	int iResult = -(FAILURE);
	int bufSize = sizeof (testInfo);
	int conID = 0;
	int sizeRecv = 0, sizeSent = 0;
	
	iResult = socketManager->ServerInit(DEFAULT_PORT);
	if (iResult != SUCCESS) {
		delete socketManager;
		return iResult;
	}
	iResult = socketManager->Listen(1);
	if (iResult == SUCCESS)
	{
		conID = socketManager->Accept();
		if (conID < 0) {
			cout << "Failed to accept a new connection" <<endl;
			iResult = socketManager->CloseConnection();
			delete socketManager;
			iResult = (-FAILURE);
			return iResult;
		}
		sizeRecv = socketManager->ReceiveData(conID, (char*)&testInfo, bufSize);
		if (sizeRecv == bufSize && testInfo.OpCode == OP_INFO)
		{
			/* retrieve received data */
			testInfo.OpCode = OP_INFO_ACK;
			testInfo.SeqID = 1; /* FIXME: Why is it always 1? */
			testInfo.ScenarioID = scene->GetScenarioId();
			strcpy(testInfo.RecvPath, scene->GetReceiverFilePath().c_str());
			testInfo.Filename = scene->GetSenderFilePath();			
			
			sizeSent = socketManager->SendData(conID, (char *)&testInfo, bufSize);
			if (bufSize != sizeSent) 
			{
				cout << "Failed to send data" << endl;
				iResult = socketManager->CloseConnection();
				iResult = -(FAILURE);
				delete socketManager;
				return iResult;
			}

			sizeRecv = socketManager->ReceiveData(conID, (char*)&testInfo, bufSize);
			if (sizeRecv != bufSize || testInfo.OpCode != OP_CLOSE) {
				cout << "Failed to Receive OP_CLOSE from receiver agent" << endl;
				iResult = socketManager->CloseConnection();
				iResult = -(FAILURE);
				delete socketManager;
				return iResult;
			}
			
		} else {
			cout << "Failed to receive data" << endl;
			iResult = (-FAILURE);
		}
	}
	iResult = socketManager->CloseConnection();
	delete socketManager;
	return iResult;
}

static int ReceiveTestResult(char* recvHash)
{
	int conID = 0;
	int sizeRecv = 0, sizeSent = 0;
	int iResult = SUCCESS;
	TestInfo testInfo;
	int bufSize = sizeof (struct testinfo);
	SocketManager *socketManager = new SocketManager();

	/* Step1: initialize TCP client and connect to the server */
	iResult = socketManager->ServerInit(DEFAULT_PORT);
	if (iResult != SUCCESS) {
		delete socketManager;
		return iResult;
	}
	iResult = socketManager->Listen(1);
	if (iResult == SUCCESS)
	{
		conID = socketManager->Accept();
		if (conID < 0) {
			cout << "Failed to accept a new connection" <<endl;
			iResult = socketManager->CloseConnection();
			delete socketManager;
			iResult = (-FAILURE);
			return iResult;
		}

		/* Step 1: receive test result from a receiver agent*/
		sizeRecv = socketManager->ReceiveData(conID, (char*)&testInfo, bufSize);
		if (sizeRecv == bufSize && testInfo.OpCode == OP_REPORT)
		{
			testInfo.OpCode = OP_REPORT_ACK;

			/* Step 2: Error code is checked and receiver hash is set in the result */
			if (testInfo.ErrorCode == SUCCESS)
			{
				strcpy(recvHash, testInfo.HashCode);
			}
			else
			{
				cout << "Error in getting has from receiver" << endl; 
				iResult = socketManager->CloseConnection();
				delete socketManager;
				iResult = (-FAILURE);
				return iResult;

			}

			sizeSent = socketManager->SendData(conID, (char *)&testInfo, bufSize);
			if (bufSize != sizeSent) 
			{
				iResult = socketManager->CloseConnection();
				delete socketManager;
				iResult = (-FAILURE);
				return iResult;
			}
		} else
			iResult = -(FAILURE);
	}
	/* Step3: Close connection after OP_REPORT_ACK or on any error */
	iResult = socketManager->CloseConnection();
	delete socketManager;
	return iResult;
}

/**
 * main
 * @param argc: no. of arguments
 * @param argv: character array of input arguments
 * @return int: 0 - exit with success. 1 - exit with error.
 * 
 */
int main(int argc, char* argv[])
{
	if (argc != 2) {
		DisplayUsage(argv[0]);
		exit(0);
	}

	// object instances for different functionalities
	ConfigManager* configManager = ConfigManager::Instance();
	ScheduleManager* scheduleManager = new ScheduleManager();
	ScenarioManager* scenarioManager = new ScenarioManager();
	NISTNetWrapper* nistnetWrapper = new NISTNetWrapper();
	LibjingleWrapper* libjingleWrapper = new LibjingleWrapper();
	DBWrapper* dbWrapper = new DBWrapper();
	Timer* timer = new Timer();	
	Utils* utils = new Utils();

	// local objects
	Schedule* schedule = NULL;
	Scenario* scenario = NULL;
	Result* result = NULL;
	NetworkParameters* netParams = NULL;
	map<int, string>* mapScenarioIDs = NULL;
	map<int, string>::iterator p;
	//char* sTemp = NULL;
	int ret = SUCCESS;
	string fileSchedule(argv[1]);
	char receiverHash[CMD5::HEXDIGESTSIZE], senderHash[CMD5::HEXDIGESTSIZE];
	string fPath = "";

	// Load the schedule file specified in the command-line
    ret = scheduleManager->LoadSchedule(configManager->GetConfigValue("DIR_SCHEDULES") + fileSchedule);

	if (ret == SUCCESS)
		cout << "Specified schedule loaded." << endl;
	else if (ret == -(FILE_NOT_FOUND)) {
		cout << "File does not exist" << endl;
		goto release_mem;
	} else if (ret == -(INVALID_ARGUMENT)) {
		cout << "one of the scenario in the schedule is corrupted" << endl;
		goto release_mem;
	} else {
		cout << "Error in loading scenario. Error code:" << ret;
		goto release_mem;
	}

	schedule = scheduleManager->GetSchedule();
	mapScenarioIDs = schedule->GetScenarioIDs();

	if (!mapScenarioIDs)
		goto release_mem;

	// Iterate and execute each scenario listed in the schedule file.
	for (p = mapScenarioIDs->begin(); p != mapScenarioIDs->end(); p++ ) 
	{
		ret = scenarioManager->LoadScenario(configManager->GetConfigValue("DIR_SCENARIOS") + p->second);
		if (ret != SUCCESS) 
		{
			cout << "Error in loading scenario" << endl;
			continue;
		}
		result = new Result();
		scenario = scenarioManager->GetScenario();

		/* print current scenario information */
		cout << "Executing Scenario: "<< scenario->GetScenarioId()<< " in Schedule: "<< schedule->GetScheduleId() << endl;

		result->SetScheduleId(schedule->GetScheduleId());
		result->SetScenarioId(scenario->GetScenarioId());
		result->SetProtocol((char *)scenario->GetProtocol().c_str());
		result->SetFileName((char *)scenario->GetSenderFilePath().c_str()); 
		result->SetFileSize(scenario->GetFileSize());

		netParams = scenario->GetNetworkParameters();
		result->SetBandwidth(netParams->Bandwidth);
		result->SetLoss(netParams->PacketLoss);
		result->SetDelay(netParams->PacketDelay);
		result->SetDuplicates(netParams->PacketDuplicates);
		
		if (SUCCESS != SendTestInfo(scenario)) {
			delete result;		
			continue;
		}
		
		if (scenario->UseNISTnet())
			nistnetWrapper->Configure(scenario);
		
		timer->StartTimer();
		result->SetStartTime(timer->Now()); 

		// do the actual file transfer
		libjingleWrapper->DoTransfer(scenario);

		timer->StopTimer();
		result->SetEndTime(timer->Now());
		result->SetTimeTaken(timer->GetTime());

		if (scenario->UseNISTnet())
			nistnetWrapper->DeConfigure();

		// fetch the file hashes
		
		ret = ReceiveTestResult(receiverHash);

		if (ret == SUCCESS)
		{
			result->SetReceiverHash(receiverHash);
			TRACE("Receiver hash added to result.\n");
		}
		else
		{
			cout <<"[Error: ReceiveTestResult] in executing  "<< p->second.c_str() << endl;
			delete result;
			continue;
		}
		fPath = configManager->GetConfigValue("DIR_TXFILELOC") + scenario->GetSenderFilePath();
		ret = utils->CreateFileHash(fPath.c_str(), senderHash);
		if (ret == SUCCESS)
			result->SetSenderHash(senderHash);
		else
			cout <<"[Error: CreateFileHash] in executing  "<< p->second.c_str() << endl;
			
		// Record and display results
		dbWrapper->WriteResults(result->GetInsertQuery());
		DisplaySummary(result);
		
		// FIXED: [K.M Han] it was not because result was deleted here. It was because
		// StartTime and EndTime was not defined correctly along with Timer class
		// Time_t is a number not a class!!.
		delete result;
	}

release_mem:	
	delete utils;
	delete timer;
	delete dbWrapper;
	delete scenarioManager;
	delete scheduleManager;
	delete nistnetWrapper;
	delete libjingleWrapper;	

	return 0;
}

