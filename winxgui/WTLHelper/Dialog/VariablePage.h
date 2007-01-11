////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	VariablePage.h
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

// VariablePage.h : Declaration of the CVariablePage

#pragma once

#include "../resource.h"
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atlsplit.h>
#include "SizeListCtrl.h"
#include "../DDXManager.h"
#include "atllttmap.h"

// CVariablePage
#define FIRST_DDX_COMMAND	(FIRST_TOOLBAR_COMMAND + 30)
#define ID_ADD_VAR			FIRST_DDX_COMMAND
#define ID_DELETE_VAR		(FIRST_DDX_COMMAND + 1)
#define ID_ADD_CUSTOM_VAR	(FIRST_DDX_COMMAND + 2)

#define IDC_LIST_IDS	212
#define IDC_LIST_VARS	213

struct CVarPageWindowSettings : public CSettings<CVarPageWindowSettings>
{
	int m_IdsSplitPos;
	int m_VariableWidth;
	CVarPageWindowSettings() : m_IdsSplitPos(200), m_VariableWidth(120)
	{
	}
	
	BEGIN_SETTINGS_MAP()
		SETTINGS_VARIABLE_OPT(m_IdsSplitPos)
		SETTINGS_VARIABLE_OPT(m_VariableWidth)
	END_SETTINGS_MAP()
};

class CVariablePage : 
	public CDialogImpl<CVariablePage>,
	public CSettings<CVariablePage>,
	public CToolTipMapImpl<CVariablePage>
{
	VSMap* m_pDDXMap;
	CVarPageWindowSettings m_WindowSettings;

	CSplitterWindow m_SplitIds;
	CPaneContainer m_IdsContainer;
	CListBox m_IDs;

	CPaneContainer m_VariablesContainer;
	CSizeListCtrl m_Variables;
	bool m_bShowWindow;

	CDDXManager m_DDXManager;

	void LoadSettings();
	void SaveSettings();
	void CreateControls();

	void UpdateIDs(VSClass* pClass);
	void AddMapEntry(CString ID, CString Var, VSMapEntry* pMapEntry);
	CString LoadToolTip(int ID);
public:
	CVariablePage():m_bOnlyDlgs(true), m_bShowWindow(false)
	{
		LoadSettings();
	}

	~CVariablePage()
	{
	}

	enum { IDD = IDD_VARIABLEPAGE };
	
	CComboBox m_Classes;
	bool m_bOnlyDlgs;

	CSmartAtlArray<InsDelPoints>* m_pModifications;
	ClassVector* m_pClassVector;
	int* m_piCurrentClass;
	CResourceManager* m_pResManager;
	CImageList m_ToolbarImgList;

	void UpdateToolBar(HWND hWndToolBar);
	void SetModified(BOOL bModified = TRUE);

	BEGIN_MSG_MAP(CVariablePage)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
		MESSAGE_HANDLER(WTLH_SETACTIVE, OnSetActive)

		COMMAND_HANDLER(IDC_COMBO_CLASSES, CBN_SELCHANGE, OnCbnSelchange)
		COMMAND_HANDLER(IDC_LIST_IDS, LBN_DBLCLK, OnListIdsLbnDblclk)
		COMMAND_ID_HANDLER(ID_ADD_VAR, OnAddVar)
		COMMAND_ID_HANDLER(ID_DELETE_VAR, OnDelVar)

		NOTIFY_CODE_HANDLER(HDN_ITEMCHANGED, OnHdnEndTrack)
		NOTIFY_HANDLER(IDC_LIST_VARS, LVN_KEYDOWN, OnListVarsKeydown)

		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	BEGIN_SETTINGS_MAP()
		SETTINGS_VARIABLE_OPT_RO(m_bOnlyDlgs)
	END_SETTINGS_MAP()

	BEGIN_TOOLTIP_MAP(CVariablePage)
		TIP_CHILDWND(m_IDs, LoadToolTip(IDS_TOOLTIP_IDS))
	END_TOOLTIP_MAP()
	// Handler prototypes:
	//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSetActive(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnAddVar(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnDelVar(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCbnSelchange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnListIdsLbnDblclk(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnHdnEndTrack(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnListVarsKeydown(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
};

