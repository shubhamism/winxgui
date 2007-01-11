////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	AddMemberVarGL.h
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
#include "..\vselements.h"
#include "../resource.h"

#define ADD_TYPE_FUNCTION	1
#define ADD_TYPE_VARIABLE	2

class CAddMemberVarGl :
	public CDialogImpl<CAddMemberVarGl>,
	public CWinDataExchange<CAddMemberVarGl>
{
	CString m_Edit;
	int m_AddType;
public:
	CAddMemberVarGl();
	~CAddMemberVarGl();
	
	CString m_Caption;
	CString m_Static;
	CComboBox m_ClassBox;

	CString m_Type;
	CString m_Body;
	
	BOOL m_bPrivate;
	BOOL m_bProtected;
	BOOL m_bPublic;

	BOOL m_bVirtual;
	BOOL m_bConst;
	BOOL m_bStatic;

	CSmartAtlArray<VSClass*>* m_pClassVector;
	VSClass* m_pCurClass;

	enum { IDD = IDD_DIALOG_ADD_FUNC_GLOBAL};

	BEGIN_MSG_MAP(CAddMemberVarGl)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_CLOSE, OnClose);

		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	END_MSG_MAP()

	BEGIN_DDX_MAP(CAddMemberVarGl)
		DDX_TEXT(IDC_EDIT_DEF, m_Edit)
		DDX_CHECK(IDC_RADIO1, m_bPublic)
		DDX_CHECK(IDC_RADIO2, m_bProtected)
		DDX_CHECK(IDC_RADIO3, m_bPrivate)

		DDX_CHECK(IDC_CHECK1, m_bStatic)
		DDX_CHECK(IDC_CHECK2, m_bConst)
		DDX_CHECK(IDC_CHECK3, m_bVirtual)
	END_DDX_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void SetForFunction();
	void SetForVar();
};
