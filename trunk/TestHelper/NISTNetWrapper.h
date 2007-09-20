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
* Relative Path: /TestHelper/NISTNetWrapper.h
* Author: Kalyan
* NISTNet wrapper acts as an interface between the test suite and NISTNet network emulator.
* This file is the header description of NISTNetWrapper
* This component is called by the sender agent to set the parameters in the network emulator (packet loss, bandwidth etc.).
*/

#ifndef __nistnetwrapper_h
#define __nistnetwrapper_h

#pragma once
#include <sstream>
#include <string>
#include <iomanip>
#include "TestHelper.h"
#include "../Common/ConfigManager.h"
#include "../Common/Scenario.h"


/*
* Class Name: NISTNetWrapper
* Purpose: NISTNet wrapper acts as an interface between the test suite and NISTNet network emulator.
*/
class TESTHELPER_API NISTNetWrapper
{
public:
	NISTNetWrapper(void);
	~NISTNetWrapper(void);
	bool Configure(Scenario* scenario);
	bool DeConfigure();

private:
	ConfigManager* cfg;
};

#endif