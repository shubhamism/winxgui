////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2005 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	DDXManager.cpp
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

#include "StdAfx.h"
#include ".\ddxmanager.h"
#include "Dialog/DDXVariable.h"
#include "Dialog/TypeCStringDlg.h"
#include "RegArchive.h"

extern LPCTSTR RegPath;
extern LPCTSTR DDXRegName;

CDDXManager::CDDXManager(void): m_pClass(NULL), m_pModifications(NULL), m_pDDXMap(NULL),
m_iProtection(0), m_pResManager(NULL), m_pGlobalModifications(NULL)
{
}

CDDXManager::~CDDXManager(void)
{
}

bool CDDXManager::InsertNewMap(CString MapName)
{
	VSMap* pNewMap;
	pNewMap = new VSMap;

	pNewMap->Name = MapName;
	VSParameter* pParam = new VSParameter;
	
	VCCodeModelLibrary::VCCodeClassPtr pClass = m_pClass->pElement;
	_bstr_t DisplayName;
	pClass->get_DisplayName(DisplayName.GetAddress());
	pParam->Name = (LPCTSTR)DisplayName;
	pNewMap->MapParameters.Add(pParam);
	m_pClass->Maps.Add(pNewMap);
	InsertPointMap* pInsPt = new InsertPointMap;
	pInsPt->pElement = pNewMap;
	m_pModifications->InsertPoints.Add(pInsPt);

	return true;
}

void CDDXManager::SetAtlDDX(VSClass* pClass, bool bUseFloat /* = false */)
{
	::SetAtllDDX(pClass, m_pModifications, bUseFloat);
}

bool CDDXManager::CheckCString(VSClass* pClass)
{
	EnvDTE::ProjectPtr pProject;
	EnvDTE::ProjectItemPtr pProjectItem;
	EnvDTE::GlobalsPtr pProjGlobals;

	pClass->pElement->get_ProjectItem(&pProjectItem);
	pProjectItem->get_ContainingProject(&pProject);

	pProject->get_Globals(&pProjGlobals);
	if (pProjGlobals != NULL)
	{
		VARIANT_BOOL bExist;
		pProjGlobals->get_VariableExists(_bstr_t(L"CTypeCString.Ask"), &bExist);
		if (bExist == VARIANT_TRUE)
			return true;
	}
	if (FindInclude(pClass, L"<atlstr.h>", true) != NULL ||
		FindInclude(pClass, L"<atlmisc.h>", true) != NULL)
	{
		return true;
	}

	CSmartAtlArray<InsertionPoint*>& CurInsPoints = m_pModifications->InsertPoints;
	for (size_t i = 0; i < CurInsPoints.GetCount(); i++)
	{
		if (CurInsPoints[i]->Type == INSERT_POINT_INCLUDE)
		{
			InsertInclude* pInsInclude = (InsertInclude*)CurInsPoints[i];
			if (pInsInclude->pElement->Name == _T("<atlstr.h>") ||
				pInsInclude->pElement->Name == _T("<atlmisc.h>"))
			{
				return true;
			}
		}
	}

	ATLASSERT(m_pGlobalModifications);
	for (size_t i = 0; i < m_pGlobalModifications->GetCount(); i++)
	{
		CSmartAtlArray<InsertionPoint*>& InsPoints = (*m_pGlobalModifications)[i].InsertPoints;
		for (size_t j = 0; j < InsPoints.GetCount(); j++)
		{
			if (InsPoints[j]->Type == INSERT_POINT_INCLUDE)
			{
				InsertInclude* pInsInclude = (InsertInclude*)InsPoints[j];
				if (pInsInclude->pProjectFile != NULL)
				{
					if (pInsInclude->pElement->Name == _T("<atlstr.h>") ||
						pInsInclude->pElement->Name == _T("<atlmisc.h>"))
					{
						return true;
					}
				}
			}
		}
	}

	//показать диалог в котором можно будет выбрать CString используемый
	CTypeCStringDlg dlg;
	EnvDTE::ProjectItemPtr pStdAfxFile = FindItem(pProject, _bstr_t(L"stdafx.h"), EnvDTE::ProjectItemPtr(NULL));
	if (pStdAfxFile != NULL)
	{
		dlg.m_bStdAfx = true;
	}
	else
	{
		dlg.m_bStdAfx = false;
	}
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_Type == STYPE_ANOTHER)
			return true;
		if (dlg.m_Type == STYPE_WTL)
		{
			InsertWtlCString(pProject, CurInsPoints, dlg.m_Place);
			return true;
		}
		if (dlg.m_Type == STYPE_ATL)
		{
			InsertAtlCString(pProject, CurInsPoints);
		}

		if (dlg.m_bAskAgain)
		{
			pProjGlobals->put_VariablePersists(_bstr_t(L"CTypeCString.Ask"), VARIANT_TRUE);
		}
	}
	return true;
}

void CDDXManager::InsertAtlCString(EnvDTE::ProjectPtr pProject, CSmartAtlArray<InsertionPoint*>& CurInsPoints)
{
	InsertInclude* pInsInclude = new InsertInclude;
	VSInclude* pInclude = new VSInclude;
	pInclude->Name = _T("<atlstr.h>");
	pInsInclude->AdditionalMacro = _T("_WTL_NO_CSTRING");
	pInsInclude->pElement = pInclude;
	pInsInclude->Pos = 0;
	pInsInclude->pProjectFile = FindItem(pProject, _bstr_t(L"stdafx.h"), EnvDTE::ProjectItemPtr(NULL));
	CurInsPoints.Add(pInsInclude);

}

void CDDXManager::InsertWtlCString(EnvDTE::ProjectPtr pProject, CSmartAtlArray<InsertionPoint*>& CurInsPoints, int Place)
{
	InsertInclude* pInsInclude = new InsertInclude;
	VSInclude* pInclude = new VSInclude;
	pInclude->Name = _T("<atlmisc.h>");
	pInsInclude->pElement = pInclude;
	if (Place == SPLACE_WHOLE)
	{
		pInsInclude->pProjectFile = FindItem(pProject, _bstr_t(L"stdafx.h"), EnvDTE::ProjectItemPtr(NULL));
	}
	CurInsPoints.Add(pInsInclude);
}

void CDDXManager::SetGlobalParams(HWND hParentWnd, CAtlArray<InsDelPoints>* pGlobalModifications, const CResourceManager* pResManager)
{
	m_pGlobalModifications = pGlobalModifications;
	m_hWndParent = hParentWnd;
	m_pResManager = pResManager;
}

bool CDDXManager::LoadSettings()
{
	CRegArchive RegArchive;
	bool bRes = false;
	if (RegArchive.Open(HKEY_CURRENT_USER, RegPath))
	{
		bRes = CSettings<CDDXManager>::LoadSettings(RegArchive, DDXRegName);
		RegArchive.Close();
	}
	return bRes;
}

const CAtlArray<ResControl>& CDDXManager::GetControls()
{
	return m_CurControls;
}

bool CDDXManager::Init(VSClass* pClass, InsDelPoints* pModifications)
{
	m_pClass = pClass;
	m_pModifications = pModifications;
	if (pClass->IsDialog())
	{
		m_pDDXMap = pClass->GetMap(CString(_T("DDX")));
	}
	else
	{
		m_pDDXMap = NULL;
	}

	m_CurControls.RemoveAll();
	if (pClass->m_eDialog == eTrue && !pClass->m_DialogID.IsEmpty())
	{
		
		m_pResManager->GetAllControls(pClass->m_DialogID, m_CurControls);
	}
	if (m_CurControls.GetCount())
		SortResources(m_CurControls);
	return true;
}

void CDDXManager::SetDefaultProtection(int iProtection)
{
	m_iProtection = iProtection;
}

VSMapEntry* CDDXManager::AddVariable(IN int iControlID, OUT CString& ControlID, OUT CString& VarName)
{
	CDDXVariable dlg;
	dlg.m_Controls.Copy(m_CurControls);
	dlg.m_Protection = m_iProtection;
	dlg.m_iCurControl = iControlID;

	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_DDXType != _T("Float"))
			SetAtlDDX(m_pClass);
		else
			SetAtlDDX(m_pClass, true);
		//create DDX map if needed
		if (!m_pDDXMap)
		{
			CString MapName = _T("DDX");
			InsertNewMap(MapName);
			m_pDDXMap = m_pClass->GetMap(MapName);
		}
		if (!m_pDDXMap)
		{
			MessageBox(m_hWndParent, _T("Cannot create ddx map"), NULL, 0);
			return 0;
		}

		//insert ddx map entry
		InsertPointDDX* pInsPt = new InsertPointDDX;
		VSMapEntry* MapEntry = new VSMapEntry;
		MapEntry->Name = _T("DDX_");
		VSParameter* pParam = new VSParameter;
		pParam->Name = dlg.m_ControlID;
		MapEntry->Parameters.Add(pParam);
		pParam = new VSParameter;
		pParam->Name = dlg.m_MemberName;
		MapEntry->Parameters.Add(pParam);

		if (dlg.m_DDXType == _T("Text"))
		{
			MapEntry->Name += _T("TEXT");
			if (dlg.m_iAddCount > 0)
			{
				MapEntry->Name += _T("_LEN");
				pParam = new VSParameter;
				pParam->Name = dlg.m_FirstEdit;
				MapEntry->Parameters.Add(pParam);
			}
			if (dlg.m_MemberType == _T("CString"))
			{
				CheckCString(m_pClass);
			}
		}
		if (dlg.m_DDXType == _T("Int") || dlg.m_DDXType == _T("UINT"))
		{
			if (dlg.m_DDXType == _T("Int"))
				MapEntry->Name += _T("INT");
			else
				MapEntry->Name += _T("UINT");
			if (dlg.m_iAddCount)
			{
				MapEntry->Name += _T("_RANGE");
				pParam = new VSParameter;
				pParam->Name = dlg.m_FirstEdit;
				MapEntry->Parameters.Add(pParam);
				pParam = new VSParameter;
				pParam->Name = dlg.m_SecondEdit;
				MapEntry->Parameters.Add(pParam);
			}
		}
		if (dlg.m_DDXType == _T("Float"))
		{
			MapEntry->Name += _T("FLOAT");
			if (dlg.m_iAddCount)
			{
				if (!dlg.m_ThirdEdit.IsEmpty())
				{
					//precision
					MapEntry->Name += _T("_P");
				}
				if (dlg.m_iAddCount > 1)
				{
					//range
					MapEntry->Name += _T("_RANGE");
					pParam = new VSParameter;
					pParam->Name = dlg.m_FirstEdit;
					MapEntry->Parameters.Add(pParam);
					pParam = new VSParameter;
					pParam->Name = dlg.m_SecondEdit;
					MapEntry->Parameters.Add(pParam);
				}
				if (!dlg.m_ThirdEdit.IsEmpty())
				{
					//precision
					pParam = new VSParameter;
					pParam->Name = dlg.m_ThirdEdit;
					MapEntry->Parameters.Add(pParam);
				}
			}
		}
		if (dlg.m_DDXType == _T("Control"))
		{
			MapEntry->Name += _T("CONTROL");
		}
		if (dlg.m_DDXType == _T("Control handle"))
		{
			MapEntry->Name += _T("CONTROL_HANDLE");
		}
		if (dlg.m_DDXType == _T("Check"))
		{
			MapEntry->Name += _T("CHECK");
		}
		if (dlg.m_DDXType == _T("Radio"))
		{
			MapEntry->Name += _T("RADIO");
		}

		pInsPt->pParentMap = m_pDDXMap;
		pInsPt->pElement = MapEntry;
		pInsPt->Initializer = dlg.m_Initializer;

		m_pDDXMap->MapEntries.Add(MapEntry);

		//insert variable
		VSVariable* pNewVar = new VSVariable;
		MapEntry->pData = pNewVar;
		//set access type
		if (dlg.m_Protection == PROTECTION_PRIVATE)
			pNewVar->Access = EnvDTE::vsCMAccessPrivate;
		if (dlg.m_Protection == PROTECTION_PROTECTED)
			pNewVar->Access = EnvDTE::vsCMAccessProtected;
		if (dlg.m_Protection == PROTECTION_PUBLIC)
			pNewVar->Access = EnvDTE::vsCMAccessPublic;
		//set name and type
		pNewVar->Name = dlg.m_MemberName;
		pNewVar->Type = dlg.m_MemberType;

		pInsPt->pVariable = pNewVar;
		m_pModifications->InsertPoints.Add(pInsPt);
		m_pClass->Variables.Add(pNewVar);

		ControlID = dlg.m_ControlID;
		VarName = dlg.m_MemberName;
		return MapEntry;
	}
	return NULL;
}

bool CDDXManager::DeleteVariable(VSMapEntry* pMapEntry, CString VarName)
{
	CSmartAtlArray<InsertionPoint*>& pts = m_pModifications->InsertPoints;
	size_t i;
	for (i = 0; i < pts.GetCount(); i++)
	{
		if ((pts[i])->pElement == pMapEntry)
		{
			break;
		}
	}
	VSVariable* pVar = NULL;

	if (i != pts.GetCount())
	{
		//это добавленный в эту сессию обработчик
		//удаляем вместе с функцией
		InsertPointDDX* pInsDDX = (InsertPointDDX*)pts[i];
		pVar = pInsDDX->pVariable;
		delete pInsDDX;
		pts.RemoveAt(i);

		//чистим функции и MapEntries
		for (size_t j = 0; j != m_pDDXMap->MapEntries.GetCount(); j++)
		{
			if ((m_pDDXMap->MapEntries[j]) == pMapEntry)
			{
				m_pDDXMap->MapEntries.RemoveAt(j);
				break;
			}
		}

		if (pVar)
		{
			CSmartAtlArray<VSVariable*>& pv = m_pClass->Variables;
			for (size_t j = 0; j < pv.GetCount(); j++)
			{
				if ((pv[j]) == pVar)
				{
					pv.RemoveAt(j);
					break;
				}
			}
			delete pVar;
		}
		delete pMapEntry;
	}
	else
	{
		//обработчик добавленный ранее
		//чистим функции и MapEntries
		//добавляем в список удаленных компонент
		for (size_t j = 0; j != m_pDDXMap->MapEntries.GetCount(); j++)
		{
			if ((m_pDDXMap->MapEntries[j]) == pMapEntry)
			{
				m_pModifications->DeletePoint.Add(m_pDDXMap->MapEntries[j]);
				m_pDDXMap->MapEntries.RemoveAt(j);
				break;
			}
		}

		CSmartAtlArray<VSVariable*>& pv = m_pClass->Variables;
		
		for (size_t j = 0; j != pv.GetCount(); j++)
		{
			if ((pv[j])->Name == VarName)
			{
				m_pModifications->DeletePoint.Add(pv[j]);
				pv.RemoveAt(j);
				break;
			}
		}
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
void SetAtllDDX(VSClass* pClass, InsDelPoints* pModifications, bool bUseFloat /* = false */)
{
	if (pClass->m_bDDX && !bUseFloat)
		return;
	InsertPointDDXSupport* pInsPt = FindInsertPoint(pModifications);

	EnvDTE::CodeElementPtr pIncludeElem = FindInclude(pClass, L"<atlddx.h>", true);
	if (pIncludeElem == NULL)
	{
		if (!pInsPt)
		{
			pInsPt = new InsertPointDDXSupport;
			pInsPt->bUseFloat = false;
			pInsPt->pBase = NULL;
			pInsPt->pElement = NULL;
			pModifications->InsertPoints.Add(pInsPt);
		}
		if (!pInsPt->pElement)
		{
			VSInclude* pInclude = new VSInclude;
			pInclude->Name = _T("<atlddx.h>");
			pInsPt->pElement = pInclude;
		}
	}
	if (bUseFloat)
	{
		EnvDTE::CodeElementPtr pMacro = FindDefine(pClass, L"_ATL_USE_DDX_FLOAT", true);
		if (pMacro == NULL)
		{
			if (!pInsPt)
			{
				pInsPt = new InsertPointDDXSupport;
				pInsPt->pElement = NULL;
				pInsPt->pBase = NULL;
				pInsPt->bUseFloat = true;
				pModifications->InsertPoints.Add(pInsPt);
			}
			else
			{
				pInsPt->bUseFloat = true;
			}
		}
	}

	bool bBase = false;
	for (size_t i = 0; i < pClass->Parents.GetCount(); i++)
	{
		if ((pClass->Parents[i])->Name == _T("CWinDataExchange"))
		{
			bBase = true;
			break;
		}
	}
	if (!bBase)
	{
		//нужно добавить в качестве предка класс CWinDataExchange
		VSBase* pNewBase = new VSBase;
		pNewBase->Name = _T("CWinDataExchange<") + pClass->Name + _T(">");
		pNewBase->pElement = NULL;
		pNewBase->pParent = (VSElement*)pClass;
		pClass->Parents.Add(pNewBase);
		if (!pInsPt)
		{
			pInsPt = new InsertPointDDXSupport;
			pInsPt->bUseFloat = false;
			pInsPt->pBase = NULL;
			pInsPt->pElement = NULL;
			pModifications->InsertPoints.Add(pInsPt);
		}
		if (!pInsPt->pBase)
		{
			pInsPt->pBase = pNewBase;
		}
	}
	pClass->m_bDDX = true;
}

InsertPointDDXSupport* FindInsertPoint(InsDelPoints* pModifications)
{
	CSmartAtlArray<InsertionPoint*>& InsPoints = pModifications->InsertPoints;
	for (size_t i = 0; i < InsPoints.GetCount(); i++)
	{
		if (InsPoints[i]->Type == INSERT_POINT_DDXSUPPORT)
		{
			return (InsertPointDDXSupport*)&InsPoints[i];
		}
	}
	return NULL;
}