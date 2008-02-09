/* -------------------------------------------------------------------------
//	文件名		：	qtmocfile.cpp
//	创建者		：	许式伟
//	创建时间	：	2002-3-7 10:49:17
//	功能描述	：	
//
//-----------------------------------------------------------------------*/

#include "stdafx.h"
#include "MakeGen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------------------

STDMETHODIMP_(BOOL) IsQTMocFile(LPCTSTR szFile)
{
	FILE* fpSrc;
	LPTSTR psz;
	TCHAR szLine[MG_LINE_MAX];
	BOOL  fQTMocFile = FALSE;
	
	fpSrc = _tfopen(szFile, _T("r"));
	if (fpSrc == NULL)
		return FALSE;

	for (;;)
	{
		*szLine = 0;
		_fgetts(szLine, MG_LINE_MAX, fpSrc);
		if (*szLine == 0 && feof(fpSrc))
			break;
		
		psz = szLine;
		while (*psz == ' ' || *psz == '\t') psz++;
		
		if (_tcsncmp(psz, _T("Q_OBJECT"), 8) == 0)
		{
			fQTMocFile = TRUE;
			break;
		}
	}
	fclose(fpSrc);
	return fQTMocFile;
}

const TCHAR g_szComileMocFmt[] =
_T(
	"%s : %s\n"
	"	@echo \"---> MocCompiling\" $< \"...\"\n"
	"	$(CompileMoc)\n"
	"\n"
);

STDMETHODIMP HandleQTMocFile(LPCTSTR szSrcFile, KHandlerParam* pParam)
{
	union
	{
		TCHAR szSrcFileAbs[_MAX_PATH];
		TCHAR szObjFile[_MAX_PATH];
	};
	
	try	// check depency
	{
		if (
			MergePath(szSrcFileAbs, pParam->szProjPath, szSrcFile) == S_OK &&
			IsQTMocFile(szSrcFileAbs)
			)
		{
			TCHAR fname[_MAX_FNAME];
			SplitPath(szSrcFile, NULL, NULL, fname, NULL);
			_tcsecpy(
				_tcsecpy(
					_tcsecpy(szObjFile, _T("$(ObjectDir)/")), fname), _T(".moc.o")
				);
			_ftprintf(pParam->fpDest, g_szComileMocFmt, szObjFile, szSrcFile);
			AddString(pParam->pObjList, szObjFile);			
		}
	}
	catch(...)
	{
		ASSERT(FALSE);
	}
	
	return S_OK;
}

// -------------------------------------------------------------------------

