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

// LogManagerView.cpp : implementation of the CLogManagerView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "LogManager.h"
#endif

#include "LogManagerDoc.h"
#include "CntrItem.h"
#include "resource.h"
#include "LogManagerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLogManagerView

IMPLEMENT_DYNCREATE(CLogManagerView, CRichEditView)

BEGIN_MESSAGE_MAP(CLogManagerView, CRichEditView)
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CLogManagerView construction/destruction

CLogManagerView::CLogManagerView()
{
	// TODO: add construction code here
        
}

CLogManagerView::~CLogManagerView()
{
}

BOOL CLogManagerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

void CLogManagerView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();


	// Set the printing margins (720 twips = 1/2 inch)
	SetMargins(CRect(720, 720, 720, 720));
}

void CLogManagerView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
   CRichEditView::OnDestroy();
}


void CLogManagerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CLogManagerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CLogManagerView diagnostics

#ifdef _DEBUG
void CLogManagerView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CLogManagerView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CLogManagerDoc* CLogManagerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLogManagerDoc)));
	return (CLogManagerDoc*)m_pDocument;
}
#endif //_DEBUG


// CLogManagerView message handlers
