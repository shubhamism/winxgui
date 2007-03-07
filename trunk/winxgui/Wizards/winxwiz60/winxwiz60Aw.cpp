// winxwiz60aw.cpp : implementation file
//

#include "stdafx.h"
#include "winxwiz60.h"
#include "winxwiz60aw.h"
#include "chooser.h"
#include "WizardUtils.h"

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
	m_nLevel = -1;

#if (0)
#ifndef ICC_LINK_CLASS
#define ICC_STANDARD_CLASSES   0x00004000
#define ICC_LINK_CLASS         0x00008000
#endif
	INITCOMMONCONTROLSEX iccx = { sizeof(INITCOMMONCONTROLSEX), ICC_STANDARD_CLASSES };
	BOOL bSuccess = InitCommonControlsEx(&iccx);
#endif
	
	// Set the maximum number of steps.
	SetNumberOfSteps(LAST_DLG);
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
	CString strPath = m_Dictionary[_T("FULL_DIR_PATH")];
	m_nLevel = GetWinxParentPath(strPath);
	if (m_nLevel <= 0)
	{
		winx::MsgBox(
L"ERROR: WinxGui library is not found!\n\n\
We suggest you put your projects and WinxGui library in the same directory tree.\n\
For example, you can create a directory tree like this:\n\n\
\t©À©¤winx\n\
\t©¦ ©¸©¤include\n\
\t©À©¤wtl\n\
\t©¦ ©¸©¤include\n\
\t©À©¤stdext\n\
\t©¦ ©¸©¤include\n\
\t©¸©¤YourProjects\n\
\t    ©¸©¤YourPrj",
		L"Error",
		MB_OK | MB_TOPMOST | MB_ICONEXCLAMATION
		);
	}

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

void CWinxwiz60AppWiz::ProcessTemplate(LPCTSTR lpszInput, DWORD dwSize, OutputStream* pOutput)
{
	if (_tcsncmp(lpszInput, _T("$$RootFileHeader$$"), 18) == 0)
	{
		std::vector<TCHAR> strInput;
		std::tstring strFileHeader = m_Dictionary[_T("FileHeader")];
		std::replaceText(strFileHeader, std::tstring(_T("$$FileName$$")), std::tstring(_T("$$root$$.cpp")));
		strInput.reserve(strFileHeader.size() + dwSize-18);
		strInput.insert(strInput.end(), strFileHeader.begin(), strFileHeader.end());
		strInput.insert(strInput.end(), lpszInput+18, lpszInput+dwSize);
		CCustomAppWiz::ProcessTemplate(&strInput[0], strInput.size(), pOutput);
	}
	else
	{
		CCustomAppWiz::ProcessTemplate(lpszInput, dwSize, pOutput);
	}
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

	WCHAR* psz;
	WCHAR szInclude[_MAX_PATH+_MAX_PATH];
	WCHAR szLib[_MAX_PATH+_MAX_PATH];
	if (m_nLevel > 0)
	{
		psz = MakeRelPath(m_nLevel, szInclude, L"winx\\include\" ", L"/I \"", 4);
		MakeRelPath(m_nLevel, psz, L"stdext\\include\"", L"/I \"", 4);

		psz = MakeRelPath(m_nLevel, szLib, L"winx\\lib\" ", L"/libpath:\"", 10);
		MakeRelPath(m_nLevel, psz, L"winsdk\\lib\"", L"/libpath:\"", 10);
	}

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
			if (IsUnicode()) {
				pConfig->RemoveToolSettings(L"cl.exe", L"/D \"_MBCS\"", var);
				pConfig->AddToolSettings(L"cl.exe", L"/D \"UNICODE\" /D \"_UNICODE\"", var);
			}
			if (m_nLevel > 0)
			{
				pConfig->AddToolSettings(L"cl.exe", szInclude, var);
				pConfig->AddToolSettings(L"rc.exe", szInclude, var);
				pConfig->AddToolSettings(L"link.exe", szLib, var);
			}
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

