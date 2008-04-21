// WizardInfo.h: interface for the CWizardInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WIZARDINFO_H__D023FC44_D3F7_47E1_8652_7B8222B6637B__INCLUDED_)
#define AFX_WIZARDINFO_H__D023FC44_D3F7_47E1_8652_7B8222B6637B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../vs_wizard/vs_wizard.h"
#include <vector>
#include <algorithm>

class CWizardInfo  : public vs_wizard_info
{
public:

	CWizardInfo();
	virtual ~CWizardInfo();

	CString		strProjectName;
	CString		strProjectPath;
	int			nAppType;
	bool		bModalDialog;
	bool		bFrameDialog;
	bool		bAddVFCFiles;
	bool		bEnableActiveX;
	bool		bUnicode;
	bool		bComServer;
	bool		bCppFiles;
	bool		bManifest;
	bool		bToolBar;
	bool		bReBar;
	bool		bCmdBar;
	bool		bStatusBar;
	bool		bUseView;
	bool		bMenuBar;
	bool		bMRU;
	int			nViewType;
	bool		bHostActiveX;
	bool		bVCExpress;
	bool		bVS60;
	bool		bVS2002;
	bool		bVS2003;
	bool		bVS2005;
	bool		bVS2008;
	//winxgui
	bool		bDDX;
	bool		bAccel;
	bool		bGdiPlus;
	bool		bLookNFeel;
	bool		bDefSDK;

	std::vector<CString>	ar_view;
	std::vector<CString>	ar_app;
};


#endif // !defined(AFX_WIZARDINFO_H__D023FC44_D3F7_47E1_8652_7B8222B6637B__INCLUDED_)
