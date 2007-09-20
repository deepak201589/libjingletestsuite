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
// MainGUIView.cpp : implementation of the CMainGUIView class
//

#include "stdafx.h"
#include "MainGUI.h"

#include "MainGUIDoc.h"
#include "MainGUIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainGUIView

IMPLEMENT_DYNCREATE(CMainGUIView, CView)

BEGIN_MESSAGE_MAP(CMainGUIView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMainGUIView construction/destruction

CMainGUIView::CMainGUIView()
{
	// TODO: add construction code here

}

CMainGUIView::~CMainGUIView()
{
}

BOOL CMainGUIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMainGUIView drawing

void CMainGUIView::OnDraw(CDC* /*pDC*/)
{
	CMainGUIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMainGUIView printing

BOOL CMainGUIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMainGUIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMainGUIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMainGUIView diagnostics

#ifdef _DEBUG
void CMainGUIView::AssertValid() const
{
	CView::AssertValid();
}

void CMainGUIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMainGUIDoc* CMainGUIView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainGUIDoc)));
	return (CMainGUIDoc*)m_pDocument;
}
#endif //_DEBUG


// CMainGUIView message handlers
