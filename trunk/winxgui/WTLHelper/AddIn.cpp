// AddIn.cpp : Implementation of DLL Exports.

#include "stdafx.h"
#include "resource.h"
#ifdef _FOR_VS2005
#include "AddIn8.h"
#else
#include "AddIn.h"
#endif
#include "RegArchive.h"
#include "TextFile.h"
#include "dialog/FunctionPage.h"
#include "XMLSettingsArchive.h"
#include "Dialog/DDXVariable.h"
#include "Dialog/ReflectionDlg.h"

CAddInModule _AtlModule;
extern LPCTSTR g_MainDlgName;

void UnregisterCommands();

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	_AtlModule.SetResourceInstance(hInstance);
	return _AtlModule.DllMain(dwReason, lpReserved); 
}


// Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow(void)
{
	return _AtlModule.DllCanUnloadNow();
}


// Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}

// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer(void)
{
	// registers object, typelib and all interfaces in typelib
	HRESULT hr = _AtlModule.DllRegisterServer();
	return hr;
}


// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void)
{
	UnregisterCommands();

	HRESULT hr = _AtlModule.DllUnregisterServer();
	return hr;
}

void UnregisterCommands()
{
#ifdef _FOR_VS2005
	CString strVSKey = _T("Software\\Microsoft\\VisualStudio\\8.0\\Setup\\VS");
	CString strCmd = _T(" /command WtlHelper.Connect8.Uninstall");
#else
	CString strVSKey = _T("Software\\Microsoft\\VisualStudio\\7.1\\Setup\\VS");
	CString strCmd = _T(" /setup");
#endif
	CString strParam = _T("EnvironmentPath");
	CRegKey RegKey;
	LONG Res;
	//MessageBox(NULL, strVSKey, strCmd, 0);
	Res = RegKey.Open(HKEY_LOCAL_MACHINE, strVSKey, KEY_READ);
	if (Res == ERROR_SUCCESS)
	{
		CString strPath;
		ULONG nChars = FILENAME_MAX;
		Res = RegKey.QueryStringValue(strParam, strPath.GetBuffer(FILENAME_MAX), &nChars);
		strPath.ReleaseBuffer();
		if (!strPath.IsEmpty())
		{
			//MessageBox(NULL, strPath, strCmd, 0);
			SHELLEXECUTEINFO sei;
			ZeroMemory(&sei, sizeof(sei));
			sei.cbSize = sizeof(sei);
			sei.lpFile = strPath.LockBuffer();
			sei.lpParameters = strCmd.LockBuffer();
			sei.nShow = SW_MINIMIZE;
			sei.fMask = SEE_MASK_NOCLOSEPROCESS;

			BOOL bRes = ShellExecuteEx(&sei);

			strPath.UnlockBuffer();
			strCmd.UnlockBuffer();

			if (bRes && sei.hProcess)
			{
				WaitForSingleObject(sei.hProcess, INFINITE);
				CloseHandle(sei.hProcess);
			}
		}
		
	}
}

bool CAddInModule::IsMacro(CString MacroName)
{
	for (size_t i = 0; i < m_MacroMasks.GetCount(); i++)
	{
		if (IsMatchMask(MacroName, m_MacroMasks[i]))
			return true;
	}
	return false;
}

bool CAddInModule::IsMatchMask(LPCTSTR Name, LPCTSTR Mask)
{
	if (!Mask)
		return true;
	if (!Name)
	{
		if (Mask && Mask[0] && lstrcmp(Mask, _T("*")))
			return false;
		else
		{
			return true;
		}
	}

	while(*Name && *Mask)
	{
		switch(*Mask) 
		{
		case _T('?'):
			{
				Name++;
				Mask++;
			}
			break;
		case _T('*'):
			{
				Mask++;
				if (!*Mask)
					return true;
				do 
				{
					if (IsMatchMask(Name, Mask))
						return true;
					Name++;
				} while(*Name);
				return false;
			}
			break;
		default:
			{
				if (*Name != *Mask)
					return false;
				Name++;
				Mask++;
			}
		}
	}
	return ((!*Name && !*Mask) || (*Mask == _T('*')));
}

bool CAddInModule::LoadAll()
{
	CRegArchive RegArchive;
	if (RegArchive.Open(HKEY_CURRENT_USER, _T("Software\\SaloS\\WtlHelper")))
	{
		LoadSettings(RegArchive, g_MainDlgName, 2);
		RegArchive.Close();
	}
	if (!m_DialogClasses.IsEmpty() || !m_MacroMasks.IsEmpty())
		return true;

	if (RegArchive.Open(HKEY_LOCAL_MACHINE, _T("Software\\SaloS\\WtlHelper")))
	{
		if (_AtlModule.LoadSettings(RegArchive, _T("Common")))
		{
			bool bTrue = true;
			CXMLSettingsArchive XMLArchive;
			if (XMLArchive.Open(m_CommonFile))
			{
				if (!LoadSettings(XMLArchive, _T("Common"), 1))
					bTrue = false;
				XMLArchive.StartObject(_T("Common"));
				if (!CFunctionManager::LoadSpecFunctions(&XMLArchive, _T("SpecFunctions")))
					bTrue = false;
				if (!CAtlArrayObjectSerializer<DDXContols>::LoadVariable(_T("ControlClasses"), XMLArchive, CDDXVariable::m_ControlClasses))
					bTrue = false;
				if (!CAtlArrayObjectSerializer<DDXMemberTypes>::LoadVariable(_T("MemberTypes"), XMLArchive, CDDXVariable::m_MemberTypes))
					bTrue = false;
				if (!CAtlArraySerializer<CString>::LoadVariable(_T("ReflectMessages"), XMLArchive, CReflectionDlg::m_sReflectMessages))
					bTrue = false;

				XMLArchive.EndObject();

				XMLArchive.Close();
			}
			else
				bTrue = false;
			if (XMLArchive.Open(m_RegMessages))
			{
				if (!CMessageManager::m_sHandlerManager.LoadSettings(&XMLArchive, _T("HandlerManager")))
					bTrue = false;
				XMLArchive.Close();
			}
			else
				bTrue = false;

			if (!bTrue)
			{
				MessageBox(NULL, _T("Cannot load some settings"), NULL, 0);
			}
		}
		RegArchive.Close();
	}
	else
	{
		CString str;
		str = _T("Cannot open HKLM registry"); 
		MessageBox(NULL, str, NULL, 0);
	}
	
	return true;
}

void CAddInModule::Destroy()
{
	m_DialogClasses.RemoveAll();
	m_MacroMasks.RemoveAll();
}