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

// LogManager.h : main header file for the LogManager application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "RichText.h"

// CLogManagerApp:
// See LogManager.cpp for the implementation of this class
//

class CLogManagerApp : public CWinAppEx
{
    bool m_isHide;
    RichText* m_pRichText;
    CMFCRibbonRichEditCtrl* m_pRichEdit;
    CMFCRibbonComboBox* m_pComboBox;
    CMFCRibbonEdit* m_pEdit;
    
public:
	CLogManagerApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
    afx_msg void OnFileOpen();
	DECLARE_MESSAGE_MAP()
    afx_msg void OnFindButton();
    afx_msg void OnRequestEdit();
    afx_msg void OnRemoveCombo();
    afx_msg void OnRemoveButton();
    afx_msg void OnBeforeSpin();
    afx_msg void OnAfterSpin();
    afx_msg void OnHideButton();
    afx_msg void OnShowAllButton();
    afx_msg void OnFontButton();
};

extern CLogManagerApp theApp;
