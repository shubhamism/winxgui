// src\CodeFunction.h : Declaration of the CCodeFunction

#ifndef __CODEFUNCTION_H_
#define __CODEFUNCTION_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCodeFunction
class ATL_NO_VTABLE CCodeFunction : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CCodeFunction, &CLSID_CCodeFunction>,
	public IDispatchImpl<CodeFunction, &IID_CodeFunction, &LIBID_CODEMODELLib>
{
public:
	CCodeFunction()
	{
	}

//DECLARE_REGISTRY_RESOURCEID(IDR_CODEFUNCTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCodeFunction)
	COM_INTERFACE_ENTRY(CodeFunction)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// CodeFunction
public:
	STDMETHOD(get_Access)(/*[out, retval]*/ enum vsCMAccess *pVal);
	STDMETHOD(put_Access)(/*[in]*/ enum vsCMAccess newVal);
	STDMETHOD(get_Parameters)(/*[out, retval]*/ CodeElements* *pVal);
	STDMETHOD(get_Type)(/*[out, retval]*/ CodeTypeRef* *pVal);
	STDMETHOD(put_Type)(/*[in]*/ CodeTypeRef* newVal);
	STDMETHOD(get_FunctionKind)(/*[out, retval]*/ enum vsCMFunction *pVal);
	STDMETHOD(put_FunctionKind)(/*[in]*/ enum vsCMFunction newVal);
};

#endif //__CODEFUNCTION_H_
