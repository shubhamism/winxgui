// -------------------------------------------------------------------------
//	文件名		：	sec_source.cpp
//	创建者		：	许式伟
//	创建时间	：	2002-1-27 16:25:29
//	功能描述	：	
//
// -------------------------------------------------------------------------

#include "stdafx.h"
#include "MakeGen.h"

/* -------------------------------------------------------------------------
 [Source]
	{$(SrcFile) $(SrcType)}
// -----------------------------------------------------------------------*/

const TCHAR g_szMakeAll[] = 
_T(
	"#\n"
	"# Making...\n"
	"#\n"
	"all : $(ProductDir) $(ObjectDir) StartMake $(Product) EndMake\n"
	"\n"
	"$(ProductDir) :\n"
	"	@mkdir -p $(ProductDir)\n"
	"\n"
	"ifneq ($(ProductDir),$(ObjectDir))\n"
	"$(ObjectDir) :\n"
	"	@mkdir -p $(ObjectDir)\n"
	"endif\n"
	"\n"
	"clean :\n"
	"	@rm -f $(ObjectDir)/*.o\n"
	"	@rm -f $(Product)\n"
	"\n"
	"StartMake :\n"
	"	@echo \"-------------- Configuration:\" $(PROJ) $(CFG) \"--------------\"\n"
	"ifeq ($(ForceLink),1)\n"
	"	@rm -f $(Product)\n"
	"endif\n"
	"\n"
	"EndMake :\n"
	"	@echo \">>> Success <<<\"\n"
	"\n"
	"#\n"
	"# Source Files, Objects & Product\n"
	"#\n"
);

LPCTSTR g_szCLangExt[] =
{
	_T(".h"),
	_T(".hpp"),
	_T(".hxx"),
	_T(".c"),
	_T(".cpp"),
	_T(".cxx"),
	_T(".cc"),
};

STDMETHODIMP HandleSingleFile(LPCTSTR szSrcFile, KHandlerParam* pParam);
STDMETHODIMP HandleCLangSrcFile(LPCTSTR szSrcFile, KHandlerParam* pParam);
STDMETHODIMP HandleQTMocFile(LPCTSTR szSrcFile, KHandlerParam* pParam);
STDMETHODIMP HandleDspFile(LPCTSTR szSrcFile, KHandlerParam* pParam);

struct ScanDirFileParam
{
	const TCHAR* ext;
	KHandlerParam* pParam;
};

STDMETHODIMP ScanDirFile(LPCTSTR szFile, FILEINFO* fi, void* pParam)
{
	ScanDirFileParam* para = (ScanDirFileParam*)pParam;
	
	TCHAR ext[_MAX_EXT];
	_tsplitpath(szFile, NULL, NULL, NULL, ext);
	if (strcmp(ext, para->ext) == 0)
	{
		HandleSingleFile(szFile, para->pParam);
	}
	return S_OK;
}

STDMETHODIMP HandleSingleFile(LPCTSTR token, KHandlerParam* pParam)
{
	TCHAR ext[_MAX_EXT];
	_tsplitpath(token, NULL, NULL, NULL, ext);
	
	if (strchr(token, '*') != NULL)
	{
		TCHAR szDir[_MAX_PATH];
		SplitPath2(token, szDir, NULL);
		if (*szDir == '\0')
			_tcscpy(szDir, "."); 
		ScanDirFileParam para = { ext, pParam };
		ScanDirectory(szDir, ScanDirFile, 0, &para);
	}
	else
	{
		for (UINT i = 0; i < countof(g_szCLangExt); ++i)
		{
			if (_tcsicmp(ext, g_szCLangExt[i]) == 0)
			{
				if (i >= 3)
				{
					HandleCLangSrcFile(token, pParam);
				}
				else if (pParam->fUseQTMoc)
				{
					HandleQTMocFile(token, pParam);
				}
				return S_OK;
			}
		}

		if (_tcsicmp(ext, ".dsp") ==  0)
		{
			HandleDspFile(token, pParam);
		}
	}
	return S_OK;
}

STDMETHODIMP HandleSec_Source(FILE* fpList, KHandlerParam* pParam)
{
	// make tools
	_fputts(g_szMakeAll, pParam->fpDest);

	// compile(s)
	TCHAR szLine[MG_LINE_MAX];
	LPTSTR token;
	for (; GetSection(szLine, fpList, pParam) != S_OK;)
	{
		token = _tcstok(szLine, g_szSeps);
		if (token == NULL)
			continue;

		HandleSingleFile(token, pParam);
	}
	return S_OK;
}

// -------------------------------------------------------------------------
