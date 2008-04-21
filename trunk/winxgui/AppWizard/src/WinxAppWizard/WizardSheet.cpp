// WTLWizardSheet.cpp: implementation of the CWTLWizardSheet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WizardSheet.h"
#include "resource.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWizardSheet::CWizardSheet(CWizardInfo * info, UINT uStartPage, HWND hWndParent) : 
	baseClass(_T("ATL/WTL Application Wizard"), IDB_HEADER, IDB_WTL,uStartPage, hWndParent)
{
	m_psh.dwFlags |= PSH_WIZARDHASFINISH;
	m_psh.dwFlags &= ~PSH_HASHELP;
	//	m_psh.dwFlags &= ~(PSH_NOCONTEXTHELP);
	//	m_psh.dwFlags &= ~(PSH_WIZARD | PSH_WIZARD_LITE | PSH_HASHELP | PSH_WIZARDCONTEXTHELP);

	//	m_psh.dwFlags |= (PSH_HASHELP | PSH_WIZARDCONTEXTHELP);
	//	m_psh.dwFlags |= PSH_WIZARD97;
	m_pageAppName.info = info;
	m_pageAppType.info = info;
	m_pageAppUI.info = info;
	this->AddPage(m_pageAppName);
	this->AddPage(m_pageAppType);
	this->AddPage(m_pageAppUI);
}

CWizardSheet::~CWizardSheet()
{

}

void CWizardSheet::OnSheetInitialized()
{
	baseClass::OnSheetInitialized();

//	this->SetWizardButtons(PSWIZB_NEXT);
}
