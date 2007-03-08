// src\CodeTypeRef.h : Declaration of the CCodeTypeRef

#ifndef __CODETYPEREF_H_
#define __CODETYPEREF_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCodeTypeRef
class ATL_NO_VTABLE CCodeTypeRef : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CCodeTypeRef, &CLSID_CCodeTypeRef>,
	public IDispatchImpl<CodeTypeRef, &IID_CodeTypeRef, &LIBID_CODEMODELLib>
{
public:
	CCodeTypeRef()
	{
	}

//DECLARE_REGISTRY_RESOURCEID(IDR_CODETYPEREF)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCodeTypeRef)
	COM_INTERFACE_ENTRY(CodeTypeRef)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// CodeTypeRef
public:
	STDMETHOD(get_AsString)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Rank)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Rank)(/*[in]*/ long newVal);
	STDMETHOD(get_ElementType)(/*[out, retval]*/ CodeTypeRef* *pVal);
	STDMETHOD(put_ElementType)(/*[in]*/ CodeTypeRef* newVal);
	STDMETHOD(get_CodeType)(/*[out, retval]*/ CodeType* *pVal);
	STDMETHOD(put_CodeType)(/*[in]*/ CodeType* newVal);
	STDMETHOD(get_TypeKind)(/*[out, retval]*/ enum vsCMTypeRef *pVal);
};

#endif //__CODETYPEREF_H_
