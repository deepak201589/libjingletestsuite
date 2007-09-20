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
// MainGUI.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MainGUI.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "ReportFrame.h"
#include "MainGUIDoc.h"
#include "ReportDoc.h"
#include "MainGUIView.h"
#include "ReportManager.h"
#include "ScenarioFrame.h"
#include "ScenarioEditor.h"
#include "ScheduleFrame.h"
#include "ScheduleEditor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainGUIApp

BEGIN_MESSAGE_MAP(CMainGUIApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CMainGUIApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_GENERATE_GRAPH, &CMainGUIApp::OnGenerateGraph)
	ON_COMMAND(ID_EDIT_SCENARIO, &CMainGUIApp::OnEditScenario)
	ON_COMMAND(ID_EDIT_SCHEDULE, &CMainGUIApp::OnEditSchedule)
END_MESSAGE_MAP()


// CMainGUIApp construction

CMainGUIApp::CMainGUIApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CMainGUIApp object

CMainGUIApp theApp;


// CMainGUIApp initialization

BOOL CMainGUIApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views


	/* K.M HAN: add a new document for Report manager */
	m_pReportManagerDoc = new CMultiDocTemplate(IDR_REPORT,
		RUNTIME_CLASS(CReportDoc),
		RUNTIME_CLASS(CReportFrame),
		RUNTIME_CLASS(ReportManager));
	if (!m_pReportManagerDoc)
		return FALSE;
	AddDocTemplate(m_pReportManagerDoc);

	/* K.M HAN: add a new document for sceanrio manager */
	m_pScenarioEditorDoc = new CMultiDocTemplate(IDR_SCENARIO,
		RUNTIME_CLASS(CScenarioDoc),
		RUNTIME_CLASS(CScenarioFrame),
		RUNTIME_CLASS(CScenarioEditor));
	if (!m_pScenarioEditorDoc)
		return FALSE;
	AddDocTemplate(m_pScenarioEditorDoc);
	
	/* K.M HAN: add a new document for schedule manager */
	m_pScheduleEditorDoc = new CMultiDocTemplate(IDR_SCHEDULE,
		RUNTIME_CLASS(CScheduleDoc),
		RUNTIME_CLASS(CScheduleFrame),
		RUNTIME_CLASS(CScheduleEditor));
	if (!m_pScheduleEditorDoc)
		return FALSE;
	AddDocTemplate(m_pScheduleEditorDoc);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// call DragAcceptFiles only if there's a suffix
	//  In an MDI app, this should occur immediately after setting m_pMainWnd


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	/* K.M Han: No empty document window on startup */
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew) {
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	}

	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	
	/* Initialize document objects for each main test suite UI componet */
	m_pReport = new CReportDoc();
	m_pScenario = new CScenarioDoc();
	m_pSchedule = new CScheduleDoc();

	return TRUE;
}


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void CMainGUIApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CMainGUIApp message handlers
CFrameWnd* CMainGUIApp::CreateNewWindow(CDocTemplate* pTemplate, CDocument* pDocument)
{
	ASSERT_VALID( pTemplate );
	ASSERT_VALID( pDocument );

	// 1 - Create the new frame window
	// (will in turn create the associated view)
	CFrameWnd* pFrame = pTemplate->CreateNewFrame(pDocument, NULL );

	if( pFrame == NULL )
	{
		// Window creation failed
		TRACE0( "Warning: failed to create new frame.\n" );
		return NULL;
	}

	ASSERT_KINDOF( CFrameWnd, pFrame );

	// 2 - Tell the frame to update itself
	// (and its child windows)

	pTemplate->InitialUpdateFrame( pFrame, pDocument );

	// 3 - Return a pointer to the new frame window object
	return pFrame;
}


void CMainGUIApp::OnGenerateGraph()
{
	// TODO: Add your command handler code here

	TRACE("OnGenerateGraph");
	if (m_pReport == NULL)
		m_pReport = new CReportDoc();

	CreateNewWindow(m_pReportManagerDoc, m_pReport);
}

void CMainGUIApp::OnEditScenario()
{
	// TODO: Add your command handler code here
	TRACE("OnEditScenario");

	if (m_pScenario == NULL)
		m_pScenario = new CScenarioDoc();

	CreateNewWindow(m_pScenarioEditorDoc, m_pScenario);
}

void CMainGUIApp::OnEditSchedule()
{
	// TODO: Add your command handler code here
	TRACE("OnEditScenario");

	if (m_pSchedule == NULL)
		m_pSchedule = new CScheduleDoc();

	CreateNewWindow(m_pScheduleEditorDoc, m_pSchedule);
}
