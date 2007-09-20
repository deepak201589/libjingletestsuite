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
/**
* Relative Path: /Common/Scenario.h
* Author: Kimyung Han
* This file is the header description of Scenario
* Scenario object contains the attributes required for a file transfer scenario.
* The attributes are taken from scenario file
* This component is taken by the sender agent and passed to LibjingleWrapper to send the file.
*/

#ifndef __scenario_h
#define __scenario_h

#pragma once
#pragma warning(disable:4251)
#include "Common.h"
#include <string>

using namespace std;

/* Global definition for Scenario */
#define SID			"ScenarioId"
#define SNAME		"ScenarioName"
#define SFILE_PATH	"SourceFilePath"
#define SLOG_ID		"SenderLoginID"
#define PASSWD		"SenderPassword"
#define RFILE_PATH	"ReceivedFilePath"
#define RLOG_ID		"ReceiverLoginID"
#define USE_NISTNET "UseNISTnet"
#define PDELAY		"PacketDelay"
#define PLOSS		"PacketLoss"
#define PDUP		"PacketDuplication"
#define BANDWITH	"Bandwidth"
#define DESC		"Description"
#define PROTOCOL	"Protocol"

/**
* Structure for network parameters
*/

struct NetworkParameters {
	double PacketDelay;
	double PacketLoss;
	double PacketDuplicates;
	double Bandwidth;
};

/*
* Class Name: Scenario
* Purpose: The scenario object contains all the attributes required for a file transfer
* It is a copy of a scenario file read in to memory
* The attributes are private and are accessed or modified using getter and setter methods
*/
class COMMON_API Scenario
{
public:

	/* Constructors */
	Scenario(void);

	/* Destructor */
	~Scenario(void);

	/* Member functions */
	long GetFileSize();
	int GetScenarioId();
	bool UseNISTnet();
	string GetScenarioName();
	string GetSenderLoginId();
	string GetSenderPassword();
	string GetSenderFilePath();
	string GetReceiverLoginId();
	string GetReceiverFilePath();
	string GetDescription();
	string GetProtocol();
	NetworkParameters* GetNetworkParameters();

	void SetFileSize(long filesize);
	void SetScenarioId(int scenarioID);
	void SetScenarioName(string scenarioName);
	void SetNISTnetOption(bool option);
	void SetSenderLoginId(string loginID);
	void SetSenderPassword(string senderPassword);
	void SetSenderFilePath(string senderFilePath);
	void SetReceiverLoginId(string receiverLoginID);
	void SetReceiverFilePath(string recvFilePath);
	void SetDescription(string description);
	void SetProtocol(string protocol);
	void SetNetworkParameters(NetworkParameters* pNetParams);

private:
	// Primary attributes of a scenario
	long mFileSize;
	int mScenarioID;
	bool mUseNISTnet;
	string mScenarioName;
	string mSenderLoginID;
	string mSenderPassword;
	string mSenderFilePath;
	string mReceiverLoginID;
	string mReceiverFilePath;
	string mDescription;
	string mProtocol;

	NetworkParameters* mpNetParameters;

};

#endif
