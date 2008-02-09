// -------------------------------------------------------------------------
//	文件名		：	rmpathsep.c
//	创建者		：	许式伟
//	创建时间	：	2002-1-30 11:46:10
//	功能描述	：	
//
// -------------------------------------------------------------------------

#include "stdafx.h"

STDMETHODIMP_(void) RemovePathSep(LPTSTR psz)
{
	if (*psz)
	{
		psz = _tcschr(++psz, 0);
		switch (psz[-1])
		{
		case '/': case '\\':
			psz[-1] = 0;
			break;
		}
	}
}

// -------------------------------------------------------------------------
