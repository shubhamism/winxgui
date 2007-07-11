/* -------------------------------------------------------------------------
//	�ļ���		��	testsuitebuilder.cpp
//	������		��	��ʽΰ
//	����ʱ��	��	2003-11-7 21:38:48
//	��������	��	
//
//	$Id: testsuitebuilder.cpp,v 1.9 2007/05/22 07:35:07 xuehua Exp $
// -----------------------------------------------------------------------*/

#include "stdafx.h"
#include <cppunit/TestCaller.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestSuiteBuilderContext.h>
#include <cppunit/extensions/TestNamer.h>

using namespace CPPUNIT_NS;

// -------------------------------------------------------------------------

static LPCWSTR _g_szFilterModuleName;
static LPCSTR _g_szFilterTestClass;
static LPCSTR _g_szFilterTestMethod;

STDAPI_(void) _CppUnit_FilterCase(
								  LPCWSTR szModuleName,
								  LPCSTR szTestClass,
								  LPCSTR szTestMethod
								  )
{
	if (1 !=  (int)szModuleName)
		_g_szFilterModuleName = szModuleName;
	
	if (1 !=  (int)szTestClass)
		_g_szFilterTestClass = szTestClass;

	if (1 !=  (int)szTestMethod)
		_g_szFilterTestMethod = szTestMethod;
}

// -------------------------------------------------------------------------

typedef void (TestFixture::*FnTestMethod)();

typedef void (*FnAddTestsToSuite)(TestSuiteBuilderContextBase* baseContext);

typedef void (*FnMakeFixture)(TestFixture** ppv);

typedef void (*FnMakeSuite)(TestSuite** ppv);

// -------------------------------------------------------------------------

typedef TestSuiteBuilderContext<TestFixture> TestSuiteBuilderContextType;

STDAPI_(void) _CppUnit_CreateTestSuiteBuilderContext(
												 TestSuiteBuilderContextBase* contextBase,
												 TestSuiteBuilderContextType** ppv
												 )
{
	*ppv = new TestSuiteBuilderContextType(*contextBase);
}

STDAPI_(void) _CppUnit_DeleteTestSuiteBuilderContext(
													 TestSuiteBuilderContextType* context
													 )
{
	delete context;
}

// -------------------------------------------------------------------------

typedef TestCaller<TestFixture> TestCallerType;

STDAPI _CppUnit_AddTest(
							   TestSuiteBuilderContextType* context,
							   const char* szClassName,
							   const char* szMethod,
							   FnTestMethod test
							   )
{
	if (
		_g_szFilterTestMethod != NULL &&
		strstr(szMethod, _g_szFilterTestMethod) == NULL
		)
	{
		return S_FALSE;
	}

	std::string strTestName = std::string(szClassName) + "::" + szMethod;

    context->addTest(							
        new TestCallerType( strTestName, test, context->makeFixture() )
		);
	return S_OK;
}

// -------------------------------------------------------------------------

class TestFixtureFactoryImpl : public TestFixtureFactory
{
private:
	FnMakeFixture _fnCreator;

public:
	TestFixtureFactoryImpl(FnMakeFixture fnCreator)
		: _fnCreator(fnCreator)
	{
	}
	TestFixture* makeFixture()
	{
		TestFixture* pFixture;
		_fnCreator(&pFixture);
		return pFixture;
	}
};

STDAPI_(void) _CppUnit_SuiteEx(
							   FnMakeFixture fnCreator,
							   FnAddTestsToSuite addTestsToSuite,
							   const char* szClassName,
							   const WCHAR* szModuleName,
							   TestSuite** ppv
							   )
{
	if (szModuleName)
		wcslwr((WCHAR*)szModuleName);
	if (
		(_g_szFilterModuleName && szModuleName && wcsstr(szModuleName, _g_szFilterModuleName) == NULL) ||
		(_g_szFilterTestClass && strstr(szClassName, _g_szFilterTestClass) == NULL)
		)
	{
		*ppv = new TestSuite(szClassName);
		return;
	}

	std::auto_ptr<TestSuite> suite( new TestSuite(szClassName) );
	
	TestFixtureFactoryImpl factory( fnCreator );
	
	TestSuiteBuilderContextBase context(
		*suite.get(),
		TestNamer(szClassName),
		factory
		);
	
	addTestsToSuite( &context );
	
	*ppv = suite.release();
};

STDAPI_(void) _CppUnit_Suite(
							 FnMakeFixture fnCreator,
							 FnAddTestsToSuite addTestsToSuite,
							 const char* szClassName,
							 TestSuite** ppv
							 )
{                                                                      
	std::auto_ptr<TestSuite> suite( new TestSuite(szClassName) );
	
	TestFixtureFactoryImpl factory( fnCreator );

	TestSuiteBuilderContextBase context(
		*suite.get(),
		TestNamer(szClassName),
		factory
		);

	addTestsToSuite( &context );
	
	*ppv = suite.release();
}

// -------------------------------------------------------------------------

class TestSuiteFactoryImpl : public TestFactory
{
private:
	FnMakeSuite _fnCreator; // ������һ������ָ�룺����ֵΪvoid��һ������������TestSuite**

public:
	TestSuiteFactoryImpl(FnMakeSuite fnCreator)
		: _fnCreator(fnCreator)
	{
	}
    virtual Test* makeTest()
    {
		TestSuite* pSuite;
		_fnCreator(&pSuite);
		return pSuite;
    }
};

STDAPI_(void) _CppUnit_CreateTestSuiteFactory(
											  FnMakeSuite fnCreator,
											  TestFactory** ppv
											  )
{
	*ppv = new TestSuiteFactoryImpl(fnCreator); // TestSuiteFactoryImpl�̳���TestFactory
}

STDAPI_(void) _CppUnit_DeleteTestSuiteFactory(
											  TestFactory* pFac
											  )
{
	delete pFac;
}

// -------------------------------------------------------------------------

STDAPI_(void) _CppUnit_GetRegistry(
								   TestFactoryRegistry** ppv
								   )
{
	*ppv = &TestFactoryRegistry::getRegistry();
}

STDAPI_(void) _CppUnit_RegisterFactory(
									   TestFactoryRegistry* registry,
									   TestFactory* factory
									   )
{
	registry->registerFactory(factory);
}

STDAPI_(void) _CppUnit_RegisterFactory1(
									   TestFactory* factory
									   )
{
	TestFactoryRegistry* registry = &TestFactoryRegistry::getRegistry();
	registry->registerFactory(factory);
}

STDAPI_(void) _CppUnit_UnregisterFactory(
									   TestFactoryRegistry* registry,
									   TestFactory* factory
									   )
{
    if ( TestFactoryRegistry::isValid() )
		registry->unregisterFactory( factory );
}

STDAPI_(void) _CppUnit_UnregisterFactory1(
										 TestFactory* factory
										 )
{
    if ( TestFactoryRegistry::isValid() )
	{
		TestFactoryRegistry* registry = &TestFactoryRegistry::getRegistry();
		registry->unregisterFactory( factory );
	}
}

STDAPI_(void) _CppUnit_RegisterFactory_ByName(TestFactory* factory,
										  LPCSTR strName)
{
	TestFactoryRegistry* registry = &TestFactoryRegistry::getRegistry(strName);
	registry->registerFactory(factory);
}

STDAPI_(void) _CppUnit_UnregisterFactory_ByName(TestFactory* factory,
											 LPCSTR strName)
{
    if ( TestFactoryRegistry::isValid() )
	{
		TestFactoryRegistry* registry = &TestFactoryRegistry::getRegistry(strName);
		registry->unregisterFactory( factory );
	}
}

// -------------------------------------------------------------------------
// $Log: testsuitebuilder.cpp,v $
// Revision 1.6  2005/03/25 03:29:27  xushiwei
// _CppUnit_FilterCase֧��:
//   CPPUNIT_NOFILTER_MODULE/TESTCLASS/TESTMETHOD������
//
