// -------------------------------------------------------------------------
//	文件名		：	depmap.cpp
//	创建者		：	许式伟
//	创建时间	：	2002-1-28 21:06:39
//	功能描述	：	
//
// -------------------------------------------------------------------------

#include "stdafx.h"
#include "chkdep.h"

#pragma warning(disable:4786)

#include <map>

using namespace std;

// =========================================================================
// Depency Map

class KMGDepencyMap : public map<stratom, void*> {};

STDMETHODIMP_(KMGDepencyMap*) CreateDepencyMap()
{
	return new KMGDepencyMap;
}

STDMETHODIMP_(void) DestroyDepencyMap(KMGDepencyMap* pThis)
{
	KMGDepencyMap::iterator iter;
	for (iter = pThis->begin(); iter != pThis->end(); ++iter)
	{
		delete (KMGDepencyMap*)(*iter).second;
	}
	delete pThis;
}

STDMETHODIMP_(void) StartCheckDepency(stratom szFile, KCheckDepencyParam* pParam)
{
	ASSERT(!IsDepencyChecked(szFile, pParam));

	(*pParam->pDepMap)[szFile] = NULL;
}

STDMETHODIMP_(BOOL) IsDepencyChecked(stratom szFile, KCheckDepencyParam* pParam)
{
	KMGDepencyMap* pMap = pParam->pDepMap;
	KMGDepencyMap::iterator iter = pMap->find(szFile);
	return iter != pMap->end();
}

static STDMETHODIMP fnAddDepency(stratom depFile, void* pParam)
{
	KMGDepencyMap* pMap = (KMGDepencyMap*)pParam;
	(*pMap)[depFile]	= NULL;
	return S_OK;
}

STDMETHODIMP_(void) AddDepency(stratom szSrcFile, stratom szDepFile, KCheckDepencyParam* pParam)
{
	void*& value = (*pParam->pDepMap)[szSrcFile];
	if (value == NULL)
	{
		value = new KMGDepencyMap;
	}

	// 1). 将 szDepFile自身 加入
	KMGDepencyMap* pMap = (KMGDepencyMap*)value;
	(*pMap)[szDepFile]  = NULL;

	// 2). 将 szDepFile的依赖文件 加入
	ForEachDepFile(pParam->pDepMap, szDepFile, fnAddDepency, pMap);
}

STDMETHODIMP ForEachDepFile
	(
	KMGDepencyMap*	pMap,
	stratom			srcFile,
	FDepFileAction	fnAct,
	void*			pParam
	)
{
	KMGDepencyMap::iterator iterSrcFile = pMap->find(srcFile);
	if (iterSrcFile == pMap->end())	// not found
		return S_FALSE;

	KMGDepencyMap* pDepList = (KMGDepencyMap*)(*iterSrcFile).second;
	if (pDepList == NULL)	// no depfile
		return S_OK;

	KMGDepencyMap::iterator iterDepFile;
	for (iterDepFile = pDepList->begin(); iterDepFile != pDepList->end(); ++iterDepFile)
	{
		fnAct((*iterDepFile).first, pParam);
	}
	return S_OK;
}

#if defined(_DEBUG)
STDMETHODIMP fnDumpDepency(stratom depFile, void* pParam)
{
	TRACE("\tdepFile = %s\n", depFile);
	return S_OK;
}
STDMETHODIMP_(void) DumpDepency(KMGDepencyMap* pMap, stratom szFile)
{
	ForEachDepFile(pMap, szFile, fnDumpDepency, NULL);
}
#endif

// =========================================================================
