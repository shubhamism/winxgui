/* -------------------------------------------------------------------------
//	文件名		：	adapter/STLAdapter.h
//	创建者		：	许式伟
//	创建时间	：	4/22/2003 9:19:18 PM
//	功能描述	：	
//
// -----------------------------------------------------------------------*/
#ifndef __TEXT_ADAPTER_STLADAPTER_H__
#define __TEXT_ADAPTER_STLADAPTER_H__

#if defined(__KFC_PLATFORM_H__)
#define __UESE_KFC
#endif

#if defined(_MSC_VER)
#pragma warning(disable:4786)
#pragma warning(disable:4503)
#endif

// -------------------------------------------------------------------------

#if defined(__UESE_KFC)

#ifndef __STL_MAP_H__
#include <stl/map.h>
#endif

#ifndef __STL_LIST_H__
#include <stl/list.h>
#endif

#ifndef __STL_STACK_H__
#include <stl/stack.h>
#endif

#ifndef __STL_STRING_H__
#include <stl/string.h>
#endif

// -------------------------------------------------------------------------

#else // !defined(__UESE_KFC)

#if !defined(_MAP_) && !defined(__SGI_STL_MAP)
#include <map>
#endif

#if !defined(_LIST_) && !defined(__SGI_STL_LIST)
#include <list>
#endif

#if !defined(_STACK_) && !defined(__SGI_STL_STACK)
#include <stack>
#endif

#if !defined(_STRING_) && !defined(__SGI_STL_STRING)
#include <string>
#endif

#endif

// -------------------------------------------------------------------------

#endif /* __TEXT_ADAPTER_STLADAPTER_H__ */
