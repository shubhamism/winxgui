////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	TextFile.cpp
// Created:	21.01.2005 8:57
// 
//   Using this software in commercial applications requires an author
// permission. The permission will be granted to everyone excluding the cases
// when someone simply tries to resell the code.
//   This file may be redistributed by any means PROVIDING it is not sold for
// profit without the authors written consent, and providing that this notice
// and the authors name is included.
//   This file is provided "as is" with no expressed or implied warranty. The
// author accepts no liability if it causes any damage to you or your computer
// whatsoever.
//
////////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include ".\textfile.h"

CTextFile::CTextFile(void) : m_pBuf(NULL), m_dwSize(0), m_dwPos(0)
{
}

CTextFile::~CTextFile(void)
{
	Close();
}

BOOL CTextFile::Open(LPCTSTR lpFileName)
{
	Close();

	HRESULT hRes = m_File.Create(lpFileName, GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN);
	if (hRes != S_OK)
		return FALSE;
	ULONGLONG lSize;
	m_File.GetSize(lSize);
	m_dwSize = (DWORD)lSize;
	if (m_dwSize > 128*1024)
	{
		if (m_Mapping.MapFile(m_File) != S_OK)
		{
			return FALSE;
		}
		m_pBuf = m_Mapping;
	}
	else
	{
		m_pBuf = new char[m_dwSize];
		if (m_File.Read(m_pBuf, m_dwSize) != S_OK)
			return FALSE;
	}
	return TRUE;
}

BOOL CTextFile::ReadLine(CString& Line)
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

BOOL CTextFile::Eof()
{
	if (m_dwPos >= m_dwSize)
		return TRUE;
	else
		return FALSE;
}

void CTextFile::Close()
{
	if (m_pBuf)
	{
		if (m_dwSize > 128*1024)
		{
			m_Mapping.Unmap();
		}
		else
		{
			if (m_pBuf)
			{
				delete[] m_pBuf;
				m_pBuf = NULL;
			}
		}
		m_File.Close();
	}
	m_dwSize = 0;
	m_dwPos = 0;	
}