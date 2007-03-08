// src\CodeElement.h : Declaration of the CCodeElement

#ifndef __CODEELEMENT_H_
#define __CODEELEMENT_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCodeElement
class ATL_NO_VTABLE CCodeElement : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CCodeElement, &CLSID_CCodeElement>,
	public IDispatchImpl<CodeElement, &IID_CodeElement, &LIBID_CODEMODELLib>
{
public:
	CCodeElement()
	{
	}

//DECLARE_REGISTRY_RESOURCEID(IDR_CODEELEMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCodeElement)
	COM_INTERFACE_ENTRY(CodeElement)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// CodeElement
public:
	STDMETHOD(get_EndPoint)(/*[out, retval]*/ TextPoint* *pVal);
	STDMETHOD(get_StartPoint)(/*[out, retval]*/ TextPoint* *pVal);
	STDMETHOD(get_Children)(/*[out, retval]*/ CodeElements* *pVal);
	STDMETHOD(put_Children)(/*[in]*/ CodeElements* newVal);
	STDMETHOD(get_InfoLocation)(/*[out, retval]*/ enum vsCMInfoLocation *pVal);
	STDMETHOD(get_IsCodeType)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_IsCodeType)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_Kind)(/*[out, retval]*/ enum vsCMElemen *pVal);
	STDMETHOD(put_Kind)(/*[in]*/ enum vsCMElemen newVal);
};

#endif //__CODEELEMENT_H_
