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
* File: /Common/ConfigManager.cpp
* Author: Kimyung Han
* Description:
* ConfigManager reads and parses configuration entries from a file.
* The file format should be as follows:
  KEY=VALUE
* This component is called by <fill this data>

Updates
=======
------------------------------------------------------------------------
| No. | Date |         Author        |          Reason for update       |
------------------------------------------------------------------------
|  1. |      |                       |									|
------------------------------------------------------------------------

*/

#include "StdAfx.h"
#include "ConfigManager.h"

ConfigManager* ConfigManager::_instance = NULL;

/**
 * Instance: This is to get an instance of the ConfigManager class.
 * ConfigManager is a singleton and this method makes sure that there will not be many instances created.
 * @return ConfigManager*: an instance of the ConfigManager
 * 
 */
ConfigManager* ConfigManager::Instance () { 
	if (_instance == NULL) 
	{ 
		_instance = new ConfigManager();
	} 
	return _instance; 
} 

/**
 * constructor
 * ConfigManager is a singleton and hence the constructor is protected.
 * @return ConfigManager: an instance of the ConfigManager
 * 
 */
ConfigManager::ConfigManager(void)
{
	mapConfig = new map<string, string>;
	configFile = "..\\Control\\config.dat";

	// Fillup Map of Config values
	string line;
	ifstream iFile(configFile.c_str(),ios::in);

	mapConfig->clear();
	if (iFile.is_open())
	{
		while (! iFile.eof() )
		{
			getline (iFile, line);
			size_t cutAt = 0;
			cutAt = line.find_first_of("=");

			if (cutAt < line.size())
				mapConfig->insert(pair<string,string>
				(line.substr(0,cutAt), line.substr(cutAt+1)));
		}
		iFile.close();
	}
}

/**
 * destructor
 * @return void
 * 
 */
ConfigManager::~ConfigManager(void)
{
	if (_instance)
		delete _instance;
	if (mapConfig)
		delete mapConfig;
}

/**
 * GetConfigValue: This method reads the config file for the value corresponding to the key
 * @param key
 * @return string: Value corresponding to the key
 * 
 */
string ConfigManager::GetConfigValue(string key)
{
	string s = "";
	map<string, string>::iterator p;

	if (!mapConfig)
		return s;

	p = mapConfig->find(key);

	if (p != mapConfig->end()) 
		s = p->second;

	return s;
}