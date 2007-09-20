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
* Relative Path: /TestHelper/PlotWrapper.h
* PlotWrapper is used to launch the graphing tool and create a graph
* This component needs two imput files to create a graph:
* <give settings file format here>
* <give data file format here>
* This component needs ctave/wgnuplot.exe in system path and is called by <MainGUI>
*/

#ifndef __plotwrapper_h
#define __plotwrapper_h

#pragma once
#include <string>
#include <fstream>
#include "TestHelper.h"
#include "Common/ConfigManager.h"
#include "Common/ErrorCode.h"

using namespace std;

struct SettingsFile
{
	string SettingsFileName;
	string OutputFileType;
	string OutputFileName;
	string CanvasSize;
	string DataFileName;
	string DataStyle;
	string GraphTitle;
	string XRange;
	string YRange;
	string XLabel;
	string YLabel;
	string XStyle;
	string YStyle;
	string SrcName1;
	string SrcName2;
	int nSrc;
};

class TESTHELPER_API PlotWrapper
{
public:
	PlotWrapper(void);
	~PlotWrapper(void);
	
	int CreateSettingsFile(SettingsFile* setting);
	int Plot(string settingsFile, string dataFile);
	int SetDefaultValue(SettingsFile *setting);

private:
	ConfigManager* cfg;
};

#endif