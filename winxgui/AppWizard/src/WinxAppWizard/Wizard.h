// Wizard.h: interface for the CWizard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WIZARD_H__1756BB27_ED06_4810_B375_C4991C389806__INCLUDED_)
#define AFX_WIZARD_H__1756BB27_ED06_4810_B375_C4991C389806__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../vs_wizard/vs_wizard.h"
#include "wizardinfo.h"

class CWizard  
{
public:
	bool AddFilesToProject(const CString & strProjectName, const CString &strProjectPath, str_vector & array);
	CString GetTargetName(const CString & strName, const CString & strProjName);
	bool make_project();
	bool on_evnet_finish();
	int ExecuteWizard();
	CWizard();
	virtual ~CWizard();
	CWizardInfo	info;
	vs_wizard		wizard;
};

#endif // !defined(AFX_WIZARD_H__1756BB27_ED06_4810_B375_C4991C389806__INCLUDED_)
