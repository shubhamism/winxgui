// src\CodeVariable.h : Declaration of the CCodeVariable

#ifndef __CODEVARIABLE_H_
#define __CODEVARIABLE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCodeVariable
class ATL_NO_VTABLE CCodeVariable : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CCodeVariable, &CLSID_CCodeVariable>,
	public IDispatchImpl<CodeVariable, &IID_CodeVariable, &LIBID_CODEMODELLib>
{
public:
	CCodeVariable()
	{
	}

//DECLARE_REGISTRY_RESOURCEID(IDR_CODEVARIABLE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCodeVariable)
	COM_INTERFACE_ENTRY(CodeVariable)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// CodeVariable
public:
	STDMETHOD(get_IsConstant)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_IsConstant)(/*[in]*/ VARIANT_BOOL newVal);
};

#endif //__CODEVARIABLE_H_
