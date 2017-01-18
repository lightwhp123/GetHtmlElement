// HtmlElementTestDoc.cpp : implementation of the CHtmlElementTestDoc class
//

#include "stdafx.h"
#include "HtmlElementTest.h"

#include "HtmlElementTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHtmlElementTestDoc

IMPLEMENT_DYNCREATE(CHtmlElementTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CHtmlElementTestDoc, CDocument)
END_MESSAGE_MAP()


// CHtmlElementTestDoc construction/destruction

CHtmlElementTestDoc::CHtmlElementTestDoc()
{
	// TODO: add one-time construction code here

}

CHtmlElementTestDoc::~CHtmlElementTestDoc()
{
}

BOOL CHtmlElementTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CHtmlElementTestDoc serialization

void CHtmlElementTestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CHtmlElementTestDoc diagnostics

#ifdef _DEBUG
void CHtmlElementTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHtmlElementTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CHtmlElementTestDoc commands
