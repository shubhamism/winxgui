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


#if !defined(AFX_BOUTLOOK_H_INCLUDED_)
#define AFX_BOUTLOOK_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//#define WM_OUTBAR_NOTIFY			WM_USER+1
//#define NM_OB_ITEMCLICK				WM_OUTBAR_NOTIFY+1

//esta clase da la flexibilidad de adicionar componentes
//diferentes a botones.


class COutLook;

class  CItems
{
public:
	CItems(COutLook* m_pParent,HICON m_hIcon,UINT Cmd,LPCSTR m_Message,LPCSTR m_ToolTip=_T(""), BOOL bTypeOutLook=TRUE);
public:
	CToolButton		   m_bt;
	int				   m_btipo;  	//es un boton o un derivado de Cwnd
	LPSTR			   m_szMessage;	//el mensaje bajo el boton		
};



class   COutLook : public CWin
{

	friend class CItems;	

public:
	//***************************************
	COutLook();
	virtual ~COutLook();
	//***************************************

public:

	virtual BOOL Create(DWORD dwStyle,  CRect& rect, CWin* pParentWnd, UINT nID) ;
	virtual BOOL PreTranslateMessage(MSG* pMsg);

public:
	void	AddItem(UINT Cmd,LPCSTR m_szCaption,int nIndex,LPCSTR m_ToolTip=_T(""));
	void	SetImageList(UINT nBitmapID, int cx, int nGrow, COLORREF crMask);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	void	RecalLayout();
	void	SetTypeLook(BOOL bNormal=TRUE)
	{
		m_TypeOutLook=bNormal;
	}
	
protected:
	//**************************************************
	CImageCtrl 	m_imageList;
	CArray 	m_ArrayButtons;
	CSize      	m_sizeImage;
	int		m_ActualButtonPres;
	int        	m_ultimoBotonResal;
	int        	m_NumBottoms;
	COLORREF  m_cbkg;	
	int		m_mouseMove;
	int        	m_Avance;    //avance del scroll
	CRect	m_rectArrowUp;
	CRect	m_rectArrowDown;	
	BOOL	   	m_iDrawFrameUp;		
	BOOL       	m_iDrawFrameDown;	    
	UINT	   	mnID;
	BOOL	   	m_bPressU;
	BOOL	   	m_bPressD;
	HDC		hdc;
	BOOL	   	m_bIsXp;
	BOOL		m_TypeOutLook;  // TRUE Outlook normal o FALSE 
	//**************************************************


	 BOOL OnPaint(HDC hDC);
	 BOOL OnLButtonDown(UINT nFlags, CPoint pt);
	 BOOL OnLButtonUp(UINT nFlags, CPoint pt);
	 BOOL OnSize(UINT nType, int cx, int cy);
	 BOOL OnSysColorChange();
	 void  OnTimer(UINT nIDEvent);
	 BOOL OnEraseBkgnd(HDC hDC );
	 int OnDestroy();
	 
protected:


	BEGIN_MSG_MAP()

	ON_WM_PAINT(OnPaint)
	ON_WM_LBUTTONDOWN(OnLButtonDown)
	ON_WM_LBUTTONUP(OnLButtonUp)
	ON_WM_SIZE(OnSize)
	ON_WM_SYSCOLORCHANGE(OnSysColorChange)
	ON_WM_TIMER(OnTimer)
	ON_WM_ERASEBKGND(OnEraseBkgnd)
	ON_WM_DESTROY(OnDestroy)

	END_MSG_MAP(CWin)
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOUTLOOK_H_INCLUDED_)
