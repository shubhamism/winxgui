////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	ResDialog.cpp
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
#include ".\resdialog.h"

bool CResDialog::Load(CTextFile &file)
{
	CString buffer;
	CString line;
	while(!file.Eof())
	{
		//Read styles...

		if(buffer.IsEmpty())
		{
			file.ReadLine(line);
		}
		else
		{
			line = buffer;
			buffer.Empty();
		}
		
		CAtlArray<CString> Words;
		CutString(line, Words);
		CString word = Words[0];

		if(word == _T("STYLE") || word == _T("EXSTYLE"))
		{
			//Read the following lines, maybe more data there
			while(!file.Eof())
			{
				file.ReadLine(buffer);
				int iStart = 0;
				CString str = TokenizeString(buffer,_T(" \t,"), iStart);
			
				if(	str != _T("FONT") && 
					str != _T("BEGIN") &&
					str != _T("STYLE") &&
					str != _T("CAPTION") &&
					str != _T("EXSTYLE"))
				{
					
					line += buffer;
					buffer.Empty();
				}
				else
					break;
			}

			CutString(line, Words);

			if(word == _T("STYLE"))
				m_Style = Words[1];
			else 
				if(word == _T("EXSTYLE"))
				{
					m_ExStyle = Words[1];
				}

		}
			else if (word == _T("MENU"))
			{
				m_Menu = Words[1];
			}	
		else 
			if(word == _T("BEGIN"))
			break;

	}

	CAtlArray<CString> lines;

	//Read all lines until "END"
	while(!file.Eof())
	{
		file.ReadLine(line);
		line.TrimLeft();
		line.TrimRight();
		if (line == _T("END"))
			break;

		lines.Add(line);
	}

	int startline = 0;

	LPCTSTR starties[] = {_T("CONTROL"),
		_T("LTEXT"),
		_T("RTEXT"),
		_T("CTEXT"),
		_T("ICON"),
		_T("GROUPBOX"),
		_T("PUSHBUTTON"),
        _T("DEFPUSHBUTTON"),
		_T("EDITTEXT"),
		_T("COMBOBOX"),
		_T("LISTBOX"),
		_T("SCROLLBAR")};

	while(startline < (int)lines.GetCount())
	{
		line = lines[startline];
		startline++;

		//Add more lines?
		while(startline < (int)lines.GetCount())
		{
			//Do next line start with a magic word?
			bool magic = false;
			int iStart = 0;
			CString nextstart = TokenizeString(lines[startline],_T(" \t,"), iStart);

			for(int i = 0; i < sizeof(starties) / sizeof(LPCTSTR); i++)
				if(nextstart == starties[i])
				{
					magic=true;
					break;
				}

				if(!magic)
				{
					line += _T(" ");
					line += lines[startline];
					startline++;
				}
				else
					break;
		}

		CAtlArray<CString> Words;
		CAtlArray<CString> Words2;
		CutString(line, Words2, _T(","));
		CString word = Words2[0];
		CutString(word, Words, _T(" "));
		Words2.RemoveAt(0);
		Words.Append(Words2);
		word = Words[0];
		if (word == _T("CONTROL") ||
			word == _T("LTEXT") ||
			word == _T("RTEXT") ||
			word == _T("CTEXT") ||
			word == _T("GROUPBOX") ||
			word == _T("PUSHBUTTON") ||
			word == _T("DEFPUSHBUTTON") ||
			word == _T("ICON"))
		{
			ResControl newcontrol;
			newcontrol.m_ID = Words[2];
			newcontrol.m_ID.TrimLeft();
			newcontrol.m_ID.TrimRight();
			newcontrol.m_String = Words[1];

			if(word == _T("CONTROL"))
			{
				newcontrol.m_Type = Words[3];
				newcontrol.m_Type.TrimLeft(_T("\""));
				newcontrol.m_Type.TrimRight(_T("\""));
				newcontrol.m_Create = Words[4];
				if (Words.GetCount() > 9)
				{
					newcontrol.m_ExStyle  = Words[9];
					if (Words.GetCount() > 10)
						newcontrol.m_HelpID = Words[10];
				}
			}
			else
			{
				newcontrol.m_Type = word;
				if (Words.GetCount() > 7)
				{
					newcontrol.m_Create = Words[7];
					if (Words.GetCount() > 8)
					{
						newcontrol.m_ExStyle  = Words[8];
						if (Words.GetCount() > 9)
							newcontrol.m_HelpID = Words[9];
					}
				}
			}
			m_vItems.Add(newcontrol);
		}
		else 
			if(	word == _T("EDITTEXT") ||
			word == _T("COMBOBOX") ||
			word == _T("LISTBOX") ||
			word == _T("SCROLLBAR"))
		{
			ResControl newcontrol;
			newcontrol.m_ID = Words[1];

			newcontrol.m_Type = word;
			if (Words.GetCount() > 6)
			{
				newcontrol.m_Create = Words[6];
				if (Words.GetCount() > 7)
				{
					newcontrol.m_ExStyle  = Words[7];
					if (Words.GetCount() > 8)
						newcontrol.m_HelpID = Words[8];
				}
			}
			m_vItems.Add(newcontrol);
		}
		else if( word == _T("END") )
			return true;
	}
	return false;
}