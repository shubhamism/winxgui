// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__E0F6A7A7_66BE_4419_8130_AC9BCE746845__INCLUDED_)
#define AFX_STDAFX_H__E0F6A7A7_66BE_4419_8130_AC9BCE746845__INCLUDED_

#define _ATL_APARTMENT_THREADED

$$IF(fUseWinsdk)
#include <winx/Config.h>
$$ENDIF
#include <winx.h>
$$IF(ScrollWindow)
#include <winx/ScrollWindow.h>
$$ENDIF
#include <winx/CommonDialogs.h>
$$IF(fGdiplus)
#include <winx/Gdiplus.h>
$$ENDIF
$$IF(HTMLPage)
#include <winx/WebBrowser.h>
$$ENDIF

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__E0F6A7A7_66BE_4419_8130_AC9BCE746845__INCLUDED_)
