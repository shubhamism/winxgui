// -------------------------------------------------------------------------
//	文件名		：	mergepath.c
//	创建者		：	许式伟
//	创建时间	：	2002-1-30 14:29:42
//	功能描述	：	
//
// -------------------------------------------------------------------------

#include "stdafx.h"
#include "baseimp.h"

STDMETHODIMP MergePath(LPTSTR szDestFile, LPCTSTR szPath, LPCTSTR szSrcFile)
{
	UINT nRoot;
	HRESULT hr;
	KStdPathParam para;

	if (*szPath == '\0')
	{
		strcpy(szDestFile, szSrcFile);
		return S_OK;
	}

	// 1) 如果SrcFile本身是绝对路径，直接对SrcFile进行标准化。
	para.pszDest = _GetRootPath(szDestFile, szSrcFile);
	nRoot = para.pszDest - szDestFile;
	if (nRoot & 1)	// 绝对路径
	{
		para.pszRootPathEnd = para.pszDest;
		para.fAbsolute		= TRUE;
		return _StdPath(&para, szSrcFile + nRoot);
	}
	
	// 2) 对基路径（szPath）进行标准化：
	para.pszDest =
	para.pszRootPathEnd = _GetRootPath(szDestFile, szPath);
	nRoot = para.pszDest - szDestFile;
	para.fAbsolute = (nRoot & 1);
	hr = _StdPath(&para, szPath + nRoot);
	if (hr != S_OK)
		return hr;

	// 3) 将SrcFile路径合到基路径中：
	if (para.pszDest[-1] != '/')
		*para.pszDest++ = '/';
	return _StdPath(&para, szSrcFile);
}

// -------------------------------------------------------------------------
