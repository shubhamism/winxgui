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
// Module: tpl/v1/script_variant.h
// Creator: xushiwei
// Email: xushiweizh@gmail.com
// Date: 4/24/2003 12:44:57 AM
// 
// $Id: script_variant.h,v 1.1 2006/12/02 06:44:19 xushiwei Exp $
// -----------------------------------------------------------------------*/
#ifndef __TPL_V1_SCRIPT_VARIANT_H__
#define __TPL_V1_SCRIPT_VARIANT_H__

#ifndef __TPL_V1_ADAPTER_ATOMTABLE_H__
#include "adapter/AtomTable.h"
#endif

#ifndef _LIST_
#include <list>
#endif

// -------------------------------------------------------------------------

template <class _Atom, class _Variant>
struct KVariantNode
{
	typedef _Atom Atom;
	typedef _Variant Variant;
	typedef typename _Variant::NodeList NodeList;
	_Atom name;
	_Variant value;
};


template <class _String>
struct KVariant
{
	typedef _String String;
	typedef KVariant<_String> _Myt;

	typedef KStringAtomTable<String> AtomTable;
	typedef typename AtomTable::Atom Atom;
	typedef typename AtomTable::Pointer Pointer;

	typedef KVariantNode<Atom, _Myt> Node;
	typedef std::list<Node> NodeList;
	
	int vt;
	union
	{
		int intVal;
		Atom atomVal;
		NodeList* lstVal;
		void* lpVal;
	};

	enum VariantType
	{
		vtNone		= 0,
		vtInt		= 1,
		vtAtom		= 2,
		vtElement	= 3,
	};
	
	KVariant() : vt(vtNone) {}
	KVariant(int intValA) : vt(vtInt) { intVal = intValA; }
	KVariant(Atom strValA) : vt(vtAtom) { lpVal = strValA; }
	KVariant(NodeList* lstValA) : vt(vtElement) { lpVal = lstValA; }
	KVariant(const KVariant& varA) : vt(varA.vt) { lpVal = varA.lpVal; }

	class RecycleBin
	{
	public:
		typedef KVariant Variant;
		
	protected:
		AtomTable _atoms;
		std::AutoFreeAlloc _alloc;
		
#if defined(_DEBUG)
	public:
		RecycleBin() {
			static nCount = 0;
			TRACEA("----> %d) KVariant::RecycleBin Construct...\n", ++nCount);
		}
		~RecycleBin() {
			static nCount = 0;
			TRACEA("----> %d) KVariant::RecycleBin Destruct...\n", ++nCount);
		}
#endif
	public:
		STDMETHODIMP_(Atom) NewAtom(Pointer val)
		{
			return _atoms.AddAtom(val);
		}
		STDMETHODIMP_(Atom) NewAtom(const String& val)
		{
			return _atoms.AddAtom(val);
		}
		STDMETHODIMP_(NodeList*) NewVariantList()
		{
			return STD_NEW(_alloc, NodeList);
		}
		STDMETHODIMP_(Variant*) NewVariant()
		{
			return STD_NEW(_alloc, Variant);
		}
		STDMETHODIMP_(Variant*) NewVariant(Pointer strVal)
		{
			return STD_NEW(_alloc, Variant)( NewAtom(strVal) );
		}
		STDMETHODIMP_(Variant*) NewVariant(const String& strVal)
		{
			return STD_NEW(_alloc, Variant)( NewAtom(strVal) );
		}
		STDMETHODIMP_(Variant*) NewVariant(NodeList* lstVal)
		{
			return STD_NEW(_alloc, Variant)(lstVal);
		}
	public:
		STDMETHODIMP_(void) Delete(NodeList* pList)
		{
		}
	};
};

// -------------------------------------------------------------------------

template <class Variant, class String>
STDMETHODIMP ChangeTypeToString(const Variant& var, String& str)
{
	if (var.vt == Variant::vtAtom)
	{
		str = var.atomVal;
	}
	else if (var.vt == Variant::vtInt)
	{
		IntToString(str, var.intVal, 10);
	}
	else
		return E_INVALIDARG;
	return S_OK;
}

template <class Variant, class IntType>
STDMETHODIMP ChangeTypeToInt(const Variant& var, IntType& intVal)
{
	if (var.vt == Variant::vtInt)
	{
		intVal = var.intVal;
	}
	else
		return E_INVALIDARG;
	return S_OK;
}

// -------------------------------------------------------------------------
// $Log: script_variant.h,v $
// Revision 1.1  2006/12/02 06:44:19  xushiwei
// Text Processing Library - Version 1.0
//

#endif /* __TPL_V1_SCRIPT_VARIANT_H__ */
