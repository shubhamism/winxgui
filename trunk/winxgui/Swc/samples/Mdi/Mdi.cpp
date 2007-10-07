// Mdi.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include <time.h>
#include  <stdio.h>

HHOOK CHookMenu::hHook=NULL;
// BeyonClass.cpp : Defines the entry point for the application.
//


#define HELLO 0x1111
#define IDPANEL0  60
#define IDPANEL1  20
#define IDPANEL2  20


int  Panels[]={ IDPANEL0,IDPANEL1,IDPANEL2};


class ChildHello : public CChildWnd
{

	HWND m_edit;
public:
	ChildHello(HWND hWnd=NULL): CChildWnd(hWnd)
	{}

	BOOL OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		
		m_edit= CreateWindowEx(0,"EDIT","",
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
			0,0,100,100,GetSafeHwnd(),(HMENU)HELLO,GetModuleHandle(NULL),NULL);
		return 0;
	}

	BOOL OnSize(UINT nType,long x, long y)
	{
		CRect rc1;
		GetClientRect(rc1);
		HWND hW=GetChild();
		::SetWindowPos(hW,NULL,rc1.left,rc1.top,rc1.Width(),rc1.Height(),SWP_NOZORDER);
		return TRUE;
	}

	
	void OnChangeEdit1(int wHp, int wLp, HWND hControl)
	{
	
	}

BEGIN_MSG_MAP()

	 ON_WM_CREATE(OnCreate)
	 ON_WM_SIZE(OnSize) 
	 ON_COMMAND_CONTROL(HELLO,EN_CHANGE, OnChangeEdit1)
	
END_MSG_MAP(CChildWnd)

};




class CAbout : public CDialog
{
	CEdit m_edit;
public:
	CAbout(){};
	~CAbout(){};
	virtual BOOL OnInitDialog(HWND wParam,LPARAM lParam);
	virtual BOOL OnOK(WPARAM wParam, LPARAM lParam, HWND hWnd);
	virtual BOOL OnCancel(WPARAM wParam, LPARAM lParam, HWND hWnd);
	
BEGIN_MSG_MAP()
	ON_WM_INITDIALOG(OnInitDialog)
	ON_COMMAND(IDOK,OnOK)
	ON_COMMAND(IDCANCEL,OnCancel)
END_MSG_MAP(CDialog)
};


BOOL CAbout::OnInitDialog(HWND wParam,LPARAM lParam)
{
	LINK_Control(IDC_EDIT,m_edit);
	return TRUE;
}

BOOL CAbout ::OnOK(WPARAM wParam, LPARAM lParam, HWND hWnd)
{
	char* lpText=(char*)malloc(200);
	m_edit.GetWindowText(lpText,20);
	MsgBox(lpText);
	CDialog::OnOK();	
	return TRUE;
}

BOOL CAbout ::OnCancel(WPARAM wParam, LPARAM lParam, HWND hWnd)
{
	CDialog::OnCancel();
	return TRUE;
}


class CWinFrame: public CFrameMDI
{
	CToolBarCtrlEx    m_ToolBar;
	CToolBarCtrlEx    m_ToolBar1;
	CListView	m_up;
	CMiniFrame		m_Mini;
public:

	CWinFrame(HWND hWnd=NULL):CFrameMDI(hWnd){}
	BOOL OnClose();
	BOOL OnCreate(LPCREATESTRUCT lpCreateStruct);
	BOOL OnSize(UINT nType,long x, long y);
	
	
	void OnNew(WPARAM wParam, LPARAM lParam, HWND hWnd)
	{
		ChildHello* child=new ChildHello();
		if (!child->LoadFrame(IDR_MENUHELLO,GetSafeClientHwnd()))
			return;
		
		
	}
	
	void OnExit(WPARAM wParam, LPARAM lParam, HWND hWnd)
	{
		SendMessage(WM_CLOSE,0,0);
	}

	void Cascade(WPARAM wParam, LPARAM lParam, HWND hWnd)
	{
		MDICascade();
	}

	void OnToolBar(WPARAM wParam, LPARAM lParam, HWND hWnd)
	{
		OnShowBand(m_ToolBar.GetSafeHwnd());
		
	}

	void OnFileClose(WPARAM wParam, LPARAM lParam, HWND hWnd)
	{
		OnCloseChild();
	}

	void OnFileOpen(WPARAM wParam, LPARAM lParam, HWND hWnd)
	{
		CFileOpen co(this);
		co.DoModal(TRUE);
	}
	void OnAbout(WPARAM wParam, LPARAM lParam, HWND hWnd)
	{
		CAbout cb;
		cb.DoModal(this,(LPCTSTR)IDD_ABOUTBOX);
	}

	void OnTitle(WPARAM wParam, LPARAM lParam, HWND hWnd)
	{
		MDITile();
	}

	
/*	virtual LRESULT OnMeasureItem(LPMEASUREITEMSTRUCT lpms)
	{
		return CFrame::OnMeasureItem(lpms);
	}
	virtual BOOL OnDrawItem(LPDRAWITEMSTRUCT lpds)
	{
		return CFrame::OnDrawItem(lpds);
	}
*/	

BEGIN_MSG_MAP()
	 ON_WM_CREATE(OnCreate)
	 ON_COMMAND(ID_FILE_NEW,OnNew)
	 ON_WM_SIZE(OnSize) 
	 ON_COMMAND(ID_WINDOW_CASCADE,Cascade)
	 ON_COMMAND(ID_TOOLBAR,OnToolBar)
	 ON_COMMAND(IDM_EXIT,OnExit)
	 ON_COMMAND(ID_FILE_CLOSE,OnFileClose)
	 ON_COMMAND(ID_FILE_OPEN,OnFileOpen)
	 ON_COMMAND(ID_WINDOW_TILE_HORZ,OnTitle)
	 ON_COMMAND(IDM_ABOUT,OnAbout);
	 ON_WM_CLOSE(OnClose)
//	 ON_WM_DRAWITEM(OnDrawItem)
//	 ON_WM_MEASUREITEM(OnMeasureItem) 
END_MSG_MAP(CFrameMDI)

};

 
BOOL CWinFrame::OnSize(UINT nType,long x, long y) 
{
	CFrameMDI::OnSize(nType,x,y);
	return TRUE;
}
	


BOOL CWinFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CFrameMDI::OnCreate(lpCreateStruct);

	if (!CreateExBars(Panels,3))
		return -1;
	if ( !m_ToolBar.Create(m_ReBar->GetSafeHwnd(),IDR_TOOLBAR))
		return -1;

	if ( !m_ToolBar1.Create(m_ReBar->GetSafeHwnd(),IDR_TOOLBAR1))
		return -1;

	//m_ToolBar.AddButtonText(ID_FILE_NEW, _T("Hola"));
	m_ToolBar.LoadToolBar(IDR_TOOLBAR);
	m_ToolBar1.LoadToolBar(IDR_TOOLBAR1);	
	AddBar(&m_ToolBar, IDR_TOOLBAR);
	AddBar(&m_ToolBar1, IDR_TOOLBAR1);
	m_ToolBar.AddTrueColor(IDB_TOOLBAR,TB_SETIMAGELIST);
	m_ToolBar1.AddTrueColor(IDr_BITMAP1,TB_SETIMAGELIST);
	SetPanelText(0,_T("Ready") );
	SetIcon(theApp->LoadIcon((LPCSTR)IDI_SMALL),FALSE);
	// COOLMENU SUPPORT
	cSpawn.LoadToolBarResource(IDR_TOOLBAR,IDB_TOOLBAR);
//	cSpawn.AddToolBarResource(IDR_SYSTEMBAR);
	cSpawn.AddToolBarResource(IDR_TOOLBAR1);
//	CreateDockBars(); 


	return 0;
}


BOOL CWinFrame::OnClose()
{
	int resp=MsgBox("Esta seguro de Salir","Close",MB_YESNO);
	if (resp==IDYES)
		return CWin::OnDestroy();
	return FALSE;
}



class CAppMain :public CApp 
{
public:
	int InitInstance();
	~CAppMain() 
	{
		CHookMenu::UnInstallHook();
	}
};

int CAppMain::InitInstance()
{

	CHookMenu::InstallHook();	
	m_WinMain=(CFrame*)new CWinFrame(); 

	if (m_WinMain->LoadFrame(IDC_WINCLASS)== FALSE)
		return -1;
	SetMenuResource((LPCTSTR)IDC_WINCLASS);
	LoadMenu((LPCTSTR)IDC_WINCLASS);
//	m_WinMain->cSpawn.RemapMenu(m_Menu.GetHandleMenu());
	// 3D HIGHLIGHT CODE
	m_WinMain->ShowWindow();
	m_WinMain->UpdateWindow();
	hAccelTable = LoadAccelerators( (LPCTSTR)IDC_WINCLASS);
	return Run();
	
	
}



int PASCAL WinMain(HINSTANCE hinstace, HINSTANCE PrehInstance, LPSTR cmdLine, int show)
{
	CAppMain cpMain;
	if (theApp==0) 
		return 0;
	theApp->LoadMain(hinstace, PrehInstance, cmdLine, show);
	return theApp->InitInstance();						
}







