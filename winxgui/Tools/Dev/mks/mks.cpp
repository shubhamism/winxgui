// -------------------------------------------------------------------------
//	文件名		：	mks.cpp
//	创建者		：	许式伟
//	创建时间	：	2002-1-24 16:38:34
//	功能描述	：	
//
// -------------------------------------------------------------------------

#include "stdafx.h"
#undef	__Linked_KSCommon
#include "ksx_common.h"
#include "ks_dir.h"
#include "ks_fileutils.h"

// -------------------------------------------------------------------------

#define MG_CMDLINE_MAX		4096
#define MG_LINE_MAX			2048

const TCHAR g_szSeps[] = _T(" \t\r\n");

// -------------------------------------------------------------------------

struct KFileExtAssoc
{
	LPCTSTR	szExt;
	LPCTSTR szCommand;
};

KFileExtAssoc g_fileAss[] =
{
	{ _T(".prj"),	_T("mk")	},
	{ _T(".plf"),	_T("mks")	},
};

STDMETHODIMP MakeProjects(FILE* fpPlf, LPCTSTR szPlfpath, char* argv[], int argc)
{
	int i, j;
	LPTSTR psz;
	LPTSTR token;
	static TCHAR command[MG_CMDLINE_MAX];
	static TCHAR szLine[MG_LINE_MAX];
	static TCHAR szExt[_MAX_EXT];

	for (;;)
	{
		*szLine = 0;
		_fgetts(szLine, MG_LINE_MAX, fpPlf);
		if (*szLine == 0)
		{
			if (feof(fpPlf))
			{
				return S_OK;
			}
		}
		else
		{
			token = _tcstok(szLine, g_szSeps);
			if (token == NULL)
				continue;
			
			SplitPath(token, NULL, NULL, NULL, szExt);
			for (i = 0; i < countof(g_fileAss); ++i)
			{
				if (_tcsicmp(g_fileAss[i].szExt, szExt) == 0)
					break;
			}
			if (i >= countof(g_fileAss))
				i = 0;

			psz = _tcsecpy(command, g_fileAss[i].szCommand);
			*psz++ = ' ';
			psz = _tcsecpy(psz, token);
			*psz++ = ' ';
			for (j = 0; j < argc; ++j)
			{
				psz = _tcsecpy(psz, argv[j]);
				*psz++ = ' ';
			}
			*psz = 0;
			
			TRACE("command = %s\n", command);
			ksChDir(szPlfpath);
			system(command);
		}
	}
}

// -------------------------------------------------------------------------

const TCHAR g_szExtPlf[] = _T(".plf");

int main(int argc, char* argv[])
{
	static TCHAR szPlfFile[_MAX_PATH] = _T("projects.plf");
	static TCHAR szCurDir[_MAX_PATH];
	static TCHAR szPlfpath[_MAX_PATH];
	BOOL fSpecifiedPlffile = FALSE;
	FILE* fpPlf;
	int i;
	
	ksGetCwd(szCurDir, _MAX_PATH);
	TRACE("CurDir = %s\n", szCurDir);
	
	// 1). analyze switchs
	++argv; --argc;
	for (i = 0; i < argc; ++i)
	{
		if (*argv[i] != '-' && !fSpecifiedPlffile)
		{
			fSpecifiedPlffile = TRUE;
			_tcscpy(szPlfFile, argv[i]);
			GuessExt(szPlfFile, g_szExtPlf);
			continue;
		}
		if (fSpecifiedPlffile)
		{
			argv[i-1] = argv[i];
		}
	}

	// 2). get plffile specified
	if (!fSpecifiedPlffile)
	{
		if (
			!IsFileExist(szPlfFile) &&
				(
				GenDefaultFile(szPlfFile, szCurDir, g_szExtPlf) != S_OK ||
				!IsFileExist(szPlfFile)
				)
			)
		{
			{
				puts(
					"Function: to make projects by project list file(Plffile)\n"
					"Usage: mks [-c -r] Plffile[.plf] Config\n"
					"  -c   to clean & build, that is, to rebuild\n"
					"  -r   set Config=Release, if Config is not specified\n"
					);
				return -1;
			}
		}
	}
	else
	{
		--argc;
	}
	TRACE("PlfFile = %s\n", szPlfFile);
	
	// 3). make projects by szPlffile
	
	// 3.1) open szPlffile
	fpPlf = _tfopen(szPlfFile, _T("r"));
	if (fpPlf == NULL)
	{
		return -1;
	}

	// 3.2) get Plfpath
	MergePath(szPlfpath, szCurDir, szPlfFile);
	*_tcsrchr(szPlfpath, '/') = 0;
	TRACE("Plfpath = %s\n", szPlfpath);

	// 3.3) make it!
	MakeProjects(fpPlf, szPlfpath, argv, argc);
	fclose(fpPlf);
	ksChDir(szCurDir);

	return 0;
}

// -------------------------------------------------------------------------
