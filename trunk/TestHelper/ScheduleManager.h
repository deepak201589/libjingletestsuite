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
* Relative Path: /TestHelper/ScheduleManager.h
* Author: Kimyung Han
* ScheduleManager reads/adds/updates schedule into the schedule file.
* This file is the header description of ScheduleManager
* This component is called by <fill the data here>
*/
#pragma once
#include <map>
#include <string>	
#include <fstream>
#include <iostream>
#include <string>
#include "TestHelper.h"
#include "Common/Schedule.h"
#include "Common/ErrorCode.h"
#include "Common/debugging.h"
#include "Common/ConfigManager.h"

#define LINE_MAX 256

using namespace std;
/*
* Class Name: ScheduleManager
* Purpose: ScheduleManager reads/adds/updates schedule into the schedule file.
*/
class TESTHELPER_API ScheduleManager
{
public:
	ScheduleManager(void);
public:
	~ScheduleManager(void);

public:
	/* member functions */
	Schedule* GetSchedule(void);
	int LoadSchedule(string);

	/* functions for Scenario editor */
	int AddScenario(string scenarioID, string scenarioName);
	int RemoveScenario(string sId);
	int InsertScenario(string sId, string sName, string targetID);
	int SaveSchedule(string fname);
	int OpenSchedule(string FilePath);
	void SetScheduleID (string ScheduleID);
	void SetDescription (string Description);

private:
	/* member variables */
	Schedule *mpSchedule;

	/* member variables for Scenario Editor */
	string m_ScheduleID;
	string m_Description;
	map<string, string> *mpScenarioMap;
};
