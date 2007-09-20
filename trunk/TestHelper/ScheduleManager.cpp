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
* Relative Path: /TestHelper/ScheduleManager.cpp
* Author: Han Kimyung
* ScheduleManager reads/adds/updates schedule into the schedule file.
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
#include "ScheduleManager.h"


/**
 * constructor
 * @return ScheduleManager: a schedule manager object
 * 
 */
ScheduleManager::ScheduleManager(void)
{
	mpSchedule = new Schedule();
	mpScenarioMap = NULL;
	m_Description = "";
	m_ScheduleID = "";
}

/**
 * destructor
 * 
 */
ScheduleManager::~ScheduleManager(void)
{
	if (mpSchedule)
		delete mpSchedule;

	/* clear up the map for ScenarioEditor */
	if (mpScenarioMap) 
	{
		mpScenarioMap->clear();
		delete mpScenarioMap;
	}
}

/**
 * LoadSchedule: This method loads the schedule file from disk
 * @param ScheduleName: File name of schedule file
 * @return int 0 for success and negative for failure
 * 
 */
int ScheduleManager::LoadSchedule(string ScheduleName) 
{
	int ScenarioID = 0;
	int ret = SUCCESS;
	string ScenarioName ="";
	string line="", lValue="", rValue="";
	map<int, string>* mapScenarioIDs = new map<int, string>();
	size_t cutAt = 0;
	ifstream iFile;

	iFile.open(ScheduleName.c_str(), ios::in);

	if (iFile.is_open())
	{
		while (!iFile.eof() )
		{
			//iFile.getline()
			getline (iFile, line);
			if (line == "")
				break;
			cutAt = line.find_first_of("=");

			lValue = line.substr(0, cutAt);
			rValue = line.substr(cutAt+1);
			
			/* Step 1: extract scheduleID and description */
			if (!strcmp(lValue.c_str(), SCH_ID)) 
			{
				mpSchedule->SetScheduleId(atoi(rValue.c_str()));
				continue;

			} else if (!strcmp(lValue.c_str(), SCH_DESC)) {
				mpSchedule->SetDescription(rValue);
				continue;
			}

			/* insert scnarioID and scenario file name pairs into map*/
			ScenarioID = atoi(lValue.c_str());
			ScenarioName = rValue;
			
			if (cutAt < line.size()) 
			{
				mapScenarioIDs->insert(pair<int, string> (ScenarioID, ScenarioName));
			} 
			else 
			{
				INFO("one of scenarios is not valid\n");
				delete mapScenarioIDs;
				return (-INVALID_ARGUMENT); 
			}

		}
		iFile.close();
		mpSchedule->SetScenarioIDs(mapScenarioIDs);
	} else {
		ret = (-FILE_NOT_FOUND);
		delete mapScenarioIDs;
	}

	return ret; 
}

/**
* OpenSchedule: This method reads the schedule file from disk 
*				This method is only used by Schedule Editor
* @param ScheduleName: File name of schedule file
* @return int 0 for success and negative eror for failure
* 
*/
int ScheduleManager::OpenSchedule(string FilePath) 
{
	int ret = SUCCESS;
	string line ="", lValue = "", rValue = "";
	size_t cutAt = 0;
	ifstream iFile;

	iFile.open(FilePath.c_str(), ios::in);

	if (iFile.is_open())
	{
		/* allocate memory if mpScenarioMap is not allocated */
		if(!mpScenarioMap)
			mpScenarioMap = new map<string, string>();

		while (!iFile.eof() )
		{
			//iFile.getline()
			getline (iFile, line);
			if (line == "")
				break;
			cutAt = line.find_first_of("=");

			lValue = line.substr(0, cutAt);
			rValue = line.substr(cutAt+1);

			/* Step 1: extract scheduleID and description */
			if (!strcmp(lValue.c_str(), SCH_ID)) 
			{
				m_ScheduleID = rValue.c_str();
				continue;

			} else if (!strcmp(lValue.c_str(), SCH_DESC)) {
				m_Description = rValue;
				continue;
			}

			/* insert scnarioID and scenario file name pairs into map*/
			if (cutAt < line.size()) 
			{
				mpScenarioMap->insert(pair<string, string> (lValue, rValue));
			} 
			else 
			{
				INFO("one of scenarios is not valid\n");
				return (-INVALID_ARGUMENT); 
			}

		}
		iFile.close();
	} else {
		ret = (-FILE_NOT_FOUND);
	}

	return ret; 
}

/**
 * GetSchedule
 * @return Schedule* the schedule object
 * 
 */
Schedule* ScheduleManager::GetSchedule()
{
	return mpSchedule;
}

/* functions for Scenario editor */
/**
 * AddScenario
 * @param ScenarioID: id of scenario to be added
 * @param ScenarioName: name of scenario to be added
 * @return int 0 for success and 1 for failure
 * 
 */
int ScheduleManager::AddScenario(string ScenarioID, string ScenarioName)
{
	map <string, string>::iterator found;

	if (!mpScenarioMap)
		mpScenarioMap = new map<string, string>;

	if (!mpScenarioMap->empty()) 
	{
		found = mpScenarioMap->find(ScenarioID);
		if (found != mpScenarioMap->end())
			return (-FILE_EXISTS); 
	}

	mpScenarioMap->insert(pair<string, string> (ScenarioID, ScenarioName));

	return SUCCESS;/* FIXME: should return a specific value such as 'SUCCESS' */
}

/**
 * RemoveScenario remove existing scenario from the mpScenarioMap <<what is mpScenarioMap?>>
 * @param sId: id of scenario to be removed
 * @return int 0 for success and 1 for failure
 * 
 */
int ScheduleManager::RemoveScenario(string sId) 
{
	if (!mpScenarioMap)
		return (-NULL_POINTER);

	return (int) mpScenarioMap->erase(sId);
}

/**
 * InsertScenario insert a scenario into mpScenarioMap <<what is mpScenarioMap?>>
 * @param sId: id of scenario to be removed
 * @param sName: name of scenario to be removed
 * @param targetID: position to which the scenario is to be inserted
 * @return int 0 for success and 1 for failure
 * 
 */
int ScheduleManager::InsertScenario(string sId, string sName, string targetID)
{
	map <string, string>::iterator pos;

	if (!mpScenarioMap)
		return (-NULL_POINTER); /*FIXME: specific error should be specified */
	
	pos = mpScenarioMap->find(targetID);
	if (pos == mpScenarioMap->end())
		return (-FILE_NOT_FOUND); /*FIXME: specific error should be specified */
	
	mpScenarioMap->insert(pos, pair<string, string> (sId, sName));
	return	SUCCESS; /* FIXME: should return a specific value such as 'SUCCESS' */
}

/**
* SaveSchedule create a new schedule file with a given parameter. Internal member variable
* mpScenarioMap will be used to fill out the new schedule file.
* @param fname *: string pointer for a filename to be created
* @return SUCCESS for success, negative error code in case of failure
* 
*/

int ScheduleManager::SaveSchedule(string fname)
{
	int ret = SUCCESS;
	string FullPath = "";
	ofstream oFile;
	char buf[LINE_MAX];
	
	FullPath = ConfigManager::Instance()->GetConfigValue("DIR_SCHEDULES");
	FullPath.append(fname);

	map<string, string>::iterator iter;


	if (!mpScenarioMap)
		return  -(NULL_POINTER);

	if (mpScenarioMap->empty())
	{
		return -(NO_DATA_AVAILABLE);
	}
		 
	oFile.open(FullPath.c_str(), ios::out);

	if (oFile.is_open())
	{
		/* write Schedule ID and Description first */
		sprintf(buf, "ScheduleID=%s\n", m_ScheduleID.c_str());
		oFile.write(buf, strlen(buf));

		sprintf(buf, "Description=%s\n", m_Description.c_str());
		oFile.write(buf, strlen(buf));
		for (iter = mpScenarioMap->begin(); iter != mpScenarioMap->end(); iter++) 
		{
			sprintf(buf, "%s=%s\n", iter->first.c_str(), iter->second.c_str());
			oFile.write(buf, strlen(buf));
		}
		oFile.close();
	}

	return ret;
}

void ScheduleManager::SetScheduleID (string ScheduleID)
{
	m_ScheduleID = ScheduleID;
}

void ScheduleManager::SetDescription (string Description)
{
	m_Description = Description;
}