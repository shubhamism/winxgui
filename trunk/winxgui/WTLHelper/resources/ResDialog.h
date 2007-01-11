////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	ResDialog.h
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
#include "resbase.h"

struct ResControl
{
	CString m_Type;
	CString m_ID;
	CString m_String;
	CString m_Create;
	CString m_ExStyle;
	CString m_HelpID;
};

class CResDialog :
	public CResBase<ResControl>
{
public:
	CString m_ID;
	CString m_Style;
	CString m_ExStyle;
	CString m_Type;

	bool Load(CTextFile &file);
};
