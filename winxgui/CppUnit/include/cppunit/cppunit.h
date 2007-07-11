/* -------------------------------------------------------------------------
//	文件名		：	cppunit/cppunit.h
//	创建者		：	许式伟
//	创建时间	：	2003-11-7 20:09:28
//	功能描述	：	
//
//	$Id: cppunit.h,v 1.8 2005/12/06 06:07:26 xushiwei Exp $
// -----------------------------------------------------------------------*/
#ifndef __CPPUNIT_CPPUNIT_H__
#define __CPPUNIT_CPPUNIT_H__

#if (0)
#define X_RELEASE_CASE
#define X_RELEASE_TESTCASE
#endif

#if defined(X_RELEASE_TESTCASE)
#define X_RELEASE_CASE
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
// $Log: cppunit.h,v $
//

#endif /* __CPPUNIT_CPPUNIT_H__ */
