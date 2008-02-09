/* -------------------------------------------------------------------------
//	文件名		：	adapter/AtomTable.h
//	创建者		：	许式伟
//	创建时间	：	4/26/2003 5:08:43 PM
//	功能描述	：	
//
// -----------------------------------------------------------------------*/
#ifndef __TEXT_ADAPTER_ATOMTABLE_H__
#define __TEXT_ADAPTER_ATOMTABLE_H__

#ifndef __TEXT_ADAPTER_STLADAPTER_H__
#include "STLAdapter.h"
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

#endif /* __TEXT_ADAPTER_ATOMTABLE_H__ */
