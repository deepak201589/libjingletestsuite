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
* File: /Common/scenario.cpp
* Author: Kimyung Han
* Description:
* Scenario object contains the attributes required for a file transfer scenario.
* This list is taken from a schedule file
* This component is taken by the sender agent and passed to scenario manager

Updates
=======
------------------------------------------------------------------------
| No. | Date |         Author        |          Reason for update       |
------------------------------------------------------------------------
|  1. | 06/17| Kalyan                | Merged Han's work				|
|  2. |		 |		                 |									|
------------------------------------------------------------------------

*/
#include "StdAfx.h"
#include "Scenario.h"

/**
 * constructor
 * @param void
 * @return void
 * 
 */
Scenario::Scenario(void)
{	
	mFileSize = -1;
	mScenarioID = -1;
	mScenarioName = "";
	mSenderLoginID = "";
	mSenderPassword = "";
	mSenderFilePath = "";
	mReceiverLoginID = "";
	mReceiverFilePath = "";
	mUseNISTnet = FALSE;
	mpNetParameters = new NetworkParameters();
}

/**
 * destructor
 * @param void
 * @return void
 * 
 */
Scenario::~Scenario(void)
{
	mScenarioID = -1;
	mFileSize = -1;
	mScenarioName = "";
	mSenderLoginID = "";
	mSenderPassword = "";
	mSenderFilePath = "";
	mReceiverLoginID = "";
	mReceiverFilePath = "";

	if (mpNetParameters)
		delete(mpNetParameters);

	mpNetParameters = NULL;
}

/**
 * GetScenarioId:
 * @param void
 * @return Scenario
 * 
*/
int Scenario::GetScenarioId()
{
	return mScenarioID;
}

/**
 * SetScenarioId:
 * @param: sId (Scenario Id)
 * @return void
 * 
 */
void Scenario::SetScenarioId(int sId)
{
	mScenarioID = sId;
}

/**
 * GetSenderLoginId:
 * @param void
 * @return Sender Login Id
 * 
*/
string Scenario::GetSenderLoginId()
{
	return mSenderLoginID;
}

/**
 * SetenderLoginId:
 * @param: SeLoginId (Sender Login Id)
 * @return void
 * 
 */
void Scenario::SetSenderLoginId(string SeLoginID)
{
	mSenderLoginID = SeLoginID;
}

/**
 * GetScenarioName:
 * @param void
 * @return Scenario Name
 * 
*/
string Scenario::GetScenarioName()
{
	return mScenarioName;
}

/**
 * SetScenarioName:
 * @param: name (Scenario Name)
 * @return void
 * 
 */
void Scenario::SetScenarioName(string name)
{
	mScenarioName = name;
}

/**
 * GetSenderPassword:
 * @param void
 * @return Sender Password
 * 
*/
string Scenario::GetSenderPassword()
{
	return mSenderPassword;
}

/**
 * SetSenderPassword:
 * @param: Password (Senders Password for the Login Id)
 * @return void
 * 
 */
void Scenario::SetSenderPassword(string Password)
{
	mSenderPassword = Password;
}

/**
 * GetSenderFilePath:
 * @param void
 * @return Sender File Path
 * 
*/
string Scenario::GetSenderFilePath()
{
	return mSenderFilePath;
}

/**
 * SetSenderFilePath:
 * @param: fPath (File Path at sender for the Test file)
 * @return void
 * 
 */
void Scenario::SetSenderFilePath(string fPath)
{
	mSenderFilePath = fPath;
}

/**
 * GetReceiverLoginId:
 * @param void
 * @return Receiver Login Id
 * 
*/
string Scenario::GetReceiverLoginId()
{
	return mReceiverLoginID;
}

/**
 * SetReceiverLoginId:
 * @param: RecvLoginID (Receiver's Login Id)
 * @return void
 * 
 */
void Scenario::SetReceiverLoginId(string RecvLoginID)
{
	mReceiverLoginID = RecvLoginID;
}

/**
 * GetReceiverFilePath:
 * @param void
 * @return File Path at receiver
 * 
*/
string Scenario::GetReceiverFilePath()
{
	return mReceiverFilePath;
}

/**
 * SetReceiverFilePath:
 * @param: FilePath (File path at receiver for the test file)
 * @return void
 * 
 */
void Scenario::SetReceiverFilePath(string FilePath)
{
	mReceiverFilePath = FilePath;
}


/**
 * GetNetworkParameters:
 * @param void
 * @return Pointer to structure with values for scenario network parameters
 * 
*/
NetworkParameters* Scenario::GetNetworkParameters()
{
	return mpNetParameters;
}

/**
 * SetNetworkParameters:
 * @param: pNetParams (Pointer to the filled up structure of network parameter values)
 * @return void
 * 
 */
void Scenario::SetNetworkParameters(NetworkParameters* pNetParams)
{
	mpNetParameters = pNetParams;
}

/**
 * GetFileSize:
 * @param void
 * @return File Size at sender
 * 
*/
long Scenario::GetFileSize()
{
	return mFileSize;
}

/**
 * SetFileSize:
 * @param: Size (File size at the sender)
 * @return void
 * 
 */
void Scenario::SetFileSize(long Size)
{
	mFileSize = Size;
}

/**
 * GetDescription:
 * @param void
 * @return Scenario description
 * 
*/
string Scenario::GetDescription()
{
	return mDescription;
}

/**
 * SetDescription:
 * @param: mDesc (description text of scenario)
 * @return void
 * 
 */
void Scenario::SetDescription(string mDesc)
{
	mDescription = mDesc;
}

/**
 * UseNISTnet:
 * @param void
 * @return flag indicatingweather scenario uses NISTnet
 * 
*/
bool Scenario::UseNISTnet()
{
	return mUseNISTnet;
}

/**
 * SetNISTnetOption:
 * @param: bNN (boolean value indicating weather scenario uses NISTnet)
 * @return void
 * 
 */
void Scenario::SetNISTnetOption(bool bNN)
{
	mUseNISTnet = bNN;
}

/**
 * GetProtocol:
 * @param void
 * @return Scenario Protocol
 * 
*/
string Scenario::GetProtocol()
{
	return mProtocol;
}

/**
 * SetProtocol:
 * @param: mProto (protocol used by the scenario)
 * @return void
 * 
 */
void Scenario::SetProtocol(string mProto)
{
	mProtocol = mProto;
}

