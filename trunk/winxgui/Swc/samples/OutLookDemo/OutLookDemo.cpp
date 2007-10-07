// Splitter.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include "resource.h"
#include <time.h>
#include  <stdio.h>
#include "OutLookDemo.h"

#define HELLO 0x1111
#define IDPANEL0  100
#define IDPANEL1  -1


int  Panels[]={ IDPANEL0,IDPANEL1};


HHOOK CHookMenu::hHook=NULL;
//-------------------------------------------------------------------


BOOL CAbout::OnInitDialog(HWND wParam,LPARAM lParam)
{
	
	LINK_Control(IDOK,m_button);
	
	return TRUE;
}


BOOL CAbout ::OnOK(WPARAM wParam, LPARAM lParam, HWND hWnd)
{
	CDialog::OnOK();	
	return TRUE;
}

BOOL CAbout ::OnCancel(WPARAM wParam, LPARAM lParam, HWND hWnd)
{
	CDialog::OnCancel();
	return TRUE;
}


//--------------------------------------------------------------------

void CWinFrame::OnNew(WPARAM wParam, LPARAM lParam, HWND hWnd)
{
	return;
}


void CWinFrame::OnExit(WPARAM wParam, LPARAM lParam, HWND hWnd)
{
	SendMessage(WM_CLOSE,0,0);
}


void CWinFrame::OnToolBar(WPARAM wParam, LPARAM lParam, HWND hWnd)
{
	if (m_ToolBar.IsWindowVisible())
		m_ToolBar.ShowWindow(FALSE);
	else
		m_ToolBar.ShowWindow();
	

	SendMessage(WM_SIZE,0,0);
	
}

void CWinFrame::OnFileClose(WPARAM wParam, LPARAM lParam, HWND hWnd)
{
}


void CWinFrame::OnAbout(WPARAM wParam, LPARAM lParam, HWND hWnd)
{
	CAbout cb;
	cb.DoModal(this,(LPCTSTR)IDD_ABOUTBOX);
}


void CWinFrame::OnToday(WPARAM wParam, LPARAM lParam, HWND hWnd)
{
	MsgBox(_T("Prueba de outlook"));
}


BOOL CWinFrame::OnSize(UINT nType,long x, long y)
{
	UpdateFrame();
	return TRUE;
}
	


BOOL CWinFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	
	if (!CreateBars(Panels,2))
		return -1;
	
	if ( !m_ToolBar.Create(m_ReBar->GetSafeHwnd()))
		return -1;


	m_ToolBar.LoadToolBar(IDR_TOOLBAR);
	m_ToolBar.AddTrueColor(IDB_TOOLBAR,TB_SETIMAGELIST);
	m_ToolBar.CreateCombo(&m_comboDebug,ID_COMBOBOX,150,WS_CHILD|WS_VISIBLE|CBS_DROPDOWN  | 
							WS_VSCROLL | CBS_HASSTRINGS |CBS_OWNERDRAWVARIABLE);

	AddBar(&m_ToolBar, IDR_TOOLBAR);

	SetPanelText(0,_T("nueva cadena ") );
	SetIcon(theApp->LoadIcon((LPCSTR)IDI_SMALL),FALSE);

	if (!m_Splitter.Create(this))
			return -1;

	if (!m_Splitright.Create(&m_Splitter))
		return -1;
	
	if (!m_SplitterList.Create(&m_Splitright))
		return -1;

	if (!cf.Create( &m_Splitter, CRect(0,0,0,0) ,WS_CHILD|WS_VISIBLE, 1000))
		return -1;

	if (!tc.Create(cf.GetSafeHwnd(),WS_CHILD | WS_VISIBLE | TVS_HASLINES | 
								TVS_LINESATROOT | TVS_HASBUTTONS, 2))
		return -1;

	if (!FolderList.Create(m_Splitright.GetSafeHwnd(),WS_CHILD | WS_VISIBLE | TVS_HASLINES | 
								TVS_LINESATROOT | TVS_HASBUTTONS, 2))
		return -1;
	
	
	if (!out2.Create(WS_VISIBLE,
		CRect(0,0,0,0), &cf, 1))
		return -1;
	
	if (!out1.Create(WS_VISIBLE,
		CRect(0,0,0,0), &cf, 2))
		return -1;
	out1.SetTypeLook(FALSE);
	if (!m_up.Create(m_SplitterList.GetSafeHwnd(), WS_CHILD|WS_VISIBLE, 1000))
		return -1;
	
	if (!m_down.Create(m_SplitterList.GetSafeHwnd(), WS_CHILD|WS_VISIBLE, 2000))
		return -1;

	

	out2.SetImageList(IDB_BITMAP1, 32, 0, RGB(255,0,0));
	out2.AddItem(IDO_OUTODAY,"Home",7);
	out2.AddItem(IDO_CALENDARIO,"Calendar",1);
	out2.AddItem(IDO_CONTACTO,"Contacts",2);
	out2.AddItem(IDO_TAREAS,"Tasks",3);
	out2.AddItem(IDO_NOTAS,"Notes",5);
	out2.AddItem(IDO_ELIMINAR,"Delete",6);
	
	cf.AddFolder(&out2,"Outlook Shortcuts");
	cf.AddFolder(&tc,"Other Shortcuts");
	
	m_Splitter.SetStyleSeparator(CSplitter::STYLE3D);

	m_Splitright.SeTypeALing(CSplitter::ALINGHORZ);
	m_Splitright.AddLeftCtrl(&m_up,3);
	m_Splitright.AddRightCtrl(&m_down,4);
	m_Splitright.SetStyleSeparator(CSplitter::STYLEFLAT);
	
	m_SplitterList.SeTypeALing(CSplitter::ALINGVERT);

	m_up.Create (m_SplitterList.GetSafeHwnd(),WS_CHILD | WS_VISIBLE | WS_VSCROLL | LVS_REPORT,7000);
	m_up.SendMessage (LVM_SETEXTENDEDLISTVIEWSTYLE, 0,LVS_EX_FULLROWSELECT );
	m_up.InsertColumn (0, _T("From"), LVCFMT_LEFT, 100,0);
	m_up.InsertColumn (1, _T("Subject"), LVCFMT_LEFT, 200,0);
	m_up.InsertColumn (2, _T("Received"), LVCFMT_LEFT, 100,0);
	m_up.InsertItemText (0, _T("francisco.campos"));
	m_up.InsertItemText (0, 1, _T("Pretty Winapi Class has been launched"));
	m_up.InsertItemText (0, 2, _T("May 30, 2007"));
	m_up.InsertItemText (1, _T("user@mymail.com"));
	m_up.InsertItemText (1, 1, _T("Bugs reporting"));
	m_up.InsertItemText (1, 2, _T("May 29, 2007"));

	//subclass the Header list
	HWND hWndHeader = m_up.GetDlgItem(0);
	m_header.SubclassWnd(hWndHeader);

	m_Splitter.AddLeftCtrl(&cf,200);
	m_Splitter.AddRightCtrl(&m_Splitright,400);
	m_Splitright.AddLeftCtrl(&FolderList,150);
	m_Splitright.AddRightCtrl(&m_SplitterList,350);
	m_SplitterList.AddLeftCtrl(&m_up,400);
	m_SplitterList.AddRightCtrl(&m_down,200);
	m_ClientView=(CSplitter*)&m_Splitter;
	cSpawn.LoadToolBarResource(IDR_TOOLBAR,IDB_TOOLBAR);

	//--------------------populate the tree

	if(!Image.CreateColor(IDB_TREE)) 
			return FALSE;
	FolderList.SetImageList(Image.GetImageHandle(),TVSIL_NORMAL);
	//FolderList.SetImageList(IDB_TREE, 32, 0, RGB(255,0,0));
	HTREEITEM hRoot = FolderList.InsertItem (_T("Outlook Today"), 0, 0);
		
		FolderList.InsertItem (_T("Calendar"), 1, 1, hRoot);
		FolderList.InsertItem (_T("Drafts"), 2, 2, hRoot);
		FolderList.InsertItem (_T("Inbox"), 3, 3, hRoot);
		FolderList.InsertItem (_T("Journal"), 4, 4, hRoot);
		FolderList.InsertItem (_T("Notes"), 5, 5, hRoot);
		FolderList.InsertItem (_T("Outbox"),6, 6, hRoot);
		FolderList.InsertItem (_T("Send Items"), 7, 7, hRoot);
		FolderList.InsertItem (_T("Tasks"), 8, 8, hRoot);
		FolderList.Expand (hRoot, TVE_EXPAND);
	//--------------------End populate tree	
	
	//--------------------populate the tree2

	tc.SetImageList(Image.GetImageHandle(),TVSIL_NORMAL);
	//FolderList.SetImageList(IDB_TREE, 32, 0, RGB(255,0,0));
	HTREEITEM hRoot1 = tc.InsertItem (_T("My PC"), 9, 9);
		
		tc.InsertItem (_T("Program Files"), 10, 10, hRoot1);
		tc.InsertItem (_T("Temp"), 10, 10, hRoot1);
		tc.InsertItem (_T("Windows"), 10, 10, hRoot1);
		tc.InsertItem (_T("Winold"), 10, 10, hRoot1);
		tc.Expand (hRoot1, TVE_EXPAND);
	//--------------------End populate tree	
	return 0;
}


BOOL CWinFrame::OnClose()
{
	int resp=MsgBox("Esta seguro de Salir","Close",MB_YESNO);
	if (resp==IDYES)
		return CWin::OnDestroy();
	return FALSE;
}




int CAppMain::InitInstance()
{
	CHookMenu::InstallHook();	
	
	CRect rc=CRect(10,10,840,840);

	m_WinMain=(CFrame*)new CWinFrame; 

	if (m_WinMain->LoadFrame(IDC_OUTOOLKDEMO)== FALSE)
		return -1;
	LoadMenu((LPCTSTR)IDC_OUTOOLKDEMO);
	m_WinMain->SetWindowPos(NULL,50,50,600,400 ,SWP_SHOWWINDOW);
	
	m_WinMain->ShowWindow();
	m_WinMain->UpdateWindow();
	hAccelTable = LoadAccelerators( (LPCTSTR)IDC_OUTOOLKDEMO);
	return Run();
	
	
}


//----------------------------------------------------------


int PASCAL WinMain(HINSTANCE hinstace, HINSTANCE PrehInstance, LPSTR cmdLine, int show)
{
	CAppMain cpMain;
	if (theApp==0) 
		return 0;
	theApp->LoadMain(hinstace, PrehInstance, cmdLine, show);
	return theApp->InitInstance();						
}

