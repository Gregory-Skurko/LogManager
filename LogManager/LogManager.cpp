// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// LogManager.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "LogManager.h"
#include "MainFrm.h"

#include "LogManagerDoc.h"
#include "LogManagerView.h"

#include <algorithm>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLogManagerApp

BEGIN_MESSAGE_MAP(CLogManagerApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CLogManagerApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CLogManagerApp::OnFileOpen)      
    ON_COMMAND(ID_FIND_BUTTON, &CLogManagerApp::OnFindButton)
    ON_COMMAND(ID_REQUEST_EDIT, &CLogManagerApp::OnRequestEdit)
    ON_COMMAND(ID_REQUESTS_COMBO, &CLogManagerApp::OnRemoveCombo)
    ON_COMMAND(ID_REMOVE_BUTTON, &CLogManagerApp::OnRemoveButton)
    ON_COMMAND(ID_BEFORE_SPIN, &CLogManagerApp::OnBeforeSpin)
    ON_COMMAND(ID_AFTER_SPIN, &CLogManagerApp::OnAfterSpin)
    ON_COMMAND(ID_HIDE_BUTTON, &CLogManagerApp::OnHideButton)
    ON_COMMAND(ID_SHOWALL_BUTTON, &CLogManagerApp::OnShowAllButton)
    ON_COMMAND(ID_FONT_BUTTON, &CLogManagerApp::OnFontButton)
END_MESSAGE_MAP()


// CLogManagerApp construction

CLogManagerApp::CLogManagerApp()     
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("LogManager.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CLogManagerApp object

CLogManagerApp theApp;


// CLogManagerApp initialization

BOOL CLogManagerApp::InitInstance()
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

	CWinAppEx::InitInstance();


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();
    
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CLogManagerDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CLogManagerView));
	if (!pDocTemplate)
		return FALSE;
	pDocTemplate->SetContainerInfo(IDR_CNTR_INPLACE);
	AddDocTemplate(pDocTemplate);


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

    

    auto pFrame = reinterpret_cast<CFrameWnd *>(m_pMainWnd);    
    auto pView = pFrame->GetActiveView();

    m_pRichEdit = reinterpret_cast<CMFCRibbonRichEditCtrl*>(pView);   
    m_pRichEdit->SetTargetDevice(NULL, 1); //for line break
    m_pRichEdit->SetReadOnly(TRUE);

    m_pRichText = new RichText(*m_pRichEdit);
    CFont *pFont = new CFont;
   
    pFont->CreateFont(
            14,                        // nHeight
            0,                         // nWidth
            0,                         // nEscapement
            0,                         // nOrientation
            FW_NORMAL,                 // nWeight
            FALSE,                     // bItalic
            FALSE,                     // bUnderline
            0,                         // cStrikeOut
            ANSI_CHARSET,              // nCharSet
            OUT_DEFAULT_PRECIS,        // nOutPrecision
            CLIP_DEFAULT_PRECIS,       // nClipPrecision
            DEFAULT_QUALITY,           // nQuality
            DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
            _T("Arial"));                 // lpszFacename);
    m_pRichEdit->SetFont(pFont);

    auto pRibbonBar = reinterpret_cast<CMainFrame *>(m_pMainWnd)->GetRibbonBar();
    m_pComboBox = reinterpret_cast<CMFCRibbonComboBox *>(pRibbonBar->GetCategory(1)->FindByID(ID_REQUESTS_COMBO));    
    m_pEdit = reinterpret_cast<CMFCRibbonEdit *>(pRibbonBar->GetCategory(1)->FindByID(ID_REQUEST_EDIT));    
    
    m_isHide = false;
	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();    
	return TRUE;
}

int CLogManagerApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CLogManagerApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
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
public:
//    CString ID_EDIT1;
    
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
    //  ID_EDIT1 = _T("");
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CLogManagerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CLogManagerApp customization load/save methods

void CLogManagerApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CLogManagerApp::LoadCustomState()
{
}

void CLogManagerApp::SaveCustomState()
{
}

// CLogManagerApp message handlers

void CLogManagerApp::OnFileOpen()
{   
    CFileDialog fileDialog(TRUE, NULL, "*.log");

    if (fileDialog.DoModal() == IDOK)
    {        
        m_pRichText->ReadFile(fileDialog.GetPathName().GetString()); 
        m_pEdit->SetEditText("");
        
        m_pComboBox->AddItem("");
        m_pComboBox->SelectItem("");
        m_pComboBox->RemoveAllItems();
        
    }
    
}


void CLogManagerApp::OnFindButton()
{   
    BeginWaitCursor();
    std::string textRequest = m_pEdit->GetEditText(); 

    if (m_isHide)
    {
        m_pRichText->LoadState();
        m_isHide = false;
    }

    m_pRichText->AddHighlight(textRequest);
    
    m_pComboBox->AddItem(textRequest.c_str());
    m_pComboBox->SelectItem(textRequest.c_str());
    EndWaitCursor();
}


void CLogManagerApp::OnRequestEdit()
{
    // TODO: Add your command handler code here
}


void CLogManagerApp::OnRemoveCombo()
{
    // TODO: Add your command handler code here
}


void CLogManagerApp::OnRemoveButton()
{
    // TODO: Add your command handler code here
    BeginWaitCursor();
    std::string request = m_pComboBox->GetEditText().GetString();

    if (request.empty())
    {
        return;
    }
     
    m_pRichText->RemoveHighlight(m_pComboBox->GetEditText().GetString());
    m_pComboBox->DeleteItem(m_pComboBox->GetCurSel());
    EndWaitCursor();
}


void CLogManagerApp::OnBeforeSpin()
{
    // TODO: Add your command handler code here
}


void CLogManagerApp::OnAfterSpin()
{
    // TODO: Add your command handler code here
}


void CLogManagerApp::OnHideButton()
{
    BeginWaitCursor();
    std::string request = m_pComboBox->GetEditText().GetString();
    
    if (request.empty())
    {
        return;
    }

    auto pRibbonBar = reinterpret_cast<CMainFrame *>(m_pMainWnd)->GetRibbonBar();
    auto pSplit1 = reinterpret_cast<CMFCRibbonComboBox *>(pRibbonBar->GetCategory(1)->FindByID(ID_BEFORE_SPIN));
    auto pSplit2 = reinterpret_cast<CMFCRibbonComboBox *>(pRibbonBar->GetCategory(1)->FindByID(ID_AFTER_SPIN));
    
    if (m_isHide)
    {
        m_pRichText->LoadState();
    }
    else
    { 
        m_pRichText->SaveState(); 
        m_isHide = true; 
    }

    m_pRichText->DisplayRows(request, atoi(pSplit1->GetEditText()), atoi(pSplit2->GetEditText()));
    EndWaitCursor();
}


void CLogManagerApp::OnShowAllButton()
{    
    if (m_isHide)
    {
        BeginWaitCursor();
        m_pRichText->LoadState();
        m_isHide = !m_isHide;
        EndWaitCursor();
    }
}

void CLogManagerApp::OnFontButton()
{
    CFontDialog fontDialog;
    if (fontDialog.DoModal() == IDOK)
    {
        LOGFONT lf;
        fontDialog.GetCurrentFont(&lf);

        CFont font;   
        font.CreateFontIndirect(&lf);
        m_pRichEdit->SetFont(&font);
    }      
}
