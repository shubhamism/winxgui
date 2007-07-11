/* -------------------------------------------------------------------------
//	文件名		：	cppunit/platapi.h
//	创建者		：	许式伟
//	创建时间	：	2003-11-7 22:48:54
//	功能描述	：	
//
//	$Id: platapi.h,v 1.9 2007/05/22 07:35:09 xuehua Exp $
// -----------------------------------------------------------------------*/
#ifndef __CPPUNIT_PLATAPI_H__
#define __CPPUNIT_PLATAPI_H__

// -------------------------------------------------------------------------

#ifndef CPPUNIT_TESTFIXTURE_H    // -*- C++ -*-
#define CPPUNIT_PORTABILITY_H
#define CPPUNIT_NS_BEGIN
#define CPPUNIT_API
#define CPPUNIT_NS_END
#define CPPUNIT_NS
#include "private/TestFixture.h"
#endif

// -------------------------------------------------------------------------

#if defined(_WIN32) || defined(WIN32)

#ifndef _WINDOWS_
#include <windows.h>
#endif

#endif

// -------------------------------------------------------------------------

#ifndef EXTERN_C
#ifdef __cplusplus
#define EXTERN_C    extern "C"
#else
#define EXTERN_C
#endif
#endif

#ifndef STDAPI
#define STDAPI              EXTERN_C long __stdcall
#define STDAPI_(type)       EXTERN_C type __stdcall
#endif

// -------------------------------------------------------------------------

class TestSuite;

class TestSuiteBuilderContextBase;
class TestSuiteBuilderContextType;

class TestFactory;
class TestFactoryRegistry;

// -------------------------------------------------------------------------

typedef void (TestFixture::*FnTestMethod)();

typedef void (*FnAddTestsToSuite)(IN TestSuiteBuilderContextBase* baseContext);

typedef void (*FnMakeFixture)(OUT TestFixture** ppv);

typedef void (*FnMakeSuite)(OUT TestSuite** ppv);

typedef void (*FnInitializeProc)();

typedef void (*FnTerminateProc)();

// -------------------------------------------------------------------------

enum EnumRunUnitType
{
	rununitNone		= 0,	// exe程序不需要RunUnit程序。
	rununitConsole	= 1,	// 控制台rununit程序。
	rununitWindows	= 2,	// 窗口系统rununit程序。
};

STDAPI _CppUnit_Initialize(IN EnumRunUnitType runtype);

/*
@fn _CppUnit_RegisterProcedure
@brief
	注册RunAllTestCases前、后的回调过程。
@arg [in] fnInit
	初始化过程。该回调过程在所有测试案例执行前被调用。
@arg [in] fnTerm
	终止化过程。该回调过程在所有测试案例均执行完毕后被调用。
@return
	返回值被忽略。
@*/
STDAPI _CppUnit_RegisterProcedure(
								  IN FnInitializeProc fnInit,
								  IN FnTerminateProc fnTerm
								  );

STDAPI _CppUnit_RunAllTests(
							IN int argc,
							IN WCHAR** argv
							);

STDAPI _CppUnit_RunAllTests_ByName(
							IN int argc,
							IN WCHAR** argv,
							IN LPCSTR strName);

STDAPI_(void) _CppUnit_Terminate();

STDAPI_(void) _CppUnit_CreateTestSuiteBuilderContext(
						IN TestSuiteBuilderContextBase* contextBase,
						OUT TestSuiteBuilderContextType** ppv);

STDAPI_(void) _CppUnit_DeleteTestSuiteBuilderContext(
						IN TestSuiteBuilderContextType* context);

STDAPI _CppUnit_AddTest(
						IN TestSuiteBuilderContextType* context,
						IN const char* szClassName,
						IN const char* szMethod,
						IN FnTestMethod test
						);

STDAPI_(void) _CppUnit_Suite(
							 IN FnMakeFixture fnCreator,
							 IN FnAddTestsToSuite addTestsToSuite,
							 IN const char* szClassName,
							 OUT TestSuite** ppv
							 );

STDAPI_(void) _CppUnit_SuiteEx(
							 IN FnMakeFixture fnCreator,
							 IN FnAddTestsToSuite addTestsToSuite,
							 IN const char* szClassName,
							 IN const WCHAR* szModuleName,
							 OUT TestSuite** ppv
							 );

/*
@fn _CppUnit_FilterCase
@brief
	对要执行的测试案例进行过滤。
	该函数应该在\<_CppUnit_RunAllTests>函数前调用，以限制要执行的案例。
@arg szModuleName
	你可以只限制执行那个模块中的案例。传入NULL表示不做限制。
	通常，你需要传入一个模块（exe或dll）名，\
	以便cppunit只执行该模块本身的案例，而不执行该模块所依赖的dll的案例。
@arg szTestClass
	你可以限制只执行某个TestCase类中的所有案例。传入NULL表示执行所有的TestCase中的案例。
@arg szTestMethod
	你可以限制只执行要测试的TestCase中的某个method。传入NULL表示不做限制。
@*/
STDAPI_(void) _CppUnit_FilterCase(
								IN LPCWSTR szModuleName,
								IN LPCSTR szTestClass,
								IN LPCSTR szTestMethod
								);

#ifndef CPPUNIT_NOFILTER_MODULE
#define CPPUNIT_NOFILTER_MODULE			((LPCWSTR)1)
#define CPPUNIT_NOFILTER_TESTCLASS		((LPCSTR)1)
#define CPPUNIT_NOFILTER_TESTMETHOD		((LPCSTR)1)
#endif

// -------------------------------------------------------------------------

STDAPI_(void) _CppUnit_CreateTestSuiteFactory(
											  IN FnMakeSuite fnCreator,
											  OUT TestFactory** ppv
											  );

STDAPI_(void) _CppUnit_DeleteTestSuiteFactory(
											  IN TestFactory* pFac
											  );

// -------------------------------------------------------------------------

STDAPI_(void) _CppUnit_GetRegistry(
								   OUT TestFactoryRegistry** ppv
								   );

STDAPI_(void) _CppUnit_RegisterFactory(
									   IN TestFactoryRegistry* registry,
									   IN TestFactory* factory
									   );

STDAPI_(void) _CppUnit_RegisterFactory1(
									   IN TestFactory* factory
									   );

STDAPI_(void) _CppUnit_UnregisterFactory(
										 IN TestFactoryRegistry* registry,
										 IN TestFactory* factory
										 );

STDAPI_(void) _CppUnit_UnregisterFactory1(
										 IN TestFactory* factory
										 );

STDAPI_(void) _CppUnit_RegisterFactory_ByName(
										IN TestFactory* factory,
										IN LPCSTR strName);

STDAPI_(void) _CppUnit_UnregisterFactory_ByName(
										IN TestFactory* factory,
										IN LPCSTR strName);

// -------------------------------------------------------------------------

STDAPI_(void) _CppUnit_Fail(
							IN const char* message, 
							IN const char* file,
							IN int line
							);

STDAPI_(void) _CppUnit_FailNotEqual(
									IN const char* expected, 
									IN const char* actual, 
									IN const char* file,
									IN int line,
									IN const char* detail,
									IN const char* shortDescription
									);

STDAPI_(void) _CppUnit_FailNotEqual_1(
									  IN const char* expected, 
									  IN const char* actual, 
									  IN const char* file,
									  IN int line
									  );

// -------------------------------------------------------------------------
// _CppUnit_BreakAlloc

STDAPI_(UINT) _CppUnit_BreakAlloc(UINT nAllocBreak);

// -------------------------------------------------------------------------
// $Log: platapi.h,v $
// Revision 1.8  2005/10/27 02:02:46  xushiwei
// cppunit增加DebugBreak。
//
// Revision 1.6  2005/03/15 03:34:26  xushiwei
// 1、_CppUnit_RunAllTests - 增加/run:<testclass>.<testmethod>参数支持。
// 2、_CppUnit_FilterCase - 支持修改部分Filter参数。
// 3、_CppUnit_Initialize参数改为EnumRunUnitType runtype。
//
// Revision 1.5  2005/03/10 03:33:21  xushiwei
// 增加_CppUnit_RegisterProcedure。
// 引入新宏: CPPUNIT_PROC_REGISTRATION_DBG/CPPUNIT_PROC_REGISTRATION。
//

#endif /* __CPPUNIT_PLATAPI_H__ */
