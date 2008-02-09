// -------------------------------------------------------------------------
//	文件名		：	MakeGen.cpp
//	创建者		：	许式伟
//	创建时间	：	2002-1-21 14:25:44
//	功能描述	：	
//
// -------------------------------------------------------------------------

#define _ENABLE_TRACE
#include "stdafx.h"
#undef __Linked_KSCommon
#include "ksx_common.h"
#include "MakeGen.h"

enum KEnumSwitchs
{
	switchListCfg			= 0x0001,
	switchNoCheckDepency	= 0x0002,
};

// -l	listcfg
TCHAR g_sws[] = _T("ln");

// -------------------------------------------------------------------------

const TCHAR g_szSectSeps[] = _T("] \t\r\n");

STDMETHODIMP SkipSection(FILE* fpList, KHandlerParam* pParam)
{
	TCHAR szLine[MG_LINE_MAX];
	for (; GetSection(szLine, fpList, pParam) != S_OK;)
		;
	return S_OK;
}

KSectionHandler g_hndrs[] =
{
	{ "Config",  HandleSec_Config	},
	{ "Include", HandleSec_Include	},
	{ "Lib",	 HandleSec_Lib		},
	{ "Source",  HandleSec_Source	},
};

STDMETHODIMP GetSection(LPTSTR szLine, FILE* fpList, KHandlerParam* pParam)
{
	*szLine = 0;
	_fgetts(szLine, MG_LINE_MAX, fpList);

	if (*szLine == 0 || *szLine == '\n')
	{
		if (feof(fpList))
		{
			pParam->fnHandler = NULL;
			return S_OK;
		}
		return S_FALSE;
	}
	if (*szLine == '[')
	{
		LPCTSTR token;
		pParam->fnHandler = SkipSection;
		pParam->szSecParam = NULL;
		token = _tcstok(szLine+1, g_szSectSeps);
		if (token == NULL)
		{
			return S_OK;
		}
		for (UINT i = 0; i < countof(g_hndrs); ++i)
		{
			if (StrCmpI(g_hndrs[i].szSection, token) == 0)
			{
				pParam->fnHandler = g_hndrs[i].fnHandler;
				pParam->szSecParam = _tcstok(NULL, g_szSectSeps);
				//{{ by tsingbo ---> tools_mg_bugfix(1) sols-printf
				TRACE("------------ %s : %s ----------\n", 
						token, pParam->szSecParam ? pParam->szSecParam : "(null)");
				break;
			}
		}
		return S_OK;
	}
	return S_FALSE;
}

// -------------------------------------------------------------------------

const TCHAR g_szConfigDefaultFmt[] =
_T(
	"#\n"
	"# Configuration Default\n"
	"#\n"
	"ifeq ($(CFG),)\n"
	"	CFG = %s\n"
	"endif\n"
	"\n"
);

STDMETHODIMP GenMakeFile
	(
	LPCTSTR szMakeFile,
	LPCTSTR szPrjFile,
	LPCTSTR szConfigReq,
	LPCTSTR szProjPath,
	BOOL	fCheckDepency
	)
{
	static LPCTSTR  szIncDirs[MG_INCDIR_MAX];
	static LPCTSTR  szLibDirs[MG_LIBDIR_MAX];
	KMGStringList* pObjFileList = NULL;
	KMGDepencyMap* pDepMap = NULL;
	stratomtbl	   tblAtom = NULL;
	KHandlerParam  para;
	
	HRESULT hr   = E_FAIL;
	FILE* fpDest = NULL;
	FILE* fpList = NULL;
	fpList = _tfopen(szPrjFile, _T("r"));
	if (fpList == NULL)
	{
		_tprintf(_T("Error: Open ProjFile: %s Error!\n"), szPrjFile);
		goto lzExit;
	}
	fpDest = _tfopen(szMakeFile, _T("w"));
	if (fpDest == NULL)
	{
		_tprintf(_T("Error: Create MakeFile: %s Error!\n"), szMakeFile);
		goto lzExit;
	}
	_ftprintf(fpDest, g_szConfigDefaultFmt, szConfigReq == NULL ? _T("Debug") : szConfigReq);

	// sections
	pObjFileList		= CreateStringList();
	pDepMap				= CreateDepencyMap();
	tblAtom				= CreateAtomTable();
	para.fpDest			= fpDest;
	para.fnHandler		= SkipSection;
	para.szSecParam		= NULL;
	para.szConfigReq	= szConfigReq;
	para.pObjList		= pObjFileList;
	para.pDepMap		= pDepMap;
	para.tblAtom		= tblAtom;
	para.szIncDirs		= szIncDirs;
	para.nIncDirs		= 0;
	para.szLibDirs		= szLibDirs;
	para.nLibDirs		= 0;
	para.szProjPath		= szProjPath;
	para.fUseQTMoc		= TRUE;
	para.fCheckDepency	= fCheckDepency;
	for (; para.fnHandler; )
	{
		hr = para.fnHandler(fpList, &para);
		if (hr != S_OK)
			goto lzExit;
	}

	// link tool
	TRACE("---> Linking Product ....\n");
	if (hr == S_OK)
		LinkProduct(fpDest, para.pObjList);
	
lzExit:
	if (tblAtom)
		DestroyAtomTable(tblAtom);
	if (pDepMap)
		DestroyDepencyMap(pDepMap);
	if (pObjFileList)
		DestroyStringList(pObjFileList);
	if (fpDest)
		fclose(fpDest);
	if (fpList)
		fclose(fpList);
	return hr;
}

// -------------------------------------------------------------------------

const TCHAR g_szExtMak[] = _T(".mak");
const TCHAR g_szExtPrj[] = _T(".prj");

int main(int argc, char* argv[])
{
	SWITCHS sw;
	static TCHAR szCurDir[_MAX_PATH];
	static TCHAR szProjPath[_MAX_PATH];
	TCHAR szPrjFile[_MAX_PATH];
	TCHAR szMakeFile[_MAX_PATH];
	
	ksGetCwd(szCurDir, _MAX_PATH);
	TRACE("CurDir = %s\n", szCurDir);
	
	// 1). analyze switchs
	argc = AnalyzeSwitch(++argv, argc-1, &sw, g_sws);
	if (sw & switchUnknown)
	{
		goto lzPrompt;
	}

	// 2). get prjfile specified
	if (argc < 1)
	{
		// Generate default Prjfile Name:
		if (
			GenDefaultFile(szPrjFile, szCurDir, g_szExtPrj) != S_OK ||
			!IsFileExist2(szPrjFile)
			)
		{
lzPrompt:	puts(
				"Function: Generate Makefile from a Project file\n"
				"Usage: MakeGen [-l -n] Prjfile[.prj] Makefile[.mak] Config\n"
				"    Prjfile:   Project file.\n"
				"    Makefile:  Make file.\n"
				"    Config:    Generate Makefile the specified config. Default is all config."
				 );
			return -1;
		}
		TRACE("Default Prjfile = %s\n", szPrjFile);
	}
	else
	{
		_tcscpy(szPrjFile, argv[0]);
		GuessExt(szPrjFile, g_szExtPrj);
		if (!IsFileExist2(szPrjFile))
		{
			_tprintf(_T("Error: Open ProjFile: %s Error!\n"), szPrjFile);
			return -1;
		}
	}
	
	// 3). get makefile specified, and the config requested.
	LPCTSTR szConfigReq = NULL;
	if (argc < 2)
	{
		ForceExt(szMakeFile, szPrjFile, g_szExtMak);
	}
	else
	{
		_tcscpy(szMakeFile, argv[1]);
		GuessExt(szMakeFile, g_szExtMak);
		if (argc >= 3)
			szConfigReq = argv[2];
	}

	// 4). get project path, which is needed by GenMakeFile.
	MergePath(szProjPath, szCurDir, szPrjFile);
	*_tcsrchr(szProjPath, '/') = 0;
	TRACE("szProjPath = %s\n\n", szProjPath);
	
	// 5). now, start to Generate makefile
	GenMakeFile(
		szMakeFile, 
		szPrjFile, 
		szConfigReq, 
		szProjPath, 
		!(sw & switchNoCheckDepency)
		);
	
	return 0;
}

// -------------------------------------------------------------------------
