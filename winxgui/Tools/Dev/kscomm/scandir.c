/* -------------------------------------------------------------------------
//	文件名		：	scandir.c
//	创建者		：	许式伟
//	创建时间	：	2002-2-28 14:24:28
//	功能描述	：	
//
//-----------------------------------------------------------------------*/

#include "stdafx.h"
#include "ks_dir.h"

// -------------------------------------------------------------------------

#if !defined(__SOLS__)

STDMETHODIMP ScanDirectory(LPCTSTR szDir, FFileHandle fnHandle, UINT flags, void* pParam)
{
	HRESULT  hr;
	FILEINFO fi;
	TCHAR	 szPath[_MAX_PATH];
	BOOL     fSubDir;
	LPCTSTR  pszFileName;
	
	hr = ksFindFirst(szDir, &fi);
	while (hr == S_OK)
	{
		pszFileName = ksFindInfo_FileName(&fi);
		if (*pszFileName != '.')
		{
			MakePath2(szPath, szDir, pszFileName);
			fSubDir = ksFindInfo_IsSubDir(&fi);
			if (!fSubDir || (flags & SD_HANDLE_SUBDIR))
			{
				fnHandle(szPath, &fi, pParam);
			}
			if (fSubDir && (flags & SD_SCAN_SUBDIR))
			{
				ScanDirectory(szPath, fnHandle, flags, pParam);
			}
		}
		hr = ksFindNext(&fi);
	}
	ksFindClose(&fi);
	return S_OK;
}

#endif // !defined(__SOLS__)

// -------------------------------------------------------------------------
