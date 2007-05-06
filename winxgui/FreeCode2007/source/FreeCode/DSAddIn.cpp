// AddInMod.cpp : implementation file
//

#include "stdafx.h"
#include "FreeCode.h"
#include "DSAddIn.h"
#include "Commands.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// This is called when the user first loads the add-in, and on start-up
//  of each subsequent Developer Studio session
STDMETHODIMP CDSAddIn::OnConnection(IApplication* pApp, VARIANT_BOOL bFirstTime,
		long dwCookie, VARIANT_BOOL* OnConnection)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	typedef struct
	{
		LPCTSTR lpszCommand;
		UINT nStringID;
		LPCTSTR lpszMethod;
	}COMMANDDEFS;

  // these command must be in left-to-right order of the toolbar buttons
	COMMANDDEFS s_cd[] = {
		{ "Winx ClassWizard", IDS_CMD_STRING, "ClassWizard" }, 
	};

	// Store info passed to us
	IApplication* pApplication = NULL;
	if (FAILED(pApp->QueryInterface(IID_IApplication, (void**) &pApplication))
		|| pApplication == NULL)
	{
		*OnConnection = VARIANT_FALSE;
		return S_OK;
	}

	m_dwCookie = dwCookie;

	// Create command dispatch, send info back to DevStudio
	CCommandsObj::CreateInstance(&m_pCommands);
	m_pCommands->AddRef();

	// The QueryInterface above AddRef'd the Application object.  It will
	//  be Release'd in CCommand's destructor.
	m_pCommands->SetApplicationObject(pApplication);

	// (see stdafx.h for the definition of VERIFY_OK)
	
	VERIFY_OK(pApplication->SetAddInInfo((long) _Module.GetModuleInstance(),
		(LPDISPATCH) m_pCommands, IDR_TOOLBAR_MEDIUM, IDR_TOOLBAR_LARGE, m_dwCookie));

	// Inform DevStudio of the commands we implement

	// TODO: Replace the AddCommand call below with a series of calls,
	//  one for each command your add-in will add.

	// The command name should not be localized to other languages.  The 
	//  tooltip, command description, and other strings related to this
	//  command are stored in the string table (IDS_CMD_STRING) and should
	//  be localized.
	int nNumCmds = sizeof(s_cd) / sizeof(s_cd[0]);
	for (int n = 0; n < nNumCmds; n++)
	{
		// The command name should not be localized to other languages.  The 
		//  tooltip, command description, and other strings related to this
		//  command are stored in the string table (IDS_CMD_STRING) and should
		//  be localized.
		LPCTSTR szCommand = s_cd[n].lpszCommand;
		VARIANT_BOOL bRet;
		CString strCmdString;// = szCommand;
		strCmdString.LoadString(s_cd[n].nStringID);
		strCmdString = szCommand + strCmdString;
		CComBSTR bszCmdString(strCmdString);
		CComBSTR bszMethod(s_cd[n].lpszMethod);
		CComBSTR bszCmdName(szCommand);
		VERIFY_OK(pApplication->AddCommand(bszCmdString, bszMethod, n, m_dwCookie, &bRet));
		if (bRet == VARIANT_FALSE)
		{
			// AddCommand failed because a command with this name already
			//  exists.  You may try adding your command under a different name.
			//  Or, you can fail to load as we will do here.
			*OnConnection = VARIANT_FALSE;
			return S_OK;
		}
		
		// Add toolbar buttons only if this is the first time the add-in
		//  is being loaded.  Toolbar buttons are automatically remembered
		//  by Developer Studio from session to session, so we should only
		//  add the toolbar buttons once.
		if (bFirstTime == VARIANT_TRUE)
			VERIFY_OK(pApplication->AddCommandBarButton(dsGlyph, bszCmdName, m_dwCookie));
		
	}

	*OnConnection = VARIANT_TRUE;
	return S_OK;
	return S_OK;
}

// This is called on shut-down, and also when the user unloads the add-in
STDMETHODIMP CDSAddIn::OnDisconnection(VARIANT_BOOL bLastTime)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_pCommands->UnadviseFromEvents();
	m_pCommands->Release();
	m_pCommands = NULL;

	// TODO: Perform any cleanup work here

	return S_OK;
}
