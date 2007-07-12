// rununit.cpp : Defines the entry point for the console application.
// $Id: rununit.cpp,v 1.8 2007/02/26 02:16:35 wangdong Exp $
//

#include "stdafx.h"
#include <fstream>
#include <direct.h>

//
// === command line ===
//
//	rununit.exe TestCases[.dll] [TestCaseClass] [testMethod]
//		TestCases.dll - A dll with some TestCases.
//		TestCaseClass - Specify which TestCaseClass to be tested. 
//						If not specified, all test cases within the TestCases.dll will be tested.
//		testMethod - Specify which testMethod to be tested.
//					 If not specified, all test methods within TestCaseClass will be tested.
//	
// === switch ===
//
//	/ndebug - Specify to run test cases in non-debug mode. 
//		In default condition, rununit.exe is running in debug mode, not in auto test scripts.
//		In debug mode, if some test cases are failed, AssertDialogs will be shown to indicate 
//		the errors.	But you can specify switch /ndebug to run in non-debug mode. In this case,
//		All the user interfaces with interaction, AssertDialogs for example, will be omitted.
//		As substitute, some error information will be printed to console(stderr), or to an
//		logfile with XML format.
//
//	/output:<xmlfile> - Specify to print error information to an XML logfile. If the xmlfile
//		exists, the orginal content error information will be appended to the end of file.
//		In default condition, rununit.exe prints error information to console(stderr) in 
//		non-debug mode. But you can specify switch /output:<xmlfile> to redirect.
//		Note: there are no whitespaces between '/output:' and the xml file name.
//
//	/pause - Pause when rununit.exe have run all test cases, and wait the user press ENTER key.
//
int wmain(int argc, const wchar_t* argv[])
{
	USES_CONVERSION;

	BOOL fPause = FALSE;
	LPCWSTR szModule = NULL;
	LPCSTR szClass = NULL;
	LPCSTR szMethod = NULL;
	UINT idxArg = 0;
	LPCWSTR targetModule = NULL;

	for (int i = 1; i < argc; ++i)
	{
		if (argv[i][0] == '/' || argv[i][0] == '-')
		{
			switch (tolower(argv[i][1]))
			{
			case 'p':
				fPause = TRUE;
				break;
			case 'm':
				targetModule = argv[++i];
				break;
			}
		}
		else
		{
			switch (idxArg)
			{
			case 0:	szModule = argv[i]; break;
			case 1: szClass = W2A(argv[i]); break;
			case 2: szMethod = W2A(argv[i]); break;
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
		printf("\nPress ENTER key to continue ...");
		getchar();
	}
	return 0;
}

// -------------------------------------------------------------------------
// $Log: rununit.cpp,v $
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
