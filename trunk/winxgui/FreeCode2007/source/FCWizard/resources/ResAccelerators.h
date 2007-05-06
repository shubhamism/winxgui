////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	ResAccelerators.h
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
#include "ResBase.h"

#define MODIFIER_ALT	1
#define MODIFIER_CTRL	2
#define MODIFIER_SHIFT	4

struct  ResAccel
{
	CString m_Key;
	CString m_ID;
	CString m_Type;
	int Modifires;
	CString Flags;
};


class CResAccelerators :
	public CResBase<ResAccel>
{
public:
	CString m_ID;
	CResAccelerators(void);
	~CResAccelerators(void);

	bool Load(CTextFile& file);
};
