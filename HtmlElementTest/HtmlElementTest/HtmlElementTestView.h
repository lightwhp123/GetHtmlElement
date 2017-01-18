// HtmlElementTestView.h : interface of the CHtmlElementTestView class
//


#pragma once

#include <atlbase.h>
#include <mshtml.h> 
#include <ExDisp.h>


class CHtmlElementTestView : public CHtmlView
{
protected: // create from serialization only
	CHtmlElementTestView();
	DECLARE_DYNCREATE(CHtmlElementTestView)

// Attributes
public:
	CHtmlElementTestDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CHtmlElementTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	CComPtr <IHTMLDocument2> IframeElementProcess(CComQIPtr<IHTMLIFrameElement> spIframe);

	bool IsIframe(CComPtr<IHTMLElement> spElement);
};

#ifndef _DEBUG  // debug version in HtmlElementTestView.cpp
inline CHtmlElementTestDoc* CHtmlElementTestView::GetDocument() const
   { return reinterpret_cast<CHtmlElementTestDoc*>(m_pDocument); }
#endif

