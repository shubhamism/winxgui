// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__D78D945D_D6AC_4801_A3FB_9D7295108613__INCLUDED_)
#define AFX_STDAFX_H__D78D945D_D6AC_4801_A3FB_9D7295108613__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// Insert your headers here
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <atlbase.h>

#ifndef EXPORTAPI_
#define EXPORTAPI			STDAPI
#define EXPORTAPI_(Type)	STDAPI_(Type)
#endif

#ifndef countof
#define countof(array)		(sizeof(array) / sizeof(*array))
#endif

// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__D78D945D_D6AC_4801_A3FB_9D7295108613__INCLUDED_)
