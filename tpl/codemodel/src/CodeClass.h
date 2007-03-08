// src\CodeClass.h : Declaration of the CCodeClass

#ifndef __CODECLASS_H_
#define __CODECLASS_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCodeClass
class ATL_NO_VTABLE CCodeClass : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CCodeClass, &CLSID_CCodeClass>,
	public IDispatchImpl<CodeClass, &IID_CodeClass, &LIBID_CODEMODELLib>
{
public:
	CCodeClass()
	{
	}

//DECLARE_REGISTRY_RESOURCEID(IDR_CODECLASS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCodeClass)
	COM_INTERFACE_ENTRY(CodeClass)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// CodeClass
public:
	STDMETHOD(get_IsDerivedFrom)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_IsDerivedFrom)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_Bases)(/*[out, retval]*/ CodeElements* *pVal);
	STDMETHOD(put_Bases)(/*[in]*/ CodeElements* newVal);
	STDMETHOD(get_Namespace)(/*[out, retval]*/ CodeNamespace* *pVal);
	STDMETHOD(put_Namespace)(/*[in]*/ CodeNamespace* newVal);
};

#endif //__CODECLASS_H_
