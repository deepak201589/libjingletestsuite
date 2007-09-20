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
// MainGUI.h : main header file for the MainGUI application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "ReportDoc.h"
#include "ScenarioDoc.h"
#include "ScheduleDoc.h"

// CMainGUIApp:
// See MainGUI.cpp for the implementation of this class
//

class CMainGUIApp : public CWinApp
{
public:
	CMainGUIApp();

	/* K.M Han: document object for report manager */
	CMultiDocTemplate *m_pReportManagerDoc;
	CReportDoc *m_pReport;

	/* K.M Han: document object for scenario editor */
	CMultiDocTemplate *m_pScenarioEditorDoc;
	CScenarioDoc *m_pScenario;
	
	/* K.M Han: document object for schedule editor */
	CMultiDocTemplate *m_pScheduleEditorDoc;
	CScheduleDoc *m_pSchedule;

// Overrides
public:
	virtual BOOL InitInstance();

// member functions

	/* K.M Han: method to create a new window */
	CFrameWnd* CreateNewWindow( CDocTemplate*, CDocument*);


// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnGenerateGraph();
public:
	afx_msg void OnEditScenario();
public:
	afx_msg void OnEditSchedule();
};

extern CMainGUIApp theApp;