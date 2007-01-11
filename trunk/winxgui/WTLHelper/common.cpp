////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	common.cpp
// Created:	26.01.2005 17:58
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

#include "stdafx.h"
#include "common.h"

int CutString(const CString InStr, CAtlArray<CString>& OutStrings, LPCTSTR Separators)
{
	int Pos = 0;
	int StartPos = 0;
	bool bQuotas = false;
	OutStrings.RemoveAll();

	while (Pos < InStr.GetLength())
	{
		TCHAR ch = InStr[Pos];
		if (ch == _T('\"'))
		{
			if (InStr[Pos + 1]  == _T('\"'))
			{
				Pos += 2;
				continue;
			}
			else
			{
				bQuotas = !bQuotas;
			}
		}
		if (!bQuotas && _tcsrchr(Separators, ch))
		{
			//нашли сепаратор
			int WordLen = Pos - StartPos;
			if (WordLen)
			{
				CString NewWord = InStr.Mid(StartPos, WordLen);
				OutStrings.Add(NewWord);
			}
			StartPos = Pos + 1;
		}
		Pos++;
	}
	int WordLen = Pos - StartPos;
	if (WordLen)
	{
		CString NewWord = InStr.Mid(StartPos, WordLen);
		OutStrings.Add(NewWord);
	}
	else
	{
		OutStrings.Add(CString());
	}
	return (int)OutStrings.GetCount();
}

void QSortAcs(CAtlArray<CString>& Arr, int l, int r)
{
	CString x = Arr[(l+r)/2];
	int i = l;
	int j = r;
	do 
	{
		while(lstrcmp(Arr[i], x)< 0) i++;
		while(lstrcmp(Arr[j], x) > 0) j--;
		if (i < j)
		{
			CString tmp = Arr[i];
			Arr[i] = Arr[j];
			Arr[j] = tmp;
			i++;j--;
		}
		else
		{
			if (i == j)
			{
				i++;j--;
			}
		}
	} while(i <= j);
	if (l < j) QSortAcs(Arr, l, j);
	if (i < r) QSortAcs(Arr, i, r);
}

void QSortDesc(CAtlArray<CString>& Arr, int l, int r)
{
	CString x = Arr[(l+r)/2];
	int i = l;
	int j = r;
	do 
	{
		while(lstrcmp(Arr[i], x) > 0) i++;
		while(lstrcmp(Arr[j], x) < 0) j--;
		if (i < j)
		{
			CString tmp = Arr[i];
			Arr[i] = Arr[j];
			Arr[j] = tmp;
			i++;j--;
		}
		else
		{
			if (i == j)
			{
				i++;j--;
			}
		}
	} while(i <= j);
	if (l < j) QSortAcs(Arr, l, j);
	if (i < r) QSortAcs(Arr, i, r);
}

void SortStringArray(CAtlArray<CString>& Arr, bool bAcsesnding /* = true */)
{
	if (Arr.GetCount() > 1)
	{
		if (bAcsesnding)
		{
			QSortAcs(Arr, 0, (int)Arr.GetCount() - 1);
		}
		else
		{
			QSortDesc(Arr, 0, (int)Arr.GetCount() - 1);
		}
	}
}

void QSortAcs(CAtlArray<VSClass*>& Arr, int l, int r)
{
	VSClass* px = Arr[(l+r)/2];
	int i = l;
	int j = r;
	do 
	{
		while(lstrcmp(Arr[i]->Name, px->Name) < 0) i++;
		while(lstrcmp(Arr[j]->Name, px->Name) > 0) j--;
		if (i < j)
		{
			VSClass* tmp = Arr[i];
			Arr[i] = Arr[j];
			Arr[j] = tmp;
			i++;j--;
		}
		else
		{
			if (i == j)
			{
				i++;j--;
			}
		}
	} while(i <= j);
	if (l < j) QSortAcs(Arr, l, j);
	if (i < r) QSortAcs(Arr, i, r);
}

void QSortDesc(CAtlArray<VSClass*>& Arr, int l, int r)
{
	VSClass* px = Arr[(l+r)/2];
	int i = l;
	int j = r;
	do 
	{
		while(lstrcmp(Arr[i]->Name, px->Name) > 0) i++;
		while(lstrcmp(Arr[j]->Name, px->Name) < 0) j--;
		if (i < j)
		{
			VSClass* tmp = Arr[i];
			Arr[i] = Arr[j];
			Arr[j] = tmp;
			i++;j--;
		}
		else
		{
			if (i == j)
			{
				i++;j--;
			}
		}
	} while(i <= j);
	if (l < j) QSortAcs(Arr, l, j);
	if (i < r) QSortAcs(Arr, i, r);
}

void SortClasses(CAtlArray<VSClass*>& Arr, bool bAcsesnding /* = true */)
{
	if (Arr.GetCount() > 1)
	{
		if (bAcsesnding)
		{
			QSortAcs(Arr, 0, (int)Arr.GetCount() - 1);
		}
		else
		{
			QSortDesc(Arr, 0, (int)Arr.GetCount() - 1);
		}
	}
}

void QSortRes(CAtlArray<ResControl>& Arr, int l, int r)
{
	ResControl px = Arr[(l+r)/2];
	int i = l;
	int j = r;
	do 
	{
		while(lstrcmp(Arr[i].m_ID, px.m_ID) < 0) i++;
		while(lstrcmp(Arr[j].m_ID, px.m_ID) > 0) j--;
		if (i < j)
		{
			ResControl tmp = Arr[i];
			Arr[i] = Arr[j];
			Arr[j] = tmp;
			i++;j--;
		}
		else
		{
			if (i == j)
			{
				i++;j--;
			}
		}
	} while(i <= j);
	if (l < j) QSortRes(Arr, l, j);
	if (i < r) QSortRes(Arr, i, r);
}

void SortResources(CAtlArray<ResControl>& Arr)
{
	QSortRes(Arr, 0, (int)Arr.GetCount() - 1);
}

CString CreateIDName(CString TrancatedID)
{
	CString NewName;
	bool bUppercase = true;
	for (int i = 0; i < TrancatedID.GetLength(); i++)
	{
		if (TrancatedID.GetAt(i) == _T('_'))
		{
			bUppercase = true;
		}
		else
		{
			TCHAR Letter;
			if (bUppercase)
			{
#ifdef _UNICODE
				Letter = towupper(TrancatedID[i]);
#else
				Letter = toupper(TrancatedID[i]);
#endif
			}
			else
			{
#ifdef _UNICODE
				Letter = towlower(TrancatedID[i]);
#else
				Letter = tolower(TrancatedID[i]);
#endif
			}
			NewName += Letter;
			bUppercase = false;
		}
	}
	return NewName;
}

HRESULT GetDispatchProperty(IDispatch* pDisp, LPOLESTR lpName, VARIANT* pRes)
{
#ifdef _DEBUG
	ITypeInfoPtr pTypeInfo;
	LPTYPEATTR pTypeAttr;
	pDisp->GetTypeInfo(1, GetSystemDefaultLCID(), &pTypeInfo);
	pTypeInfo->GetTypeAttr(&pTypeAttr);
	pTypeInfo->ReleaseTypeAttr(pTypeAttr);
#endif
	DISPID DispId = 0;
	HRESULT hr = pDisp->GetIDsOfNames(IID_NULL, &lpName, 1, GetSystemDefaultLCID(), &DispId);
	if (hr != S_OK)
		return hr;
	_variant_t varRes;
	unsigned int ArgError;
	DISPPARAMS Params;
	Params.cArgs = 0;
	Params.rgvarg = NULL;
	Params.cNamedArgs = 0;
	Params.rgdispidNamedArgs = NULL;
	hr = pDisp->Invoke(DispId, IID_NULL, GetSystemDefaultLCID(), DISPATCH_PROPERTYGET, &Params, pRes, NULL, &ArgError);
	return hr;
}

int CompareVersions(LPCTSTR lpVersion1, LPCTSTR lpVersion2)
{
	TCHAR Num[16];
	//compare version
	UINT Ver2 = 0, Ver1 = 0;
	LPCTSTR lpEndVer1 = lpVersion1, lpStartVer1 = lpVersion1, lpEndVer2 = lpVersion2, lpStartVer2 = lpVersion2;
	while (lpEndVer1 && lpEndVer1[0])
	{
		lpEndVer1 = _tcschr(lpStartVer1, _T('.'));
		lpEndVer2 = _tcschr(lpStartVer2, _T('.'));

		if (lpEndVer1)
		{
			lstrcpyn(Num, lpStartVer1, (int)(lpEndVer1 - lpStartVer1) + 1);
		}
		else
		{
			lstrcpy(Num, lpStartVer1);
		}
		Ver1 = StrToInt(Num);
		if (lpEndVer2)
		{
			lstrcpyn(Num, lpStartVer2, (int)(lpEndVer2 - lpStartVer2) + 1);
		}
		else
		{
			lstrcpy(Num, lpStartVer2);
		}
		Ver2 = StrToInt(Num);
		if (Ver2 < Ver1)
			return 1;

		if (Ver2 > Ver1)
			return -1;

		lpStartVer1 = lpEndVer1 + 1;
		lpStartVer2 = lpEndVer2 + 1;
	}
	return 0;
}