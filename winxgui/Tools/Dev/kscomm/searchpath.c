// -------------------------------------------------------------------------
//	�ļ���		��	searchpath.c
//	������		��	��ʽΰ
//	����ʱ��	��	2002-1-30 14:24:41
//	��������	��	
//
// -------------------------------------------------------------------------

#include "stdafx.h"
#include "ks_fileutils.h"

// -------------------------------------------------------------------------

STDMETHODIMP_(BOOL) IsFileExist(LPCTSTR szFile)
{
	FILE* fp = _tfopen(szFile, _T("r"));
	if (fp == NULL)
	{
		return FALSE;
	}
	fclose(fp);
	return TRUE;
}

// -------------------------------------------------------------------------

#if defined(__LINUX__)
#	if defined(__INTEL__)
#		define PLATEXT		".li"
#	elif defined(__SPARC__)
#		define PLATEXT		".ls"
#	endif
#elif defined(__SOLS__)
#	if defined(__INTEL__)
#		define PLATEXT		".si"
#	elif defined(__SPARC__)
#		define PLATEXT		".ss"
#	endif
#elif defined(__WINDOWS__)
#		define PLATEXT		".win"
#endif

#if defined(__32BIT__) || defined(__x86_32__)
#define BITSEXT				"32"
#elif defined(__64BIT__) || defined(__x86_64__)
#define BITSEXT				"64"
#endif

#if !defined(PLATEXT) || !defined(BITSEXT)
#error "Unknown Platform!!! - by GenDefaultFile()"
#endif

STDMETHODIMP_(BOOL) IsFileExist2(LPTSTR szFile)
{
	LPTSTR p = _tcsrchr(szFile, '\0');
	LPTSTR p2 = _tcsecpy(p, PLATEXT);
	
	_tcscpy(p2, BITSEXT);
	if (IsFileExist(szFile))
		return TRUE;
	
	*p2 = '\0';
	if (IsFileExist(szFile))
		return TRUE;

	*p = '\0';
	return IsFileExist(szFile);
}

// -------------------------------------------------------------------------

STDMETHODIMP SearchFilePath(
	LPTSTR	 szDestFile,
	LPCTSTR	 szFileSearch,
	LPCTSTR* szDirs,
	UINT	 nDirs,
	LPCTSTR	 szBasePath
	)
{
	UINT i;
	if (szBasePath)	// �ڴ˻�·����������
	{
		if (
			MergePath(szDestFile, szBasePath, szFileSearch) == S_OK &&
			IsFileExist(szDestFile)
			)
			return S_OK;
	}
	for (i = 0; i < nDirs; ++i)
	{
		if (
			MergePath(szDestFile, szDirs[i], szFileSearch) == S_OK &&
			IsFileExist(szDestFile)
			)
			return S_OK;
	}
	return S_FALSE;
}

// -------------------------------------------------------------------------
