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

#if !defined(AFX_GUITABWND_H__4C966B28_CE7A_407D_9A7A_9BE7A80B395D__INCLUDED_)
#define AFX_GUITABWND_H__4C966B28_CE7A_407D_9A7A_9BE7A80B395D__INCLUDED_

#pragma once

#define NORMAL 0
#define OVER   1
#define PRESS  2



class CTab 
{
public:
	CTab(CWin* mpParent, LPCSTR lpMsgs=NULL, UINT uHmenu=0)
	{
		pParent	= mpParent;
		if (lpMsgs== NULL)
			GetWindowText(pParent->GetSafeHwnd(),lpMsg,128);
		else
			strcpy(lpMsg,lpMsgs);
		nMenu=uHmenu;

	}

	~CTab()
	{
	
	}

	
	
public:
	CWin*	pParent;
	TCHAR	lpMsg[128];
	CRect	rect;
	UINT	nMenu;
	
};



//*********************************************************
class CContainer : public CWin
{
// Construction

public:

	//************************************************
	CContainer();
	virtual ~CContainer();
	//************************************************

	enum Style{S3D=0,FLAT=1,SHADOW=2};
	enum AlingTab{ALN_TOP=0,ALN_BOTTOM=1};
	enum TypeTab{TYPE_NORMAL=0,TYPE_MDI=1};

public:

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWin* pParentWnd, UINT nID);

public:
	//***********************************************************************	
	void	SetStyle(Style estyle);
	void    SetTypeTab(TypeTab Type=TYPE_NORMAL);
	void	virtual Drawtabs(CGDI* dc);
	void	Addtab(CWin* pParent, LPCSTR lpMsg=NULL, UINT uHmenu=0);
	void	RecalLayout();
	virtual void AjustTabs();
	virtual void    SetCurtab(int m_numtab);
	int     GetCurtab();
	void    DeleteTab(int m_numTab);
	void	ShowTitle(LPCSTR m_Caption);
	CWin*   GetActiveWnd () ;
	CWin*   GetNumWnd(int m_numtab)  ;
	int     GetCount(){return m_Numtabs;}
	void	SetActualTitle(BOOL bActual);
	void    SetALingTabs(AlingTab alnTab);
	int  	FindItem(HWND hWnd);
	void    UpdateCaption(CWin* pWnd,LPCSTR m_Title);
	void    SetTabMenu(LPCTSTR lpszMenuName);
	void	OpcionDrawWindow(BOOL bDraw=TRUE) {m_bDrawFrame=bDraw;}
	void    SetCaption(BOOL bCap=FALSE){m_bCaption=bCap; SendMessage(WM_NCPAINT,0,0);}
	void	ShowMenu(CPoint point);
	//***********************************************************************
	CTab* GetTab(int nTab);
	
protected:
	CImageCtrl			m_img;
	CControlBarButton	 m_CloseBtn;
	CControlBarButton	 m_AutoHideBtn;
	TypeTab			m_TypeTab;
	BOOL			m_ActualTitle;
	CArray		 m_pArray; 
	CSize			m_sizeImag;
	int				m_Numtabs;
	int				m_iMinValRec;
	int				m_ActualVar;
	int				m_iSelectTab;
	CRect			m_rectCliente;
	CRect			m_rectTab;
	CToolTipCtrl	CToolTip;
	CFont*			m_cfont;
	CFont			m_cfontBold;
	BOOL			m_style;
	CWin*			pParent;
	AlingTab		m_alnTab;
	BOOL			m_InTab;
	BOOL			m_bDrawFrame; //if want to draw the mayor child window  or all windows
	CRect			m_rcCloseBtn;
	CRect			m_rcAutoHideBtn;
	int				m_stateBtn;
	int				m_stateAHBtn;
	BOOL			m_bCaption;
	BOOL			m_close;
	LPCTSTR			m_hMenu;
	//Drag Variables
	BOOL			m_DragTab;
	BOOL			m_NCDragWindow;
	int				m_TabMove;
	BOOL		    m_DragWindow;
	CPoint			m_pointbase;
	//End Drag 


public:
	UINT			m_DOCKFLOAT;
	UINT			m_DOCKSITE;  //ultimo docksite de la ventana
	CContainer*		m_pContainer; //it is this parent a Container
public:
	 BOOL OnPaint(HDC hDC);
	 BOOL OnLButtonDown(UINT nFlags, CPoint pt);
	 BOOL OnRButtonDown(UINT nFlags, CPoint pt);
	 BOOL OnSize(UINT nType, int cx, int cy);
	 BOOL OnEraseBkgnd(HDC hDC );
	 int  OnDestroy();
	 int  OnCreate(LPCREATESTRUCT lpCreateStruct); 
     BOOL OnSetCursor(HWND hWnd, UINT nHitTest, UINT message);
	 void OnNcMouseMove(UINT nHitTest, CPoint point);	
	 UINT OnNcHitTest(CPoint cp);
	 BOOL OnNcCalcSize(BOOL bCalcValidRects,LPNCCALCSIZE_PARAMS lpncsp);
	 void OnNcPaint(HRGN hRgn);
	 void DrawGripper(CGDI* dc,CRect rcWin);
	 void OnTimer(UINT nIDEvent);
	 void OnNcLButtonDown(UINT nHitTest, CPoint point);
	 void OnNcRButtonDown(UINT nHitTest, CPoint point);
	 void OnNcLButtonUp(UINT nHitTest, CPoint point);
	 BOOL OnLButtonUp(UINT nFlags, CPoint pt);
	 void OnMouseMove(UINT nHitTest, CPoint point);
	 void ShowPane(BOOL bShow); 
	 BOOL IsClosePane();
	
public:

BEGIN_MSG_MAP()
	ON_WM_ERASEBKGND(OnEraseBkgnd)
	ON_WM_PAINT(OnPaint)
	ON_WM_CREATE(OnCreate)
	ON_WM_SIZE(OnSize)
	ON_WM_LBUTTONDOWN(OnLButtonDown)
	ON_WM_RBUTTONDOWN(OnRButtonDown)
	ON_WM_DESTROY(OnDestroy)
	ON_WM_SETCURSOR(OnSetCursor)
	ON_WM_NCCALCSIZE(OnNcCalcSize)
	ON_WM_NCPAINT(OnNcPaint)
	ON_WM_NCHITTEST(OnNcHitTest);
	ON_WM_LBUTTONDOWN(OnLButtonDown)
	ON_WM_NCLBUTTONDOWN(OnNcLButtonDown)
	ON_WM_NCRBUTTONDOWN(OnNcRButtonDown)
	ON_WM_NCMOUSEMOVE(OnNcMouseMove)
	ON_WM_TIMER(OnTimer)
	ON_WM_NCLBUTTONUP(OnNcLButtonUp)
	ON_WM_LBUTTONUP(OnLButtonUp)
	ON_WM_MOUSEMOVE(OnMouseMove)
END_MSG_MAP(CWin)

protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUITABWND_H__4C966B28_CE7A_407D_9A7A_9BE7A80B395D__INCLUDED_)
