/* -------------------------------------------------------------------------
//	文件名		：	cppunit/linklib.h
//	创建者		：	许式伟
//	创建时间	：	2003-11-7 20:44:45
//	功能描述	：	
//
//	$Id: linklib.h,v 1.2 2005/05/10 02:46:27 xushiwei Exp $
// -----------------------------------------------------------------------*/
#ifndef __CPPUNIT_LINKLIB_H__
#define __CPPUNIT_LINKLIB_H__

// -------------------------------------------------------------------------

#if !defined(__Linked_cppunit)
#define __Linked_cppunit
#if defined(X_CC_BC)
#	if defined(X_OS_WINDOWS)
#		if defined(USES_KSKERN)
#			pragma link "cppunitk_bcb.lib"
#		else
#			pragma link "cppunit_bcb.lib"
#		endif
#	else
#		pragma link "libcppunit.so"
#	endif
#elif defined(_MSC_VER)
#	pragma comment(lib, "cppunit")
#endif
#endif

// -------------------------------------------------------------------------
// $Log: linklib.h,v $
//

#endif /* __CPPUNIT_LINKLIB_H__ */
