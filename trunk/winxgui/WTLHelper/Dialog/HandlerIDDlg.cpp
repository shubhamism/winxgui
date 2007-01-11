////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	HandlerIDDlg.cpp
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

// HandlerDlg.cpp : Implementation of CHandlerDlg

#include "stdafx.h"
#include "HandlerIDDlg.h"
#include "../common.h"

// CHandlerDlg
CHandlerIDDlg::CHandlerIDDlg():m_Style(TRUE), m_bHandlerID(TRUE), m_bHandlerCode(TRUE),
m_bReflected(FALSE), m_bInline(FALSE), m_bInitDialog(FALSE), m_bCustom(FALSE), 
m_bRange(FALSE), m_iSelectedHandler(-1), m_bAllowSelectClasses(false), m_iSelectedClass(0), 
m_iSelMessage(-1), m_fEnabledFeatures(EF_ALL)
{
}

CHandlerIDDlg::~CHandlerIDDlg()
{
}

void CHandlerIDDlg::CheckFunctionName()
{
	for (size_t i = 0; i < m_SupHandlers.GetCount(); i++)
	{
		if (m_SupHandlers[i].pFunc->Name == m_Function)
		{
			m_iSelectedHandler = (int)i;
			GetDlgItem(IDC_CHECK_STYLE).EnableWindow(FALSE);
			return;
		}
	}
	m_iSelectedHandler = -1;
	GetDlgItem(IDC_CHECK_STYLE).EnableWindow(TRUE);
}

bool CHandlerIDDlg::IsMessageCombo()
{
	TCHAR Buf[256];
	::GetClassName(GetDlgItem(IDC_STATIC_MESSAGE), Buf, 256);
	Buf[255] = 0;
	if (!lstrcmpi(Buf, _T("COMBOBOX")))
		return true;
	else
		return false;
}

CString CHandlerIDDlg::CreateFunctionName(CString TrancatedID)
{
	return CreateIDName(TrancatedID);
}

void CHandlerIDDlg::UpdateFunctionName()
{
	CString NewName = _T("On");
	if (m_bHandlerID || m_bRange)
	{
		//вначале добавляем идентификатор
		CString TrancatedID;
		if (m_ID.Left(4) == _T("IDC_"))
		{
			TrancatedID = m_ID.Mid(4);
		}
		else if (m_ID.Left(3) == _T("ID_"))
		{
			TrancatedID = m_ID.Mid(3);
		}
		else
		{
			TrancatedID = m_ID;
		}
		NewName += CreateFunctionName(TrancatedID);
		if (m_bRange)
		{
			if (m_LastID.Left(4) == _T("IDC_"))
			{
				TrancatedID = m_LastID.Mid(4);
			}
			else if (m_LastID.Left(3) == _T("ID_"))
			{
				TrancatedID = m_LastID.Mid(3);
			}
			else
			{
				TrancatedID = m_LastID;
			}
			NewName += CreateFunctionName(TrancatedID);
		}
	}
	//потом код
	if (m_bHandlerCode)
	{
		CString TrancatedCode;
		TrancatedCode = m_Message;
		if (!m_DefMessage.IsEmpty() && m_DefMessage == m_Message)
		{
			NewName += m_DefFunc;
		}
		else
		{
			NewName += CreateFunctionName(TrancatedCode);
		}
	}
	m_Function = NewName;
	CheckFunctionName();
}

LRESULT CHandlerIDDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CenterWindow(GetParent());

	CComboBox ClassCombo = GetDlgItem(IDC_COMBO_CLASSES);
	for (size_t i = 0; i < m_Classes.GetCount(); i++)
	{
		ClassCombo.AddString(m_Classes[i]);
	}
	ClassCombo.SetCurSel(m_iSelectedClass);
	if (!m_bAllowSelectClasses)
	{
		ClassCombo.EnableWindow(FALSE);
	}
	ClassCombo.Detach();
	if (m_Messages.GetCount() && (m_iSelMessage != -1))
	{
		CRect rc;
		GetDlgItem(IDC_STATIC_MESSAGE).GetWindowRect(rc);
		HFONT hFont = GetDlgItem(IDC_STATIC_MESSAGE).GetFont();
		GetDlgItem(IDC_STATIC_MESSAGE).DestroyWindow();
		ScreenToClient(rc);
		CComboBox MesCombo;
		MesCombo.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE | CBS_AUTOHSCROLL | CBS_DROPDOWN, 0, IDC_STATIC_MESSAGE);
		MesCombo.SetFont(hFont);
		for (size_t i = 0; i < m_Messages.GetCount(); i++)
		{
			MesCombo.AddString(m_Messages[i]);
		}
		MesCombo.SetCurSel(m_iSelMessage);
		m_Message = m_Messages[m_iSelMessage];
		MesCombo.Detach();
	}

	//fill ID's combos
	CComboBox StartCombo = GetDlgItem(IDC_EDIT_ID);
	CComboBox EndCombo = GetDlgItem(IDC_COMBO_END_ID);
	int iSelId1 = -1, iSelId2 = -1;
	for (size_t i = 0; i < m_ResIDs.GetCount(); i++)
	{
		StartCombo.AddString(m_ResIDs.GetAt(i));
		if (m_ResIDs[i] == m_ID)
		{
			iSelId1 = (int)i;
		}
		EndCombo.AddString(m_ResIDs.GetAt(i));
		if (m_ResIDs[i] == m_LastID)
		{
			iSelId2 = (int)i;
		}
	}
	if (iSelId1 != -1)
	{
		StartCombo.SetCurSel(iSelId1);
	}

	if (iSelId2 != -1)
	{
		EndCombo.SetCurSel(iSelId2);
	}

	CComboBox FuncCombo = GetDlgItem(IDC_COMBO_FUNCTION);
	for (size_t i = 0; i < m_SupHandlers.GetCount(); i++)
	{
		int iItem = FuncCombo.AddString(m_SupHandlers[i].pFunc->Name);
		if (iItem != CB_ERR)
		{
			FuncCombo.SetItemData(iItem, (DWORD_PTR)i);
		}
	}

	if (!m_bHandlerCode && !IsMessageCombo())
	{
		GetDlgItem(IDC_STATIC_MESSAGE).EnableWindow(FALSE);
	}
	
	if (!m_bHandlerID)
	{
		StartCombo.EnableWindow(FALSE);
	}
	else
	{
		if (m_ResIDs.GetCount() && m_ID.IsEmpty())
		{
			m_ID = m_ResIDs[0];
		}
	}
	if (!m_bRange)
	{
		EndCombo.EnableWindow(FALSE);
	}
	else
	{
		if (m_ResIDs.GetCount() && m_LastID.IsEmpty())
		{
			m_LastID = m_ResIDs[0];
		}
	}
	
	if (m_bCustom)
	{
		ATLASSERT(!IsMessageCombo());
		GetDlgItem(IDC_STATIC_MESSAGE).SendMessage(EM_SETREADONLY, FALSE, 0);
		m_Message.Empty();
	}
	m_DefMessage = m_Message;
	if (m_DefFunc.Left(2) == _T("On"))
		m_DefFunc.Delete(0, 2);
	
	StartCombo.Detach();
	EndCombo.Detach();
	FuncCombo.Detach();

	UpdateFunctionName();
	DoDataExchange();

	if (!(m_fEnabledFeatures & EF_ID))
	{
		GetDlgItem(IDC_CHECK_ID).EnableWindow(FALSE);
	}
	if (!(m_fEnabledFeatures & EF_CODE))
	{
		GetDlgItem(IDC_CHECK_CODE).EnableWindow(FALSE);
	}
	if (!(m_fEnabledFeatures & EF_RANGE))
	{
		GetDlgItem(IDC_CHECK_RANGE).EnableWindow(FALSE);
	}

	InitToolTip();
	m_ToolTip.SetMaxTipWidth(400);

	GetDlgItem(IDC_COMBO_FUNCTION).SetFocus();
	GetDlgItem(IDC_COMBO_FUNCTION).SendMessage(CB_SETEDITSEL, 0, -1);
		
	m_bInitDialog = TRUE;
	return 0;
}

LRESULT CHandlerIDDlg::OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	DoDataExchange(TRUE);
	if (m_bRange)
		m_bHandlerID = TRUE;
	
	if (m_Function.IsEmpty())
	{
		MessageBox(_T("Function name must not be empty"));
		return 1;
	}
	if (!m_bHandlerID && !m_bHandlerCode)
	{
		MessageBox(_T("Handler use \'code\' and \'id\' must not be false at the same time"));
		return 1;
	}

	if (m_bHandlerID && m_ID.IsEmpty())
	{
		MessageBox(_T("Field ID must not be empty"));
		return 1;
	}
	m_iSelectedClass = (int)GetDlgItem(IDC_COMBO_CLASSES).SendMessage(CB_GETCURSEL);
	EndDialog(wID);
	return 0;
}

LRESULT CHandlerIDDlg::OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}

LRESULT CHandlerIDDlg::OnClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (wID == IDC_CHECK_ID)
	{
		DoDataExchange(TRUE, IDC_CHECK_ID);
		if (m_bHandlerID)
		{
			if (!m_bRange)
			{
				GetDlgItem(IDC_EDIT_ID).EnableWindow();
				GetDlgItem(IDC_EDIT_ID).SendMessage(CB_SETCURSEL, 0, 0);
			}
			DoDataExchange(TRUE, IDC_EDIT_ID);
			UpdateFunctionName();
			DoDataExchange(FALSE, IDC_COMBO_FUNCTION);
		}
		else
		{
			if (!m_bRange)
			{
				GetDlgItem(IDC_EDIT_ID).EnableWindow(FALSE);
			}

			UpdateFunctionName();
			DoDataExchange(FALSE, IDC_COMBO_FUNCTION);
		}
	}
	if (wID == IDC_CHECK_CODE)
	{
		DoDataExchange(TRUE, IDC_CHECK_CODE);
		if (m_bHandlerCode)
		{
			DoDataExchange(TRUE, IDC_STATIC_MESSAGE);
			GetDlgItem(IDC_STATIC_MESSAGE).EnableWindow(TRUE);
			
			UpdateFunctionName();
			DoDataExchange(FALSE, IDC_COMBO_FUNCTION);
		}
		else
		{
			GetDlgItem(IDC_STATIC_MESSAGE).EnableWindow(FALSE);
			UpdateFunctionName();
			DoDataExchange(FALSE, IDC_COMBO_FUNCTION);
		}
	}
	if (wID == IDC_CHECK_RANGE)
	{
		DoDataExchange(TRUE, IDC_CHECK_RANGE);
		if (m_bRange)
		{
			DoDataExchange(FALSE, IDC_CHECK_ID);
			if (!m_bHandlerID)
			{
				GetDlgItem(IDC_EDIT_ID).EnableWindow(TRUE);
				GetDlgItem(IDC_EDIT_ID).SendMessage(CB_SETCURSEL, 0, 0);
			}
			GetDlgItem(IDC_COMBO_END_ID).EnableWindow(TRUE);
			GetDlgItem(IDC_COMBO_END_ID).SendMessage(CB_SETCURSEL, 0, 0);
			
			DoDataExchange(TRUE, IDC_COMBO_END_ID);
			UpdateFunctionName();
			DoDataExchange(FALSE, IDC_COMBO_FUNCTION);
		}
		else
		{
			GetDlgItem(IDC_COMBO_END_ID).EnableWindow(FALSE);
			if (!m_bHandlerID)
			{
				GetDlgItem(IDC_EDIT_ID).EnableWindow(FALSE);
			}
			UpdateFunctionName();
			DoDataExchange(FALSE, IDC_COMBO_FUNCTION);
		}
	}
	return 0;
}

LRESULT CHandlerIDDlg::OnEditIdSelchange(WORD wNotifyCode, WORD wID, HWND hWndCtl)
{
	//составляем имя функции
	if (m_ResIDs.GetCount())
	{
		DoDataExchange(TRUE);
		CComboBox FirstCombo(GetDlgItem(IDC_EDIT_ID));
		CComboBox SecondCombo(GetDlgItem(IDC_COMBO_END_ID));

		int iSel = FirstCombo.GetCurSel();
		FirstCombo.GetLBText(iSel, m_ID);
		iSel = SecondCombo.GetCurSel();
		SecondCombo.GetLBText(iSel, m_LastID);

		UpdateFunctionName();
		DoDataExchange(FALSE, IDC_COMBO_FUNCTION);
		FirstCombo.Detach();
		SecondCombo.Detach();
	}
	return 0;
}
LRESULT CHandlerIDDlg::OnEditIdEditchange(WORD wNotifyCode, WORD wID, HWND hWndCtl)
{
	DoDataExchange(TRUE);
	UpdateFunctionName();
	DoDataExchange(FALSE, IDC_COMBO_FUNCTION);

	return 0;
}

LRESULT CHandlerIDDlg::OnEditIdDropDown(WORD wNotifyCode, WORD wID, HWND hWndCtl)
{
	if (!m_ResIDs.GetCount())
	{
		// add fake item to prevent show invisible listbox
		DoDataExchange(TRUE, wID);
		CComboBox IDCombo = GetDlgItem(wID);
		int Count = IDCombo.GetCount();
		ATLASSERT(Count == 1 || Count == 0);
		for (int i = 0; i < Count; i++)
		{
			IDCombo.DeleteString(0);
		}
		if (wID == IDC_EDIT_ID)
		{
			IDCombo.AddString(m_ID);
		}
		if (wID == IDC_COMBO_END_ID)
		{
			IDCombo.AddString(m_LastID);
		}
		IDCombo.Detach();
	}
	return 0;
}

LRESULT CHandlerIDDlg::OnStaticMessageEnChange(WORD wNotifyCode, WORD wID, HWND hWndCtl)
{
	if (m_bInitDialog)
	{
		DoDataExchange(TRUE, IDC_STATIC_MESSAGE);
		DoDataExchange(TRUE, IDC_CHECK_CODE);
		UpdateFunctionName();
		DoDataExchange(FALSE, IDC_COMBO_FUNCTION);
	}
	return 0;
}

LRESULT CHandlerIDDlg::OnStaticMessageEnUpdate(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CString Message;
	GetDlgItem(IDC_STATIC_MESSAGE).GetWindowText(Message);
	int Pos;
	if (!IsMessageCombo())
	{
		GetDlgItem(IDC_STATIC_MESSAGE).SendMessage(EM_GETSEL, (WPARAM)&Pos, 0);
	}
	else
	{
		GetDlgItem(IDC_STATIC_MESSAGE).SendMessage(CB_GETEDITSEL, (WPARAM)&Pos, 0);
	}
	Pos--;
	if (Pos >=0 && Message[Pos] == _T(' '))
	{
		Message.Delete(Pos);
		GetDlgItem(IDC_STATIC_MESSAGE).SetWindowText(Message);
		if (!IsMessageCombo())
		{
			GetDlgItem(IDC_STATIC_MESSAGE).SendMessage(EM_SETSEL, Pos, Pos);
		}
		else
		{
			GetDlgItem(IDC_STATIC_MESSAGE).SendMessage(CB_SETEDITSEL, 0, MAKELONG(Pos, Pos));
		}
		MessageBeep(MB_OK);
	}
	return 0;
}

LRESULT CHandlerIDDlg::OnComboFunctionEditchange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	DoDataExchange(TRUE, IDC_COMBO_FUNCTION);
	CheckFunctionName();
	return 0;
}

LRESULT CHandlerIDDlg::OnComboFunctionSelchange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	// we add fake item if no items in m_SupHandlers
	// so we do not have to change anything
	if (m_SupHandlers.GetCount())
	{
		CComboBox ComboFunc = GetDlgItem(IDC_COMBO_FUNCTION);
		int iSelItem = ComboFunc.GetCurSel();
		m_iSelectedHandler = (int)ComboFunc.GetItemData(iSelItem);
		if (m_SupHandlers[m_iSelectedHandler].Type & HANDLER_EX)
		{
			GetDlgItem(IDC_CHECK_STYLE).SendMessage(BM_SETCHECK, BST_CHECKED, 0);
		}
		else
		{
			GetDlgItem(IDC_CHECK_STYLE).SendMessage(BM_SETCHECK, BST_UNCHECKED, 0);
		}
		ComboFunc.Detach();
		GetDlgItem(IDC_CHECK_STYLE).EnableWindow(FALSE);
	}
	return 0;
}

LRESULT CHandlerIDDlg::OnComboFunctionCbnDropdown(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (!m_SupHandlers.GetCount())
	{
		// add fake item to prevent show invisible listbox
		DoDataExchange(TRUE, IDC_COMBO_FUNCTION);
		CComboBox FuncCombo = GetDlgItem(IDC_COMBO_FUNCTION);
		int Count = FuncCombo.GetCount();
		ATLASSERT(Count == 1 || Count == 0);
		for (int i = 0; i < Count; i++)
		{
			FuncCombo.DeleteString(0);
		}
		FuncCombo.AddString(m_Function);
		FuncCombo.Detach();
	}
	return 0;
}

LRESULT CHandlerIDDlg::OnStaticMessageCbnSelchange(WORD wNotifyCode, WORD wID, HWND hWndCtl)
{
	if (m_bInitDialog)
	{
		CComboBox ComboMes = GetDlgItem(IDC_STATIC_MESSAGE);
		int iCurSel = ComboMes.GetCurSel();
		ComboMes.GetLBText(iCurSel, m_Message);
		DoDataExchange(TRUE, IDC_CHECK_CODE);
		UpdateFunctionName();
		DoDataExchange(FALSE, IDC_COMBO_FUNCTION);
	}
	return 0;
}