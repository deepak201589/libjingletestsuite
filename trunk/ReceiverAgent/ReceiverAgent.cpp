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
* File: /ReceiverAgent/ReceiverAgent.cpp
* Author: Kimyung Han
* Description:
* Receiver agent is stand-alone component that communicates with a SenderAgent

Updates
=======
------------------------------------------------------------------------
| No. | Date |         Author        |          Reason for update       |
------------------------------------------------------------------------
|  1. |      |                       |									|
------------------------------------------------------------------------

*/

#include "StdAfx.h"
#include "ReceiverAgent.h"
#include "../Common/Debugging.h"

ReceiverAgent::ReceiverAgent(void)
{
	m_ServerIP = "";
	m_ServerPort = 0;
}

ReceiverAgent::ReceiverAgent(string ServerIP, int ServerPort)
{
	ReceiverAgent();
	m_ServerIP = ServerIP;
	m_ServerPort = ServerPort;
}

ReceiverAgent::~ReceiverAgent(void)
{
	m_ServerIP = "";
	m_ServerPort = 0;
}

/*
 * retrieve test information from sender agent through TCP/IP
 * @param none
 * @return SUCCESS on success, negative error in case of failure
 */

int ReceiverAgent::GetTestInfo()
{
	int ret = 0;
	TestInfo buf;
	int bufSize = sizeof (struct testinfo);

	SocketManager *pSocketHandler = new SocketManager();

	/* Step1: initialize TCP client and connect to the server */
	pSocketHandler->ClientInit((char *)m_ServerIP.c_str(), m_ServerPort);
	
	while (1)
	{
		if ((ret = pSocketHandler->Connect()) < 0)
			cout <<"no server !!" << endl;
		else 
		{
			cout <<"I am connected !!" << endl;		
			break;
		}
	}

	/* Step2: Test info initialization for test information request */
	memset(&buf, 0, sizeof(buf));
	buf.OpCode = OP_INFO;

	TRACE("Sending request for test information\n");
	ret = pSocketHandler->SendData(CLIENT_ONLY, (char *)&buf, bufSize);
	if (ret != bufSize) 
	{
		TRACE("Sending data is failed\n");
		ret = -(FAILURE); /* FIXME: how about SEND_FAIL ? */
		goto disconnect; /* jump to disconnect */	
	}
	TRACE("Receiving test information from a SenderAgent\n");
	ret = pSocketHandler->ReceiveData(CLIENT_ONLY, (char *)&buf, bufSize);
	if (ret != bufSize) {
		TRACE("Receving data is failed");
		ret = -(FAILURE); /* FIXME: how about RECV_FAIL ? */
		goto disconnect; /* jump to disconnect */	
	}
	if (buf.OpCode != OP_INFO_ACK) {
		TRACE("Received opcode is wrong");
		INFO("Error code: ", buf.ErrorCode);
		ret = -(INVALID_ARGUMENT);
		goto disconnect; /* jump to disconnect */
	}

	/* Step 2-1: retrieve data from buf */
	m_TestInfo.SeqID = buf.SeqID;
	m_TestInfo.ScenarioID = buf.ScenarioID;	
	strcpy(m_TestInfo.RecvPath, buf.RecvPath);
	m_TestInfo.Filename = buf.Filename;
	
	INFO("Transmission result");
	INFO("seqID ", buf.SeqID);	
	INFO("Scenario ID ", buf.ScenarioID);
	INFO("Recv Path ", buf.RecvPath);
	INFO("Filename ", buf.Filename);

	/* Step3: Notify a SenderAgent the connection close */
	memset(&buf, 0, sizeof(buf));
	buf.OpCode = OP_CLOSE;

	TRACE("Requesting connection close");
	ret = pSocketHandler->SendData(CLIENT_ONLY, (char *)&buf, bufSize);
	if (ret < 0) {
		ret = -(FAILURE);
		TRACE("failed to send OP_CLOSE\n");
	}

disconnect:

	/* ignore error in CloseConnection */
	pSocketHandler->CloseConnection();
	delete pSocketHandler;
	TRACE("Connection is expired");

	return ret;
}

/*
* send test result to a sender agent through TCP/IP
* @param none
* @return SUCCESS on success, negative error in case of failure
*/
int ReceiverAgent::SendTestResult()
{
	int ret = 0;
	char *hashCode = NULL;
	TestInfo buf;
	Utils *util = new Utils();
	string recvFile = "";
	int bufSize = sizeof (struct testinfo);
	SocketManager *pSocketHandler = new SocketManager();

	/* Step1: initialize TCP client and connect to the server */
	pSocketHandler->ClientInit((char *)m_ServerIP.c_str(), m_ServerPort);

	while (1)
	{
		if ((ret = pSocketHandler->Connect()) < 0) 
		{
			INFO("no server !!\n");
		}
		else 
		{
			INFO("I am connected !!\n");		
			break;
		}
	}

	/* Step2: Test info initialization for test information request */
	memset(&buf, 0, sizeof(buf));
	buf.OpCode = OP_REPORT;

	/* Step 2-1: produce hash value using a file hash library */

	recvFile = m_TestInfo.RecvPath + m_TestInfo.Filename;
	ret = util->CreateFileHash(recvFile.c_str(), buf.HashCode);
	if (ret < 0) {
		INFO("file open failed\n");	
		buf.ErrorCode = -(FAILURE);
	} else {
		buf.ErrorCode = SUCCESS;
		TRACE("Hash: %x \n", buf.HashCode);
	}
	
	INFO("Sending Test result\n");

	ret = pSocketHandler->SendData(CLIENT_ONLY, (char *)&buf, bufSize);
	if (ret != bufSize) {
		ret = (-FAILURE);
		TRACE("fail to send test information \n");
		goto disconnect;
	}

	INFO("Receiving acknowledge for test report\n");

	ret = pSocketHandler->ReceiveData(CLIENT_ONLY, (char *)&buf, bufSize);
	if (ret != bufSize && buf.ErrorCode != OP_REPORT_ACK) {
		ret = -(FAILURE);
		TRACE("fail to receive acknowledge from a sender agent\n");
	}
	
disconnect:
	/* Step3: Close connection on receiving OP_REPORT_ACK or on any error */

	ret = pSocketHandler->CloseConnection();

	delete util;
	delete pSocketHandler;
	INFO("Connection is expired\n");
	return ret;
}


// ReceiverAgent.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Common/LibjingleWrapper.h"
#include "Common/ConfigManager.h"
#include "Common/Result.h"
#include "Common/ErrorCode.h"
#include <stdlib.h>

/**
* main
* @param argc: no. of arguments
* @param argv: character array of input arguments
* @return int: 0 - exit with success. 1 - exit with error.
* 
* Poll to connect to sender (TCP/socket).
* If sender responds with scenario information; start libjingle receiver. (xmpp)
* After transfer is complete; compute file hash and give it back to sender (TCP/socket).	
* Go back and poll for more files/scenarios.
*/

int main(int argc, char* argv[])
{
	bool nExit = false;
	int ServerPort = 0;
	int ret = SUCCESS;
	string ServerIP = "", LoginID = "", LogPasswd = "";
	string RecvPath = "";
	LibjingleWrapper* libjingleWrapper = NULL;
	ConfigManager* configManager = NULL;
	ReceiverAgent* myAgent = NULL;

	libjingleWrapper =	new LibjingleWrapper();
	configManager = ConfigManager::Instance();

	/* preliminary error checking */

	if (!libjingleWrapper) {
		cout << "Libjingle Wrapper is NULL" <<endl;
		return NULL_POINTER;
	}

	if (!configManager) {
		cout << "Config Manager is NULL" <<endl;
		delete libjingleWrapper;
		return NULL_POINTER;
	}

	/* Step 1: get connection parameters */
	ServerIP = configManager->GetConfigValue("NW_SENDER_IP");
	ServerPort = DEFAULT_PORT;	

	cout << "ReceiverAgent server_ip: " << ServerIP << endl;
	cout << "server port " << ServerPort << endl;

	/* Step 2: create a new receiver agent */
	myAgent = new ReceiverAgent(ServerIP, ServerPort);
	LoginID = configManager->GetConfigValue("RX_USERNAME");
	LogPasswd = configManager->GetConfigValue("RX_PASSWORD");
	RecvPath = configManager->GetConfigValue("DIR_RXFILELOC");

	while (!nExit)
	{
		/* Step 3: get test information from a sender agent */
		ret = myAgent->GetTestInfo();
		if (ret != SUCCESS) {
			cout << "Getting test information failed" << endl;
			break;
		}
		else
		{
			RecvPath = myAgent->m_TestInfo.RecvPath;
		}

		if (LoginID.empty() || LogPasswd.empty()) 
		{
			cout << "Invalid login name or password" << endl;
			break;
		}
		
		/* Step 4: Receive a file through Pseudo TCP/ RUDP */		
		libjingleWrapper->ReceiveFile(LoginID, LogPasswd, RecvPath); 
		
		/* Step 5: Send test result to a SenderAgent */
		ret = myAgent->SendTestResult();
		if (ret != SUCCESS) {
			TRACE("Fail to send test result\n"); 
			break;
		}
		
	}
	
	delete configManager;
	delete libjingleWrapper;
	delete myAgent;

	return ret;
}

