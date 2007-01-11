////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	ResAccelerators.cpp
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
#include ".\resaccelerators.h"
#include "../common.h"

CResAccelerators::CResAccelerators(void)
{
}

CResAccelerators::~CResAccelerators(void)
{
}

bool CResAccelerators::Load(CTextFile& file)
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

	while(!file.Eof())
	{
		file.ReadLine(line);
		line.Trim();
		CAtlArray<CString> Words;
		CutString(line, Words, _T(","));
		CString word = Words[0];
		word.Trim();

		if(word == _T("END"))
			return true;
		
		for (size_t i = 1; i < Words.GetCount(); i++)
		{
			Words[i].Trim();
		}
		while (Words[Words.GetCount() - 1].IsEmpty())
		{
			//need next line
			do 
			{
				file.ReadLine(line);
				line.Trim();
			} while(line.IsEmpty() && !file.Eof());
			if (file.Eof())
				return false;
			CAtlArray<CString> nextWords;
			CutString(line, nextWords, _T(","));
			for (size_t i = 0; i < nextWords.GetCount(); i++)
			{
				nextWords[i].Trim();
			}
			Words.Append(nextWords);
		}

		ResAccel item;
		item.Modifires = 0;
		item.m_Key = word;
		if (Words.GetCount() > 1)
		{
			item.m_ID = Words[1];
			if (Words.GetCount() > 2)
			{
				item.m_Type = Words[2];
				size_t iCurWord = 3;
				while(iCurWord < Words.GetCount())
				{
					if (Words[iCurWord] == _T("ALT"))
					{
						item.Modifires |= MODIFIER_ALT;
						iCurWord++;
						continue;
					}
					if (Words[iCurWord] == _T("CONTROL"))
					{
						item.Modifires |= MODIFIER_CTRL;
						iCurWord++;
						continue;
					}
					if (Words[iCurWord] == _T("SHIFT"))
					{
						item.Modifires |= MODIFIER_SHIFT;
						iCurWord++;
						continue;
					}
					break;
				}
				if (iCurWord < Words.GetCount())
				{
					item.Flags = Words[iCurWord];
				}
			}
		}
		m_vItems.Add(item);

	}
	return false;
}