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
#include "Utils.h"
#include "ErrorCode.h"

Utils::Utils(void)
{
	m_HashValue = 0;
}

Utils::~Utils(void)
{
	m_HashValue = 0;
}

char* Utils::StringToCharPointer(std::string str)
{
	int length = (int) str.length();
	char* returnValue = new char[length+1];
	
	strcpy(returnValue, (char *)str.c_str());
	returnValue[length] = '\0';
	return returnValue;
}

/**
 * Hash function that can be used repeatedly for a file.
 *
 * @param *FileName: Name of file for which the hash is to be generated
 * @param return: resulting hash value.
 */

int Utils::CreateFileHash(const char* FileName, char* digesthex){
	const unsigned int BUFF_SIZE = 1024;
	unsigned char buff[ BUFF_SIZE ];
	CMD5 hash;
	fstream file;

	file.open(FileName, ios::in |ios::binary);

    if( file.is_open())
    {
		//Calculate the digest by calling Update for each block of the file
	    
		while( !file.eof() )
		{
			file.read( ( char* )buff, BUFF_SIZE );
			hash.Update( buff, file.gcount() );
		}
	    
		//Do final changes and get the digest in hex format
	    
		hash.FinalHex(digesthex); // FinalHex reinitializes the hash object for the next use
	    
		file.close();
	} 
	else 
	{
		cout << "\nCould not open file: " << FileName;
		return (-FILE_NOT_FOUND);
	}
	
	return SUCCESS;
}
