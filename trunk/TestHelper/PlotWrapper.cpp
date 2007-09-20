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
#include "PlotWrapper.h"

PlotWrapper::PlotWrapper(void)
{
	cfg = ConfigManager::Instance();
}

PlotWrapper::~PlotWrapper(void)
{
}

int PlotWrapper::Plot(string settingsFile, string dataFile)
{
	int iResult = SUCCESS;
	string cmd = "";

	ifstream iSettingsFile(settingsFile.c_str(), ios::in);
	if (iSettingsFile.is_open()) {
		iSettingsFile.close();
	} else {
		iResult = -(FILE_DOES_NOT_EXIST);
		return iResult;
	}

	ifstream iDataFile(dataFile.c_str(), ios::in);
	if (iDataFile.is_open()) {
		iDataFile.close();
	} else {
		iResult = -(FILE_DOES_NOT_EXIST);
		return iResult;
	}
	
	cmd = cfg->GetConfigValue("PW_WPLOT_PATH");
	cmd = cmd + " " + settingsFile;
	iResult = system(cmd.c_str());

	if (iResult != SUCCESS) 
		iResult = -(FAILURE);

	return iResult;
}

int PlotWrapper::CreateSettingsFile(SettingsFile* sf)
{
	ofstream oFile;
	string sTemp = "";
	int ret = SUCCESS;

	if (sf->nSrc < 2 || sf->nSrc > 3)
		ret = -(INVALID_ARGUMENT);
	else {

		oFile.open(sf->SettingsFileName.c_str(), ios::out);
		
		if (oFile.is_open())
		{
			sTemp = "set out \"" + sf->OutputFileName + "\"\n";
			oFile.write(sTemp.c_str(), sTemp.length());
			sTemp = "set terminal " + sf->OutputFileType + " size " + sf->CanvasSize + "\n";
			oFile.write(sTemp.c_str(), sTemp.length());
			sTemp = "set data style " + sf->DataStyle + "\n";
			oFile.write(sTemp.c_str(), sTemp.length());
			sTemp = "set title \"" + sf->GraphTitle + "\"\n";
			oFile.write(sTemp.c_str(), sTemp.length());
			sTemp = "set xrange " + sf->XRange + "\n";
			oFile.write(sTemp.c_str(), sTemp.length());
			sTemp = "set yrange " + sf->YRange + "\n";
			oFile.write(sTemp.c_str(), sTemp.length());
			sTemp = "set xlabel \"" + sf->XLabel + "\"\n";
			oFile.write(sTemp.c_str(), sTemp.length());
			sTemp = "set ylabel \"" + sf->YLabel + "\"\n";
			oFile.write(sTemp.c_str(), sTemp.length());

			if (strcmp(sf->XStyle.c_str(),"logscale") != 0 && strcmp(sf->YStyle.c_str(),"logscale") != 0)
			{
				sTemp = "set nologscale\n";			
			}
			else if (strcmp(sf->XStyle.c_str(),"logscale") == 0)
			{
				sTemp = "set logscale x\n";
			}
			else if (strcmp(sf->YStyle.c_str(),"logscale") == 0)
			{
				sTemp = "set logscale Y\n";
			}
			oFile.write(sTemp.c_str(), sTemp.length());
			
			if (sf->nSrc == 2)
				sTemp = "pl '" + sf->DataFileName + "' u 1:2 t '" + sf->SrcName1 +"'";
			else 
				sTemp = "pl '" + sf->DataFileName + "' u 1:2 t '" + sf->SrcName1 +"', '" + sf->DataFileName + "' u 1:3 t '" + sf->SrcName2 + "'";

			oFile.write(sTemp.c_str(), sTemp.length());

		}
		oFile.close();
	}

	return ret;
}

int PlotWrapper::SetDefaultValue(SettingsFile *setting)
{
	int ret = SUCCESS; 

	if (!setting)
		ret = -(FAILURE);
	else {
		setting->CanvasSize = "640, 400";
		setting->DataStyle = "lp";
		setting->OutputFileType = "png";
		setting->YStyle = "";
		setting->XStyle = "";
	}

	return ret;
}