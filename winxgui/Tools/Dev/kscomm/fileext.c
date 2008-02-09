// -------------------------------------------------------------------------
//	文件名		：	fileext.c
//	创建者		：	许式伟
//	创建时间	：	2002-1-24 16:50:27
//	功能描述	：	
//
// -------------------------------------------------------------------------

#include "stdafx.h"
#include "ks_fileutils.h"

STDMETHODIMP_(void) ForceExt(LPTSTR szFileDest, LPCTSTR szFileSrc, LPCTSTR szExtDest)
{
	TCHAR drive	[_MAX_DRIVE];
	TCHAR dir	[_MAX_DIR];
	TCHAR fname	[_MAX_FNAME];
	TCHAR ext	[_MAX_EXT];
	SplitPath(szFileSrc, drive, dir, fname, ext);
	MakePath(szFileDest, drive, dir, fname, szExtDest);
}

STDMETHODIMP GuessExt(LPTSTR szFileSrc, LPCTSTR szExtDest)
{
	TCHAR drive	[_MAX_DRIVE];
	TCHAR dir	[_MAX_DIR];
	TCHAR fname	[_MAX_FNAME];
	TCHAR ext	[_MAX_EXT];
	SplitPath(szFileSrc, drive, dir, fname, ext);
	if (*ext == 0)
	{
		MakePath(szFileSrc, drive, dir, fname, szExtDest);
		return S_OK;
	}
	return S_FALSE;
}

// -------------------------------------------------------------------------
