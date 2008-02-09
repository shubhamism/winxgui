// -------------------------------------------------------------------------
//	文件名		：	makegen.h
//	创建者		：	许式伟
//	创建时间	：	2002-1-29 19:26:08
//	功能描述	：	
//
// -------------------------------------------------------------------------
#ifndef __MAKEGEN_H__
#define __MAKEGEN_H__

#include "chkdep.h"

typedef HRESULT (__stdcall *FSectionHanlder)(FILE* fpList, struct tagKHandlerParam* pParam);

#define MG_LINE_MAX			2048
#define MG_KEYWORD_MAX		128
#define MG_INCDIR_MAX		128
#define MG_LIBDIR_MAX		128

#define E_PRODTYPE_ERROR	E_FAIL
#define E_PRODUCT_ERROR		E_FAIL
#define E_OBJDIR_ERROR		E_FAIL
#define E_PRODDIR_ERROR		E_FAIL
#define E_CFGPARAM_ERROR	E_FAIL

class KMGStringList;
class KMGDepencyMap;

struct tagKHandlerParam : public KCheckDepencyParam
{
	LPCTSTR*		szLibDirs;
	UINT			nLibDirs;

	KMGStringList*	pObjList;
	
	FILE*			fpDest;
	FSectionHanlder	fnHandler;
	LPTSTR			szSecParam;
	LPCTSTR			szConfigReq;
	LPCTSTR			szProjPath;
	
	BOOL			fUseQTMoc;	// QT的Moc文件
	BOOL			fCheckDepency;
};
typedef struct tagKHandlerParam KHandlerParam;

typedef struct tagKSectionHandler
{
	LPCTSTR			szSection;
	FSectionHanlder fnHandler;
} KSectionHandler;

STDMETHODIMP GetSection(LPTSTR szLine, FILE* fpList, KHandlerParam* pParam);
STDMETHODIMP SkipSection(FILE* fpList, KHandlerParam* pParam);

STDMETHODIMP_(KMGStringList*) CreateStringList();
STDMETHODIMP_(void) DestroyStringList(KMGStringList* pList);
STDMETHODIMP_(void) AddString(KMGStringList* pThis, LPCTSTR szDepFile);
STDMETHODIMP LinkProduct(FILE* fpDest, KMGStringList* pObjList);

extern const TCHAR g_szSeps[];
extern const TCHAR g_szOptSeps[];

STDMETHODIMP HandleSec_Include(FILE* fpList, KHandlerParam* pParam);
STDMETHODIMP HandleSec_Lib(FILE* fpList, KHandlerParam* pParam);
STDMETHODIMP HandleSec_Source(FILE* fpList, KHandlerParam* pParam);
STDMETHODIMP HandleSec_Config(FILE* fpList, KHandlerParam* pParam);

#endif // __MAKEGEN_H__
