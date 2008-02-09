// -------------------------------------------------------------------------
//	文件名		：	stdpath.c
//	创建者		：	许式伟
//	创建时间	：	2002-1-28 19:30:34
//	功能描述	：	标准化一个文件路径。
//		0). 所有的PathSep转换为"/"，而不用"\"。
//		1). 如果是相对路径，则以 "./" 或者 "D:./" 开始。其中D是盘符。
//		2). 如果是绝对路径，则:
//			对于 Linux, szRoot = "/"。
//			对于 DOS/Windows, szRoot = "D:/"  或者 "/", 其中D是盘符。
//	eg.
//		test.cpp					=> ./test.cpp
//		d:\..\tempfile				=> error path
//		../temp/ign/../file.c		=> ./../temp/file.c
//		c:/./.../..exe\Hello.cpp	=> c:/../../..exe/Hello.cpp	
//			{{ --> 注意: ..exe是合法的目录名
//			{{ --> Windows支持 ".../" = "../../" 表示方法。
// -------------------------------------------------------------------------

#include "stdafx.h"
#include "ks_fileutils.h"
#include "baseimp.h"

#ifndef ASSERT
#include <assert.h>
#define ASSERT(e)	assert(e)
#endif

// -------------------------------------------------------------------------

static const TCHAR g_szPathSep[] = _T("/\\");

STDMETHODIMP _StdPath(KStdPathParam* pDest, LPCTSTR szSrcFile)
{
	UINT pos, i;
	LPTSTR pszDest = pDest->pszDest;

	//ASSERT(pDest->pszRootPathEnd[-1] == '/');
	//ASSERT(pDest->pszDest[-1] == '/');
	ASSERT(pDest->pszDest >= pDest->pszRootPathEnd);
	for (;;)
	{
		pos = _tcscspn(szSrcFile, g_szPathSep);

		// 1) 没有 PathSep
		if (szSrcFile[pos] == 0)
			break;
		if (pos == 0)	// 有两个PathSep相连 - "//", 视为 Error！
			goto lzError;
		
		// 2) 普通目录 
		for (i = 0; i < pos; ++i)
		{
			if (szSrcFile[i] != '.') // 不是 .. 或者 .
			{
				while (pos--)
					*pszDest++ = *szSrcFile++;
				*pszDest++ = '/';
				++szSrcFile;
				goto lzContinue;
			}
		}
		
		// 3) 是 .. 或 .
		//    为了支持Windows的 ".../" = "../../" 表示方法，这里用while语句
		szSrcFile += pos+1;
		while (--pos)
		{
			if (pDest->pszRootPathEnd >= pszDest) // 已经回退到根了!
			{
				if (pDest->fAbsolute)	// 且是绝对路径，那么肯定是无效的路径了。
					goto lzError;
				// 相对路径，那么要将 ".../" 格式转为 "../../"
				for (;;)
				{
					*pDest->pszRootPathEnd++ = '.';
					*pDest->pszRootPathEnd++ = '.';
					*pDest->pszRootPathEnd++ = '/';
					if (!--pos)
						break;
				}
				pszDest = pDest->pszRootPathEnd;
				break;
			}
			// pszDest回退一个目录:
			for (;;)
			{
				--pszDest;
				if (pszDest[-1] == '/')
					break;
			}
		}
lzContinue: ;
	}
	pDest->pszDest = StrECopy(pszDest, szSrcFile);
	return S_OK;
	
lzError:
	return E_PATH_INVALID;
}

// 1). 如果 szPath 是一个相对路径，szRoot = "", "./" 或者 "D:", "D:./"
// 2). 否则，对于 Linux, szRoot = "/"。
//			 对于 DOS/Windows, szRoot = "D:/"  或者 "/", 其中D是盘符。
// 返回值 = pszRootPathEnd
STDMETHODIMP_(LPTSTR) _GetRootPath(LPTSTR szRoot, LPCTSTR szPath)
{
	if (*szPath)
	{
		if (szPath[1] == ':')
		{
			*szRoot++ = szPath[0];
			*szRoot++ = ':';
			szPath += 2;
		}
		if (*szPath == '/' || *szPath == '\\')
		{
			*szRoot++ = '/';
			return szRoot;
		}
	}
	if (
		szPath[0] == '.' &&
		(szPath[1] == '/' || *szPath == '\\')
		)
	{
		*szRoot++ = '.';
		*szRoot++ = '/';
	}
	return szRoot;
}

STDMETHODIMP StdPath(LPTSTR szDestPath, LPCTSTR szPath)
{
	UINT nRoot;
	KStdPathParam para;

	para.pszDest = 
	para.pszRootPathEnd = _GetRootPath(szDestPath, szPath);
	
	nRoot = para.pszDest - szDestPath;
	para.fAbsolute = (nRoot & 1);
	
	return _StdPath(&para, szPath + nRoot);
}

// -----------------------------------------------------------------------*/
