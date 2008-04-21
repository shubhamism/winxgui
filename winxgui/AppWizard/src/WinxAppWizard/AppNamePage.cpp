// AppNamePage.cpp: implementation of the CAppNamePage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AppNamePage.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAppNamePage::CAppNamePage()
{
	SetTitle("WinxGui AppWizard 8.0 - Step 1 of 3");
	SetHeaderTitle("Application Name");
	SetHeaderSubTitle("Set Projects Application Name");
	m_dwButton = PSWIZB_NEXT;
}

CAppNamePage::~CAppNamePage()
{

}

LRESULT CAppNamePage::OnBrowse(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CFolderDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		SetDlgItemText(IDC_LOCATION_EDIT,dlg.m_szFolderPath);
		SetDlgItemText(IDC_PROJECT_PATH_EDIT,dlg.m_szFolderPath+CString(_T("\\"))+GetText(IDC_PROJECT_NAME_EDIT));
	}
	return 0;
}

LRESULT CAppNamePage::OnEnChangeProjectNameEdit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	SetDlgItemText(IDC_PROJECT_PATH_EDIT,GetText(IDC_LOCATION_EDIT)+CString(_T("\\"))+GetText(IDC_PROJECT_NAME_EDIT));
	return 0;
}

CString CAppNamePage::GetText(UINT nID)
{
	TCHAR sz[MAX_PATH] = {0};
	GetDlgItemText(nID,sz,MAX_PATH);
	return sz;
}
