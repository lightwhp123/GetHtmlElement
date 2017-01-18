// HtmlElementTestDoc.h : interface of the CHtmlElementTestDoc class
//


#pragma once


class CHtmlElementTestDoc : public CDocument
{
protected: // create from serialization only
	CHtmlElementTestDoc();
	DECLARE_DYNCREATE(CHtmlElementTestDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CHtmlElementTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


