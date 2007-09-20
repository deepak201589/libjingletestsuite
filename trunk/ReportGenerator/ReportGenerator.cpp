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
// ReportGenerator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include "Common/ErrorCode.h"
#include "Common/ResultManager.h"
#include "TestHelper/PlotWrapper.h"

using namespace std;

/**
 * GetSQLQuery: This method reads an input file and gets the sql query.
 * @param pname: Command entered by the user
 * @return void
 * 
 */
static string GetSQLQuery(string reportFile)
{
	string sQuery = "";
	string line;
	ifstream iFile(reportFile.c_str(),ios::in);

	if (iFile.is_open())
	{
		while (! iFile.eof() )
		{
			getline (iFile, line);
			sQuery.append(line);
		}
		iFile.close();
	}

	return sQuery;
}


/**
 * DisplayUsage: This method displays a help to the user, on how to execute the test-suite application.
 * @param pname: Command entered by the user
 * @return void
 * 
 */
static void DisplayUsage(char* pname)
{
	// display usage
	cout << "USAGE: " << pname << " [sFile]" << endl;
	cout << "  " << endl;
	cout << "COMMAND LINE ARGUMENTS" << endl;
	cout << "  sFile	-- schedule File name (no need to specify path)" << endl;
	exit(0);
}

/**
 * main
 * @param argc: no. of arguments
 * @param argv: character array of input arguments
 * @return int: 0 - exit with success. 1 - exit with error.
 * 
 */
int main(int argc, char* argv[])
{
	if (argc != 0)
	{
		DisplayUsage(argv[0]);
	}
	
	ResultManager* resultManager = new ResultManager();
	PlotWrapper* plotWrapper = new PlotWrapper();

	// Get the SQL Query; Preferably from a file; optionally from a command-line?
	char* strSQL = (char*)GetSQLQuery(argv[1]).c_str();
	string dataFile = "c:\\scenario1.dat";
	string settingsFile = "c:\\senario1.txt";

	int ret = 0;
	ret = resultManager->WriteDataToFile(strSQL, dataFile);

	if (ret == SUCCESS)
		cout << "Result manager wrote data file successfully.";
	else
		cout << "Result manager failed with error code: " << ret;

	ret = plotWrapper->Plot(settingsFile, dataFile);

	if (ret == SUCCESS)
		cout << "PlotWrapper created graphs successfully.";
	else
		cout << "PlotWrapper failed with error code: " << ret;


	delete  resultManager;
	delete plotWrapper;
	return 0;
}

