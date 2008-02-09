/* -------------------------------------------------------------------------
//	�ļ���		��	gendeffile.c
//	������		��	��ʽΰ
//	����ʱ��	��	2002-3-2 18:16:19
//	��������	��	
//
//-----------------------------------------------------------------------*/

#include "stdafx.h"

// ���ܣ�ȡ·�����һ������
//	1) ��� szPath = '/' ���� nil, �� ʧ�ܡ�
//  2) ��� szPath = '~/workspace/Tools/MakeGen', �� szPathName = 'MakeGen'
//			szPath = 'tcc/', �� szPathName = 'tcc'
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

// ���ܣ��������¹�������Ĭ���ļ���:
//	1) ��� szPath = '/' ���� nil, �� ʧ�ܡ�
//  2) ��� szPath = '~/workspace/Tools/MakeGen', szExt = '.prj', ��
//			szDefaultFile = ~/workspace/Tools/MakeGen/MakeGen.prj
//			szPath = 'tcc', ��
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
