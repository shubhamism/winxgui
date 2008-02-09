// -------------------------------------------------------------------------
//	�ļ���		��	stdpath.c
//	������		��	��ʽΰ
//	����ʱ��	��	2002-1-28 19:30:34
//	��������	��	��׼��һ���ļ�·����
//		0). ���е�PathSepת��Ϊ"/"��������"\"��
//		1). ��������·�������� "./" ���� "D:./" ��ʼ������D���̷���
//		2). ����Ǿ���·������:
//			���� Linux, szRoot = "/"��
//			���� DOS/Windows, szRoot = "D:/"  ���� "/", ����D���̷���
//	eg.
//		test.cpp					=> ./test.cpp
//		d:\..\tempfile				=> error path
//		../temp/ign/../file.c		=> ./../temp/file.c
//		c:/./.../..exe\Hello.cpp	=> c:/../../..exe/Hello.cpp	
//			{{ --> ע��: ..exe�ǺϷ���Ŀ¼��
//			{{ --> Windows֧�� ".../" = "../../" ��ʾ������
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

		// 1) û�� PathSep
		if (szSrcFile[pos] == 0)
			break;
		if (pos == 0)	// ������PathSep���� - "//", ��Ϊ Error��
			goto lzError;
		
		// 2) ��ͨĿ¼ 
		for (i = 0; i < pos; ++i)
		{
			if (szSrcFile[i] != '.') // ���� .. ���� .
			{
				while (pos--)
					*pszDest++ = *szSrcFile++;
				*pszDest++ = '/';
				++szSrcFile;
				goto lzContinue;
			}
		}
		
		// 3) �� .. �� .
		//    Ϊ��֧��Windows�� ".../" = "../../" ��ʾ������������while���
		szSrcFile += pos+1;
		while (--pos)
		{
			if (pDest->pszRootPathEnd >= pszDest) // �Ѿ����˵�����!
			{
				if (pDest->fAbsolute)	// ���Ǿ���·������ô�϶�����Ч��·���ˡ�
					goto lzError;
				// ���·������ôҪ�� ".../" ��ʽתΪ "../../"
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
			// pszDest����һ��Ŀ¼:
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

// 1). ��� szPath ��һ�����·����szRoot = "", "./" ���� "D:", "D:./"
// 2). ���򣬶��� Linux, szRoot = "/"��
//			 ���� DOS/Windows, szRoot = "D:/"  ���� "/", ����D���̷���
// ����ֵ = pszRootPathEnd
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
