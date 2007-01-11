////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	TypeCStringDlg.h
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

// TypeCStringDlg.h : Declaration of the CTypeCStringDlg

#pragma once

#include "../resource.h"
// CTypeCStringDlg

#define STYPE_ANOTHER	0
#define STYPE_WTL		1
#define STYPE_ATL		2

#define SPLACE_WHOLE	0
#define SPLACE_H		1

class CTypeCStringDlg : 
	public CDialogImpl<CTypeCStringDlg>,
	public CWinDataExchange<CTypeCStringDlg>
{
public:
	CTypeCStringDlg();
	~CTypeCStringDlg();
	
	enum { IDD = IDD_TYPECSTRINGDLG };

    BEGIN_MSG_MAP(CTypeCStringDlg)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
        COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
		COMMAND_HANDLER(IDC_RADIO_TYPE_ANOTHER, BN_CLICKED, OnBnClickRadioTypeAnother)
		COMMAND_HANDLER(IDC_RADIO_TYPE_WTL, BN_CLICKED, OnBnClickRadioTypeWtl)
		COMMAND_HANDLER(IDC_RADIO_TYPE_ATL, BN_CLICKED, OnBnClickRadioTypeAtl)
    END_MSG_MAP()
	
	BEGIN_DDX_MAP(CTypeCStringDlg)
		DDX_RADIO(IDC_RADIO_TYPE_ANOTHER, m_Type)
		DDX_RADIO(IDC_RADIO_PLACE_WHOLE, m_Place)
		DDX_CHECK(IDC_CHECK1, m_bAskAgain)
	END_DDX_MAP()
	
	int m_Type;
	int m_Place;
	bool m_bAskAgain;
	//true if stdafx.h exists
	bool m_bStdAfx;

    // Handler prototypes:
    //  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    //  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
    //  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnBnClickRadioTypeAnother(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnBnClickRadioTypeWtl(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnBnClickRadioTypeAtl(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};


