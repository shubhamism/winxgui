////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	AddAltMapDlg.h
// Created:	17.01.2005 9:58
// 
//   Using this software in commercial applications requires an author
// permission. The permission will be granted to everyone excluding the cases
// when someone simply tries to resell the code.
//   This file may be redistributed by any means PROVIDING it is not sold for
// profit without the authors written consent, and providing that this notice
// and the authors name is included.
//   This file is provided "as is" with no expressed or implied warranty. The
// author accepts no liability if it causes any damage to you or your computer
// whatsoever.
//
////////////////////////////////////////////////////////////////////////////////

// This file was generated by WTL Dialog wizard 
// AddAltMapDlg.h : Declaration of the CAddAltMapDlg
#pragma once
#include "../resource.h"
#include "atllttmap.h"
// CAddAltMapDlg

class CAddAltMapDlg : 
	public CDialogImpl<CAddAltMapDlg>,
	public CWinDataExchange<CAddAltMapDlg>,
	public CToolTipMapImpl<CAddAltMapDlg>
{
public:
	CAddAltMapDlg();
	~CAddAltMapDlg();
	enum { IDD = IDD_ADDALTMAPDLG };
	CString m_iNumber;
	CString m_Name;

    BEGIN_MSG_MAP(CAddAltMapDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
        COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
    END_MSG_MAP()

	BEGIN_DDX_MAP(CAddAltMapDlg)
		DDX_TEXT(IDC_EDIT_ALTNAME, m_Name)
		DDX_TEXT(IDC_EDIT_ALTNUM, m_iNumber)
	END_DDX_MAP()

	BEGIN_TOOLTIP_MAP(CAddAltMapDlg)
		TIP_CHILDWND(IDC_EDIT_ALTNAME, IDS_TOOLTIP_ALT_NAME)
		TIP_CHILDWND(IDC_EDIT_ALTNUM, IDS_TOOLTIP_ALT_NUM)
	END_TOOLTIP_MAP()
    // Handler prototypes:
    //  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    //  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
    //  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};


