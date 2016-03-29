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

// CntrItem.cpp : implementation of the CLogManagerCntrItem class
//

#include "stdafx.h"
#include "LogManager.h"

#include "LogManagerDoc.h"
#include "LogManagerView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLogManagerCntrItem implementation

IMPLEMENT_SERIAL(CLogManagerCntrItem, CRichEditCntrItem, 0)

CLogManagerCntrItem::CLogManagerCntrItem(REOBJECT* preo, CLogManagerDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
}

CLogManagerCntrItem::~CLogManagerCntrItem()
{
	// TODO: add cleanup code here
}


// CLogManagerCntrItem diagnostics

#ifdef _DEBUG
void CLogManagerCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CLogManagerCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

