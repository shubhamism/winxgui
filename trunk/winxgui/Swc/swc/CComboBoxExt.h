/*
 * 
 *
 * Copyright 2007 Francisco Campos. All rights reserved.
 * BEYONDATA  PROPRIETARY. Use is subject to license terms. </F>
 *
 *			 \|||/
 *			 |o_o|
 *	----o00o-------o00o---      
 **/

#if !defined(AFX_COMBOBOXEXT_H__4E237771_A1F4_11D5_A8C4_0008C7B2934C__INCLUDED_)
#define AFX_COMBOBOXEXT_H__4E237771_A1F4_11D5_A8C4_0008C7B2934C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CImageCtrl;

/////////////////////////////////////////////////////////////////////////////
// CComboBoxExt window

class  CComboBoxExt : public CComboBox
{
// Construction
public:
	CComboBoxExt();
	virtual		~CComboBoxExt();

// Attributes
public:
	
// Operations
public:
	enum enTypeShow{CM_NORMAL=0,CM_ONFOCUS,CM_SELECCIONADO};

public:
	BOOL		m_bOverCombo;
	int			m_iWidthDrowDown;
	COLORREF	m_clrBtnFace;
	COLORREF	m_clrBtnLight;
	COLORREF	m_clrBtnDark;
	CFont		m_Font;
	BOOL		m_bPress;
	BOOL        m_bFondoXp;
	BOOL		m_IsCallMiniTool;
	BOOL		bhistory;

public:
	//******************************************************
	void		DrawCombo(enTypeShow enShow,CGDI* pDC);
	void		DrawArrow(CGDI* pDC,CRect m_rc);
	void		SetColor(COLORREF clrFace);
	void        AutoColor(BOOL bColor=TRUE);
	int			AddString(LPCTSTR lpszString);
	
	virtual void PreSubClassWnd();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
		
	// Generated message map functions
protected:
	CPoint			mHeight;
	CDrawLayer		m_dw;
	BOOL			bColor;
	CImageCtrl		m_imgArrow;
protected:

     BOOL OnPaint(HDC hDC);
	 BOOL OnLButtonDown(UINT nFlags, CPoint pt);
	 BOOL OnLButtonUp(UINT nFlags, CPoint pt);
	 int  OnCreate(LPCREATESTRUCT lpCreateStruct); 
     BOOL OnSetCursor(HWND hWnd, UINT nHitTest, UINT message);
	 BOOL OnSysColorChange();
	 virtual void OnCbnSelendCandel();
	 void OnSetFocus(HWND hOldWnd);
	 void OnTimer(UINT nIDEvent);
	 virtual void OnCbnCloseUp();
	 virtual void OnCbnEditUpdate();
	 BEGIN_MSG_MAP()
		ON_WM_CREATE(OnCreate)
		ON_WM_PAINT(OnPaint)
		ON_WM_LBUTTONDOWN(OnLButtonDown)
		ON_WM_LBUTTONUP(OnLButtonUp)
		ON_WM_SYSCOLORCHANGE(OnSysColorChange)
		ON_WM_SETCURSOR(OnSetCursor)
		ON_WM_TIMER(OnTimer)
		ON_WM_SETFOCUS(OnSetFocus)
	END_MSG_MAP(CComboBox)

	 
	
	
	
};


#endif 
