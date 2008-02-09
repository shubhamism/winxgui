// -------------------------------------------------------------------------
//	�ļ���		��	mergepath.c
//	������		��	��ʽΰ
//	����ʱ��	��	2002-1-30 14:29:42
//	��������	��	
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

	// 1) ���SrcFile�����Ǿ���·����ֱ�Ӷ�SrcFile���б�׼����
	para.pszDest = _GetRootPath(szDestFile, szSrcFile);
	nRoot = para.pszDest - szDestFile;
	if (nRoot & 1)	// ����·��
	{
		para.pszRootPathEnd = para.pszDest;
		para.fAbsolute		= TRUE;
		return _StdPath(&para, szSrcFile + nRoot);
	}
	
	// 2) �Ի�·����szPath�����б�׼����
	para.pszDest =
	para.pszRootPathEnd = _GetRootPath(szDestFile, szPath);
	nRoot = para.pszDest - szDestFile;
	para.fAbsolute = (nRoot & 1);
	hr = _StdPath(&para, szPath + nRoot);
	if (hr != S_OK)
		return hr;

	// 3) ��SrcFile·���ϵ���·���У�
	if (para.pszDest[-1] != '/')
		*para.pszDest++ = '/';
	return _StdPath(&para, szSrcFile);
}

// -------------------------------------------------------------------------
