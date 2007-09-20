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
#include "DBWrapper.h"

#define StringToChar(str) (char *)str.c_str()

DBWrapper::DBWrapper(void)
{
	connection = NULL;
	utils = NULL;
	utils = new Utils();
	ConnectToDB();
}

DBWrapper::~DBWrapper(void)
{
	if (utils)
		delete utils;
}

int DBWrapper::ConnectToDB()
{
	int status = SUCCESS;
	ConfigManager *cm = ConfigManager::Instance();
	char* DBName = utils->StringToCharPointer(cm->GetConfigValue("DB_NAME"));
	char* HostName = utils->StringToCharPointer(cm->GetConfigValue("DB_HOST"));
	char* UserID = utils->StringToCharPointer(cm->GetConfigValue("DB_USER"));
	char* Password = utils->StringToCharPointer(cm->GetConfigValue("DB_PASS"));

	connection = new sql_connection_c( DBName, 
           HostName, UserID, Password );

	if (connection->errcode() == 1)
		status = DB_INIT_FAILED;
	else if (connection->errcode() == 2)
		status = DB_CONNECT_FAILED;
	else if (connection->errcode() == 3)
		status = DB_SETDB_FAILED;
	else if(connection->errcode() != 0)
		status = FAILURE;

	delete DBName;
	delete HostName;
	delete UserID;
	delete Password;

	return status;
}

int DBWrapper::GetNewRunID()
{
	int result = SUCCESS;
	sql_result_c *sql_result = NULL;
	sql_row_c sql_row;
	sql_query_c query( connection );
	if ( !query.execute( "SELECT COALESCE(MAX(RunID)) from resultmaster" ) )
	{
		printf( "oops... didn't execute!!\n" );
		return (-QUERY_EXEC_FAILED);
	}

	sql_result = query.store();
	int n_rows = sql_result->n_rows();

	sql_row = sql_result->fetch_row();
	
	if (!n_rows)
		return (-FAILURE);

	result = atoi((char*)sql_row[0])+1;
	return result;
}

/*
 * Retrieve data from DB.
 * ResultList should be freed outside of this method.
 * @param queryString string containing query
 * @param nField the number of field retrieved
 * @return ResultList with data in case of success, NULL otherwise.
 */

list<string*>* DBWrapper::ReadRepository(char* queryString, int *nField)
{
	int n_fields = 0;
	sql_result_c *sql_result = NULL;
	sql_row_c sql_row;
	sql_query_c query( connection );

	list<string*> *ResultList = new list<string*>();
	if ( !query.execute( queryString) )
	{
		delete ResultList;
		ResultList = NULL;
		return ResultList;
	}

	sql_result = query.store();
	int n_rows = sql_result->n_rows();

	if (!n_rows) 
	{
		delete ResultList;
		ResultList = NULL;
		return ResultList;
	}

	string* sArray;

	//Use this parameter to create as many string arrays as you want.
	n_fields = sql_result->n_fields();
	*nField = n_fields;

	for(int row=0; row<n_rows; row++)
	{
		sql_row = sql_result->fetch_row();
		sArray= new string[n_fields];
		for (int col=0; col<n_fields; col++)
		{
			sArray[col] = sql_row[col];
		}
		ResultList->push_back(sArray);
	}

	return ResultList;
}

int DBWrapper::WriteResults(string sQuery)
{
	sql_query_c query( connection );

	int status = SUCCESS;

	char* queryString = StringToChar(sQuery);
	if ( query.execute( queryString ) )
	{
		status = QUERY_EXEC_FAILED;
	}
	return status;
}

