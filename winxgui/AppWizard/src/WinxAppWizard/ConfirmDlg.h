// ConfirmDlg.h: interface for the CConfirmDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIRMDLG_H__27DD9670_A4D2_46FF_A5E1_AFF5948A7692__INCLUDED_)
#define AFX_CONFIRMDLG_H__27DD9670_A4D2_46FF_A5E1_AFF5948A7692__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

class CConfirmDlg  : public CDialogImpl<CConfirmDlg>, public CWinDataExchange<CConfirmDlg>
{
public:
	CString	m_projectPath;
	CString	m_info;
	enum { IDD = IDD_CONFIRM_DLG};
	CConfirmDlg();
	virtual ~CConfirmDlg();

	BEGIN_MSG_MAP(CConfirmDlg)
		COMMAND_ID_HANDLER(IDOK, OnOk)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	END_MSG_MAP()

	BEGIN_DDX_MAP(CConfirmDlg)
		DDX_TEXT(IDC_PROJECT_PATH, m_projectPath)
		DDX_TEXT(IDC_INFO_EDIT, m_info)
	END_DDX_MAP();
	
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnOk(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);	
};

#endif // !defined(AFX_CONFIRMDLG_H__27DD9670_A4D2_46FF_A5E1_AFF5948A7692__INCLUDED_)
