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
#pragma once

#include <time.h>
#include <STDIO.H>
#include <list>
#include <string>
#include "Common.h"
#include "mysqlplus.h"
#include "ErrorCode.h"
#include "ConfigManager.h"
#include "Utils.h"

class COMMON_API DBWrapper
{
public:
	DBWrapper(void);
	~DBWrapper(void);
	list<string*>* ReadRepository(char* query, int *nColumn);
	int WriteResults(string);
	int ConnectToDB();
	int GetNewRunID();

private:
	sql_connection_c *connection;
	Utils *utils;
	string CreateQuery(Result*);
};
