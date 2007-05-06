////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	Resources.h
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

#pragma once
#include "ResDialog.h"
#include "ResMenu.h"
#include "ResToolbar.h"
#include "ResAccelerators.h"


struct ResString
{
	CString m_ID;
	CString m_String;

};

struct ResBinary
{
	CString m_ID;
	CString m_FileName;
};

class CResources
{
	bool LoadString(CTextFile& file);
public:
	void Clear()
	{
		m_Dialogs.RemoveAll();
		m_Menus.RemoveAll();
		m_Toolbars.RemoveAll();
		m_Accels.RemoveAll();
		m_Icons.RemoveAll();
		m_Bitmaps.RemoveAll();
		m_Cursors.RemoveAll();
	}
	CAtlArray<CResDialog> m_Dialogs;
	CAtlArray<CResMenu> m_Menus;
	CAtlArray<CResToolbar> m_Toolbars;
	CAtlArray<CResAccelerators> m_Accels;
	CAtlArray<ResString> m_Strings;
	CAtlArray<ResBinary> m_Icons;
	CAtlArray<ResBinary> m_Bitmaps;
	CAtlArray<ResBinary> m_Cursors;

	CResources(void);
	~CResources(void);

	bool Load(LPCTSTR filename, bool bAppend = false);
};
