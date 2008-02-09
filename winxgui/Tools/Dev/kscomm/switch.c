// -------------------------------------------------------------------------
//	文件名		：	switch.c
//	创建者		：	许式伟
//	创建时间	：	2002-1-24 16:52:39
//	功能描述	：	
//
// -------------------------------------------------------------------------

#include "stdafx.h"

#if defined(__LINUX__) || defined(__SOLS__)
#	define IsSwitch(sw)		((sw) == '-')
#elif defined(__WIN32__) || defined(__MSDOS__)
#	define IsSwitch(sw)		((sw) == '-' || (sw) == '/')
#else
#	error "Unknown Platform!"
#endif

UINT __stdcall AnalyzeSwitch(LPTSTR* argv, UINT argc, SWITCHS* pSw, LPCTSTR sws)
{
	int i;
	LPTSTR* argv0 = argv;
	
	*pSw = 0;
	for (i = 0; i < (int)argc; ++i)
	{
		if (IsSwitch(argv0[i][0]))
		{
			LPCTSTR swFind = _tcschr(sws, argv0[i][1]);
			if (swFind)
			{
				*pSw |= (1 << (swFind - sws));
			}
			else
			{
				*pSw |= switchUnknown;
			}
		}
		else
		{
			*argv++ = argv0[i];
		}
	}
	return (argv - argv0);
}

// -------------------------------------------------------------------------
