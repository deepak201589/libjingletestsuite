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
// MainGUIDoc.cpp : implementation of the CMainGUIDoc class
//

#include "stdafx.h"
#include "MainGUI.h"

#include "MainGUIDoc.h"
#include "MainGUI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainGUIDoc

IMPLEMENT_DYNCREATE(CMainGUIDoc, CDocument)

BEGIN_MESSAGE_MAP(CMainGUIDoc, CDocument)
END_MESSAGE_MAP()


// CMainGUIDoc construction/destruction

CMainGUIDoc::CMainGUIDoc()
{
	// TODO: add one-time construction code here
	TRACE("document object is contructed");
	m_IsOn = FALSE;
}

CMainGUIDoc::~CMainGUIDoc()
{
#ifdef _DEBUG
	Dump(afxDump);
#endif
}

BOOL CMainGUIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

void CMainGUIDoc::Serialize(CArchive& ar)
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


// CMainGUIDoc diagnostics

#ifdef _DEBUG
void CMainGUIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMainGUIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
//	dc << "\n" << m_query << "\n";
}
#endif //_DEBUG


// CMainGUIDoc commands
