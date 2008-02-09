/* -------------------------------------------------------------------------
//	�ļ���		��	makepath2.c
//	������		��	��ʽΰ
//	����ʱ��	��	2002-2-28 13:44:00
//	��������	��	
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
