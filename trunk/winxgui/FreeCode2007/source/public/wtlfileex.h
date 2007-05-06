//Email : QWL1996@GMAIL.COM
//Time  : 2007-2-16
//CTextFile port for WTLHelper

#ifndef _WTL_FILEEX_H__
#define _WTL_FILEEX_H__

#include "wtlfile.h"

#pragma once

namespace WTL
{

class CTextFile
{
protected:
	CFile m_File;
	char* m_pBuf;
	DWORD m_dwSize;
	DWORD m_dwPos;
public:
	CTextFile(void);
	~CTextFile(void);
	BOOL Open(LPCTSTR lpFileName, UINT uOpenFlags = CFile::modeRead| CFile::shareDenyNone);
	BOOL ReadLine(CString& Line);
	BOOL Eof();
	void Close();
};

inline CTextFile::CTextFile(void) : m_pBuf(NULL), m_dwSize(0), m_dwPos(0)
{
}

inline CTextFile::~CTextFile(void)
{
	Close();
}

inline BOOL CTextFile::Open(LPCTSTR lpFileName, UINT uOpenFlags)
{
	Close();

	if (!m_File.Open(lpFileName, uOpenFlags, NULL))
		return	FALSE;
	ULONGLONG lSize = m_File.GetLength();
	m_dwSize = (DWORD)lSize;
	m_pBuf = new char[m_dwSize];
	if (m_File.Read(m_pBuf, m_dwSize) != m_dwSize)
		return FALSE;
	return TRUE;
}

inline BOOL CTextFile::ReadLine(CString& Line)
{
	if (m_dwPos >= m_dwSize)
		return FALSE;
	DWORD dwPos = m_dwPos;
	while(dwPos < m_dwSize)
	{
		if (m_pBuf[dwPos] == '\n')
		{
			DWORD Len = dwPos - m_dwPos;
			if (m_pBuf[dwPos - 1] == '\r' && Len)
				Len--;
			if (Len)
				Line = CString(m_pBuf + m_dwPos, Len);
			else
				Line.Empty();
			m_dwPos = dwPos + 1;
			return TRUE;
		}
		dwPos++;
	}
	Line = CString(m_pBuf + m_dwPos, dwPos - m_dwPos);
	m_dwPos = dwPos;
	return TRUE;
}

inline BOOL CTextFile::Eof()
{
	if (m_dwPos >= m_dwSize)
		return TRUE;
	else
		return FALSE;
}

inline void CTextFile::Close()
{
	if (m_pBuf)
	{
		if (m_pBuf)
		{
			delete[] m_pBuf;
			m_pBuf = NULL;
		}
		m_File.Close();
	}
	m_dwSize = 0;
	m_dwPos = 0;	
}

} //namespace WTL;
#endif