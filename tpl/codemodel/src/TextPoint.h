// src\TextPoint.h : Declaration of the CTextPoint

#ifndef __TEXTPOINT_H_
#define __TEXTPOINT_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTextPoint
class ATL_NO_VTABLE CTextPoint : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CTextPoint, &CLSID_CTextPoint>,
	public IDispatchImpl<TextPoint, &IID_TextPoint, &LIBID_CODEMODELLib>
{
public:
	CTextPoint()
	{
	}

//DECLARE_REGISTRY_RESOURCEID(IDR_TEXTPOINT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTextPoint)
	COM_INTERFACE_ENTRY(TextPoint)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// TextPoint
public:
};

#endif //__TEXTPOINT_H_
