/* -------------------------------------------------------------------------
//	�ļ���		��	run.cpp
//	������		��	��ʽΰ
//	����ʱ��	��	2003-11-7 20:34:55
//	��������	��	
//
//	$Id: run.cpp,v 1.11 2007/05/22 07:35:06 xuehua Exp $
// -----------------------------------------------------------------------*/

#include "stdafx.h"
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>

#include <fstream>
#include <algorithm>

#define rununitNone 0

static enum EnumRunUnitType _g_runtype;

inline STDMETHODIMP_(LPCWSTR) _CppUnit_ModuleFilterName(
														IN LPCWSTR szModule
														)
{
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
	wcslwr(const_cast<LPWSTR>(szModuleName));
	return szModuleName;
}

// -------------------------------------------------------------------------

typedef void (*FnInitializeProc)();
typedef void (*FnTerminateProc)();
typedef std::pair<FnInitializeProc, FnTerminateProc> RegisterProcedureParams;

std::vector<RegisterProcedureParams> _g_regProcs;

class _RunInitializeProc
{
public:
	operator()(const RegisterProcedureParams& rhs) const
	{
		rhs.first();
	}
};

class _RunTerminateProc
{
public:
	operator()(const RegisterProcedureParams& rhs) const
	{
		rhs.second();
	}
};

EXPORTAPI _CppUnit_RegisterProcedure(
									 IN FnInitializeProc fnInit,
									 IN FnTerminateProc fnTerm
									 )
{
	_g_regProcs.push_back(
		RegisterProcedureParams(fnInit, fnTerm)
		);
	return S_OK;
}

const WCHAR _g_outputsw[] = { 'o', 'u', 't', 'p', 'u', 't', ':' };
const WCHAR _g_runsw[] = { 'r', 'u', 'n', ':' };

#ifndef CPPUNIT_NOFILTER_MODULE
#define CPPUNIT_NOFILTER_MODULE			((LPCWSTR)1)
#define CPPUNIT_NOFILTER_TESTCLASS		((LPSTR)1)
#define CPPUNIT_NOFILTER_TESTMETHOD		((LPSTR)1)
#endif

STDAPI_(void) _CppUnit_FilterCase(
								  IN LPCWSTR szModuleName,
								  IN LPCSTR szTestClass,
								  IN LPCSTR szTestMethod
								  );

//
// <== switch table ==>
//		/output:<filename> �����xml�ļ���ע�⣺/output:�����пո�
//		/run:<testclass>.<testmethod> ִ��<testclass>�࣬<testmethod>������
//
EXPORTAPI _CppUnit_RunAllTests(
							   IN int argc,
							   IN WCHAR** wargv
							   )
{
	USES_CONVERSION;

	LPCWSTR pwszFileName = NULL;

	if (wargv != NULL)
	{
		LPCWSTR pwszModule = CPPUNIT_NOFILTER_MODULE;
		LPSTR pszTestClass = CPPUNIT_NOFILTER_TESTCLASS;
		LPSTR pszTestMethod = CPPUNIT_NOFILTER_TESTMETHOD;
		for (int i = 1; i < argc; ++i)
		{
			if (wargv[i][0] == '/' || wargv[i][0] == '-')
			{
				if (wcsnicmp(wargv[i]+1, _g_outputsw, countof(_g_outputsw)) == 0)
				{
					pwszFileName = wargv[i] + (1 + countof(_g_outputsw)); // ���Խ���ļ�
				}
				else if (wcsnicmp(wargv[i]+1, _g_runsw, countof(_g_runsw)) == 0)
				{
					LPCWSTR pwszRunParam = wargv[i] + (1 + countof(_g_runsw));
					pszTestClass = W2A(pwszRunParam);
					pszTestMethod = strchr(pszTestClass, '.');
					if (pszTestMethod)
						*pszTestMethod++ = '\0';
				}
			}
		}
		if (_g_runtype == rununitNone)
		{
			pwszModule = _CppUnit_ModuleFilterName(wargv[0]);
		}

		_CppUnit_FilterCase(pwszModule, pszTestClass, pszTestMethod);
	}

	// ��������
	CPPUNIT_NS::Test *suite = CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest();
	CPPUNIT_NS::TextUi::TestRunner runner;
	runner.addTest( suite );
	
	CPPUNIT_NS::Outputter* outputter = NULL;
	std::ofstream outfile;
	if (pwszFileName)
		outfile.open(W2A(pwszFileName), std::ios::out | std::ios::app);
	if (outfile.is_open())
		outputter = new CPPUNIT_NS::XmlOutputter(&runner.result(), outfile);
	else
		outputter = new CPPUNIT_NS::CompilerOutputter(&runner.result(), std::cerr);

	runner.setOutputter(outputter);
	
	try {
		std::for_each(
			_g_regProcs.begin(),
			_g_regProcs.end(),
			_RunInitializeProc());
	}
	catch (...) {
		if (outfile.is_open()) {
			outfile << "<Exception_In__RunInitializeProc/>" << std::endl;
		}
		else {
			std::cerr << " Caught an exception in _RunInitializeProc()!" << std::endl;
		}
		return E_FAIL;
	}

	bool wasSucessful = runner.run();
	
	try {
		std::for_each(
			_g_regProcs.rbegin(),
			_g_regProcs.rend(),
			_RunTerminateProc());
	}
	catch (...) {
		if (outfile.is_open()) {
			outfile << "<Exception_In__RunTerminateProc/>" << std::endl;
		}
		else {
			std::cerr << " Caught an exception in _RunTerminateProc()!" << std::endl;
		}
		return E_FAIL;
	}

	return wasSucessful ? S_OK : E_FAIL;
}

EXPORTAPI _CppUnit_RunAllTests_ByName(
							   IN int argc,
							   IN WCHAR** wargv,
							   IN const std::string& strName)
{
	USES_CONVERSION;
	
	LPCWSTR pwszFileName = NULL;
	
	if (wargv != NULL)
	{
		LPCWSTR pwszModule = CPPUNIT_NOFILTER_MODULE;
		LPSTR pszTestClass = CPPUNIT_NOFILTER_TESTCLASS;
		LPSTR pszTestMethod = CPPUNIT_NOFILTER_TESTMETHOD;
		for (int i = 1; i < argc; ++i)
		{
			if (wargv[i][0] == '/' || wargv[i][0] == '-')
			{
				if (wcsnicmp(wargv[i]+1, _g_outputsw, countof(_g_outputsw)) == 0)
				{
					pwszFileName = wargv[i] + (1 + countof(_g_outputsw)); // ���Խ���ļ�
				}
				else if (wcsnicmp(wargv[i]+1, _g_runsw, countof(_g_runsw)) == 0)
				{
					LPCWSTR pwszRunParam = wargv[i] + (1 + countof(_g_runsw));
					pszTestClass = W2A(pwszRunParam);
					pszTestMethod = strchr(pszTestClass, '.');
					if (pszTestMethod)
						*pszTestMethod++ = '\0';
				}
			}
		}
		if (_g_runtype == rununitNone)
		{
			pwszModule = _CppUnit_ModuleFilterName(wargv[0]);
		}
		
		_CppUnit_FilterCase(pwszModule, pszTestClass, pszTestMethod);
	}
	
	// ��������
	CPPUNIT_NS::Test *suite = CPPUNIT_NS::TestFactoryRegistry::getRegistry(strName).makeTest();
	CPPUNIT_NS::TextUi::TestRunner runner;
	runner.addTest( suite );
	
	CPPUNIT_NS::Outputter* outputter = NULL;
	std::ofstream outfile;
	if (pwszFileName)
		outfile.open(W2A(pwszFileName), std::ios::out | std::ios::app);
	if (outfile.is_open())
		outputter = new CPPUNIT_NS::XmlOutputter(&runner.result(), outfile);
	else
		outputter = new CPPUNIT_NS::CompilerOutputter(&runner.result(), std::cerr);
	
	runner.setOutputter(outputter);
	
	try {
		std::for_each(
			_g_regProcs.begin(),
			_g_regProcs.end(),
			_RunInitializeProc());
	}
	catch (...) {
		if (outfile.is_open()) {
			outfile << "<Exception_In__RunInitializeProc/>" << std::endl;
		}
		else {
			std::cerr << " Caught an exception in _RunInitializeProc()!" << std::endl;
		}
		return E_FAIL;
	}
	
	bool wasSucessful = runner.run();
	
	try {
		std::for_each(
			_g_regProcs.rbegin(),
			_g_regProcs.rend(),
			_RunTerminateProc());
	}
	catch (...) {
		if (outfile.is_open()) {
			outfile << "<Exception_In__RunTerminateProc/>" << std::endl;
		}
		else {
			std::cerr << " Caught an exception in _RunTerminateProc()!" << std::endl;
		}
		return E_FAIL;
	}
	
	return wasSucessful ? S_OK : E_FAIL;
}

// -------------------------------------------------------------------------

EXPORTAPI _CppUnit_Initialize(EnumRunUnitType runtype)
{
	_g_runtype = runtype;
	return S_OK;
}

EXPORTAPI_(void) _CppUnit_Terminate()
{
}

// -------------------------------------------------------------------------
// $Log: run.cpp,v $
// Revision 1.11  2007/05/22 07:35:06  xuehua
// *** empty log message ***
//
// Revision 1.10  2005/10/28 09:08:11  zhuyie
// ץסģ��Init���̺�Term�����е��쳣��
//
// Revision 1.9  2005/10/28 02:45:06  xushiwei
// cppunit���벻��
//
// Revision 1.8  2005/10/27 02:01:55  xushiwei
// cppunit����DebugBreak��
//
// Revision 1.7  2005/03/25 03:25:35  xushiwei
// _CppUnit_RunAllTests֧�ִ���wargvΪNULL�������
// ��������������û�ֻʹ��cppunit������ʹ��kfcʱ����Ҫ�����ݴ�
//
// Revision 1.6  2005/03/15 03:33:36  xushiwei
// 1��_CppUnit_RunAllTests - ����/run:<testclass>.<testmethod>����֧�֡�
// 2��_CppUnit_FilterCase - ֧���޸Ĳ���Filter������
//
// Revision 1.5  2005/03/10 03:56:16  xushiwei
// ���ǵ��ж��dll������_CppUnit_RegisterProcedure���������RegisterProcedure����vector���档
//
// Revision 1.4  2005/03/10 03:32:28  xushiwei
// ����_CppUnit_RegisterProcedure��
//
// Revision 1.3  2005/03/04 09:12:54  xushiwei
// ����/output:ͨ�ÿ���֧�֡�
//
