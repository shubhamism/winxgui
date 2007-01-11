////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	TypeCStringDlg.cpp
// Created:	01.12.2004 9:48
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

// TypeCStringDlg.cpp : Implementation of CTypeCStringDlg

#include "stdafx.h"
#include "TypeCStringDlg.h"


// CTypeCStringDlg

CTypeCStringDlg:: CTypeCStringDlg() : m_bAskAgain(false), m_Type(0), m_Place(-1)
{
}
 
CTypeCStringDlg::~ CTypeCStringDlg()
{
}
  
LRESULT CTypeCStringDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CenterWindow();
	DoDataExchange();
	if (!m_bStdAfx)
	{
		GetDlgItem(IDC_RADIO_PLACE_WHOLE).EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_TYPE_ATL).EnableWindow(FALSE);
	}
	OnBnClickRadioTypeAnother(0, 0, NULL, bHandled);
	return 1;  // Let the system set the focus
}

LRESULT CTypeCStringDlg::OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	DoDataExchange(TRUE);
	
	EndDialog(wID);
	return 0;
}

LRESULT CTypeCStringDlg::OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}

LRESULT CTypeCStringDlg::OnBnClickRadioTypeAnother(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	GetDlgItem(IDC_RADIO_PLACE_WHOLE).EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_PLACE_H).EnableWindow(FALSE);
	if (GetDlgItem(IDC_RADIO_PLACE_WHOLE).SendMessage(BM_GETCHECK) == BST_CHECKED)
	{
		GetDlgItem(IDC_RADIO_PLACE_WHOLE).SendMessage(BM_SETCHECK, BST_UNCHECKED);
	}
	if (GetDlgItem(IDC_RADIO_PLACE_H).SendMessage(BM_GETCHECK) == BST_CHECKED)
	{
		GetDlgItem(IDC_RADIO_PLACE_H).SendMessage(BM_SETCHECK, BST_UNCHECKED);
	}
	return 0;
}

LRESULT CTypeCStringDlg::OnBnClickRadioTypeWtl(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_bStdAfx)
		GetDlgItem(IDC_RADIO_PLACE_WHOLE).EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_PLACE_H).EnableWindow(TRUE);
	if (GetDlgItem(IDC_RADIO_PLACE_WHOLE).SendMessage(BM_GETCHECK) != BST_CHECKED &&
		GetDlgItem(IDC_RADIO_PLACE_H).SendMessage(BM_GETCHECK) != BST_CHECKED)
	{
		GetDlgItem(IDC_RADIO_PLACE_WHOLE).SendMessage(BM_SETCHECK, BST_CHECKED);
	}
	return 0;
}

LRESULT CTypeCStringDlg::OnBnClickRadioTypeAtl(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_bStdAfx)
	{
		if (GetDlgItem(IDC_RADIO_PLACE_WHOLE).SendMessage(BM_GETCHECK) != BST_CHECKED)
		{
			//GetDlgItem(IDC_RADIO_PLACE_WHOLE).CheckRadioButton(IDC_RADIO_PLACE_WHOLE, IDC_RADIO_PLACE_CPP, IDC_RADIO_PLACE_WHOLE);
			CheckRadioButton(IDC_RADIO_PLACE_WHOLE, IDC_RADIO_PLACE_H, IDC_RADIO_PLACE_WHOLE);
		}
		GetDlgItem(IDC_RADIO_PLACE_WHOLE).EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_PLACE_H).EnableWindow(FALSE);
	}
	else
	{
		return OnBnClickRadioTypeAnother(wNotifyCode, wID, hWndCtl, bHandled);
	}
	return 0;
}