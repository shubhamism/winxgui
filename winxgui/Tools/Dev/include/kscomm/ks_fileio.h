// -------------------------------------------------------------------------
//	文件名		：	ks_fileio.h
//	创建者		：	许式伟
//	创建时间	：	2002-2-8 11:45:04
//	功能描述	：	
//
// -------------------------------------------------------------------------
#ifndef __KS_FILEIO_H__
#define __KS_FILEIO_H__

#ifndef _INC_STDIO
#include <stdio.h>
#endif

#if !defined(_dbg_fflush)
#	ifdef _DEBUG
#		define	_dbg_fflush		fflush
#	else
#		define	_dbg_fflush		NULLFN
#	endif
#endif

#ifndef UNICODE
#	define _tfopen			fopen		// note: _wfopen在Win9x下不行！
#	define _tprintf			printf
#	define _ftprintf		fprintf
#	define _stprintf		sprintf
#	define _fputts			fputs
#	define _fgetts			fgets
#else
#endif

#endif // __KS_FILEIO_H__
