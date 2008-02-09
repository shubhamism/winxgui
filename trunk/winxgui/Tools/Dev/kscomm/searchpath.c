// -------------------------------------------------------------------------
//	文件名		：	searchpath.c
//	创建者		：	许式伟
//	创建时间	：	2002-1-30 14:24:41
//	功能描述	：	
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
#elif defined(__WIN32__)
#		define PLATEXT		".win32"
#endif

#ifndef PLATEXT
#error "Unknown Platform!!! - by GenDefaultFile()"
#endif

STDMETHODIMP_(BOOL) IsFileExist2(LPTSTR szFile)
{
	if (!IsFileExist(szFile))
	{
		_tcscat(szFile, PLATEXT);
		return IsFileExist(szFile);
	}
	return TRUE;
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
	if (szBasePath)	// 在此基路径下先搜索
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
