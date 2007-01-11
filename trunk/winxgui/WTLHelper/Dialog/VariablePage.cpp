////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	VariablePage.cpp
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

// VariablePage.cpp : Implementation of CVariablePage

#include "stdafx.h"
#include "VariablePage.h"
#include "ddxvariable.h"
#include "..\common.h"
#include "TypeCStringDlg.h"
#include "../RegArchive.h"

extern LPCTSTR RegPath;
extern LPCTSTR DDXRegName;

//////////////////////////////////////////////////////////////////////////
// CVariablePage
//////////////////////////////////////////////////////////////////////////

void CVariablePage::CreateControls()
{
	m_Classes.Attach(GetDlgItem(IDC_COMBO_CLASSES));
	
	m_SplitIds.Create(m_hWnd, rcDefault, NULL,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	m_SplitIds.SetSplitterExtendedStyle(0);
	
	HFONT hFont = GetFont();

	m_IdsContainer.Create(m_SplitIds, _T("Control ID"));
	m_IdsContainer.SetPaneContainerExtendedStyle(PANECNT_NOCLOSEBUTTON, PANECNT_NOCLOSEBUTTON);
	m_IDs.Create(m_IdsContainer, NULL, NULL, WS_CHILD | WS_VISIBLE | LBS_NOINTEGRALHEIGHT
		| WS_VSCROLL | WS_TABSTOP | LBS_NOTIFY | LBS_SORT,
		WS_EX_CLIENTEDGE, IDC_LIST_IDS);
	m_IDs.SetFont(hFont);
	m_IdsContainer.SetClient(m_IDs);

	m_VariablesContainer.Create(m_SplitIds, _T("Variables"));
	m_VariablesContainer.SetPaneContainerExtendedStyle(PANECNT_NOCLOSEBUTTON, PANECNT_NOCLOSEBUTTON);
	m_Variables.Create(m_VariablesContainer, NULL, NULL, 0,	0, IDC_LIST_VARS);
	m_Variables.SendMessage(CCM_SETVERSION, 5);
	m_Variables.SetFont(hFont);
	m_VariablesContainer.SetClient(m_Variables);

	m_SplitIds.SetSplitterPanes(m_IdsContainer, m_VariablesContainer);
}

void CVariablePage::LoadSettings()
{
	CRegArchive RegArchive;
	if (RegArchive.Open(HKEY_CURRENT_USER, RegPath))
	{
		CSettings<CVariablePage>::LoadSettings(RegArchive, DDXRegName);
		m_WindowSettings.LoadSettings(RegArchive, DDXRegName);
		RegArchive.Close();
	}
	m_DDXManager.LoadSettings();
}

void CVariablePage::SaveSettings()
{
	if (m_bShowWindow)
	{
		//сохраняем только если окно хоть раз показалось
		//иначе будем сохранять -1 для сплитера
		m_WindowSettings.m_IdsSplitPos = m_SplitIds.GetSplitterPos();
		ATLASSERT(m_WindowSettings.m_IdsSplitPos != -1);

		m_WindowSettings.m_VariableWidth = m_Variables.GetColumnWidth(0);
		CRegArchive RegArchive;
		if(RegArchive.Open(HKEY_CURRENT_USER, RegPath, true))
		{
			m_WindowSettings.SaveSettings(RegArchive, DDXRegName);
			RegArchive.Close();
		}
	}
}

void CVariablePage::UpdateIDs(VSClass* pClass)
{
	m_IDs.ResetContent();
	const CAtlArray<ResControl>& Controls = m_DDXManager.GetControls();
	for (size_t i = 0; i < Controls.GetCount(); i++)
	{
		m_IDs.AddString(Controls.GetAt(i).m_ID);
	}
}

void CVariablePage::AddMapEntry(CString ID, CString Var, VSMapEntry* pMapEntry)
{
	int iLast = m_Variables.GetItemCount();
	int iItem = m_Variables.AddItem(iLast, 0, ID);
	m_Variables.AddItem(iLast, 1, Var);
	m_Variables.SetItemData(iItem, (LPARAM)pMapEntry);
}

CString CVariablePage::LoadToolTip(int ID)
{
	CString str;
	str.LoadString(ID);
	return str;
}

#define DDX_BUTTON_COUNT	2

void CVariablePage::UpdateToolBar(HWND hWndToolBar)
{
	CToolBarCtrl ToolBar(hWndToolBar);
	ToolBar.SetImageList(m_ToolbarImgList);
	int Count = ToolBar.GetButtonCount();
	int i;
	int nSeps = 0;
	BOOL Res;
	for (i = 0; i < min(Count, DDX_BUTTON_COUNT); i++)
	{
		TBBUTTONINFO tb;
		tb.cbSize = sizeof(tb);
		tb.dwMask = TBIF_IMAGE | TBIF_STYLE;
		tb.fsStyle = TBSTYLE_BUTTON;
		tb.iImage = i - nSeps;

		tb.idCommand = FIRST_DDX_COMMAND + i;
		ToolBar.SetCmdID(i, tb.idCommand)		;
		Res = ToolBar.SetButtonInfo(tb.idCommand, &tb);
	}
	if (Count < DDX_BUTTON_COUNT)
	{
		TBBUTTON Buttons[DDX_BUTTON_COUNT];
		int Delta = DDX_BUTTON_COUNT - Count;
		for (i = 0; i < Delta; i++)
		{
			Buttons[i].iBitmap = i + Count - nSeps;
			Buttons[i].fsState = TBSTATE_ENABLED;
			Buttons[i].fsStyle = TBSTYLE_BUTTON;
			Buttons[i].dwData = 0;
			Buttons[i].iString = 0;
			
			Buttons[i].idCommand = FIRST_DDX_COMMAND + i + Count;
		}
		ToolBar.AddButtons(Delta, Buttons);
	}
	if (Count > DDX_BUTTON_COUNT)
	{
		for (i = Count - 1; i >= DDX_BUTTON_COUNT; i--)
		{
			ToolBar.DeleteButton(i);
		}
	}
	ToolBar.Detach();
}

LRESULT CVariablePage::OnSetActive(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int iCurClass = 0;
	if (!m_bOnlyDlgs)
		iCurClass = *m_piCurrentClass;
	else
	{
		int Count = -1;
		for (size_t i = 0; i < m_pClassVector->GetCount(); i++)
		{
			VSClass* pCurClass = (*m_pClassVector)[i];
			if (pCurClass->m_eDialog == eTrue)
			{
				Count++;
				if (i >= (size_t)*m_piCurrentClass)
				{
					break;
				}
			}
		}
		iCurClass = Count;

	}
	m_Classes.SetCurSel(iCurClass);
	OnCbnSelchange(CBN_SELCHANGE, IDC_COMBO_CLASSES, NULL, bHandled);
	UpdateToolBar((HWND)wParam);
	return 0;
}

void CVariablePage::SetModified(BOOL bModified /* = TRUE */)
{
	GetParent().GetParent().SendMessage(WTLH_SETMODIFIED, bModified);
}

LRESULT CVariablePage::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATLASSERT(m_piCurrentClass);
	START_PROFILE(VarInit);
	CreateControls();
	
	m_DDXManager.SetGlobalParams(m_hWnd, m_pModifications, m_pResManager);

	CRect r;
	m_Variables.GetClientRect(r);
	m_Variables.InsertColumn(0, _T("ID"), LVCFMT_LEFT, m_WindowSettings.m_VariableWidth, 0);
	m_Variables.InsertColumn(1, _T("Variable"), LVCFMT_LEFT, r.Width() - m_WindowSettings.m_VariableWidth - 5, 1);
	m_Variables.SetExtendedListViewStyle(LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	START_PROFILE(VarDlg);
	for (size_t i = 0; i < m_pClassVector->GetCount(); i++)
	{
		VSClass* pCurClass = (*m_pClassVector)[i];
		if (!m_bOnlyDlgs ||
			(pCurClass->IsDialog() && !(pCurClass->m_DialogID.IsEmpty())))
		{
			int iItem = m_Classes.AddString(pCurClass->Name);
			m_Classes.SetItemData(iItem, i);
		}

	}
	END_PROFILE(VarDlg, _T("CVariablePage::OnInitDialog check dialog classes"));
	m_Classes.SetCurSel(0);
	m_ToolbarImgList.CreateFromImage(IDB_BITMAP_DDX, 18, 1, RGB(197, 200,201), IMAGE_BITMAP, LR_CREATEDIBSECTION);
	InitToolTip();
	END_PROFILE(VarInit, _T("CVariablePage::OnInitDialog"));

	return 0;
}

LRESULT CVariablePage::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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
		m_SplitIds.MoveWindow(rc2);

		if (!m_bShowWindow && lParam)
		{
			m_bShowWindow = true;
			m_SplitIds.SetSplitterPos(m_WindowSettings.m_IdsSplitPos);
		}
	}
	return 0;
}

LRESULT CVariablePage::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SaveSettings();
	return 0;
}

LRESULT CVariablePage::OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_IDs.SetFocus();
	return 0;
}

LRESULT CVariablePage::OnAddVar(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int iSel = m_IDs.GetCurSel();
	if (iSel == -1)
	{
		MessageBox(_T("Not selected ID"));
		return 0;
	}
	
	CString ControlID, MemberName;
	VSMapEntry* pMapEntry = m_DDXManager.AddVariable(iSel, ControlID, MemberName);
	if (pMapEntry)
	{
		AddMapEntry(ControlID, MemberName, pMapEntry);
		SetModified();
	}

	return 0;
}

LRESULT CVariablePage::OnDelVar(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int n = m_Variables.GetSelectedIndex();
	if (n == -1)
	{
		MessageBox(_T("No selected Items"));
		return 1;
	}
	int iCurSel = m_Classes.GetCurSel();
	int iCurClass = (int)m_Classes.GetItemData(iCurSel);

	if (MessageBox(_T("Are you realy want to delete variable"), _T(""), MB_YESNO) == IDYES)
	{
		VSMapEntry* pListEntry = (VSMapEntry*)m_Variables.GetItemData(n);
		CString VarName;
		m_Variables.GetItemText(n, 1, VarName);
		if (m_DDXManager.DeleteVariable(pListEntry, VarName))
		{
			m_Variables.DeleteItem(n);
			SetModified(TRUE);
		}
	}

	return 0;
}

LRESULT CVariablePage::OnCbnSelchange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int iCurClass = m_Classes.GetCurSel();
	if (iCurClass == -1)
		return 0;
	m_Variables.DeleteAllItems();
	int iClass = (int)m_Classes.GetItemData(iCurClass);
	if (iClass == -1)
		return 0;

	VSClass* pCurClass = (*m_pClassVector)[iClass];
	pCurClass->RetriveItems();
	*m_piCurrentClass = iClass;
	m_DDXManager.Init(pCurClass, &(*m_pModifications)[iClass]);

	if (pCurClass->IsDialog())
	{
		m_pDDXMap = pCurClass->GetMap(CString(_T("DDX")));
	}
	else
	{
		m_pDDXMap = NULL;
	}
	UpdateIDs(pCurClass);
	if (!m_pDDXMap)
	{
		return 0;
	}
	for (size_t i = 0; i < m_pDDXMap->MapEntries.GetCount(); i++)
	{
		VSMapEntry* pMapEntry = m_pDDXMap->MapEntries[i];
		CString ID, Var;
		ID = pMapEntry->Parameters[0]->Name;
		Var = pMapEntry->Parameters[1]->Name;
		for (size_t j = 0; j != pCurClass->Variables.GetCount(); j++)
		{
			if ((pCurClass->Variables[j])->Name == Var)
			{
				pMapEntry->pData = pCurClass->Variables[j];
				break;
			}
		}
		AddMapEntry(ID, Var, pMapEntry);
	}
	
	return 0;
}

LRESULT CVariablePage::OnListIdsLbnDblclk(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return OnAddVar(0, 0, hWndCtl, bHandled);
}

LRESULT CVariablePage::OnHdnEndTrack(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	int HandlerHeaderID = m_Variables.GetHeader().GetWindowLong(GWL_ID);
	if (idCtrl == HandlerHeaderID)
	{
		LPNMHEADER lpHeader = (LPNMHEADER)pnmh;
		if (lpHeader->iItem == 0)
		{
			CRect rc;
			m_Variables.GetClientRect(rc);
			int Width = m_Variables.GetColumnWidth(0);
			m_Variables.SetColumnWidth(1, rc.Width() - Width - 5);
		}
	}
	return 0;
}

LRESULT CVariablePage::OnListVarsKeydown(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	LPNMLVKEYDOWN lpnmkey = (LPNMLVKEYDOWN)pnmh;
	if (lpnmkey->wVKey == VK_DELETE)
	{
		return OnDelVar(BN_CLICKED, 0, NULL, bHandled);
	}
	bHandled = FALSE;
	return 0;
}
