/*
 * CFrame.h		1.0  23/09/2003
 *
 * Copyright 2003 Francisco Campos. All rights reserved.
 * BEYONDATA  PROPRIETARY. Use is subject to license terms. 
 *
 *			 \|||/
 *			 |o_o|
 *	----o00o-------o00o---      
 *  ----------------------
 * 
 *   Frames Wrapper functions
 *
 *****/


#if !defined(C_FRAME_H__INCLUDED_)
#define C_FRAME_H__INCLUDED_

#pragma once



#include "stdafx.h"

/*
 *
 *    CFrame Class
 *
 *
 *
 ****/

#include "stdafx.h"


#define BS_ALIGN_LEFT	0x3100L
#define BS_ALIGN_BOTTOM	0x3101L
#define BS_ALIGN_RIGHT	0x3102L
#define BS_ALIGN_FLOAT	0x3103L

#define BS_ALIGN_VERT	0x3104L
#define BS_ALIGN_HORZ	0x3105L


#define BS_BORDER_LEFT	0x3106L
#define BS_BORDER_TOP	0x3107L
#define BS_BORDER_RIGHT	0x3108L

#define BS_SPLIT_VERT	0x3109L
#define BS_SPLIT_HORTZ	0x3110L

#define BS_AUTO_LEFT	0x3111L
#define BS_AUTO_BOTTOM	0x3112L
#define BS_AUTO_RIGHT	0x3113L
#define BS_AUTO_FLOAT	0x314L

class CMiniDock;
class DockManager;


class CFrame : public CWin
{
public:
	CWin*			m_ClientView;
	CReBarCtrlEx*	m_ReBar;
//	CArray			m_dockBars;
	CFont			m_fontMenu;	
	CStatusCtrlEx	m_statusCtrl;
	HWND			m_SubMenuActual;
	CMiniDock*		m_MiniFrame;
	HWND hMDIClient;
	DockManager*	m_DockLeft;
	DockManager*	m_DockBottom;
	DockManager*	m_DockRight;
	CImageCtrl		m_imgCtrl;
	CSize			m_sizeImagDocks;

public:
	
	// COOLMENU SUPPORT
		CMenuSpawn	cSpawn;
		CRect oldMenuBarRc;
		bool bMenuLooping;
		UINT uiTimerId;
	// END COOLMENU SUPPORT


public:
	
	CFrame(HWND hWnd=NULL) : CWin(hWnd)
	{
		m_ClientView=NULL;
		hMDIClient=NULL;
		oldMenuBarRc.SetRect(0,0,0,0);
		bMenuLooping = false;
		uiTimerId = 0;
		m_ReBar=NULL;
		m_ClientView=NULL;
		m_DockLeft=NULL;
		m_DockBottom=NULL;
		m_DockRight=NULL;
		m_sizeImagDocks=CSize(0,0);
	}
	
	~CFrame()
	{
		if (m_ReBar != NULL) delete m_ReBar;
		if (m_ClientView== NULL) return;
		if (::IsWindow(m_ClientView->GetSafeHwnd()))
			delete m_ClientView; 
		if (m_imgCtrl.GetImageHandle())
			m_imgCtrl.Destroy();
	};

	virtual BOOL LoadFrame(UINT uID,DWORD dwStyle=WS_OVERLAPPEDWINDOW,HWND hParentWnd=NULL);
	void LoadPositionBar();
	void ShowFloatWindow(HWND hWnd);
	UINT GfxSetSafeTimer(CWin * pWnd, const UINT uiElapse)
	{
		ASSERT(pWnd && pWnd->GetSafeHwnd());
		UINT iTimer = 1;
		while (iTimer < 10000)
		{
			UINT res = pWnd->SetTimer(1, uiElapse, NULL);
			if (res) return res;
			iTimer ++;
		}
		return 0;
	}

	void FloatWindow(CWin* pParent, CPoint point,CRect rc );
	void CreateDock();
	LRESULT OnReBarAutoSize(int idCtrl, LPNMHDR pnmh)
	{
		UpdateFrame(FALSE);	
		return 0;
	}

	
	int CreateExBars(int Panels[],int nIDCount)
	{
		m_ReBar=new CReBarCtrlEx();		
		if (!m_ReBar->Create(GetSafeHwnd()))
			return FALSE;
		if ( !m_statusCtrl.Create(GetSafeHwnd()))
			return FALSE;
		m_statusCtrl.SetIndicators(Panels,nIDCount);
		CreateDock();
		return TRUE;
	}

	int CreateBars(int Panels[],int nIDCount)
	{
		m_ReBar = new CReBarCtrlEx();
		if (!m_ReBar->Create(GetSafeHwnd()))
			return FALSE;

		if ( !m_statusCtrl.Create(GetSafeHwnd()))
			return FALSE;
		m_statusCtrl.SetIndicators(Panels,nIDCount);
		
		return TRUE;
	}

	BOOL SetPanelText(int iPanel,LPCTSTR lpText)
	{
		ASSERT(m_statusCtrl.GetSafeHwnd())
		return m_statusCtrl.SetPaneText(iPanel,lpText);
	}

	void SetImageDockWindows(UINT nBitmapID, int cx, int nGrow, COLORREF crMask)
	{
		
		if (nBitmapID != -1)
		{
			if(!m_imgCtrl.CreateColor(nBitmapID)) 
				return ;
			int x,y;
			x=y=0;
			m_imgCtrl.GetIconSize(&x,&y);
			m_sizeImagDocks=CSize(x,y);	
		}
		else
		{
			CBitmap cbmp;
			BITMAP bmp;
			m_imgCtrl.Create(nBitmapID,cx,nGrow,crMask);
			cbmp.LoadBitmap(theApp->GetInstance(),(LPCTSTR)nBitmapID);
			cbmp.GetBitmap(&bmp);
			m_imgCtrl.Add(&cbmp,crMask);
			m_sizeImagDocks=CSize(cx,bmp.bmHeight);	
			cbmp.DeleteObject();
			

		}		
	}

	void DrawIconDocks(int numIcon,CPoint cp, CGDI* dc)
	{
		if (m_imgCtrl.GetImageHandle())
			m_imgCtrl.Draw(numIcon,dc->m_hDC,cp,ILD_TRANSPARENT);

	}

	BOOL AddBar(CToolBarCtrl* pToolBar, int nID, LPTSTR lpstrTitle = NULL)
	{
		if(m_ReBar->GetSafeHwnd() != NULL )
		{
			m_ReBar->AddBar(pToolBar, nID,lpstrTitle);
			return TRUE;
		}
		
		return FALSE;
		
	}
	void UpdateFrame(BOOL bResizeBars=TRUE);

	

	HWND GetSafeClientHwnd()
	{
		return hMDIClient;
	}

	//--------------------------------------------
	// Messages map
	//--------------------------------------------
	int  OnPaint(HDC hDC);

   	LRESULT OnToolTipText(int idButton, LPNMHDR pnmh)
	{
		LPNMTTDISPINFOA lpNmDisPinfo = (LPNMTTDISPINFOA)pnmh;
		char Buffer[256];
		lpNmDisPinfo->szText[0] = 0;
		memset(Buffer,0x00,256);
		int iPos=0;
		if((idButton != 0) && !(lpNmDisPinfo->uFlags & TTF_IDISHWND))
		{
			::LoadStringA(theApp->GetInstance(),idButton,Buffer,256);
			int i;
			for( i=0; i < lstrlen(Buffer); i++)
			{
				if (Buffer[i] == '\n')
					break;
			}			
			if (i <0) return 0;
			lstrcpynA(lpNmDisPinfo->szText,Buffer+i+1,
					  sizeof(lpNmDisPinfo->szText) / sizeof(lpNmDisPinfo->szText[0]));
			
		#if (_WIN32_IE >= 0x0300)
				lpNmDisPinfo->uFlags |= TTF_DI_SETITEM;
		#endif 
		
		}
	
		return 0;
	}

	LRESULT OnShowBand(HWND hWnd)
	{
		return m_ReBar->OnShowBand(hWnd);
	}

	CFont GetMenuFont()
	{
		if (!(HFONT)m_fontMenu) {
			NONCLIENTMETRICS info;
			info.cbSize = sizeof(info);
			SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(info), &info, 0);
			m_fontMenu.CreateFontIndirect(&info.lfMenuFont);
		}
		return m_fontMenu;
	}


	//--------------------------------------------
	//Menu Functions
	//--------------------------------------------

	
		void OnMenuSelect( UINT nItemID,UINT nFlags,HMENU hSysMenu )
		{
			if (nItemID != 0)
			{
				TCHAR szTemp[256];
				theApp->LoadString(nItemID,szTemp,255);
				for(int i=0; i < lstrlen(szTemp); i++)
				{
					if (szTemp[i] == '\n')
						szTemp[i]='\0';
				}			
				SetPanelText(0,szTemp );
			}

		}

		 virtual BOOL OnDrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct)
		 {
			 if (!cSpawn.DrawItem(lpDrawItemStruct))
				Default();
			 return TRUE;
		 }
		 virtual LRESULT OnMeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
		 {
			 if (!cSpawn.MeasureItem(lpMeasureItemStruct))
				Default();
			 return TRUE;
		 }
		 void OnInitMenuPopup(HMENU hPopupMenu, UINT nIndex, BOOL bSysMenu)
		 {
			 if( !SubMenuSystem(hPopupMenu))
				 cSpawn.RemapMenu(hPopupMenu);
			 else
				Default();
			 
		 }

		 void OnInitMenu(HMENU hMMenu)
		 {
			 if( !SubMenuSystem(hMMenu))
				cSpawn.RemapMenu(hMMenu);
			 else
				Default();
		 }


		 

		 virtual void SaveConfig()
		 {
		    /* CRect rc;
			TCHAR szSection[512];
			wsprintf(szSection, _T("%s-MainWindow"), theApp->m_lpBuffer);
			GetWindowRect(rc);
			WriteInteger(rc.left,szSection, _T("Left"));
			WriteInteger(rc.right,szSection, _T("Right"));
			WriteInteger(rc.top,szSection, _T("Top"));
			WriteInteger(rc.bottom,szSection, _T("Bottom"));
			*/
		 }

		 virtual CRect GetConfig()
		 {
		    TCHAR szSection[512];
			CRect rcPosition;
			wsprintf(szSection, _T("%s-MainWindow"), theApp->m_lpBuffer);
		
			rcPosition.left=ReadInteger(szSection, _T("Left"));
			rcPosition.right=ReadInteger(szSection, _T("Right"));
			rcPosition.top=ReadInteger(szSection, _T("Top"));
			rcPosition.bottom=ReadInteger(szSection, _T("Bottom"));
		
	   		if (rcPosition.left <0 || rcPosition.right < 0 || rcPosition.bottom <= 0 || rcPosition.right <= 0)
				rcPosition=CRect(0,0,240,240);
		
			return rcPosition;
		 }

		 LRESULT OnMenuChar(UINT nChar, UINT nFlags, HMENU hMenu)
		 {
			 LRESULT lRes;
			if (!cSpawn.FindKeyboardShortcut(nChar, nFlags, hMenu, lRes)) 
				lRes = Default();
			return lRes;
		 }
		
		 BOOL SubMenuSystem(HMENU hPopupMenu)
		 {
			 MENUITEMINFO mii;
			 mii.cbSize = sizeof (MENUITEMINFO); // must fill up this field
			 mii.fMask = MIIM_ID;             // get the state of the menu item
			 return (BOOL)GetMenuItemInfo( hPopupMenu, SC_CLOSE, FALSE,&mii);
		 }

		/*void OnNcPaint(HRGN hRgn)
		{
			HDC hdc;
		    hdc = GetDCEx((HRGN)hRgn, DCX_WINDOW|DCX_EXCLUDERGN);
			Default();
			DrawNcMenuBar(hdc);
			ReleaseDC(hdc);

		}
		 void DrawNcMenuBar(HDC hdc)
		 {
			 CRect rc;
			 GetClientRect(rc);
			 rc.top+=GetSystemCaption()+GetSystemBorderX()*2+1;
			 rc.left+=GetSystemBorderY()*2;
			 rc.bottom=rc.top+GetSystemMenuHeight()+GetSystemBorderX()+1;
			 rc.top=rc.bottom-2;
			 CWindowDC wdc(GetSafeHwnd());
			 CBrush cb;
			 cb.CreateSysColorBrush(COLOR_BTNFACE);
			 wdc.FillRect(rc,&cb);
		 }*/

		
		 void OnTimer(UINT nIDEvent)
		 {
			 	if (uiTimerId == nIDEvent && !bMenuLooping)
				{
					CPoint pt;
					GetCursorPos(&pt);
					LRESULT res = SendMessage(WM_NCHITTEST, 0, MAKELONG(pt.x, pt.y));
				}
				
				Default();
		 }

		 void OnEnterMenuLoop(BOOL bIsTrackPopupMenu)
		 {
			if (!(oldMenuBarRc.IsRectEmpty()))
			{
				CWindowDC dc(this);
				dc.Draw3dRect(oldMenuBarRc,cSpawn.crMenu, cSpawn.crMenu);
				oldMenuBarRc.SetRect(0,0,0,0);
				dc.DeleteDC();
			}

			bMenuLooping = true;
		 }

		 void OnExitMenuLoop(BOOL bIsTrackPopupMenu)
		 {
			bMenuLooping = false;
		 }

		 BOOL OnNotifyItemChange(int wParam, LPNMHDR lParam)
		 {
			 if ((((LPNMTBHOTITEM)lParam)->dwFlags) & HICF_LEAVING)
				SetPanelText(0,"Ready");
			 else
			 {
				TCHAR szTemp[256];
				theApp->LoadString((((LPNMTBHOTITEM)lParam)->idNew),szTemp,255);
				for(int i=0; i < lstrlen(szTemp); i++)
				{
					if (szTemp[i] == '\n')
						szTemp[i]='\0';
				}			
				SetPanelText(0,szTemp );
			  }
			return TRUE;
		 }

		 BOOL OnSize(UINT nType,long x, long y) 
		 {
		 	UpdateFrame();
			return TRUE;
		 }
	
		 virtual BOOL OnDestroy()
		 {
			 SaveConfig();
			 return TRUE;
		 }
	//--------------------------------------------
	// End messages map
	//--------------------------------------------

BEGIN_MSG_MAP()
	 ON_WM_PAINT(OnPaint)
	 ON_WM_SIZE(OnSize) 
	 ON_NOTIFY_CODE(RBN_AUTOSIZE, OnReBarAutoSize)
	 ON_NOTIFY_CODE(TTN_GETDISPINFOA, OnToolTipText)
	 ON_NOTIFY_CODE(TBN_HOTITEMCHANGE, OnNotifyItemChange)
	 ON_WM_DRAWITEM(OnDrawItem)
	 ON_WM_MEASUREITEM(OnMeasureItem)
	 ON_WM_INITMENUPOPUP(OnInitMenuPopup)
	 ON_WM_MENUCHAR(OnMenuChar)
	 ON_WM_INITMENU(OnInitMenu)
	 ON_WM_TIMER(OnTimer)
	 ON_WM_ENTERMENULOOP(OnEnterMenuLoop)
	 ON_WM_EXITMENULOOP(OnExitMenuLoop)
	 ON_WM_MENUSELECT(OnMenuSelect)
	 //ON_WM_NCPAINT(OnNcPaint)
END_MSG_MAP(CWin)

};


class CMiniFrame : public CFrame
{
protected:
	CWin* pParent;
	CPoint m_oldPost;
	

public:
	CMiniFrame(HWND hWnd=NULL): CFrame(hWnd)
	{
		
	}
	~CMiniFrame(){ }
public:
	

	virtual BOOL Create(CWin* pParentWnd, UINT nID, CRect& rc, CWin* pControls, DWORD dwStyle=WS_POPUP|WS_CAPTION|WS_CLIPSIBLINGS |WS_SYSMENU);
	
	virtual BOOL PreCreateWindow(LPCREATESTRUCT cs)
	{
		if (cs->style & WS_CAPTION)
			cs->dwExStyle |= WS_EX_TOOLWINDOW;
		cs->dwExStyle &= ~(WS_EX_CLIENTEDGE);
		return TRUE;
		
	}
	
	

	void OnNcDestroy(LPCREATESTRUCT lpst)
	{
		delete this;
	}
	

	virtual BOOL OnDestroy();
	

	BOOL OnSize(UINT nType,long x, long y) 
	{
	 	UpdateFrame();
		return TRUE;
	 }
	
virtual UINT OnNcHitTest(CPoint cp)
{
	
	return Default();
}

 virtual void OnNcLButtonDown(UINT nHitTest, CPoint point)
 {
	Default();
 }

 virtual void OnNcLButtonUp(UINT nHitTest, CPoint point)
 {
	Default();
 }

 virtual void OnMouseMove(UINT nHitTest, CPoint point)
 {
	Default();
 }
 virtual void OnNcMouseMove(UINT nHitTest, CPoint point)
 {
	Default();	
 }

 virtual void OnNcButtonDblClk(UINT nHitTest, CPoint point)
 {
	Default();
 }

 virtual void OnLButtonUp(UINT nHitTest, CPoint point)
 {
	Default();
 }
 virtual void OnRButtonDown(UINT nHitTest, CPoint point)
 {
	Default();
 }

 virtual void OnWindowPostChanging(LPWINDOWPOS lpWindowsPos)
 {
	 Default();
 }

 virtual void OnKeyDown(int iVkey, DWORD dTime)
 {
	 Default();
 }

BEGIN_MSG_MAP()
	ON_WM_NCDESTROY(OnNcDestroy)
	ON_WM_DESTROY(OnDestroy);
	ON_WM_SIZE(OnSize) 
	ON_WM_NCHITTEST(OnNcHitTest)
	//ON_WM_NCMOUSEMOVE(OnNcMouseMove)
	ON_WM_MOUSEMOVE(OnMouseMove)
	ON_WM_NCLBUTTONDOWN(OnNcLButtonDown)
	ON_WM_NCLBUTTONUP(OnNcLButtonUp)
	ON_WM_LBUTTONUP(OnLButtonUp)
	ON_WM_RBUTTONDOWN(OnRButtonDown)
	ON_WM_NCLBUTTONDBLCLK(OnNcButtonDblClk)
	ON_WM_KEYDOWN(OnKeyDown)
//	ON_WM_WINDOWPOSCHANGING(OnWindowPostChanging)
END_MSG_MAP(CFrame)
};

//----------------------------------------
//Docking windows routines
//----------------------------------------
class CMiniDock: public CMiniFrame
{
public:
	CMiniDock(HWND hWnd=NULL): CMiniFrame(hWnd)
	{
		m_Drag=FALSE;
		bDrawNormal=FALSE;
		bDrawTab=FALSE;
		bDrawNormalDock=FALSE;
	}
	~CMiniDock(){}

protected:
	BOOL m_Drag;
	CRect m_Oldrc; //Old Rect Normal float
	CRect m_OldrcTab; //Old Rect Tab
	CRect m_OldrcDock; //Old Rect Docking
	CRect mWin;
	BOOL	bDrawNormal;
	BOOL	bDrawTab;
	BOOL	bDrawNormalDock;

	

public:

	virtual void OnNcLButtonDown(UINT nHitTest, CPoint point);
	
	virtual void OnNcLButtonUp(UINT nHitTest, CPoint point);
	
	virtual void OnNcMouseMove(UINT nHitTest, CPoint point);
	virtual void OnMouseMove(UINT nHitTest, CPoint point);
	virtual void OnNcButtonDblClk(UINT nHitTest, CPoint point);
	virtual void OnLButtonUp(UINT nHitTest, CPoint point);
	virtual void OnWindowPostChanging(LPWINDOWPOS lpWindowsPos);
	virtual void OnRButtonDown(UINT nHitTest, CPoint point);
  	virtual void DrawFrame(CRect rc, BOOL bDrawTab=0);
	void DrawNormal();
	void DrawDock(CRect rc,CPoint point,DockManager* mDock, UINT bHorz);
	virtual void OnKeyDown(int iVkey, DWORD dTime);
 
};


class CDockPanelBase : public CWin
{
public:
	CRect rcPosition;
	UINT  uAling;
	int	  iLasPosition;
	BOOL  bIsPartOfTabbed;
	BOOL  bIsShow;
	UINT   m_IdCtrlParent;	

public:
	CDockPanelBase(HWND hWnd=NULL)
	{
		m_hWnd=hWnd;
		rcPosition=CRect(0,0,0,0);
		bIsShow=TRUE;
		uAling=-1;
		iLasPosition=-1;
		bIsPartOfTabbed=FALSE;
		m_IdCtrlParent=0;
		
	}


public:

	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWin* pParentWnd, UINT nID,LPCTSTR lpCaption=_T("")) 
	{
		LPCTSTR lpclassname=RegisterDefaultClass(NULL,WS_CHILD|WS_VISIBLE);
		return CWin::Create(lpclassname, lpCaption, dwStyle, rect, pParentWnd->GetSafeHwnd(), nID);
	}


	virtual BOOL OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		return TRUE;
	}

	virtual BOOL OnSize(UINT nType,long x, long y)
	{
		UpdatePanel();
		Invalidate();
		UpdateWindow();
		Default();
		return TRUE;
	}

	virtual BOOL OnPaint(HDC hDC)
	{
		Default();
		return TRUE;
	}

	virtual void UpdatePanel()
	{
		
	}

	 virtual void SaveConfig()
	 {
	    CRect rc;
		TCHAR szSection[512];
		wsprintf(szSection, _T("%s-BaseDockBar-%d"), theApp->m_lpBuffer,GetDlgCtrlID());
		GetWindowRect(rc);
		WriteInteger(rc.left,szSection, _T("Left"));
		WriteInteger(rc.right,szSection, _T("Right"));
		WriteInteger(rc.top,szSection, _T("Top"));
		WriteInteger(rc.bottom,szSection, _T("Bottom"));
		WriteInteger(bIsShow,szSection, _T("IsVisible"));
		WriteInteger(uAling,szSection, _T("Aling"));
		WriteInteger(iLasPosition,szSection, _T("LasPosition"));
		WriteInteger(bIsPartOfTabbed,szSection, _T("IsPartofTabbed"));
		WriteInteger(m_IdCtrlParent,szSection, _T("CtrlIDParent"));

	 }

	 virtual  void GetConfig()
	 {

		TCHAR szSection[512];
		wsprintf(szSection, _T("%s-BaseDockBar-%d"), theApp->m_lpBuffer,GetDlgCtrlID());
		
		rcPosition.left=ReadInteger(szSection, _T("Left"));
		rcPosition.right=ReadInteger(szSection, _T("Right"));
		rcPosition.top=ReadInteger(szSection, _T("Top"));
		rcPosition.bottom=ReadInteger(szSection, _T("Bottom"));
		bIsShow=(BOOL)ReadInteger(szSection, _T("IsVisible"));
		uAling=(UINT)ReadInteger(szSection, _T("Aling"));
		iLasPosition=(BOOL)ReadInteger(szSection, _T("LasPosition"));
		bIsPartOfTabbed=(BOOL)ReadInteger(szSection, _T("IsPartofTabbed"));
		m_IdCtrlParent=(UINT)ReadInteger(szSection, _T("CtrlIDParent"));

	   	if (rcPosition.left <0 || rcPosition.right < 0 || rcPosition.bottom <= 0 || rcPosition.right <= 0)
			rcPosition=CRect(0,0,120,120);
		
		
	 }

	 virtual BOOL OnDestroy()
	 {
		 SaveConfig();
		 return TRUE;
	 }

BEGIN_MSG_MAP()
	 ON_WM_CREATE(OnCreate)
	 ON_WM_SIZE(OnSize) 
	 ON_WM_PAINT(OnPaint)
	
END_MSG_MAP(CWin)
};


class CDockStruct
{
public:
	CDockStruct(CWin* pParent)
	{
		if (!HIWORD(pParent)) return;
		m_WinDock=pParent;
		m_rectPost=CRect(0,0,0,0);

	}
public:
	CRect m_rectPost;
	CWin* m_WinDock;

};


class CContainer;
class DockAutoHide : public CWin
{
public:
	DockAutoHide();
	~DockAutoHide();
	
public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWin* pParentWnd, UINT nID);
	void AddWindow(CWin* pWin);
	void RecalLayout();
  	void DrawTextVert(CGDI* pDC, CRect m_rect,LPCSTR m_Caption);
public:
	 BOOL OnPaint(HDC hDC);
	 BOOL OnLButtonDown(UINT nFlags, CPoint pt);
	 BOOL OnSize(UINT nType, int cx, int cy);
	 BOOL OnEraseBkgnd(HDC hDC );
	 int  OnDestroy();
	 BOOL OnLButtonUp(UINT nFlags, CPoint pt);
	 void OnMouseMove(UINT nHitTest, CPoint point);

protected:
  CArray m_DockWindows; 
  int			n_numBars;
  CWin*			pParent;
  UINT			m_uID;
protected:

BEGIN_MSG_MAP()
	ON_WM_ERASEBKGND(OnEraseBkgnd)
	ON_WM_PAINT(OnPaint)
	ON_WM_SIZE(OnSize)
	ON_WM_LBUTTONDOWN(OnLButtonDown)
	ON_WM_DESTROY(OnDestroy)
	ON_WM_LBUTTONDOWN(OnLButtonDown)
	ON_WM_LBUTTONUP(OnLButtonUp)
	ON_WM_MOUSEMOVE(OnMouseMove)
END_MSG_MAP(CWin)

};

class DockManager : public CWin
{

public:
	DockManager();
	~DockManager();
	
public:
  CMiniDock* m_MiniFloat;

public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWin* pParentWnd, UINT nID);
	void AddWindow(CWin* pWin,int nPos=-1);
	UINT AddWindow(CDockPanelBase* pWin,UINT dlgCtrl=NULL,int nPos=-1);
	void FloatWindow(CWin *pWin);
	void DeleteWindow(int pWin);
	void RecalLayout(BOOL bReSize=FALSE);
	void DrawSppliter(CRect rc);
	void DrawSppliterInside(CPoint cp);
	BOOL IsFloating();
	BOOL IsVertical();
	BOOL IsHorz();
	BOOL IsLeft();
	BOOL IsRight();
	int  FindItem(HWND hWnd);
	CWin* GetNumWnd(int m_numWin); 
	int  GetNumChild();
	CSize Getsize();
	void CalSizeWindow();
	void EveryWindowsInsert();
	int  GetNumVisibleWindows();
	void ResizeWindow(CPoint cp);
	int GetFirstVisible();
	int GetLastVisible();
	CContainer*  GetWichContainerIsTheParent(HWND hWnd);
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
	 void OnTimer(UINT nIDEvent);
	 void OnNcLButtonDown(UINT nHitTest, CPoint point);
	 void OnNcLButtonUp(UINT nHitTest, CPoint point);
	 BOOL OnLButtonUp(UINT nFlags, CPoint pt);
	 void OnMouseMove(UINT nHitTest, CPoint point);
	 BOOL ShowMe(){return m_ShowMe;};
	 CContainer* PointIsInCaption(CPoint cp);
	 int PointInDock(CPoint cp, CRect& rc, int& pos);
protected:

   CArray m_DockWindows; 
   NewBValArray<CRect> m_Splits; 
  DWORD			m_Aling;		//Actual Aling
  DWORD			m_lastAling;	//before float where was the windows
  DWORD			m_Side;
  BOOL			m_Visible;		//Is the Windows visible 
  CMiniDock*	m_MiniDock;		
  CRect			m_Splitter;	
  CRect			m_OldSplitter;
  CSize			m_size;
  CWin*			m_pParent;
  int			m_NumWins;
  int			m_NumSep;
  BOOL			m_DragSplitter;
  BOOL			m_DragSplitterInside;
  CPoint		m_ptStartPos;
  CPoint		m_ptOldPos;
  int			m_SplitMove;
  BOOL			m_ShowMe;
  

protected:

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
	ON_WM_NCMOUSEMOVE(OnNcMouseMove)
	ON_WM_TIMER(OnTimer)
	ON_WM_NCLBUTTONUP(OnNcLButtonUp)
	ON_WM_LBUTTONUP(OnLButtonUp)
	ON_WM_MOUSEMOVE(OnMouseMove)
END_MSG_MAP(CWin)

};

/*
 *  <class> CChildWnd </class>
 *  <Description> Wrapper de una ventana hija, para programas MDI
 *  </Description>
 *  <Author> Francisco Campos </Author>
 *  <Version> 23/09/2003 v 1.0 </Version>
 *  <Modified>  </Modified>
 *****/



class CChildWnd : public CFrame
{
	HMENU hMenu;
public:
	CChildWnd(HWND hWnd=NULL): CFrame(hWnd)
	{bChildWnd=TRUE;}
	virtual BOOL LoadFrame(UINT uID,HWND hParentWnd=NULL,DWORD dwStyle=WS_VISIBLE|WS_CHILD|WS_OVERLAPPEDWINDOW);
	virtual  LRESULT DefWindowProc(HWND hWnd, UINT uID, WPARAM wParam, LPARAM lParam);
	void MDIActivate(HWND hWndActivate,LPARAM lParam);
	void MDIMaximize(HWND hWndActivate);
BEGIN_MSG_MAP()
  ON_WM_MDIACTIVATE(MDIActivate)
  ON_WM_MDIMAXIMIZE(MDIMaximize)	
END_MSG_MAP(CFrame)

};



/*
 *  <class> CFrameMDI </class>
 *  <Description> Esta clase contiene el marco para una aplicacion MDI    
 *  </Description>
 *  <Author> Francisco Campos </Author>
 *  <Version> 23/09/2003 v 1.0 </Version>
 *  <Modified>  </Modified>
 *****/
class CFrameMDI : public CFrame
{

protected:
	CLIENTCREATESTRUCT ccs;
public:

	CFrameMDI(HWND hWnd) : CFrame(hWnd)
	{
		hMDIClient=NULL;
	}
	
	~CFrameMDI()
	{
	
	};

	virtual BOOL LoadFrame(UINT uID,DWORD dwStyle=WS_OVERLAPPEDWINDOW,HWND hParentWnd=NULL);
	HWND MDIGetActive(BOOL* pbMaximized);
	void MDIActivate(HWND hWndActivate,LPARAM lParam);
	void MDIIconArrange();
	void MDIMaximize(HWND hWndParent);
	void MDINext();
	void MDIRestore(HWND hWndParent);
	HMENU MDISetMenu(HMENU hMenuParent, HMENU hMenuWindow);
	void MDITile();
	void MDICascade();
	void MDICascade(int nType);
	void MDITile(int nType);
	virtual  LRESULT DefWindowProc(HWND hWnd, UINT uID, WPARAM wParam, LPARAM lParam);
	BOOL OnCreate(LPCREATESTRUCT lpCreateStruct);
	BOOL WindowsPosChanged(LPWINDOWPOS lpWindowsPos);
	void OnCloseChild();
	
BEGIN_MSG_MAP()
	 ON_WM_WINDOWPOSCHANGED (WindowsPosChanged)
	 ON_WM_CREATE(OnCreate)
	 ON_WM_MDIMAXIMIZE(MDIMaximize)
END_MSG_MAP(CFrame)

 
};



/*
 *
 *  CHookMenu
 *
 ****/

// if you want to learn more about it go to
//http://msdn.microsoft.com/library/default.asp?url=/library/en-us/dnwui/html/msdn_hooks32.asp
//http://msdn.microsoft.com/library/default.asp?url=/library/en-us/winui/WinUI/WindowsUserInterface/Windowing/Hooks/UsingHooks.asp

class CHookMenu
{
protected:
	
	static HHOOK hHook; 
	HWND  m_hWnd;
public:
    CHookMenu (HWND hWnd): m_hWnd(hWnd){};
   ~CHookMenu ();

private:
	
    static LRESULT CALLBACK CallWndProc (int code, WPARAM wParam, LPARAM lParam)
	{
	  
	    CWPSTRUCT* pst = (CWPSTRUCT*)lParam;
	
	    while ( code == HC_ACTION )
	    {
		
		if ( pst->message != WM_CREATE && pst->message != 0x01E2 )
		    break; // isn't our bussines
		
		TCHAR sClassName[10];
		::GetClassName (pst->hwnd, sClassName,10);
		if ( _tcscmp( sClassName, _T( "#32768" ))!=0)
			break; // isn't our bussines
		if ( ::GetProp( pst->hwnd,_T("SWC_OLDPROCMENU")) != NULL )
			break;					
		//w'll need this  proc in the subWndProc, thi's the original menu dialog procedure
		WNDPROC OldProc = (WNDPROC)::GetWindowLong (pst->hwnd, GWL_WNDPROC);
		if ( !OldProc ) break; //something is wrong
		if ( !SetProp (pst->hwnd, _T("SWC_OLDPROCMENU"), OldProc) ) break;  
		
		if ( !::SetWindowLong (pst->hwnd, GWL_WNDPROC, (DWORD)(unsigned long)SubWndProc) )
		{
		    ::RemoveProp (pst->hwnd, _T("SWC_OLDPROCMENU"));
		    break;
		}
		
		break;
	    }
	    return CallNextHookEx (hHook, code, wParam, lParam);
	}
	

    static LRESULT CALLBACK SubWndProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
	    WNDPROC oldWndProc = (WNDPROC)::GetProp (hWnd, _T("SWC_OLDPROCMENU"));
	    HWND hWndg = ::GetParent(hWnd);
		int Opc=theApp->m_WinMain->cSpawn.fltMenu.iCmd;
		if (Opc==-4)	
			theApp->m_WinMain->m_SubMenuActual=hWnd;
	    switch ( uMsg )
	    {
	     		
		case WM_WINDOWPOSCHANGING:
			{
				WINDOWPOS* pWP=(LPWINDOWPOS)lParam;
				pWP->cx--;
				pWP->cy--;
			}
	    case WM_PRINT:
			{

				CGDI	dc((HDC)wParam);
				CRect rect;
				CGDI		m_dc;	
				CBitmap		m_bitmap;
				CPen pen;
				CWindowDC dcw;
				dc.GetClipBox(rect);
				
				m_dc.CreateCompatibleDC(dc.m_hDC);
				m_bitmap.CreateCompatibleBitmap(dc.m_hDC,rect.Width(),rect.Height());
				CBitmap m_OldBitmap=m_dc.SelectObject(&m_bitmap);
				//aqui debe utilizarse la brocha que define CDrawLayer, si no hacemos la siguiente
				//linea usted vera un horrible color negro, a cambio del dibujo.
				
				HBRUSH hb=(HBRUSH)::SelectObject(m_dc.m_hDC,::GetStockObject(NULL_BRUSH));
				CBrush cb;
				::SendMessage( hWnd, WM_ERASEBKGND,  ( WPARAM )( HDC )m_dc.m_hDC, 0 );
				::SendMessage( hWnd, WM_PRINTCLIENT, ( WPARAM )( HDC )m_dc.m_hDC, lParam );
				//LRESULT lResult = CallWindowProc (oldWndProc, hWnd, uMsg,(WPARAM)m_dc.m_hDC, lParam);
				pen.CreatePen(PS_SOLID,1,CDrawLayer::GetRGBColorShadow());
				CPen cpen=m_dc.SelectObject(&pen);
				m_dc.Rectangle(rect);
				rect.DeflateRect(1,1);
				m_dc.Draw3dRect(rect,CDrawLayer::GetRGBColorWhite(),CDrawLayer::GetRGBColorWhite());
				rect.DeflateRect(1,1);
				m_dc.Draw3dRect(rect,CDrawLayer::GetRGBColorWhite(),CDrawLayer::GetRGBColorWhite());
				rect.InflateRect(2,2);
				::SelectObject(m_dc.m_hDC,hb);
				m_dc.SelectObject(&cpen);
				dc.BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),m_dc.m_hDC,0L,0L,SRCCOPY);
				cpen.DeleteObject();
				m_dc.SelectObject(&m_OldBitmap);
				m_bitmap.DeleteObject();
				m_OldBitmap.DeleteObject();
				cb.DeleteObject();
				m_dc.DeleteDC();
				dc.DeleteDC();
				return 0;	
			}
		break;

	    case WM_NCPAINT:
			{

				CRect rect;
				CWindowDC dc(hWnd);
				CPen pen;
				int Opc=theApp->m_WinMain->cSpawn.fltMenu.iCmd;
				theApp->m_WinMain->cSpawn.fltMenu.iCmd=-1;
				HBRUSH hb=(HBRUSH)::SelectObject(dc.m_hDC,::GetStockObject(NULL_BRUSH));
				dc.GetClipBox(rect); CRect rect1=rect;
				pen.CreatePen(PS_SOLID,1,CDrawLayer::GetRGBColorShadow());
				CPen cpen=dc.SelectObject(&pen);
				dc.Rectangle(rect);
				rect.DeflateRect(1,1);
				dc.Draw3dRect(rect,CDrawLayer::GetRGBColorWhite(),CDrawLayer::GetRGBColorWhite());
				rect.DeflateRect(1,1);
				int bottom =rect.bottom;
				rect.bottom=rect.top+1;
				dc.Draw3dRect(rect,CDrawLayer::GetRGBColorWhite(),CDrawLayer::GetRGBColorWhite());
				rect.bottom=bottom;
				rect.left=rect.right-1;
				dc.Draw3dRect(rect,CDrawLayer::GetRGBColorWhite(),CDrawLayer::GetRGBColorWhite());
				if (theApp->m_WinMain->m_SubMenuActual==hWnd)//;Opc==-4)
				{
					rect1.left+=1;
					rect1.right=rect1.left+theApp->m_WinMain->cSpawn.fltMenu.Width-1;
					rect1.bottom=rect1.top;
					dc.Draw3dRect(rect1,CDrawLayer::GetRGBColorXP(),CDrawLayer::GetRGBColorXP());
					
				}
				dc.SelectObject(&cpen);
				::SelectObject(dc.m_hDC,hb);
				pen.DeleteObject();
				cpen.DeleteObject();
				dc.DeleteDC();	
				return 0;	
			}
		break;
	
	    case WM_NCCALCSIZE:
		{
		    LRESULT lResult = CallWindowProc (oldWndProc, hWnd, uMsg, wParam, lParam);
		    NCCALCSIZE_PARAMS*  pCalcSize = ( NCCALCSIZE_PARAMS*  )lParam;	
		    pCalcSize->rgrc[0].left -= 1;
		//	pCalcSize->rgrc[0].right -=1;
		    pCalcSize->rgrc[0].bottom += 1;
		    return lResult;
		}
	}
	    return CallWindowProc (oldWndProc, hWnd, uMsg, wParam, lParam);
}	



public:
	static void InstallHook()
	{
		hHook = ::SetWindowsHookEx (WH_CALLWNDPROC, CallWndProc,theApp->GetInstance(), ::GetCurrentThreadId());
	}
	
	static void UnInstallHook()
	{
		if ( hHook)
		        ::UnhookWindowsHookEx (hHook);
		
	}
protected:
    
  void OnWindowPosChanging (WINDOWPOS* pWP);
  void OnEraseBkgnd ();
  void OnPrint (CWindowDC wDC, bool bOwnerDrawnItems);
  void OnNcPaint ();
  void OnNcDestroy ();
    
};


//----------------------------------------------

class CHookMouse
{
protected:
	
	static HHOOK hHook; 
	HWND  m_hWnd;
	static BOOL  m_NCMousePress;
public:
    CHookMouse (HWND hWnd): m_hWnd(hWnd){ m_NCMousePress=FALSE;};
   ~CHookMouse ();

private:
	

static LRESULT CALLBACK CallWndProc(int nCode, WPARAM wParam, LPARAM lParam) 
{ 
    if(nCode == HC_ACTION) 
    { 
      
        PMOUSEHOOKSTRUCT pms = (PMOUSEHOOKSTRUCT) lParam; 
        
         switch(wParam) 
        { 
            case WM_NCLBUTTONDOWN: 
                {
                    if((pms->hwnd == theApp->m_WinMain->GetSafeHwnd()) 	&& (pms->wHitTestCode == HTCAPTION)) 
                        m_NCMousePress = TRUE;
                      
                }
                break;

            case WM_NCLBUTTONUP: 
                m_NCMousePress = FALSE; 
                break; 

            case WM_LBUTTONUP: 
                {
                    if((pms->hwnd == theApp->m_WinMain->GetSafeHwnd()) && ( m_NCMousePress == TRUE))
                    {
                         theApp->m_WinMain->PostMessage(WM_NCLBUTTONUP, HTCAPTION, MAKELONG(pms->pt.x, pms->pt.y)); 
						 m_NCMousePress=FALSE;
                    }
                } 
                break; 

            default: 
                break; 
        } 
    } 
   
	return CallNextHookEx(hHook, nCode, wParam, lParam); 
}

public:
	static void InstallHook()
	{

		hHook = ::SetWindowsHookEx (WH_MOUSE, CallWndProc,theApp->GetInstance(), ::GetCurrentThreadId());
	}
	
	static void UnInstallHook()
	{
		if ( hHook)
		        ::UnhookWindowsHookEx (hHook);
		
	}
};
#endif