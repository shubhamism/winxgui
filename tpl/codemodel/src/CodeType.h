// src\CodeType.h : Declaration of the CCodeType

#ifndef __CODETYPE_H_
#define __CODETYPE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCodeType
class ATL_NO_VTABLE CCodeType : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CCodeType, &CLSID_CCodeType>,
	public IDispatchImpl<CodeType, &IID_CodeType, &LIBID_CODEMODELLib>
{
public:
	CCodeType()
	{
	}

//DECLARE_REGISTRY_RESOURCEID(IDR_CODETYPE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCodeType)
	COM_INTERFACE_ENTRY(CodeType)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// CodeType
public:
};

#endif //__CODETYPE_H_
