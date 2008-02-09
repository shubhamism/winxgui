// -------------------------------------------------------------------------
//	文件名		：	stratom.h
//	创建者		：	许式伟
//	创建时间	：	2002-1-29 13:01:26
//	功能描述	：	
//
// -------------------------------------------------------------------------
#ifndef __STRATOM_H__
#define __STRATOM_H__

struct tagStringAtomTbl	{};
struct tagStringAtom	{};

typedef tagStringAtomTbl*	stratomtbl;
typedef tagStringAtom*		stratom;

STDMETHODIMP_(stratomtbl) CreateAtomTable();
STDMETHODIMP_(stratom)	AddStringAtom(stratomtbl pTbl, LPCTSTR key);
STDMETHODIMP_(LPCTSTR)	GetAtomString(stratomtbl pTbl, stratom atomid);
STDMETHODIMP_(void)		DestroyAtomTable(stratomtbl pTbl);

inline
STDMETHODIMP_(LPCTSTR) GetAtomString(stratomtbl pTbl, stratom atomid)
{
	return (LPCTSTR)atomid;
}

// -------------------------------------------------------------------------

#endif // __STRATOM_H__
