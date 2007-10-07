#include "stdafx.h"

// CMainFrame

CMainFrame::CMainFrame()
{
	
}

CMainFrame::~CMainFrame()
{

}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// TODO:  Add your specialized creation code here
	
	if (!splitterMain.Create(this))
			return -1;

	if (!splitterLeft.Create(&splitterMain))
		return -1;
	
	if (!splitterCenter.Create(&splitterLeft))
		return -1;

	if (!cmedBottom.Create( &splitterMain, CRect(0,0,0,0) ,WS_CHILD, 1000))
		return -1;

	if (!cmedLeft.Create( &splitterLeft, CRect(0,0,0,0) ,WS_CHILD, 1001))
		return -1;

	if (!cmedRight.Create( &splitterCenter, CRect(0,0,0,0) ,WS_CHILD, 1002))
		return -1;

	//Splitters config
	splitterMain.SeTypeALing(CSplitter::ALINGVERT);
	splitterMain.SetStyleSeparator(CSplitter::STYLEFLAT);

	splitterLeft.SeTypeALing(CSplitter::ALINGHORZ);
	splitterLeft.SetStyleSeparator(CSplitter::STYLEFLAT);

	splitterCenter.SeTypeALing(CSplitter::ALINGHORZ);
	splitterCenter.SetStyleSeparator(CSplitter::STYLEFLAT);

	//Add basic windows
	splitterMain.AddLeftCtrl(&splitterLeft,200);
	//splitterMain.AddRightCtrl(&cmedBottom,200);

	
	splitterLeft.AddRightCtrl(&splitterCenter,200);

	splitterCenter.AddRightCtrl(&cmedRight,200);

	return 0;
}


BOOL CMainFrame::Create(CWin* pParentWnd)
{
	// TODO: Add your specialized code here and/or call the base class
	LPTSTR lpclassname=RegisterDefaultClass(NULL,WS_CHILD|WS_VISIBLE);
	return CWin::Create(lpclassname,NULL, WS_VISIBLE|WS_CHILD|WS_CLIPSIBLINGS|WS_CLIPCHILDREN, CRect(0,0,0,0), pParentWnd->GetSafeHwnd(), 0xffff);
}



void  CMainFrame::AddLeftCtrl(CWin* pWnd,LPCSTR lpMsg,long MinSize)
{
	ASSERT(pWnd);
	splitterLeft.AddLeftCtrl(pWnd,200);
	/*if (!cmedLeft.IsWindowVisible())
		cmedLeft.ShowWindow();
	cmedLeft.AddFolder(pWnd,lpMsg);*/

}

void  CMainFrame::AddRightCtrl(CWin* pWnd,LPCSTR lpMsg,long MinSize)
{
	ASSERT(pWnd);
	if (!cmedRight.IsWindowVisible())
		cmedRight.ShowWindow();
	cmedRight.AddFolder(pWnd,lpMsg);
	splitterMain.AddLeftCtrl(pWnd,200);
}

void  CMainFrame::AddBottomCtrl(CWin* pWnd,LPCSTR lpMsg,long MinSize)
{
	ASSERT(pWnd);
	//if (!cmedBottom.IsWindowVisible())
	//	cmedBottom.ShowWindow();
	//cmedBottom.AddFolder(pWnd,lpMsg);
	splitterMain.AddRightCtrl(pWnd,200);

}

void  CMainFrame::AddCenterCtrl(CWin* pWnd,LPCSTR lpMsg,long MinSize)
{
	ASSERT(pWnd);
	splitterCenter.AddLeftCtrl(pWnd,200);

}

void CMainFrame::AddCenterDefault()
{
	if (!m_Tabbed.Create(WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),&splitterCenter,0x333))
		return ;
	splitterCenter.AddLeftCtrl(&m_Tabbed,200);
}

BOOL CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CRect m_rectCli;
	GetClientRect(m_rectCli);
	if (m_rectCli.IsRectEmpty()) return FALSE;

	if (splitterMain.IsWindowVisible())
		splitterMain.MoveWindow(m_rectCli);
	cmedLeft.Invalidate();
	cmedLeft.UpdateWindow();
	cmedRight.Invalidate();
	cmedRight.UpdateWindow();
	CWin* pWnd=splitterCenter.GetLeft();
	if (pWnd != NULL)
	{
		pWnd->Invalidate();
		pWnd->UpdateWindow();
	}
	pWnd=splitterLeft.GetLeft();
	if (pWnd != NULL)
	{
		pWnd->Invalidate();
		pWnd->UpdateWindow();
	}
	splitterMain.Invalidate();
	splitterMain.UpdateWindow();
	splitterCenter.Invalidate();
	splitterCenter.UpdateWindow();
	return TRUE;
	// TODO: Add your message handler code here
}


BOOL CMainFrame::OnSysColorChange()
{
	// TODO: Add your message handler code here
	return TRUE;
}

