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
#pragma once

#include <string>
#include <list>
#include "afxcmn.h"
#include "afxwin.h"
#include "macro.h"
#include "Common/Common.h"
#include "Common/Result.h"
#include "Common/DBWrapper.h"
#include "Common/ErrorCode.h"


using namespace std;


// ReportManager form view

class ReportManager : public CFormView
{
	DECLARE_DYNCREATE(ReportManager)

protected:
	ReportManager();           // protected constructor used by dynamic creation
	virtual ~ReportManager();

public:
	enum { IDD = IDD_REPORT_GENERATOR };

    void OnBnClickedGenerate();
	void OnInitialUpdate();
	
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	

	/* member variables */
public:
	CString m_filename;
	CString m_Title;

	/* member variables for X axis value */
	CString m_xType;
	CString m_xValue;
	CString m_xValue2;
	CString m_xFormula;
	CString m_xMin;
	CString m_xMax;

	/* member variables for Y axis value */
	CString m_yName;
	CString m_yName2;

	CString m_yType;
	CString m_yValue;
	CString m_yValue2;
	CString m_yFormula;
	CString m_yMax;
	CString m_yMin;

	/* data source variables and contraint variables */
	CListCtrl m_rangeList;
	CListCtrl m_rangeList2;

	CString m_orderby;
	CString m_groupby;
	CString m_rangeFormula;

	CString m_query;
	CButton m_btPreview;
	CButton m_btGenerate;

	/* member variables for Y axis value */


public:
	afx_msg void OnBnClickedPreview();
	afx_msg void OnEnChangeQuery();
	








};

