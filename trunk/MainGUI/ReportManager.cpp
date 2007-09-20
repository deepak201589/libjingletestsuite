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
// ReportManager.cpp : implementation file
//

#include "stdafx.h"
#include "MainGUI.h"
#include "ReportManager.h"
#include "Common/ResultManager.h"
#include "GraphDlg.h"

// ReportManager

IMPLEMENT_DYNCREATE(ReportManager, CFormView)

ReportManager::ReportManager()
	: CFormView(ReportManager::IDD)
	, m_filename(_T(""))

	, m_xType(_T(""))
	, m_xValue(_T(""))
	, m_xValue2(_T(""))
	, m_xFormula(_T(""))
	, m_xMin(_T(""))
	, m_xMax(_T(""))

	, m_yName(_T(""))
	, m_yName2(_T(""))
	, m_yType(_T(""))
	, m_yValue(_T(""))
	, m_yValue2(_T(""))
	, m_yFormula(_T(""))
	, m_yMax(_T(""))
	, m_yMin(_T(""))

	, m_orderby(_T(""))
	, m_groupby(_T(""))
	, m_rangeFormula(_T(""))
	, m_query(_T(""))
	, m_Title(_T(""))
{
}

ReportManager::~ReportManager()
{
}

void ReportManager::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FILE_NAME, m_filename);
	DDX_Text(pDX, IDC_TITLE, m_Title);


	DDX_Control(pDX, IDC_RANGE, m_rangeList);
	DDX_Control(pDX, IDC_RANGE2, m_rangeList2);

	DDX_Text(pDX, IDC_ORDERBY, m_orderby);
	DDX_Text(pDX, IDC_GROUPBY, m_groupby);
	DDX_Text(pDX, IDC_RANGE_FORMULA, m_rangeFormula);
	DDV_MaxChars(pDX, m_rangeFormula, 255);
	DDX_Text(pDX, IDC_Query, m_query);
	DDX_Control(pDX, ID_PREVIEW, m_btPreview);
	DDX_Control(pDX, ID_GENERATE, m_btGenerate);
	DDX_Text(pDX, IDC_Y2_NAME, m_yName);
	DDX_CBString(pDX, IDC_Y2_TYPE, m_yType);
	DDX_CBString(pDX, IDC_Y2_VALUE, m_yValue);
	DDX_Text(pDX, IDC_Y2_VALUE2, m_yValue2);
	DDX_Text(pDX, IDC_Y2_FORMULA, m_yFormula);
	DDX_Text(pDX, IDC_Y2_MAX, m_yMax);
	DDX_Text(pDX, IDC_Y2_MIN, m_yMin);
	DDX_Text(pDX, IDC_Y3_NAME, m_yName2);
	DDX_CBString(pDX, IDC_X2_TYPE, m_xType);
	DDX_CBString(pDX, IDC_X2_VALUE, m_xValue);
	DDX_Text(pDX, IDC_X2_VALUE2, m_xValue2);
	DDX_Text(pDX, IDC_X2_FORMULA, m_xFormula);
	DDX_Text(pDX, IDC_X2_MIN, m_xMin);
	DDX_Text(pDX, IDC_X2_MAX, m_xMax);
	DDV_MaxChars(pDX, m_yMax, 100);
	DDV_MaxChars(pDX, m_xMax, 255);
}

BEGIN_MESSAGE_MAP(ReportManager, CFormView)
	ON_BN_CLICKED(ID_GENERATE, &ReportManager::OnBnClickedGenerate)
	ON_BN_CLICKED(ID_PREVIEW, &ReportManager::OnBnClickedPreview)
END_MESSAGE_MAP()


// ReportManager diagnostics

#ifdef _DEBUG
void ReportManager::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void ReportManager::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void ReportManager::OnInitialUpdate()
{
	CWnd *button;
	CWnd *pQuery, *pStatic;
	int i = 0, j = 0, nIndex = 0, nColumn = 0;
	CString itemName; // temporary
	CReportDoc* pDoc = (CReportDoc *) GetDocument();
	DBWrapper *pConn = NULL;
	list <string *> *pResult = NULL;
	list <string *>::iterator iter;
	string DefaultQuery = "SELECT ScenarioID, ScheduleID, Protocol ,EndTime from resultmaster WHERE ScheduleID > 10 ORDER BY ScenarioID";
	string *row = NULL;

	m_filename = pDoc->m_query.m_filename;
	m_xType = pDoc->m_query.m_xType;
	m_xValue = pDoc->m_query.m_xValue;
	m_xValue2 = pDoc->m_query.m_xValue2;
	m_xFormula = pDoc->m_query.m_xFormula;

	m_yType = pDoc->m_query.m_yType;
	m_yValue = pDoc->m_query.m_yValue;
	m_yValue2 = pDoc->m_query.m_yValue2;
	m_yFormula = pDoc->m_query.m_yFormula;

	m_rangeFormula = pDoc->m_query.m_rangeFormula;
	m_groupby = pDoc->m_query.m_groupby;
	m_orderby = pDoc->m_query.m_orderby;

	UpdateData(FALSE);

	/* 1: Initialize two list controls */
	m_rangeList.InsertColumn(0, _T("Scenario ID"), LVCFMT_LEFT, 120, -1);
	m_rangeList.InsertColumn(1, _T("Protocol"), LVCFMT_LEFT, 100, -1);
	m_rangeList.InsertColumn(2, _T("Description"), LVCFMT_LEFT, 300, -1);
	m_rangeList.InsertColumn(3, _T("Execution Date"), LVCFMT_LEFT, 170, -1);

	m_rangeList2.InsertColumn(0, _T("Scenario ID"), LVCFMT_LEFT, 120, -1);
	m_rangeList2.InsertColumn(1, _T("Protocol"), LVCFMT_LEFT, 100, -1);
	m_rangeList2.InsertColumn(2, _T("Description"), LVCFMT_LEFT, 300, -1);
	m_rangeList2.InsertColumn(3, _T("Execution Date"), LVCFMT_LEFT, 170, -1);

	/* Macro definition to use character transformation function */
	USES_CONVERSION; 

	/* 2: retrieve a list of available test result from DB */
	pConn = new DBWrapper();

	pResult = pConn->ReadRepository((char *)DefaultQuery.c_str(), &nColumn);

	if(pResult) 
	{
		for(j = 0, iter = pResult->begin(); iter != pResult->end(); iter++)
		{	
			row = *iter;
			for (i = 0 ; i < nColumn; i++)
			{
				itemName = _T("");
				itemName.Format(_T("%s"), A2CW(row[i].c_str()));
				if (i == 0) {
					nIndex = m_rangeList.InsertItem(LVIF_TEXT, j++, (LPCTSTR)itemName, 0, 0, 0,NULL);
					nIndex = m_rangeList2.InsertItem(LVIF_TEXT, j++, (LPCTSTR)itemName, 0, 0, 0,NULL);
				} else {
					m_rangeList.SetItem(nIndex, i, LVIF_TEXT, (LPCTSTR)itemName, 0, 0, 0, NULL, 0);
					m_rangeList2.SetItem(nIndex, i, LVIF_TEXT, (LPCTSTR)itemName, 0, 0, 0, NULL, 0); 
				}
			}
			delete[] row;
		}
	}
	/* 3: make "generate" button invisible. */
	button = GetDlgItem(ID_GENERATE);
	button->ShowWindow(FALSE);

	pQuery = GetDlgItem(IDC_Query);
	pQuery->ShowWindow(FALSE);

	pStatic = GetDlgItem(IDC_CHANGE_QUERY);
	pStatic->ShowWindow(FALSE);
	
	if(pConn)
		delete pConn;
	if(pResult)
		delete pResult;

}

// ReportManager message handlers

void ReportManager::OnBnClickedGenerate()
{
	// TODO: Add your control notification handler code here
	int ret =  SUCCESS;
	CReportDoc* pDoc = (CReportDoc *) GetDocument();
	CString strMsg = _T("");
	CGraphDlg hGraph;
	bool bReady = false;

	UpdateData(TRUE);
	pDoc->m_SqlQuery = m_query;
	pDoc->m_Fname.Format(_T("%s.png"), m_filename);
 	pDoc->m_Title = m_Title;
 	pDoc->m_y1Title = m_yName;
 	pDoc->m_y2Title = m_yName2;
	pDoc->m_xMax = m_xMax;
	pDoc->m_xMin = m_xMin;
	pDoc->m_yMin = m_yMin;
	pDoc->m_yMax = m_yMax;

	/* Step 1: invoke GenerateGraph method */
	ret = pDoc->GenerateGraph();
	if (ret != SUCCESS)
		strMsg.Format(_T("Error [%d]: Generating graph is failed."), ret);
	else { 
		strMsg.Format(_T("Generating graph (%s.png) succeed."), m_filename);
		bReady = true;
	}
	AfxMessageBox(strMsg, MB_OK);

	if (bReady) {
		hGraph.m_fPath.Format(_T("%s.png"), m_filename);
		hGraph.m_fName = m_filename;
		hGraph.DoModal();
	}
}

void ReportManager::OnBnClickedPreview()
{

	// TODO: Add your control notification handler code here
	POSITION pos;
	CWnd *pPreview, *pGenerate, *pQuery, *pStatic;
	CString ItemText = _T("");
	CString strQuery = _T("");
	int nItem = 0, nSelected = 0, i = 1;
	int ret = SUCCESS;
	CReportDoc* pDoc = (CReportDoc *)GetDocument();


	/* 1. Copy data from form view to document object */
	UpdateData(TRUE);
	pDoc->m_query.m_filename = m_filename;

	pDoc->m_query.m_xType = m_xType;
	pDoc->m_query.m_xValue = m_xValue;
	pDoc->m_query.m_xValue2 = m_xValue2;
	pDoc->m_query.m_xFormula = m_xFormula;

	pDoc->m_query.m_yType = m_yType;
	pDoc->m_query.m_yValue = m_yValue;
	pDoc->m_query.m_yValue2 = m_yValue2;
	pDoc->m_query.m_yFormula = m_yFormula;

	pDoc->m_query.m_rangeFormula = m_rangeFormula;
	pDoc->m_query.m_groupby = m_groupby;
	pDoc->m_query.m_orderby = m_orderby;


	if (!m_yName2.IsEmpty())
		pDoc->m_nYValues = COMPARE_TWO_PROTOCOL; // indicate that second x value is set
	else 
		pDoc->m_nYValues = SINGLE_PROTOCOL;

	/* 1-1: retrieve selected items from the list control 1 */
	nSelected = m_rangeList.GetSelectedCount();
	pos = m_rangeList.GetFirstSelectedItemPosition();

	if (pos == NULL)
		TRACE0("No items were selected!\n");
	else
	{
		while (pos)
		{
			nItem = m_rangeList.GetNextSelectedItem(pos);
			ItemText = m_rangeList.GetItemText(nItem, 0);
			TRACE1("Item %d was selected!\n", nItem);
			pDoc->m_query.m_dataSource->push_back(ItemText);
		}
	}

	/* 1-2: retrieve selected items from the list control 2 */
	nSelected = m_rangeList2.GetSelectedCount();
	pos = m_rangeList2.GetFirstSelectedItemPosition();

	if (pos == NULL)
		TRACE0("No items were selected!\n");
	else
	{
		while (pos)
		{
			nItem = m_rangeList2.GetNextSelectedItem(pos);
			ItemText = m_rangeList2.GetItemText(nItem, 0);
			TRACE1("Item %d was selected!\n", nItem);
			pDoc->m_query.m_dataSource2->push_back(ItemText);
		}
	}

	/* 2. generate a query and update a to-be query edit box */
	ret = pDoc->MakeQuery(&strQuery);
	if (ret < 0) {
		TRACE0("Fail to produce query \n");
		/* TODO: make pop-up error message appear */
	}
	m_query = strQuery;
	UpdateData(FALSE);

	/* 3. make "preview button" invisible and "generate" button visible */
	pPreview = GetDlgItem(ID_PREVIEW);
	pGenerate = GetDlgItem(ID_GENERATE);
	pQuery = GetDlgItem(IDC_Query);
	pStatic = GetDlgItem(IDC_CHANGE_QUERY);

	pPreview->ShowWindow(FALSE);
	pGenerate->ShowWindow(TRUE);
	pQuery->ShowWindow(TRUE);
	pStatic->ShowWindow(TRUE);

}

