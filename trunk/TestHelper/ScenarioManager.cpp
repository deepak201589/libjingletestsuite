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
#include "ScenarioManager.h"
/*
* Relative Path: /TestHelper/ScenarioManager.cpp
* Author: Han
* ScenarioManager reads/creates/updates/deletes scenario files
* This component is called by <fill the data here>

Updates
=======
------------------------------------------------------------------------
| No. | Date |         Author        |          Reason for update       |
------------------------------------------------------------------------
|  1. |      |                       |									|
------------------------------------------------------------------------
*/
#include "StdAfx.h"
#include "ScenarioManager.h"

/**
 * constructor
 * @return ScenarioManager a ScenarioManager object
 * 
 */
ScenarioManager::ScenarioManager(void)
{
	mpScenario = NULL;
}

/**
 * destructor
 * 
 */
ScenarioManager::~ScenarioManager(void)
{
	if (mpScenario)
		delete mpScenario;
}

/************************************************************************/
/* Local method                                                         */
/************************************************************************/

string DoubleToString(double value)
{
	int BASE = 10;
	char *buf = NULL;
	string result = "";
	int length = 0;

	if (value)
		length = (log10(abs(value))) + 1;

	buf = (char *)malloc(sizeof(char) * length);
	
	sprintf(buf, "%ld", value);
	result = buf;

	free(buf);
	return result;
}

/************************************************************************/
/* Member methods                                                       */
/************************************************************************/


/**
 * LoadScenario: Read the scenario from the scenario file
 * @param fname - file name of scenario
 * @return int 0 for success and 1 for failure
 * 
 */
int ScenarioManager::LoadScenario(string fname)
{
	string line = "", fPath = "";
	string lValue = "", rValue = "";
	char *pStr = NULL;
	double length = 0;
	ifstream iFile, SenderFile;
	size_t cutAt = 0, fsize = 0;
	bool Use_NistNet = FALSE, Is_FlagSet = FALSE;
	NetworkParameters *pNetParams = NULL;
	ConfigManager *pConfig = ConfigManager::Instance();


	/* initiate the member function */
	if (!mpScenario)
		mpScenario = new Scenario();

	/* get pointer of network parameters */
	pNetParams = mpScenario->GetNetworkParameters();
	
	iFile.open(fname.c_str(),ios::in);

	if (iFile.is_open())
	{
		while (! iFile.eof() )
		{
			cutAt = 0;
			getline (iFile, line);

			cutAt = line.find_first_of("=");
			lValue = line.substr(0, cutAt);
			rValue = line.substr(cutAt+1);

			pStr = (char *)lValue.c_str();

			/* check if rValue is empty */
			if (rValue.empty())
				continue;

			/* validation procedure */
			if (!strcmp(pStr, SNAME))
			{
				mpScenario->SetScenarioName(rValue);
			}
			else if (!strcmp(pStr, SID)) 
			{
				mpScenario->SetScenarioId(atoi(rValue.c_str()));
			}
			else if(!strcmp(pStr, SFILE_PATH)) 
			{
				fPath = pConfig->GetConfigValue("DIR_TXFILELOC") + rValue;
				mpScenario->SetSenderFilePath(rValue);

				/* calculate file size */
				SenderFile.open(fPath.c_str(), ios::binary);

				if (!SenderFile.is_open()) 
				{
					//cout << "Sender file path is not valid!!"<<endl;
					return -(FILE_NOT_FOUND); /* TODO: should return a specific error code */
				}
				SenderFile.seekg(0, ios::end);
				length = SenderFile.tellg();
				mpScenario->SetFileSize(length);
				SenderFile.close();
			} 
			else if (!strcmp(pStr, SLOG_ID)) 
			{
				mpScenario->SetSenderLoginId(rValue);
			}
			else if (!strcmp(pStr, PASSWD))
			{
				mpScenario->SetSenderPassword(rValue);
			}
			else if (!strcmp(pStr, RFILE_PATH))
			{
				/* get a sending file path and the size of it */
				mpScenario->SetReceiverFilePath(rValue);
			}
			else if (!strcmp(pStr, RLOG_ID))
			{
				mpScenario->SetReceiverLoginId(rValue);
			}	
			else if (!strcmp(pStr, USE_NISTNET))
			{
				if (rValue == "YES")
				{
					Use_NistNet = TRUE;
					mpScenario->SetNISTnetOption(TRUE);
				}
			}
			else if (!strcmp(pStr, PDELAY))
			{
				pNetParams->PacketDelay = atoi(rValue.c_str());
			}
			else if (!strcmp(pStr, PLOSS))
			{
				pNetParams->PacketLoss = atoi(rValue.c_str());
				if (pNetParams->PacketLoss < PERCENT_MIN && pNetParams->PacketLoss > PERCENT_MAX) {
					pNetParams->PacketLoss = 0;
					return (-INVALID_ARGUMENT);
				}
			}
			else if (!strcmp(pStr, PDUP))
			{
				pNetParams->PacketDuplicates = atoi(rValue.c_str());

				if (pNetParams->PacketDuplicates < PERCENT_MIN && pNetParams->PacketDuplicates > PERCENT_MAX) {
					pNetParams->PacketDuplicates = 0;
					return (-INVALID_ARGUMENT);
				}
			}
			else if (!strcmp(pStr, BANDWITH))
			{
				pNetParams->Bandwidth = atoi(rValue.c_str());
			}
			else if (!strcmp(pStr, DESC))
			{
				mpScenario->SetDescription(rValue);
			}
			else if (!strcmp(pStr, PROTOCOL))
			{
				mpScenario->SetProtocol(rValue);
			}
			else 
			{
				//cout << "Unidentified parameter";
				INFO("Invalid argument in Scenario.");				
			}

		}
		iFile.close();

		/* assign "fname" to a member variable */
		mpScenario->SetScenarioName(fname);
	}/* end of if (iFile.open) */

	return SUCCESS; 
}

/**
* GetScenarioMap: convert member variables of Scenario into map
*	This function is created for convenience of scenario file creation
*
* @param ScenarioMap a pointer of ScenarioMap 
* @return int 0 for success, -1 for failure
* 
*/

int ScenarioManager::GetScenarioMap(map<string, string> *ResultMap)
{
	NetworkParameters *pNetParams = NULL;
	char buf[INT_LENGTH];
	string SId;
	Utils func;

	if (!ResultMap)
	{
		INFO("Null pointer error\n");
		return -(NULL_POINTER);
	}

	/* input parameters */
	itoa(mpScenario->GetScenarioId(), buf, INT_LENGTH);
	SId += buf;

	ResultMap->insert(pair<string, string>(SID, SId));
	ResultMap->insert(pair<string, string>(SNAME, mpScenario->GetScenarioName()));
	ResultMap->insert(pair<string, string>(SLOG_ID, mpScenario->GetSenderLoginId()));
	ResultMap->insert(pair<string, string>(PASSWD, mpScenario->GetSenderPassword()));
	ResultMap->insert(pair<string, string>(SFILE_PATH, mpScenario->GetSenderFilePath()));
	ResultMap->insert(pair<string, string>(RLOG_ID, mpScenario->GetReceiverLoginId()));
	ResultMap->insert(pair<string, string>(RFILE_PATH, mpScenario->GetReceiverFilePath()));
	ResultMap->insert(pair<string, string>(DESC, mpScenario->GetDescription()));

	if (mpScenario->UseNISTnet())
	{
		pNetParams = mpScenario->GetNetworkParameters();
		if (!pNetParams)
		{
			INFO("Null pointer error\n");		
			return -(NULL_POINTER);
		}
		ResultMap->insert(pair<string, string>(USE_NISTNET, "YES"));


		/* insert network parameters */
		ResultMap->insert(pair<string, string>(PDELAY, DoubleToString(pNetParams->PacketDelay)));
		ResultMap->insert(pair<string, string>(PLOSS, DoubleToString(pNetParams->PacketLoss)));
		ResultMap->insert(pair<string, string>(PDUP, DoubleToString(pNetParams->PacketDuplicates)));
		ResultMap->insert(pair<string, string>(BANDWITH, DoubleToString(pNetParams->Bandwidth)));
	} 
	else
	{
		ResultMap->insert(pair<string, string>(USE_NISTNET, "NO"));
		/* input default values to keep the consistent format for a scenario file*/

		ResultMap->insert(pair<string, string>(PDELAY, "0"));
		ResultMap->insert(pair<string, string>(PLOSS, "0"));
		ResultMap->insert(pair<string, string>(PDUP, "0"));
		ResultMap->insert(pair<string, string>(BANDWITH, "0"));
	}
	return SUCCESS;
}


/**
* SaveScenario: Create a new scenario file using mpScenario
* @param fname name of a new scenario file
* @return int 0 for success and 1 for failure
* 
*/
int ScenarioManager::SaveScenario(string fname)
{
	int error = SUCCESS;
	ofstream oFile;
	char buf[LINE_MAX];

	map<string, string> *ParameterMap = NULL;
	map<string, string>::iterator iter;

	/* check if mpScenari is valid, otherwise return a error */
	if (!mpScenario)
		return -(FAILURE); /* FIXME: need to return a specific error code */

	/* get parameters from mpScenario and put them into map for convenience. */
	ParameterMap = new map <string, string>;

	error = GetScenarioMap(ParameterMap);

	if (error < 0)
	{
		INFO("Scenario parameters are not valid !!\n");
		delete ParameterMap;
		return error;
	}

	oFile.open(fname.c_str(), ios::out);

	if (oFile.is_open())
	{
		for (iter = ParameterMap->begin(); iter != ParameterMap->end(); iter++) 
		{
			sprintf(buf, "%s=%s\n", iter->first.c_str(), iter->second.c_str());
			oFile.write(buf, strlen(buf));
		}
		oFile.close();
	}
	delete ParameterMap;

	return error;
}

/**
 * GetScenario This method is to access the scenario map
 * @return Scenario* a scenario object
 * 
 */
Scenario* ScenarioManager::GetScenario()
{
	return mpScenario;
}

/**
 * SetScenario This method sets a scenario to the map
 * @param scenario: A scenario object
 * @return bool true for success false for failure
 * 
 */
bool ScenarioManager::SetScenario(Scenario *scenario)
{
	bool bResult = false;

	if (scenario) {
		mpScenario = scenario;
		bResult = true;
	}
	return bResult;
	/* FIXME: Does it always return TRUE? */
}

/**
* Initialize Scenario (only for Scencario manager)
* @param scenario: none
* @return none
* 
*/
void ScenarioManager::InitScenario()
{
	if (!mpScenario)
		mpScenario = new Scenario();
}
