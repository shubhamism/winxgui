// -------------------------------------------------------------------------
//	文件名		：	mk.cpp
//	创建者		：	许式伟
//	创建时间	：	2002-1-24 16:38:34
//	功能描述	：	
//
// -------------------------------------------------------------------------

#define _ENABLE_TRACE
#include "stdafx.h"
#undef	__Linked_KSCommon
#include "ksx_common.h"
#include "ks_dir.h"
#include "ks_fileutils.h"
#include <stdlib.h>

// -------------------------------------------------------------------------

enum KEnumSwitchs
{
	switchClean		= 0x0001,
	switchRelease	= 0x0002,
	switchListCfg	= 0x0004,
	switchForceLink = 0x0008,
};

// -c	clean
// -r	release
// -l	listcfg
// -f	force to link
TCHAR g_sws[] = _T("crlfh?");

// -------------------------------------------------------------------------

const TCHAR g_szExtMak[] = _T(".temp.mak");
const TCHAR g_szExtPrj[] = _T(".prj");

int main(int argc, char* argv[])
{
	static TCHAR command[2048];
	static TCHAR szMakeFile[_MAX_PATH];
	static TCHAR szPrjFile[_MAX_PATH];
	static TCHAR szCurDir[_MAX_PATH];
	static TCHAR szProjPath[_MAX_PATH];
	static TCHAR szProjName[_MAX_FNAME];
	SWITCHS sw;
	LPCTSTR szCfg;
	LPTSTR  pszMakeFileName;
	
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
		if (
			GenDefaultFile(szPrjFile, szCurDir, g_szExtPrj) != S_OK ||
			!IsFileExist2(szPrjFile)
			)
		{
lzPrompt:	puts(
				"Function: to make a project by Prjfile\n"
				"Usage: mk [-c -r -f] Prjfile[.prj] Config\n"
				"  -c    to clean & build, that is, to rebuild\n"
				"  -r    set $(CFG)=Release, if Config is not specified\n"
				"  -f    force to link\n"
				);
			return -1;
		}
	}
	else
	{
		_tcscpy(szPrjFile, argv[0]);
	}
	TRACE("PrjFile = %s\n", szPrjFile);
	
	// 3). get config-request:
	if      (argc > 1)				szCfg = argv[1];
	else if	(sw & switchListCfg)	szCfg = _T("-l");
	else if (sw & switchRelease)	szCfg = _T("Release");
	else							szCfg = _T("Debug");

	// 4). call MakeGen(mg) to generate makefile
	ForceExt(szMakeFile, szPrjFile, g_szExtMak);
	TRACE("MakeFile = %s\n", szMakeFile);
	_stprintf(command, _T("mg %s %s %s"), szPrjFile, szMakeFile, szCfg);
	system(command);
	
	// 5). make

	// 5.1) set current dir to be makefile's path!
	MergePath(szProjPath, szCurDir, szMakeFile);
	TRACE("MakeFileAbs = %s\n", szProjPath);
	pszMakeFileName = _tcsrchr(szProjPath, '/');
	*pszMakeFileName++ = 0;
	TRACE("ProjPath = %s, MakeFileName = %s\n", szProjPath, pszMakeFileName);
	ksChDir(szProjPath);

	// 5.2) make it!
	LPCTSTR szForceLink = sw & switchForceLink ? _T(" ForceLink=1") : _T("");
	LPCTSTR szBuild = sw & switchClean ? _T("clean all") : _T("");
	UINT iFind = _tcschr(pszMakeFileName, '.') - pszMakeFileName;
	_tcsncpy(szProjName, pszMakeFileName, iFind);
	szProjName[iFind] = 0;

	_stprintf(command, _T("make -f %s %s%s PROJ=%s"), 
		pszMakeFileName, szBuild, szForceLink, szProjName);
	TRACE("%s\n", command);
	system(command);
	remove(pszMakeFileName);

	// 5.3). restore current dir!
	ksChDir(szCurDir);
	
	return 0;
}

// -------------------------------------------------------------------------
