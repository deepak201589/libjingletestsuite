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
* Schedule object contains a list of scenario ids
* This list is taken from a schedule file
* This component is taken by the sender agent and passed to scenario manager

Updates
=======
------------------------------------------------------------------------
| No. | Date |         Author        |          Reason for update       |
------------------------------------------------------------------------
|  1. |      |                       |									|
------------------------------------------------------------------------

*/

#include "StdAfx.h"
#include "Schedule.h"

/**
 * constructor
 * @param void
 * @return void
 * 
 */
Schedule::Schedule(void)
{
	mScheduleId = -1;
	mDescription = "";
	mScenarioIDs = NULL;
}

/**
 * destructor
 * @param void
 * @return void
 * 
 */
Schedule::~Schedule(void)
{
	mScheduleId = -1;
	mDescription = "";
	if (mScenarioIDs)
		delete mScenarioIDs;
}


void Schedule::SetScheduleId(int sID)
{
	mScheduleId = sID;
}

int Schedule::GetScheduleId() 
{
	return mScheduleId;
}


void Schedule::SetDescription(string description)
{
	mDescription = description;
}

string Schedule::GetDescription(void) {
	return mDescription;
}

/**
 * SetScenarioIDs: Modifier method for list of scenario ids
 * @param void
 * @return map<int, string>* : map of scenario IDs and corresponding file names
 * 
 */
void Schedule::SetScenarioIDs(map<int, string>* scenarioIDs)
{
	mScenarioIDs = scenarioIDs;
	/* FIXME: probably we need to return an error here too. */
}

/**
 * GetScenarioIDs: Access method for list of scenario ids
 * @param void
 * @return map<int, string>* : map of scenario IDs and corresponding file names
 * 
 */
map<int, string>* Schedule::GetScenarioIDs()
{
	return mScenarioIDs;
}

/**
* InitScenarioIDs: allocate memory for scenario map
* @param void
* @return none
* 
*/

void Schedule::InitScenarioIDs()
{
	if (!mScenarioIDs)
		mScenarioIDs = new map <int, string>();
}