// MTXCalc.cpp : Defines the class behaviors for the application.
/******************************************************************************
 Filename		:MTXCalc.cpp
 Author			:Tomas Schier
 Description	:The implementation file for the CWinApp derived CMTXCalc class.

 Date		Notes
 03-Feb-04	First draft

******************************************************************************/

#include "stdafx.h"
#include "MTXCalc.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "MTXCalcDoc.h"
#include "MTXCalcView.h"
#include "MtxSpecsDlg.h"
#include "CalcDlg.h"
#include "LimitSingleInstance.h"
#include "AllPages.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// XPS:The one and only CLimitSingleInstance object
// GUIDGEN was used create this identifier
CLimitSingleInstance g_SingleInstanceObj(TEXT("{C62B5D99-8DC8-4120-9E6A-182323042ADC}"));


/////////////////////////////////////////////////////////////////////////////
// CMTXCalcApp

BEGIN_MESSAGE_MAP(CMTXCalcApp, CWinApp)
	//{{AFX_MSG_MAP(CMTXCalcApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_TOOLS_CALC, OnToolsCalc)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMTXCalcApp construction

CMTXCalcApp::CMTXCalcApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_pDlgCalc = NULL;
}


/////////////////////////////////////////////////////////////////////////////
// The one and only CMTXCalcApp object

CMTXCalcApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMTXCalcApp initialization

BOOL CMTXCalcApp::InitInstance()
{
	
   //XPS: ensure this is the only instance of this application
	if (g_SingleInstanceObj.IsAnotherInstanceRunning())
       return FALSE; 

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_MTXCALTYPE,
		RUNTIME_CLASS(CMTXCalcDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CMTXCalcView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	//XPS: don't open a file by default. This was changed from the MFC default settings
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;


	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CMTXCalcApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CMTXCalcApp message handlers/*

void CMTXCalcApp::OnToolsCalc() 
{
	// TODO: Add your command handler code here
	if (m_pDlgCalc == NULL)
	{
	   m_pDlgCalc = new CAllPages("Calculator", m_pMainWnd, 0);
	   if (m_pDlgCalc->Create(m_pMainWnd) == TRUE)
			m_pDlgCalc->SetActiveWindow();
	}
	else
	{
		m_pDlgCalc->updateMtxList();
		m_pDlgCalc->ShowWindow(SW_SHOW);
		m_pDlgCalc->SetActiveWindow();
	}
}

void CMTXCalcApp::CalcDone()
{
	m_pDlgCalc = NULL;
}

//DEL void CMTXCalcApp::OnFileNew() 
//DEL {	
//DEL //	m_mtx = new xpMatrix(mtxSpecsDlg.m_Rows, mtxSpecsDlg.m_Columns);
//DEL //	return TRUE;
//DEL }
