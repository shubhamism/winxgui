////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	common.h
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

#pragma once
#include "InsertPoint.h"
#include "resources/Resources.h"

struct InsDelPoints
{
	CSmartAtlArray<InsertionPoint*> InsertPoints;
	CSmartAtlArray<VSElement*> DeletePoint;
};

typedef CSmartAtlArray<VSClass*> ClassVector;

extern VSFunction* g_pSelectedFunction;
void UpdateClasses(CSmartAtlArray<InsDelPoints>* pModifications, ClassVector* pClassVector);
EnvDTE::ProjectItemPtr FindItem(EnvDTE::ProjectPtr pProject, _bstr_t ItemName, EnvDTE::ProjectItemPtr pPrevElem);
EnvDTE::CodeElementPtr FindDefine(VSClass* pClass, LPCWSTR Name, bool bStdAfx = false);
EnvDTE::CodeElementPtr FindInclude(VSClass* pClass, LPCWSTR Name, bool bStdAfx = false);

int CutString(CString InStr, CAtlArray<CString>& OutStrings, LPCTSTR Separators = _T(" \t,"));
void SortStringArray(CAtlArray<CString>& Arr, bool bAcsesnding = true);
void SortClasses(CAtlArray<VSClass*>& Arr, bool bAcsesnding = true);
void SortResources(CAtlArray<ResControl>& Arr);

CString CreateIDName(CString TrancatedID);
HRESULT GetDispatchProperty(IDispatch* pDisp, LPOLESTR lpName, VARIANT* pRes);
int CompareVersions(LPCTSTR lpVersion1, LPCTSTR lpVersion2);