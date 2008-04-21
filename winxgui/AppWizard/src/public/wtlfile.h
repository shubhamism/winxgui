//Email : QWL1996@GMAIL.COM
//Time  : 2005-10-10
//CFile port for MFC
//CFileDialogEx port for MFC

#ifndef __ATLWTLFILE_H__
#define __ATLWTLFILE_H__

#pragma once

#include <atlapp.h>
#include <atlwin.h>

//class CFile
#ifndef __ATLMISC_H__
#include <atlmisc.h>
#endif

#ifndef __ATLDLGS_H__
#include <atldlgs.h>
#endif

namespace WTL
{
inline CString GetExePath()
{
	CString path;
	//取得程序所在路径
	TCHAR exeFullPath[MAX_PATH];
	::GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	CString strPath = exeFullPath;
	int r = strPath.ReverseFind(_T('\\'));
	if (r != -1)
	{
		path = strPath.Left(r);
	}
	return path;
}

inline CString GetModulePath(HMODULE hMod)
{
	CString path;
	//取得程序所在路径
	TCHAR exeFullPath[MAX_PATH];
	::GetModuleFileName(hMod,exeFullPath,MAX_PATH);
	CString strPath = exeFullPath;
	int r = strPath.ReverseFind(_T('\\'));
	if (r != -1)
	{
		path = strPath.Left(r);
	}
	return path;
}

struct __POSITION { };
typedef __POSITION* POSITION;

class CFileDialogEx : public CFileDialogImpl<CFileDialog>
{
public:
	CFileDialogEx(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		HWND hWndParent = NULL)
		: CFileDialogImpl<CFileDialog>(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, hWndParent)
	{ }
	
	// override base class map and references to handlers
	DECLARE_EMPTY_MSG_MAP()
public:
	POSITION GetStartPosition() const
	{
		return (POSITION)m_ofn.lpstrFile; 
	}
	CString GetNextPathName(POSITION& pos) const
	{
		BOOL bExplorer = m_ofn.Flags & OFN_EXPLORER;
		TCHAR chDelimiter;
		if (bExplorer)
			chDelimiter = '\0';
		else
			chDelimiter = ' ';
		
		LPTSTR lpsz = (LPTSTR)pos;
		if (lpsz == m_ofn.lpstrFile) // first time
		{
			if ((m_ofn.Flags & OFN_ALLOWMULTISELECT) == 0)
			{
				pos = NULL;
				return m_ofn.lpstrFile;
			}
			
			// find char pos after first Delimiter
			while(*lpsz != chDelimiter && *lpsz != '\0')
				lpsz = _tcsinc(lpsz);
			lpsz = _tcsinc(lpsz);
			
			// if single selection then return only selection
			if (*lpsz == 0)
			{
				pos = NULL;
				return m_ofn.lpstrFile;
			}
		}
		
		CString strPath = m_ofn.lpstrFile;
		if (!bExplorer)
		{
			LPTSTR lpszPath = m_ofn.lpstrFile;
			while(*lpszPath != chDelimiter)
				lpszPath = _tcsinc(lpszPath);
			strPath = strPath.Left(lpszPath - m_ofn.lpstrFile);
		}
		
		LPTSTR lpszFileName = lpsz;
		CString strFileName = lpsz;
		
		// find char pos at next Delimiter
		while(*lpsz != chDelimiter && *lpsz != '\0')
			lpsz = _tcsinc(lpsz);
		
		if (!bExplorer && *lpsz == '\0')
			pos = NULL;
		else
		{
			if (!bExplorer)
				strFileName = strFileName.Left(lpsz - lpszFileName);
			
			lpsz = _tcsinc(lpsz);
			if (*lpsz == '\0') // if double terminated then done
				pos = NULL;
			else
				pos = (POSITION)lpsz;
		}
		
		// only add '\\' if it is needed
		if (!strPath.IsEmpty())
		{
			// check for last back-slash or forward slash (handles DBCS)
			LPCTSTR lpsz = _tcsrchr(strPath, '\\');
			if (lpsz == NULL)
				lpsz = _tcsrchr(strPath, '/');
			// if it is also the last character, then we don't need an extra
			if (lpsz != NULL &&
				(lpsz - (LPCTSTR)strPath) == strPath.GetLength()-1)
			{
				ATLASSERT(*lpsz == '\\' || *lpsz == '/');
				return strPath + strFileName;
			}
		}
		return strPath + '\\' + strFileName;
	}
	
};

class CFile
{
public:
// Constructors
	CFile();
	~CFile();
// Attributes
	DWORD GetPosition() const;
	DWORD GetLength() const;
// Operations
	BOOL Open(LPCTSTR lpszFileName, UINT nOpenFlags, LPVOID pError = NULL);
	static void PASCAL Rename(LPCTSTR lpszOldName,
				LPCTSTR lpszNewName);
	static void PASCAL Remove(LPCTSTR lpszFileName);

	LONG Seek(LONG lOff, UINT nFrom);
	void SetLength(DWORD dwNewLen);

	UINT Read(void* lpBuf, UINT nCount);
	void Write(const void* lpBuf, UINT nCount);
	DWORD ReadHuge(void* lpBuffer, DWORD dwCount);
	void WriteHuge(const void* lpBuffer, DWORD dwCount);

	void LockRange(DWORD dwPos, DWORD dwCount);
	void UnlockRange(DWORD dwPos, DWORD dwCount);
	DWORD SeekToEnd();
	void SeekToBegin();

	void Flush();
	void Close();
	void Abort();
public:
// Flag values
	enum OpenFlags {
		modeRead =         (int) 0x00000,
		modeWrite =        (int) 0x00001,
		modeReadWrite =    (int) 0x00002,
		shareCompat =      (int) 0x00000,
		shareExclusive =   (int) 0x00010,
		shareDenyWrite =   (int) 0x00020,
		shareDenyRead =    (int) 0x00030,
		shareDenyNone =    (int) 0x00040,
		modeNoInherit =    (int) 0x00080,
		modeCreate =       (int) 0x01000,
		modeNoTruncate =   (int) 0x02000,
		typeText =         (int) 0x04000, // typeText and typeBinary are
		typeBinary =       (int) 0x08000, // used in derived classes only
		osNoBuffer =       (int) 0x10000,
		osWriteThrough =   (int) 0x20000,
		osRandomAccess =   (int) 0x40000,
		osSequentialScan = (int) 0x80000,
		};

	enum Attribute {
		normal =    0x00,
		readOnly =  0x01,
		hidden =    0x02,
		system =    0x04,
		volume =    0x08,
		directory = 0x10,
		archive =   0x20
		};

	enum SeekPosition { begin = 0x0, current = 0x1, end = 0x2 };

	//enum { hFileNull = -1 };
public:
	HANDLE hFileNull;
	HANDLE	m_hFile;
	CString m_strFileName;
protected:
	BOOL	m_bCloseOnDelete;
};

//HANDLE CFile::hFileNull = NULL;

inline CFile::CFile()
{
	m_hFile = NULL;
	hFileNull = NULL;
}
inline CFile::~CFile()
{
	if (m_hFile != hFileNull && m_bCloseOnDelete)
		Close();
}
inline BOOL CFile::Open(LPCTSTR lpszFileName, UINT nOpenFlags,
				 LPVOID pError)
{
	// CFile objects are always binary and CreateFile does not need flag
	nOpenFlags &= ~(UINT)typeBinary;
	
	m_bCloseOnDelete = FALSE;
	m_hFile = hFileNull;
	m_strFileName.Empty();
	//	TCHAR szTemp[_MAX_PATH];
	//	AfxFullPath(szTemp, lpszFileName);
	//	m_strFileName = szTemp;
	DWORD dwAccess = 0;
	switch (nOpenFlags & 3)
	{
	case modeRead:
		dwAccess = GENERIC_READ;
		break;
	case modeWrite:
		dwAccess = GENERIC_WRITE;
		break;
	case modeReadWrite:
		dwAccess = GENERIC_READ|GENERIC_WRITE;
		break;
	default:
		ATLASSERT(FALSE);  // invalid share mode
	}
	
	// map share mode
	DWORD dwShareMode = 0;
	switch (nOpenFlags & 0x70)    // map compatibility mode to exclusive
	{
		//	default:
		//		ASSERT(FALSE);  // invalid share mode?
	case shareCompat:
	case shareExclusive:
		dwShareMode = 0;
		break;
	case shareDenyWrite:
		dwShareMode = FILE_SHARE_READ;
		break;
	case shareDenyRead:
		dwShareMode = FILE_SHARE_WRITE;
		break;
	case shareDenyNone:
		dwShareMode = FILE_SHARE_WRITE|FILE_SHARE_READ;
		break;
	}
	
	// Note: typeText and typeBinary are used in derived classes only.
	
	// map modeNoInherit flag
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = (nOpenFlags & modeNoInherit) == 0;
	
	// map creation flags
	DWORD dwCreateFlag;
	if (nOpenFlags & modeCreate)
	{
		if (nOpenFlags & modeNoTruncate)
			dwCreateFlag = OPEN_ALWAYS;
		else
			dwCreateFlag = CREATE_ALWAYS;
	}
	else
		dwCreateFlag = OPEN_EXISTING;
	
	// attempt file creation
	HANDLE hFile = ::CreateFile(lpszFileName, dwAccess, dwShareMode, &sa,
		dwCreateFlag, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	m_hFile = hFile;
	m_bCloseOnDelete = TRUE;
	
	return TRUE;	
}
inline UINT CFile::Read(void* lpBuf, UINT nCount)
{
	ATLASSERT(m_hFile != hFileNull);
	if (nCount == 0)
		return 0;   // avoid Win32 "null-read"
	ATLASSERT(lpBuf != NULL);
	
	DWORD dwRead;
	::ReadFile((HANDLE)m_hFile, lpBuf, nCount, &dwRead, NULL);
	
	return (UINT)dwRead;
}
inline void CFile::Write(const void* lpBuf, UINT nCount)
{
	if (nCount == 0)
		return;     // avoid Win32 "null-write" option
	
	ATLASSERT(lpBuf != NULL);
	//ASSERT(AfxIsValidAddress(lpBuf, nCount, FALSE));
	DWORD nWritten;
	if (!::WriteFile((HANDLE)m_hFile, lpBuf, nCount, &nWritten, NULL))
		return;
	
	// Win32s will not return an error all the time (usually DISK_FULL)
	if (nWritten != nCount)
		return;
	return;
}
inline LONG CFile::Seek(LONG lOff, UINT nFrom)
{
	//		ASSERT_VALID(this);
	ATLASSERT(m_hFile != hFileNull);
	ATLASSERT(nFrom == begin || nFrom == end || nFrom == current);
	ATLASSERT(begin == FILE_BEGIN && end == FILE_END && current == FILE_CURRENT);
	DWORD dwNew = ::SetFilePointer((HANDLE)m_hFile, lOff, NULL, (DWORD)nFrom);
	//if (dwNew  == (DWORD)-1)
	//	CFileException::ThrowOsError((LONG)::GetLastError());
	return dwNew;
}
inline DWORD CFile::GetPosition() const
{
	ATLASSERT(m_hFile != hFileNull);
	
	DWORD dwPos = ::SetFilePointer((HANDLE)m_hFile, 0, NULL, FILE_CURRENT);
	return dwPos;
}
inline void CFile::Flush()
{
	if (m_hFile == hFileNull)
		return;

	::FlushFileBuffers((HANDLE)m_hFile);
}
inline void CFile::Abort()
{
	if (m_hFile != hFileNull)
	{
		// close but ignore errors
		::CloseHandle((HANDLE)m_hFile);
		m_hFile = hFileNull;
	}
	m_strFileName.Empty();
}

inline void CFile::Close()
{
	//	ASSERT_VALID(this);
	ATLASSERT(m_hFile != hFileNull);
	
	BOOL bError = FALSE;
	if (m_hFile != hFileNull)
		bError = !::CloseHandle((HANDLE)m_hFile);
	
	m_hFile =  hFileNull;
	m_bCloseOnDelete = FALSE;
	m_strFileName.Empty();
}
inline void CFile::LockRange(DWORD dwPos, DWORD dwCount)
{
	ATLASSERT(m_hFile != hFileNull);
	
	::LockFile(m_hFile, dwPos, 0, dwCount, 0);
}
inline void CFile::UnlockRange(DWORD dwPos, DWORD dwCount)
{
	ATLASSERT(m_hFile != hFileNull);
	
	::UnlockFile(m_hFile, dwPos, 0, dwCount, 0);
}
inline void CFile::SetLength(DWORD dwNewLen)
{
	//	ASSERT_VALID(this);
	ATLASSERT(m_hFile != hFileNull);
	
	Seek((LONG)dwNewLen, (UINT)begin);
	
	::SetEndOfFile(m_hFile);
}
inline DWORD CFile::GetLength() const
{
	DWORD dwLen, dwCur;
	// Seek is a non const operation
	CFile* pFile = (CFile*)this;
	dwCur = pFile->Seek(0L, current);
	dwLen = pFile->SeekToEnd();
	dwCur = (DWORD)pFile->Seek(dwCur, begin);
	
	return dwLen;
}
inline void PASCAL CFile::Rename(LPCTSTR lpszOldName, LPCTSTR lpszNewName)
{
	::MoveFile((LPTSTR)lpszOldName, (LPTSTR)lpszNewName);
}

inline void PASCAL CFile::Remove(LPCTSTR lpszFileName)
{
	::DeleteFile((LPTSTR)lpszFileName);
}
inline DWORD CFile::ReadHuge(void* lpBuffer, DWORD dwCount)
{ return (DWORD)Read(lpBuffer, (UINT)dwCount); }
inline void CFile::WriteHuge(const void* lpBuffer, DWORD dwCount)
{ Write(lpBuffer, (UINT)dwCount); }
inline DWORD CFile::SeekToEnd()
{ return Seek(0, CFile::end); }
inline void CFile::SeekToBegin()
{ Seek(0, CFile::begin); }

};//namespace WTL

#endif