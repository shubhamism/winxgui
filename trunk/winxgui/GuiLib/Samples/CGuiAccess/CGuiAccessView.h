// CGuiAccessView.h : interface of the CCGuiAccessView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGUIACCESSVIEW_H__2A9AEA43_4FD8_44CE_AC44_912722FCE58A__INCLUDED_)
#define AFX_CGUIACCESSVIEW_H__2A9AEA43_4FD8_44CE_AC44_912722FCE58A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCGuiAccessView : public CView
{
protected: // create from serialization only
	CCGuiAccessView();
	DECLARE_DYNCREATE(CCGuiAccessView)

// Attributes
public:
	CCGuiAccessDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCGuiAccessView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCGuiAccessView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCGuiAccessView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CGuiAccessView.cpp
inline CCGuiAccessDoc* CCGuiAccessView::GetDocument()
   { return (CCGuiAccessDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGUIACCESSVIEW_H__2A9AEA43_4FD8_44CE_AC44_912722FCE58A__INCLUDED_)
