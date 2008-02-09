// -------------------------------------------------------------------------
//	文件名		：	StringList.cpp
//	创建者		：	许式伟
//	创建时间	：	2002-1-29 14:19:21
//	功能描述	：	
//
// -------------------------------------------------------------------------

#include "stdafx.h"

#pragma warning(disable:4786)

#include <string>
#include <list>

using namespace std;

// =========================================================================
// DepFile List

class KMGStringList : public list<tstring> {};

STDMETHODIMP_(KMGStringList*) CreateStringList()
{
	return new KMGStringList;
}

STDMETHODIMP_(void) DestroyStringList(KMGStringList* pList)
{
	delete pList;
}

STDMETHODIMP_(void) AddString(KMGStringList* pThis, LPCTSTR szDepFile)
{
	pThis->push_back(tstring(szDepFile));
}

// =========================================================================
// Helper: LinkProduct

const TCHAR g_szLinkProductStart[] =
_T(
	"\n"
	"Objects ="
);

const TCHAR g_szLinkProductEnd[] =
_T(
   "\n\n"
   "$(Product) : $(Objects) $(Libs)\n" 
	"	@echo \"---> Creating\" $@ \"...\"\n"
	"	@rm -f $@\n"
	"	$(Link) $(Objects) $(Libraries)\n"
	"	$(CheckLink)\n"
	"\n"
);

const TCHAR g_szNewLine[] = _T("\t\\\n\t");
const TCHAR g_szStringFmt[] = _T("%s");

STDMETHODIMP LinkProduct(FILE* fpDest, KMGStringList* pObjList)
{
	KMGStringList::iterator iter;

	_ftprintf(fpDest, g_szLinkProductStart);
	for (iter = pObjList->begin(); iter != pObjList->end(); ++iter)
	{
		_ftprintf(fpDest, g_szNewLine);
		_ftprintf(fpDest, g_szStringFmt, iter->c_str());
	}
	_ftprintf(fpDest, g_szLinkProductEnd);
	return S_OK;
}

// =========================================================================
