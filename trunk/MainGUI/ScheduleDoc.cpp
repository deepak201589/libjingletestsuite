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
// ScheduleDoc.cpp : implementation file
//

#include "stdafx.h"
#include "MainGUI.h"
#include "ScheduleDoc.h"


// CScheduleDoc

IMPLEMENT_DYNCREATE(CScheduleDoc, CDocument)

CScheduleDoc::CScheduleDoc()
{
}

BOOL CScheduleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CScheduleDoc::~CScheduleDoc()
{
	TRACE("I am being destroyed");
	cout<< "bye"<<endl;
}


BEGIN_MESSAGE_MAP(CScheduleDoc, CDocument)
END_MESSAGE_MAP()


// CScheduleDoc diagnostics

#ifdef _DEBUG
void CScheduleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CScheduleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CScheduleDoc serialization

void CScheduleDoc::Serialize(CArchive& ar)
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


// CScheduleDoc commands
