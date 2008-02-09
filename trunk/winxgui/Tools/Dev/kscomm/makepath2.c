/* -------------------------------------------------------------------------
//	文件名		：	makepath2.c
//	创建者		：	许式伟
//	创建时间	：	2002-2-28 13:44:00
//	功能描述	：	
//
// -----------------------------------------------------------------------*/

#include "stdafx.h"

// -------------------------------------------------------------------------

STDMETHODIMP_(void) MakePath2(LPTSTR szFileDest, LPCTSTR szPath, LPCTSTR szFile)
{
	LPTSTR psz;
	if (szPath == NULL || *szPath == 0)
	{
		StrECopy(szFileDest, szFile);
	}
	else
	{
		psz = StrECopy(szFileDest, szPath);
		if (psz[-1] != '/' && psz[-1] != '\\')
		{
			*psz++ = '/';
		}
		StrECopy(psz, szFile);
	}
}

// -------------------------------------------------------------------------
