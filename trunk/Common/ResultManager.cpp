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
#include "StdAfx.h"
#include "ResultManager.h"

ResultManager::ResultManager(void)
{
}

ResultManager::~ResultManager(void)
{
}

int ResultManager::WriteDataToFile(char* query, string fname)
{
	int status = SUCCESS;
	int nColumn = 0;
	DBWrapper *dbw = NULL;
	ofstream oFile;
	char buf[100];
	list<string*> *ResultList= NULL;

	dbw = new DBWrapper();
	ResultList = dbw->ReadRepository(query, &nColumn);
	list<string*>::iterator iter;

	/* if query execution fails, return -FAILURE */
	if (!ResultList) {
		status -(FAILURE);
		goto release;
	}

	oFile.open(fname.c_str(), ios::out);

	string* sArray;

	if (oFile.is_open())
	{
		for (iter = ResultList->begin(); iter != ResultList->end(); iter++) 
		{
			sArray = *iter;
			for(int i=0; i< nColumn; i++)
			{
				oFile.write(sArray[i].c_str(), strlen(sArray[i].c_str()));
				oFile.write(" ",strlen(" "));

			}
			oFile.write("\n",strlen("\n"));
			delete []sArray; //<-- you should release memory here
		}
		oFile.close();
	} else 
		status = -(FILE_NOT_FOUND);

release:
	if (ResultList)
		delete ResultList;
	if (dbw)
		delete dbw;

	return status;
}
