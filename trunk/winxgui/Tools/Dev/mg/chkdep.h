// -------------------------------------------------------------------------
//	文件名		：	chkdep.h
//	创建者		：	许式伟
//	创建时间	：	2002-1-29 14:03:34
//	功能描述	：	
//
// -------------------------------------------------------------------------
#ifndef __CHKDEP_H__
#define __CHKDEP_H__

#include "stratom.h"

class KMGDepencyMap;

STDMETHODIMP_(KMGDepencyMap*) CreateDepencyMap();
STDMETHODIMP_(void) DestroyDepencyMap(KMGDepencyMap* pThis);

struct tagKCheckDepencyParam
{
	LPCTSTR*		szIncDirs;
	UINT			nIncDirs;
	KMGDepencyMap*	pDepMap;
	stratomtbl		tblAtom;
};
typedef struct tagKCheckDepencyParam KCheckDepencyParam;

// public:
STDMETHODIMP CheckDepency(stratom srcFile, KCheckDepencyParam* pParam);

typedef HRESULT (__stdcall* FDepFileAction)(stratom depFile, void* pParam);
STDMETHODIMP ForEachDepFile	// enum depfile, useful.
	(
	KMGDepencyMap*	pMap,
	stratom			srcFile,
	FDepFileAction	fnAct,
	void*			pParam
	);

// private:
STDMETHODIMP_(void) StartCheckDepency(stratom szFile, KCheckDepencyParam* pParam);
STDMETHODIMP_(BOOL) IsDepencyChecked(stratom szFile, KCheckDepencyParam* pParam);
STDMETHODIMP_(void) AddDepency(stratom srcFile, stratom depFile, KCheckDepencyParam* pParam);

STDMETHODIMP_(BOOL) IsFileExist(LPCTSTR szFile);
STDMETHODIMP LookupDepFile(LPTSTR szDepFile, FILE* fpSrc, BOOL* pfCheckCurDir);
STDMETHODIMP_(void) DumpDepency(KMGDepencyMap* pMap, stratom szFile);

#endif // __CHKDEP_H__
