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
* Relative Path: /Common/Schedule.h
* Author: Kimyung Han
* This file is the header description of Schedule
* Schedule object contains a list of scenario ids
* This list is taken from a schedule file
* This component is taken by the sender agent and passed to scenario manager
*/

#ifndef __schedule_h
#define __schedule_h

#pragma once
#pragma warning(disable:4251)
#include "Common.h"
#include <map>
#include <string>

/* Global definition for Schedule */

#define SCH_ID		"ScheduleID"
#define SCH_DESC	"Description"

using namespace std;

/*
* Class Name: Schedule
* Purpose: The schedule object contains the list of scenario ids contained in a schedule file
* It is a copy of a schedule file read in to memory
* The list is private and is accessed or modified using getter and setter method
*/
class COMMON_API Schedule
{
	public:
		/* Constructor */
		Schedule(void);

		/* Destructor */
		~Schedule(void);	

		/* Member function */
	public:
		void SetScheduleId(int scheduleID);
		int GetScheduleId();
		void SetDescription(string description);
		string GetDescription();
		void SetScenarioIDs(map<int, string>* pScenarioIDs);
		map<int, string>* GetScenarioIDs();
		void InitScenarioIDs();
		
	private:
		int mScheduleId;
		string mDescription;
		map<int, string>* mScenarioIDs;
};

#endif
