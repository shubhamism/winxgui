
#if !defined(AFX_OUTOOLKDEMO_H__29F3484A_5894_4BB1_8E64_89F4FFB581BD__INCLUDED_)
#define AFX_OUTOOLKDEMO_H__29F3484A_5894_4BB1_8E64_89F4FFB581BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "stdafx.h"

#define IDO_OUTODAY	   5600
#define IDO_CALENDARIO 5601
#define IDO_CONTACTO   5602
#define IDO_TAREAS     5603
#define IDO_NOTAS	   5604	
#define IDO_ELIMINAR   5605

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


//---------------------------------------------------

class CAbout : public CDialog
{
protected:
	CButton   m_button;
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


//---------------------------------------------------


class CWinFrame: public CFrame
{

	CToolBarCtrlEx    m_ToolBar;
	CSplitter	m_Splitter;
	CSplitter	m_Splitright;
	CSplitter	m_SplitterList;
	CTreeViewCtrl	tc;
	CTreeViewCtrl	FolderList;
	CListView	m_up;
	CListView	m_down;
	CFolder cf;
	CListView	m_der;
	COutLook	out;
	COutLook	out1;
	COutLook	out2;
	CImageCtrl	Image;
	CImageCtrl	Image1;
	CComboBoxExt	  m_comboDebug;
	CHeaderView		m_header;

public:
	

	CWinFrame(){}
	BOOL OnClose();
	BOOL OnCreate(LPCREATESTRUCT lpCreateStruct);
	BOOL OnSize(UINT nType,long x, long y);
	void OnNew(WPARAM wParam, LPARAM lParam, HWND hWnd);
	void OnExit(WPARAM wParam, LPARAM lParam, HWND hWnd);
	void OnToolBar(WPARAM wParam, LPARAM lParam, HWND hWnd);
	void OnFileClose(WPARAM wParam, LPARAM lParam, HWND hWnd);
	void OnAbout(WPARAM wParam, LPARAM lParam, HWND hWnd);
	void OnToday(WPARAM wParam, LPARAM lParam, HWND hWnd);

BEGIN_MSG_MAP()

	 ON_WM_CLOSE(OnClose)
	 ON_WM_CREATE(OnCreate)
	 ON_COMMAND(ID_FILE_NEW,OnNew)
	 ON_WM_SIZE(OnSize) 
	 ON_COMMAND(IDR_TOOLBAR,OnToolBar)
	 ON_COMMAND(IDM_EXIT,OnExit)
	 ON_COMMAND(ID_APP_ABOUT,OnAbout);
	 ON_COMMAND(IDO_OUTODAY,OnToday);
END_MSG_MAP(CFrame)

};


//---------------------------------------------------

class CAppMain :public CApp 
{
public:
	int InitInstance();
	~CAppMain(){
		//CHookMenu::UnInstallHook();
	}
};




#endif // !defined(AFX_OUTOOLKDEMO_H__29F3484A_5894_4BB1_8E64_89F4FFB581BD__INCLUDED_)
