// -------------------------------------------------------------------------
//	文件名		：	sec_pathlist.cpp
//	创建者		：	许式伟
//	创建时间	：	2002-1-27 16:24:58
//	功能描述	：	
//
// -------------------------------------------------------------------------

#define _ENABLE_TRACE
#include "stdafx.h"
#include "MakeGen.h"

/* -------------------------------------------------------------------------
 [Inlcude]
	{$(Include)}

 [Lib]
	{$(Lib)}
// -----------------------------------------------------------------------*/

STDMETHODIMP HandleSec_PathList
	(
	FILE*	fpList,
	KHandlerParam* pParam,
	LPCTSTR szVar,
	LPCTSTR	szFmt,
	LPCTSTR* szDirs,
	UINT&	nDirs,
	stratomtbl tblAtom
	)
{
	TCHAR szLine[MG_LINE_MAX];
	TCHAR szDirAbs[_MAX_PATH];
	LPTSTR token;

	_ftprintf(pParam->fpDest, szVar);
	for (; GetSection(szLine, fpList, pParam) != S_OK;)
	{
		token = _tcstok(szLine, g_szSeps);
		if (token == NULL)
			continue;
		_ftprintf(pParam->fpDest, szFmt, token);

		if (token[1] == 0 && token[0] == '.')
			token = (LPTSTR)_T("./");
		MergePath(szDirAbs, pParam->szProjPath, token);
		szDirs[nDirs++] = GetAtomString(tblAtom, AddStringAtom(tblAtom, szDirAbs));
		TRACE("%s%s\n", szVar, szDirAbs);
	}
	_fputts(_T("\n\n"), pParam->fpDest);
	return S_OK;
}

// -------------------------------------------------------------------------

STDMETHODIMP HandleSec_Include(FILE* fpList, KHandlerParam* pParam)
{
	return HandleSec_PathList(
		fpList,
		pParam,
		_T("IncludeDir = "),
		_T("-I%s "),
		pParam->szIncDirs,
		pParam->nIncDirs,
		pParam->tblAtom
		);
}

STDMETHODIMP HandleSec_Lib(FILE* fpList, KHandlerParam* pParam)
{
	return HandleSec_PathList(
		fpList,
		pParam,
		_T("LibDir     = "),
		_T("-L%s "),
		pParam->szLibDirs,
		pParam->nLibDirs,
		pParam->tblAtom
		);
}

// -------------------------------------------------------------------------
