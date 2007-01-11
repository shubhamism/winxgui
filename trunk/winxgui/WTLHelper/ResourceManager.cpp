////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2005 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	ResourceManager.cpp
// Created:	13.12.2005 9:05
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
#include ".\resourcemanager.h"

CResourceManager::CResourceManager(void)
{
}

CResourceManager::~CResourceManager(void)
{
}

void CResourceManager::AddResourceFiles(EnvDTE::ProjectItemPtr pParentItem, CAtlArray<CString>& Files)
{
	EnvDTE::ProjectItemsPtr pProjItems;
	HRESULT hr = pParentItem->get_ProjectItems(&pProjItems);
	if (hr != S_OK || pProjItems == NULL)
		return;
	long Count;
	pProjItems->get_Count(&Count);
	EnvDTE::ProjectItemPtr pItem;

	for (long i = 1; i <= Count; i++)
	{
		pProjItems->Item(_variant_t(i), &pItem);
		short FilesCount;
		pItem->get_FileCount(&FilesCount);
		if (FilesCount == 1)
		{
			_bstr_t str;
			pItem->get_FileNames(1, str.GetAddress());
			CString FileName = str;

			if (FileName.Right(3) == _T(".rc"))
			{
				Files.Add(FileName);
			}
		}
		else
		{
			AddResourceFiles(pItem, Files);
		}
	}
}

void CResourceManager::GetResourceFiles(EnvDTE::ProjectPtr pProj, CAtlArray<CString>& Files)
{
	EnvDTE::ProjectItemsPtr pProjItems;
	HRESULT hr = pProj->get_ProjectItems(&pProjItems);
	if (hr != S_OK || pProjItems == NULL)
		return;

	long Count;
	pProjItems->get_Count(&Count);
	EnvDTE::ProjectItemPtr pItem;

	for (long i = 1; i <= Count; i++)
	{
		pProjItems->Item(_variant_t(i), &pItem);
		short FilesCount;
		pItem->get_FileCount(&FilesCount);
		if (FilesCount == 1)
		{
			_bstr_t str;
			pItem->get_FileNames(1, str.GetAddress());
			CString FileName = str;

			if (FileName.Right(3) == _T(".rc"))
			{
				Files.Add(FileName);
			}
		}
		else
		{
			AddResourceFiles(pItem, Files);
		}
	}
}

void CResourceManager::LoadMenuItemIds(CResMenu& Menu, CAtlArray<CString>& ResIds)
{
	for (size_t i = 0; i < Menu.GetCount(); i++)
	{
		CString MenuItemId = Menu.GetAt(i).m_ID;
		if (!MenuItemId.IsEmpty())
		{
			ResIds.Add(MenuItemId);
		}
	}
	for (size_t i = 0; i < Menu.m_SubMenus.GetCount(); i++)
	{
		LoadMenuItemIds(Menu.m_SubMenus[i], ResIds);
	}
}
//////////////////////////////////////////////////////////////////////////
// public methods

bool CResourceManager::LoadResources(EnvDTE::ProjectPtr pProj)
{
	CAtlArray<CString> ResFiles;
	GetResourceFiles(pProj, ResFiles);

	for (size_t i = 0; i < ResFiles.GetCount(); i++)
	{
		m_Resources.Load(ResFiles[i], true);
	}
	return true;
}

bool CResourceManager::LoadResources(EnvDTE::ProjectItemPtr pProjItem)
{
	_bstr_t bsFileName;
	pProjItem->get_FileNames(1, bsFileName.GetAddress());
	return m_Resources.Load(bsFileName, true);
}

const CResources* CResourceManager::GetResources()
{
	return &m_Resources;
}

const CResDialog* CResourceManager::GetDialog(const CString DlgID) const
{
	for (size_t i = 0; i < m_Resources.m_Dialogs.GetCount(); i++)
	{
		const CResDialog& dlg = m_Resources.m_Dialogs.GetAt(i);
		if (dlg.m_ID == DlgID)
		{
			return &dlg;
		}
	}
	return NULL;
}

const ResControl* CResourceManager::GetDlgControl(const CString DlgId, const CString ControlId) const
{
	const CResDialog* pDlg = GetDialog(DlgId);
	if (pDlg == NULL)
		return NULL;
	return GetDlgControl(pDlg, ControlId);
}

const ResControl* CResourceManager::GetDlgControl(const CResDialog* pDlg, const CString ControlId) const
{
	ATLASSERT(pDlg);

	for (size_t i = 0; i < pDlg->GetCount(); ++i)
	{
		const ResControl& Control = pDlg->GetAt(i);
		if (Control.m_ID == ControlId)
		{
			return &Control;
		}
	}
	return NULL;
}

eControlType CResourceManager::GetControlType(const CString Type)
{
	if (Type == _T("PUSHBUTTON") || Type == _T("EDITTEXT") || 
		Type == _T("COMBOBOX") || Type == _T("LISTBOX") ||
		Type == _T("DEFPUSHBUTTON") || Type == _T("Button") ||
		(Type.CompareNoCase(_T("STATIC")) == 0) ||
		Type == _T("LTEXT") || Type == _T("RTEXT") ||
		Type == _T("CTEXT"))
	{
		return eCTCommand;
	}
	else if (Type.CompareNoCase(_T("SCROLLBAR")) == 0)
	{
		return eCTScrollbar;
	}
	else
	{
		return eCTNotify;
	}
}

bool CResourceManager::GetMenuIds(CAtlArray<CString>& StringIds, bool bAppend /* = true */)
{
	if (!bAppend)
		StringIds.RemoveAll();

	for (size_t i = 0; i < m_Resources.m_Menus.GetCount(); ++i) 
	{
		LoadMenuItemIds(m_Resources.m_Menus[i], StringIds);
	} 
	return true;
}

bool CResourceManager::GetMenuIds(const CString ResID, CAtlArray<CString>& StringIds)
{
	for (size_t i = 0; i < m_Resources.m_Menus.GetCount(); ++i) 
	{
		if (m_Resources.m_Menus[i].m_ID == ResID)
		{
			LoadMenuItemIds(m_Resources.m_Menus[i], StringIds);
			return true;
		}
	}
	return false;
}

bool CResourceManager::GetToolbarIds(CAtlArray<CString>& StringIds, bool bAppend /* = true */)
{
	if (!bAppend)
		StringIds.RemoveAll();

	for (size_t i = 0; i < m_Resources.m_Toolbars.GetCount(); i++)
	{
		for (size_t j = 0; j < m_Resources.m_Toolbars[i].GetCount(); ++j) 
		{
			StringIds.Add(m_Resources.m_Toolbars[i].GetAt(j).m_ID);
		}
	}
	return true;
}

bool CResourceManager::GetToolbarIds(const CString ResID, CAtlArray<CString>& StringIds)
{
	for (size_t i = 0; i < m_Resources.m_Toolbars.GetCount(); i++)
	{
		if (m_Resources.m_Toolbars[i].m_ID == ResID)
		{
			for (size_t j = 0; j < m_Resources.m_Toolbars[i].GetCount(); ++j) 
			{
				StringIds.Add(m_Resources.m_Toolbars[i].GetAt(j).m_ID);
			}
			true;
		}
	}
	return false;
}

bool CResourceManager::GetAcceleratorIds(CAtlArray<CString>& StringIds, bool bAppend /* = true */)
{
	if (!bAppend)
		StringIds.RemoveAll();

	for (size_t i = 0; i < m_Resources.m_Accels.GetCount(); ++i)
	{
		for (size_t j = 0; j < m_Resources.m_Accels[i].GetCount(); ++j)
		{
			StringIds.Add(m_Resources.m_Accels[i].GetAt(j).m_ID);
		}
	}
	return true;
}

bool CResourceManager::GetAcceleratorIds(const CString ResID, CAtlArray<CString>& StringIds)
{
	for (size_t i = 0; i < m_Resources.m_Accels.GetCount(); i++)
	{
		if (m_Resources.m_Accels[i].m_ID == ResID)
		{
			for (size_t j = 0; j < m_Resources.m_Accels[i].GetCount(); ++j) 
			{
				StringIds.Add(m_Resources.m_Accels[i].GetAt(j).m_ID);
			}
			return true;
		}
	}
	return false;
}

bool CResourceManager::GetCommandControls(const CString DialogID, CAtlArray<CString>& StringIds) const
{
	const CResDialog* pDlg = GetDialog(DialogID);
	if (pDlg == NULL)
		return false;
	
	for (size_t j = 0; j < pDlg->GetCount(); j++)
	{
		const ResControl& ResCtrl = pDlg->GetAt(j);
		if (ResCtrl.m_ID ==_T("IDC_STATIC"))
			continue;
		if (GetControlType(ResCtrl.m_Type) == eCTCommand)
		{
			StringIds.Add(pDlg->GetAt(j).m_ID);
		}
	}

	return true;
}

bool CResourceManager::GetTypedControls(const CString DialogID, const CAtlArray<CString>* pPosibleTypes, CAtlArray<CString>& StringIds) const
{
	const CResDialog* pDlg = GetDialog(DialogID);
	if (pDlg == NULL)
		return false;

	for (size_t j = 0; j < pDlg->GetCount(); j++)
	{
		if (pDlg->GetAt(j).m_ID ==_T("IDC_STATIC"))
			continue;
		CString Type = pDlg->GetAt(j).m_Type;
		Type.Trim(_T("\""));
		bool bFind = false;
		for (size_t k = 0; k < pPosibleTypes->GetCount(); k++)
		{
			if (pPosibleTypes->GetAt(k) == Type)
			{
				bFind = true;
				break;
			}
		}
		if (bFind)
		{
			StringIds.Add(pDlg->GetAt(j).m_ID);
		}
	}

	return true;
}

bool CResourceManager::GetNotifyControls(const CString DialogID, CAtlArray<CString>& StringIds) const
{
	const CResDialog* pDlg = GetDialog(DialogID);
	if (pDlg == NULL)
		return false;

	for (size_t j = 0; j < pDlg->GetCount(); j++)
	{
		if (GetControlType(pDlg->GetAt(j).m_Type) == eCTNotify)
		{
			StringIds.Add(pDlg->GetAt(j).m_ID);
		}
	}

	return true;
}

bool CResourceManager::GetAllControls(const CString DialogID, CAtlArray<ResControl>& Controls) const
{
	const CResDialog* pDlg = GetDialog(DialogID);
	if (pDlg == NULL)
		return false;

	for (size_t j = 0; j < pDlg->GetCount(); j++)
	{
		const CString ID = pDlg->GetAt(j).m_ID;
		if (ID != _T("IDC_STATIC"))
		{
			Controls.Add(pDlg->GetAt(j));
		}
	}

	return true;
}