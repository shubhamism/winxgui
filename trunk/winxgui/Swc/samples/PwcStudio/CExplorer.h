#pragma once

#include "StdAfx.h"
#include "resource.h"

class CExplorer : public CDockPanelBase
{
protected:
	CToolBarCtrlEx    m_ToolBarBuild;
	CTreeViewCtrl	  m_TreeExplorer;
	CComboBox	  m_comboboxExt;
	CImageCtrl	Image;
public:
	CExplorer()
	{
		
	}
	~CExplorer()
	{
		SaveConfig();
	}
protected:
	virtual BOOL OnCreate(LPCREATESTRUCT lpCreateStruct)
	{

		if ( !m_ToolBarBuild.Create(GetSafeHwnd(),IDR_BUILD))
		return -1;
	
		if (!m_comboboxExt.Create(GetSafeHwnd(),0x10000,NULL,WS_CHILD|WS_VISIBLE|CBS_DROPDOWN  | 
							WS_VSCROLL | CBS_HASSTRINGS |CBS_OWNERDRAWVARIABLE))
							return -1;

		m_ToolBarBuild.LoadToolBar(IDR_BUILD);
		m_ToolBarBuild.AddTrueColor(IDB_BUILD,TB_SETIMAGELIST);
		if (!m_TreeExplorer.Create(GetSafeHwnd(),WS_CHILD | WS_VISIBLE | TVS_HASLINES | 
								TVS_LINESATROOT | TVS_HASBUTTONS, 2))
		return -1;
	
		
		
		if(!Image.CreateColor(IDB_TREEEXPLORER)) 
			return FALSE;
		m_TreeExplorer.SetImageList(Image.GetImageHandle(),TVSIL_NORMAL);
		PopulateTree();
		return TRUE;
	}

	void PopulateTree()
	{
		HTREEITEM hRoot = m_TreeExplorer.InsertItem (_T("MySwc files"), 0, 0);
		HTREEITEM hSrc = m_TreeExplorer.InsertItem (_T("Source Files"), 2, 3, hRoot);

		m_TreeExplorer.InsertItem (_T("CMainWin.cpp"), 4, 4, hSrc);
		m_TreeExplorer.InsertItem (_T("CMenuSpawn.cpp"), 4, 4, hSrc);
		m_TreeExplorer.InsertItem (_T("CWinDock.cpp"), 4, 4, hSrc);
		m_TreeExplorer.InsertItem (_T("StdAfx.cpp"), 4, 4, hSrc);
		m_TreeExplorer.InsertItem (_T("MainFrm.cpp"), 4, 4, hSrc);
		m_TreeExplorer.InsertItem (_T("CComboBoxExt.cpp"), 4, 4, hSrc);
		m_TreeExplorer.InsertItem (_T("CContainer.cpp"), 4,4, hSrc);
		m_TreeExplorer.InsertItem (_T("CCFolder.cpp"), 4, 4, hSrc);
		m_TreeExplorer.InsertItem (_T("CCMMedia.cpp"), 4, 4, hSrc);
		m_TreeExplorer.InsertItem (_T("CCOutLook.cpp"), 4, 4, hSrc);
		m_TreeExplorer.InsertItem (_T("CSplitter.cpp"), 4, 4, hSrc);
		m_TreeExplorer.InsertItem (_T("CTabbed.cpp"), 4, 4, hSrc);
		m_TreeExplorer.InsertItem (_T("CWorkTab.cpp"), 4, 4, hSrc);

		HTREEITEM hInc = m_TreeExplorer.InsertItem (_T("Header Files"), 2, 3, hRoot);

		m_TreeExplorer.InsertItem (_T("CMainWin.h"), 5, 5, hInc);
		m_TreeExplorer.InsertItem (_T("CMenuSpawn.h"), 5, 5, hInc);
		m_TreeExplorer.InsertItem (_T("CWinDock.h"), 5, 5, hInc);
		m_TreeExplorer.InsertItem (_T("StdAfx.h"), 5, 5, hInc);
		m_TreeExplorer.InsertItem (_T("MainFrm.h"), 5, 5, hInc);
		m_TreeExplorer.InsertItem (_T("CComboBoxExt.h"), 5, 5, hInc);
		m_TreeExplorer.InsertItem (_T("CContainer.h"), 5, 5, hInc);
		m_TreeExplorer.InsertItem (_T("CCFolder.h"), 5, 5, hInc);
		m_TreeExplorer.InsertItem (_T("CCMMedia.h"), 5, 5, hInc);
		m_TreeExplorer.InsertItem (_T("CCOutLook.h"), 5, 5, hInc);
		m_TreeExplorer.InsertItem (_T("CSplitter.h"),5, 5, hInc);
		m_TreeExplorer.InsertItem (_T("CTabbed.h"), 5,5, hInc);
		m_TreeExplorer.InsertItem (_T("CWorkTab.h"), 5, 5, hInc);

		HTREEITEM hRes = m_TreeExplorer.InsertItem (_T("Resource Files"), 2, 3, hRoot);

		m_TreeExplorer.InsertItem (_T("MySwc.ico"), 10, 10, hRes);
		m_TreeExplorer.InsertItem (_T("MySwc.rc2"), 9, 9, hRes);
		m_TreeExplorer.InsertItem (_T("MySwcDoc.ico"), 10, 10, hRes);
		m_TreeExplorer.InsertItem (_T("Toolbar.bmp"), 13, 13, hRes);

		m_TreeExplorer.Expand (hRoot, TVE_EXPAND);
		m_TreeExplorer.Expand (hSrc, TVE_EXPAND);
		m_TreeExplorer.Expand (hInc, TVE_EXPAND);
		m_TreeExplorer.Expand (hRes, TVE_EXPAND);
	}

	
	virtual BOOL OnPaint(HDC hDC)
	{
		CRect rcClient;
		CPaintDC dc(GetSafeHwnd()); // device context for painting
		m_TreeExplorer.GetWindowRect(rcClient);
		ScreenToClient(rcClient);
		rcClient.InflateRect(1,1);
		rcClient.bottom+=1;
		dc.Draw3dRect(rcClient,GetSysColor(COLOR_BTNSHADOW),GetSysColor(COLOR_BTNSHADOW));
		dc.DeleteDC();
		return TRUE;
	}

	virtual void UpdatePanel()
	{
		CRect rc;
		CRect rcT;
		GetClientRect(rc);
		int nVal=0;
		rcT=rc;
		nVal=rc.top;
		rcT.bottom=22;
		m_comboboxExt.SetWindowPos(NULL,rcT,SWP_NOACTIVATE|SWP_NOZORDER);
		nVal+=24;
		rcT=rc;
		rcT.top=nVal;
		rcT.bottom=22;
		nVal+=22+2;
		m_ToolBarBuild.SetWindowPos(NULL,rcT,SWP_NOACTIVATE|SWP_NOZORDER);
		rcT=rc;
		rcT.right-=2;
		rcT.top=nVal;
		rcT.bottom-=nVal+3;
		rcT.DeflateRect(1,1);
		m_TreeExplorer.SetWindowPos(NULL,rcT,SWP_NOACTIVATE|SWP_NOZORDER);
		
	}

};

//---------------------------------------------------------------
class COutputList : public CListView
{
public:
	COutputList(){};
	virtual ~COutputList(){};
	void  OnWindowPosChanging(WINDOWPOS* lpwndpos)
	{
		Default();
		ShowScrollBar (SB_HORZ, FALSE);
		//ModifyStyle (WS_HSCROLL, 0, SWP_DRAWFRAME);
	}
protected:
	
	BEGIN_MSG_MAP()
		ON_WM_WINDOWPOSCHANGING(OnWindowPosChanging)
	END_MSG_MAP(CListView)
};


class CWkTab : public CDockPanelBase
{
protected:
	CWorkTab	  m_wktab;
	
	COutputList m_wndOutList1;
	COutputList m_wndOutList2;
	COutputList m_wndOutList3;
	CHeaderView m_h1;
	CHeaderView m_h2;
	CHeaderView m_h3;
public:
	CWkTab()
	{
			
	}

	~CWkTab()
	{
		
	}
protected:
	virtual BOOL OnCreate(LPCREATESTRUCT lpCreateStruct)
	{

		if (!m_wktab.Create(WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),this,0x9933))
			return -1;


		
			//-------------------------------------------------------------
			m_wndOutList1.Create (m_wktab.GetSafeHwnd(),WS_CHILD | WS_VISIBLE | WS_VSCROLL | LVS_REPORT,7000);
			m_wndOutList2.Create (m_wktab.GetSafeHwnd(),WS_CHILD | WS_VISIBLE | WS_VSCROLL | LVS_REPORT,8000);
			m_wndOutList3.Create (m_wktab.GetSafeHwnd(),WS_CHILD | WS_VISIBLE | WS_VSCROLL | LVS_REPORT,9000);
			
			m_wndOutList1.SendMessage (LVM_SETEXTENDEDLISTVIEWSTYLE, 0,
								LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			m_wndOutList1.InsertColumn (0, _T("Description"), LVCFMT_LEFT, 200,0);
			m_wndOutList1.InsertColumn (1, _T("Line"), LVCFMT_LEFT, 100,0);

			m_wndOutList1.InsertItemText (0, _T("Could not open the temporary file c:\\temp\\example.exe"));
			m_wndOutList1.InsertItemText (0, 1, _T("23"));

			m_wndOutList2.SendMessage (LVM_SETEXTENDEDLISTVIEWSTYLE, 0,
								LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			m_wndOutList2.InsertColumn (0, _T("Description"), LVCFMT_LEFT, 400,0);
			
			m_wndOutList2.InsertItemText (0, _T("Project loaded c:\\temp\\example.exe"));
			m_wndOutList2.InsertItemText (0, _T("Project loaded Microsoft.windows.common-controls"));
			m_wndOutList2.InsertItemText (0, _T("Project loaded c:\\windows\\system32\\shlapi.dll"));

			m_wndOutList3.SendMessage (LVM_SETEXTENDEDLISTVIEWSTYLE, 0,
								LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			m_wndOutList3.InsertColumn (0, _T("Description"), LVCFMT_LEFT, 300,0);
			
			m_wndOutList3.InsertItemText (0, _T("Project loaded c:\\temp\\example.exe No sysmbols loaded"));
			m_wndOutList3.InsertItemText (0, _T("Project loaded PwcStudio [4260] Native has exit with code 0 (0x0)"));

			HWND hWndHeader = m_wndOutList1.GetDlgItem(0);
			m_h1.SubclassWnd(hWndHeader);

			hWndHeader = m_wndOutList2.GetDlgItem(0);
			m_h2.SubclassWnd(hWndHeader);

			hWndHeader = m_wndOutList3.GetDlgItem(0);
			m_h3.SubclassWnd(hWndHeader);

			m_wktab.Addtab (&m_wndOutList1, _T("Error List"));
			m_wktab.Addtab (&m_wndOutList2, _T("Command"));
			m_wktab.Addtab (&m_wndOutList3, _T("Output"));
			m_wktab.SetCaption();
			SetWindowText(_T("Demo Worktab"));
		//-------------------------------------------------------------

		return TRUE;
	}

		
	virtual BOOL OnPaint(HDC hDC)
	{
		CRect rcClient;
		CPaintDC dc(GetSafeHwnd()); // device context for painting
		m_wktab.GetWindowRect(rcClient);
		ScreenToClient(rcClient);
		rcClient.InflateRect(1,1);
		rcClient.bottom+=1;
		dc.Draw3dRect(rcClient,GetSysColor(COLOR_BTNSHADOW),GetSysColor(COLOR_BTNSHADOW));
		dc.DeleteDC();
		return TRUE;
	}

	virtual void UpdatePanel()
	{
		CRect rc;
		
		GetClientRect(rc);
		
		rc.right-=2;
		rc.bottom-=3;
		rc.DeflateRect(1,1);
		m_wktab.SetWindowPos(NULL,rc,SWP_NOACTIVATE|SWP_NOZORDER);
		
	}

};
 

class CResource : public CDockPanelBase
{
protected:
	CTreeViewCtrl	  m_TreeResource;
		CImageCtrl	Image;
public:
	CResource()
	{
		
	}

	~CResource()
	{
		
	}
protected:
	virtual BOOL OnCreate(LPCREATESTRUCT lpCreateStruct)
	{

		if (!m_TreeResource.Create(GetSafeHwnd(),WS_CHILD | WS_VISIBLE | TVS_HASLINES | 
								TVS_LINESATROOT | TVS_HASBUTTONS, 0x123456))
		return -1;
	
		
		
		if(!Image.CreateColor(IDB_TREEEXPLORER)) 
			return FALSE;
		m_TreeResource.SetImageList(Image.GetImageHandle(),TVSIL_NORMAL);
		PopulateTree();
		return TRUE;
	}

	void PopulateTree()
	{
		HTREEITEM hRoot = m_TreeResource.InsertItem (_T("My Project"), 1, 1);
		HTREEITEM hAcc = m_TreeResource.InsertItem (_T("Accelerator"), 2, 3, hRoot);
		HTREEITEM hBit = m_TreeResource.InsertItem (_T("Bitmap"), 2, 3, hRoot);
		HTREEITEM hDial = m_TreeResource.InsertItem (_T("Dialog"), 2, 3, hRoot);
		HTREEITEM hIcon = m_TreeResource.InsertItem (_T("Icon"), 2, 3, hRoot);
		HTREEITEM hMenu = m_TreeResource.InsertItem (_T("Menu"), 2, 3, hRoot);
		m_TreeResource.InsertItem (_T("IDC_WINCLASS"), 8, 8, hAcc);
		m_TreeResource.InsertItem (_T("IDB_BUILD"), 7, 7, hBit);
		m_TreeResource.InsertItem (_T("IDB_EDITTOOLBAR"), 7, 7, hBit);
		m_TreeResource.InsertItem (_T("IDB_MAINTOOLBAR"), 7, 7, hBit);
		m_TreeResource.InsertItem (_T("IDD_ABOUTBOX"), 9, 9, hDial);
		m_TreeResource.InsertItem (_T("IDI_SMALL"), 10, 10, hIcon);
		m_TreeResource.InsertItem (_T("IDI_BASEMENU"), 11, 11, hMenu);
		m_TreeResource.InsertItem (_T("IDI_MENUHELLO"), 11, 11, hMenu);
		m_TreeResource.InsertItem (_T("IDI_MENUOPTION"), 11, 11, hMenu);
		m_TreeResource.Expand (hRoot, TVE_EXPAND);
		m_TreeResource.Expand (hAcc, TVE_EXPAND);
		m_TreeResource.Expand (hBit, TVE_EXPAND);
		m_TreeResource.Expand (hDial, TVE_EXPAND);
		m_TreeResource.Expand (hIcon, TVE_EXPAND);
		m_TreeResource.Expand (hMenu, TVE_EXPAND);
	
	}

	
	virtual BOOL OnPaint(HDC hDC)
	{
		CRect rcClient;
		CPaintDC dc(GetSafeHwnd()); // device context for painting
		m_TreeResource.GetWindowRect(rcClient);
		ScreenToClient(rcClient);
		rcClient.InflateRect(1,1);
		rcClient.bottom+=1;
		dc.Draw3dRect(rcClient,GetSysColor(COLOR_BTNSHADOW),GetSysColor(COLOR_BTNSHADOW));
		dc.DeleteDC();
		return TRUE;
	}

	virtual void UpdatePanel()
	{
		CRect rc;
		
		GetClientRect(rc);
		
		rc.right-=2;
		rc.bottom-=3;
		rc.DeflateRect(1,1);
		m_TreeResource.SetWindowPos(NULL,rc,SWP_NOACTIVATE|SWP_NOZORDER);
		
	}

};


class CClassView : public CDockPanelBase
{
protected:
	CTreeViewCtrl	  m_TreeResource;
	CImageCtrl	Image;
public:
	CClassView()
	{
		
	}

	~CClassView()
	{
		
	}
protected:
	virtual BOOL OnCreate(LPCREATESTRUCT lpCreateStruct)
	{

		if (!m_TreeResource.Create(GetSafeHwnd(),WS_CHILD | WS_VISIBLE | TVS_HASLINES | 
								TVS_LINESATROOT | TVS_HASBUTTONS, 0x123456))
		return -1;
	
		
		
		if(!Image.CreateColor(IDB_TREEEXPLORER)) 
			return FALSE;
		m_TreeResource.SetImageList(Image.GetImageHandle(),TVSIL_NORMAL);
		PopulateTree();
		return TRUE;
	}

	void PopulateTree()
	{
		HTREEITEM hRoot = m_TreeResource.InsertItem (_T("My Project"), 0, 0);
		
		m_TreeResource.InsertItem (_T("Global Functions and Variables"), 20, 20, hRoot);
		m_TreeResource.InsertItem (_T("Macros and Constantes"), 21, 21, hRoot);
		m_TreeResource.InsertItem (_T("CAbout"), 19, 19, hRoot);
		m_TreeResource.InsertItem (_T("CAppMain"), 19, 19, hRoot);
		m_TreeResource.InsertItem (_T("CClassView"), 19, 19, hRoot);
		m_TreeResource.InsertItem (_T("CExplorer"),19, 19, hRoot);
		m_TreeResource.InsertItem (_T("COutputList"), 19, 19, hRoot);
		m_TreeResource.InsertItem (_T("CResourcce"), 19, 19, hRoot);
		m_TreeResource.Expand (hRoot, TVE_EXPAND);
		
	
	}

	
	virtual BOOL OnPaint(HDC hDC)
	{
		CRect rcClient;
		CPaintDC dc(GetSafeHwnd()); // device context for painting
		m_TreeResource.GetWindowRect(rcClient);
		ScreenToClient(rcClient);
		rcClient.InflateRect(1,1);
		rcClient.bottom+=1;
		dc.Draw3dRect(rcClient,GetSysColor(COLOR_BTNSHADOW),GetSysColor(COLOR_BTNSHADOW));
		dc.DeleteDC();
		return TRUE;
	}

	virtual void UpdatePanel()
	{
		CRect rc;
		
		GetClientRect(rc);
		
		rc.right-=2;
		rc.bottom-=3;
		rc.DeflateRect(1,1);
		m_TreeResource.SetWindowPos(NULL,rc,SWP_NOACTIVATE|SWP_NOZORDER);
		
	}

};
