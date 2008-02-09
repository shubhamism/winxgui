// -------------------------------------------------------------------------
//	�ļ���		��	linux_finddir.c
//	������		��	��ʽΰ
//	����ʱ��	��	2002-2-8 13:54:11
//	��������	��	
//
// -------------------------------------------------------------------------

#include "stdafx.h"

#if defined(__LINUX__)

#include "ks_dir.h"

#define NULL_HDIR		NULL

HRESULT __cdecl ksFindFirstA(LPCSTR szDir, FILEINFOA* fi)
{
	fi->hdir = opendir(szDir);
	return ksFindNextA(fi);
}

HRESULT __cdecl ksFindNextA(FILEINFOA* fi)
{
	if (fi->hdir == NULL_HDIR)
	{
		return S_FALSE;
	}
	fi->find = readdir(fi->hdir);
	return (fi->find == NULL ? S_FALSE : S_OK);
}

#endif // __LINUX__

// -------------------------------------------------------------------------
