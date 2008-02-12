// This is part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.
//
// mfcieVw.h : interface of the CMfcieView class
//
// $Id: mfcievw.h,v 1.5 2006/02/18 08:58:01 liucong Exp $
/////////////////////////////////////////////////////////////////////////////

#ifndef __SEARCHER_H__
#include "src/searcher.h"
#endif

#if !defined(AFX_MFCIEVIEW_H__47FF4085_CE1B_11D0_BEB6_00C04FC99F83__INCLUDED_)
#define AFX_MFCIEVIEW_H__47FF4085_CE1B_11D0_BEB6_00C04FC99F83__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// -------------------------------------------------------------------------

STDMETHODIMP XSLTConvert(LPCWSTR xslFile, LPCWSTR xmlFile, IStream* outStream);

#define INDEXING_DIR		L"searcher_output"
#define INPUT_DIR			L"../testcase/"
#define XML_FILE			L"SearchResults.xsl"
#define XSL_FILE			L"SearchResults.xml"

// -------------------------------------------------------------------------

class CMfcieView : public CHtmlView
{
protected: // create from serialization only
	CMfcieView();

	DECLARE_DYNCREATE(CMfcieView)

// Attributes
public:
	CMfcieDoc* GetDocument();

private:
	//@@modify - add member(s)
	FileSearcher m_searcher;

public:
	//@@modify - add method Navigate2
	void Navigate2(LPCTSTR lpszURL, DWORD dwFlags = 0,
		LPCTSTR lpszTargetFrameName = NULL,	LPCTSTR lpszHeaders = NULL,
		LPVOID lpvPostData = NULL, DWORD dwPostDataLen = 0)
	{
			#undef CreateStreamOnHGlobal

			WCHAR resultPath[MAX_PATH];
			GetSystemIniPath(resultPath, INDEXING_DIR);

			kfc::ks_wstring xslPath(resultPath);
			normalizePath(xslPath);
			xslPath.append(XSL_FILE);

			kfc::ks_wstring xmlPath(resultPath);
			normalizePath(xmlPath);
			xmlPath.append(XML_FILE);

			kfc::KWriteArchive arch(xmlPath);
			m_searcher.search(lpszURL, arch);

			CComPtr<IStream> spStrm;
			HRESULT hr = CreateStreamOnHGlobal(NULL, TRUE, &spStrm);

			if (SUCCEEDED(hr))
			{
				hr = ::XSLTConvert(xslPath.c_str(), xmlPath.c_str(), spStrm);

				LARGE_INTEGER dlibMove;
				ULISet32(dlibMove, 0);
				spStrm->Seek(dlibMove, SEEK_SET, NULL);
			}

			if (SUCCEEDED(hr))
				LoadWebBrowserFromStream(m_pBrowserApp, spStrm);
	}

	//@@modify - add method GoHome
	void GoHome()
	{
		CHtmlView::Navigate(_T("about:blank"));
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcieView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

	//@@modify - comment
	//void OnTitleChange(LPCTSTR lpszText);
	//void OnDocumentComplete(LPCTSTR lpszUrl);

	void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags,
		LPCTSTR lpszTargetFrameName, CByteArray& baPostedData,
		LPCTSTR lpszHeaders, BOOL* pbCancel);

// Implementation
public:
	virtual ~CMfcieView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMfcieView)
	afx_msg void OnGoBack();
	afx_msg void OnGoForward();
	afx_msg void OnGoSearchTheWeb();
	afx_msg void OnGoStartPage();
	afx_msg void OnViewStop();
	afx_msg void OnViewRefresh();
	afx_msg void OnHelpWebTutorial();
	afx_msg void OnHelpOnlineSupport();
	afx_msg void OnHelpMicrosoftOnTheWebFreeStuff();
	afx_msg void OnHelpMicrosoftOnTheWebFrequentlyAskedQuestions();
	afx_msg void OnHelpMicrosoftOnTheWebGetFasterInternetAccess();
	afx_msg void OnHelpMicrosoftOnTheWebMicrosoftHomePage();
	afx_msg void OnHelpMicrosoftOnTheWebSearchTheWeb();
	afx_msg void OnHelpMicrosoftOnTheWebSendFeedback();
	afx_msg void OnHelpMicrosoftOnTheWebInternetStartPage();
	afx_msg void OnHelpMicrosoftOnTheWebBestOfTheWeb();
	afx_msg void OnViewFontsLargest();
	afx_msg void OnViewFontsLarge();
	afx_msg void OnViewFontsMedium();
	afx_msg void OnViewFontsSmall();
	afx_msg void OnViewFontsSmallest();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in mfcieView.cpp
inline CMfcieDoc* CMfcieView::GetDocument()
   { return (CMfcieDoc*)m_pDocument; }
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

/////////////////////////////////////////////////////////////////////////////
// $Log: mfcievw.h,v $
// Revision 1.5  2006/02/18 08:58:01  liucong
// no message
//
// Revision 1.4  2006/02/17 06:48:04  liucong
// 稍微调整了一下searcher相关的格式
//
// Revision 1.3  2006/01/09 02:04:46  xushiwei
// GUI版本的搜索demo初步完成。
//
// Revision 1.2  2006/01/09 01:22:25  xushiwei
// 1、增加工程mfcie，其实改造为searcher的demo（GUI）
// 2、英文分词漏入文件，暂时屏蔽。
//

#endif // !defined(AFX_MFCIEVIEW_H__47FF4085_CE1B_11D0_BEB6_00C04FC99F83__INCLUDED_)
