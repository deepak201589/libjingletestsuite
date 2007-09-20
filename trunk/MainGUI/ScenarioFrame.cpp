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
// ScenarioFrame.cpp : implementation file
//

#include "stdafx.h"
#include "MainGUI.h"
#include "ScenarioFrame.h"


// CScenarioFrame

IMPLEMENT_DYNCREATE(CScenarioFrame, CMDIChildWnd)

CScenarioFrame::CScenarioFrame()
{

}

CScenarioFrame::~CScenarioFrame()
{
}

BOOL CScenarioFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style &=~FWS_ADDTOTITLE;  
	cs.lpszName = _T("New Scenario Creation");
	return CMDIChildWnd::PreCreateWindow(cs);
}

BEGIN_MESSAGE_MAP(CScenarioFrame, CMDIChildWnd)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CScenarioFrame message handlers

void CScenarioFrame::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	theApp.m_pScenario = NULL;
	CMDIChildWnd::OnClose();
}
