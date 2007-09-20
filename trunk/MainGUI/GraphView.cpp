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
// GraphView.cpp : implementation file
//

#include "stdafx.h"
#include "MainGUI.h"
#include "GraphView.h"


// CGraphView

IMPLEMENT_DYNCREATE(CGraphView, CFormView)

CGraphView::CGraphView()
	: CFormView(CGraphView::IDD)
	, m_FileName(_T(""))
{

}

CGraphView::~CGraphView()
{
}

void CGraphView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FNAME, m_FileName);
	DDX_Control(pDX, IDC_GRRAPH, m_hGraph);
}

BEGIN_MESSAGE_MAP(CGraphView, CFormView)
END_MESSAGE_MAP()


// CGraphView diagnostics

#ifdef _DEBUG
void CGraphView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CGraphView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CGraphView message handlers
