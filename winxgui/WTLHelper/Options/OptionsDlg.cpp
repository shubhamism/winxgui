////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	OptionsDlg.cpp
// Created:	21.12.2004 10:46
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

// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OptionsDlg.h"

COptionsDlg::COptionsDlg()
{
	m_tabbedChildWindow.KeepTabsHidden(false);
}

void COptionsDlg::CreateCtrls()
{
	m_tabbedChildWindow.SetReflectNotifications(true);
	m_tabbedChildWindow.SetTabStyles(CTCS_TOOLTIPS | CTCS_DRAGREARRANGE);
	CRect rc, trc, dlgrc;
	rc.left = rc.top = 0;
	CRect r1(0, 0, 8, 8);
	MapDialogRect(r1);

	GetDlgItem(IDOK).GetWindowRect(&trc);
	GetClientRect(&dlgrc);
	ScreenToClient(&trc);
	rc.bottom = trc.top - r1.Height();
	rc.right = dlgrc.right;
	int MinWidth = dlgrc.right - trc.left + r1.Width();
	int ButtonHeight = dlgrc.bottom - trc.top + r1.Height();

	m_tabbedChildWindow.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_STATICEDGE);
	m_DDXForm.Create(m_tabbedChildWindow);
	m_FuncOpt.Create(m_tabbedChildWindow);
	m_AboutDlg.Create(m_tabbedChildWindow);
	m_CommonOpt.Create(m_tabbedChildWindow);

	m_DDXForm.GetWindowRect(&trc);
	CRect trc2;
	m_FuncOpt.GetWindowRect(&trc2);
	
	int Width, Height;
	Width = max(trc.Width(), trc2.Width());
	Height = max(trc.Height(), trc2.Height());
	m_AboutDlg.GetWindowRect(&trc);
	Width = max(trc.Width(), Width);
	Height = max(trc.Height(), Height);

	Width = max(Width, MinWidth);
	int TabHeight = m_tabbedChildWindow.GetTabAreaHeight();
	Height += ButtonHeight + TabHeight;
	Width = (Width - dlgrc.Width());
	Height = (Height - dlgrc.Height());
	rc.bottom += Height;
	rc.right += Width;
	GetWindowRect(&dlgrc);
	dlgrc.InflateRect(Width / 2, Height / 2);
	MoveWindow(&dlgrc);
	m_tabbedChildWindow.MoveWindow(&rc);

	m_tabbedChildWindow.AddTab(m_FuncOpt, _T("Functions"));
	m_tabbedChildWindow.AddTab(m_DDXForm, _T("Variables"));
	m_tabbedChildWindow.AddTab(m_CommonOpt, _T("General"));
	m_tabbedChildWindow.AddTab(m_AboutDlg, _T("About"));
	
	GetDlgItem(IDOK).GetWindowRect(&trc);
	GetDlgItem(IDCANCEL).GetWindowRect(&trc2);
	int ButtonOffsetX, ButtonOffsetY;
	
	ButtonOffsetX = dlgrc.right - trc2.right - r1.Width();
	ButtonOffsetY = dlgrc.bottom - trc2.bottom - r1.Height();
	trc.OffsetRect(ButtonOffsetX, ButtonOffsetY);
	trc2.OffsetRect(ButtonOffsetX, ButtonOffsetY);
	ScreenToClient(&trc);
	ScreenToClient(&trc2);
	GetDlgItem(IDOK).MoveWindow(&trc);
	GetDlgItem(IDCANCEL).MoveWindow(&trc2);
}

LRESULT COptionsDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// center the dialog on the screen
	CenterWindow();
	CreateCtrls();

	return TRUE;
}

LRESULT COptionsDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_DDXForm.SaveOptions();
	m_FuncOpt.SaveOptions();
	m_CommonOpt.SaveOptions();
	EndDialog(wID);
	return 0;
}

LRESULT COptionsDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(wID);
	return 0;
}
