// HtmlElementTestView.cpp : implementation of the CHtmlElementTestView class
//

#include "stdafx.h"
#include "HtmlElementTest.h"

#include "HtmlElementTestDoc.h"
#include "HtmlElementTestView.h"
#include "MainFrm.h"

#include <string>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHtmlElementTestView

IMPLEMENT_DYNCREATE(CHtmlElementTestView, CHtmlView)

BEGIN_MESSAGE_MAP(CHtmlElementTestView, CHtmlView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CHtmlView::OnFilePrint)
	//	ON_WM_MOUSEMOVE()
	//	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CHtmlElementTestView construction/destruction

CHtmlElementTestView::CHtmlElementTestView()
{
	// TODO: add construction code here

}

CHtmlElementTestView::~CHtmlElementTestView()
{
}

BOOL CHtmlElementTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

void CHtmlElementTestView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	Navigate2(_T("https://mybank.icbc.com.cn/icbc/newperbank/perbank3/frame/frame_index.jsp"),NULL,NULL);
}


// CHtmlElementTestView printing



// CHtmlElementTestView diagnostics

#ifdef _DEBUG
void CHtmlElementTestView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CHtmlElementTestView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CHtmlElementTestDoc* CHtmlElementTestView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHtmlElementTestDoc)));
	return (CHtmlElementTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CHtmlElementTestView message handlers
CComPtr <IHTMLDocument2> CHtmlElementTestView::IframeElementProcess(CComQIPtr<IHTMLIFrameElement> spIframe)
{
	if (spIframe == NULL)
	{
		return NULL;
	}
	CComPtr<IHTMLDocument2> spDoc2 = NULL;

	// spDoc2 = HtmlIframeToHtmlDocument2( spElement );
	CComQIPtr<IHTMLFrameBase2> spFrameBase2 = spIframe;
	if (spFrameBase2 == NULL)
	{
		return NULL;
	}
	CComPtr<IHTMLWindow2> spIframeWindow2;
	HRESULT hr = spFrameBase2->get_contentWindow( &spIframeWindow2 );
	if (spIframeWindow2 == NULL )
	{
		return NULL;
	}
	spIframeWindow2->get_document( &spDoc2 );
	if (spDoc2 == NULL)
	{
		CComPtr<IDispatch> spDisp = NULL;
		CComQIPtr<IServiceProvider> spServiceProvider = spIframeWindow2;
		if (spServiceProvider == NULL)
		{
			return NULL;
		}

		CComPtr<IWebBrowser2> spWebBrws;
		hr = spServiceProvider->QueryService(IID_IWebBrowserApp, IID_IWebBrowser2, (void**)&spWebBrws);
		if (hr != S_OK)
		{
			return NULL;
		}
		spDisp = NULL;
		spWebBrws->get_Document( &spDisp );
		spDoc2 = spDisp;
	}

	return spDoc2;
}

bool CHtmlElementTestView::IsIframe(CComPtr<IHTMLElement> spElement)
{
	if (spElement  == NULL)
	{
		return false;
	}

	BSTR tagName = NULL;
	spElement->get_tagName(&tagName);
	if ((tagName != NULL) && wcsicmp(tagName , L"IFRAME") == 0)
	{
		::SysFreeString(tagName);
		return true;
	}

	return false;
}

BOOL CHtmlElementTestView::PreTranslateMessage(MSG* pMsg)
{
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	if ((pMsg->message == WM_MOUSEMOVE))
	{
		CPoint point(pMsg->pt);
		CString strPt;
		strPt.Format(_T("%d, %d"), point.x, point.y);
		CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();

		ScreenToClient(&point);

		CComPtr<IHTMLDocument2> pdoc2 = (IHTMLDocument2*)(this->GetHtmlDocument());
		CComPtr<IHTMLElement> pElement;
		CComPtr<IDispatch> pDisp;
		VARIANT_BOOL vIsTextEdit = VARIANT_FALSE;

		if (pdoc2 == NULL)
		{
			return true;
		}
		pdoc2->elementFromPoint(point.x,point.y,&pElement);
		long left = 0;
		long top = 0;

		while (IsIframe(pElement))
		{
			if (pElement == NULL)
			{
				break;
			}
			point.x -= left;
			point.y -= top;

			strPt += _T("   iframe   ");

			CComVariant strName;
			HRESULT hRet = pElement->getAttribute(CComBSTR(_T("name") ), 0 ,&strName) ;
			if (FAILED(hRet) || (strName.bstrVal == NULL) || (strName.GetSize() == sizeof(VARTYPE)))
			{
				return true ;
			}

			strPt += strName.bstrVal;

			CComPtr<IHTMLRect> spRect;
			CComQIPtr<IHTMLElement2> spElement2 = pElement;
			spElement2->getBoundingClientRect( &spRect );
			if (spRect)
			{
				spRect->get_left( &left );
				spRect->get_top( &top );
			}

			//处理iframe
			// 不是Object元素判断是不是iframe
			CComQIPtr<IHTMLIFrameElement> spIframeElement = pElement;
			if (spIframeElement == NULL)
			{
				return true;
			}

			pdoc2 = IframeElementProcess(spIframeElement);

			if (pdoc2 == NULL)
			{
				return true;
			}

			pElement = NULL;
			pdoc2->elementFromPoint(point.x - left , point.y - top ,&pElement);
		}

		if (pElement != NULL)
		{
			BSTR tagName = NULL;
			pElement->get_tagName(&tagName);

			strPt += _T(" tagname:");
			strPt += tagName;
			::SysFreeString(tagName);

			strPt.Format(strPt + _T(" x=%d, y=%d, left=%d, top=%d"), point.x, point.y, left, top);

			BSTR innertext = NULL;
			pElement->get_innerText(&innertext);
			if (innertext != NULL)
			{
				strPt += _T(" innertext:");
				strPt += innertext;
				::SysFreeString(innertext);
			}

			CComVariant strName;
			HRESULT hRet = pElement->getAttribute(CComBSTR(_T("name") ), 0 ,&strName) ;
			if (SUCCEEDED(hRet) && (strName.bstrVal != NULL) && (strName.GetSize() != sizeof(VARTYPE)))
			{
				USES_CONVERSION;
				std::string name = W2A(strName.bstrVal);
				strPt += _T(" name:");
				strPt += name.c_str();
			}

			pFrame->SetMessageText(strPt);
		}

		return true;
	}

	return CHtmlView::PreTranslateMessage(pMsg);
}
