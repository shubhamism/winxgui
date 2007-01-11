////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	FunctionPage.h
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

// FunctionPage.h : Declaration of the CFunctionPage

#pragma once

#include <atlcrack.h>
#include "../RegArchive.h"
#include "../resources/Resources.h"
#include "../common.h"
#include "../HandlerManager.h"
#include <atlctrlx.h>
#include <atlsplit.h>
#include "SizeListCtrl.h"
#include "../MessageManager.h"
#include "../FunctionManager.h"
#include "../resource.h"
#include "atllttmap.h"

// CFunctionPage

struct CWindowFuncSettings : public CSettings<CWindowFuncSettings>
{
	int m_MesSpitPos;
	int m_FuncSplitPos;
	int m_HandlerHeaderWidth;

	BEGIN_SETTINGS_MAP()
		SETTINGS_VARIABLE_OPT(m_MesSpitPos)
		SETTINGS_VARIABLE_OPT(m_FuncSplitPos);
		SETTINGS_VARIABLE_OPT(m_HandlerHeaderWidth)
	END_SETTINGS_MAP()

	CWindowFuncSettings() : m_MesSpitPos(-1), m_FuncSplitPos(-1),m_HandlerHeaderWidth(120)
	{
	}
};

#define ID_ADD_HANDLER		FIRST_TOOLBAR_COMMAND
#define ID_DELETE_HANDLER	(FIRST_TOOLBAR_COMMAND + 1)
#define ID_ADD_FUNC			(FIRST_TOOLBAR_COMMAND + 3)
#define ID_DELETE_FUNC		(FIRST_TOOLBAR_COMMAND + 4)
#define ID_ADD_SPEC_FUNC	(FIRST_TOOLBAR_COMMAND + 5)
#define ID_ADD_MAP			(FIRST_TOOLBAR_COMMAND + 6)
#define ID_DELETE_MAP		(FIRST_TOOLBAR_COMMAND + 7)

#define IDC_MESSAGES		216
#define IDC_HANDLERS_LIST	207
#define IDC_FUNCTION_LIST	206

#define FUNC_BUTTON_COUNT	9

class CFunctionPage : 
	public CDialogImpl<CFunctionPage>,
	public CSettings<CFunctionPage>,
	public CToolTipMapImpl<CFunctionPage>
{
	VSMessageMap* m_pMessageMap;

	CPaneContainer m_FunctionContainer;
	CListBox m_Functions;

	CPaneContainer m_HandlerContaner;
	CSizeListCtrl m_Handlers;

	CPaneContainer m_MessagesContainer;
	CTreeViewCtrl m_Messages;

	CComboBox m_ClassCombo;
	
	CSplitterWindowT<true> m_SplitMessages;
	CSplitterWindowT<false> m_SplitFunctions;

	CComboBox m_MessageMaps;
	CAtlArray<HandlerStruct> m_HandlersMap;

	bool m_bShowWindow;

	CAtlArray<CString> m_GeneralResources;
	CWindowFuncSettings m_WindowSettings;
	CImageList m_ToolbarImgList;

	static TBBUTTON s_FuncButtons[FUNC_BUTTON_COUNT];
	
	void CreateControls();
	void LoadSettings();
	void SaveSettings();
	void LoadGeneralResources();
protected:
	CMessageManager m_MessageManager;
	CFunctionManager m_FunctionManager;

	COLORREF m_clWindowsText;
	COLORREF m_clWindowsBack;
	COLORREF m_clCommandText;
	COLORREF m_clCommandBack;
	COLORREF m_clNotifyText;
	COLORREF m_clNotifyBack;
	COLORREF m_clReflectText;
	COLORREF m_clReflectBack;

	void FillTreeView();
	void FillTreeView(HTREEITEM hRootItem, MessageStruct* pMes);
	CString LoadToolTip(int ID);
public:
	CFunctionPage(): m_piCurrentClass(NULL), m_bShowWindow(false), m_clWindowsText(CLR_NONE),
		m_clWindowsBack(CLR_NONE), m_clCommandText(CLR_NONE), m_clCommandBack(CLR_NONE), 
		m_clNotifyText(CLR_NONE), m_clNotifyBack(CLR_NONE), m_pMessageMap(NULL),
		m_clReflectBack(CLR_NONE), m_clReflectText(CLR_NONE)
	{
		LoadSettings();
	}

	~CFunctionPage()
	{
	}
	
	int* m_piCurrentClass;
	ClassVector* m_pClassVector;
	CSmartAtlArray<InsDelPoints>* m_pModifications;
	CResourceManager* m_pResManager;
	
	static void FillFuncButtons();
	void UpdateToolBar(HWND hWndToolBar);

	void SetModified(BOOL bModified = TRUE);

	bool GetModify();
	void UpdateClass(void);
	void UpdateForwardReflect();
	void AddHandler(HandlerStruct* pHandler, bool bNew = false);
	HTREEITEM FindMessage(CString Message, HTREEITEM RootItem);

	enum { IDD = IDD_FUNCTION_PROPPAGE };

	BEGIN_MSG_MAP(CFunctionPage)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
		MESSAGE_HANDLER(WM_VKEYTOITEM, OnVkeytoitem)
		MESSAGE_HANDLER(WTLH_SETACTIVE, OnSetActive)

		COMMAND_ID_HANDLER(IDC_COMBO_CLASSES, OnCbnSelchangeComboClass)
		COMMAND_HANDLER(IDC_COMBO_MESSAGEMAP, CBN_SELCHANGE, OnCbnSelchangeComboMessagemap)
		COMMAND_HANDLER(IDC_CHECK_REFLECT, BN_CLICKED, OnReflectBnClicked)
		COMMAND_HANDLER(IDC_FUNCTION_LIST, LBN_DBLCLK, OnFunctionListLbnDblclk)
		COMMAND_ID_HANDLER(ID_ADD_HANDLER, OnBnClickedButtonAddHandler)
		COMMAND_ID_HANDLER(ID_DELETE_HANDLER, OnBnClickedButtonDelHandler)
		COMMAND_ID_HANDLER(ID_ADD_FUNC, OnBnClickedButtonAddFunc)
		COMMAND_ID_HANDLER(ID_DELETE_FUNC, OnBnClickedButtonDelFunc)
		COMMAND_ID_HANDLER(ID_ADD_MAP, OnAddMap)
		COMMAND_ID_HANDLER(ID_DELETE_MAP, OnDeleteMap)

		NOTIFY_HANDLER(IDC_MESSAGES, NM_DBLCLK, OnLbnDblclkMessagesList)
		NOTIFY_HANDLER(IDC_MESSAGES, TVN_ITEMEXPANDED, OnTvnItemExpanded)
		NOTIFY_HANDLER_EX(IDC_HANDLERS_LIST, NM_DBLCLK, OnHandlerListNmDblclk)
		NOTIFY_CODE_HANDLER(HDN_ITEMCHANGED, OnHdnEndTrack)
		NOTIFY_HANDLER(IDC_HANDLERS_LIST, LVN_KEYDOWN, OnHandlerListlvnKeyDown)
		NOTIFY_CODE_HANDLER(TBN_DROPDOWN, OnToolbarDropDown)
		
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	BEGIN_SETTINGS_MAP()
		SETTINGS_VARIABLE_OPT_RO(m_clWindowsText)
		SETTINGS_VARIABLE_OPT_RO(m_clWindowsBack)
		SETTINGS_VARIABLE_OPT_RO(m_clCommandText)
		SETTINGS_VARIABLE_OPT_RO(m_clCommandBack)
		SETTINGS_VARIABLE_OPT_RO(m_clNotifyText)
		SETTINGS_VARIABLE_OPT_RO(m_clNotifyBack)
		SETTINGS_VARIABLE_OPT_RO(m_clReflectText)
		SETTINGS_VARIABLE_OPT_RO(m_clReflectBack)
		SETTINGS_CHILD_RO_USE_PARENT(m_WindowSettings)
		SETTINGS_CHILD_RO_USE_PARENT(m_MessageManager)
		SETTINGS_CHILD_RO_USE_PARENT(m_FunctionManager)
	END_SETTINGS_MAP()

	BEGIN_TOOLTIP_MAP(CFunctionPage)
		TIP_CHILDWND(m_Messages, LoadToolTip(IDS_TOOLTIP_MESSAGES))
		TIP_CHILDWND(m_Functions, LoadToolTip(IDS_TOOLTIP_FUNCTIONS))
		TIP_CHILDWND(m_Handlers, LoadToolTip(IDS_TOOLTIP_HANDLERS))
		TIP_CHILDWND(IDC_CHECK_REFLECT, LoadToolTip(IDS_TOOLTIP_REFLECT_NOTIFICATIONS))
		TIP_CHILDWND(IDC_CHECK_FORWARD, LoadToolTip(IDS_TOOLTIP_FORWARD_NOTIFICATIONS))
		TIP_CHILDWND(IDC_CHECK_DEF_HANDLER, LoadToolTip(IDS_TOOLTIP_DEFAULT_HANDLER))
		TIP_CHILDWND(IDC_CHECK_REFLECT_EX, LoadToolTip(IDS_TOOLTIP_REFLECT_NOTIFICATIONS_EX))
	END_TOOLTIP_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnVkeytoitem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSetActive(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnBnClickedButtonAddFunc(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnBnClickedButtonDelFunc(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnBnClickedButtonAddHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnBnClickedButtonDelHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnLbnDblclkMessagesList(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnCbnSelchangeComboClass(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCbnSelchangeComboMessagemap(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnReflectBnClicked(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnFunctionListLbnDblclk(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnAddMap(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnDeleteMap(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	
	LRESULT OnTvnDeleteItem(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnTvnItemExpanded(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnHandlerListNmDblclk(LPNMHDR pnmh);
	LRESULT OnHdnEndTrack(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnHandlerListlvnKeyDown(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnToolbarDropDown(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
};


