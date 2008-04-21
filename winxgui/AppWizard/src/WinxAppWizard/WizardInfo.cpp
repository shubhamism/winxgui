// WizardInfo.cpp: implementation of the CWizardInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WizardInfo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWizardInfo::CWizardInfo()
{
	bEnableActiveX = false;
	bUnicode = true;
	bCmdBar = true;
	bComServer = false;
	bCppFiles = false;
	bHostActiveX = false;
	bManifest = true;
	bMRU = false;
	bMenuBar = false;
	bReBar = true;
	bStatusBar = true;
	bToolBar = true;
	bVS2005 = false;
	bVCExpress = false;
	nAppType = 0;
	nViewType = 0;
	bModalDialog = false;
	bVS60 = true;
	bDefSDK = false;
	bVS2002 = false;
	bVS2003 = false;
	bVS2008 = false;
	bVS2005 = false;
	bUseView = false;
	bFrameDialog = false;
	bAddVFCFiles = false;
	bDDX = true;
	bLookNFeel = false;
	bGdiPlus = false;
	bAccel = true;

	templatePath = GetModulePath(_Module.m_hInst)+_T("\\templates");
	cfgPath = GetModulePath(NULL)+_T("\\setup.ini");
	cfgApp = _T("WinxAppWizard");

	ar_view.push_back("Generic Window");
	ar_view.push_back("ListBox");
	ar_view.push_back("Edit");
	ar_view.push_back("List View");
	ar_view.push_back("Tree View");
	ar_view.push_back("Rich Edit");
	ar_view.push_back("HTML Page");
	ar_view.push_back("Scroll Window");

	ar_app.push_back("WINX_APPTYPE_DLG_MODAL");
	ar_app.push_back("WINX_APPTYPE_DLG");

	ar_lang.push_back(_T("1033"));
	nAppLang = 0;
	load_lang();
}

CWizardInfo::~CWizardInfo()
{

}
