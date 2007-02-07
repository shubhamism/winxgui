// winxwiz60aw.cpp : implementation file
//

#include "stdafx.h"
#include "winxwiz60.h"
#include "winxwiz60aw.h"
#include "chooser.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// This is called immediately after the custom AppWizard is loaded.  Initialize
//  the state of the custom AppWizard here.
void CWinxwiz60AppWiz::InitCustomAppWiz()
{
	// Create a new dialog chooser; CDialogChooser's constructor initializes
	//  its internal array with pointers to the steps.
	m_pChooser = new CDialogChooser(this);

	// Set the maximum number of steps.
	SetNumberOfSteps(LAST_DLG);

#if defined(_DEBUG) || defined(_PSEUDO_DEBUG)
	for (POSITION pos = m_Dictionary.GetStartPosition(); pos; )
	{
		CString strKey, strValue;
		m_Dictionary.GetNextAssoc(pos, strKey, strValue);
		TRACE(_T("['%s', '%s']\n"), (LPCTSTR)strKey, (LPCTSTR)strValue);
	}
#endif
}

// This is called just before the custom AppWizard is unloaded.
void CWinxwiz60AppWiz::ExitCustomAppWiz()
{
	// Deallocate memory used for the dialog chooser
	ASSERT(m_pChooser != NULL);
	delete m_pChooser;
	m_pChooser = NULL;
}

// This is called when the user clicks "Create..." on the New Project dialog
//  or "Next" on one of the custom AppWizard's steps.
CAppWizStepDlg* CWinxwiz60AppWiz::Next(CAppWizStepDlg* pDlg)
{
	// Delegate to the dialog chooser
	return m_pChooser->Next(pDlg);
}

// This is called when the user clicks "Back" on one of the custom
//  AppWizard's steps.
CAppWizStepDlg* CWinxwiz60AppWiz::Back(CAppWizStepDlg* pDlg)
{
	// Delegate to the dialog chooser
	return m_pChooser->Back(pDlg);
}

#include <shlwapi.h>
#include <atlbase.h>
#include <algorithm>
#pragma comment(lib, "shlwapi")

template <class StringT>
inline int GetWinxParentPath(StringT& strPrjPath)
{
	int nLast = strPrjPath.GetLength()-1;
	if (strPrjPath.GetAt(nLast) == '\\')
		strPrjPath.Delete(nLast);

	int nLevel = 0;
	int pos;
	while ((pos = strPrjPath.ReverseFind('\\')) != -1)
	{
		++nLevel;
		strPrjPath = strPrjPath.Left(pos);
		if (PathIsDirectory(strPrjPath + _T("\\winx\\include")))
			return nLevel;
	}
	return -1;
}

template <class CharT>
inline CharT* MakeRelPath(
	int nLevel, CharT* szRelPath, const CharT* szPathName)
{
	int nNameLen = std::char_traits<CharT>::length(szPathName);
	while (nLevel--) {
		*szRelPath++ = '.';
		*szRelPath++ = '.';
		*szRelPath++ = '\\';
	}
	return std::copy(szPathName, szPathName+nNameLen+1, szRelPath)-1;
}

template <class CharT>
inline CharT* MakeRelPath(
	int nLevel, CharT* szRelPath, const CharT* szPathName,
	const CharT* szPre, int cchPre)
{
	szRelPath = std::copy(szPre, szPre+cchPre, szRelPath);
	return MakeRelPath(nLevel, szRelPath, szPathName);
}

void CWinxwiz60AppWiz::CustomizeProject(IBuildProject* pProject)
{
	// TODO: Add code here to customize the project.  If you don't wish
	//  to customize project, you may remove this virtual override.
	
	// This is called immediately after the default Debug and Release
	//  configurations have been created for each platform.  You may customize
	//  existing configurations on this project by using the methods
	//  of IBuildProject and IConfiguration such as AddToolSettings,
	//  RemoveToolSettings, and AddCustomBuildStep. These are documented in
	//  the Developer Studio object model documentation.

	// WARNING!!  IBuildProject and all interfaces you can get from it are OLE
	//  COM interfaces.  You must be careful to release all new interfaces
	//  you acquire.  In accordance with the standard rules of COM, you must
	//  NOT release pProject, unless you explicitly AddRef it, since pProject
	//  is passed as an "in" parameter to this function.  See the documentation
	//  on CCustomAppWiz::CustomizeProject for more information.

	CString strPath = m_Dictionary[_T("FULL_DIR_PATH")];
	int nLevel = GetWinxParentPath(strPath);
	if (nLevel <= 0)
		return;

	WCHAR* psz;
	WCHAR szInclude[_MAX_PATH+_MAX_PATH];
	psz = MakeRelPath(nLevel, szInclude, L"winx\\include\" ", L"/I \"", 4);
	MakeRelPath(nLevel, psz, L"stdext\\include\"", L"/I \"", 4);

	WCHAR szLib[_MAX_PATH+_MAX_PATH];
	psz = MakeRelPath(nLevel, szLib, L"winx\\lib\" ", L"/libpath:\"", 10);
	MakeRelPath(nLevel, psz, L"winsdk\\lib\"", L"/libpath:\"", 10);

	IConfigurations* pConfigs;
	HRESULT hr = pProject->get_Configurations(&pConfigs);
	if (FAILED(hr))
		return;

	VARIANT var = {0};
	long nCount = 0;
	pConfigs->get_Count(&nCount);
	for (long i = 1; i <= nCount; ++i)
	{
		IConfiguration* pConfig;
		hr = pConfigs->Item(CComVariant(i), &pConfig);
		if (SUCCEEDED(hr)) {
			pConfig->AddToolSettings(L"mfc", L"0", var);
			pConfig->AddToolSettings(L"cl.exe", szInclude, var);
			pConfig->AddToolSettings(L"rc.exe", szInclude, var);
			pConfig->AddToolSettings(L"link.exe", szLib, var);
			pConfig->AddToolSettings(L"link.exe", L"gdi32.lib", var);
			pConfig->Release();
		}
	}
	pConfigs->Release();
}


// Here we define one instance of the CWinxwiz60AppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global Winxwiz60aw.
CWinxwiz60AppWiz Winxwiz60aw;

