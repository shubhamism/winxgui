/* -------------------------------------------------------------------------
//	文件名		：	sols/_dir.h
//	创建者		：	许式伟
//	创建时间	：	2002-5-9 10:46:25
//	功能描述	：	
//
//-----------------------------------------------------------------------*/
#ifndef __SOLS__DIR_H__
#define __SOLS__DIR_H__

#ifndef _UNISTD_H
#include <unistd.h>
#endif

#ifndef _DIRENT_H
#include <dirent.h>
#endif

__BEGIN_DECLS

// -------------------------------------------------------------------------

#define ksGetCwdA(dir, cch)		getcwd(dir, cch)
#define ksChDirA(dir)			chdir(dir)

// -------------------------------------------------------------------------

struct tagFILEINFOA
{
	struct dirent* find;
	DIR* hdir;
};
typedef struct tagFILEINFOA FILEINFOA;

#if defined(UNICODE)
#	define	FILEINFO	FILEINFOW
#else
#	define	FILEINFO	FILEINFOA
#endif

HRESULT __cdecl ksFindFirstA(LPCSTR file, FILEINFOA* fi);
HRESULT __cdecl ksFindNextA (FILEINFOA* fi);
LPCTSTR __cdecl ksFindInfo_FileName(FILEINFO* fi);

#define ksFindClose(fi)				closedir((fi)->hdir)
#define ksFindInfo_FileName(fi)		((fi)->find->d_name)
#define ksFindInfo_IsSubDir(fi)		((fi)->find->d_type == DT_DIR)

// -------------------------------------------------------------------------

__END_DECLS

#endif /* __SOLS__DIR_H__ */
