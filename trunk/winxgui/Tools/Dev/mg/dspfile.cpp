/* -------------------------------------------------------------------------
//	文件名		：	mg/dspfile.cpp
//	创建者		：	许式伟
//	创建时间	：	2003-3-2 21:07:38
//	功能描述	：	
//
// -----------------------------------------------------------------------*/

#include "stdafx.h"
#include "MakeGen.h"
#include <stdlib.h>

// -------------------------------------------------------------------------

typedef
struct __KHandleDspFileLocal
{
	TCHAR szSrcFile[_MAX_PATH];
	TCHAR szLine[MG_LINE_MAX];
}KHandleDspFileLocal;

STDMETHODIMP HandleSingleFile(LPCTSTR szSrcFile, KHandlerParam* pParam);
STDMETHODIMP HandleDspFile(LPCTSTR szSrcFile, KHandlerParam* pParam)
{
	KHandleDspFileLocal* p;
	LPTSTR token;
	TCHAR* szLine;
	FILE* fpSrc;
	
	p = (KHandleDspFileLocal*)malloc(sizeof(KHandleDspFileLocal));
	szLine = p->szLine;
	
	MergePath(p->szSrcFile, pParam->szProjPath, szSrcFile);

	fpSrc = fopen(p->szSrcFile, "r");
	if (fpSrc == NULL)
	{
		delete p;
		return S_FALSE;
	}
	
	for (;;)
	{
		*szLine = 0;
		_fgetts(szLine, MG_LINE_MAX, fpSrc);
		if (*szLine == 0 && feof(fpSrc))
			break;

		if (_tcsncmp(szLine, "SOURCE=", 7) == 0)
		{
			token = _tcstok(szLine+7, g_szSeps);
			for (LPTSTR psz = token; *psz; ++psz)
				if (*psz == '\\')
					*psz = '/';
			HandleSingleFile(token, pParam);
		}
	}

	delete p;
	fclose(fpSrc);
	return S_OK;
}

// -------------------------------------------------------------------------
