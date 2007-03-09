// src\CodeModel.h : Declaration of the CCodeModel

#ifndef __CODEMODEL_H_
#define __CODEMODEL_H_

#include "resource.h"       // main symbols
#include "codemodel_i.h"

/////////////////////////////////////////////////////////////////////////////
// CCodeModel
class ATL_NO_VTABLE CCodeModel : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCodeModel, &CLSID_CCodeModel>,
	public IDispatchImpl<CodeModel, &IID_CodeModel, &LIBID_CODEMODELLib>
{
public:
	CCodeModel()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CODEMODEL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCodeModel)
	COM_INTERFACE_ENTRY(CodeModel)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// CodeModel
public:
    STDMETHODIMP get_CodeElements( 
        /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *ppCodeElements);
    
    STDMETHODIMP get_IsCaseSensitive( 
        /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pSensitive);
    
    STDMETHODIMP Remove( 
        /* [in] */ VARIANT Element);
    
    STDMETHODIMP AddNamespace( 
        /* [in] */ BSTR Name,
        /* [in] */ VARIANT Location,
        /* [in] */ VARIANT Position,
        /* [retval][out] */ CodeNamespace __RPC_FAR *__RPC_FAR *ppCodeNamespace);
    
    STDMETHODIMP AddClass( 
        /* [in] */ BSTR Name,
        /* [in] */ VARIANT Location,
        /* [in] */ VARIANT Position,
        /* [in] */ VARIANT Bases,
        /* [in] */ VARIANT ImplementedInterfaces,
        /* [retval][out] */ CodeClass __RPC_FAR *__RPC_FAR *ppCodeClass);
    
    STDMETHODIMP AddFunction( 
        /* [in] */ BSTR Name,
        /* [in] */ VARIANT Location,
        /* [in] */ enum vsCMFunction Kind,
        /* [in] */ VARIANT Type,
        /* [in] */ VARIANT Position,
        /* [in] */ enum vsCMAccess Access,
        /* [retval][out] */ CodeFunction __RPC_FAR *__RPC_FAR *ppCodeFunction);
    
    STDMETHODIMP AddVariable( 
        /* [in] */ BSTR Name,
        /* [in] */ VARIANT Location,
        /* [in] */ VARIANT Type,
        /* [in] */ VARIANT Position,
        /* [in] */ enum vsCMAccess Access,
        /* [retval][out] */ CodeVariable __RPC_FAR *__RPC_FAR *ppCodeVariable);
    
    STDMETHODIMP IsValidID( 
        /* [in] */ BSTR Name,
        /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pValid);
};

#endif //__CODEMODEL_H_
