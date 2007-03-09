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

#pragma once

#ifndef STRICT
#define STRICT
#endif

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows 95 and Windows NT 4 or later.
#define WINVER 0x0500		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows NT 4 or later.
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target Windows 2000 or later.
#endif						

#ifndef _WIN32_IE			// Allow use of features specific to IE 4.0 or later.
#define _WIN32_IE 0x0500	// Change this to the appropriate value to target IE 5.0 or later.
#endif

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE
#define _CRT_SECURE_NO_DEPRECATE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

// turns off ATL's hiding of some common and often safely ignored warning messages
#define _ATL_ALL_WARNINGS
#define ISOLATION_AWARE_ENABLED 1

#define  _WTL_NO_CSTRING
#include <atlstr.h>
#include <atlbase.h>
#include <atlcom.h>
#include <atlsafe.h>
#include <atlcoll.h>
#include <atlapp.h>
#include <atlwin.h>
#include <atlctrls.h>
#include <atlmisc.h>
#include <atlddx.h>

using namespace ATL;

#include "Settings.h"
#include "CollSerialize.h"
#include <windows.h>
#include <objbase.h>

#pragma warning( disable : 4278 )
#pragma warning( disable : 4146 )

#ifdef _FOR_VS2005

#import "libid:1CBA492E-7263-47BB-87FE-639000619B15" version ("8.0") lcid("0") raw_interfaces_only named_guids
//The following #import imports DTE based on it's LIBID
#import "libid:80cc9f66-e7d8-4ddd-85b6-d9e6cd0e93e2" version("8.0") lcid("0") raw_interfaces_only named_guids

#else

//The following #import imports MSO based on it's LIBID
#import "libid:2DF8D04C-5BFA-101B-BDE5-00AA0044DE52" version("2.2") lcid("0") raw_interfaces_only named_guids
//The following #import imports DTE based on it's LIBID
#import "libid:80cc9f66-e7d8-4ddd-85b6-d9e6cd0e93e2" version("7.0") lcid("0") raw_interfaces_only named_guids

#endif

//Addin designer
#import "libid:AC0714F2-3D04-11D1-AE7D-00A0C90F26F4" version("7.0") lcid("0") raw_interfaces_only named_guids

#ifdef _FOR_VS2005
//The following #import imports DTE80 based on it's LIBID
#import "libid:1A31287A-4D7D-413e-8E32-3B374931BD89" version("8.0") lcid("0") raw_interfaces_only named_guids
#endif

//VC Project Model
///#import "libid:233ADBAD-405A-4249-AA0B-828093D57184" version ("7.1") lcid("0") no_namespace raw_interfaces_only named_guids
//VC Code Model
#ifdef _FOR_VS2005
#import "libid:4660A126-0E85-4506-B325-115F0FE27B0D" version ("8.0") lcid("0")
#else
#import "libid:F6A0C8E9-68E6-4483-A89D-017AFEC485DF" version ("7.1") lcid("0")
#endif
//VC Project Engine
//#import "libid:6194E01D-71A1-419F-85E3-47BA6283DD1D" version ("7.1") lcid("0") no_implementation

//wParam - BOOL is modified
#define WTLH_SETMODIFIED	(WM_USER + 500)
//wParam = HWND of the toolbar
#define WTLH_SETACTIVE		(WM_USER + 501)


#define FIRST_TOOLBAR_COMMAND	20000
//res edit
#ifdef _FOR_VS2005
#import "libid:6B96E914-4E98-44D6-BD67-173694B10F37" version("8.0") lcid("0") no_implementation
#else
#import "libid:7365C6FE-4191-476B-A3FE-1CB6A7B1C119" version("7.1") lcid("0") no_implementation
#endif


#pragma warning( default : 4278 )
#pragma warning( default : 4146 )


#define IfFailGo(x) { hr=(x); if (FAILED(hr)) goto Error; }
#define IfFailGoCheck(x, p) { hr=(x); if (FAILED(hr)) goto Error; if(p == NULL) {hr = E_FAIL; goto Error; } }

class DECLSPEC_UUID("730B33D4-7AEB-476B-9018-703AB582E457") WtlHelperLib;

enum eWTLVersion
{
	eWTL71 = 0,
	eWTL75 = 1,
	eWTL80 = 2
};

class CAddInModule : public CAtlDllModuleT< CAddInModule >,
	public CSettings<CAddInModule>
{
public:
	CAddInModule() : m_eWTLVersion(eWTL75)
	{
		m_hInstance = NULL;
	}

	DECLARE_LIBID(__uuidof(WtlHelperLib))

	inline HINSTANCE GetResourceInstance()
	{
		return m_hInstance;
	}

	inline void SetResourceInstance(HINSTANCE hInstance)
	{
		m_hInstance = hInstance;
	}
	CAtlArray<CString> m_DialogClasses;

	bool IsMacro(CString MacroName);
	bool LoadAll();
	void Destroy();

	CString m_RegMessages;
	CString m_CommonFile;
	eWTLVersion m_eWTLVersion;

	BEGIN_SETTINGS_MAP()
		SETTINGS_VARIABLE_RO(m_RegMessages)
		SETTINGS_VARIABLE_RO(m_CommonFile)
	ALT_SETTINGS_MAP(1)
		SETTINGS_OBJECT_RO(m_DialogClasses, CAtlArraySerializer<CString>)
		SETTINGS_OBJECT_RO(m_MacroMasks, CAtlArraySerializer<CString>)
	ALT_SETTINGS_MAP(2)
		SETTINGS_ENUM_OPT_RO(m_eWTLVersion)
	END_SETTINGS_MAP()
	
private:
	HINSTANCE m_hInstance;
	CAtlArray<CString> m_MacroMasks;
	bool IsMatchMask(LPCTSTR Name, LPCTSTR Mask);
};

template<class T>
class CSmartAtlArray : public CAtlArray<T>
{
public:
	CSmartAtlArray(const CSmartAtlArray<T>& ar)
	{
		Copy(ar);
	}
	CSmartAtlArray() : CAtlArray<T>(){};
	CSmartAtlArray& operator =(const CSmartAtlArray<T> ar)
	{
		Copy(ar);
		return *this;
	}
};
extern CAddInModule _AtlModule;

#ifdef _DEBUG
//profile macros
#define START_PROFILE(shortname) \
	LARGE_INTEGER start_##shortname, end_##shortname;\
	QueryPerformanceCounter(&start_##shortname);

#define END_PROFILE(shortname, str)\
	QueryPerformanceCounter(&end_##shortname);\
	__int64 res_##shortname = *(__int64*)&(end_##shortname) - *(__int64*)&(start_##shortname);\
	LARGE_INTEGER freq_##shortname; QueryPerformanceFrequency(&freq_##shortname);\
	__int64 ifreq_##shortname = *(__int64*)&(freq_##shortname);\
	double millisec_##shortname = (double)(res_##shortname * 1000) / (double)ifreq_##shortname;\
	CString str_##shortname; str_##shortname.Format(_T("\r\n%s - %f ms\r\n\r\n"), str, millisec_##shortname);\
	OutputDebugString(str_##shortname);
#else

#define	START_PROFILE(shortname)
#define END_PROFILE(str, shortname)

#endif

#ifndef _countof
#define _countof(_Array) sizeof(_Array) / sizeof(_Array[0])
#endif