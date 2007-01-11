////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2005 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	DDXManager.h
// Created:	19.09.2005 15:30
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

#pragma once

#include "VSElements.h"
#include "ResourceManager.h"
#include "common.h"
#include "Settings.h"

class CDDXManager : public CSettings<CDDXManager>
{
	VSClass* m_pClass;
	InsDelPoints* m_pModifications;
	CAtlArray<InsDelPoints>* m_pGlobalModifications;
	VSMap* m_pDDXMap;
	const CResourceManager* m_pResManager;
	int m_iProtection;
	CAtlArray<ResControl> m_CurControls;
	HWND m_hWndParent;
	void SetAtlDDX(VSClass* pClass, bool bUseFloat = false);
	bool InsertNewMap(CString MapName);
	bool CheckCString(VSClass* pClass);
	void InsertWtlCString(EnvDTE::ProjectPtr pProject, CSmartAtlArray<InsertionPoint*>& CurInsPoints, int Place);
	void InsertAtlCString(EnvDTE::ProjectPtr pProject, CSmartAtlArray<InsertionPoint*>& CurInsPoints);
public:
	CDDXManager(void);
	~CDDXManager(void);
	void SetGlobalParams(HWND hParentWnd, CAtlArray<InsDelPoints>* pGlobalModifications, const CResourceManager* pResManager);
	bool LoadSettings();

	const CAtlArray<ResControl>& GetControls();

	bool Init(VSClass* pClass, InsDelPoints* pModifications);
	void SetDefaultProtection(int iProtection);
	VSMapEntry* AddVariable(IN int iControlID, OUT CString& ControlID, OUT CString& VarName);
	bool DeleteVariable(VSMapEntry* pMapEntry, CString VarName);

	BEGIN_SETTINGS_MAP()
		SETTINGS_VARIABLE_OPT_RO(m_iProtection)
	END_SETTINGS_MAP()
};

InsertPointDDXSupport* FindInsertPoint(InsDelPoints* pModifications);
void SetAtllDDX(VSClass* pClass, InsDelPoints* pModifications, bool bUseFloat = false);
