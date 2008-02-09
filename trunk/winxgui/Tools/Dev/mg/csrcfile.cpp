/* -------------------------------------------------------------------------
//	文件名		：	csrcfile.cpp
//	创建者		：	许式伟
//	创建时间	：	2002-3-7 10:50:40
//	功能描述	：	
//
//-----------------------------------------------------------------------*/

#define _ENABLE_TRACE
#include "stdafx.h"
#include "MakeGen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------------------

const TCHAR g_szCompileFmt[] = 
_T(
	"\n"
	"	@echo \"---> Compiling\" $< \"...\"\n"
	"	%s\n"
	"\n"
);

const TCHAR g_szNewLineFmt[] = _T("\t\\\n\t%s");

static STDMETHODIMP WriteDepency(stratom depFile, void* _pParam)
{
	KHandlerParam* pParam = (KHandlerParam*)_pParam;
	_ftprintf(pParam->fpDest, g_szNewLineFmt, GetAtomString(pParam->tblAtom, depFile));
	_dbg_fflush(pParam->fpDest);
	return S_OK;
}

STDMETHODIMP HandleCLangSrcFile(LPCTSTR szSrcFile, KHandlerParam* pParam)
{
	// objfile
	static TCHAR fname[_MAX_FNAME];
	static TCHAR ext[_MAX_EXT];
	static TCHAR szObjFile[_MAX_PATH];
	static TCHAR szSrcFileAbs[_MAX_PATH];
	
	_tsplitpath(szSrcFile, NULL, NULL, fname, ext);
	_stprintf(szObjFile, _T("$(ObjectDir)/%s.o"), fname);
	_ftprintf(pParam->fpDest, _T("%s :"), szObjFile);
	
	_ftprintf(pParam->fpDest, g_szNewLineFmt, szSrcFile);
	_dbg_fflush(pParam->fpDest);
	
	try	// check depency
	{
		if (
			pParam->fCheckDepency &&
			MergePath(szSrcFileAbs, pParam->szProjPath, szSrcFile) == S_OK
			)
		{
			stratom srcFile = AddStringAtom(pParam->tblAtom, szSrcFileAbs);
			CheckDepency(srcFile, pParam);
			ForEachDepFile(pParam->pDepMap, srcFile, WriteDepency, pParam);
		}
	}
	catch(...)
	{
		ASSERT(FALSE);
	}
	
	// compile
	_ftprintf(pParam->fpDest, g_szCompileFmt,
		_tcsicmp(ext, _T(".c")) == 0 ? _T("$(CompileC)") : _T("$(CompileCXX)")
		);

	// link depency
	AddString(pParam->pObjList, szObjFile);
	return S_OK;
}

// -------------------------------------------------------------------------
