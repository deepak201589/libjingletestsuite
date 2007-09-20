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
// ScenarioEditor.cpp : implementation file
//

#include "stdafx.h"
#include "macro.h"
#include "MainGUI.h"
#include "ScenarioEditor.h"
#include "ScenarioDoc.h"
#include "../Common/Scenario.h"
#include "../Common/ErrorCode.h"
#include "../Common/ConfigManager.h"

// CScenarioEditor


IMPLEMENT_DYNCREATE(CScenarioEditor, CFormView)

CScenarioEditor::CScenarioEditor()
	: CFormView(CScenarioEditor::IDD)
	, m_ScenarioID(_T(""))
	, m_ScenarioName(_T(""))
	, m_SenderLoginID(_T(""))
	, m_ReceiverLoginID(_T(""))
	, m_SenderPasswd(_T(""))
	, m_FilePath(_T(""))
	, m_Description(_T(""))
	, m_bUseNISTnet(FALSE)
	, m_PacketDelay(_T(""))
	, m_PacketDup(_T(""))
	, m_PacketLoss(_T(""))
	, m_BandWidth(_T(""))
{

}

CScenarioEditor::~CScenarioEditor()
{
}

void CScenarioEditor::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SID, m_ScenarioID);
	DDX_Text(pDX, IDC_SNAME, m_ScenarioName);
	DDX_Text(pDX, IDC_SLOGIN, m_SenderLoginID);
	DDX_Text(pDX, IDC_RLOGIN, m_ReceiverLoginID);
	DDX_Text(pDX, IDC_SPASSWD, m_SenderPasswd);
	DDX_Text(pDX, IDC_SFPATH, m_FilePath);
	DDX_Text(pDX, IDC_DESCRIPTION, m_Description);
	DDX_Check(pDX, IDC_USE_NISTNET, m_bUseNISTnet);
	DDX_Text(pDX, IDC_PDELAY, m_PacketDelay);
	DDX_Text(pDX, IDC_PDUP, m_PacketDup);
	DDX_Text(pDX, IDC_PLOSS, m_PacketLoss);
	DDV_MaxChars(pDX, m_PacketLoss, 5);
	DDX_Text(pDX, IDC_BANDWIDTH, m_BandWidth);
	DDV_MaxChars(pDX, m_BandWidth, 10);
	DDV_MaxChars(pDX, m_PacketDup, 20);
	DDV_MaxChars(pDX, m_PacketDelay, 10);
	DDV_MaxChars(pDX, m_Description, 255);
	DDV_MaxChars(pDX, m_FilePath, 255);
	DDV_MaxChars(pDX, m_SenderPasswd, 20);
	DDV_MaxChars(pDX, m_ReceiverLoginID, 20);
	DDV_MaxChars(pDX, m_SenderLoginID, 20);
	DDV_MaxChars(pDX, m_ScenarioName, 100);
	DDV_MaxChars(pDX, m_ScenarioID, 30);
}

BEGIN_MESSAGE_MAP(CScenarioEditor, CFormView)
	ON_BN_CLICKED(ID_SAVE, &CScenarioEditor::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BT_SPATH, &CScenarioEditor::OnBnClickedBtSpath)
END_MESSAGE_MAP()


// CScenarioEditor diagnostics

#ifdef _DEBUG
void CScenarioEditor::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CScenarioEditor::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CScenarioEditor message handlers

void CScenarioEditor::OnBnClickedSave()
{
	/* K.M HAN: get object pointer of CScenarioDoc */
	CString FilePath = _T(""), errMsg(_T(""));
	CScenarioDoc* pDoc = (CScenarioDoc *)GetDocument();
	ConfigManager *pConfig = ConfigManager::Instance();
	string defaultPath ="";
	int ret = SUCCESS;
	
	/* Declaration to use ATL macro */
	USES_CONVERSION; 
	
	/* 1. Copy data from form view to document object */
	UpdateData(TRUE);
	TransferData(pDoc->m_manager.GetScenario());

	/* 2. Save input data as a file */
	if (!m_FilePath.IsEmpty()) {
		FilePath.Format(_T("%s%s"), m_FilePath, m_ScenarioName);
	} else { /* use default scenario dir path */
	
		defaultPath = pConfig->GetConfigValue("DIR_SCENARIOS");
		m_FilePath.Format(_T("%s"), A2CW(defaultPath.c_str()));
		FilePath.Format(_T("%s%s"), m_FilePath, m_ScenarioName);
	}

	ret = pDoc->SaveAsFile(FilePath);

	/* 3. error message box shows the result  */

	if (ret == FAILURE)
		errMsg.Format(_T("ERROR[%d] %s was failed to be saved!!\nDo you want to keep current values in the editor ?"), ret, m_ScenarioName);
	else
		errMsg.Format(_T("%s was successfully saved\nDo you want to keep current values in the editor ?"), m_ScenarioName);

	if (IDNO == AfxMessageBox(errMsg, MB_YESNO))
		ClearContent();
}

void CScenarioEditor::ClearContent()
{
	/* clear member variables */
	m_FilePath = _T("");
	m_ScenarioID = _T("");
	m_ScenarioName = _T("");
	m_SenderLoginID = _T("");
	m_ReceiverLoginID = _T("");
	m_SenderPasswd = _T("");
	m_Description = _T("");
	m_bUseNISTnet = FALSE;
	m_PacketDelay = _T("");
	m_PacketDup = _T("");
	m_PacketLoss = _T("");
	m_BandWidth = _T("");
	UpdateData(FALSE);
}


int CScenarioEditor::TransferData(Scenario *pScenario) {
	
	int ret = SUCCESS;
	int sid = 0;
	double PDelay = 0, PDup = 0, BandWidth = 0, PLoss = 0;
	NetworkParameters *pNetParams = NULL;
	
	if (!pScenario)
		return -(NULL_POINTER);

	/* input data */
	pScenario->SetScenarioId(ATOI(m_ScenarioID));
	pScenario->SetSenderFilePath(CASTSTR(m_FilePath));
	pScenario->SetSenderLoginId(CASTSTR(m_SenderLoginID));
	pScenario->SetSenderPassword(CASTSTR(m_SenderPasswd));
	pScenario->SetReceiverLoginId(CASTSTR(m_ReceiverLoginID));
	pScenario->SetDescription(CASTSTR(m_Description));
	pScenario->SetScenarioName(CASTSTR(m_ScenarioName));
	pScenario->SetNISTnetOption(BTOb(m_bUseNISTnet));

	/* check if m_bUseNISTnet is TRUE. If so allocate memory for network parameter */
	if(m_bUseNISTnet)
	{
		pNetParams = (NetworkParameters *)malloc(sizeof(NetworkParameters));
		/* parse network parameter */
		pNetParams->PacketDelay = ATOF(m_PacketDelay);
		pNetParams->PacketDuplicates = ATOF(m_PacketDup);
		pNetParams->PacketLoss = ATOF(m_PacketLoss);
		pNetParams->Bandwidth = ATOF(m_BandWidth);

		/* assign parameter to scenario object */
		pScenario->SetNetworkParameters(pNetParams);
	}
	return ret;	
}

void CScenarioEditor::OnBnClickedBtSpath()
{
	// TODO: Add your control notification handler code here
	CFileDialog fDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Scenario files(*.schedule)|*.scenario|"));
	CString fullPath, fName, fPath; 
	ConfigManager *pConfig;
	string defaultPath;

	//set default path
	USES_CONVERSION; 

	pConfig = ConfigManager::Instance();
	defaultPath = ConfigManager::Instance()->GetConfigValue("DIR_SCENARIOS");

	fDlg.m_ofn.lpstrInitialDir = A2CW(defaultPath.c_str());
	
	if (fDlg.DoModal() == IDOK)
	{
		fullPath = fDlg.GetPathName();
		if (fullPath.IsEmpty())
			return;		
		SplitFilePath(fullPath, &fName,&fPath);
		m_FilePath = fPath;
		m_ScenarioName = fName;
		UpdateData(FALSE);
	}
}

void CScenarioEditor::SplitFilePath(CString OriginalPath, CString *fname, CString *fpath)
{
	CString token, last;
	int nSize, Pos = 0;
	
	nSize = OriginalPath.GetLength();

	token = OriginalPath.Tokenize(_T("\\"), Pos);
	while (1)
	{
		token = OriginalPath.Tokenize(_T("\\"), Pos);
		if (token.IsEmpty())
			break;
		last = token;
	}

	/* separate filename from file path */
	*fpath = OriginalPath.Left(nSize - last.GetLength());
	*fname = last.Left(last.GetLength() - strlen(SCENARIO_EXTENSION));
}