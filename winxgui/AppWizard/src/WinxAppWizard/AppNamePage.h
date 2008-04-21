// AppNamePage.h: interface for the CAppNamePage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPNAMEPAGE_H__3E62F20C_1440_4F03_A971_D424F6B8B18E__INCLUDED_)
#define AFX_APPNAMEPAGE_H__3E62F20C_1440_4F03_A971_D424F6B8B18E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "wizardinfo.h"
#include <direct.h>

class CAppNamePage : public CWizardPageImpl<CAppNamePage, CWizardInfo>
{
public:
	CString GetText(UINT nID);
	CString		m_strLocation;

	BEGIN_DDX_MAP(CAppNamePage)
		if (bSaveAndValidate == DDX_LOAD)
		{
			m_strLocation = info->load_cfg_str(_T("PROJECT_PATH"));
			info->bVS60 = info->load_cfg_bool(_T("PROJECT_VS60"),0);
			info->bVS2002 = info->load_cfg_bool(_T("PROJECT_VS2002"),0);
			info->bVS2003 = info->load_cfg_bool(_T("PROJECT_VS2003"),0);
			info->bVS2005 = info->load_cfg_bool(_T("PROJECT_VS2005"),1);
			info->bVS2008 = info->load_cfg_bool(_T("PROJECT_VS2008"),0);
			info->bDefSDK = info->load_cfg_bool(_T("PROJECT_DEFSDK"),0);
		}
		DDX_TEXT(IDC_PROJECT_NAME_EDIT, info->strProjectName)
		DDX_TEXT(IDC_PROJECT_PATH_EDIT, info->strProjectPath)
		DDX_CHECK(IDC_VS60_CHECK,info->bVS60)
		DDX_CHECK(IDC_DEFSDK_CHECK, info->bDefSDK)
		DDX_CHECK(IDC_VS2002_CHECK,info->bVS2002)
		DDX_CHECK(IDC_VS2003_CHECK,info->bVS2003)
		DDX_CHECK(IDC_VS2005_CHECK,info->bVS2005)
		DDX_CHECK(IDC_VS2008_CHECK,info->bVS2008)
		DDX_TEXT(IDC_LOCATION_EDIT, m_strLocation)
		//bSaveAndValidate
		if (bSaveAndValidate == DDX_SAVE)
		{
			if (info->check_project_name(info->strProjectName) == false)
			{
				MessageBox("The name specified is not a valid name for a project.","WTLAppWizard",MB_OK | MB_ICONWARNING);
				return FALSE;
			}

			info->strProjectPath = m_strLocation+_T("\\")+info->strProjectName;

			if (::PathFileExists(m_strLocation) == FALSE)
			{
				MessageBox("The location path is not exists!","WTLAppWizard",MB_OK | MB_ICONWARNING);
				return FALSE;
			}
			if (::PathFileExists(info->strProjectPath) != FALSE)
			{
				MessageBox("The project path is exists!","WTLAppWizard",MB_OK | MB_ICONWARNING);
				return FALSE;
			}
			if (!info->bVS60 && !info->bVS2002 && !info->bVS2003 && !info->bVS2005 && !info->bVS2008)
			{
				MessageBox("Please select make target","WTLAppWizard",MB_OK | MB_ICONWARNING);
				return FALSE;
			}
			
			info->save_cfg_str(_T("PROJECT_PATH"),m_strLocation);
			info->save_cfg_bool(_T("PROJECT_VS60"),info->bVS60);
			info->save_cfg_bool(_T("PROJECT_VS2002"),info->bVS2002);
			info->save_cfg_bool(_T("PROJECT_VS2003"),info->bVS2003);
			info->save_cfg_bool(_T("PROJECT_VS2005"),info->bVS2005);
			info->save_cfg_bool(_T("PROJECT_VS2008"),info->bVS2008);
			info->save_cfg_bool(_T("PROJECT_DEFSDK"),info->bDefSDK);
		}
	END_DDX_MAP();
	
	enum { IDD = IDD_APPNAME_PAGE };
	CAppNamePage();
	virtual ~CAppNamePage();

	BEGIN_MSG_MAP(CAppNamePage)
		COMMAND_HANDLER(IDC_PROJECT_NAME_EDIT, EN_CHANGE, OnEnChangeProjectNameEdit)
		COMMAND_ID_HANDLER(IDC_BROWSE, OnBrowse)
		CHAIN_MSG_MAP(CWizardPageImplBase)
	END_MSG_MAP()

	LRESULT OnEnChangeProjectNameEdit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnBrowse(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);	
};

#endif // !defined(AFX_APPNAMEPAGE_H__3E62F20C_1440_4F03_A971_D424F6B8B18E__INCLUDED_)
