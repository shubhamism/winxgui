/* -------------------------------------------------------------------------
//	�ļ���		��	cppunit/cppunit.h
//	������		��	��ʽΰ
//	����ʱ��	��	2003-11-7 20:09:28
//	��������	��	
//
//	$Id: cppunit.h,v 1.8 2005/12/06 06:07:26 xushiwei Exp $
// -----------------------------------------------------------------------*/
#ifndef __CPPUNIT_CPPUNIT_H__
#define __CPPUNIT_CPPUNIT_H__

#if (0)
#define X_ENABLE_DEBUG_UI
#define X_RELEASE_CASE
#define X_RELEASE_TESTCASE
#endif

#if defined(X_RELEASE_TESTCASE)
#define X_RELEASE_CASE
#endif

#if defined(ENABLE_DEBUG_UI)
#define X_ENABLE_DEBUG_UI
#endif

#ifndef __CPPUNIT_PLATAPI_H__
#include "platapi.h"
#endif

#ifndef __CPPUNIT_BASIC_H__
#include "basic.h"
#endif

#ifndef __CPPUNIT_LINKLIB_H__
#include "linklib.h"
#endif

// -------------------------------------------------------------------------

#if defined(X_ENABLE_DEBUG_UI)

// ����Debug�е�Assert�Ի���

#elif !defined(_KFC) || defined(X_NO_DEBUG_STRATEGY)

#undef ASSERT
#undef ASSERT_EQ
#undef ASSERT_OK

#define	ASSERT				CPPUNIT_ASSERT
#define ASSERT_EQ			CPPUNIT_ASSERT_EQUAL
#define	ASSERT_OK(hr)		CPPUNIT_ASSERT(SUCCEEDED(hr))

#else // ����KFC��˵���и��ӺõĽ��������

#undef ASSERT
#undef ASSERT_OK
#undef ASSERT_EQ

#undef CPPUNIT_ASSERT
#undef CPPUNIT_ASSERT_EQUAL

#define	ASSERT(e)															\
	_XStrategyAssert4(msg_report, e, "ASSERT", #e)

#define ASSERT_EQ(x, y)														\
	_XStrategyAssert4(msg_report, _XIsEqualDbg(x, y), "ASSERT_EQ", #x "," #y)

#define	ASSERT_OK(hr)														\
	_XStrategyAssert4(msg_report, SUCCEEDED(hr), "ASSERT_OK", #hr)

#define CPPUNIT_ASSERT(e)													\
	_XStrategyAssert4(msg_report, e, "CPPUNIT_ASSERT", #e)

#define CPPUNIT_ASSERT_EQUAL(x, y)											\
	_XStrategyAssert4(msg_report, _XIsEqualDbg(x, y), "CPPUNIT_ASSERT_EQUAL", #x "," #y)

#endif // !defined(_KFC)

// -------------------------------------------------------------------------
// $Log: cppunit.h,v $
// Revision 1.8  2005/12/06 06:07:26  xushiwei
// ENABLE_DEBUG_UI
//
// Revision 1.7  2005/12/05 05:43:57  xushiwei
// Ϊkfclite.h�ṩһ��lite���debug����ʹ�õ��Բ��ԣ�X_NO_DEBUG_STRATEGY����
//
// Revision 1.6  2005/03/25 02:53:58  xushiwei
// ֧��ASSERT_OK��
//
// Revision 1.5  2005/03/25 02:49:14  xushiwei
// ��CPPUNIT_ASSERT��CPPUNIT_ASSERT_EQUALҲ֧�ֵ��Բ��ԡ�
//
// Revision 1.4  2005/02/24 01:09:02  xushiwei
// ����X_RELEASE_CASE/X_RELEASE_TESTCASE�ꡣ
//

#endif /* __CPPUNIT_CPPUNIT_H__ */
