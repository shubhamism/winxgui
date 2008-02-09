// -------------------------------------------------------------------------
//	文件名		：	ksx_common.h
//	创建者		：	许式伟
//	创建时间	：	2002-1-30 11:28:52
//	功能描述	：	
//
//	$Id: ksx_common.h,v 1.4 2006/05/30 00:20:49 xushiwei Exp $
// -------------------------------------------------------------------------
#ifndef __KSX_COMMON_H__
#define __KSX_COMMON_H__

// -------------------------------------------------------------------------
#if defined(X_BACKWARD_DEFINE)
#include "_base.h"
#else
// -------------------------------------------------------------------------

#define X_NO_DEBUG_STRATEGY
//#include <kfc/stddef.h>
//#include <tchar.h>
#if defined(X_OS_WINDOWS)
#define __WIN32__
#elif defined(X_OS_LINUX)
#define __LINUX__
#endif

#undef	_MBCS
#define _ISLEADBYTE(c)  _ismbblead(c)

#endif
// -------------------------------------------------------------------------

#include <stdlib.h>

#define STDMETHODIMP long
#define STDMETHODIMP_(type) type

typedef const char* LPCSTR;
typedef const char* LPCTSTR;
typedef char* LPTSTR;
typedef char* LPSTR;
typedef char TCHAR;
typedef char _TSCHAR;
#define _T(x) x

typedef int BOOL;
#define TRUE 1
#define FALSE 0

typedef long HRESULT;
#define S_OK 0
#define S_FALSE 1
#define E_FAIL  (-2)

#define __cdecl
#define __stdcall

typedef int INT;
typedef unsigned UINT;

#if defined(_DEBUG)
#define TRACE printf
#elif defined(_ENABLE_TRACE) || defined(__cplusplus)
inline void __null_fn__(...) {}
#define TRACE __null_fn__
#define NULLFN __null_fn__
#endif

#if defined(_DEBUG)
#include <assert.h>
#define ASSERT(e) assert(e)
#else
#define ASSERT(e)
#endif

#define countof(array) (sizeof(array) / sizeof(array[0]))

#include "ks_fileio.h"
#include "ks_fileutils.h"
#include "ks_strutils.h"

__BEGIN_DECLS

typedef unsigned long SWITCHS;

#define switchUnknown				0x80000000L

STDMETHODIMP_(UINT) AnalyzeSwitch(LPTSTR* argv, UINT argc, SWITCHS* pSw, LPCTSTR sws);
STDMETHODIMP_(int) GetKeywordIndex(LPCTSTR szKey, LPCTSTR* szKeys, UINT nKeys);

__END_DECLS

#endif // __KSX_COMMON_H__

// -------------------------------------------------------------------------

#if !defined(__Linked_KSCommon)
#define __Linked_KSCommon

#ifdef UNICODE

#else // !defined(UNICODE)
#	ifdef _MT
#		ifdef _DLL			// MT DLL
#			ifdef _DEBUG
#				define _LIBNAME	"kscommsod"
#			else
#				define _LIBNAME	"kscommso"
#			endif
#		else				// MT
#			ifdef _DEBUG
#				define _LIBNAME	"kscommd"
#			else
#				define _LIBNAME	"kscomm"
#			endif
#		endif
#	else // !defined(_MT)	// ST
#		ifdef _DEBUG
#			define _LIBNAME		"kscommstd"
#		else
#			define _LIBNAME		"kscommst"
#		endif
#	endif
#endif

#pragma message("\t程序将自动链接模块 - " _LIBNAME)
#pragma comment(lib, _LIBNAME)
#undef	_LIBNAME

#endif // __Linked_KSCommon

// -------------------------------------------------------------------------
// $Log: ksx_common.h,v $
// Revision 1.4  2006/05/30 00:20:49  xushiwei
// X_NO_DEBUG_STRATEGY
//
