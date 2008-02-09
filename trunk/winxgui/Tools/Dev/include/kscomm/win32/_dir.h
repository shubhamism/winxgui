// -------------------------------------------------------------------------
//	文件名		：	_dir.h
//	创建者		：	许式伟
//	创建时间	：	2002-2-8 10:42:05
//	功能描述	：	
//
// -------------------------------------------------------------------------
#ifndef __WIN32_DIR_H__
#define __WIN32_DIR_H__

#ifndef _INC_DIRECT
#include <direct.h>
#endif

#ifndef _INC_IO
#include <io.h>
#endif

__BEGIN_DECLS

#if defined(__WINNT__)
#define ksGetCwdW(dir, cch)	 _wgetcwd(dir, cch)
#define ksChDirW(dir)		 _wchdir(dir)
#define ksFindFirstW(file, fi)												\
		(-1 != ((fi)->hdir = _wfindfirst(file, &(fi)->find)) ? S_OK : S_FALSE)
#define ksFindNextW(fi)		 _wfindnext((fi)->hdir, &(fi)->find)
#endif

// -------------------------------------------------------------------------

#define ksGetCwdA(dir, cch)		getcwd(dir, cch)
#define ksChDirA(dir)			chdir(dir)

// -------------------------------------------------------------------------

struct tagFILEINFOW
{
	struct _wfinddata_t	find;
	long hdir;
};
typedef struct tagFILEINFOW FILEINFOW;

struct tagFILEINFOA
{
	struct _finddata_t find;
	long hdir;
};
typedef struct tagFILEINFOA FILEINFOA;

#if defined(UNICODE)
#	define	FILEINFO	FILEINFOW
#else
#	define	FILEINFO	FILEINFOA
#endif

HRESULT __cdecl ksFindFirstA(LPCTSTR szDir, FILEINFO* fi);
HRESULT __cdecl ksFindNext (FILEINFO* fi);
void    __cdecl ksFindClose(FILEINFO* fi);
LPCTSTR __cdecl ksFindInfo_FileName(FILEINFO* fi);

#define ksFindNextA(fi)				_findnext((fi)->hdir, &(fi)->find)
#define ksFindClose(fi)				_findclose((fi)->hdir)
#define ksFindInfo_FileName(fi)		((fi)->find.name)
#define ksFindInfo_IsSubDir(fi)		((fi)->find.attrib & _A_SUBDIR)

// -------------------------------------------------------------------------

__END_DECLS

#endif // __WIN32_DIR_H__
