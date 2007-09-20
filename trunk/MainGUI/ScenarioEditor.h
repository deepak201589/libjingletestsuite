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
#ifndef __scenarioeditor__
#define  __scenarioeditor__

#pragma once



// CScenarioEditor form view

class CScenarioEditor : public CFormView
{
	DECLARE_DYNCREATE(CScenarioEditor)

protected:
	CScenarioEditor();           // protected constructor used by dynamic creation
	virtual ~CScenarioEditor();

public:
	enum { IDD = IDD_SCENARIO_EDITOR };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	/* member function */
	int TransferData(Scenario* pScenario);
	void SplitFilePath(CString OriginalPath, CString *fname, CString *fpath);
	void ClearContent();


	/* member variables */
public:
	CString m_ScenarioID;
	CString m_ScenarioName;
	CString m_SenderLoginID;
	CString m_ReceiverLoginID;
	CString m_SenderPasswd;
	CString m_FilePath;
	CString m_Description;
	BOOL m_bUseNISTnet;
	CString m_PacketDelay;
	CString m_PacketDup;
	CString m_PacketLoss;
	CString m_BandWidth;
public:
	afx_msg void OnBnClickedSave();
public:
	afx_msg void OnBnClickedBtSpath();
};


#endif