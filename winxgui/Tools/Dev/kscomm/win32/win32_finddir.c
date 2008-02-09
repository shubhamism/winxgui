// -------------------------------------------------------------------------
//	文件名		：	win32_finddir.c
//	创建者		：	许式伟
//	创建时间	：	2002-2-8 13:54:11
//	功能描述	：	
//
// -------------------------------------------------------------------------

#include "stdafx.h"

#if defined(__WIN32__)

#include "ks_fileutils.h"
#include "ks_dir.h"

#define NULL_HDIR	(-1)

static TCHAR g_szExtAll[] = _T("*.*");

HRESULT __cdecl ksFindFirstA(LPCTSTR szDir, FILEINFO* fi)
{
	TCHAR	path[_MAX_PATH];
	LPTSTR psz;
	
	if (szDir == NULL || *szDir == 0)
	{
		_tcsecpy(path, g_szExtAll);
	}
	else
	{
		psz = _tcsecpy(path, szDir);
		if (psz[-1] != '/' && psz[-1] != '\\')
		{
			*psz++ = '/';
		}
		_tcsecpy(psz, g_szExtAll);
	}
	fi->hdir = _findfirst(path, &fi->find);

	return (fi->hdir == NULL_HDIR ? S_FALSE : S_OK);
}

#endif // __WIN32__

// -------------------------------------------------------------------------
