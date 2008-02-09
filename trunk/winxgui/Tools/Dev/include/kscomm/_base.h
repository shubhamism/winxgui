// -------------------------------------------------------------------------
//	文件名		：	_base.h
//	创建者		：	许式伟
//	创建时间	：	2002-1-29 15:29:53
//	功能描述	：	
//
// -------------------------------------------------------------------------
#ifndef __STDAFX_COMMON_H__
#define __STDAFX_COMMON_H__

#include <stdlib.h>
#include "kern/errno.h"

/*********************************
#if defined(__INTEL__) || defined(INTEL) || defined(_INTEL)
#	undef	__INTEL__
#	define  __INTEL__
#elif defined(__SPARC__) || defined(SPARC) || defined(_SPARC)
#	undef	__SPARC__
#	define  __SPARC__
#else
#	error "Unknown CPU type!!!"
#endif
***********************************/

#if defined(__SPARC__) || defined(SPARC) || defined(_SPARC)
#	undef	__SPARC__
#	define  __SPARC__
#else
#	undef	__INTEL__
#	define  __INTEL__
#endif

#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32)
#	define __WIN32__
#	undef NULLFN
#	define	NULLFN			0
#elif defined(__LINUX__) || defined(LINUX) || defined(_LINUX)
#	undef  __LINUX__
#	define __LINUX__
#elif defined(__SOLS__) || defined(SOLARIS) || defined(_SOLARIS)
#	undef  __SOLS__
#	define __SOLS__
#else
#	error "Unknown Planform!!!"
#endif

#if !defined(__WIN32__)
#	define __stdcall
#	define	__cdecl
#	if defined(__cplusplus)
		inline void __cdecl NULLFN(...) {}
#	else
//		void  __cdecl _g_NULLFN(...);
#		define NULLFN _g_NULLFN
#	endif
#endif

#if !defined(__BEGIN_DECLS)
#	if defined(__cplusplus)
#		define __BEGIN_DECLS	extern "C" {
#		define __END_DECLS		}
#	else
#		define __BEGIN_DECLS
#		define __END_DECLS
#	endif
#endif

// -------------------------------------------------------------------------

#ifndef STDMETHODIMP
#define STDMETHODIMP_(Type)		Type __stdcall
#define STDMETHODIMP			HRESULT __stdcall
#endif
		
#define LPCSTR			const char*
#define BOOL			int
#define UINT			unsigned
#define TCHAR			char
#define _TSCHAR			TCHAR
#define LPTSTR			char*
#define LPCTSTR			const char*
#ifndef _T
#define _T(x)			x
#endif

#define HRESULT			long

#define TRUE			1
#define FALSE			0

#undef	_MBCS
#define _ISLEADBYTE(c)  _ismbblead(c)

#ifndef KS_BREAKPOINT
#define KS_BREAKPOINT()	__asm { int 3 }
#endif

#ifndef _DEBUG
#ifndef TRACE
#define	TRACE			NULLFN
#endif
#else
#ifndef TRACE
#define TRACE			_tprintf
#endif
#endif

#ifndef MSGBOX
#define MSGBOX(s)		{ TRACE(s); KS_BREAKPOINT(); }
#endif

#ifndef _DEBUG
#define ASSERT(x)		0
#else
#ifndef ASSERT
#define ASSERT(x)		do { if(!(x)) KS_BREAKPOINT(); } while(0)
#endif
#endif

#ifndef _DEBUG_ONLY
#	if defined(_DEBUG)
#		define _DEBUG_ONLY(e)		e
#	else
#		define _DEBUG_ONLY(e)		NULL
#	endif
#endif

//#define countof(a)		(sizeof(a) / sizeof(a[0]))

#ifndef IN
#define IN
#endif
		
#ifndef OUT
#define OUT
#endif

#ifndef KS_CHECK
#define KS_CHECK_BOOLEX(result, expr)										\
	if (!(result))															\
	{																		\
		expr;																\
		ASSERT(0);															\
		goto KS_EXIT;														\
	}
#define KS_CHECK_BOOL(result)		KS_CHECK_BOOLEX(result, NULL)
#define KS_CHECK(hr)				KS_CHECK_BOOL(SUCCEEDED(hr))
#endif

// -------------------------------------------------------------------------

#endif // __STDAFX_COMMON_H__
