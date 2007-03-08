// src\CodeParameter.h : Declaration of the CCodeParameter

#ifndef __CODEPARAMETER_H_
#define __CODEPARAMETER_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCodeParameter
class ATL_NO_VTABLE CCodeParameter : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CCodeParameter, &CLSID_CCodeParameter>,
	public IDispatchImpl<CodeParameter, &IID_CodeParameter, &LIBID_CODEMODELLib>
{
public:
	CCodeParameter()
	{
	}

//DECLARE_REGISTRY_RESOURCEID(IDR_CODEPARAMETER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCodeParameter)
	COM_INTERFACE_ENTRY(CodeParameter)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// CodeParameter
public:
};

#endif //__CODEPARAMETER_H_
