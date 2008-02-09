// -------------------------------------------------------------------------
//	�ļ���		��	chkdep.cpp
//	������		��	��ʽΰ
//	����ʱ��	��	2002-1-29 14:02:54
//	��������	��	
//
// -------------------------------------------------------------------------

#define _ENABLE_TRACE
#include "stdafx.h"
#include "chkdep.h"
#include <stdlib.h>

#ifndef CD_LINE_MAX
#define CD_LINE_MAX				1024
#endif

#ifndef E_PATH_INVALID
#define E_PATH_INVALID			E_FAIL
#endif

#define is_stl_header(psz)		(_tcschr(psz, '.') == NULL)

// -------------------------------------------------------------------------

STDMETHODIMP LookupDepFile(LPTSTR szDepFile, FILE* fpSrc, BOOL* pfCheckCurDir)
{
	LPTSTR psz;
	TCHAR* szLine = new TCHAR[CD_LINE_MAX];

	*szDepFile = 0;
	*pfCheckCurDir = FALSE;
	for (;;)
	{
		*szLine = 0;
		_fgetts(szLine, CD_LINE_MAX, fpSrc);
		if (*szLine == 0 && feof(fpSrc))
		{
			delete[] szLine;
			return S_FALSE;
		}

		psz = szLine;
		while (*psz == ' ' || *psz == '\t') psz++;
		if (*psz++ != '#')
			continue;

		while (*psz == ' ' || *psz == '\t') psz++;
		if (_tcsncmp(psz, _T("include"), 7) != 0)
			continue;

		TRACE("szInclude = %s\n", psz);
		
		psz += 7;
		while (*psz == ' ' || *psz == '\t') psz++;
		if (*psz == '\"')
		{
			*pfCheckCurDir = TRUE;
		}
		else
		{
			ASSERT(*psz == '<');
			*pfCheckCurDir = FALSE;
		}
		psz = strtok(++psz, _T(">\"\r\n"));
		if (psz == NULL || *psz == 0 || is_stl_header(psz))
			continue;

		_tcscpy(szDepFile, psz);
		delete[] szLine;
		return S_OK;
	}
}

// -------------------------------------------------------------------------

struct tagKCheckDepencyLocal
{
	TCHAR szSrcPath[_MAX_PATH];
	TCHAR szDepFileAbs[_MAX_PATH];	// ����·����ʾ DepFile!
	TCHAR szDepFile[_MAX_PATH];
};
typedef struct tagKCheckDepencyLocal KCheckDepencyLocal;

STDMETHODIMP CheckDepency(stratom srcFile, KCheckDepencyParam* pParam)
{
	BOOL	 fCheckCurDir;
	FILE*	 fpSrc;
	stratom	 depFile;
	LPCTSTR	 psz;
	LPCTSTR	 szSrcFile;
	LPTSTR	 szSrcPath;
	LPTSTR	 szDepFileAbs;
	LPTSTR	 szDepFile;
	HRESULT	 hr = E_PATH_INVALID;
	KCheckDepencyLocal* pLocal = NULL;
	
	szSrcFile = GetAtomString(pParam->tblAtom, srcFile);
	TRACE("Checking Depency Of %s...\n", szSrcFile);

	psz = _tcsrchr(szSrcFile, '/');
	if (psz == NULL)
		goto lzError; // Ҫ��szSrcFile�Ǳ�׼·����Ҳ����˵���϶��� '/'

	// >>> ��Windows�·�����ջ��� (Linux�»�û��:-)
	// ��������Ϊ�˼��ٶ�ջ��ʹ�ã��Ӷ�����ջ����Ŀ����ԡ�
	pLocal = (KCheckDepencyLocal*)malloc(sizeof(KCheckDepencyLocal));
	szSrcPath = pLocal->szSrcPath;
	szDepFileAbs = pLocal->szDepFileAbs;
	szDepFile = pLocal->szDepFile;

	_tcsncpy(szSrcPath, szSrcFile, psz - szSrcFile);
	szSrcPath[psz - szSrcFile] = 0;

	StartCheckDepency(srcFile, pParam);

	fpSrc = _tfopen(szSrcFile, _T("r"));
	if (fpSrc == NULL)
		goto lzError;	// �ļ�������?
	
	while (LookupDepFile(szDepFile, fpSrc, &fCheckCurDir) == S_OK)
	{
		if (
			S_OK == SearchFilePath(
				szDepFileAbs, szDepFile,
				pParam->szIncDirs, pParam->nIncDirs,
				fCheckCurDir ? szSrcPath : NULL)
			)
		{
			depFile = AddStringAtom(pParam->tblAtom, szDepFileAbs);
			if (!IsDepencyChecked(depFile, pParam))
			{
				CheckDepency(depFile, pParam);
			}
			AddDepency(srcFile, depFile, pParam);
		}
	}
	fclose(fpSrc);
	TRACE(">>> End Checking Depency Of %s\n", szSrcFile);
	hr = S_OK;
	
lzError:
	if (pLocal)
		free(pLocal);
	return hr;
}

// -------------------------------------------------------------------------
