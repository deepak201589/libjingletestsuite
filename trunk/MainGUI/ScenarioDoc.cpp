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
// ScenarioDoc.cpp : implementation file
//

#include "stdafx.h"
#include "macro.h"
#include "MainGUI.h"
#include "ScenarioDoc.h"


// CScenarioDoc

IMPLEMENT_DYNCREATE(CScenarioDoc, CDocument)

CScenarioDoc::CScenarioDoc()
{
	m_manager.InitScenario();
}

BOOL CScenarioDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CScenarioDoc::~CScenarioDoc()
{
}


BEGIN_MESSAGE_MAP(CScenarioDoc, CDocument)
END_MESSAGE_MAP()


// CScenarioDoc diagnostics

#ifdef _DEBUG
void CScenarioDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CScenarioDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CScenarioDoc serialization

void CScenarioDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}
#endif
int CScenarioDoc::SaveAsFile(CString FileName)
{
	int ret;
	string fname;

	fname.append(CASTSTR(FileName));
	fname.append(SCENARIO_EXTENSION);

	ret = m_manager.SaveScenario(fname);

	return ret;
}

// CScenarioDoc commands
