// -------------------------------------------------------------------------
//	文件名		：	splitpat2.c
//	创建者		：	许式伟
//	创建时间	：	2002-1-30 22:31:37
//	功能描述	：	
//
// -------------------------------------------------------------------------

#include "stdafx.h"
#include "ks_fileutils.h"

STDMETHODIMP_(void) SplitPath2(LPCTSTR szFileOrg, LPTSTR szPath, LPTSTR szFile)
{
	TCHAR drive	[_MAX_DRIVE];
	TCHAR dir	[_MAX_DIR];
	TCHAR fname	[_MAX_FNAME];
	TCHAR ext	[_MAX_EXT];
	SplitPath(szFileOrg, drive, dir, fname, ext);
	if (szPath)
	{
		StrECopy(
			StrECopy(szPath, drive), dir
			);
	}
	if (szFile)
	{
		StrECopy(
			StrECopy(szFile, fname), ext
			);
	}
}

// -------------------------------------------------------------------------
