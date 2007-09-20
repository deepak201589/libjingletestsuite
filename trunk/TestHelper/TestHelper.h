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
#ifndef __testhelper_h
#define __testhelper_h

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the TESTHELPER_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// TESTHELPER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef TESTHELPER_EXPORTS
#define TESTHELPER_API __declspec(dllexport)
#else
#define TESTHELPER_API __declspec(dllimport)
#endif

// This class is exported from the TestHelper.dll
class TESTHELPER_API CTestHelper {
public:
	CTestHelper(void);
	// TODO: add your methods here.
};

extern TESTHELPER_API int nTestHelper;

TESTHELPER_API int fnTestHelper(void);

#endif