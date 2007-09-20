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
// ScheduleEditor.cpp : implementation file
//

#include "stdafx.h"
#include "MainGUI.h"
#include "ScheduleEditor.h"
#include "ScheduleDoc.h"
#include "../Common/ConfigManager.h"
#include "../Common/ErrorCode.h"
#include "macro.h"

// CScheduleEditor

IMPLEMENT_DYNCREATE(CScheduleEditor, CFormView)

CScheduleEditor::CScheduleEditor()
	: CFormView(CScheduleEditor::IDD)
	, m_ScheduleID(_T(""))
	, m_ScheduleName(_T(""))
	, m_Description(_T(""))
{
	if (IsWindow(m_AvailableList))
		cout<<"List is available" <<endl;
	else
		cout<<"List is not available" << endl;


}

CScheduleEditor::~CScheduleEditor()
{
}

void CScheduleEditor::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SCH_ID, m_ScheduleID);
	DDV_MaxChars(pDX, m_ScheduleID, 10);
	DDX_Text(pDX, IDC_SCH_NAME, m_ScheduleName);
	DDV_MaxChars(pDX, m_ScheduleName, 100);
	DDX_Text(pDX, IDC_SCH_DESC, m_Description);
	DDV_MaxChars(pDX, m_Description, 255);
	DDX_Control(pDX, IDC_LT_AVAILABLE, m_AvailableList);
	DDX_Control(pDX, IDC_LT_SCHEDULED, m_SelectedList);
}

BEGIN_MESSAGE_MAP(CScheduleEditor, CFormView)
	ON_BN_CLICKED(ID_SCH_SAVE, &CScheduleEditor::OnBnClickedSchSave)
	ON_BN_CLICKED(IDC_BT_LEFT, &CScheduleEditor::OnBnClickedBtLeft)
	ON_BN_CLICKED(IDC_BT_RIGHT, &CScheduleEditor::OnBnClickedBtRight)
	ON_BN_CLICKED(IDC_BT_UP, &CScheduleEditor::OnBnClickedBtUp)
	ON_BN_CLICKED(IDC_BT_DOWN, &CScheduleEditor::OnBnClickedBtDown)
	ON_BN_CLICKED(IDC_BT_RIGHT_ALL, &CScheduleEditor::OnBnClickedBtRightAll)
	ON_BN_CLICKED(IDC_BT_LEFT_ALL, &CScheduleEditor::OnBnClickedBtLeftAll)
END_MESSAGE_MAP()


// CScheduleEditor diagnostics

#ifdef _DEBUG
void CScheduleEditor::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CScheduleEditor::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

	
void CScheduleEditor::OnInitialUpdate()
{
	CString ScenarioDir;
	string path;

	/* Synchronized data in CScheduleEditor with CScheduleDoc */
	UpdateData(FALSE);
	ConfigManager *pConfig = ConfigManager::Instance();
	
	path = pConfig->GetConfigValue("DIR_SCENARIOS");

	ScenarioDir.Preallocate(355);
	ScenarioDir += path.c_str();

	ScenarioDir += "\\*.scenario";
	FillUpList(ScenarioDir);
}

void CScheduleEditor::FillUpList(CString fpath)
{
	int nIndex = 0, nCount = 0;
	CString fname;
	CFileFind hFinder;
	BOOL bMore = FALSE;

	bMore = hFinder.FindFile(fpath);

	while(bMore)
	{
 		bMore = hFinder.FindNextFile();
 		fname = hFinder.GetFileName();
 		m_AvailableList.InsertString(nIndex++, fname);
 	}

}
// CScheduleEditor message handlers

void CScheduleEditor::OnBnClickedSchSave()
{
	// TODO: Add your control notification handler code here
	int i = 0, nCount = 0, nLen = 0;
	int ret = SUCCESS;
	CString fname, iName, index;
	CString errMsg = _T("");
	CArray <int,int> ArraySelectd;
	CScheduleDoc *pDoc  = (CScheduleDoc *) GetDocument();
	UpdateData(TRUE);
	
	pDoc->m_manager.SetScheduleID(CASTSTR (m_ScheduleID));
	pDoc->m_manager.SetDescription(CASTSTR(m_Description));

	/* input scenarios from Schedule List */
	nCount = m_SelectedList.GetCount();
	if (nCount) {
		for (i = 0; i < nCount; i++){
			index.Format(_T("%d"), i);
			m_SelectedList.GetText(i, iName);
			pDoc->m_manager.AddScenario(CASTSTR(index), CASTSTR(iName));
		}
	}
	fname.Format(_T("%s.schedule"), m_ScheduleName);
	ret = pDoc->m_manager.SaveSchedule(CASTSTR(fname));

	if (ret == SUCCESS)
		errMsg.Format(_T("%s was successfully saved\nDo you want to keep current values in the editor ?"), fname);
	else
		errMsg.Format(_T("ERROR[%d] %s was failed to be saved!!\nDo you want to keep current values in the editor ?"), ret, fname);

	if (IDNO == AfxMessageBox(errMsg, MB_YESNO))
		ClearContent();

	//Clear Contents
}

void CScheduleEditor::ClearContent()
{
	/* clear member variables */
	int i = 0, nCount = 0;
	CString tmpStr;

	m_ScheduleName = _T("");
	m_ScheduleID = _T("");
	m_Description = _T("");

	nCount = m_SelectedList.GetCount();

	for (i = nCount - 1; i >= 0; i--)
	{
		m_SelectedList.GetText(i, tmpStr);
		m_AvailableList.AddString(tmpStr);
		m_SelectedList.DeleteString(i);
	}
	UpdateData(FALSE);
}

void CScheduleEditor::OnBnClickedBtLeft()
{
	// TODO: Add your control notification handler code here
	int i =0, nSelected = 0, nIndex = 0;
	CString fname; 
	CArray <int, int> SArray;

	nSelected = m_AvailableList.GetSelCount();
	if (nSelected <= 0)
		return;

	SArray.SetSize(nSelected);
	m_AvailableList.GetSelItems(nSelected, SArray.GetData());

	
	/* copy data from availableList to Selected List */
	for(i = 0; i < nSelected; i++)
	{
		nIndex = SArray[i];

		m_AvailableList.GetText(nIndex,fname);
		m_SelectedList.AddString(fname);
	}

	/* delete copied data from AvaliableList */
	for(i = nSelected - 1; i >= 0; i--)
	{
		nIndex = SArray[i];
		m_AvailableList.DeleteString(nIndex);
	}
}

void CScheduleEditor::OnBnClickedBtRight()
{

}
/**
 * When a user click on "UP" button, selected item is swapped with one above it.	
 * @param none
 * @return none
 */
void CScheduleEditor::OnBnClickedBtUp()
{
	// TODO: Add your control notification handler code here
	int nCount, nIndex = 0;

	nCount = m_SelectedList.GetSelCount();
	if (nCount > 1) {
		AfxMessageBox(_T("Only one item can be moved up"));
		return;
	} else if (nCount <= 0)
		return;

	nIndex = m_SelectedList.GetCaretIndex();

	ListSwitch(nIndex, UP);
}

void CScheduleEditor::ListSwitch(int CurIndex, int direction)
{
	int nLast = 0;
	CString tmpStr = _T("");
	
	nLast = m_SelectedList.GetCount() - 1;

	if (direction == UP)
	{
		if (CurIndex == 0)
			return;
		m_SelectedList.GetText(CurIndex - 1, tmpStr);
		m_SelectedList.DeleteString(CurIndex - 1);
		m_SelectedList.InsertString(CurIndex, tmpStr);
		m_SelectedList.SetSel(CurIndex - 1);
	} 
	else if (direction == DOWN) 
	{
		if (CurIndex == (nLast))
			return;

		m_SelectedList.GetText(CurIndex, tmpStr);
		m_SelectedList.DeleteString(CurIndex);
		m_SelectedList.InsertString(CurIndex + 1, tmpStr);
		m_SelectedList.SetSel(CurIndex + 1);
	} 


}
void CScheduleEditor::OnBnClickedBtDown()
{
	// TODO: Add your control notification handler code here
	int nCount, nIndex = 0;

	nCount = m_SelectedList.GetSelCount();
	if (nCount > 1) {
		AfxMessageBox(_T("Only one item can be moved up"));
		return;
	} else if (nCount <= 0)
		return;

	nIndex = m_SelectedList.GetCurSel();

	ListSwitch(nIndex, DOWN);
}

void CScheduleEditor::OnBnClickedBtRightAll()
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here

	int i = 0, nCount = 0;
	CString tmpStr = _T("");

	nCount = m_AvailableList.GetCount();

	for (i = nCount - 1; i >= 0; i--)
	{
		m_AvailableList.GetText(i, tmpStr);
		m_SelectedList.AddString(tmpStr);
		m_AvailableList.DeleteString(i);
	}
}

void CScheduleEditor::OnBnClickedBtLeftAll()
{
	// TODO: Add your control notification handler code here
	int i = 0, nCount = 0;
	CString tmpStr = _T("");

	nCount = m_SelectedList.GetCount();

	for (i = nCount - 1; i >= 0; i--)
	{
		m_SelectedList.GetText(i, tmpStr);
		m_AvailableList.AddString(tmpStr);
		m_SelectedList.DeleteString(i);
	}
}
