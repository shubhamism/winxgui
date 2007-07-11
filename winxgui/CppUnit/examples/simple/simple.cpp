// simple.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "simple.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

// This is an example of an exported function.
SIMPLE_API int DoubleOf(int n)
{
	return n * 2;
}

// -------------------------------------------------------------------------

class TestDoubleOf : public TestCase
{
public:
	CPPUNIT_TEST_SUITE(TestDoubleOf);
		CPPUNIT_TEST(test1);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp() {}
	void tearDown() {}

public:
	void test1()
	{
		CPPUNIT_ASSERT( DoubleOf(1) != 2 );
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION_DBG(TestDoubleOf);

// -------------------------------------------------------------------------
