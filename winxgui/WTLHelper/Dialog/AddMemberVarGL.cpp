////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	AddMemberVarGL.cpp
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
#include ".\addmembervargl.h"

CAddMemberVarGl::CAddMemberVarGl():m_bPublic(TRUE), m_bPrivate(FALSE), 
m_bProtected(FALSE), m_pClassVector(NULL), m_pCurClass(NULL), m_bStatic(FALSE),
m_bVirtual(FALSE), m_bConst(FALSE), m_AddType(ADD_TYPE_FUNCTION)
{
}

CAddMemberVarGl::~CAddMemberVarGl(void)
{
}

LRESULT CAddMemberVarGl::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	DoDataExchange();
	CenterWindow();
	SetWindowText(m_Caption);
	GetDlgItem(IDC_STATIC1).SetWindowText(m_Static);
	m_ClassBox = GetDlgItem(IDC_COMBO1);

	if (m_pClassVector)
	{
		for (size_t i = 0; i < m_pClassVector->GetCount(); i++)
		{
			int k1 = m_ClassBox.AddString((*m_pClassVector)[i]->Name);
			m_ClassBox.SetItemDataPtr(k1, (*m_pClassVector)[i]);
			if ((*m_pClassVector)[i] == m_pCurClass)
			{
				m_ClassBox.SetCurSel(k1);
			}
		}
	}

	if (m_AddType == ADD_TYPE_VARIABLE)
	{
		GetDlgItem(IDC_CHECK3).ShowWindow(SW_HIDE);
	}
	
	GetDlgItem(IDC_EDIT_DEF).SetFocus();
	
	return 0;
}

LRESULT CAddMemberVarGl::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	EndDialog(IDCANCEL);
	return 0;
}

LRESULT CAddMemberVarGl::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	DoDataExchange(TRUE);
	//получаем тип
	int StartType = 0;
	CString Delim = _T(" \t\r\n");
	int n1 ,n2;
	BOOL bConst = FALSE;

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
			bConst = TRUE;
			StartType = n2;

			continue;
		}
		StartType = -1;
	}
	if (bConst && m_AddType == ADD_TYPE_FUNCTION)
	{
		m_Type = _T("const ") + m_Type;
	}
	else
	{
		m_bConst |= bConst;
	}

	m_Body = m_Edit.Mid(n2);
	m_Body.TrimRight();
	
	int k1 = m_ClassBox.GetCurSel();
	if (k1 != -1) 
	{
		m_pCurClass = (VSClass*)m_ClassBox.GetItemDataPtr(k1);
	}
	else
	{
		m_pCurClass = NULL;
	}

	EndDialog(IDOK);
	return 0;
}

LRESULT CAddMemberVarGl::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(IDCANCEL);
	return 0;
}

void CAddMemberVarGl::SetForFunction()
{
	m_Caption = _T("Add Function");
	m_Static = _T("Full function definition");
	m_AddType = ADD_TYPE_FUNCTION;
}

void CAddMemberVarGl::SetForVar()
{
	m_Caption = _T("Add Variable");
	m_Static = _T("Full variable definition");
	m_bPublic = FALSE;
	m_bPrivate = TRUE;
	m_AddType = ADD_TYPE_VARIABLE;
}