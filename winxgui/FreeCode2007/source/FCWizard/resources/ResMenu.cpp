////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	ResMenu.cpp
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
#include ".\resmenu.h"
//#include "../common.h"

CResMenu::CResMenu(void)
{
}

CResMenu::CResMenu(const CResMenu& parmenu)
{
	m_ID = parmenu.m_ID;
	m_String = parmenu.m_String;
	m_SubMenus.Copy(parmenu.m_SubMenus);
	m_vItems.Copy(parmenu.m_vItems);
}

CResMenu& CResMenu::operator =(const CResMenu& parmenu)
{
	m_ID = parmenu.m_ID;
	m_String = parmenu.m_String;
	m_SubMenus.Copy(parmenu.m_SubMenus);
	m_vItems.Copy(parmenu.m_vItems);
	return *this;
}

CResMenu::~CResMenu(void)
{
}

bool CResMenu::Load(CTextFile &file)
{
	int level = 0;

	CString buffer;//next line
	CString line;
	CAtlArray<CString> Words;

	while(!file.Eof())
	{
		CString word;
		if (buffer.IsEmpty())
		{
			file.ReadLine(line);
		}
		else
		{
			line = buffer;
			buffer.Empty();
		}
		
		CutString(line, Words);
		if (Words[0] == _T("BEGIN"))
		{
			continue;
		}
		if (Words[0] == _T("END"))
		{
			return true;
		}
		if (Words[0] == _T("POPUP"))
		{
			CResMenu SubMenu;
			SubMenu.m_String = Words[1];
			if (!SubMenu.Load(file))
				return false;
			m_SubMenus.Add(SubMenu);
		}
		if (Words[0] == _T("MENUITEM"))
		{
			file.ReadLine(buffer);
			buffer.TrimLeft();
			buffer.TrimRight();
			while (_tcsncmp(buffer, _T("MENUITEM"), 8) &&
				_tcsncmp(buffer, _T("POPUP"), 5) &&
				_tcsncmp(buffer, _T("BEGIN"), 5) &&
				_tcsncmp(buffer, _T("END"), 3))
			{
				//нет ключевых слов
				line += _T(" ") + buffer;
				CutString(line, Words);
				file.ReadLine(buffer);
				buffer.TrimLeft();
				buffer.TrimRight();
			}
			ResMenuItem newitem;
			if (Words.GetCount() > 1)
			{
				newitem.m_String = Words[1];
				if (newitem.m_String == _T("SEPARATOR") && Words.GetCount() == 2)
				{
				}
				else
				{
					newitem.m_String.Replace(_T("\"\""), _T("\""));
					newitem.m_ID = Words[2];
					if (Words.GetCount() > 3)
					{
						newitem.m_Style = Words[3];
					}
				}
			}
			m_vItems.Add(newitem);
		}
	}
	return false;
}