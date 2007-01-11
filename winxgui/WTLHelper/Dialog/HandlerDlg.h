////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	HandlerDlg.h
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

#include "../resource.h"
#include "atllttmap.h"
// CHandlerDlg

class CHandlerDlg : 
	public CDialogImpl<CHandlerDlg>,
	public CWinDataExchange<CHandlerDlg>,
	public CToolTipMapImpl<CHandlerDlg>
{
public:
	CHandlerDlg() : m_Style(TRUE), m_bInline(FALSE), m_bCustom(FALSE), 
		m_iSelectedHandler(-1)
	{
	}

	~CHandlerDlg()
	{
	}

	CString m_DefFunc;
	CString m_Function;
	CString m_Message;
	BOOL m_Style;
	BOOL m_bInline;
	BOOL m_bCustom;

	CAtlArray<HandlerFunction> m_SupHandlers;
	int m_iSelectedHandler;

	enum { IDD = IDD_DIALOG_HANDLER };

	BEGIN_MSG_MAP(CHandlerDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
		COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
		COMMAND_HANDLER(IDC_STATIC_MESSAGE, EN_CHANGE, OnStaticMessageEnChange)
		COMMAND_HANDLER(IDC_STATIC_MESSAGE, EN_UPDATE, OnStaticMessageEnUpdate)
		COMMAND_HANDLER(IDC_COMBO_FUNCTION, CBN_SELCHANGE, OnComboFunctionSelchange)
		COMMAND_HANDLER(IDC_COMBO_FUNCTION, CBN_EDITCHANGE, OnComboFunctionEditchange)
	END_MSG_MAP()

	BEGIN_DDX_MAP(CHandlerDlg)
		DDX_TEXT(IDC_COMBO_FUNCTION, m_Function)
		DDX_TEXT(IDC_STATIC_MESSAGE, m_Message)
		DDX_CHECK(IDC_CHECK_STYLE, m_Style)
		DDX_CHECK(IDC_CHECK_INLINE, m_bInline);
	END_DDX_MAP()

	BEGIN_TOOLTIP_MAP(CHandlerDlg)
		TIP_CHILDWND(IDC_CHECK_STYLE, IDS_TOOLTIP_NEW_STYLE)
		TIP_CHILDWND(IDC_CHECK_INLINE, IDS_TOOLTIP_INLINE)
	END_TOOLTIP_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_Function = m_DefFunc;
		CenterWindow(GetParent());

		if (m_bCustom)
		{
			GetDlgItem(IDC_STATIC_MESSAGE).SendMessage(EM_SETREADONLY, 0, 0);
			m_Message.Empty();
			GetDlgItem(IDC_STATIC_MESSAGE).SetFocus();
		}
		else
		{
			GetDlgItem(IDC_COMBO_FUNCTION).SetFocus();
		}
		CComboBox ComboFunc = GetDlgItem(IDC_COMBO_FUNCTION);
		for (size_t i = 0; i < m_SupHandlers.GetCount(); i++)
		{
			int iPos = ComboFunc.AddString(m_SupHandlers[i].pFunc->Name);
			ComboFunc.SetItemData(iPos, i);
		}
		DoDataExchange();
		InitToolTip();
		m_ToolTip.SetMaxTipWidth(400);

		ComboFunc.SetEditSel(0, -1);
		ComboFunc.Detach();
		return 0;  // Let the system set the focus
	}

	LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		DoDataExchange(TRUE);
		EndDialog(wID);
		return 0;
	}

	LRESULT OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	LRESULT OnStaticMessageEnChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		CString Message;
		GetDlgItem(IDC_STATIC_MESSAGE).GetWindowText(Message);
		if (Message == m_Message && !m_DefFunc.IsEmpty())
		{
			GetDlgItem(IDC_COMBO_FUNCTION).SetWindowText(m_DefFunc);
			return 0;
		}
		CString FuncName = _T("On");
		FuncName += CreateIDName(Message);
		
		GetDlgItem(IDC_COMBO_FUNCTION).SetWindowText(FuncName);
		return 0;
	}

	LRESULT OnStaticMessageEnUpdate(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		CString Message;
		GetDlgItem(IDC_STATIC_MESSAGE).GetWindowText(Message);
		int Pos;
		GetDlgItem(IDC_STATIC_MESSAGE).SendMessage(EM_GETSEL, (WPARAM)&Pos, 0);
		Pos--;
		if (Pos >=0 && Message[Pos] == _T(' '))
		{
			Message.Delete(Pos);
			GetDlgItem(IDC_STATIC_MESSAGE).SetWindowText(Message);
			GetDlgItem(IDC_STATIC_MESSAGE).SendMessage(EM_SETSEL, Pos, Pos);
			MessageBeep(MB_OK);
		}
		return 0;
	}

	LRESULT OnComboFunctionSelchange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		CComboBox ComboFunc = GetDlgItem(IDC_COMBO_FUNCTION);
		int iSelItem = ComboFunc.GetCurSel();
		m_iSelectedHandler = (int)ComboFunc.GetItemData(iSelItem);
		ComboFunc.Detach();

		GetDlgItem(IDC_CHECK_STYLE).EnableWindow(FALSE);
		return 0;
	}

	LRESULT OnComboFunctionEditchange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		DoDataExchange(TRUE, IDC_COMBO_FUNCTION);
		for (size_t i = 0; i < m_SupHandlers.GetCount(); i++)
		{
			if (m_SupHandlers[i].pFunc->Name == m_Function)
			{
				m_iSelectedHandler = (int)i;
							
				GetDlgItem(IDC_CHECK_STYLE).EnableWindow(FALSE);
				return 0;
			}
		}
		m_iSelectedHandler = -1;
		GetDlgItem(IDC_CHECK_STYLE).EnableWindow(TRUE);
		return 0;
	}
};
