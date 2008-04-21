// ConfirmDlg.cpp: implementation of the CConfirmDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ConfirmDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConfirmDlg::CConfirmDlg()
{

}

CConfirmDlg::~CConfirmDlg()
{

}

LRESULT CConfirmDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CenterWindow(GetActiveWindow());
	DoDataExchange(false);
	return 0;
}

LRESULT CConfirmDlg::OnOk(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}
LRESULT CConfirmDlg::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}
