////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	FunctionPage.cpp
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

// FunctionPage.cpp : Implementation of CFunctionPage

#include "stdafx.h"
#include "../VSElements.h"
#include "FunctionPage.h"
#include "HandlerDlg.h"
#include "HandlerIDDlg.h"
#include "AddMemberVar.h"
#include ".\functionpage.h"
#include "../InsertPoint.h"
#include "AddAltMapDlg.h"

LPCTSTR RegPath = _T("Software\\Salos\\WtlHelper");
LPCTSTR FunctionName = _T("Messages");

void CFunctionPage::CreateControls()
{
	m_ClassCombo.Attach(GetDlgItem(IDC_COMBO_CLASSES));
	CRect r1;
	HFONT hFont = GetFont();

	m_ClassCombo.GetWindowRect(&r1);
	ScreenToClient(&r1);

	m_SplitMessages.Create(m_hWnd, rcDefault, NULL,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	m_SplitMessages.SetSplitterExtendedStyle(0);

	m_MessagesContainer.Create(m_SplitMessages, _T("Messages"));
	m_MessagesContainer.SetPaneContainerExtendedStyle(PANECNT_NOCLOSEBUTTON, PANECNT_NOCLOSEBUTTON);
	m_Messages.Create(m_MessagesContainer, NULL, NULL, WS_VISIBLE | WS_CHILD | TVS_HASBUTTONS | 
		TVS_HASLINES | WS_TABSTOP, WS_EX_CLIENTEDGE, IDC_MESSAGES);
	m_Messages.SetFont(hFont);
	m_MessagesContainer.SetClient(m_Messages);

	m_SplitFunctions.Create(m_SplitMessages, rcDefault, NULL,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	m_SplitMessages.SetSplitterExtendedStyle(0);

	m_HandlerContaner.Create(m_SplitFunctions, _T("Handlers"));
	m_HandlerContaner.SetPaneContainerExtendedStyle(PANECNT_NOCLOSEBUTTON, PANECNT_NOCLOSEBUTTON);
	m_Handlers.Create(m_HandlerContaner, NULL, NULL, 0, 0, IDC_HANDLERS_LIST);
	m_Handlers.SendMessage(CCM_SETVERSION, 5);
	m_Handlers.SetFont(hFont);
	m_HandlerContaner.SetClient(m_Handlers);

	m_FunctionContainer.Create(m_SplitFunctions, _T("Functions"));
	m_FunctionContainer.SetPaneContainerExtendedStyle(PANECNT_NOCLOSEBUTTON, PANECNT_NOCLOSEBUTTON);
	m_Functions.Create(m_FunctionContainer, NULL, NULL, WS_CHILD | WS_VISIBLE | LBS_SORT | 
		LBS_NOINTEGRALHEIGHT | WS_VSCROLL | WS_TABSTOP | LBS_NOTIFY | LBS_WANTKEYBOARDINPUT,  WS_EX_CLIENTEDGE, IDC_FUNCTION_LIST);
	m_Functions.SetFont(hFont);
	m_FunctionContainer.SetClient(m_Functions);

	m_SplitFunctions.SetSplitterPanes(m_HandlerContaner, m_FunctionContainer);
	m_SplitMessages.SetSplitterPanes(m_MessagesContainer, m_SplitFunctions);
}

void CFunctionPage::FillTreeView(HTREEITEM hRootItem, MessageStruct* pMes)
{
	if ((int)_AtlModule.m_eWTLVersion < eWTL75 && pMes->Type & REFLECTION_MESSAGE)
		return;

	TVITEM* tvi;
	TVINSERTSTRUCT tvis;
	ZeroMemory(&tvis, sizeof(tvis));
	tvi = &tvis.item;
	tvi->mask = TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvi->lParam = (LPARAM)pMes;
	CString Name = pMes->Message;

	LPTSTR pName = Name.LockBuffer();
	tvi->pszText = pName;
	tvi->cchTextMax = Name.GetLength() + 1;
	int Type = pMes->Type & TYPE_MASK;
	if (pMes->IconIndex == -1)
	{
		if (Type == ROOT_PLACE)
		{
			tvi->iImage = 0;
			tvi->iSelectedImage = 0;
		}
		else
		{
			tvi->iImage = 2;
			tvi->iSelectedImage = 2;
		}
	}
	else
	{
		tvi->iSelectedImage = tvi->iImage = pMes->IconIndex;
	}
	tvi->cChildren = 0;
	tvis.hParent = hRootItem;
	int Flags = pMes->Type & FLAGS_MASK;
	if (Flags & CUSTOM_MESSAGE)
	{
		tvis.hInsertAfter = TVI_LAST;
	}
	else
	{
		tvis.hInsertAfter = TVI_SORT;
	}
	HTREEITEM NewItem = m_Messages.InsertItem(&tvis);
	Name.UnlockBuffer();

	if (Type == ROOT_PLACE)
	{
		for (size_t i = 0; i < pMes->Children.GetCount(); i++)
		{
			FillTreeView(NewItem, pMes->Children[i]);
		}
	}
}

void CFunctionPage::FillTreeView()
{
	MessageStruct* pMes = CMessageManager::m_sHandlerManager.GetRootMessage();
	ATLASSERT(pMes);
	if (!pMes)
		return;
	FillTreeView(NULL, pMes);
}

CString CFunctionPage::LoadToolTip(int ID)
{
	CString str;
	str.LoadString(ID);
	return str;
}

void CFunctionPage::LoadSettings()
{
	CRegArchive RegSettings;
	if (RegSettings.Open(HKEY_CURRENT_USER, RegPath, false))
	{
		if (!CSettings<CFunctionPage>::LoadSettings(RegSettings, FunctionName))
		{
			RegSettings.Close();
			return;
		}
		RegSettings.Close();
	}
}

void CFunctionPage::SaveSettings()
{
	if (m_bShowWindow)
	{
		m_WindowSettings.m_FuncSplitPos = m_SplitFunctions.GetSplitterPos();
		m_WindowSettings.m_MesSpitPos = m_SplitMessages.GetSplitterPos();
		m_WindowSettings.m_HandlerHeaderWidth = m_Handlers.GetColumnWidth(0);

		CRegArchive RegArchive;
		if (RegArchive.Open(HKEY_CURRENT_USER, RegPath, true))
		{
			m_WindowSettings.SaveSettings(RegArchive, FunctionName);
			RegArchive.Close();
		}
	}
}

void CFunctionPage::LoadGeneralResources()
{
	m_GeneralResources.RemoveAll();
	m_pResManager->GetMenuIds(m_GeneralResources);
	m_pResManager->GetAcceleratorIds(m_GeneralResources);
	m_pResManager->GetToolbarIds(m_GeneralResources);
	
	//сортировка
	SortStringArray(m_GeneralResources);
	//удаление повторяющихся идентификаторов
	CString PrevWord;
	for (int i = (int)m_GeneralResources.GetCount() - 1; i >= 0; i--)
	{
		if (m_GeneralResources[i] == PrevWord)
		{
			m_GeneralResources.RemoveAt(i);
		}
		else
		{
			PrevWord = m_GeneralResources[i];
		}
	}
}

TBBUTTON CFunctionPage::s_FuncButtons[FUNC_BUTTON_COUNT];

void CFunctionPage::FillFuncButtons()
{
	memset(s_FuncButtons, 0, FUNC_BUTTON_COUNT * sizeof(TBBUTTON));
	s_FuncButtons[0].idCommand = ID_ADD_HANDLER;
	s_FuncButtons[0].iBitmap = 0;
	s_FuncButtons[0].fsState = TBSTATE_ENABLED;
	s_FuncButtons[0].fsStyle = TBSTYLE_BUTTON;
	
	s_FuncButtons[1].idCommand = ID_DELETE_HANDLER;
	s_FuncButtons[1].iBitmap = 1;
	s_FuncButtons[1].fsState = TBSTATE_ENABLED;
	s_FuncButtons[1].fsStyle = TBSTYLE_BUTTON;

	s_FuncButtons[2].idCommand = ID_SEPARATOR;
	s_FuncButtons[2].iBitmap = -1;
	s_FuncButtons[2].fsStyle = TBSTYLE_SEP;

	s_FuncButtons[3].idCommand = ID_ADD_FUNC;
	s_FuncButtons[3].iBitmap = 2;
	s_FuncButtons[3].fsState = TBSTATE_ENABLED;
	s_FuncButtons[3].fsStyle = TBSTYLE_BUTTON;

	s_FuncButtons[4].idCommand = ID_DELETE_FUNC;
	s_FuncButtons[4].iBitmap = 3;
	s_FuncButtons[4].fsState = TBSTATE_ENABLED;
	s_FuncButtons[4].fsStyle = TBSTYLE_BUTTON;

	s_FuncButtons[5].idCommand = ID_ADD_SPEC_FUNC;
	s_FuncButtons[5].iBitmap = 4;
	s_FuncButtons[5].fsState = TBSTATE_ENABLED;
	s_FuncButtons[5].fsStyle = BTNS_WHOLEDROPDOWN;

	s_FuncButtons[6].idCommand = ID_SEPARATOR;
	s_FuncButtons[6].iBitmap = -1;
	s_FuncButtons[6].fsStyle = TBSTYLE_SEP;

	s_FuncButtons[7].idCommand = ID_ADD_MAP;
	s_FuncButtons[7].iBitmap = 5;
	s_FuncButtons[7].fsState = TBSTATE_ENABLED;
	s_FuncButtons[7].fsStyle = TBSTYLE_BUTTON;

	s_FuncButtons[8].idCommand = ID_DELETE_MAP;
	s_FuncButtons[8].iBitmap = 6;
	s_FuncButtons[8].fsState = TBSTATE_ENABLED;
	s_FuncButtons[8].fsStyle = TBSTYLE_BUTTON;
}

void CFunctionPage::UpdateToolBar(HWND hWndToolBar)
{
	CToolBarCtrl ToolBar(hWndToolBar);
	ToolBar.SetImageList(m_ToolbarImgList);
	int Count = ToolBar.GetButtonCount();
	int i;
	int nSeps = 0;
	for (i = 0; i < min(Count, FUNC_BUTTON_COUNT); i++)
	{
		TBBUTTONINFO tb;
		tb.cbSize = sizeof(tb);
		tb.dwMask = 0;
		if (s_FuncButtons[i].fsStyle != TBSTYLE_SEP)
		{
			tb.dwMask = TBIF_IMAGE;
			tb.iImage = s_FuncButtons[i].iBitmap;
		}
		
		tb.fsStyle = s_FuncButtons[i].fsStyle;
		tb.dwMask |= TBIF_STYLE | TBIF_BYINDEX | TBIF_COMMAND;
		tb.idCommand = s_FuncButtons[i].idCommand;
		ToolBar.SetButtonInfo(i, &tb);
	}
	if (Count < FUNC_BUTTON_COUNT)
	{
		int Delta = FUNC_BUTTON_COUNT - Count;
		ToolBar.AddButtons(Delta, &s_FuncButtons[Count]);
	}
	if (Count > FUNC_BUTTON_COUNT)
	{
		for (i = Count - 1; i >= FUNC_BUTTON_COUNT; i--)
		{
			ToolBar.DeleteButton(i);
		}
	}
	ToolBar.Detach();
}

LRESULT CFunctionPage::OnSetActive(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int iCurSel = m_ClassCombo.GetCurSel();
	if (iCurSel != *m_piCurrentClass)
	{
		m_ClassCombo.SetCurSel(*m_piCurrentClass);
		OnCbnSelchangeComboClass(CBN_SELCHANGE, 0, NULL, bHandled);
	}
	UpdateToolBar((HWND)wParam);
	return 0;
}

void CFunctionPage::SetModified(BOOL bModified /* = TRUE */)
{
	GetParent().GetParent().SendMessage(WTLH_SETMODIFIED, bModified);
}

LRESULT CFunctionPage::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = TRUE;
	START_PROFILE(FuncInit);
	m_MessageMaps.Attach(GetDlgItem(IDC_COMBO_MESSAGEMAP));
	m_MessageManager.Init(m_hWnd, m_pResManager, &m_GeneralResources);
	m_FunctionManager.Init(m_hWnd);

	CreateControls();

	CImageList ImageList;
	ImageList.Create(16, 16, ILC_COLOR24 | ILC_MASK, 3, 2);
	ImageList.AddIcon(LoadIcon(_AtlModule.GetResourceInstance(), MAKEINTRESOURCE(IDI_ICON_CLOSE)));
	ImageList.AddIcon(LoadIcon(_AtlModule.GetResourceInstance(), MAKEINTRESOURCE(IDI_ICON_OPEN)));
	ImageList.AddIcon(LoadIcon(_AtlModule.GetResourceInstance(), MAKEINTRESOURCE(IDI_ICON_MESSAGE)));
	ImageList.Add(LoadBitmap(_AtlModule.GetResourceInstance(), MAKEINTRESOURCE(IDB_BITMAP_ICONS)), 0x7C00FF);

	m_Messages.SetImageList(ImageList.Detach(), TVSIL_NORMAL);
	FillTreeView();

	//построение дерева
	HTREEITEM hRoot = m_Messages.GetRootItem();
	m_Messages.Expand(hRoot);
	HTREEITEM hRootChild = m_Messages.GetChildItem(hRoot);
	while(hRootChild)
	{
		m_Messages.Expand(hRootChild);
		hRootChild = m_Messages.GetNextSiblingItem(hRootChild);
	}

	CRect r;
	m_Handlers.GetWindowRect(r);
	int width = m_WindowSettings.m_HandlerHeaderWidth; //(r.Width() * 5) / 11;
	m_Handlers.InsertColumn(0, _T("Handler"), LVCFMT_LEFT, width, 0);
	m_Handlers.InsertColumn(1, _T("Message"), LVCFMT_LEFT, r.Width() - width-5, 1);
	m_Handlers.SetExtendedListViewStyle(LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

	if (m_pClassVector->GetCount())
	{
		int iCurClass = 0;
		for (size_t i = 0; i < m_pClassVector->GetCount(); i++)
		{
			int iPos = m_ClassCombo.AddString((*m_pClassVector)[i]->Name);
			m_ClassCombo.SetItemData(iPos, i);
			if (i == *m_piCurrentClass)
				iCurClass = iPos;
		}
		m_ClassCombo.SetCurSel(iCurClass);
		UpdateClass();
	}

	LoadGeneralResources();
	m_ToolbarImgList.CreateFromImage(IDB_BITMAP_MESSAGE, 18, 6, RGB(197, 200,201), IMAGE_BITMAP, LR_CREATEDIBSECTION);
	InitToolTip();
	m_ToolTip.SetMaxTipWidth(400);
	if ((int)_AtlModule.m_eWTLVersion < eWTL75)
	{
		GetDlgItem(IDC_CHECK_REFLECT_EX).ShowWindow(SW_HIDE);
	}

	m_SplitMessages.SetFocus();
	END_PROFILE(FuncInit, _T("CFunctionPage::OnInitDialog"));
	return 0;
}

LRESULT CFunctionPage::OnTvnItemExpanded(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	NMTREEVIEW* pnmtv = (NMTREEVIEW*)pnmh;
	MessageStruct* pMes = (MessageStruct*)m_Messages.GetItemData(pnmtv->itemNew.hItem);
	if (pMes->IconIndex == -1)
	{
		if (pnmtv->action == TVE_COLLAPSE)
		{
			m_Messages.SetItemImage(pnmtv->itemNew.hItem, 0, 0);
		}
		if (pnmtv->action == TVE_EXPAND)
		{
			m_Messages.SetItemImage(pnmtv->itemNew.hItem, 1, 1);
		}
	}
	
	return 1;
}

LRESULT CFunctionPage::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (wParam == SIZE_RESTORED)
	{
		CRect rc, rc2;
		CWindow wnd = GetDlgItem(IDC_COMBO_CLASSES);
		wnd.GetWindowRect(rc);
		ScreenToClient(rc);
		CSize NewSize(LOWORD(lParam), HIWORD(lParam));
		
		CRect CheckRc(0, 0, 1,12);
		MapDialogRect(CheckRc);
		rc2.left = 0;
		rc2.right = NewSize.cx;
		rc2.top = rc.bottom + CheckRc.Height();
		rc2.bottom = NewSize.cy;
		m_SplitMessages.MoveWindow(rc2);

		if (!m_bShowWindow && lParam)
		{
			m_bShowWindow = true;
			m_SplitMessages.SetSplitterPos(m_WindowSettings.m_MesSpitPos);
			m_SplitFunctions.SetSplitterPos(m_WindowSettings.m_FuncSplitPos);
		}
	}
	return 0;
}

LRESULT CFunctionPage::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SaveSettings();

	m_Messages.DeleteAllItems();
	bHandled = TRUE;
	return 1;
}

LRESULT CFunctionPage::OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_Messages.SetFocus();
	return 0;
}

LRESULT CFunctionPage::OnBnClickedButtonAddFunc(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (wNotifyCode == BN_CLICKED)
	{
		VSFunction* pFunc = m_FunctionManager.AddFunction();
		if (pFunc)
		{
			int k1 = m_Functions.AddString(pFunc->Name);
			m_Functions.SetItemDataPtr(k1, pFunc);
		}
	}

	bHandled = TRUE;
	return 1;
}

LRESULT CFunctionPage::OnBnClickedButtonDelFunc(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	bHandled = TRUE;

	if (wNotifyCode == BN_CLICKED)
	{
		int n = m_Functions.GetCurSel();
		if (n == -1)
		{
			MessageBox(_T("No selected Items"));
			return 1;
		}

		if (MessageBox(_T("Are you realy want to delete function"), _T(""), MB_YESNO) == IDYES)
		{
			VSFunction* pListEntry = (VSFunction*)m_Functions.GetItemDataPtr(n);
			if (m_FunctionManager.DeleteFunction(pListEntry))
			{
				m_Functions.DeleteString(n);
				SetModified(TRUE);
			}
		}

	}

	return 1;
}

//////////////////////////////////////////////////////////////////////////
//Получаем выбранное сообщение, проверяем нет ли его уже в карте.
//После этого создаем новый обьект VSMapEntry и  VSFunction.
//Указатели на них копируются и в список функций (MapEntries) и в массив
//добавленных элементов для данного класса. При реальном добавлении 
//просто получаем нужные обекты среды в уже созданные обьекты
//////////////////////////////////////////////////////////////////////////

LRESULT CFunctionPage::OnBnClickedButtonAddHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	bHandled = FALSE;
	if (wNotifyCode == BN_CLICKED)
	{
		HTREEITEM hItem = m_Messages.GetSelectedItem();
		if (!hItem)
			return 1;

		MessageStruct* pMes = (MessageStruct*) m_Messages.GetItemData(hItem);
		if (!pMes)
		{
			MessageBox(_T("No selected items"));
			return 1;
		}
		if ((pMes->Type & TYPE_MASK) == ROOT_PLACE)
			return 1;
		if (CMessageManager::m_sHandlerManager.IsHandlerExist(pMes, m_pMessageMap))
		{
			MessageBox(_T("Handler for this message allready exists"));
			return 1;
		}

		if (!m_pMessageMap)
		{
			if (!m_MessageManager.AddMessageMap())
				return 1;
			m_pMessageMap = (VSMessageMap*)(*m_pClassVector)[*m_piCurrentClass]->GetMap(CString(_T("MSG")));
		}

		HandlerStruct Handler;
		switch(pMes->Type & TYPE_MASK) 
		{
		case CUSTOM_MESSAGE_HANDLER:
		case STD_MESSAGE_HANDLER:
			if (m_MessageManager.InsertWindowsMessageHandler(pMes, Handler))
			{
				AddHandler(CMessageManager::m_sHandlerManager.AddHandler(&Handler), true);
				SetModified(TRUE);
			}
			break;
		case STD_COMMAND_HANDLER:
		case CUSTOM_COMMAND_HANDLER:
			if (m_MessageManager.InsertCommandMessageHandler(pMes, Handler))
			{
				AddHandler(CMessageManager::m_sHandlerManager.AddHandler(&Handler), true);
				SetModified(TRUE);
			}
			break;
		case STD_NOTIFY_HANDLER:
		case CUSTOM_NOTIFY_HANDLER:
			if (m_MessageManager.InsertNotifyMessageHandler(pMes, Handler))
			{
				AddHandler(CMessageManager::m_sHandlerManager.AddHandler(&Handler), true);
				SetModified(TRUE);
			}
			break;
		case CUSTOM_NOTIFY_REFLECTION_HANDLER:
		case CUSTOM_COMMAND_REFLECTION_HANDLER:
		case CUSTOM_REFLECTION_HANDLER:
			if (m_MessageManager.InsertReflectionHandler(pMes, Handler))
			{
				AddHandler(CMessageManager::m_sHandlerManager.AddHandler(&Handler), true);
				SetModified(TRUE);
			}
			break;
		default:
			ATLASSERT(0);
		}
	}

	return 1;
}

LRESULT CFunctionPage::OnBnClickedButtonDelHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	bHandled = TRUE;
	if (wNotifyCode == BN_CLICKED)
	{
		int n = m_Handlers.GetSelectedIndex();
		if (n == -1)
		{
			MessageBox(_T("No selected items"));
			return 1;
		}

		if (MessageBox(_T("Are you realy want to delete handler"), _T(""), MB_YESNO) == IDYES)
		{
			HandlerStruct* pHandler = (HandlerStruct*)m_Handlers.GetItemData(n);
			
			if (m_MessageManager.DeleteHandler(pHandler))
			{
				m_Handlers.DeleteItem(n);
				SetModified(TRUE);
			}
		}
	}

	return 1;
}

LRESULT CFunctionPage::OnCbnSelchangeComboClass(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (wNotifyCode == CBN_SELCHANGE)
	{
		int iCurSel = m_ClassCombo.GetCurSel();
		if (iCurSel != -1)
		{
			(*m_piCurrentClass) = (int)m_ClassCombo.GetItemData(iCurSel);
			UpdateClass();
		}
	}
	bHandled = TRUE;
	return 1;
}

LRESULT CFunctionPage::OnCbnSelchangeComboMessagemap(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int iSel = m_MessageMaps.GetCurSel();

	VSClass* pClass = (*m_pClassVector)[*m_piCurrentClass];
	VSMessageMap* pRootMap = (VSMessageMap*)pClass->GetMap(CString(_T("MSG")));
	if (!pRootMap)
		return 0;

	if (iSel == 0)
	{
		m_pMessageMap = pRootMap;
		m_MessageManager.SetMessageMap(m_pMessageMap);
	}
	else
	{
		if (pRootMap->AltMaps.GetCount())
		{
			if (iSel - 1 <  (int)pRootMap->AltMaps.GetCount())
			{
				m_pMessageMap = pRootMap->AltMaps[iSel - 1];
				m_MessageManager.SetMessageMap(m_pMessageMap);
			}
		}
		if (iSel == pRootMap->AltMaps.GetCount() + 1)
		{
			if (m_MessageManager.InsertAltMap())
			{
				m_pMessageMap = pRootMap->AltMaps[iSel - 1];
				m_MessageManager.SetMessageMap(m_pMessageMap);
				m_MessageMaps.InsertString(m_MessageMaps.GetCount() - 1, m_pMessageMap->Name);
				m_MessageMaps.SetCurSel(iSel);
			}
			else
			{
				m_MessageMaps.SetCurSel(0);
				m_pMessageMap = pRootMap;
				m_MessageManager.SetMessageMap(m_pMessageMap);
			}
		}
	}

	m_Handlers.DeleteAllItems();
	bool bForward = false, bReflect = false;
	for (size_t j = 0; j != m_pMessageMap->MapEntries.GetCount(); j++)
	{
		if (m_pMessageMap->MapEntries[j]->Name == _T("FORWARD_NOTIFICATIONS"))
		{
			bForward = true;
			continue;
		}
		if (m_pMessageMap->MapEntries[j]->Name == _T("REFLECT_NOTIFICATIONS"))
		{
			bReflect = true;
			continue;
		}

		HandlerStruct* pHandler = CMessageManager::m_sHandlerManager.GetHandler(m_pMessageMap->MapEntries[j]);
		if (pHandler)
			AddHandler(pHandler);
	}
	if (bForward)
	{
		GetDlgItem(IDC_CHECK_FORWARD).SendMessage(BM_SETCHECK, BST_CHECKED);
	}
	else
	{
		GetDlgItem(IDC_CHECK_FORWARD).SendMessage(BM_SETCHECK, BST_UNCHECKED);
	}
	if (bReflect)
	{
		GetDlgItem(IDC_CHECK_REFLECT).SendMessage(BM_SETCHECK, BST_CHECKED);
	}
	else
	{
		GetDlgItem(IDC_CHECK_REFLECT).SendMessage(BM_SETCHECK, BST_UNCHECKED);
	}
	return 0;
}

LRESULT CFunctionPage::OnLbnDblclkMessagesList(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	return OnBnClickedButtonAddHandler(BN_CLICKED, 0, 0, bHandled);
}

LRESULT CFunctionPage::OnAddMap(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_pMessageMap)
	{
		MessageBox(_T("Message map already exists!"), NULL, MB_OK |MB_ICONINFORMATION);
	}
	else
	{
		m_MessageManager.AddMessageMap();
	}
	return 0;
}

LRESULT CFunctionPage::OnDeleteMap(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int Res = MessageBox(_T("Are you realy want to delete message map?"), NULL, MB_YESNO | MB_ICONQUESTION);
	if (Res == IDYES)
	{
		m_MessageManager.DeleteMap(m_pMessageMap);
		UpdateClass();
	}
	return 0;
}

bool CFunctionPage::GetModify()
{
	for (size_t i = 0; i < (*m_pModifications).GetCount(); i++)
	{
		if ((*m_pModifications)[i].InsertPoints.GetCount() || (*m_pModifications)[i].DeletePoint.GetCount())
			return true;
	}
	return false;
}

void CFunctionPage::AddHandler(HandlerStruct* pHandler, bool bNew /* = false */)
{
	ATLASSERT(pHandler);
	if (!pHandler)
		return;

	int iNext = m_Handlers.GetItemCount();
	CString FirstStr, SecondStr;
	FirstStr = pHandler->HandlerName;
	COLORREF BackColor;
	COLORREF TextColor;
	if (pHandler->Type & (HANDLER_TYPE_MESSAGE | HANDLER_TYPE_CRACK_MESSAGE))
	{
		SecondStr = pHandler->Message;
		BackColor = m_clWindowsBack;
		TextColor = m_clWindowsText;
	}
	else
	{
		if (pHandler->Type & HANDLER_TYPE_COMMAND_MESSAGE)
		{
			BackColor = m_clCommandBack;
			TextColor = m_clCommandText;
		}
		if (pHandler->Type & HANDLER_TYPE_NOTIFY_MESSAGE)
		{
			BackColor = m_clNotifyBack;
			TextColor = m_clNotifyText;
		}
		if (pHandler->Type & HANDLER_REFLECTION_MESSAGE ||
			pHandler->Type & HANDLER_REFLECTION_COMMAND ||
			pHandler->Type & HANDLER_REFLECTION_NOTIFY)
		{
			BackColor = m_clReflectBack;
			TextColor = m_clReflectText;
		}
		CString ID;
		if (pHandler->Type & HANDLER_RANGE)
		{
			ID.Format(_T("[%s .. %s]"), pHandler->FirstId, pHandler->LastId);
		}
		else
		{
			if (pHandler->Type & HANDLER_ID)
				ID = pHandler->FirstId;
			if (pHandler->Type & HANDLER_HWND)
				ID = pHandler->HWND;
		}
		if (ID.IsEmpty())
		{
			if (!pHandler->Code.IsEmpty())
			{
				SecondStr = pHandler->Code + _T(" - ") + pHandler->Message;
			}
			else
			{
				SecondStr = pHandler->Message;
			}
		}
		else
		{
			if (pHandler->Code.IsEmpty())
			{
				if (!pHandler->Message.IsEmpty())
					SecondStr = ID + _T(" - ") + pHandler->Message;
				else
					SecondStr = ID;
			}
			else
			{
				SecondStr = ID + _T(" - ") + pHandler->Code;
			}
		}
	}
	int k1 = m_Handlers.InsertItem(LVIF_TEXT | LVIF_PARAM, iNext, FirstStr, 0, 0, 0, (LPARAM)pHandler);
	m_Handlers.SetItem(k1 ,1, LVIF_TEXT, SecondStr, 0, 0, 0, 0);
	MyCustomDrawStruct mds;
	if (bNew)
	{
		mds.dwMask = MCDS_BACKCOLOR | MCDS_TEXTCOLOR | MCDS_STYLE;
		mds.dwStyle = SLC_STYLE_ITALIC;
	}
	else
	{
		mds.dwMask = MCDS_BACKCOLOR | MCDS_TEXTCOLOR;
		mds.dwStyle = 0;
	}
	mds.BackColor = BackColor;
	mds.TextColor = TextColor;
	
	m_Handlers.SetDrawStruct(k1, &mds);
}

void CFunctionPage::UpdateClass(void)
{
	//save previous FORWARD_NOTIFICATIONS, REFLECT_NOTIFICATIONS[_EX] for class
	if (m_pMessageMap)
		UpdateForwardReflect();

	m_Handlers.DeleteAllItems();
	m_Functions.ResetContent();
	m_MessageMaps.ResetContent();
	m_HandlersMap.RemoveAll();

	if ((*m_piCurrentClass) == -1)
		return;

	VSClass* pClass = (*m_pClassVector)[(*m_piCurrentClass)];
	if (m_MessageManager.SetClass(pClass, &(*m_pModifications)[(*m_piCurrentClass)]))
	{
		SetModified(TRUE);
	}
	m_FunctionManager.SetClass(pClass, &(*m_pModifications)[(*m_piCurrentClass)]);
	//добавление сообщений
	m_pMessageMap = NULL;
	m_pMessageMap = (VSMessageMap*)pClass->GetMap(CString(_T("MSG")));

	if (m_pMessageMap)
	{
		m_MessageMaps.EnableWindow();
		GetDlgItem(IDC_CHECK_FORWARD).EnableWindow();
		GetDlgItem(IDC_CHECK_REFLECT).EnableWindow();
		GetDlgItem(IDC_CHECK_DEF_HANDLER).EnableWindow();

		m_MessageMaps.AddString(_T("Default"));
		for (size_t j = 0; j != m_pMessageMap->MapEntries.GetCount(); j++)
		{
			HandlerStruct* pHandler = CMessageManager::m_sHandlerManager.AddMapEntry(m_pMessageMap->MapEntries[j]);
			if (pHandler)
			{
				AddHandler(pHandler);
			}
		}
		// check Forward notifications
		if (CMessageManager::m_sHandlerManager.m_bForwardNotifications)
		{
			GetDlgItem(IDC_CHECK_FORWARD).SendMessage(BM_SETCHECK, BST_CHECKED);
		}
		else
		{
			GetDlgItem(IDC_CHECK_FORWARD).SendMessage(BM_SETCHECK, BST_UNCHECKED);
		}
		//check reflect notifications
		if (CMessageManager::m_sHandlerManager.m_bReflectNotifications)
		{
			GetDlgItem(IDC_CHECK_REFLECT).SendMessage(BM_SETCHECK, BST_CHECKED);
			GetDlgItem(IDC_CHECK_REFLECT_EX).EnableWindow();
			if (CMessageManager::m_sHandlerManager.m_bReflectNotificationsEx)
			{
				GetDlgItem(IDC_CHECK_REFLECT_EX).SendMessage(BM_SETCHECK, BST_CHECKED);
			}
			else
			{
				GetDlgItem(IDC_CHECK_REFLECT_EX).SendMessage(BM_SETCHECK, BST_UNCHECKED);
			}
		}
		else
		{
			GetDlgItem(IDC_CHECK_REFLECT).SendMessage(BM_SETCHECK, BST_UNCHECKED);
			GetDlgItem(IDC_CHECK_REFLECT_EX).EnableWindow(FALSE);
			GetDlgItem(IDC_CHECK_REFLECT_EX).SendMessage(BM_SETCHECK, BST_UNCHECKED);
		}
		//check default reflection handler
		if (CMessageManager::m_sHandlerManager.m_bDefReflectHandler)
		{
			GetDlgItem(IDC_CHECK_DEF_HANDLER).SendMessage(BM_SETCHECK, BST_CHECKED);
		}
		else
		{
			GetDlgItem(IDC_CHECK_DEF_HANDLER).SendMessage(BM_SETCHECK, BST_UNCHECKED);
		}
		// fill message maps
		for (size_t i = 0; i < m_pMessageMap->AltMaps.GetCount(); i++)
		{
			VSMessageMap* pAltMap = m_pMessageMap->AltMaps[i];
			m_MessageMaps.AddString(pAltMap->Name);

			for (size_t j = 0; j != pAltMap->MapEntries.GetCount(); j++)
			{
				CMessageManager::m_sHandlerManager.AddMapEntry(pAltMap->MapEntries[j]);
			}
		}

		m_MessageMaps.AddString(_T("Create new ALT map"));
		m_MessageMaps.SetCurSel(0);
	}
	else
	{
		m_MessageMaps.EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_FORWARD).SendMessage(BM_SETCHECK, BST_UNCHECKED);
		GetDlgItem(IDC_CHECK_FORWARD).EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_REFLECT).SendMessage(BM_SETCHECK, BST_UNCHECKED);
		GetDlgItem(IDC_CHECK_REFLECT).EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_REFLECT_EX).SendMessage(BM_SETCHECK, BST_UNCHECKED);
		GetDlgItem(IDC_CHECK_REFLECT_EX).EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_DEF_HANDLER).SendMessage(BM_SETCHECK, BST_UNCHECKED);
		GetDlgItem(IDC_CHECK_DEF_HANDLER).EnableWindow(FALSE);
	}

	//добавление функций
	for (size_t i2 = 0; i2 != pClass->Functions.GetCount(); i2++)
	{
		if (!CMessageManager::m_sHandlerManager.IsHandler((int)i2))
		{
			int k1 = m_Functions.AddString((pClass->Functions[i2])->Name);
			m_Functions.SetItemDataPtr(k1, pClass->Functions[i2]);
		}
	}
}

void CFunctionPage::UpdateForwardReflect()
{
	CString Name;
	Name = _T("FORWARD_NOTIFICATIONS");
	int Res = (int)GetDlgItem(IDC_CHECK_FORWARD).SendMessage(BM_GETCHECK);
	if (Res == BST_CHECKED)
	{
		if (!CMessageManager::m_sHandlerManager.m_bForwardNotifications)
			m_MessageManager.AddForwardReflect(Name);
	}
	else
	{
		if (CMessageManager::m_sHandlerManager.m_bForwardNotifications)
			m_MessageManager.DeleteForwardReflect(Name);
	}
	Name = _T("DEFAULT_REFLECTION_HANDLER");
	Res = (int)GetDlgItem(IDC_CHECK_DEF_HANDLER).SendMessage(BM_GETCHECK);
	if (Res == BST_CHECKED)
	{
		if (!CMessageManager::m_sHandlerManager.m_bDefReflectHandler)
		{
			m_MessageManager.AddForwardReflect(Name);
		}
	}
	else
	{
        if (CMessageManager::m_sHandlerManager.m_bDefReflectHandler)
			m_MessageManager.DeleteForwardReflect(Name);
	}
	// reflections
	int ReflectionOld = 0;
	if (CMessageManager::m_sHandlerManager.m_bReflectNotifications)
	{
		ReflectionOld++;
		if (CMessageManager::m_sHandlerManager.m_bReflectNotificationsEx)
			ReflectionOld++;
	}
	int ReflectionNew = 0;
	Res = (int)GetDlgItem(IDC_CHECK_REFLECT).SendMessage(BM_GETCHECK);
	if (Res == BST_CHECKED)
	{
		ReflectionNew++;
		Res = (int)GetDlgItem(IDC_CHECK_REFLECT_EX).SendMessage(BM_GETCHECK);
		if (Res == BST_CHECKED)
		{
			ReflectionNew++;
		}
	}
	if (ReflectionNew != ReflectionOld)
	{
		if (ReflectionOld == 1)
		{
			m_MessageManager.DeleteForwardReflect(_T("REFLECT_NOTIFICATIONS"));
		}
		if (ReflectionOld == 2)
		{
			m_MessageManager.DeleteForwardReflect(_T("REFLECT_NOTIFICATIONS_EX"));
		}

		if (ReflectionNew == 1)
		{
			m_MessageManager.AddForwardReflect(_T("REFLECT_NOTIFICATIONS"));
		}
		if (ReflectionNew == 2)
		{
			m_MessageManager.AddForwardReflect(_T("REFLECT_NOTIFICATIONS_EX"), _T("<atlwinx.h>"));
		}
	}
}

LRESULT CFunctionPage::OnHandlerListNmDblclk(LPNMHDR pnmh)
{
	//for ListView - (LPNMITEMACTIVATE)pnmh
	//for StatusBar	- (LPNMMOUSE)pnmh
	LPNMITEMACTIVATE pnia = (LPNMITEMACTIVATE)pnmh;
	HandlerStruct* pHandler = (HandlerStruct*)m_Handlers.GetItemData(pnia->iItem);
	g_pSelectedFunction = pHandler->pFunction;
	GetParent().GetParent().SendMessage(WM_COMMAND, MAKELONG(IDOK, BN_CLICKED), 0);

	return 0;
}

LRESULT CFunctionPage::OnHdnEndTrack(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	int HandlerHeaderID = m_Handlers.GetHeader().GetWindowLong(GWL_ID);
	if (idCtrl == HandlerHeaderID)
	{
		LPNMHEADER lpHeader = (LPNMHEADER)pnmh;
		if (lpHeader->iItem == 0)
		{
			CRect rc;
			m_Handlers.GetClientRect(rc);
			int Width = m_Handlers.GetColumnWidth(0);
			m_Handlers.SetColumnWidth(1, rc.Width() - Width - 5);
		}
	}
	return 0;
}

LRESULT CFunctionPage::OnHandlerListlvnKeyDown(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	LPNMLVKEYDOWN lpnmkey = (LPNMLVKEYDOWN)pnmh;
	if (lpnmkey->wVKey == VK_DELETE)
	{
		return OnBnClickedButtonDelHandler(BN_CLICKED, 0, NULL, bHandled);
	}
	bHandled = FALSE;
	return 0;
}

LRESULT CFunctionPage::OnToolbarDropDown(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	LPNMTOOLBAR lpnmtb = (LPNMTOOLBAR) pnmh;

	CMenu Menu = m_FunctionManager.CreateSpecFunctionDropMenu();
	CToolBarCtrl Toolbar(lpnmtb->hdr.hwndFrom);
	CRect r = lpnmtb->rcButton;
	Toolbar.ClientToScreen(r);
	Toolbar.Detach();
	int ID = Menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD, r.left, r.bottom, m_hWnd);
	if (!ID)
		return 0;

	CAtlArray<MessageStruct*> Messages;
	VSFunction* pFunc = m_FunctionManager.AddSpecFunction(ID, Messages);
	if (pFunc)
	{
		for (size_t i = 0; i < Messages.GetCount(); i++)
		{
			HandlerStruct Handler;
			if (m_MessageManager.InsertWindowsMessageHandler(Messages[i], Handler))
			{
				AddHandler(&Handler);
			}
		}
		int k = m_Functions.AddString(pFunc->Name);
		m_Functions.SetItemDataPtr(k, pFunc);
	}
	return 0;
}

LRESULT CFunctionPage::OnReflectBnClicked(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (GetDlgItem(IDC_CHECK_REFLECT).SendMessage(BM_GETCHECK) == BST_CHECKED)
	{
		GetDlgItem(IDC_CHECK_REFLECT_EX).EnableWindow();
	}
	else
	{
		GetDlgItem(IDC_CHECK_REFLECT_EX).EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_REFLECT_EX).SendMessage(BM_SETCHECK, BST_UNCHECKED);
	}
	return 0;
}

LRESULT CFunctionPage::OnFunctionListLbnDblclk(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int iItem = m_Functions.GetCurSel();
	VSFunction* pFunc = (VSFunction*)m_Functions.GetItemData(iItem);
	g_pSelectedFunction = pFunc;
	GetParent().GetParent().SendMessage(WM_COMMAND, MAKELONG(IDOK, BN_CLICKED), 0);
	return 0;
}

LRESULT CFunctionPage::OnVkeytoitem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT vk = LOWORD(wParam);
	if (vk == VK_DELETE)
	{
		OnBnClickedButtonDelFunc(BN_CLICKED, 0, NULL, bHandled);
	}
	return TRUE;
}