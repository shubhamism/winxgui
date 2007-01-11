////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	stdafx.h
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

// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once

// Change these values to use different versions
#define WINVER		0x0400
//#define _WIN32_WINNT	0x0400
#define _WIN32_IE	0x0400
#define _RICHEDIT_VER	0x0100

#define  _WTL_NO_CSTRING
#include <atlstr.h>
#include <atlbase.h>
#include <atlapp.h>

#include <atlwin.h>

#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>

//wParam - BOOL is modified
#define WTLH_SETMODIFIED	(WM_USER + 500)


interface IWtlHelperPage
{
	virtual void UpdateToolBar(HWND hWndToolBar) = NULL;
	virtual void OnToolBarButton(int ButtonId) = NULL;
	virtual void OnSetAcrive() = NULL;
};