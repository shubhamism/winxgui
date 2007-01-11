////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	HandlerIDDlg.h
// Created:	16.11.2004 8:55
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
// HandlerDlg.h : Declaration of the CHandlerDlg
#pragma once

#include <atlcrack.h>
#include "../HandlerManager.h"
#include "../resource.h"
#include "atllttmap.h"
// CHandlerDlg

#define EF_ID		1
#define EF_CODE		2
#define EF_RANGE	4

#define EF_ALL		(EF_ID | EF_CODE | EF_RANGE)

class CHandlerIDDlg : 
	public CDialogImpl<CHandlerIDDlg>,
	public CWinDataExchange<CHandlerIDDlg>,
	public CToolTipMapImpl<CHandlerIDDlg>
{
	CString m_DefMessage;
	void CheckFunctionName();
	bool IsMessageCombo();
public:
	CHandlerIDDlg();
	~CHandlerIDDlg();
	
	CString m_DefFunc;
	CString m_Function;
	CString m_Message;
	CString m_ID;
	CString m_LastID;

	BOOL m_Style;
	BOOL m_bHandlerID;
	BOOL m_bHandlerCode;
	BOOL m_bReflected;
	BOOL m_bInline;
	BOOL m_bRange;
	BOOL m_bInitDialog;
	BOOL m_bCustom;
	CAtlArray<CString> m_ResIDs;
	CAtlArray<HandlerFunction> m_SupHandlers;
	int m_iSelectedHandler;
	CAtlArray<CString> m_Classes;
	int m_iSelectedClass;
	bool m_bAllowSelectClasses;
	CAtlArray<CString> m_Messages;
	int m_iSelMessage;
	// set of flags to enable/disable ability code, id and range
	DWORD m_fEnabledFeatures;

	enum { IDD = IDD_DIALOG_ID_HANDLER };

	CString CreateFunctionName(CString TrancatedID);
	void UpdateFunctionName();
		
	BEGIN_MSG_MAP(CHandlerIDDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
		COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
		COMMAND_CODE_HANDLER(BN_CLICKED, OnClick)
		
		COMMAND_HANDLER_EX(IDC_EDIT_ID, CBN_SELCHANGE, OnEditIdSelchange)
		COMMAND_HANDLER_EX(IDC_EDIT_ID, CBN_EDITCHANGE, OnEditIdEditchange)
		COMMAND_HANDLER_EX(IDC_EDIT_ID, CBN_DROPDOWN, OnEditIdDropDown)
		
		COMMAND_HANDLER_EX(IDC_COMBO_END_ID, CBN_EDITCHANGE, OnEditIdEditchange)
		COMMAND_HANDLER_EX(IDC_COMBO_END_ID, CBN_SELCHANGE, OnEditIdSelchange)
		COMMAND_HANDLER_EX(IDC_COMBO_END_ID, CBN_DROPDOWN, OnEditIdDropDown)

		COMMAND_HANDLER_EX(IDC_STATIC_MESSAGE, EN_CHANGE, OnStaticMessageEnChange)
		COMMAND_HANDLER_EX(IDC_STATIC_MESSAGE, CBN_EDITCHANGE, OnStaticMessageEnChange)
		COMMAND_HANDLER_EX(IDC_STATIC_MESSAGE, CBN_SELCHANGE, OnStaticMessageCbnSelchange)
		COMMAND_HANDLER(IDC_STATIC_MESSAGE, EN_UPDATE, OnStaticMessageEnUpdate)
		COMMAND_HANDLER(IDC_STATIC_MESSAGE, CBN_EDITUPDATE, OnStaticMessageEnUpdate)

		COMMAND_HANDLER(IDC_COMBO_FUNCTION, CBN_SELCHANGE, OnComboFunctionSelchange)
		COMMAND_HANDLER(IDC_COMBO_FUNCTION, CBN_EDITCHANGE, OnComboFunctionEditchange)
		COMMAND_HANDLER(IDC_COMBO_FUNCTION, CBN_DROPDOWN, OnComboFunctionCbnDropdown)
	END_MSG_MAP()

	BEGIN_DDX_MAP(CHandlerIDDlg)
		DDX_TEXT(IDC_COMBO_FUNCTION, m_Function)
		DDX_TEXT(IDC_STATIC_MESSAGE, m_Message)
		DDX_TEXT(IDC_EDIT_ID, m_ID)
		DDX_TEXT(IDC_COMBO_END_ID, m_LastID)
		DDX_CHECK(IDC_CHECK_STYLE, m_Style)
		DDX_CHECK(IDC_CHECK_REFLECTED, m_bReflected)
		DDX_CHECK(IDC_CHECK_CODE, m_bHandlerCode)
		DDX_CHECK(IDC_CHECK_ID, m_bHandlerID)
		DDX_CHECK(IDC_CHECK_RANGE, m_bRange)
		DDX_CHECK(IDC_CHECK_INLINE, m_bInline)
	END_DDX_MAP()

	BEGIN_TOOLTIP_MAP(CHandlerDlg)
		TIP_CHILDWND(IDC_CHECK_STYLE, IDS_TOOLTIP_NEW_STYLE)
		TIP_CHILDWND(IDC_CHECK_INLINE, IDS_TOOLTIP_INLINE)
		TIP_CHILDWND(IDC_CHECK_REFLECTED, IDS_TOOLTIP_REFLECTED)
		TIP_CHILDWND(IDC_CHECK_ID, IDS_TOOLTIP_ID)
		TIP_CHILDWND(IDC_CHECK_CODE, IDS_TOOLTIP_CODE)
		TIP_CHILDWND(IDC_CHECK_RANGE, IDS_TOOLTIP_RANGE)
	END_TOOLTIP_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEditIdSelchange(WORD wNotifyCode, WORD wID, HWND hWndCtl);
	LRESULT OnEditIdEditchange(WORD wNotifyCode, WORD wID, HWND hWndCtl);
	LRESULT OnEditIdDropDown(WORD wNotifyCode, WORD wID, HWND hWndCtl);
	LRESULT OnStaticMessageCbnSelchange(WORD wNotifyCode, WORD wID, HWND hWndCtl);

	LRESULT OnStaticMessageEnChange(WORD wNotifyCode, WORD wID, HWND hWndCtl);
	LRESULT OnStaticMessageEnUpdate(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnComboFunctionSelchange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnComboFunctionEditchange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnComboFunctionCbnDropdown(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};
