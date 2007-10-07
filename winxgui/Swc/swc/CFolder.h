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


#if !defined(SWC_BCFOLDER_H_INCLUDED_)
#define SWC_BCFOLDER_H_INCLUDED_



//**********************************************************
class CFolderBar
{
public:
	CFolderBar(CWin* m_wnd,LPCSTR lp_msg,UINT uImg=(UINT)-1);
	~CFolderBar();
public:
	CWin*	m_CWin;
	LPCSTR	m_lpMsg;
	UINT	m_img;
	CRect	m_rect;
	BOOL	m_posUp;
		
};

//*************************************************************
class  CFolder : public CWin
{

public:
	CFolder();
	virtual ~CFolder();
public:
	//*******************************
	enum Style{
			mNormal	=0,
			mPush	=1,
			mFlat	=2
	};
	enum TypeFolder{
		    mOutlook=0,
			mToolBox=1
	};

	//*******************************
public:
	virtual BOOL Create(CWin* pParentWnd, CRect& rect, DWORD dwStyle,   UINT nID) ;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreSubclassWindow(); 
public:
	void	AddFolder(CWin* pParent,LPCSTR lpMsg, UINT uIMg=(UINT)-1);
	void	DeleteFolder(int m_iNumFolder,BOOL bUpdate=TRUE);
	void	RecalLayout();
	virtual void DrawFolder(CFolderBar* cfb,Style m_Style);
	int		PointInFolder(CPoint pt);
	void 	EfectoScroll();
	void	RemoveAllFolder();
	void	TypeLook(TypeFolder tol);
	void	SelectFolder(int m_iNumFolder);
	BOOL	IsThisSelected(); 
protected:
	CArray	 m_ArrayFolder; 
	CToolTipCtrl		m_ToolTip;
	int				m_NumFolders;   //total de folders
	int				m_numFolderDown;
	int				m_numFolderUp;   //numero de folders arriba
	CFont*			cfont;
	int				m_iSelected;
	int				m_ultimoFolderResal;
	int				m_iPosDown; //a partir de donde se ubica el anterior folder
	int			    	m_iposUp;   //a partir de donde se ubica el siguiente folder
	int				m_itemp;
	int				m_AntFolder; //folder anterior
	TypeFolder			m_typel;	//tipo de look
	int				m_iWhatFolderIsDrawNow; //que folder estoy pintando

public:
	
	 BOOL OnPaint(HDC hDC);
	 BOOL OnLButtonDown(UINT nFlags, CPoint pt);
	 BOOL OnLButtonUp(UINT nFlags, CPoint pt);
	 void OnMouseMove(UINT nFlags, CPoint pt);
	 BOOL OnSize(UINT nType, int cx, int cy);
	 void  OnTimer(UINT nIDEvent);
	 BOOL OnEraseBkgnd(HDC hDC );
	 int OnDestroy();
protected:
	
	BEGIN_MSG_MAP()
	ON_WM_PAINT(OnPaint)
	ON_WM_LBUTTONDOWN(OnLButtonDown)
	ON_WM_MOUSEMOVE(OnMouseMove)
	ON_WM_LBUTTONUP(OnLButtonUp)
	ON_WM_SIZE(OnSize)
	ON_WM_TIMER(OnTimer)
	ON_WM_ERASEBKGND(OnEraseBkgnd)
	ON_WM_DESTROY(OnDestroy)
	END_MSG_MAP(CWin)
	
	
public:
	
};

/////////////////////////////////////////////////////////////////////////////


#endif 
