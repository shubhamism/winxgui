// -------------------------------------------------------------------------
//	�ļ���		��	baseimp.h
//	������		��	��ʽΰ
//	����ʱ��	��	2002-1-30 19:16:36
//	��������	��	
//
// -------------------------------------------------------------------------
#ifndef __BASEIMP_H__
#define __BASEIMP_H__

struct tagKStdPathParam
{
	LPTSTR	pszDest;
	LPTSTR	pszRootPathEnd;
	BOOL	fAbsolute;
};
typedef struct tagKStdPathParam KStdPathParam;

STDMETHODIMP _StdPath(KStdPathParam* pDest, LPCTSTR szSrcFile);
STDMETHODIMP_(LPTSTR) _GetRootPath(LPTSTR szRoot, LPCTSTR szPath);

#endif // __BASEIMP_H__
