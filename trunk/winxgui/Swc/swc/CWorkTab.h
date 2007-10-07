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

#if !defined(AFX_WORKTAB_H__A711D725_2268_4750_B58E_5218AD3BC0A5__INCLUDED_)
#define AFX_WORKTAB_H__A711D725_2268_4750_B58E_5218AD3BC0A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SCROLLLEFT  0x889
#define SCROLLRIGHT 0x890
//****************************************************************

class  CWorkTab : public CContainer  
{
public:
	
	//***************************************
		CWorkTab();
		virtual ~CWorkTab();
	//***************************************

public:

	void  virtual Drawtabs(CGDI* dc);
	void  OnHScroll(UINT nSBCode, UINT nPos, HWND hScrollBar); 
	void  PintaSeparador(CGDI* dc);
	void  OnSpiNiz(WPARAM wParam, LPARAM lParam, HWND hWnd);
	void  OnSpiNde(WPARAM wParam, LPARAM lParam, HWND hWnd);
	void  SizeScroll();
	void  OnWindowPosChanging(WINDOWPOS* lpwndpos);
	BOOL  OnPaint(HDC hDC);
	BOOL  OnLButtonDown(UINT nFlags, CPoint pt);
	BOOL  OnLButtonUp(UINT nFlags, CPoint pt);
	void  OnMouseMove(UINT nFlags, CPoint pt);
	BOOL  OnSize(UINT nType, int cx, int cy);
	virtual int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	BOOL  OnSysColorChange();
	BOOL  OnSetCursor(HWND hWnd, UINT nHitTest, UINT message);

protected:
	

	CScrollBar		m_spin;
	CNormalButton	m_toolBtn[2];
	CScrollBar		m_scroll;
	BOOL			m_PresRight;
	BOOL			m_PresLeft;
	int				m_deplaza;
	CRect			m_btndesplaza;
	BOOL			bIniciaArrastre;
	CDrawLayer	m_wd;
	BOOL			m_EnableL;
	BOOL			m_EnableR;
	CImageCtrl		m_img;
protected:

	BEGIN_MSG_MAP()
		ON_WM_PAINT(OnPaint)
		ON_WM_CREATE(OnCreate)
		ON_WM_SIZE(OnSize)
		ON_WM_LBUTTONDOWN(OnLButtonDown)
		ON_WM_LBUTTONUP(OnLButtonUp)
		ON_WM_MOUSEMOVE(OnMouseMove)
		ON_WM_SYSCOLORCHANGE(OnSysColorChange)
		ON_WM_SETCURSOR(OnSetCursor)
		ON_WM_WINDOWPOSCHANGING(OnWindowPosChanging)
		ON_COMMAND(SCROLLLEFT, OnSpiNiz)
		ON_COMMAND(SCROLLRIGHT, OnSpiNde)
		ON_WM_HSCROLL(OnHScroll)
	END_MSG_MAP(CContainer)

public:
	

};

#endif // !defined(AFX_WORKTAB_H__A711D725_2268_4750_B58E_5218AD3BC0A5__INCLUDED_)
