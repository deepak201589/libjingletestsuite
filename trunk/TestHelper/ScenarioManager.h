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
* Relative Path: /TestHelper/ScenarioManager.h
* Author: Kimyung Han
* ScenarioManager reads/creates/updates/deletes scenario files
* This file is the header description of ScenarioManager
* This component is called by <fill the data here>
*/
#ifndef __scenariosmanager_h
#define __scenariosmanager_h

#pragma once
#include <map>
#include <cmath>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <limits.h>
#include "TestHelper.h"
#include "Common/Scenario.h"
#include "Common/Utils.h"
#include "Common/debugging.h"
#include "Common/ErrorCode.h"
#include "Common/ConfigManager.h"

#define PERCENT_MIN 0
#define PERCENT_MAX 100
#define LINE_MAX 256
#define INT_LENGTH 5

/*
* Class Name: ScenarioManager
* Purpose: ScenarioManager reads/creates/updates/deletes scenario files.
*/
class TESTHELPER_API ScenarioManager
{
public:
	ScenarioManager(void);
	~ScenarioManager(void);

public:
	/* Member functions */
	int LoadScenario(string fname);
	int SaveScenario(string fname);
	Scenario *GetScenario();
	bool SetScenario(Scenario *scenario);
	int GetScenarioMap(map<string, string> *pScenarioMap);
	void InitScenario(void);

private:
	/* Member variables */
	Scenario *mpScenario;

};
#endif