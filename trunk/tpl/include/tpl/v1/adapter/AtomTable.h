/* -------------------------------------------------------------------------
// WINX: a C++ template GUI library - MOST SIMPLE BUT EFFECTIVE
// 
// This file is a part of the WINX Library.
// The use and distribution terms for this software are covered by the
// Common Public License 1.0 (http://opensource.org/licenses/cpl.php)
// which can be found in the file CPL.txt at this distribution. By using
// this software in any fashion, you are agreeing to be bound by the terms
// of this license. You must not remove this notice, or any other, from
// this software.
// 
// Module: tpl/v1/adapter/AtomTable.h
// Creator: xushiwei
// Email: xushiweizh@gmail.com
// Date: 4/26/2003 5:08:43 PM
// 
// $Id: AtomTable.h,v 1.1 2006/12/02 06:44:18 xushiwei Exp $
// -----------------------------------------------------------------------*/
#ifndef __TPL_V1_ADAPTER_ATOMTABLE_H__
#define __TPL_V1_ADAPTER_ATOMTABLE_H__

#ifndef _MAP_
#include <map>
#endif

#ifndef _STRING_
#include <string>
#endif

// -------------------------------------------------------------------------

template <class _String>
class KStringAtomTable
{
public:
	typedef _String String;
	typedef typename _String::value_type char_type;
	typedef typename _String::size_type size_type;	
	typedef const char_type* Pointer;
	typedef Pointer Atom;
	
protected:
	typedef std::map<String, Atom> _Impl;
	_Impl _map;

public:
	STDMETHODIMP_(Atom) AddAtom(Pointer key)
	{
		typename _Impl::value_type value(key, NULL);
		typename _Impl::iterator it = _map.insert(value).first;
		if ((*it).second == NULL) // add new atom...
		{
			(*it).second = (Atom)(*it).first.c_str();
		}
		return (*it).second;
	}
	STDMETHODIMP_(Atom) AddAtom(const String& key)
	{
		typename _Impl::value_type value(key, NULL);
		typename _Impl::iterator it = _map.insert(value).first;
		if ((*it).second == NULL) // add new atom...
		{
			(*it).second = (Atom)(*it).first.c_str();
		}
		return (*it).second;
	}
	static STDMETHODIMP_(Pointer) AtomString(Atom atomid)
	{
		return (Pointer)atomid;
	}
};

// -------------------------------------------------------------------------
// $Log: AtomTable.h,v $
// Revision 1.1  2006/12/02 06:44:18  xushiwei
// Text Processing Library - Version 1.0
//

#endif /* __TPL_V1_ADAPTER_ATOMTABLE_H__ */
