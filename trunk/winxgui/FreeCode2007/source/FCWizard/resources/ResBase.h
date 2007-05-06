////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	ResBase.h
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

#include "reshelper.h"

enum ResType
{
	RES_MENUITEM,
	RES_CONTROL
};

struct ResBase
{
	virtual ResType GetResType() = 0;
};

template<class T>
class CResBase
{
protected:
	CAtlArray<T> m_vItems;
public:
	CResBase()	{};
	CResBase(const CResBase<T>& base)
	{
		//m_vItems = base.m_vItems;
		m_vItems.Copy(base.m_vItems);
	}
	size_t GetCount() const
	{
		return m_vItems.GetCount();
	}

	const T& GetAt(size_t index) const
	{
		return m_vItems.GetAt(index);
	}
};
