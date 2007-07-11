// rununit.cpp : Defines the entry point for the console application.
// $Id: rununit.cpp,v 1.8 2007/02/26 02:16:35 wangdong Exp $
//

#include "stdafx.h"
#include <fstream>
#include <direct.h>

//
// rununit.exe testcase[.dll] [testclass] [testmethod] [/ndebug] [/pause] [/output:<xmlfile>]
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
		getchar();
	}
	return 0;
}

// -------------------------------------------------------------------------
// $Log: rununit.cpp,v $
// Revision 1.7  2005/03/24 10:03:21  xushiwei
// ȥ��/debug���ء�rununitĬ�ϸ�Ϊdebug״̬������ʹ����ͨ�ÿ���/ndebug��
//
// Revision 1.6  2005/03/15 03:35:46  xushiwei
// 1��_CppUnit_RunAllTests - ����/run:<testclass>.<testmethod>����֧�֡�
// 2��_CppUnit_FilterCase - ֧���޸Ĳ���Filter������
// 3��_CppUnit_Initialize������ΪEnumRunUnitType runtype��
//
// Revision 1.5  2005/03/03 04:53:31  xushiwei
// ����/pause������
//
// Revision 1.4  2005/03/03 04:02:30  xushiwei
// �޸Ĵ���_CppUnit_FilterCase��module������ȫ·��Ϊ��ȫ·����
//
// Revision 1.3  2005/01/21 02:01:07  xushiwei
// TestApp::AddUnit����ֵ��void��ΪHRESULT��
//
