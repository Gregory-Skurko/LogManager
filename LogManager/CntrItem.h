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

// CntrItem.h : interface of the CLogManagerCntrItem class
//

#pragma once

class CLogManagerDoc;
class CLogManagerView;

class CLogManagerCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CLogManagerCntrItem)

// Constructors
public:
	CLogManagerCntrItem(REOBJECT* preo = NULL, CLogManagerDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer

// Attributes
public:
	CLogManagerDoc* GetDocument()
		{ return reinterpret_cast<CLogManagerDoc*>(CRichEditCntrItem::GetDocument()); }
	CLogManagerView* GetActiveView()
		{ return reinterpret_cast<CLogManagerView*>(CRichEditCntrItem::GetActiveView()); }

// Implementation
public:
	~CLogManagerCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

