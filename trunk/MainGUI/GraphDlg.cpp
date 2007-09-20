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
// GraphDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MainGUI.h"
#include "GraphDlg.h"
#include <windows.h>
#include <GdiPlus.h>

using namespace Gdiplus;

// CGraphDlg dialog

IMPLEMENT_DYNAMIC(CGraphDlg, CDialog)

CGraphDlg::CGraphDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGraphDlg::IDD, pParent)
	, m_fName(_T(""))
	, m_fPath(_T(""))
{

}

CGraphDlg::~CGraphDlg()
{
}

void CGraphDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FNAME, m_fName);
}

BEGIN_MESSAGE_MAP(CGraphDlg, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CGraphDlg message handlers

void CGraphDlg::OnPaint()
{
	CPaintDC pDC(this); // device context for painting

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	Graphics* pGraphics;
	Image *pImage = NULL;

	pGraphics = new Graphics(pDC);
	pImage = new Image(m_fPath);

	pGraphics->DrawImage(pImage, 0, 50);

	delete pImage;
	delete pGraphics;
	GdiplusShutdown(gdiplusToken);

}
