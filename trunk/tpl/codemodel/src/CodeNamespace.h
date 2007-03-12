// src\CodeNamespace.h : Declaration of the CCodeNamespace

#ifndef __CODENAMESPACE_H_
#define __CODENAMESPACE_H_

#include "resource.h"       // main symbols
#include <codemodel_i.h>

/////////////////////////////////////////////////////////////////////////////
// CCodeNamespace
class ATL_NO_VTABLE CCodeNamespace : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CCodeNamespace, &CLSID_CCodeNamespace>,
	public IDispatchImpl<CodeNamespace, &IID_CodeNamespace, &LIBID_CODEMODELLib>
{
public:
	CCodeNamespace()
	{
	}

//DECLARE_REGISTRY_RESOURCEID(IDR_CODENAMESPACE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCodeNamespace)
	COM_INTERFACE_ENTRY(CodeNamespace)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// CodeNamespace
public:
	STDMETHOD(get_Members)(/*[out, retval]*/ CodeElements* *pVal);
	STDMETHOD(get_FullName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);
};

#endif //__CODENAMESPACE_H_
