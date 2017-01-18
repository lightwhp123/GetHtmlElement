// HtmlElementTest.h : main header file for the HtmlElementTest application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CHtmlElementTestApp:
// See HtmlElementTest.cpp for the implementation of this class
//

class CHtmlElementTestApp : public CWinApp
{
public:
	CHtmlElementTestApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CHtmlElementTestApp theApp;