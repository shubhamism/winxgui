#include "stdafx.h"
#include "resource.h"
#include "PWcStudio.h"
//---------------------
//CDialog Functions
//---------------------

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

//---------------------------
//CFrame functions
//---------------------------
void CWinFrame::OnNew(WPARAM wParam, LPARAM lParam, HWND hWnd)
{
	m_edit = new CEdit();
	if (!m_edit->Create(m_Tabbed.GetSafeHwnd(),IDR_MENUHELLO, _T(""), 
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL|ES_WANTRETURN))
		return;
	m_Tabbed.AddNewtab(m_edit,IDR_MENUHELLO);
	return;
}


void CWinFrame::OnExit(WPARAM wParam, LPARAM lParam, HWND hWnd)
{
	
	SendMessage(WM_CLOSE,0,0);
}


void CWinFrame::OnToolBar(WPARAM wParam, LPARAM lParam, HWND hWnd)
{
	OnShowBand(m_ToolBarMain.GetSafeHwnd());
	

	SendMessage(WM_SIZE,0,0);
	
}


void CWinFrame::OnviewSourceView(WPARAM wParam, LPARAM lParam, HWND hWnd){ShowFloatWindow( m_TreeResource.GetParent());}
void CWinFrame::OnViewHelp(WPARAM wParam, LPARAM lParam, HWND hWnd){/*ShowFloatWindow( m_TreeHelp.GetParent());*/}
void CWinFrame::OnViewToolbox(WPARAM wParam, LPARAM lParam, HWND hWnd){ShowFloatWindow( m_explorer.GetParent());}
void CWinFrame::OnViewClassView(WPARAM wParam, LPARAM lParam, HWND hWnd){ShowFloatWindow( m_TreeClassView.GetParent());}
void CWinFrame::OnOutlook(WPARAM wParam, LPARAM lParam, HWND hWnd){ShowFloatWindow( m_explorer.GetParent());}
void CWinFrame::OnSolutionExplorer(WPARAM wParam, LPARAM lParam, HWND hWnd){ShowFloatWindow( m_explorer.GetParent());}
void CWinFrame::OnWorTabdemo(WPARAM wParam, LPARAM lParam, HWND hWnd){ShowFloatWindow( m_WorkTab.GetParent());}

void CWinFrame::OnFileClose(WPARAM wParam, LPARAM lParam, HWND hWnd)
{
	
}

void CWinFrame::OnFileOpen(WPARAM wParam, LPARAM lParam, HWND hWnd)
{
		CFileOpen co(this);
		co.DoModal(TRUE);
}

void CWinFrame::OnAbout(WPARAM wParam, LPARAM lParam, HWND hWnd)
{
	CAbout cb;
	cb.DoModal(this,(LPCTSTR)IDD_ABOUTBOX);
}



BOOL CWinFrame::OnSize(UINT nType,long x, long y)
{
	UpdateFrame();
	return TRUE;
}
	
BOOL CWinFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//Create CReBar/StatusBars
	
	if (!CreateExBars(Panels,3))
		return -1;

	//Toolbars
	if ( !m_ToolBarMain.Create(m_ReBar->GetSafeHwnd(),IDR_MAINTOOLBAR))
		return -1;

	if ( !m_ToolBarEdit.Create(m_ReBar->GetSafeHwnd(),IDR_BUILD))
		return -1;
	m_ToolBarMain.LoadToolBar(IDR_STANDAR);
	m_ToolBarEdit.LoadToolBar(IDR_BUILD);
	m_ToolBarMain.AddTrueColor(IDB_STANDAR,TB_SETIMAGELIST);
	m_ToolBarEdit.AddTrueColor(IDB_BUILD,TB_SETIMAGELIST);

	if (!m_Tabbed.Create(WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),this,0x333))
		return -1;

	AddBar(&m_ToolBarMain, IDR_MAINTOOLBAR);
	AddBar(&m_ToolBarEdit, IDR_BUILD);
	m_ToolBarMain.CreateCombo(&m_comboDebug,ID_COMBOBOX,150,WS_CHILD|WS_VISIBLE|CBS_DROPDOWN  | 
							WS_VSCROLL | CBS_HASSTRINGS |CBS_OWNERDRAWVARIABLE);
	//Init Statubar 
	SetPanelText(0,_T("Ready ") );
	SetIcon(theApp->LoadIcon((LPCSTR)IDI_SMALL),FALSE);
	//--------------------------------------
	// Tab
	//--------------------------------------
		if (!m_tab.Create(WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),m_DockLeft,0x9999))
			return -1;
	
		if (!m_rtab.Create(WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),m_DockRight,0x9991))
			return -1;

		if (!m_tab_Edit.Create(WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),m_DockLeft,0x9992))
			return -1;
	
		
		if (!m_WorkTab.Create(WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),m_DockBottom,0x9962))
			return -1;
		
		
		if (!m_TreeResource.Create( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 0x9994, _T("Solution Explorer ")))
			return -1;

		if (!m_TreeClassView.Create(WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),m_DockRight,0x9931))
			return -1;
		
		
		if (!m_TreeHelp.Create(m_tab.GetSafeHwnd(),WS_CHILD | WS_VISIBLE | TVS_HASLINES | 
								TVS_LINESATROOT | TVS_HASBUTTONS, 10))
		return -1;


		if (! m_explorer.Create( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 0x99989, _T("Solution Explorer ")))
			return -1;


	
	m_TreeResource.SetWindowText(_T("Resource "));
	m_TreeHelp.SetWindowText(_T("Help "));
	FullfilHelp();
	m_TreeClassView.SetWindowText(_T("Class View "));

	
	
	m_tab.Addtab(&m_TreeHelp,NULL,IDR_MENUOPTION);
	m_tab.SetStyle(CContainer::S3D);
	
	//-------------------------------------
	// WorkTab Bottom
	//-------------------------------------

	if (!m_wtab.Create(WS_CHILD|WS_VISIBLE,
					CRect(0,0,0,0),m_DockBottom , 0x9991)) //m_DockBottom
		return -1;
	

	CRect rectClient (0, 0, lpCreateStruct->cx, lpCreateStruct->cy);

	
	const DWORD dwStyle =   WS_CHILD | WS_VISIBLE | WS_VSCROLL | LVS_REPORT;
	
	
	SetImageDockWindows(IDB_MAINTOOLBAR, 16,16, RGB (192,192,192));
	m_wndDebug.Create (m_wtab.GetSafeHwnd(),dwStyle,2000,_T("Debug "));
	m_wndDebug.SendMessage (LVM_SETEXTENDEDLISTVIEWSTYLE, 0,
								LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_wndDebug.InsertColumn (0, _T("Name"), LVCFMT_LEFT, 200,0);
	m_wndDebug.InsertColumn (1,  _T("Condition"), LVCFMT_LEFT, 100,0);
	m_wndDebug.InsertColumn (2,  _T("Hit Count"), LVCFMT_LEFT, 100,0);		
	m_wndDebug.InsertItemText (0, _T("SimpleWin.cpp, Line 26"));
	m_wndDebug.InsertItemText (0,1, _T("(no condition)"));
	m_wndDebug.InsertItemText (0,2, _T("break always"));
	m_wndDebug.InsertItemText (1, _T("CFolder.cpp, line 20"));
	m_wndDebug.InsertItemText (1,1, _T("(no condition)"));
	m_wndDebug.InsertItemText (1,2, _T("break always (currently 0)"));
	m_wndDebug.InsertItemText (2, _T("CCommonCtrl.h, line 20"));
	m_wndDebug.InsertItemText (2,1, _T("(no condition)"));
	m_wndDebug.InsertItemText (2,2, _T("break always (currently 0)"));

	
	//----------------  ToolBox

	if (!cf.Create( &m_rtab, CRect(0,0,0,0) ,WS_CHILD|WS_VISIBLE, 1000))
		return -1;


	cf.SetWindowText(_T("Toolbox "));
	
	if (!out2.Create(WS_VISIBLE,
		CRect(0,0,0,0), &cf, 1))
		return -1;
	
	if (!out1.Create(WS_VISIBLE,
		CRect(0,0,0,0), &cf, 2))
		return -1;
	
	out1.SetTypeLook(FALSE);
	out2.SetTypeLook(FALSE);

	out2.SetImageList(IDB_DB, 16, 0, RGB(255,0,0));
	out1.SetImageList(IDB_TOOLBOX, 16, 0, RGB(255,0,0));
	out1.AddItem(IDO_POINTER,"Pointer",0);
	out1.AddItem(IDO_LABEL,"Label",1);
	out1.AddItem(IDO_BUTTON,"Button",2);
	out1.AddItem(IDO_TEXTBOX,"TextBox",3);
	out1.AddItem(IDO_MAINMENU,"MainMenu",4);
	out1.AddItem(IDO_CHECHBOX,"Checkbox",5);
	out1.AddItem(IDO_RADIOBUTTON,"Radiobutton",6);
	out1.AddItem(IDO_GROUPBOX,"GroupBox",7);
	out1.AddItem(IDO_PICTUREBOX,"Picture box",8);
	out1.AddItem(IDO_PANEL,"Panel",9);
	out1.AddItem(IDO_DATAGRID,"Datagrid",10);
	out1.AddItem(IDO_LISTBOX,"Listbox",11);

	out2.AddItem(IDO_DBCONNECT,"SqlDbConnect",0);
	out2.AddItem(IDO_DBCOMMAND,"SqlDbCommand",1);
	out2.AddItem(IDO_DBADAPTER,"SqlDbAdapter",2);
	out2.AddItem(IDO_DBCONNECTION,"SqlDbConnection",3);
	out2.AddItem(IDO_SQLCOMMAND,"SqlCommand",5);
	
	cf.AddFolder(&out2,"Database");
	cf.AddFolder(&out1,"Windows Form");
	

	//-------------------End Toolbox-----------------------------------
	m_tab_Edit.Addtab (&m_wndEdit,NULL,IDR_MENUOPTION);

	m_wtab.Addtab (&m_wndDebug,NULL,IDR_MENUOPTION);

	//subclass the Header list
	HWND hWndHeader = m_wndEdit.GetDlgItem(0);
	m_headerEdit.SubclassWnd(hWndHeader);

	hWndHeader = m_wndDebug.GetDlgItem(0);
	m_headerDebug.SubclassWnd(hWndHeader);

	m_rtab.Addtab (&cf,NULL,IDR_MENUOPTION);
	SetIconsList();
	m_DockLeft->AddWindow(&m_tab);
	
	m_DockBottom->AddWindow(&m_WorkTab);
	m_DockBottom->AddWindow(&m_wtab);
	m_DockRight->AddWindow(&m_rtab);
	m_DockRight->AddWindow(&m_TreeClassView);
	m_DockLeft->AddWindow(&m_explorer);
	m_DockLeft->AddWindow(&m_TreeResource,(UINT)m_explorer.GetDlgCtrlID());
	

	//Init the MenuBar
	cSpawn.LoadToolBarResource(IDR_STANDAR,IDB_STANDAR);
//	cSpawn.LoadToolBarResource(IDR_EDITTOOLBAR,IDB_EDITTOOLBAR);
	cSpawn.LoadToolBarResource(IDR_BUILD,IDB_BUILD);
	
	m_ClientView=(CMainFrame*)&m_Tabbed;
	OnNew(0, 0, 0);
	return 0;
}



void CWinFrame::FullfilHelp()
{
		

		if(!Image.CreateColor(IDB_TREEEXPLORER)) 
			return;
		m_TreeHelp.SetImageList(Image.GetImageHandle(),TVSIL_NORMAL);
		HTREEITEM hRoot = m_TreeHelp.InsertItem (_T("Help files"), 24, 24);
		m_TreeHelp.InsertItem (_T("Index"), 25, 25, hRoot);
		m_TreeHelp.InsertItem (_T("Search"), 26, 26, hRoot);
		m_TreeHelp.Expand (hRoot, TVE_EXPAND);
}

void CWinFrame::SetIconsList()
{
	CImageCtrl Image;
	
	if (IDB_MAINTOOLBAR != -1)
	{
		if(!Image.CreateColor(IDB_MAINTOOLBAR)) 
			return ;
	}
	else
	{
		CBitmap cbmp;
		BITMAP bmp;
		Image.Create(IDB_MAINTOOLBAR,16,16,RGB (192,192,192));
		cbmp.LoadBitmap(theApp->GetInstance(),(LPCTSTR)IDB_MAINTOOLBAR);
		cbmp.GetBitmap(&bmp);
		Image.Add(&cbmp,RGB (192,192,192));
		cbmp.DeleteObject();
		

	}
	m_tab.SetNumIcon(1);
	m_wtab.SetNumIcon(2);
	m_explorer.SetNumIcon(0);
	m_TreeResource.SetNumIcon(2);
	m_wndDebug.SetNumIcon(5);
	m_TreeClassView.SetNumIcon(1);
	m_wndEdit.SetNumIcon(4);
	m_wndFind1.SetNumIcon(3);
	m_wndFind2.SetNumIcon(9);
	cf.SetNumIcon(9);
	m_TreeHelp.SetNumIcon(10);
	m_wndResult.SetNumIcon(6);
	m_wndSqlDebug.SetNumIcon(7); 
}


BOOL CWinFrame::OnClose()
{
	int resp=MsgBox("Esta seguro de Salir","Close",MB_YESNO);
	if (resp==IDYES)
	{
		SaveConfig();
		return CWin::OnDestroy();
	}
	return FALSE;
}

int CAppMain::InitInstance()
{

	
	
	CHookMenu::InstallHook();	
	SetRegistryKey(_T("SWC\\Example\\DevStudio\\"));
	m_WinMain=(CFrame*)new CWinFrame; 
		
	if (m_WinMain->LoadFrame(IDC_BASEMENU)== FALSE)
		return -1;
	LoadMenu((LPCTSTR)IDC_BASEMENU);
	CRect rc;
	rc=m_WinMain->GetConfig();
	m_WinMain->cSpawn.RemapMenu(m_Menu.GetHandleMenu());
	m_WinMain->SetWindowPos(NULL,rc.left,rc.top,rc.Width(),rc.Height() ,SWP_SHOWWINDOW);
	m_WinMain->ShowWindow(SW_SHOW);
	m_WinMain->Invalidate();
	m_WinMain->UpdateWindow();
	hAccelTable = LoadAccelerators( (LPCTSTR)IDC_BASEMENU);
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