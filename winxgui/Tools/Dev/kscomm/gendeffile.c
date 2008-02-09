/* -------------------------------------------------------------------------
//	文件名		：	gendeffile.c
//	创建者		：	许式伟
//	创建时间	：	2002-3-2 18:16:19
//	功能描述	：	
//
//-----------------------------------------------------------------------*/

#include "stdafx.h"

// 功能：取路径最后一级名字
//	1) 如果 szPath = '/' 或者 nil, 则 失败。
//  2) 如果 szPath = '~/workspace/Tools/MakeGen', 则 szPathName = 'MakeGen'
//			szPath = 'tcc/', 则 szPathName = 'tcc'
STDMETHODIMP GetPathName(LPTSTR szPathName, LPCTSTR szPath)
{
	LPCTSTR psz;
	LPCTSTR psz2;

	if (*szPath == 0)
	{
		return E_FAIL;
	}
	psz = _tcschr(szPath, 0);
	if (psz[-1] == '/' || psz[-1] == '\\')
	{
		--psz;
	}
	if (psz <= szPath) // szPath is root: '/'
	{
		return E_FAIL;
	}

	for (psz2 = psz; psz2 > szPath; --psz2)
	{
		if (psz2[-1] == '/' || psz2[-1] == '\\')
			break;
	}

	while (psz2 < psz)
	{
		*szPathName++ = *psz2++;
	}
	*szPathName = 0;
	
	return S_OK;
}

// 功能：按照以下规则生成默认文件名:
//	1) 如果 szPath = '/' 或者 nil, 则 失败。
//  2) 如果 szPath = '~/workspace/Tools/MakeGen', szExt = '.prj', 则
//			szDefaultFile = ~/workspace/Tools/MakeGen/MakeGen.prj
//			szPath = 'tcc', 则
//			szDefaultFile = tcc/tcc.prj
STDMETHODIMP GenDefaultFile(LPTSTR szDestFile, LPCTSTR szPath, LPCTSTR szExt)
{
	HRESULT hr;
	LPTSTR psz;
	TCHAR szPathName[_MAX_PATH];

	hr = GetPathName(szPathName, szPath);
	if (hr != S_OK)
		return hr;

	psz = _tcsecpy(szDestFile, szPath);
	if (psz[-1] != '/' && psz[-1] != '\\')
	{
		*psz++ = '/';
	}

	_tcsecpy(
		_tcsecpy(psz, szPathName), szExt
		);

	return S_OK;
}

// -------------------------------------------------------------------------
