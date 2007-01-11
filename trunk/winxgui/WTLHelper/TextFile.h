////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	TextFile.h
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

#pragma once

#include <atlfile.h>

class CTextFile
{
	CAtlFile m_File;
	CAtlFileMapping<char> m_Mapping;
	char* m_pBuf;
	DWORD m_dwSize;
	DWORD m_dwPos;
public:
	CTextFile(void);
	~CTextFile(void);
	
	BOOL Open(LPCTSTR lpFileName);
	BOOL ReadLine(CString& Line);
	BOOL Eof();
	void Close();
};
