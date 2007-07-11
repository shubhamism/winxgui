/* -------------------------------------------------------------------------
//	文件名		：	cppunit/advunit.h
//	创建者		：	许式伟
//	创建时间	：	2004-9-20 20:40:19
//	功能描述	：	
//
// -----------------------------------------------------------------------*/
#ifndef __CPPUNIT_ADVUNIT_H__
#define __CPPUNIT_ADVUNIT_H__

#ifndef __CPPUNIT_BASIC_H__
#include "basic.h"
#endif

typedef const void* TestUnitIdentifierType;

// -------------------------------------------------------------------------

#pragma pack(1)

struct TestSuiteCond
{
	TestSuiteCond* pPrev;
	TestUnitIdentifierType idTestUnit;
	FnMakeSuite fnCreator;
	TestFactory* pFactory;
};

#pragma pack()

// -------------------------------------------------------------------------

STDAPI_(void) _CppUnit_RegisterTestSuiteCond(
											 IN OUT TestSuiteCond* pCond);

STDAPI_(void) _CppUnit_AddUnit(
								IN TestUnitIdentifierType idTestUnit);

STDAPI_(void) _CppUnit_UnregisterTestSuiteCond(
											 IN OUT TestSuiteCond* pCond);

// -------------------------------------------------------------------------
// TestUnitIdentifier

template <class Unused>
class _TestUnitIdentifier
{
public:
	static int _g_nInst;
};

template <class Unused>
int _TestUnitIdentifier<Unused>::_g_nInst;

#define TestUnitIdentifier()	(&_TestUnitIdentifier<int>::_g_nInst)

// -------------------------------------------------------------------------

template <class TestFixtureType>
class AutoRegisterTestSuiteCond
{
private:
	TestSuiteCond m_cond;
	
public:
	AutoRegisterTestSuiteCond()
	{
		m_cond.idTestUnit = TestUnitIdentifier();
		m_cond.fnCreator = TestFixtureType::suite;
		m_cond.pFactory = NULL;
		m_cond.pPrev = NULL;
		_CppUnit_RegisterTestSuiteCond(&m_cond);
	}
	~AutoRegisterTestSuiteCond()
	{
		_CppUnit_UnregisterTestSuiteCond(&m_cond);
	}
};

// -------------------------------------------------------------------------

#define CPPUNIT_TEST_SUITE_REGISTRATION_COND(TestFixtureType)				\
	static AutoRegisterTestSuiteCond<TestFixtureType>						\
			TestFixtureType ## AutoRegister__ ## __LINE__

// -------------------------------------------------------------------------

#endif /* __CPPUNIT_ADVUNIT_H__ */
