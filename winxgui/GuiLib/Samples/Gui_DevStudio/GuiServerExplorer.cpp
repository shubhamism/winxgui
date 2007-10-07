#include "StdAfx.h"
#include "guiserverexplorer.h"
#include "resource.h"

#define ID_REFRESH 0x355
#define ID_CONNECT 0x356
#define ID_CONSERVER 0x367

CGuiServerExplorer::CGuiServerExplorer(void)
{
}

CGuiServerExplorer::~CGuiServerExplorer(void)
{
}
BEGIN_MESSAGE_MAP(CGuiServerExplorer, CGuiControlBar)
	ON_WM_CREATE()
	ON_COMMAND(ID_REFRESH,  OnExplorer)
	ON_COMMAND(ID_CONNECT,  OnServer)
	ON_COMMAND(ID_CONSERVER,  OnConnect)
END_MESSAGE_MAP()

int CGuiServerExplorer::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CGuiControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	const DWORD dwStyle =WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS ;
	if (!m_ctServer.Create(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,124))
		return -1;
	CreatServerExplorer();
	if (!m_TreeServerExplorer.Create(dwStyle,	CRect(0,0,0,0), &m_ctServer, 2))
		return -1;
	m_ctServer.AddComponen(&m_TreeServerExplorer);
	// TODO:  Add your specialized creation code here
	SetIcon(IDB_BITMAPHELP,16,4,RGB(255,0,0),4);

	return 0;
}

void CGuiServerExplorer::OnConnect()
{
	AfxMessageBox("Connect");
}

void CGuiServerExplorer::OnServer()
{
	AfxMessageBox("Server");
}
void CGuiServerExplorer::OnExplorer()
{
	AfxMessageBox("Refresh");
}
	
int CGuiServerExplorer::CreatServerExplorer()
{
	m_ctServer.AddComponen(&m_miServer);
	m_miServer.AlingButtons(CGuiMiniTool::ALIGN_LEFT);
	m_miServer.SetImageList(IDB_DBPROJECTS, 16,27, RGB (255, 0, 0));
	m_miServer.AddButton(24,ID_REFRESH,NULL,_T(""),"Refresh");
	m_miServer.AddButton(25,ID_CONNECT,NULL,_T(""),"Connect To Database");
	m_miServer.AddButton(26,ID_CONSERVER,NULL,_T(""),"Connect To Server");
	m_miServer.AutoSize(FALSE);
//	m_miServer.SetColor(GuiDrawLayer::GetRGBColorXP());
	return 1;
}