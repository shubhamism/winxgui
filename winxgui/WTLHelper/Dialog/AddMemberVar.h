////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	AddMemberVar.h
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

#pragma once

#include "../resource.h"

class CAddMemberVar :
	public CDialogImpl<CAddMemberVar>,
	public CWinDataExchange<CAddMemberVar>
{
	CString m_Edit;
public:
	CAddMemberVar();
	~CAddMemberVar();
	
	CString m_Caption;
	CString m_Static;

	CString m_Type;
	CString m_Body;
	
	BOOL m_bVirtual;
	BOOL m_bConst;
	BOOL m_bStatic;

	BOOL m_bPrivate;
	BOOL m_bProtected;
	BOOL m_bPublic;
	enum { IDD = IDD_DIALOG_ADD_FUNC};

	BEGIN_MSG_MAP(CAddMemberVar)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_CLOSE, OnClose);

		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	END_MSG_MAP()

	BEGIN_DDX_MAP(CAddMemberVar)
		DDX_TEXT(IDC_EDIT_DEF, m_Edit)
		DDX_CHECK(IDC_RADIO1, m_bPublic)
		DDX_CHECK(IDC_RADIO2, m_bProtected)
		DDX_CHECK(IDC_RADIO3, m_bPrivate)
	END_DDX_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void SetForFunction();
	void SetForVar();
};
