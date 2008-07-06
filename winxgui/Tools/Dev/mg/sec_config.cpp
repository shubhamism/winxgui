// -------------------------------------------------------------------------
//	文件名		：	sec_config.cpp
//	创建者		：	许式伟
//	创建时间	：	2002-1-27 16:19:16
//	功能描述	：	
//
// -------------------------------------------------------------------------

#define _ENABLE_TRACE
#include "stdafx.h"
#include "MakeGen.h"
#include <stdlib.h>

#ifndef _tcscmp
#define _tcscmp		strcmp
#endif

#define g_szCheckLink			\
		"	CheckLink    = @ldd -u -r $(Product); echo"

#if defined(__WIN32__)
#	define g_szExportDefFile	"_export_.def"
#	define g_szCFlagsDef0		""
#	define g_szCCompiler		"gcc"
#	define g_szCXXCompiler		"g++"
#   define g_szExeLinker        \
		"@g++ $(LibDir) -o $(Product)\n" \
		g_szCheckLink
#   define g_szDllLinker        \
		"@g++ $(LibDir) -W1 -shared -o $(Product)\n" \
		g_szCheckLink

#elif defined(__SOLS__) && defined(Uses_SunProCC)
#	define g_szCFlagsDef0		""
#	define g_szCCompiler		"cc"
#	define g_szCXXCompiler		"CC"
#   define g_szExeLinker        \
		"@CC $(LibDir) -o $(Product)\n" \
		g_szCheckLink
#   define g_szDllLinker        \
		"@CC -G -KPIC -O $(LibDir) -o $(Product)\n" \
		g_szCheckLink

#else
#	define g_szExportDefFile	"_export_.def"
#	define g_szExportDef		"-Wl,--version-script," g_szExportDefFile
#	define g_szCFlagsDef0		"-fPIC "
#	define g_szCCompiler		"gcc"
#	define g_szCXXCompiler		"g++"
#   define g_szExeLinker        \
		"@g++ $(LibDir) -o $(Product)\n" \
		g_szCheckLink
#   define g_szDllLinker        \
		"@g++ $(LibDir) -W1 -shared -o $(Product) " g_szExportDef "\n" \		g_szCheckLink
#endif

#if defined(__32BIT__) || defined(__x86_32__)
#	define g_szBitsType			"-D__32BIT__ "
#elif defined(__64BIT__) || defined(__x86_64__)
#	define g_szBitsType			"-D__64BIT__ "
#else
#	error "Unknown CPU Type!!!"
#endif

#if defined(__INTEL__)
#	define g_szCPUType			"-D__INTEL__ " g_szBitsType
#elif defined(__SPARC__)
#	define g_szCPUType			"-D__SPARC__ " g_szBitsType
#else
#	error "Unknown CPU Type!!!"
#endif

/* -------------------------------------------------------------------------
 [Config $(Config)]
	Product		$(ProdType) $(ProdPath)
	Options		{$(Option);}
	ObjDir		$(ObjDir)
	Libraries	{$(Lib);}
// -----------------------------------------------------------------------*/

#if defined(__WIN32__)
#	define g_szCFlagsDef		_T(g_szCFlagsDef0 g_szCPUType "-D__WIN32__ -D_WIN32 ")
#elif defined(__LINUX__)
// {{ ---------------------------> -fPIC 产生位置独立代码，可以在任意地址链接和加载
#	define g_szCFlagsDef		_T(g_szCFlagsDef0 g_szCPUType "-D__LINUX__ -DLINUX ")
#elif defined(__SOLS__)
#	define g_szCFlagsDef		_T(g_szCFlagsDef0 g_szCPUType "-D__SOLS__ -DSOLARIS ")
#else
#	error "Unknown Platform!!!"
#endif

enum KMG_ProdTypes
{
	mgProdTypeLib	= 0,
	mgProdTypeExe	= 1,
	mgProdTypeDll	= 2,
	mgProdTypeMax,
};

LPCTSTR g_szProdTypes[] =
{
	_T("Lib"),
	_T("Exe"),
	_T("Dll"),
};

LPCTSTR g_szLinkCommands[] =
{
	_T("@ar cr $(Product)"),
	g_szExeLinker,
	g_szDllLinker,
};

const TCHAR g_szNull[] = _T("");
const TCHAR g_szLib[]  = _T("lib");

// prefix, ext
LPCTSTR g_szProdTypeTrueNames[][2] =
{
	{ g_szLib,		_T(".a")	},
	{ g_szNull,		g_szNull	},
	{ g_szLib,		_T(".so")	},
};

enum KMG_Options
{
	mgOptRelease		= 0,
	mgOptUnicode		= 1,
	mgOptXChar			= 2,
	mgOptSingleThread	= 3,
	mgOptNoException	= 4,
	mgOptNoRtti			= 5,
	mgOptMax,
};

LPCTSTR g_szOptionsName[] =
{
	_T("Debug"),
	_T("Release"),
	_T("Unicode"),
	_T("XChar"),
	_T("MultiThread"),
	_T("Exception"),
	_T("NoException"),
	_T("Rtti"),
	_T("NoRtti"),
	_T("WarningAll"),
};

LPCTSTR g_szOptions[] =
{
	_T("-D_DEBUG -g3 "),
	_T("-DNDEBUG -O2 "),
	_T("-DUNICODE "),
	_T("-DXCHAR "),
	_T("-D_MT "),
	_T("-fexceptions "),
	_T("-fno-exceptions "),
	_T("-frtti "),
	_T("-fno-rtti "),
	_T("-Wall"),
};

int g_typeOptions[] =
{
    1, // Debug: C/C++
    1, // Release: C/C++
    1, // Unicode: C/C++
    1, // XChar: C/C++
    1, // MT: C/C++
    1, // Exception: C/C++
    1, // NoException: C/C++
    0, // Rtti: C++
    0, // NoRtti: C++
};

#define g_szConfigStartParam		\
	pParam->szSecParam, pParam->szSecParam
#define g_szConfigEndParam			\
	szProdDir, szObjDir, szProduct, pLocal->szCFlags, pLocal->szCppFlags, g_szLinkCommands[nProdType]

const TCHAR g_szConfigStartFmt[] =
_T(
	"#\n"
	"# Configuration %s\n"
	"#\n"
	"ifeq ($(CFG), %s)\n"
);

const TCHAR g_szConfigEndFmt[] =
_T(
	"	ProductDir   = %s\n"
	"	ObjectDir    = %s\n"
	"	MocFile      = $(ObjectDir)/temp.moc.cpp\n"
	"	Product      = %s\n"
	"	CFlags       = $(Defines) %s\n"
	"	CXXFlags     = $(CFlags) %s\n"
	"	CXX          = " g_szCXXCompiler " -c $(IncludeDir) $(CXXFlags) -o $@\n"
	"	CompileC     = @"  g_szCCompiler " -c $(IncludeDir) $(CFlags) -o $@ $<\n"
	"	CompileCXX   = @$(CXX) $<\n"
	"	CompileMoc   = @moc $< -o $(MocFile) && $(CXX) $(MocFile) && rm -f $(MocFile)\n"
	"	Link         = %s\n"
	"	LD_LIBRARY_PATH += :$(ProductDir)\n"
	"endif\n"
	"\n"
);

const TCHAR g_szLibrariesFmt[]	= _T("	Libraries   += -l%s\n");
const TCHAR g_szLibsFmt[]		= _T("	Libs        += %s\n");
const TCHAR g_szDefinesFmt[]	= _T("	Defines	    += -D%s\n");
const TCHAR g_szLibDirFmt[]		= _T("	LibDir	    += -L%s\n");

const TCHAR g_szSeps[] = _T(" \t\r\n");
const TCHAR g_szOptSeps[] = _T("; \t\r\n,");

STDMETHODIMP_(void) GetTrueProdName(LPTSTR szTrueName, LPCTSTR szName, UINT nProdType)
{
	if (nProdType >= mgProdTypeMax)
	{
		_tcscpy(szTrueName, szName);
		return;
	}
	LPCTSTR* pszTrueName = g_szProdTypeTrueNames[nProdType];

	TCHAR drive	[_MAX_DRIVE];
	TCHAR dir	[_MAX_DIR];
	TCHAR fname	[_MAX_FNAME];
	TCHAR ext   [_MAX_EXT];
	LPTSTR pfname = _tcsecpy(fname, pszTrueName[0]);
	_tsplitpath(szName, drive, dir, pfname, ext);
	if (*ext == 0)
		_tmakepath(szTrueName, drive, dir, fname, pszTrueName[1]);
	else
		_tcscpy(szTrueName, szName);
}
#define GetTrueLibName(szTrueName, szName)	GetTrueProdName(szTrueName, szName, mgProdTypeLib)

struct tagKHandleSec_ConfigLocal
{
	TCHAR szLine[MG_LINE_MAX];
	TCHAR szObjDir[_MAX_PATH];
	TCHAR szProduct[_MAX_PATH];
	TCHAR szLibFile[_MAX_PATH];
	TCHAR szCFlags[512];
    TCHAR szCppFlags[256];
	union
	{
		TCHAR szProdDir[_MAX_PATH];
		TCHAR szLibFileAbs[_MAX_PATH];
	};
};
typedef struct tagKHandleSec_ConfigLocal KHandleSec_ConfigLocal;

STDMETHODIMP GenerateExportDefFile(LPCTSTR szDestFile, LPCTSTR szSrcFile);

STDMETHODIMP HandleSec_Config(FILE* fpList, KHandlerParam* pParam)
{
	LPTSTR szLine;
	LPTSTR szObjDir;
	LPTSTR szProduct;
	LPTSTR szProdDir;
	LPTSTR szLibFileAbs;
	LPTSTR szLibFile;
	int    nProdType = -1;
	LPTSTR token;
	HRESULT hr = S_OK;
	KHandleSec_ConfigLocal* pLocal = NULL;
	LPTSTR pszCFlags;
    LPTSTR pszCppFlags;
	
	pLocal = (KHandleSec_ConfigLocal*)malloc(sizeof(KHandleSec_ConfigLocal));
	szLine = pLocal->szLine;
	szObjDir = pLocal->szObjDir;
	szProduct = pLocal->szProduct;
	szProdDir = pLocal->szProdDir;
	szLibFileAbs = pLocal->szLibFileAbs;
	szLibFile = pLocal->szLibFile;
	pszCFlags = _tcsecpy(pLocal->szCFlags, g_szCFlagsDef);
    pszCppFlags = pLocal->szCppFlags;
    pszCppFlags[0] = '\0';
	
	*szObjDir	= 0;
	*szProduct	= 0;
	if (pParam->szSecParam == NULL)
	{
		return E_CFGPARAM_ERROR;
	}
	if (pParam->szConfigReq && 
		_tcsicmp(pParam->szConfigReq, pParam->szSecParam) != 0)
	{
		return SkipSection(fpList, pParam);
	}
    //printf("Config: %s\n", pParam->szSecParam);
	_ftprintf(pParam->fpDest, g_szConfigStartFmt, g_szConfigStartParam);

	for (; GetSection(szLine, fpList, pParam) != S_OK;)
	{
		token = _tcstok(szLine, g_szSeps);
		if (token == NULL)
			continue;

		if (_tcsicmp(token, _T("Product")) == 0)
		{
			token = _tcstok(NULL, g_szSeps);	// szProdType
			if (token)
				nProdType = GetKeywordIndex(token, g_szProdTypes, countof(g_szProdTypes));
			token = _tcstok(NULL, g_szSeps);	// szProduct
			if (token)
				GetTrueProdName(szProduct, token, nProdType);
		}
		else if (_tcsicmp(token, _T("Options")) == 0)
		{
			for (;;)
			{
				token = _tcstok(NULL, g_szOptSeps);
				if (token == NULL)
					break;
				if (*token == '-')
				{
					pszCFlags = _tcsecpy(pszCFlags, token);
					*pszCFlags++ = ' ';
				}
				else
				{
					UINT iTemp = GetKeywordIndex(token, g_szOptionsName, countof(g_szOptions));
					if (iTemp != -1) {
                        switch (g_typeOptions[iTemp])
                        {
                        case 1: // C/C++
        					pszCFlags = _tcsecpy(pszCFlags, g_szOptions[iTemp]);
                            break;
                        default:
                            pszCppFlags = _tcsecpy(pszCppFlags, g_szOptions[iTemp]);
                        }
                    }
				}
			}
		}
		else if (_tcsicmp(token, _T("Libraries")) == 0 && nProdType != mgProdTypeLib)
		{
			for (;;)
			{
				token = _tcstok(NULL, g_szOptSeps);
				if (token == NULL)
					break;
				_ftprintf(pParam->fpDest, g_szLibrariesFmt, token);
				
				GetTrueLibName(szLibFile, token);
				TRACE("szLibFile = %s\n", szLibFile);
				if (
					pParam->fCheckDepency &&
					S_OK == SearchFilePath(
						szLibFileAbs, szLibFile,
						pParam->szLibDirs, pParam->nLibDirs,
						pParam->szProjPath)
					)
				{
					TRACE("Find Lib! szLibFileAbs = %s\n", szLibFileAbs);
					_ftprintf(pParam->fpDest, g_szLibsFmt, szLibFileAbs);
				}
			}
		}
		else if (_tcsicmp(token, _T("LibDir")) == 0)
		{
			for (;;)
			{
				token = _tcstok(NULL, g_szOptSeps);
				if (token == NULL)
					break;
				_ftprintf(pParam->fpDest, g_szLibDirFmt, token);
			}
		}
		else if (_tcsicmp(token, _T("Defines")) == 0)
		{
			for (;;)
			{
				token = _tcstok(NULL, g_szOptSeps);
				if (token == NULL)
					break;
				_ftprintf(pParam->fpDest, g_szDefinesFmt, token);
			}
		}
		else if (_tcsicmp(token, _T("ObjDir")) == 0)
		{
			token = _tcstok(NULL, g_szSeps);
			if (token)
				_tcscpy(szObjDir, token);
		}
	}

	// Validate:
	if (*szProduct == 0)
	{
		hr = E_PRODUCT_ERROR;
		goto lzExit;
	}
	RemovePathSep(szObjDir);
	if (*szObjDir == 0)
	{
		hr = E_OBJDIR_ERROR;
		goto lzExit;
	}
	if (nProdType == -1)
	{
		hr = E_PRODTYPE_ERROR;
		goto lzExit;
	}
	else if (nProdType == mgProdTypeDll)
	{
		class __Execute // 为了防止栈溢出，采用new方式
		{
		protected:
			TCHAR szDestDefFile[_MAX_PATH];
			TCHAR szSrcDefFile[_MAX_PATH];
			TCHAR szCmd[1024];

		public:
			STDMETHODIMP Exec(LPCTSTR szProjPath)
			{
				//_tprintf(_T("szProjPath = %s!\n"), szProjPath);
				
				GenDefaultFile(szSrcDefFile, szProjPath, _T(".def"));
				if (!IsFileExist2(szSrcDefFile))
				{
					_tprintf(_T("Error: Can't Open %s!\n"), szSrcDefFile);
					return E_FAIL;
				}
				MergePath(szDestDefFile,  szProjPath, g_szExportDefFile);
				return GenerateExportDefFile(szDestDefFile, szSrcDefFile);
			}
		};
		__Execute* pExecute = new __Execute;
		hr = pExecute->Exec(pParam->szProjPath);
		delete pExecute;
	}

	// Configuration:
	SplitPath2(szProduct, szProdDir, NULL);
	RemovePathSep(szProdDir);
	_ftprintf(pParam->fpDest, g_szConfigEndFmt, g_szConfigEndParam);

lzExit:
	if (pLocal)
		free(pLocal);
	return hr;
}

// -------------------------------------------------------------------------

TCHAR g_szExportDefContentBegin[] = 
_T(
	"EXPORTED {\n"
	"global:\n"
);

TCHAR g_szExportDefContentEnd[] =
_T(
	"local: *;\n"
	"};\n"
);

STDMETHODIMP GenerateExportDefFile(LPCTSTR szDestFile, LPCTSTR szSrcFile)
{
	TRACE("Generating ExportDefFile %s...\n", szDestFile);
	TRACE("szSrcDefFile = %s\n", szSrcFile);

	FILE* fpSrc = _tfopen(szSrcFile, _T("r"));
	FILE* fpDest = _tfopen(szDestFile, _T("w"));
	if (fpDest == NULL)
	{
		_tprintf(_T("Error: Create ExportDefFile %s Error!\n"), szDestFile);
		if (fpSrc)
			fclose(fpSrc);
		return E_FAIL;
	}
	_ftprintf(fpDest, g_szExportDefContentBegin);
	if (fpSrc == NULL)
	{
		_ftprintf(fpDest, _T("\t*;\n"));
		_ftprintf(fpDest, g_szExportDefContentEnd);
		fclose(fpDest);
		return S_OK;
	}
	
	BOOL fInExportSection = FALSE;
	LPTSTR token;
	TCHAR* szLine = new TCHAR[MG_LINE_MAX];
	for (;;)
	{
		*szLine = 0;
		_fgetts(szLine, MG_LINE_MAX, fpSrc);
		if (*szLine == 0 && feof(fpSrc))
			break;

		token = _tcstok(szLine, g_szSeps);
		if (token == NULL || *token == ';' )
			continue;
		
		if (!fInExportSection)
		{
			if (_tcscmp(token, "EXPORTS") == 0)
				fInExportSection = TRUE;
		}
		else
		{
			_ftprintf(fpDest, _T("\t%s;\n"), token);
		}
	}
	_ftprintf(fpDest, g_szExportDefContentEnd);
	
	delete[] szLine;
	fclose(fpDest);
	fclose(fpSrc);
	return S_OK;
}

// -------------------------------------------------------------------------
