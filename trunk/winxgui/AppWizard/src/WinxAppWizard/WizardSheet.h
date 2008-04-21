// WizardSheet.h: interface for the CWizardSheet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WIZARDSHEET_H__8AA81604_6B1A_41BB_B2D1_CCEA9E2A59FE__INCLUDED_)
#define AFX_WIZARDSHEET_H__8AA81604_6B1A_41BB_B2D1_CCEA9E2A59FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>

#include "wizardinfo.h"
#include "appnamepage.h"
#include "apptypepage.h"
#include "appuipage.h"

class CWizardSheet : public CWizard97SheetImpl<CWizardSheet>
{
public:
	void OnSheetInitialized();
	typedef CWizard97SheetImpl<CWizardSheet> baseClass;

	CWizardSheet(CWizardInfo * info, UINT uStartPage, HWND hWndParent);
	virtual ~CWizardSheet();

	BEGIN_MSG_MAP(CWizardSheet)
		CHAIN_MSG_MAP(baseClass)
	END_MSG_MAP()
	
	CAppNamePage	m_pageAppName;
	CAppTypePage	m_pageAppType;
	CAppUIPage	m_pageAppUI;

};

#endif // !defined(AFX_WIZARDSHEET_H__8AA81604_6B1A_41BB_B2D1_CCEA9E2A59FE__INCLUDED_)
