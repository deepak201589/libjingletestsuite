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
#include "afxwin.h"



// CScheduleEditor form view

class CScheduleEditor : public CFormView
{
	DECLARE_DYNCREATE(CScheduleEditor)

protected:
	CScheduleEditor();           // protected constructor used by dynamic creation
	virtual ~CScheduleEditor();

public:
	enum { IDD = IDD_SCHEDULE_EDITOR };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()

	/* member functions */
public:
	void FillUpList(CString ScenarioDir);
	void OnInitialUpdate();
	void ListSwitch(int CurIndex, int direction);
	void ClearContent();

	/* member variables */
public:
	CString m_ScheduleID;
	CString m_ScheduleName;
	CString m_Description;
	CListBox m_ListAvailable;
	CListBox m_ListScheduled;

public:
	afx_msg void OnBnClickedSchSave();
public:
	CListBox m_AvailableList;
public:
	CListBox m_SelectedList;
public:
	afx_msg void OnBnClickedBtLeft();
public:
	afx_msg void OnBnClickedBtRight();
public:
	afx_msg void OnBnClickedBtUp();
public:
	afx_msg void OnBnClickedBtDown();
public:
	afx_msg void OnBnClickedBtRightAll();
public:
	afx_msg void OnBnClickedBtLeftAll();
};

