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
* File: /TestHelper/NISTNetWrapper.cpp
* Author: Kalyan Jakka
* Description:
* NISTNet wrapper acts as an interface between the test suite and NISTNet network emulator.
* This file is the header description of NISTNetWrapper
* This component is called by the sender agent to set the parameters in the network emulator (packet loss, bandwidth etc.).

Updates
=======
------------------------------------------------------------------------
| No. | Date |         Author        |          Reason for update       |
------------------------------------------------------------------------
|  1. |      |                       |									|
------------------------------------------------------------------------

*/
#include "StdAfx.h"
#include "NISTNetWrapper.h"

NISTNetWrapper::NISTNetWrapper(void)
{
	cfg = ConfigManager::Instance();
}

NISTNetWrapper::~NISTNetWrapper(void)
{
}

/**
 * Configure: This method configures NISTNet with the given network conditions from Scenario object
 * @param scene Scenario object from which the network conditions are taken
 * @return bool If the configuration was successful or not
 * 
 */
bool NISTNetWrapper::Configure(Scenario* scene)
{
	bool bResult = false;
	NetworkParameters* np = scene->GetNetworkParameters();
	std::ostringstream sCmdStream;
	string sCmd;

	sCmdStream	<< cfg->GetConfigValue("NW_PLINK_PATH")				// local path for plink.exe
				<< " -l " << cfg->GetConfigValue("NW_LOGINID")		// login id to make SSH connection
				<< " -pw " << cfg->GetConfigValue("NW_PASSWORD")	// password to make SSH Connection
				<< " " << cfg->GetConfigValue("NW_SERVER_IP")		// IP address/name of Emulator server machine
				<< " " << cfg->GetConfigValue("NW_REMOTEPATH")		// remote path of cnistnet
				<< " -a"
				<< " " << cfg->GetConfigValue("NW_SENDER_IP")		// * source IP address; 0.0.0.0 for all links
				<< " " << cfg->GetConfigValue("NW_RECEIVER_IP")		// * destination IP address; 0.0.0.0 for all links
				<< " add new"
				<< " --delay"
				<< " " << np->PacketDelay							// Packet Delay in ms	
				<< " --drop"
				<< " " << np->PacketLoss 							// Percentage packet loss
				<< " --dup"
				<< " " << np->PacketDuplicates						// Percentage packet duplication
				<< " --bandwidth"
				<< " " << std::setprecision(10) << np->Bandwidth; 	// Link bandwithd in kbps


	sCmd = sCmdStream.str();

	int return_code = 0;
	return_code = system(sCmd.c_str());
	bResult = (return_code == 0)? true:false;

	return bResult;
}

bool NISTNetWrapper::DeConfigure()
{
	bool bResult = false;
	int return_code = 0;
	//build the real command from network conditions parameter
	std::ostringstream sCmdStream;
	string sCmd;

	sCmdStream	<< cfg->GetConfigValue("NW_PLINK_PATH")				// local path for plink.exe
		<< " -l " << cfg->GetConfigValue("NW_LOGINID")		// login id to make SSH connection
		<< " -pw " << cfg->GetConfigValue("NW_PASSWORD")	// password to make SSH Connection
		<< " " << cfg->GetConfigValue("NW_SERVER_IP")		// IP address/name of Emulator server machine
		<< " " << cfg->GetConfigValue("NW_REMOTEPATH")		// remote path of cnistnet
		<< " -r"
		<< " " << cfg->GetConfigValue("NW_SENDER_IP")		// * source IP address; 0.0.0.0 for all links
		<< " " << cfg->GetConfigValue("NW_RECEIVER_IP");	// * destination IP address; 0.0.0.0 for all links


	sCmd = sCmdStream.str();
	return_code = system(sCmd.c_str());
	bResult = (return_code==0)? true:false;

	return bResult;
}

