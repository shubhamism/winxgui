// -------------------------------------------------------------------------
//	�ļ���		��	string.c
//	������		��	��ʽΰ
//	����ʱ��	��	2002-1-27 20:27:40
//	��������	��	
//
// -------------------------------------------------------------------------

#include "stdafx.h"

STDMETHODIMP_(LPTSTR) StrECopy(LPTSTR pszDest, LPCTSTR pszSrc)
{
	while ((*pszDest = *pszSrc) != 0)
	{
		++pszDest;
		++pszSrc;
	}
	return pszDest;
}

STDMETHODIMP_(int) GetKeywordIndex(LPCTSTR szKey, LPCTSTR* szKeys, UINT nKeys)
{
	UINT i;
	for (i = 0; i < nKeys; ++i)
	{
		if (StrCmpI(szKey, szKeys[i]) == 0)
		{
			return i;
		}
	}
	return -1;
}

// -------------------------------------------------------------------------
