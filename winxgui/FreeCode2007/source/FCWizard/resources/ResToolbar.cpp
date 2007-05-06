////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	ResToolbar.cpp
// Created:	16.11.2004 8:55
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
#include ".\restoolbar.h"

CResToolbar::CResToolbar(void)
{
}

CResToolbar::~CResToolbar(void)
{
}

bool CResToolbar::Load(CTextFile& file)
{
	CString line;
	while(!file.Eof())
	{
		file.ReadLine(line);
		if (line == _T("BEGIN"))
			break;
	}
	if (file.Eof())
		return false;
	
	int sepcount = 0;

	while(!file.Eof())
	{
		CString line;
		file.ReadLine(line);
		CAtlArray<CString> Words;
		CutString(line, Words);
		CString word = Words[0];

		if(word == _T("BUTTON") || word == _T("SEPARATOR"))
		{
			ResToolbarItem item;

			item.m_Type = word;

			if(word == _T("BUTTON"))
			{
				if (Words.GetCount() > 1)
				{
					item.m_ID = Words[1];
				}
				m_vItems.Add(item);
			}
						
		}
		else if(word == _T("END"))
			return true;
	}
	return false;
}