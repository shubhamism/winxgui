// -------------------------------------------------------------------------
//	�ļ���		��	ks_fileutils.h
//	������		��	��ʽΰ
//	����ʱ��	��	2002-2-8 11:44:24
//	��������	��	
//
// -------------------------------------------------------------------------
#ifndef __KS_FILEUTILS_H__
#define __KS_FILEUTILS_H__

__BEGIN_DECLS

#ifndef _MAX_PATH
#define _MAX_PATH		512
#define _MAX_FNAME		256
#define _MAX_DRIVE		3
#define _MAX_DIR		256
#define _MAX_EXT		256
#endif

#ifndef E_PATH_INVALID
#define E_PATH_INVALID			E_FAIL
#endif

STDMETHODIMP_(void) SplitPath(
	LPCTSTR path,
	LPTSTR drive,
	LPTSTR dir,
	LPTSTR fname,
	LPTSTR ext
	);

STDMETHODIMP_(void) MakePath(
	LPTSTR path,
	LPCTSTR drive,
	LPCTSTR dir,
	LPCTSTR fname,
	LPCTSTR ext
	);

STDMETHODIMP SearchFilePath(
	LPTSTR	 szDestFile,
	LPCTSTR	 szFileSearch,
	LPCTSTR* szDirs,
	UINT	 nDirs,
	LPCTSTR	 szBasePath
	);

STDMETHODIMP StdPath(LPTSTR szDestPath, LPCTSTR szPath);
STDMETHODIMP MergePath(LPTSTR szDestFile, LPCTSTR szBasePath, LPCTSTR szSrcFile);

// ���ܣ�ȡ·�����һ������
//	1) ��� szPath = '/' ���� nil, �� ʧ�ܡ�
//  2) ��� szPath = '~/workspace/Tools/MakeGen', �� szPathName = 'MakeGen'
//			szPath = 'tcc/', �� szPathName = 'tcc'
STDMETHODIMP GetPathName(LPTSTR szPathName, LPCTSTR szPath);

// ���ܣ�
//  GetPathName(szPathName, szPath);
//	StrCat(szPathName, szExt);
//	MakePath2(szDestFile, szPath, szPathName);
STDMETHODIMP GenDefaultFile(LPTSTR szDestFile, LPCTSTR szPath, LPCTSTR szExt);

STDMETHODIMP_(void) GetFileName(LPTSTR fname, LPCTSTR szFileSrc);
STDMETHODIMP_(void) ForceExt(LPTSTR szFileDest, LPCTSTR szFileSrc, LPCTSTR szExtDest);
STDMETHODIMP GuessExt(LPTSTR szFile, LPCTSTR szExtGuess);

STDMETHODIMP_(void) MakePath2(LPTSTR szFileDest, LPCTSTR szPath, LPCTSTR szFile);
STDMETHODIMP_(void) SplitPath2(LPCTSTR szFileOrg, LPTSTR szPath, LPTSTR szFile);

STDMETHODIMP_(void) RemovePathSep(LPTSTR szPath);
STDMETHODIMP_(BOOL) IsFileExist(LPCTSTR szFile);
STDMETHODIMP_(BOOL) IsFileExist2(LPTSTR szFile);

STDMETHODIMP_(BOOL) GetRealFileName(LPTSTR szFile, LPCTSTR szFileSrc);

#define GetFileName(fname, szFileSrc)	SplitPath(szFileSrc, NULL, NULL, fname, NULL)

#ifndef _tsplitpath
#define _tsplitpath		SplitPath
#define _tmakepath		MakePath
#endif

__END_DECLS

#endif // __KS_FILEUTILS_H__
