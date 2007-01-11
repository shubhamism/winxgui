////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	AddMemberVar.cpp
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

#include "StdAfx.h"
#include ".\addmembervar.h"

CAddMemberVar::CAddMemberVar():m_bPublic(TRUE), m_bPrivate(FALSE), m_bProtected(FALSE),m_bStatic(FALSE),
m_bVirtual(FALSE), m_bConst(FALSE)
{
}

CAddMemberVar::~CAddMemberVar(void)
{
}

LRESULT CAddMemberVar::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	DoDataExchange();
	CenterWindow();
	SetWindowText(m_Caption);
	GetDlgItem(IDC_STATIC1).SetWindowText(m_Static);
	GetDlgItem(IDC_EDIT_DEF).SetFocus();
	
	return 0;
}

LRESULT CAddMemberVar::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	EndDialog(IDCANCEL);
	return 0;
}

LRESULT CAddMemberVar::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int StartType = 0;
	CString Delim = _T(" \t\r\n");
	int n1 ,n2;

	DoDataExchange(TRUE);
	while(StartType >= 0)
	{
		n1 = m_Edit.Mid(StartType).FindOneOf(Delim) + StartType;
		if (n1 == -1)
		{
			MessageBox(_T("Wrong definition"));
			return 0;
		}

		n2 = n1;
		while((Delim.Find(m_Edit[n2]) != -1) && (n2 < m_Edit.GetLength()))
		{
			n2++;
		}
		//не совсем правильно, но в больштнстве случаев работает
		m_Type = m_Edit.Left(n1);
		m_Type.TrimLeft();
		if (m_Type == _T("static"))
		{
			m_bStatic = TRUE;
			StartType = n2;
			continue;
		}
		if (m_Type == _T("virtual"))
		{
			m_bVirtual = TRUE;
			StartType = n2;
			continue;
		}
		if (m_Type == _T("const"))
		{
			m_bConst = TRUE;
			StartType = n2;
			continue;
		}
		StartType = -1;
	}
	m_Body = m_Edit.Mid(n2);
	m_Body.TrimRight(_T(" \t\r\n;"));
	
	EndDialog(IDOK);
	return 0;
}

LRESULT CAddMemberVar::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(IDCANCEL);
	return 0;
}

void CAddMemberVar::SetForFunction()
{
	m_Caption = _T("Add Function");
	m_Static = _T("Full function definition");
}

void CAddMemberVar::SetForVar()
{
	m_Caption = _T("Add Variable");
	m_Static = _T("Full variable definition");
	m_bPublic = FALSE;
	m_bPrivate = TRUE;
}