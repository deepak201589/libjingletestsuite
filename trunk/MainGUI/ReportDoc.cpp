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
// ReportDoc.cpp : implementation file
//

#include "stdafx.h"
#include "MainGUI.h"
#include "ReportDoc.h"
#include "macro.h"
#include "Common/ErrorCode.h"
#include "Common/ResultManager.h"
#include "TestHelper/PlotWrapper.h"
#include <iostream>

// CReportDoc

IMPLEMENT_DYNCREATE(CReportDoc, CDocument)

CReportDoc::CReportDoc()
{
	m_query.m_filename = "";

	m_query.m_xType = "";
	m_query.m_xValue ="";
	m_query.m_xValue2 ="";
	m_query.m_xFormula = "";

	m_query.m_yType = "";
	m_query.m_yValue = "";
	m_query.m_yValue2 = "";
	m_query.m_yFormula = "";

	m_query.m_groupby = "";
	m_query.m_orderby = "";
	m_query.m_rangeFormula = "";

	m_query.m_dataSource->clear();
	m_query.m_dataSource2->clear();
}

BOOL CReportDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CReportDoc::~CReportDoc()
{
	m_query.m_filename = "";

	m_query.m_xType = "";
	m_query.m_xValue ="";
	m_query.m_xValue2 ="";
	m_query.m_xFormula = "";

	m_query.m_yType = "";
	m_query.m_yValue = "";
	m_query.m_yValue2 = "";
	m_query.m_yFormula = "";

	m_query.m_groupby = "";
	m_query.m_orderby = "";
	m_query.m_rangeFormula = "";

	m_query.m_dataSource->clear();
	m_query.m_dataSource2->clear();
}


BEGIN_MESSAGE_MAP(CReportDoc, CDocument)
END_MESSAGE_MAP()


// CReportDoc diagnostics

#ifdef _DEBUG
void CReportDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CReportDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CReportDoc serialization

void CReportDoc::Serialize(CArchive& ar)
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
#endif
// CReportDoc commands


int CReportDoc::GenerateGraph(void)
{
	int ret = SUCCESS;
	string strData = "", strSetUp = "";
	CString xRange = _T(""), yRange = _T("");
	SettingsFile setting;
	ResultManager* resultManager = new ResultManager();
	PlotWrapper* plotWrapper = new PlotWrapper();

	/* 1: product query based on values in member variables */
	if(m_SqlQuery.IsEmpty()) {
		ret = -(FAILURE);
		goto release;
	}
	/* 1-1: setup the file path of both data file and setup file for plotting */
	// 	strData = pConfig->GetConfigValue("DIR_PLOT_CONFIG");
	// 	strSetUp = pConfig->GetConfigValue("DIR_PLOT_CONFIG");
	// 	strData.append("plot.dat");
	// 	strSetUp.append("setting.txt");
	strData = "D:\\plot.dat";
	strSetUp = "D:\\plotSetup.txt";

	ret = resultManager->WriteDataToFile(CASTSTR(m_SqlQuery), strData);
	if (ret != SUCCESS)
		goto release;

	/* 2: Initializes setting structure and Draws a graph by passing setup file and result file */

	/* Initialized setting structure */
	setting.GraphTitle = CASTSTR(m_Title);
	setting.OutputFileName = CASTSTR(m_Fname);
	setting.SettingsFileName = strSetUp;
	setting.DataFileName = strData;
	setting.XLabel = CASTSTR(m_xLabel);
	setting.YLabel = CASTSTR(m_yLabel);
	setting.SrcName1 = CASTSTR(m_y1Title);
	setting.SrcName2 = CASTSTR(m_y2Title);

	/* set range for both x and y */
	xRange.Format(_T("[%s:%s]"), m_xMin, m_xMax);
	setting.XRange = CASTSTR(xRange);
	yRange.Format(_T("[%s:%s]"), m_yMin, m_yMax);
	setting.YRange = CASTSTR(yRange);
	setting.nSrc = m_nYValues;

	/* Default values */
	ret = plotWrapper->SetDefaultValue(&setting);
	if (ret != SUCCESS)
		return ret;

	ret = plotWrapper->CreateSettingsFile(&setting);

	/* FIXME: I should be able to specify the graph name */
	ret = plotWrapper->Plot(strSetUp, strData);
	if (ret != SUCCESS) {
		ret = -(FAILURE);
		goto release;
	}

release:

	if (resultManager)
		delete resultManager;

	if (plotWrapper)
		delete plotWrapper;

	return ret;
}

int CReportDoc::MakeQuery(CString *query)
{
	int i = 0, ret = SUCCESS;
	CString tmpStr = _T("");
	CString tempQuery; 
	CString subQuery1, subQuery2;
	BOOL bCmpProtocl = FALSE;
	list <CString>::iterator iter;
	
	/* allocate large buffer for the query */
	tempQuery.Preallocate(QUERY_LENGTH);

	/* Step 1: if query is to retrieve data for two protocol, initialize sub query buffer */
	if (m_nYValues == COMPARE_TWO_PROTOCOL) 
	{
		subQuery1.Preallocate(SUB_QUERY_LENGTH);
		subQuery2.Preallocate(SUB_QUERY_LENGTH);
		subQuery1 = _T("SELECT ");
		subQuery2 = _T("SELECT ");
		bCmpProtocl = TRUE;
	} 
	
	/* Step 2: Build main query */
	tempQuery = _T("SELECT ");

	/* Step 3. check if x value is valid. If so, added it query. Return INVALID_ARGUMENT otherwise */
	if (!m_query.m_xValue.IsEmpty())
	{
		if (bCmpProtocl) {
			tempQuery.Format(_T("%s ProtocolA.%s"), tempQuery, m_query.m_xValue);
			subQuery1.Format(_T("%s %s"), subQuery1, m_query.m_xValue);
			subQuery2.Format(_T("%s %s"), subQuery2, m_query.m_xValue);
		} else {
			tempQuery.Format(_T("%s %s"), tempQuery, m_query.m_xValue);
		}

		m_xLabel = m_query.m_xValue;
	} 
	else if (!m_query.m_xValue2.IsEmpty() && !m_query.m_xFormula.IsEmpty()) 
	{
		if (bCmpProtocl) {
			tempQuery.Format(_T("%s ProtocolA.%s"), tempQuery, m_query.m_yValue2);
			subQuery1.Format(_T("%s (%s) as %s"), subQuery1, m_query.m_xFormula, m_query.m_xValue2);
			subQuery2.Format(_T("%s (%s) as %s"), subQuery2, m_query.m_xFormula, m_query.m_xValue2);
		}else {
			tempQuery.Format(_T("%s (%s) as %s"), tempQuery, m_query.m_xFormula, m_query.m_xValue2);
		}
		m_xLabel = m_query.m_xValue2;
	}
	else 
	{
		return (-INVALID_ARGUMENT);
	}
	
	/* Step 4. check if query is for two y values*/
	if (bCmpProtocl) 
	{
		/* CASE 1. construct querys for comparing two protocols*/

		/* Step 4A-1: check if x value is valid and added to query */
		if (!m_query.m_yValue.IsEmpty())
		{
			tempQuery.Format(_T("%s, ProtocolA.%s, ProtocolB.%s"), tempQuery, m_query.m_yValue, m_query.m_yValue);
			subQuery1.Format(_T("%s, %s"), subQuery1, m_query.m_yValue);
			subQuery2.Format(_T("%s, %s"), subQuery2, m_query.m_yValue);
			m_yLabel = m_query.m_yValue;
		} 
		else if (!m_query.m_yValue2.IsEmpty() && !m_query.m_yFormula.IsEmpty()) 
		{
			tempQuery.Format(_T("%s, ProtocolA.%s, Protoco1B.%s"), tempQuery, m_query.m_yValue2, m_query.m_yValue2);
			subQuery1.Format(_T("%s, (%s) as %s"), subQuery1, m_query.m_yFormula, m_query.m_yValue2);
			subQuery2.Format(_T("%s, (%s) as %s"), subQuery2, m_query.m_yFormula, m_query.m_yValue2);
			m_yLabel = m_query.m_yValue2;
		}
		else 
		{
			return (-INVALID_ARGUMENT);
		}

		/* Step 4A-2: add "from" clause to queries */
		tempQuery.Format(_T("%s from ("), tempQuery);
		subQuery1.Format(_T("%s from resultmaster"), subQuery1);
		subQuery2.Format(_T("%s from resultmaster"), subQuery2);

		/* Step 4A-3: add data range to sub query 1*/
		if (m_query.m_dataSource->empty() == TRUE) 
		{
			return (-INVALID_ARGUMENT);
		} 
		else 
		{
			iter = m_query.m_dataSource->begin();
			for( i = 0; iter != m_query.m_dataSource->end(); iter++, i++)
			{
				tmpStr.Format(_T("%s"), *iter);
				if (i == 0)
					subQuery1.Format(_T("%s WHERE ScenarioID = %s"), subQuery1, tmpStr);
				else 
					subQuery1.Format(_T("%s OR scenarioID = %s"), subQuery1, tmpStr);
			}
		}
	
		/* Step 4A-4: add data range to sub query 2*/
		if (m_query.m_dataSource2->empty() == TRUE) 
		{
			return (-INVALID_ARGUMENT);
		} 
		else 
		{
			iter = m_query.m_dataSource2->begin();
			for( i = 0; iter != m_query.m_dataSource2->end(); iter++, i++)
			{
				tmpStr.Format(_T("%s"), *iter);
				if (i == 0)
					subQuery2.Format(_T("%s WHERE ScenarioID = %s"), subQuery2, tmpStr);
				else 
					subQuery2.Format(_T("%s OR scenarioID = %s"), subQuery2, tmpStr);
			}
		}
	
		/* Step 4A-5: integrate sub queries into a main query*/
		tempQuery.Format(_T("%s (%s) ProtocolA, (%s) ProtocolB) WHERE ProtocolA.%s = ProtocolB.%s"), 
					tempQuery, subQuery1, subQuery2, m_xLabel, m_xLabel);

	} else { 
		/* CASE2: construct query for one protocol */
		/* Step 4B-1: add y value to the query */
		if (!m_query.m_xValue.IsEmpty())
		{
			tempQuery.Format(_T("%s, %s"), tempQuery, m_query.m_yValue);
			m_yLabel = m_query.m_yValue;
		} 
		else if (!m_query.m_xValue2.IsEmpty() && !m_query.m_xFormula.IsEmpty()) 
		{
			tempQuery.Format(_T("%s, (%s) as %s"), tempQuery, m_query.m_yFormula, m_query.m_yValue2);
			m_yLabel = m_query.m_yValue2;
		}
		else 
		{
			return (-INVALID_ARGUMENT);
		}
		/* Step 4B-2: FIXME: add table name (This should be got from config file) */
		tempQuery.Format(_T("%s from resultmaster"), tempQuery);

		/* Step 4B-3: check if data source range is valid. If so, added it query. Return INVALID_ARGUMENT otherwise */
		if (m_query.m_dataSource->empty() == TRUE) 
		{
			return (-INVALID_ARGUMENT);
		} 
		else 
		{
			m_query.m_dataSource->sort();
			iter = m_query.m_dataSource->begin();
			for( i = 0; iter != m_query.m_dataSource->end(); iter++, i++)
			{
				tmpStr.Format(_T("%s"), *iter);
				if (i == 0)
					tempQuery.Format(_T("%s WHERE ScenarioID = %s"), tempQuery, tmpStr);
				else 
					tempQuery.Format(_T("%s OR scenarioID = %s"), tempQuery, tmpStr);
			}
		}

	}
	
	/* Step 5: put data range formula if exists */
	if (!m_query.m_rangeFormula.IsEmpty())
		tempQuery.Format(_T("%s and (%s)"), tempQuery, m_query.m_rangeFormula);

	/* 5. put group by condition if exists */
	if (!m_query.m_groupby.IsEmpty())
		tempQuery.Format(_T("%s GROUP BY %s"), tempQuery, m_query.m_groupby);

	/* 6. put order by condition if exists */
	if (!m_query.m_orderby.IsEmpty())
		tempQuery.Format(_T("%s ORDER BY %s"), tempQuery, m_query.m_orderby);
	
	*query = tempQuery;
	return ret;
}
