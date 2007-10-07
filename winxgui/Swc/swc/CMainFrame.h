
#pragma once


// CmainFrame

class  CMainFrame : public CWin
{
public:
	void AddLeftCtrl(CWin* pWnd,LPCSTR lpMsg,long MinSize);
	void AddRightCtrl(CWin* pWnd,LPCSTR lpMsg,long MinSize);
	void AddCenterCtrl(CWin* pWnd,LPCSTR lpMsg,long MinSize);
	void AddBottomCtrl(CWin* pWnd,LPCSTR lpMsg,long MinSize);
	void AddCenterDefault();
public:
	
	//-----------------------
	 BOOL Create(CWin* pParentWnd);
	 int OnCreate(LPCREATESTRUCT lpCreateStruct);
	 BOOL OnSize(UINT nType, int cx, int cy);
	 BOOL OnSysColorChange();
	//-----------------------
public:
	CMainFrame();
	virtual ~CMainFrame();
public:
	CSplitter	splitterMain;
	CSplitter   splitterLeft;
	CSplitter	splitterCenter;
	CMMedia		cmedBottom;
	CMMedia		cmedLeft;
	CMMedia		cmedRight;

public:
	CTabbed		m_Tabbed;
protected:
	BEGIN_MSG_MAP()
	ON_WM_CREATE(OnCreate)
	ON_WM_SIZE(OnSize)
	END_MSG_MAP(CWin)
	
};

