// -------------------------------------------------------------------------
//	文件名		：	ks_dir.h
//	创建者		：	许式伟
//	创建时间	：	2002-2-8 10:31:18
//	功能描述	：	
//
// -------------------------------------------------------------------------
#ifndef __KS_DIR_H__
#define __KS_DIR_H__

// -------------------------------------------------------------------------

#ifndef _MAX_PATH
#define _MAX_PATH		512
#define _MAX_FNAME		256
#define _MAX_DRIVE		3
#define _MAX_DIR		256
#define _MAX_EXT		256
#endif

#if defined(__WIN32__)
#	include "win32/_dir.h"
#elif defined(__LINUX__)
#	include "linux/_dir.h"
#elif defined(__SOLS__)
#	include "sols/_dir.h"
#else
#	error "Unknown Platform!!!"
#endif

// -------------------------------------------------------------------------

__BEGIN_DECLS

#if defined(UNICODE)
#	define ksGetCwd				ksGetCwdW
#	define ksChDir				ksChDirW
#else
#	define ksGetCwd				ksGetCwdA
#	define ksChDir				ksChDirA
#endif

#if defined(UNICODE)
#	define ksFindFirst				ksFindFirstW
#	define ksFindNext				ksFindNextW
#else
#	define ksFindFirst				ksFindFirstA
#	define ksFindNext				ksFindNextA
#endif

// -------------------------------------------------------------------------

#define SD_SCAN_SUBDIR			0x0001
#define SD_HANDLE_SUBDIR		0x0002

typedef HRESULT (__stdcall *FFileHandle)(LPCTSTR szFile, FILEINFO* fi, void* pParam);

STDMETHODIMP ScanDirectory(LPCTSTR szDir, FFileHandle fnHandle, UINT flags, void* pParam);

// -------------------------------------------------------------------------

__END_DECLS

#endif // __KS_DIR_H__
