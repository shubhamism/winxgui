// -------------------------------------------------------------------------
//	文件名		：	ks_string.h
//	创建者		：	许式伟
//	创建时间	：	2002-2-8 15:05:37
//	功能描述	：	
//		see <shlwapi.h> - Interface for the Windows light-weight utility APIs
// -------------------------------------------------------------------------
#ifndef __KS_STRING_H__
#define __KS_STRING_H__

#ifndef _INC_STRING
#include <string.h>
#endif

#if defined(__LINUX__) || defined(__SOLS__)
#	undef  stricmp
#	define stricmp		strcasecmp
#endif

__BEGIN_DECLS

char* __cdecl StrTokA(char * string, const char* control);

STDMETHODIMP_(int)	  StrCmpI(LPCTSTR dst, LPCTSTR src);
STDMETHODIMP_(LPTSTR) StrCopy(LPTSTR pszDest, LPCTSTR pszSrc);
STDMETHODIMP_(LPTSTR) StrCat(LPTSTR pszDest, LPCTSTR pszSrc);
STDMETHODIMP_(LPTSTR) StrECopy(LPTSTR pszDest, LPCTSTR pszSrc);

#ifndef UNICODE
#	define _tcslen			strlen
#	define _tcscpy			strcpy
#	define _tcsncmp			strncmp
#	define _tcsncpy			strncpy
#	define _tcscat			strcat
#	define _tcschr			strchr
#	define _tcsrchr			strrchr
#	define _tcstok			strtok
#	define _tcscspn			strcspn
#	define _tcsicmp			stricmp
#	define _tcsecpy			StrECopy
#else
#endif

#define StrCmpI			_tcsicmp
#define StrICmp			_tcsicmp
#define StrCopy			_tcscpy
#define StrCat			_tcscat

#if !defined(tstring)
#	if defined(UNICODE)
#		define tstring			wstring
#	else
#		define tstring			string
#	endif
#endif

__END_DECLS

#endif // __KS_STRING_H__
