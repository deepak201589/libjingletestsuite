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
#ifndef __reportmanager__
#define  __reportmanager__

#pragma once

// CReportDoc document
#include "ReportQuery.h"
#include <list>


class CReportDoc : public CDocument
{
	DECLARE_DYNCREATE(CReportDoc)

public:
	CReportDoc();
	virtual ~CReportDoc();

/* member variables */
public:
	CReportQuery m_query;
	CString m_SqlQuery;
	CString m_Fname;
	CString m_Title;
	CString m_y1Title;
	CString m_y2Title;
	CString m_xLabel;
	CString m_yLabel;
	CString m_xMin;
	CString m_xMax;
	CString m_yMin;
	CString m_yMax;
	int m_nYValues;

#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual BOOL OnNewDocument();

	DECLARE_MESSAGE_MAP()
public:
	/* member functions */
	int GenerateGraph(void);
	int MakeQuery(CString *);
};
#endif