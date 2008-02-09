// -------------------------------------------------------------------------
//	文件名		：	stratom.cpp
//	创建者		：	许式伟
//	创建时间	：	2002-1-29 13:24:36
//	功能描述	：	
//
// -------------------------------------------------------------------------

#include "stdafx.h"

#pragma warning(disable:4786)

#include <string>
#include <map>
#include "stratom.h"

#if !defined(tstring)
#	if defined(UNICODE)
#		define tstring		wstring
#	else
#		define tstring		string
#	endif
#endif

using namespace std;

// -------------------------------------------------------------------------

class KStringAtomMap : public map<tstring, stratom>
{
};

STDMETHODIMP_(stratomtbl) CreateAtomTable()
{
	return (stratomtbl)new KStringAtomMap;
}

STDMETHODIMP_(stratom) AddStringAtom(stratomtbl pTbl, LPCTSTR key)
{
	KStringAtomMap* pMap = (KStringAtomMap*)pTbl;

	stratom& value = (*pMap)[key];
	if (value == NULL)
	{
		// add new atom...
		KStringAtomMap::iterator iter = pMap->find(key);
		value = (stratom)(*iter).first.c_str();
	}
	return value;
}

STDMETHODIMP_(void) DestroyAtomTable(stratomtbl pTbl)
{
	delete (KStringAtomMap*)pTbl;
}

// -------------------------------------------------------------------------
