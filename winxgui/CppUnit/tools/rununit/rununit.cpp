// rununit.cpp : Defines the entry point for the console application.
// $Id: rununit.cpp,v 1.8 2007/02/26 02:16:35 wangdong Exp $
//

#include "stdafx.h"
#include <fstream>
#include <direct.h>

/*
void _AddUnits(LPCSTR argv)
{
	char ext[_MAX_EXT];
	_splitpath(argv, NULL, NULL, NULL, ext);
	if (stricmp(ext, ".dll") == 0)
		LoadLibrary(argv);
	else if (stricmp(ext, ".units") == 0)
	{
		std::ifstream fin(argv);
		if (fin.good())
		{
			for (;;)
			{
				std::string strDll;
				std::getline(fin, strDll);
				if (
					strDll.empty() ||
					strchr(" \t\r\n", strDll[0]) != 0)
				{
					break;
				}
				LoadLibrary(strDll.c_str());
			}
		}
	}
}

int main()
{
	USES_CONVERSION;
	if (__argc > 1)
	{
		_XInitCppUnitEnv();
		_CppUnit_Initialize(_TestAppType);
		_AddUnits(W2A(__wargv[1]));
		HRESULT hr = _CppUnit_RunAllTests(__argc, __wargv);
		_CppUnit_Terminate();
		if (FAILED(hr))
			getchar();
	}
	return 0;
}
*/

//
// rununit.exe testcase[.dll] [testclass] [testmethod] [/ndebug] [/pause] [/output:<xmlfile>]
// 其中，/ndebug /output:<xmlfile>是通用开关，由cppunit完成的。参考：
//		STDAPI _CppUnit_RunAllTests(
//			IN int argc,
//			IN WCHAR** argv);
//		STDAPI_(BOOL) _CppUnit_IsDebugMode();
//
int main()
{
	USES_CONVERSION;

	BOOL fPause = FALSE;
	LPCWSTR szModule = NULL;
	LPCSTR szClass = NULL;
	LPCSTR szMethod = NULL;
	UINT idxArg = 0;
	LPCWSTR targetModule = NULL;

	for (int i = 1; i < __argc; ++i)
	{
		if (__wargv[i][0] == '/' || __wargv[i][0] == '-')
		{
			switch (tolower(__wargv[i][1]))
			{
			case 'p':
				fPause = TRUE;
				break;
			case 'm':
				targetModule = __wargv[++i];
				break;
			}
		}
		else
		{
			switch (idxArg)
			{
			case 0:	szModule = __wargv[i]; break;
			case 1: szClass = W2A(__wargv[i]); break;
			case 2: szMethod = W2A(__wargv[i]); break;
			}
			++idxArg;
		}
	}
	if (idxArg > 0)
	{
		TestApp app(rununitConsole);
		HRESULT hr = app.AddUnit(szModule);
		if (FAILED(hr))
		{
			printf("load %s failed!!!", W2A(szModule));
			return -1;
		}
		LPCWSTR szModuleName = wcsrchr(szModule, '\\');
		if (szModuleName)
			++szModuleName;
		else
		{
			szModuleName = wcsrchr(szModule, '/');
			if (szModuleName)
				++szModuleName;
			else
				szModuleName = szModule;
		}
		if (targetModule)
			_CppUnit_FilterCase(targetModule, szClass, szMethod);
		else
			_CppUnit_FilterCase(szModuleName, szClass, szMethod);
	}
	if (fPause)
	{
		getchar();
	}
	return 0;
}

// $Log: rununit.cpp,v $
// Revision 1.8  2007/02/26 02:16:35  wangdong
// *** empty log message ***
//
// Revision 1.7  2005/03/24 10:03:21  xushiwei
// 去除/debug开关。rununit默认改为debug状态，除非使用了通用开关/ndebug。
//
// Revision 1.6  2005/03/15 03:35:46  xushiwei
// 1、_CppUnit_RunAllTests - 增加/run:<testclass>.<testmethod>参数支持。
// 2、_CppUnit_FilterCase - 支持修改部分Filter参数。
// 3、_CppUnit_Initialize参数改为EnumRunUnitType runtype。
//
// Revision 1.5  2005/03/03 04:53:31  xushiwei
// 增加/pause参数。
//
// Revision 1.4  2005/03/03 04:02:30  xushiwei
// 修改传入_CppUnit_FilterCase的module名，改全路径为非全路径。
//
// Revision 1.3  2005/01/21 02:01:07  xushiwei
// TestApp::AddUnit返回值由void改为HRESULT。
//
