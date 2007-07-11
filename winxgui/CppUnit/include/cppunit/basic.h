/* -------------------------------------------------------------------------
//	文件名		：	cppunit/basic.h
//	创建者		：	许式伟
//	创建时间	：	2003-11-8 0:45:03
//	功能描述	：	
//
//	$Id: basic.h,v 1.24 2007/05/22 07:35:08 xuehua Exp $
// -----------------------------------------------------------------------*/
#ifndef __CPPUNIT_BASIC_H__
#define __CPPUNIT_BASIC_H__

// -------------------------------------------------------------------------

#ifndef __CPPUNIT_PLATAPI_H__
#include "platapi.h"
#endif

// -------------------------------------------------------------------------
/*@@delete

#ifndef __KFC_PLATFORM_H__
#include <kfc/platform.h>
#endif

#if defined(X_APPTYPE_CONSOLE)
#define _TestAppType	AppTypeConsole

#elif defined(X_APPTYPE_WINDOWS)
#define _TestAppType	AppTypeWindow

#elif defined(X_APPTYPE_DLL)
#define _TestAppType	AppTypeDynLib

#else
#define _TestAppType	AppTypeUnknown
#endif
*/

// -------------------------------------------------------------------------
// 通用开关 /ndebug 的检测

inline BOOL _CppUnit_IsDebugMode()
{
	const WCHAR _g_ndebugsw[] = { 'n', 'd', 'e', 'b', 'u', 'g', '\0' };
	
	for (int i = 1; i < __argc; ++i)
	{
		if (__wargv[i][0] == '/' || __wargv[i][0] == '-')
		{
			if (wcsicmp(__wargv[i]+1, _g_ndebugsw) == 0)
				return FALSE;
		}
	}

	// 默认是debug模式。
	return TRUE;
}

// -------------------------------------------------------------------------

#if defined(_KFC)
#define _CppUnit_InitEnv()			_XInitCppUnitEnv()
#define _CppUnit_GetModuleName()	_XGetModuleName()
#else
#define _CppUnit_InitEnv()			NULL
#define _CppUnit_GetModuleName()	NULL
#endif

// -------------------------------------------------------------------------

template <class TestFixtureType>
class TestFixtureCreator
{
public:
	static void makeFixture(TestFixture** ppv)
	{
		*ppv = new TestFixtureType();
	}
};

template <class TestFixtureType>
class AutoRegisterTestSuite
{
private:
	TestFactory* m_factory;

public:
	AutoRegisterTestSuite()
	{	// TestFixtureType::suite是一个创建suite的函数指针，被m_factory保存并被其makeTest（）函数利用
		_CppUnit_CreateTestSuiteFactory(TestFixtureType::suite, &m_factory);
		_CppUnit_RegisterFactory1(m_factory);
	}
	~AutoRegisterTestSuite()
	{
		_CppUnit_UnregisterFactory1(m_factory);
		_CppUnit_DeleteTestSuiteFactory(m_factory);
	}
};

// -------------------------------------------------------------------------

#define _CppUnit_Abort()	0

class TestApp
{
public:
	TestApp(EnumRunUnitType runtype = rununitNone)
	{
		if (!_CppUnit_IsDebugMode())
			_CppUnit_InitEnv();
		_CppUnit_Initialize(runtype);
		_CppUnit_FilterCase(_CppUnit_GetModuleName(), NULL, NULL);
	}
	TestApp(BOOL fInitCppUnitEnv, EnumRunUnitType runtype = rununitNone)
	{
		if (fInitCppUnitEnv)
			_CppUnit_InitEnv();
		_CppUnit_Initialize(runtype);
		_CppUnit_FilterCase(_CppUnit_GetModuleName(), NULL, NULL);
	}
	~TestApp()
	{
		try
		{
			_CppUnit_RunAllTests(__argc, __wargv);
		}
		catch (...)
		{
			_CppUnit_Abort();
		}
		_CppUnit_Terminate();
	}

	static HRESULT AddUnit(
		LPCSTR szDll)
	{
		return LoadLibraryA(szDll) ? S_OK : E_ACCESSDENIED;
	}

	static HRESULT AddUnit(
		LPCWSTR szDll)
	{		
		USES_CONVERSION;
		return LoadLibraryA(W2A(szDll)) ? S_OK : E_ACCESSDENIED;
	}
};

template <class TestFixtureType>
class AutoRegisterTestSuite_ByName
{
private:
	TestFactory* m_factory;
	
public:
	AutoRegisterTestSuite_ByName(const char* strName) : m_strName(strName)
	{	
		// TestFixtureType::suite是一个创建suite的函数指针，被m_factory保存并被其makeTest（）函数利用
		_CppUnit_CreateTestSuiteFactory(TestFixtureType::suite, &m_factory);
		_CppUnit_RegisterFactory_ByName(m_factory, m_strName);
	}
	~AutoRegisterTestSuite_ByName()
	{
		_CppUnit_UnregisterFactory_ByName(m_factory, m_strName);
		_CppUnit_DeleteTestSuiteFactory(m_factory);
	}

private:
	std::string m_strName;
};

class TestApp_ByName
{
public:
	TestApp_ByName(const char* pName, 
		EnumRunUnitType runtype = rununitNone) : m_strName(pName)
	{
		if (!_CppUnit_IsDebugMode())
			_CppUnit_InitEnv();
		_CppUnit_Initialize(runtype);
		_CppUnit_FilterCase(_CppUnit_GetModuleName(), NULL, NULL);
	}
	~TestApp_ByName()
	{
		try
		{
			_CppUnit_RunAllTests_ByName(__argc, __wargv, m_strName);
		}
		catch (...)
		{
			_CppUnit_Abort();
		}
		_CppUnit_Terminate();
	}

private:
	std::string m_strName;
};

// -------------------------------------------------------------------------

class TestCase : public TestFixture
{
};

// -------------------------------------------------------------------------

#define CPPUNIT_TEST_SUITE(ATestFixtureType)                           		\
public:                                                                		\
	typedef ATestFixtureType TestFixtureType;								\
	static const char* __getFixtureName()									\
	{																		\
		return #ATestFixtureType;											\
	}																		\
    static void addTestsToSuite(TestSuiteBuilderContextBase* baseContext )	\
    {																		\
		TestSuiteBuilderContextType* context;								\
		_CppUnit_CreateTestSuiteBuilderContext(baseContext, &context)

#define CPPUNIT_TEST(testMethod)											\
		_CppUnit_AddTest(													\
			context, 														\
			__getFixtureName(),												\
			#testMethod,													\
			(FnTestMethod)&TestFixtureType::testMethod						\
			)

#define CPPUNIT_TEST_EXCEPTION(testMethod, ExceptionType)

#define CPPUNIT_TEST_SUITE_END()                                           	\
		_CppUnit_DeleteTestSuiteBuilderContext(context);					\
    }																		\
																			\
    static void suite(TestSuite** ppSuite)                                  \
    {																		\
		_CppUnit_SuiteEx(													\
			TestFixtureCreator<TestFixtureType>::makeFixture,				\
			TestFixtureType::addTestsToSuite,								\
			__getFixtureName(),												\
			_CppUnit_GetModuleName(),										\
			ppSuite);														\
	}																		\
private: /* dummy typedef so that the macro can still end with ';'*/		\
	typedef int CppUnitDummyTypedefForSemiColonEnding__

// -------------------------------------------------------------------------
// CPPUNIT_ASSERT

#define CPPUNIT_ASSERT(condition)											\
	if ( !(condition) )														\
		_CppUnit_Fail(														\
			"Expression: CPPUNIT_ASSERT(" #condition ");",					\
			__FILE__,														\
			__LINE__														\
			)

// -------------------------------------------------------------------------
// CPPUNIT_ASSERT_EQUAL

template <class T>
inline
STDMETHODIMP_(BOOL) _CppUnit_IsEqualDbg(const T& x, const T& y)
{
    return x == y;
}

inline
STDMETHODIMP_(BOOL) _CppUnit_IsEqualDbg(const char* x, const char* y)
{
	return strcmp(x, y) == 0;
}

inline
STDMETHODIMP_(BOOL) _CppUnit_IsEqualDbg(const WCHAR* x, const WCHAR* y)
{
	return wcscmp(x, y) == 0;
}

#define CPPUNIT_ASSERT_EQUAL(expected, actual)								\
do																			\
{																			\
	if ( !_CppUnit_IsEqualDbg(expected, actual) )							\
	{																		\
		_CppUnit_Fail(														\
			"Expression: CPPUNIT_ASSERT_EQUAL(" #expected "," #actual ");",	\
			__FILE__, __LINE__);											\
	}																		\
}																			\
while (0)

// -------------------------------------------------------------------------

#define CPPUNIT_PROC_REGISTRATION(fnInit, fnTerm)							\
	static HRESULT _CppUnit_RegisterProcedure__ ## fnInit =					\
			_CppUnit_RegisterProcedure(fnInit, fnTerm)

#define CPPUNIT_TEST_SUITE_REGISTRATION(TestFixtureType)					\
	static AutoRegisterTestSuite<TestFixtureType>							\
			TestFixtureType ## AutoRegister__ ## __LINE__

#define CPPUNIT_TEST_SUITE_REGISTRATION_BYNAME(TestFixtureType, SuiteName)			\
	static AutoRegisterTestSuite_ByName<TestFixtureType>							\
		TestFixtureType ## AutoRegister__ ## __LINE__ ## __ByName__(SuiteName)

// -------------------------------------------------------------------------

#if defined(_DEBUG) || defined(X_RELEASE_CASE)
#define CPPUNIT_TEST_SUITE_REGISTRATION_DBG(TestFixtureType)				\
		CPPUNIT_TEST_SUITE_REGISTRATION(TestFixtureType)
#else
#define CPPUNIT_TEST_SUITE_REGISTRATION_DBG(TestFixtureType)
#endif

#if defined(_DEBUG) || defined(X_RELEASE_CASE)
#define CPPUNIT_PROC_REGISTRATION_DBG(fnInit, fnTerm)						\
		CPPUNIT_PROC_REGISTRATION(fnInit, fnTerm)
#else
#define CPPUNIT_PROC_REGISTRATION_DBG(fnInit, fnTerm)
#endif

// -------------------------------------------------------------------------
// $Log: basic.h,v $
// Revision 1.24  2007/05/22 07:35:08  xuehua
// *** empty log message ***
//
// Revision 1.23  2006/04/18 05:42:56  xulingjiao
// 修复25796号BUG
//
// Revision 1.22  2005/12/06 02:31:46  xushiwei
// 引入<kfc/osllite.h>，将常见的os相关代码纳入。
//
// Revision 1.21  2005/12/05 05:48:24  xushiwei
// 为kfclite.h提供一个lite版的debug。不使用调试策略（X_NO_DEBUG_STRATEGY）。
//
// Revision 1.20  2005/03/25 03:12:36  xushiwei
// 让cppunit不依赖kfc照样工作。
//
// Revision 1.19  2005/03/24 09:57:34  xushiwei
// 引入新的通用开关: /ndebug。参考_CppUnit_IsDebugMode。
//
// Revision 1.18  2005/03/15 03:34:26  xushiwei
// 1、_CppUnit_RunAllTests - 增加/run:<testclass>.<testmethod>参数支持。
// 2、_CppUnit_FilterCase - 支持修改部分Filter参数。
// 3、_CppUnit_Initialize参数改为EnumRunUnitType runtype。
//
// Revision 1.17  2005/03/10 03:33:21  xushiwei
// 增加_CppUnit_RegisterProcedure。
// 引入新宏: CPPUNIT_PROC_REGISTRATION_DBG/CPPUNIT_PROC_REGISTRATION。
//
// Revision 1.16  2005/01/21 01:58:26  xushiwei
// TestApp::AddUnit返回值由void改为HRESULT。
//

#endif /* __CPPUNIT_BASIC_H__ */
