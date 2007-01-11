////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	Resources.cpp
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
#include ".\resources.h"
#include "../common.h"

CResources::CResources(void)
{
}

CResources::~CResources(void)
{
}

bool CResources::Load(LPCTSTR filename, bool bAppend /* = false */)
{
	CTextFile file;
	if (!bAppend)
	{
		m_Dialogs.RemoveAll();
		m_Menus.RemoveAll();
		m_Toolbars.RemoveAll();
		m_Accels.RemoveAll();
		m_Icons.RemoveAll();
		m_Bitmaps.RemoveAll();
		m_Cursors.RemoveAll();
	}
	if(!file.Open(filename))
	{
		return false;
	}

	while(!file.Eof())
	{
		CString line;
		file.ReadLine(line);
		if (line.IsEmpty())
			continue;
		line.TrimLeft();
		if (line.GetLength() >= 2 && line[0] == _T('/') && line[1] == _T('/'))
			continue;
		if (line[0] == _T('#'))
			continue;

		CAtlArray<CString> Words;
		CutString(line, Words);
		{
			CString word;
			if (Words.GetCount() > 1)
			{
				word = Words[1];
			}
			else
			{
				word.Empty();
			}
			if (word == _T("DESIGNINFO"))
			{
				//skip disign info
				while(!file.Eof())
				{
					file.ReadLine(line);
					line.Trim();
					if (line == _T("BEGIN"))
						break;
				}
				if (file.Eof())
					return false;
				int Level = 1;
				while(!file.Eof() && Level)
				{
					file.ReadLine(line);
					line.Trim();
					if (line == _T("BEGIN"))
						Level++;
					if (line == _T("END"))
						Level--;
				}
				if (Level)
					return false;
				else
					continue;
			}

			if(word == _T("MENU"))
			{
				CResMenu newmenu;
				newmenu.m_ID = Words[0];
				newmenu.Load(file);

				m_Menus.Add(newmenu);
			}
			else if( word == _T("TOOLBAR") )
			{
				CResToolbar newtoolbar;
				newtoolbar.m_ID = Words[0];
				newtoolbar.Load(file);

				m_Toolbars.Add(newtoolbar);
			}
			else if( (word == _T("DIALOG"))
				|| word == _T("DIALOGEX")
				)
			{
				CResDialog newdialog;
				newdialog.m_ID = Words[0];
				newdialog.m_Type = word;
				newdialog.Load(file);

				m_Dialogs.Add(newdialog);
			}
			else if( word == _T("BITMAP") || 
				word == _T("ICON") ||
				word == _T("CURSOR")
				)
			{
				ResBinary m_simple;
				m_simple.m_ID = Words[0];

				if(word == _T("BITMAP"))
					m_Bitmaps.Add(m_simple);
				else if(word == _T("ICON"))
					m_Icons.Add(m_simple);
				else
					m_Cursors.Add(m_simple);
			}
			else if(word == _T("ACCELERATORS"))
			{
				CResAccelerators accels;
				accels.m_ID = Words[0];
				accels.Load(file);
				m_Accels.Add(accels);
			}
			else 
			{
				if(Words.GetCount() > 0 && (Words[0] == _T("STRINGTABLE")))
				{
					LoadString(file);
				}
			}
		}
	}
	return true;
}

bool CResources::LoadString(CTextFile& file)
{
	while(!file.Eof())
	{
		CString line;
		file.ReadLine(line);
		line.Trim();
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

		if(word == _T("END"))
			return true;
		
		ResString item;
		item.m_ID = word;
		if (Words.GetCount() > 1)
		{
			item.m_String = Words[1];
		}
	}
	return false;
}