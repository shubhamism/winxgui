// DSAddIn.h : header file
//

#if !defined(AFX_DSADDIN_H__B8C576E9_E601_466E_AFA5_AB78538C747F__INCLUDED_)
#define AFX_DSADDIN_H__B8C576E9_E601_466E_AFA5_AB78538C747F__INCLUDED_

#include "commands.h"

// {D458FCE7-7690-41D7-8F8D-B3F6E3F560EC}
DEFINE_GUID(CLSID_DSAddIn,
0xd458fce7, 0x7690, 0x41d7, 0x8f, 0x8d, 0xb3, 0xf6, 0xe3, 0xf5, 0x60, 0xec);

/////////////////////////////////////////////////////////////////////////////
// CDSAddIn

class CDSAddIn : 
	public IDSAddIn,
	public CComObjectRoot,
	public CComCoClass<CDSAddIn, &CLSID_DSAddIn>
{
public:
	DECLARE_REGISTRY(CDSAddIn, "FreeCode.DSAddIn.1",
		"FreeCode for VS60 Add-in", IDS_FREECODE_LONGNAME,
		THREADFLAGS_BOTH)

	CDSAddIn() {}
	BEGIN_COM_MAP(CDSAddIn)
		COM_INTERFACE_ENTRY(IDSAddIn)
	END_COM_MAP()
	DECLARE_NOT_AGGREGATABLE(CDSAddIn)

// IDSAddIns
public:
	STDMETHOD(OnConnection)(THIS_ IApplication* pApp, VARIANT_BOOL bFirstTime,
		long dwCookie, VARIANT_BOOL* OnConnection);
	STDMETHOD(OnDisconnection)(THIS_ VARIANT_BOOL bLastTime);

protected:
	CCommandsObj* m_pCommands;
	DWORD m_dwCookie;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSADDIN_H__B8C576E9_E601_466E_AFA5_AB78538C747F__INCLUDED)
