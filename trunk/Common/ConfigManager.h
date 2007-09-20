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
* Relative Path: /Common/ConfigManager.h
* ConfigManager reads and parses configuration entries from a file.
* The file format should be as follows:
* <give file format here>
* This file is the header description of ConfigManager
* This component is called by <fill this data>
* Author: Kalyan
*/

#ifndef __configmanager_h
#define __configmanager_h

#pragma once
#include <string>
#include <map>
#include <fstream>
#include "Common.h"
#include "Schedule.h"
#include "Scenario.h"
#include "Result.h"


/*
* Class Name: ConfigManager
* Purpose: ConfigManager reads and parses configuration entries from a file.
*/

class COMMON_API ConfigManager
{
public:
	static ConfigManager* Instance();
	~ConfigManager();
	string GetConfigValue(string ValueName);

protected:
	ConfigManager();
	ConfigManager(const ConfigManager&);
	ConfigManager& operator=(const ConfigManager&);
	
private:
	void Init();
	string itos(int i);
	string configFile;

	static ConfigManager* _instance;
	map<string, string>* mapConfig;	
};

#endif