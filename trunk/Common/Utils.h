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
#ifndef __utils_h
#define __utils_h

#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "common.h"
#include "QuickHash.h"

using namespace QuickHash;
using namespace std;

class COMMON_API Utils
{
public:
	Utils(void);
	~Utils(void);
	/* Convert string to char array */
	char* StringToCharPointer(std::string str);
	
	/* create file hash from given file */
	int CreateFileHash(const char* FileName, char* hash);

/* member variable */
private:
	unsigned char m_HashValue;
};

#endif
