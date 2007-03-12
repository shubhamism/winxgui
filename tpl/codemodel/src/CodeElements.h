// src\CodeElements.h : Declaration of the CCodeElements

#ifndef __CODEELEMENTS_H_
#define __CODEELEMENTS_H_

#include "resource.h"       // main symbols
#include <codemodel_i.h>

/////////////////////////////////////////////////////////////////////////////
// CCodeElements
class ATL_NO_VTABLE CCodeElements : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CCodeElements, &CLSID_CCodeElements>,
	public IDispatchImpl<CodeElements, &IID_CodeElements, &LIBID_CODEMODELLib>
{
public:
	CCodeElements()
	{
	}

//DECLARE_REGISTRY_RESOURCEID(IDR_CODEELEMENTS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCodeElements)
	COM_INTERFACE_ENTRY(CodeElements)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// CodeElements
public:
	STDMETHOD(get_Count)(/*[out, retval]*/ long *pVal);
};

#endif //__CODEELEMENTS_H_
