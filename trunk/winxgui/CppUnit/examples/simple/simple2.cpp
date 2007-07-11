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
SIMPLE_API int DoubleOf2(int n)
{
	return DoubleOf(n);
}

// -------------------------------------------------------------------------

class TestDoubleOf2 : public TestCase
{
public:
	CPPUNIT_TEST_SUITE(TestDoubleOf2);
		CPPUNIT_TEST(test2);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp() {}
	void tearDown() {}

public:
	void test2()
	{
		CPPUNIT_ASSERT( DoubleOf2(2) == 4 );
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION_DBG(TestDoubleOf2);

// -------------------------------------------------------------------------
