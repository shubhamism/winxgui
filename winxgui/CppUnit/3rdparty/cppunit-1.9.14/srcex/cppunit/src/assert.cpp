/* -------------------------------------------------------------------------
//	�ļ���		��	assert.cpp
//	������		��	��ʽΰ
//	����ʱ��	��	2003-11-8 0:07:28
//	��������	��	
//
//	$Id: assert.cpp,v 1.3 2005/03/25 03:31:00 xushiwei Exp $
// -----------------------------------------------------------------------*/

#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

using namespace CPPUNIT_NS;

// -------------------------------------------------------------------------

STDAPI_(void) _CppUnit_Fail(
					const char* message, 
					const char* file,
					int line
					)
{
	Asserter::fail(message, SourceLine(file, line));
}

STDAPI_(void) _CppUnit_FailNotEqual(
									const char* expected, 
									const char* actual, 
									const char* file,
									int line,
									const char* detail,
									const char* shortDescription
									)
{
	Asserter::failNotEqual(
		expected, actual, SourceLine(file, line), detail, shortDescription );
}

STDAPI_(void) _CppUnit_FailNotEqual_1(
									const char* expected, 
									const char* actual, 
									const char* file,
									int line
									)
{
	Asserter::failNotEqual(
		expected, actual, SourceLine(file, line) );
}

// -------------------------------------------------------------------------
// $Log: assert.cpp,v $
//
