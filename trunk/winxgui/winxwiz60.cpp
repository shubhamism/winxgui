// winxwiz60.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "winxwiz60.h"
#include "winxwiz60aw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE Winxwiz60DLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("WINXWIZ60.AWX Initializing!\n");
		
		// Extension DLL one-time initialization
		AfxInitExtensionModule(Winxwiz60DLL, hInstance);

		// Insert this DLL into the resource chain
		new CDynLinkLibrary(Winxwiz60DLL);

		// Register this custom AppWizard with MFCAPWZ.DLL
		SetCustomAppWizClass(&Winxwiz60aw);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("WINXWIZ60.AWX Terminating!\n");

		// Terminate the library before destructors are called
		AfxTermExtensionModule(Winxwiz60DLL);
	}
	return 1;   // ok
}
