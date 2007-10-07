#pragma once

#include "StdAfx.h"
#include "resource.h"
#include "cexplorer.h"
HHOOK CHookMenu::hHook=NULL; //This variable is requered by Menu
//---------------------------------------------------------------

	#define HELLO 0x1111
	#define IDPANEL0  60
	#define IDPANEL1  20
	#define IDPANEL2  20
	#define ID_COMBO1 0x2020 

	int  Panels[]={ IDPANEL0,IDPANEL1,IDPANEL2};
//---------------------------------------------------------------

#define IDO_POINTER  5606
#define IDO_LABEL 5607
#define IDO_BUTTON 5608
#define IDO_TEXTBOX 5609
#define IDO_MAINMENU 5910
#define IDO_CHECHBOX 5911
#define IDO_RADIOBUTTON 5912
#define IDO_GROUPBOX 5913
#define IDO_PICTUREBOX 5914
#define IDO_PANEL 5915
#define IDO_DATAGRID 5916
#define IDO_LISTBOX 5917
#define IDO_DBCONNECT 5918
#define IDO_DBCOMMAND 5919
#define IDO_DBADAPTER 5920
#define IDO_DBCONNECTION 5921
#define IDO_SQLCOMMAND 5922

//----------------------------------

#define IDO_OUTODAY	   5600
#define IDO_CALENDARIO 5601
#define IDO_CONTACTO   5602
#define IDO_TAREAS     5603
#define IDO_NOTAS	   5604	
#define IDO_ELIMINAR   5605

//----------------------------
class CAbout : public CDialog
{
public:
	CAbout(){};
	~CAbout(){};
	
	CButton   m_button;
	
	virtual BOOL OnInitDialog(HWND wParam,LPARAM lParam);
	virtual BOOL OnOK(WPARAM wParam, LPARAM lParam, HWND hWnd);
	virtual BOOL OnCancel(WPARAM wParam, LPARAM lParam, HWND hWnd);
	
BEGIN_MSG_MAP()
	ON_WM_INITDIALOG(OnInitDialog)
	ON_COMMAND(IDOK,OnOK)
	ON_COMMAND(IDCANCEL,OnCancel)
END_MSG_MAP(CDialog)
};



//------------------------------
//CFrame Class
//------------------------------

class CWinFrame: public CFrame
{

	CToolBarCtrlEx    m_ToolBarMain;
	CToolBarCtrlEx    m_ToolBarEdit;
	CExplorer		  m_explorer;	
	CResource		  m_TreeResource;
	CClassView		  m_TreeClassView;
	CTreeViewCtrl	  m_TreeHelp;
	CListView		  m_ListTaskList;
	CListView		  m_OutPut;
	CListView		  m_Find;
	CContainer		  m_tab;
	CContainer		  m_wtab;
	CContainer		  m_tab_Edit;
	CContainer		  m_rtab;
	CWkTab			  m_WorkTab;
	CEdit*			  m_edit;
	
	//---- para prueba
	CEdit			  m_edit1;
	CImageCtrl		  Image;
	COutLook		outPrincipal;
	CHeaderView		m_headerDebug;
	CHeaderView		m_headerEdit;
	COutLook	out1;
	COutLook	out2;
	CMMedia cf;
	CToolBarCtrlEx   m_ToolContainer;
	CComboBoxExt	  m_comboDebug;
	CMiniFrame		m_Mini;
	HWND			hWnd;
	
	COutputList m_wndDebug;
	COutputList m_wndFind1;
	COutputList m_wndFind2;
	COutputList m_wndResult;
	COutputList m_wndSqlDebug;
	COutputList m_wndEdit;


	CTabbed		m_Tabbed;
public:
	

	CWinFrame(){}
	BOOL OnClose();
	BOOL OnCreate(LPCREATESTRUCT lpCreateStruct);
	BOOL OnSize(UINT nType,long x, long y);
	void SetIconsList();
	void FullfilHelp();
	
	void OnNew(WPARAM wParam, LPARAM lParam, HWND hWnd);
	void OnExit(WPARAM wParam, LPARAM lParam, HWND hWnd);
	void OnToolBar(WPARAM wParam, LPARAM lParam, HWND hWnd);
	void OnFileClose(WPARAM wParam, LPARAM lParam, HWND hWnd);
	void OnAbout(WPARAM wParam, LPARAM lParam, HWND hWnd);
	void OnviewSourceView(WPARAM wParam, LPARAM lParam, HWND hWnd);
	void OnViewHelp(WPARAM wParam, LPARAM lParam, HWND hWnd);
	void OnViewToolbox(WPARAM wParam, LPARAM lParam, HWND hWnd);
	void OnViewClassView(WPARAM wParam, LPARAM lParam, HWND hWnd);
	void OnOutlook(WPARAM wParam, LPARAM lParam, HWND hWnd);
	void OnSolutionExplorer(WPARAM wParam, LPARAM lParam, HWND hWnd);
	void OnWorTabdemo(WPARAM wParam, LPARAM lParam, HWND hWnd);
	void OnFileOpen(WPARAM wParam, LPARAM lParam, HWND hWnd);
	
BEGIN_MSG_MAP()
	 ON_WM_CLOSE(OnClose)
	 ON_WM_CREATE(OnCreate)
	 ON_COMMAND(ID_FILE_NEW,OnNew)
	 ON_COMMAND(ID_FILE_CLOSE,OnFileClose)
	 ON_COMMAND(ID_FILE_OPEN,OnFileOpen)
	 ON_WM_SIZE(OnSize) 
	 ON_COMMAND(ID_TOOLBAR,OnToolBar)
	 ON_COMMAND(IDM_EXIT,OnExit)
	 ON_COMMAND(IDM_ABOUT,OnAbout)

	 ON_COMMAND(ID_VIEWRESOURCEVIEW,OnviewSourceView)
	 ON_COMMAND(ID_VIEWHELPWINDOW,OnViewHelp)
	 ON_COMMAND(ID_VIEWTOOLBOX,OnViewToolbox)
	 ON_COMMAND(ID_VIEWCLASSVIEW,OnViewClassView)
	 ON_COMMAND(ID_VIEW_OUTLOOKWINDOW,OnOutlook)
	 ON_COMMAND(ID_VIEW_SOLUTIONEXPLORER,OnSolutionExplorer)
	 ON_COMMAND(ID_VIEW_WORTABDEMO,OnWorTabdemo)
END_MSG_MAP(CFrame)

};


//---------------------------
//CAppMain
//---------------------------

class CAppMain :public CApp 
{
public:
	int InitInstance();
	~CAppMain() 
	{
		CHookMenu::UnInstallHook();
	}
};

