////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	Connect.cpp
// Created:	16.11.2004 8:55
// 
//   Using this software in commercial applications requires an author
// permission. The permission will be granted to everyone excluding the cases
// when someone simply tries to resell the code.
//   This file may be redistributed by any means PROVIDING it is not sold for
// profit without the authors written consent, and providing that this notice
// and the authors name is included.
//   This file is provided "as is" with no expressed or implied warranty. The
// author accepts no liability if it causes any damage to you or your computer
// whatsoever.
//
////////////////////////////////////////////////////////////////////////////////

// Connect.cpp : Implementation of CConnect
#include "stdafx.h"
#ifdef _FOR_VS2005
#include "AddIn8.h"
#else
#include "AddIn.h"
#endif
#include "AddIn.h"
#include "Connect.h"
#include "dialog/FunctionPage.h"
#include "dialog/GeneralPage.h"
#include "dialog/VariablePage.h"
#include "dialog/AddMemberVarGL.h"
#include "Options/OptionsDlg.h"
#include "Dialog/WtlHelperDlg.h"
#include "common.h"
#include <msiquery.h>
#include <msi.h>
#include "WtlHelperRes/resource.h"

extern CAddInModule _AtlModule;
VSFunction* g_pSelectedFunction;

#ifdef _FOR_VS2005
#define AddinString() L"WtlHelper.Connect8."
#else
#define AddinString() L"WtlHelper.Connect."
#endif

#define CMD(Command) AddinString()L#Command

WtlHelperCmdBar WtlHelperCmdBars[]=
{
	{L"Tools", 1, EnvDTE::vsCommandBarTypeMenu, },
	{L"Class View Item", 10, EnvDTE::vsCommandBarTypeMenu, },
	{L"Resource Editors", 1, EnvDTE::vsCommandBarTypeMenu, },
	{L"Menu Designer", 1, EnvDTE::vsCommandBarTypeMenu, },
	{L"Resource View", 1, EnvDTE::vsCommandBarTypeMenu, }
};

const CommandStruct VariableCmd(L"AddVariable", L"Add Variable", L"Add variable to class", 
								L"Text Editor::Ctrl+Shift+W, V");
const CommandStruct FunctionCmd(L"AddFunction", L"Add Function", L"Add function to class", 
								L"Text Editor::Ctrl+Shift+W, F");
#ifdef _FOR_VS2005
const CommandStruct UninstallCmd(L"Uninstall", L"Uninstall", NULL, L"", CMDBAR_NO, -1,
								 false, -1);
#endif

// WTL Helper command

const CommandStruct HelperCmd(L"WtlHelper", L"WTL Helper", L"Helps to add message handlers",
							  L"Text Editor::Ctrl+Alt+W", CMDBAR_TOOLS, 1, false, IDB_BITMAP_WIZARD);

// Options command
const CommandStruct OptionCmd(L"Options", L"Options", L"Set options for WTL Helper", 
							  L"Text Editor::Ctrl+Shift+W, O", CMDBAR_TOOLS, 2, false, IDB_BITMAP_OPTION);

//Class view context menu
const CommandStruct ClassViewHandlerCmd(L"ClassView_Handlers", L"Add handler or function",
										L"Show WTL Helper main window on Functions page", 
										L"", CMDBAR_CLASSVIEW, 1, false, IDB_BITMAP_MSG);
const CommandStruct ClassViewVarCmd(L"ClassView_Variables", L"Add DDX variable", 
									L"Show WTL Helper main window on Variables page", L"", 
									CMDBAR_CLASSVIEW, 2, false, IDB_BITMAP_DDXVAR);

// Resource view context menu
const CommandStruct ResViewDDXCmd(L"ResView_DDX", L"Add DDX entry", 
								  L"Add entry to DDX map for the specified control", L"", 
								  CMDBAR_RESEDITORS, 1, false, IDB_BITMAP_DDXVAR);
const CommandStruct ResViewDDXMultCmd(L"ResView_DDX_Mult", L"Add multiple DDX entries", 
									  L"Add multiple entries to DDX map for the specified controls", 
									  L"", CMDBAR_RESEDITORS, 2, false, IDB_BITMAP_DDXVAR);
const CommandStruct ResViewHandlerCmd(L"ResView_Handler", L"Add handler", 
									  L"Add command or notify handler for the specified item", 
									  L"", CMDBAR_RESEDITORS, 3, false, IDB_BITMAP_MSG);
const CommandStruct ResViewHandlerMultCmd(L"ResView_Handler_Mult", L"Add multiple handlers", 
										  L"Add command or notify handlers for the specified items", 
										  L"", CMDBAR_RESEDITORS, 4, false, IDB_BITMAP_MSG);
const CommandStruct ResViewDialogCmd(L"ResView_Dialog", L"Create dialog class", 
									 L"Create dialog class using WTL Dialog Wizard", L"", 
									 CMDBAR_RESEDITORS, 5, false, IDB_BITMAP_DIALOG);
const CommandStruct ResViewReflectCmd(L"ResView_Reflect", L"Add custom reflection handler", 
									  L"Add custom reflection handler only for WTL 7.5 and above", 
									  L"", CMDBAR_RESEDITORS, 6, false, IDB_BITMAP_REFLECT);

// Resource view for menu editor
const CommandStruct MenuDesignHandlerCmd(L"MenuDesign_Handler", L"Add handler", 
										 L"Add command handler for the specified menu item", 
										 L"", CMDBAR_MENUEDITORS, 1, false, IDB_BITMAP_MSG);

// Resource file view 
const CommandStruct ResViewContextDialogCmd(L"ResViewContext_Dialog", L"Create dialog class", 
											L"Create dialog class using WTL Dialog Wizard", 
											L"", CMDBAR_RESVIEW, 1, false, IDB_BITMAP_DIALOG);
const CommandStruct ResViewContextHandlerCmd(L"ResViewContext_Handler", L"Add handler", 
											 L"Add command or notify handler for the specified item", 
											 L"", CMDBAR_RESVIEW, 2, false, IDB_BITMAP_MSG);
const CommandStruct ResViewContextDDXCmd(L"ResViewContext_DDX", L"Add DDX entry", 
										 L"Add entry to DDX map for the specified control", 
										 L"", CMDBAR_RESVIEW, 3, false, IDB_BITMAP_DDXVAR);

// List of all commands
const CommandStruct* WtlHelperCommands[]=
{
	&VariableCmd,
	&FunctionCmd,
#ifdef _FOR_VS2005
	&UninstallCmd,
#endif
	&HelperCmd,
	&OptionCmd,
	&ClassViewHandlerCmd,
	&ClassViewVarCmd,
	&ResViewDDXCmd,
	&ResViewDDXMultCmd,
	&ResViewHandlerCmd,
	&ResViewHandlerMultCmd,
	&ResViewDialogCmd,
	&ResViewReflectCmd,
	&MenuDesignHandlerCmd,
	&ResViewContextDialogCmd,
	&ResViewContextHandlerCmd,
	&ResViewContextDDXCmd
};


// When run, the Add-in wizard prepared the registry for the Add-in.
// At a later time, if the Add-in becomes unavailable for reasons such as:
//   1) You moved this project to a computer other than which is was originally created on.
//   2) You chose 'Yes' when presented with a message asking if you wish to remove the Add-in.
//   3) Registry corruption.
// you will need to re-register the Add-in by building the MyAddin21Setup project 
// by right clicking the project in the Solution Explorer, then choosing install.

EnvDTE::ProjectPtr g_pActiveProject;

// CConnect
STDMETHODIMP CConnect::OnConnection(IDispatch *pApplication, AddInDesignerObjects::ext_ConnectMode ConnectMode, IDispatch *pAddInInst, SAFEARRAY ** /*custom*/ )
{
	HRESULT hr = S_OK;
	pApplication->QueryInterface(__uuidof(EnvDTE::_DTE), (LPVOID*)&m_pDTE);
	pAddInInst->QueryInterface(__uuidof(EnvDTE::AddIn), (LPVOID*)&m_pAddInInstance);

	EnvDTE::CommandsPtr pCommands;
	UICommandBarsPtr pCommandBars;
	EnvDTE::CommandPtr pCreatedCommand;
	UICommandBarPtr pHostCmdBar;

	// When run, the Add-in wizard prepared the registry for the Add-in.
	// At a later time, the Add-in or its commands may become unavailable for reasons such as:
	//   1) You moved this project to a computer other than which is was originally created on.
	//   2) You chose 'Yes' when presented with a message asking if you wish to remove the Add-in.
	//   3) You add new commands or modify commands already defined.
	// You will need to re-register the Add-in by building the WtlHelperSetup project,
	// right-clicking the project in the Solution Explorer, and then choosing install.
	// Alternatively, you could execute the ReCreateCommands.reg file the Add-in Wizard generated in 
	// the project directory, or run 'devenv /setup' from a command prompt.
	//if (ConnectMode == AddInDesignerObjects::ext_cm_Startup || ConnectMode == AddInDesignerObjects::ext_cm_AfterStartup)
	if(ConnectMode == 5) //5 == ext_cm_UISetup
	{
		IfFailGoCheck(m_pDTE->get_Commands(&pCommands), pCommands);
#ifdef _FOR_VS2005
		IfFailGoCheck(m_pDTE->get_CommandBars((IDispatch**)&pCommandBars), pCommandBars);
#else
		IfFailGoCheck(m_pDTE->get_CommandBars(&pCommandBars), pCommandBars);
#endif
		for (size_t i = 0; i < _countof(WtlHelperCmdBars); i++)
		{
			pHostCmdBar = NULL;
			if (FAILED(pCommandBars->get_Item(_variant_t(WtlHelperCmdBars[i].lpName), 
				&pHostCmdBar)) || pHostCmdBar == NULL)
			{
				continue;
			}
			
			UICommandBarControlsPtr pControls;
			UICommandBarPtr pHelperCmdBar;
			pHostCmdBar->get_Controls(&pControls);
			UICommandBarControlPtr pControl;
			hr = pControls->get_Item(_variant_t(L"WTL Helper"), &pControl);
			while (pControl != NULL)
			{
				UICommandBarPopupControlPtr pPopup = pControl;
				if (pPopup != NULL)
				{
					pPopup->get_CommandBar(&pHelperCmdBar);
					if(pHelperCmdBar != NULL)
					{
						hr = pCommands->RemoveCommandBar(pHelperCmdBar);
					}
					else
					{
						pPopup->Delete();
					}
				}
				
				pControls->get_Item(_variant_t(L"WTL Helper"), &pControl);
			}
			
			hr = pCommands->AddCommandBar(_bstr_t(L"WTL Helper"), WtlHelperCmdBars[i].CmdType,
				pHostCmdBar, WtlHelperCmdBars[i].nPos, (IDispatch**)&WtlHelperCmdBars[i].pCmdBar);
			if (FAILED(hr))
				break;
		}
		
		ATLASSERT(false);
		for (size_t i = 0; i < _countof(WtlHelperCommands); i++)
		{
			CreateCommand(pCommands, WtlHelperCommands[i]);
		}
	}
	CFunctionPage::FillFuncButtons();

	return S_OK;

Error:
	return hr;
}

HRESULT CConnect::CreateCommand(EnvDTE::Commands* pCommands, const CommandStruct* pCmd)
{
	EnvDTE::CommandPtr pCreatedCommand;
	UICommandBarControlPtr pCommandBarControl;

	HRESULT hr = pCommands->AddNamedCommand(m_pAddInInstance, pCmd->Name, pCmd->ButtonText, pCmd->ToolTip, pCmd->bMSOButton, pCmd->lBitmapId, NULL, EnvDTE::vsCommandStatusSupported+EnvDTE::vsCommandStatusEnabled, &pCreatedCommand);
	if(SUCCEEDED(hr) && (pCreatedCommand != NULL))
	{
		if ((pCmd->iCmdBar != CMDBAR_NO) && (WtlHelperCmdBars[pCmd->iCmdBar].pCmdBar != NULL))
		{
			//Add a button to the tools menu bar.
#ifdef _FOR_VS2005
			if (FAILED(pCreatedCommand->AddControl(WtlHelperCmdBars[pCmd->iCmdBar].pCmdBar,
				pCmd->lPos, (IDispatch**)&pCommandBarControl)) || (pCommandBarControl == NULL))
#else
			if (FAILED(pCreatedCommand->AddControl(WtlHelperCmdBars[pCmd->iCmdBar].pCmdBar,
				pCmd->lPos, &pCommandBarControl)) || (pCommandBarControl == NULL))
#endif
			{
				return E_FAIL;
			}
		}

		if (pCmd->Bindings.bstrVal && pCmd->Bindings.bstrVal[0])
		{
			if (pCreatedCommand->put_Bindings(pCmd->Bindings) != S_OK)
			{
				return S_FALSE;
			}
		}
	}
	else
	{
		EnvDTE::CommandPtr pCurCommand = NULL;
		_bstr_t commandname = AddinString();
		commandname += pCmd->Name;
		pCommands->Item(_variant_t(commandname), 0, &pCurCommand);
		if (pCurCommand == NULL)
		{
			return E_FAIL;
		}

		if ((pCmd->iCmdBar != CMDBAR_NO) && (WtlHelperCmdBars[pCmd->iCmdBar].pCmdBar != NULL))
		{
#ifdef _FOR_VS2005
			if (FAILED(pCurCommand->AddControl(WtlHelperCmdBars[pCmd->iCmdBar].pCmdBar, 
				pCmd->lPos,	(IDispatch**)&pCommandBarControl)) || (pCommandBarControl == NULL))
#else
			if (FAILED(pCurCommand->AddControl(WtlHelperCmdBars[pCmd->iCmdBar].pCmdBar, 
				pCmd->lPos, &pCommandBarControl)) || (pCommandBarControl == NULL))
#endif
			{
				return E_FAIL;
			}
		}

		if (pCurCommand->put_Bindings(pCmd->Bindings) != S_OK)
		{
			return S_FALSE;	
		}

	}
	return S_OK;
}

STDMETHODIMP CConnect::OnDisconnection(AddInDesignerObjects::ext_DisconnectMode /*RemoveMode*/, SAFEARRAY ** /*custom*/ )
{
	HRESULT hr = S_OK;
	
	m_pDTE.Release();
	m_pAddInInstance.Release();
	_AtlModule.Destroy();
	return hr;
}

STDMETHODIMP CConnect::OnAddInsUpdate (SAFEARRAY ** /*custom*/ )
{
	return S_OK;
}

STDMETHODIMP CConnect::OnStartupComplete (SAFEARRAY ** /*custom*/ )
{
	return S_OK;
}

STDMETHODIMP CConnect::OnBeginShutdown (SAFEARRAY ** /*custom*/ )
{
	return S_OK;
}

STDMETHODIMP CConnect::QueryStatus(BSTR bstrCmdName, EnvDTE::vsCommandStatusTextWanted NeededText, EnvDTE::vsCommandStatus *pStatusOption, VARIANT *pvarCommandText)
{
	if(NeededText == EnvDTE::vsCommandStatusTextWantedNone)
	{
		if(!_wcsicmp(bstrCmdName, CMD(WtlHelper)))
		{
			*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusEnabled+EnvDTE::vsCommandStatusSupported);
		}
		else
		{
			int a = 0;
		}
		if(!_wcsicmp(bstrCmdName, CMD(AddFunction)))
		{
			*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusEnabled+EnvDTE::vsCommandStatusSupported);
		}
		if(!_wcsicmp(bstrCmdName, CMD(AddVariable)))
		{
			*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusEnabled+EnvDTE::vsCommandStatusSupported);
		}
		if(!_wcsicmp(bstrCmdName, CMD(Options)))
		{
			*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusEnabled+EnvDTE::vsCommandStatusSupported);
		}
		if (!_wcsicmp(bstrCmdName, CMD(ClassView_Handlers)))
		{
			EnvDTE::ProjectPtr pProj;
			if (GetSelectedClass(pProj) != NULL)
			{
				*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusEnabled+EnvDTE::vsCommandStatusSupported);
			}
			else
			{
				*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusInvisible+EnvDTE::vsCommandStatusSupported);
			}
		}
		if (!_wcsicmp(bstrCmdName, CMD(ClassView_Variables)))
		{
			EnvDTE::ProjectPtr pProj;
			if (GetSelectedClass(pProj) != NULL)
			{
				*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusEnabled+EnvDTE::vsCommandStatusSupported);
			}
			else
			{
				*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusInvisible+EnvDTE::vsCommandStatusSupported);
			}
		}
		if (!_wcsicmp(bstrCmdName, CMD(ResView_DDX)))
		{
			CString ResourceID;
			CString RCFileName;
			if (GetActiveResourceType(ResourceID, RCFileName) == _T("Dialog") && !IsMultipleSelected())
			{
				*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusEnabled+EnvDTE::vsCommandStatusSupported);
			}
			else
			{
				*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusInvisible+EnvDTE::vsCommandStatusSupported);
			}
		}
		if (!_wcsicmp(bstrCmdName, CMD(ResView_DDX_Mult)))
		{
			CString ResourceID;
			CString RCFileName;
			if (GetActiveResourceType(ResourceID, RCFileName) == _T("Dialog") && IsMultipleSelected())
			{
				*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusEnabled+EnvDTE::vsCommandStatusSupported);
			}
			else
			{
				*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusInvisible+EnvDTE::vsCommandStatusSupported);
			}
		}

		if (!_wcsicmp(bstrCmdName, CMD(ResView_Handler_Mult)))
		{
			CString ResourceID;
			CString RCFileName;
			if (IsPossibleResourceType(GetActiveResourceType(ResourceID, RCFileName)) && IsMultipleSelected())
			{
				*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusEnabled+EnvDTE::vsCommandStatusSupported);
			}
			else
			{
				*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusInvisible+EnvDTE::vsCommandStatusSupported);
			}
		}

		if (!_wcsicmp(bstrCmdName, CMD(ResView_Handler)) ||
			!_wcsicmp(bstrCmdName, CMD(MenuDesign_Handler)))
		{
			CString ResourceID;
			CString RCFileName;
			if (IsPossibleResourceType(GetActiveResourceType(ResourceID, RCFileName)) && !IsMultipleSelected())
			{
				*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusEnabled+EnvDTE::vsCommandStatusSupported);
			}
			else
			{
				*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusInvisible+EnvDTE::vsCommandStatusSupported);
			}
		}
		if (!_wcsicmp(bstrCmdName, CMD(ResView_Dialog)))
		{
			CString ResourceID;
			CString RCFileName;
			if (GetActiveResourceType(ResourceID, RCFileName) == _T("Dialog") && IsDialogSelected())
			{
				*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusEnabled+EnvDTE::vsCommandStatusSupported);
			}
			else
			{
				*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusInvisible+EnvDTE::vsCommandStatusSupported);
			}
		}
		if (!_wcsicmp(bstrCmdName, CMD(ResViewContext_Handler)))
		{
			if (IsDialogSelected())
			{
				*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusEnabled+EnvDTE::vsCommandStatusSupported);
			}
			else
			{
				*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusInvisible+EnvDTE::vsCommandStatusSupported);
			}
		}
		if (!_wcsicmp(bstrCmdName, CMD(ResViewContext_DDX)))
		{
			if (IsDialogSelected())
			{
				*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusEnabled+EnvDTE::vsCommandStatusSupported);
			}
			else
			{
				*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusInvisible+EnvDTE::vsCommandStatusSupported);
			}
		}
		if (!_wcsicmp(bstrCmdName, CMD(ResViewContext_Dialog)))
		{
			if (IsDialogSelected())
			{
				*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusEnabled+EnvDTE::vsCommandStatusSupported);
			}
			else
			{
				*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusInvisible+EnvDTE::vsCommandStatusSupported);
			}
		}
		if (!_wcsicmp(bstrCmdName, CMD(ResView_Reflect)))
		{
			CString ResourceID;
			CString RCFileName;
			if (GetActiveResourceType(ResourceID, RCFileName) == _T("Dialog") 
				&& !IsMultipleSelected()
				&& _AtlModule.m_eWTLVersion >= eWTL75)
			{
				*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusEnabled+EnvDTE::vsCommandStatusSupported);
			}
			else
			{
				*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusInvisible+EnvDTE::vsCommandStatusSupported);
			}
		}
#ifdef _FOR_VS2005
		if (!_wcsicmp(bstrCmdName, CMD(Uninstall)))
		{
			*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusEnabled+EnvDTE::vsCommandStatusSupported);
		}
#endif
	}
	
	return S_OK;
}

STDMETHODIMP CConnect::Exec(BSTR bstrCmdName, EnvDTE::vsCommandExecOption ExecuteOption, VARIANT * /*pvarVariantIn*/, VARIANT * /*pvarVariantOut*/, VARIANT_BOOL *pvbHandled)
{
	*pvbHandled = VARIANT_FALSE;
	if(ExecuteOption == EnvDTE::vsCommandExecOptionDoDefault)
	{
		if(!_wcsicmp(bstrCmdName, CMD(WtlHelper)))
		{
			*pvbHandled = VARIANT_TRUE;
			DoAddin();
		}
		if (!_wcsicmp(bstrCmdName, CMD(AddFunction)))
		{
			*pvbHandled = VARIANT_TRUE;
			DoAddFunction();
		}
		if (!_wcsicmp(bstrCmdName, CMD(AddVariable)))
		{
			*pvbHandled = VARIANT_TRUE;
			DoAddVariable();
		}
		if (!_wcsicmp(bstrCmdName, CMD(Options)))
		{
			*pvbHandled = VARIANT_TRUE;
			DoOptions();
		}
		if (!_wcsicmp(bstrCmdName, CMD(ClassView_Handlers)))
		{
			*pvbHandled = VARIANT_TRUE;
			DoClassViewHandler();
		}
		if (!_wcsicmp(bstrCmdName, CMD(ClassView_Variables)))
		{
			*pvbHandled = VARIANT_TRUE;
			DoClassViewVariable();
		}
		if (!_wcsicmp(bstrCmdName, CMD(ResView_DDX)) ||
			!_wcsicmp(bstrCmdName, CMD(ResView_DDX_Mult)))
		{
			*pvbHandled = VARIANT_TRUE;
			DoResViewDDX();
		}
		if (!_wcsicmp(bstrCmdName, CMD(ResView_Handler)) ||
			!_wcsicmp(bstrCmdName, CMD(ResView_Handler_Mult)) ||
			!_wcsicmp(bstrCmdName, CMD(MenuDesign_Handler)))
		{
			*pvbHandled = VARIANT_TRUE;
			DoResViewHandler();
		}
		if (!_wcsicmp(bstrCmdName, CMD(ResView_Dialog)))
		{
			*pvbHandled = VARIANT_TRUE;
			DoResViewDialog();
		}
		if (!_wcsicmp(bstrCmdName, CMD(ResViewContext_Dialog)))
		{
			*pvbHandled = VARIANT_TRUE;
			DoResViewContextDialog();
		}
		if (!_wcsicmp(bstrCmdName, CMD(ResViewContext_Handler)))
		{
			*pvbHandled = VARIANT_TRUE;
			DoResViewContextHandler();
		}
		if (!_wcsicmp(bstrCmdName, CMD(ResViewContext_DDX)))
		{
			*pvbHandled = VARIANT_TRUE;
			DoResViewContextDDX();
		}

		if (!_wcsicmp(bstrCmdName, CMD(ResView_Reflect)))
		{
			*pvbHandled = VARIANT_TRUE;
			DoResViewReflect();
		}
#ifdef _FOR_VS2005
		if (!_wcsicmp(bstrCmdName, CMD(Uninstall)))
		{
			UninstallAddin();
		}
#endif
	}
	return S_OK;
}

bool CConnect::ShowWTLHelper(EnvDTE::ProjectPtr pProj, CString ActiveClass, int ActivePage)
{
	_bstr_t str;
	_AtlModule.LoadAll();

	if (pProj == NULL)
	{
		if (GetActiveProject(pProj) != S_OK)
		{
			return false;
		}
	}
	g_pActiveProject = pProj;

	CSmartAtlArray<VSClass*> Classes;
	if (GetClasses(pProj, Classes) != S_OK)
	{
		return false;
	}
	if (!Classes.GetCount())
	{
		MessageBox(NULL, _T("No classes to work with!"), _T("No classes"), MB_OK | MB_ICONINFORMATION);
		return false;
	}
	SortClasses(Classes);
	size_t iCurClass =  GetActiveClass(Classes, ActiveClass);

	SaveResourceDocuments();

	CSmartAtlArray<InsDelPoints> Modifications;
	CResourceManager ResManager;
	CAtlArray<CString> ResFiles;

	ResManager.LoadResources(pProj);

	// set modifications count
	Modifications.SetCount(Classes.GetCount());

	CWtlHelperDlg dlg;
	dlg.m_pClassVector = &Classes;
	dlg.m_pModifications = &Modifications;
	dlg.m_piCurrentClass = (int*)&iCurClass;
	dlg.m_pResManager = &ResManager;
	dlg.m_iActivePage = ActivePage;

	if (dlg.DoModal() == IDOK)
	{
		UpdateClasses(&Modifications, &Classes);
		pProj->Save(NULL);
	}

	for (size_t i = 0; i < Classes.GetCount(); i++)
	{
		delete Classes[i];
	}
	Classes.RemoveAll();
#ifdef DEBUG
	MessageBox(NULL, _T("End Work"), NULL, 0);
#endif
	return true;
}

STDMETHODIMP CConnect::DoAddin()
{
	g_pSelectedFunction = NULL;
	ShowWTLHelper(EnvDTE::ProjectPtr(), CString(), -1);
	return S_OK;
}

HRESULT CConnect::DoAddFunction()
{
	EnvDTE::ProjectPtr pProj;
	if (GetActiveProject(pProj) != S_OK)
	{
		return S_FALSE;
	}

	CSmartAtlArray<VSClass*> Classes;
	if (GetClasses(pProj, Classes) != S_OK)
	{
		return S_FALSE;
	}

	VSClass* pCurClass = NULL;
	pCurClass = Classes[GetActiveClass(Classes, CString())];

	CAddMemberVarGl dlg;
	dlg.SetForFunction();
	dlg.m_pClassVector = &Classes;
	dlg.m_pCurClass = pCurClass;

	if ((dlg.DoModal() == IDOK) && (dlg.m_pCurClass))
	{
		VSFunction* pFunc = new VSFunction;
		pFunc->Type = dlg.m_Type;
		int n1 = dlg.m_Body.Find(_T('('));
		if (n1 == -1)
		{
			MessageBox(NULL, _T("It's not a function"), NULL, 0);
			return 0;
		}
		pFunc->Name = dlg.m_Body.Left(n1);
		pFunc->Name.Trim();
		if (dlg.m_bPublic)
		{
			pFunc->Access = EnvDTE::vsCMAccessPublic;
		}
		else
		{
			if (dlg.m_bProtected)
			{
				pFunc->Access = EnvDTE::vsCMAccessProtected;
			}
			else
			{
				pFunc->Access = EnvDTE::vsCMAccessPrivate;
			}
		}

		CString Params = dlg.m_Body.Mid(n1+1, dlg.m_Body.GetLength() - n1 - 2);
		int StartPos = 0;
		VSParameter* pParam;
		Params.Trim();
		if (!Params.IsEmpty())
		{
			while(StartPos >=0)
			{
				//определение параметров не совсем правильное
				//может быть ситуация int a b, int c
				CString Param1;
				int n2 = Params.Find(_T(','), StartPos);
				if (n2 != -1)
				{
					Param1 = Params.Mid(StartPos, n2 - StartPos);
					StartPos = n2+1;
				}
				else
				{
					Param1 = Params.Mid(StartPos);
					StartPos = -1;
				}
				Param1.Trim();
				int n3 = -1;
				int i = Param1.GetLength()-1;
				CString Delim = _T(" \t\r\n");

				//находим первый разделитель с конца
				while(i >= 0)
				{
					if (Delim.Find(Param1[i]) != -1)
					{
						n3 = i;
						break;
					}
					i--;
				}

				if (n3 == -1)
				{
					MessageBox(NULL, _T("Wrong parameter list"), NULL, 0);
					return 0;
				}

				pParam = new VSParameter;
				pParam->Name  = Param1.Mid(n3+1);
				pParam->Name.Trim();
				pParam->Type = Param1.Left(n3);
				pParam->Type.Trim();
				pFunc->Parameters.Add(pParam);

			};
		}
		pFunc->bConst = dlg.m_bConst;
		pFunc->bStatic = dlg.m_bStatic;
		pFunc->bVirtual = dlg.m_bVirtual;

		dlg.m_pCurClass->InsertFunction(pFunc, CString());
		delete pFunc;
	}

	return S_OK;
}

HRESULT CConnect::DoAddVariable()
{
	EnvDTE::ProjectPtr pProj;
	if (GetActiveProject(pProj) != S_OK)
	{
		return S_FALSE;
	}

	CSmartAtlArray<VSClass*> Classes;
	if (GetClasses(pProj, Classes) != S_OK)
	{
		return S_FALSE;
	}
	VSClass* pCurClass = NULL;

	pCurClass = Classes[GetActiveClass(Classes, CString())];

	CAddMemberVarGl dlg;
	dlg.SetForVar();
	dlg.m_pClassVector = &Classes;
	dlg.m_pCurClass = pCurClass;
	VARIANT_BOOL bStatic = VARIANT_FALSE;
	VARIANT_BOOL bConst = VARIANT_FALSE;

	if ((dlg.DoModal() == IDOK) && (dlg.m_pCurClass))
	{
		VSVariable* pVar = new VSVariable;
		pVar->Type = dlg.m_Type;
		pVar->Name = dlg.m_Body;
		if (dlg.m_bPublic)
		{
			pVar->Access = EnvDTE::vsCMAccessPublic;
		}
		else
		{
			if (dlg.m_bProtected)
			{
				pVar->Access = EnvDTE::vsCMAccessProtected;
			}
			else
			{
				pVar->Access = EnvDTE::vsCMAccessPrivate;
			}
		}
		while(pVar->Name[pVar->Name.GetLength()-1] == _T(';'))
		{
			pVar->Name.Delete(pVar->Name.GetLength()-1);
		}

		pVar->bConst = dlg.m_bConst;
		pVar->bStatic = dlg.m_bStatic;

		dlg.m_pCurClass->InsertVariable(pVar);
		delete pVar;
	}

	return S_OK;
}

HRESULT CConnect::DoOptions()
{
	g_pSelectedFunction = NULL;

	COptionsDlg dlg;
	dlg.DoModal();
	return S_OK;
}

HRESULT CConnect::DoClassViewHandler()
{
	g_pSelectedFunction = NULL;

	EnvDTE::ProjectPtr pProj;
	EnvDTE::CodeClassPtr pClass = GetSelectedClass(pProj);
	CString ClassName;
	if (pClass != NULL)
	{
		_bstr_t bsName;
		pClass->get_FullName(bsName.GetAddress());
		ClassName = (LPCTSTR)bsName;
	}
	ShowWTLHelper(pProj, ClassName, 0);
	return S_OK;
}

HRESULT CConnect::DoClassViewVariable()
{
	g_pSelectedFunction = NULL;

	EnvDTE::ProjectPtr pProj;
	EnvDTE::CodeClassPtr pClass = GetSelectedClass(pProj);
	CString ClassName;
	if (pClass != NULL)
	{
		_bstr_t bsName;
		pClass->get_FullName(bsName.GetAddress());
		ClassName = (LPCTSTR)bsName;
	}
	ShowWTLHelper(pProj, ClassName, 1);
	return S_OK;
}

HRESULT CConnect::DoResViewDDX()
{
	g_pSelectedFunction = NULL;

	EnvDTE::ProjectPtr pProj;
	int iDlgClass = -1;
	CAtlArray<CString> Controls;
	CSmartAtlArray<VSClass*> Classes;
	
	CSmartAtlArray<InsDelPoints> Modifications;
	CResourceManager ResManager;
	HRESULT hRes = PrepareDlgClass(pProj, Classes, iDlgClass, Controls, &ResManager);
	if (hRes == S_FALSE)
	{
		bool Res = ShowWTLHelper(pProj, Classes[iDlgClass]->Name, 1);
		for (size_t i = 0; i < Classes.GetCount(); i++)
		{
			delete Classes[i];
		}
		return Res ? S_OK : E_FAIL;
	}
	if (FAILED(hRes))
		return hRes;

	int iCurControl = -1;
	Classes[iDlgClass]->RetriveItems();
	Modifications.SetCount(Classes.GetCount());

	CDDXManager DDXManager;
	DDXManager.SetGlobalParams(NULL, &Modifications, &ResManager);
	DDXManager.Init(Classes[iDlgClass], &Modifications[iDlgClass]);
	for (size_t i = 0; i < Controls.GetCount() ;i++)
	{
		CString ControlID = Controls[i];
		if (ControlID == _T("IDC_STATIC"))
			continue;

		const CAtlArray<ResControl>& SelControls = DDXManager.GetControls();
		for (size_t j = 0; j < SelControls.GetCount(); j++)
		{
			if (SelControls[j].m_ID == ControlID)
			{
				iCurControl = (int)j;
				break;
			}
		}
		CString strCtrlId, strMemberName;
		VSMapEntry* pMapEntry = DDXManager.AddVariable(iCurControl, strCtrlId, strMemberName);
	}

	UpdateClasses(&Modifications, &Classes);
	for (size_t i = 0; i < Classes.GetCount(); i++)
	{
		delete Classes[i];
	}
	Classes.RemoveAll();

	return S_OK;
}

HRESULT CConnect::DoResViewHandler()
{
	g_pSelectedFunction = NULL;

	CString ResourceID, RCFileName;
	CString ResourceType = GetActiveResourceType(ResourceID, RCFileName);
	if (ResourceType == _T("Dialog"))
	{
		return AddDialogHandler(RCFileName, ResourceID);
	}
	if (ResourceType == _T("Menu") ||
		ResourceType == _T("Toolbar") ||
		ResourceType == _T("Accelerator"))
	{
		return AddIDHandler(RCFileName, ResourceID, ResourceType);
	}

	return S_OK;
}

HRESULT CConnect::DoResViewReflect()
{
	int iDlgClass;
	CAtlArray<CString> Controls;
	CSmartAtlArray<VSClass*> Classes;
	EnvDTE::ProjectPtr pProj;

	CString DialogID, RCFile;
	CString ResourceType = GetActiveResourceType(DialogID, RCFile);
	
	CResourceManager ResManager;
	CSmartAtlArray<InsDelPoints> Modifications;
	HRESULT hRes = PrepareDlgClass(pProj, Classes, iDlgClass, Controls, &ResManager);
	if (hRes == S_FALSE)
	{
		bool bRes = ShowWTLHelper(pProj, Classes[iDlgClass]->Name, 0);
		for (size_t i = 0; i < Classes.GetCount(); i++)
		{
			delete Classes[i];
		}
		Classes.RemoveAll();
		return bRes ? S_OK : E_FAIL;
	}
	if (FAILED(hRes))
		return hRes;

	int iCurControl = -1;
	Modifications.SetCount(Classes.GetCount());

	CMessageManager MessageManager;
	MessageManager.Init(NULL, &ResManager, NULL);
	MessageManager.SetClass(Classes[iDlgClass], &Modifications[iDlgClass]);
	const CResDialog* pCurDlg = ResManager.GetDialog(DialogID);

	for (size_t i = 0; i < Controls.GetCount() ;i++)
	{
		CString ControlID = Controls[i];
		if (ControlID == _T("IDC_STATIC"))
			continue;

		const ResControl* pControl = ResManager.GetDlgControl(pCurDlg, ControlID);
		HandlerStruct Handler;
		MessageStruct Mes;
		eControlType eType = ResManager.GetControlType(pControl->m_Type);
		if (eType == eCTCommand)
		{
			Mes.Type = CUSTOM_COMMAND_REFLECTION_HANDLER;
		}
		else if (eType == eCTNotify)
		{
			Mes.Type = CUSTOM_NOTIFY_REFLECTION_HANDLER;
		}
		else
		{
			Mes.Type = CUSTOM_REFLECTION_HANDLER;
		}
		MessageManager.InsertReflectionHandler(&Mes, Handler, pControl->m_ID);
	}
	UpdateClasses(&Modifications, &Classes);

	for (size_t i = 0; i < Classes.GetCount(); i++)
	{
		delete Classes[i];
	}
	Classes.RemoveAll();
	return S_OK;
}

HRESULT CConnect::DoResViewDialog()
{
	g_pSelectedFunction = NULL;

	CString DialogID;
	CString RCFileName;
	int iDlgClass = -1;
	if (GetActiveResourceType(DialogID, RCFileName) != _T("Dialog"))
		return S_OK;

	bool bDialogSelected = IsDialogSelected();

	CAtlArray<CString> Controls;
	if (!GetActiveControlID(Controls))
		return S_OK;

	_AtlModule.LoadAll();

	EnvDTE::ProjectPtr pProj;
	if (GetActiveProject(pProj) != S_OK)
	{
		return E_FAIL;
	}

	CSmartAtlArray<VSClass*> Classes;
	if (GetClasses(pProj, Classes) != S_OK)
	{
		return E_FAIL;
	}
	
	iDlgClass = FindClassByDlgID(Classes, DialogID);
	if (iDlgClass == -1)
	{
		CreateDialogClass(pProj, DialogID);
	}
	else
	{
		MessageBox(NULL, _T("Class for this dialog is already created!"), _T("Already created"), MB_ICONINFORMATION);
	}
	for (size_t i = 0; i < Classes.GetCount(); i++)
	{
		delete Classes[i];
	}
	return S_OK;
}

HRESULT CConnect::DoResViewContextDDX()
{
	g_pSelectedFunction = NULL;

	CSmartAtlArray<VSClass*> Classes;
	CAtlArray<CString> Controls;
	EnvDTE::ProjectPtr pProj;

	int iDlgClass = -1;
	
	if (!GetActiveControlID(Controls) || !Controls.GetCount())
		return S_OK;

	_AtlModule.LoadAll();

	if (GetSelectedProject(pProj) != S_OK)
	{
		return E_FAIL;
	}

	
	if (GetClasses(pProj, Classes) != S_OK)
	{
		return E_FAIL;
	}
	if (!Classes.GetCount())
	{
		MessageBox(NULL, _T("No classes to work with!"), _T("No classes"), MB_OK | MB_ICONINFORMATION);
		return E_FAIL;
	}

	CString DialogID = Controls[0];
	iDlgClass = FindClassByDlgID(Classes, DialogID);
	if (iDlgClass == -1)
	{
		if (CreateDialogClass(pProj, DialogID) == EnvDTE::wizardResultSuccess)
		{
			for (size_t i = 0; i < Classes.GetCount(); i++)
			{
				delete Classes[i];
			}
			Classes.RemoveAll();
			if (GetClasses(pProj, Classes) != S_OK)
			{
				return E_FAIL;
			}
			iDlgClass = FindClassByDlgID(Classes, DialogID);
		}

		if (iDlgClass == -1)
			return S_OK;
	}

	bool Res = ShowWTLHelper(pProj, Classes[iDlgClass]->Name, 1);
		
	for (size_t i = 0; i < Classes.GetCount(); i++)
	{
		delete Classes[i];
	}

	return S_OK;
}

HRESULT CConnect::DoResViewContextHandler()
{
	g_pSelectedFunction = NULL;

	CSmartAtlArray<VSClass*> Classes;
	CAtlArray<CString> Controls;
	EnvDTE::ProjectPtr pProj;

	int iDlgClass = -1;

	if (!GetActiveControlID(Controls) || !Controls.GetCount())
		return S_OK;

	_AtlModule.LoadAll();

	if (GetSelectedProject(pProj) != S_OK)
	{
		return E_FAIL;
	}

	if (GetClasses(pProj, Classes) != S_OK)
	{
		return E_FAIL;
	}
	if (!Classes.GetCount())
	{
		MessageBox(NULL, _T("No classes to work with!"), _T("No classes"), MB_OK | MB_ICONINFORMATION);
		return false;
	}

	CString DialogID = Controls[0];
	iDlgClass = FindClassByDlgID(Classes, DialogID);
	if (iDlgClass == -1)
	{
		if (CreateDialogClass(pProj, DialogID) == EnvDTE::wizardResultSuccess)
		{
			for (size_t i = 0; i < Classes.GetCount(); i++)
			{
				delete Classes[i];
			}
			Classes.RemoveAll();
			if (GetClasses(pProj, Classes) != S_OK)
			{
				return E_FAIL;
			}
			iDlgClass = FindClassByDlgID(Classes, DialogID);
		}

		if (iDlgClass == -1)
			return S_OK;
	}

	bool bRes = ShowWTLHelper(pProj, Classes[iDlgClass]->Name, 0);
	
	for (size_t i = 0; i < Classes.GetCount(); i++)
	{
		delete Classes[i];
	}
	Classes.RemoveAll();
	return S_OK;
}

HRESULT CConnect::DoResViewContextDialog()
{
	g_pSelectedFunction = NULL;

	int iDlgClass = -1;
	CAtlArray<CString> Controls;
	CSmartAtlArray<VSClass*> Classes;

	if (!GetActiveControlID(Controls) || !Controls.GetCount())
		return S_OK;

	_AtlModule.LoadAll();

	EnvDTE::ProjectPtr pProj;
	if (GetSelectedProject(pProj) != S_OK)
	{
		return E_FAIL;
	}

	
	if (GetClasses(pProj, Classes) != S_OK)
	{
		return E_FAIL;
	}

	CString DialogID = Controls[0];
	iDlgClass = FindClassByDlgID(Classes, DialogID);
	if (iDlgClass == -1)
	{
		CreateDialogClass(pProj, DialogID);
	}
	else
	{
		MessageBox(NULL, _T("Class for this dialog is already created!"), _T("Already created"), MB_ICONINFORMATION);
	}
	for (size_t i = 0; i < Classes.GetCount(); i++)
	{
		delete Classes[i];
	}
	return S_OK;
}

EnvDTE::CodeClassPtr CConnect::GetSelectedClass(EnvDTE::ProjectPtr& pProj)
{
	EnvDTE::SelectedItemsPtr pSelItems;
	EnvDTE::CodeClassPtr pClass;
	if (m_pDTE->get_SelectedItems(&pSelItems) == S_OK)
	{
		ATLASSERT(pSelItems != NULL);
		long Count;
		pSelItems->get_Count(&Count);
		if (Count)
		{
			EnvDTE::SelectedItemPtr pSelItem;
			pSelItems->Item(_variant_t(1), &pSelItem);
			ATLASSERT(pSelItem != NULL);
			EnvDTE::ProjectItemPtr pProjItem;
			pSelItem->get_ProjectItem(&pProjItem);
			if (pProjItem != NULL)
			{
				pProjItem->get_ContainingProject(&pProj);
			}
		}
				
		EnvDTE::SelectionContainerPtr pSelContainer;
		if (pSelItems->get_SelectionContainer(&pSelContainer) == S_OK)
		{
			if (pSelContainer != NULL)
			{
				IDispatchPtr pObject;
				pSelContainer->Item(_variant_t(1), &pObject);
				pClass = pObject;
			}
		}
	}
	return pClass;
}

HRESULT CConnect::GetActiveProject(EnvDTE::ProjectPtr& pProj)
{
	EnvDTE::DocumentPtr pCurDoc;
	m_pDTE->get_ActiveDocument(&pCurDoc);
	if (pCurDoc != NULL)
	{
		EnvDTE::ProjectItemPtr pProjItem;
		pCurDoc->get_ProjectItem(&pProjItem);
		if (pProjItem == NULL)
		{
			return E_FAIL;
		}
		return pProjItem->get_ContainingProject(&pProj);
	}
	else
	{
		_variant_t vt, vt2;

		if (FAILED(m_pDTE->get_ActiveSolutionProjects(&vt)))
		{
			return S_FALSE;
		}

		if (vt.vt != (VT_ARRAY | VT_VARIANT))
		{
			return S_FALSE;
		}
		SAFEARRAY* pArray = vt.parray;
		if (pArray->cDims != 1 && !(pArray->fFeatures & FADF_DISPATCH ))
		{
			return S_FALSE;
		}

		if (pArray[0].rgsabound[0].cElements > 0)
		{
			vt2 = ((_variant_t*)pArray[0].pvData)[0];
			pProj = vt2.pdispVal;
			if (pProj == NULL)
			{
				return S_FALSE;
			}
		}
		else
			return S_FALSE;
	}

	return S_OK;
}

HRESULT CConnect::GetSelectedProject(EnvDTE::ProjectPtr& pProj)
{
	EnvDTE::SelectedItemsPtr pSelItems;
	if (m_pDTE->get_SelectedItems(&pSelItems) == S_OK)
	{
		ATLASSERT(pSelItems != NULL);
		long Count;
		pSelItems->get_Count(&Count);
		if (Count)
		{
			EnvDTE::SelectedItemPtr pSelItem;
			pSelItems->Item(_variant_t(1), &pSelItem);
			ATLASSERT(pSelItem != NULL);
			EnvDTE::ProjectItemPtr pProjItem;
			pSelItem->get_ProjectItem(&pProjItem);
			if (pProjItem != NULL)
			{
				return pProjItem->get_ContainingProject(&pProj);
			}
		}
	}
	return E_FAIL;
}

EnvDTE::CodeElementPtr CConnect::GetClassFromMember(EnvDTE::CodeElementPtr pMember)
{
	EnvDTE::CodeElementPtr pParrentElem;
	EnvDTE::CodeElementsPtr pColection = NULL;
	if (FAILED(pMember->get_Collection(&pColection)) || (pColection == NULL))
	{
		return pParrentElem;
	}

	IDispatch* pPar = NULL;
	pColection->get_Parent((IDispatch**)&pPar);
	pParrentElem = pPar;
	return pParrentElem;
}

EnvDTE::wizardResult CConnect::CreateDialogClass(EnvDTE::ProjectPtr pProj, CString DialogID, bool bShow /* = false */)
{
	CString WizardPath;
	LPCTSTR lpVersion = _T("1.1");
	eWizardsErrors Res = GetWTLDLGWizardPath(WizardPath, lpVersion);
	switch(Res) 
	{
	case eWizardsNotInstalled:
		{
			MessageBox(NULL, _T("WTL Wizards are not installed!\r\nYou cannot create new dialog class"), _T("No WTL Wizards"), MB_ICONWARNING);
			return EnvDTE::wizardResultFailure;
		}
	case eWTLDLGNotInstalled:
		{
			MessageBox(NULL, _T("WTL Dialog Wizard is not installed!\r\nYou cannot create new dialog class"), _T("No WTL Wizards"), MB_ICONWARNING);
			return EnvDTE::wizardResultFailure;
		}
	case eWrongVersion:
		{
			CString Mes;
			Mes.Format(_T("You need at least version %s of WTL Wizards to create new dialog class"), lpVersion);
			MessageBox(NULL, Mes, _T("No WTL Wizards"), MB_ICONWARNING);
			return EnvDTE::wizardResultFailure;
		}
	case eError:
		{
			MessageBox(NULL, _T("Unknow error!\r\nYou cannot create new dialog class"), _T("No WTL Wizards"), MB_ICONERROR);
			return EnvDTE::wizardResultFailure;
		}
	}
	CComSafeArray<VARIANT> ContextParams;
	_bstr_t Str;
	ContextParams.Add(_variant_t(EnvDTE::vsWizardAddItem));
	pProj->get_Name(Str.GetAddress());
	ContextParams.Add(_variant_t(Str));
	EnvDTE::ProjectItemsPtr pProjItems;
	pProj->get_ProjectItems(&pProjItems);
	pProj->get_FullName(Str.GetAddress());
	CString FullName = (LPCTSTR)Str;
	int Pos = FullName.ReverseFind(_T('\\'));
	FullName.Delete(Pos, FullName.GetLength() - Pos);
	ContextParams.Add(_variant_t((LPDISPATCH)pProjItems));
	ContextParams.Add(_variant_t(FullName));
	ContextParams.Add(_variant_t((char*)NULL));
	ContextParams.Add(_variant_t(L"c:\\Program Files\\Microsoft Visual Studio .NET 2003\\Vc7"));
	ContextParams.Add(_variant_t(false));
	EnvDTE::wizardResult Result;
	//generate vsz file
	CStringA VSZData = "VSWIZARD 7.0\r\nWizard=VsWizard.VsWizardEngine.";
	_bstr_t DTEVersion;
	m_pDTE->get_Version(DTEVersion.GetAddress());
	CStringA strVersion((char*)DTEVersion);
	int iVLen = strVersion.GetLength();
	if ((iVLen >= 2) && (strVersion[iVLen - 1] == '0') && (strVersion[iVLen - 2] != '.'))
	{
		strVersion.Delete(iVLen - 1);
	}
	
	VSZData += strVersion;
	VSZData += "\r\nParam=\"WIZARD_NAME = WTLDLG\"\r\n";
	CStringA WizPath(WizardPath);
	VSZData += "Param=\"ABSOLUTE_PATH = " + WizPath + "\"\r\n";
	VSZData += CStringA("Param=\"DIALOG_ID = ") + CStringA(DialogID) + "\"\r\n";
	VSZData += CStringA("Param=\"SHOW_AFTER_CREATE = ") + (bShow ? "true\"" : "false\"");
	VSZData += "\r\n";
	//create vsz file in temporary directory
	TCHAR Buf[FILENAME_MAX];
	GetTempPath(FILENAME_MAX, Buf);
	CString FileName = Buf;
	if (FileName[FileName.GetLength() - 1] == _T('\\'))
		FileName += _T("WTLDLG.vsz");
	else
		FileName += _T("\\WTLDLG.vsz");
	CAtlFile File;
	if (FAILED(File.Create(FileName, FILE_ALL_ACCESS, 0, CREATE_ALWAYS)))
		return EnvDTE::wizardResultFailure;
	File.Write(VSZData, (DWORD)VSZData.GetLength());
	File.Flush();
	File.Close();

	HRESULT hr = m_pDTE->LaunchWizard(_bstr_t(FileName), &ContextParams.m_psa, &Result);
	DeleteFile(FileName);

	return Result;
}

eWizardsErrors CConnect::GetWTLDLGWizardPath(CString& Path, LPCTSTR lpMinVersion)
{
	CRegKey Key;
	if (Key.Open(HKEY_LOCAL_MACHINE, _T("Software\\SaloS\\WTL Wizards"), KEY_READ) == ERROR_SUCCESS)
	{
		ULONG Len;
		CString RegPath;
		LONG Res = Key.QueryStringValue(_T("InstallPath"), NULL, &Len);
		if (Res == ERROR_MORE_DATA || Res == ERROR_SUCCESS)
		{
			Key.QueryStringValue(_T("InstallPath"), RegPath.GetBuffer(Len + 1), &Len);
			RegPath.ReleaseBuffer();

			TCHAR VersionBuf[256];
			Len = 256;
			Res = Key.QueryStringValue(_T("Version"), VersionBuf, &Len);
			if (Res == ERROR_SUCCESS)
			{
				if (lpMinVersion)
				{
					if (CompareVersions(VersionBuf, lpMinVersion) < 0)
						return eWrongVersion;
				}
				Path = RegPath + _T("WTLDLG");
				return eSuccess;
			}
		}
	}

	LPCTSTR lpProductCode = TEXT("{C1EBF990-BE54-4e43-BA92-D0731263B016}");
	UINT Res;

	Res = MsiQueryProductState(lpProductCode);
	if (Res != INSTALLSTATE_DEFAULT)
	{
		return eWizardsNotInstalled;
	}
	TCHAR buf[FILENAME_MAX];
	DWORD dwSize = FILENAME_MAX;

	Res = MsiGetProductInfo(lpProductCode, INSTALLPROPERTY_VERSIONSTRING, buf, &dwSize);
	if (Res != ERROR_SUCCESS)
	{
		return eError;
	}
	buf[dwSize] = 0;
	if (lpMinVersion)
	{
		if (CompareVersions(buf, lpMinVersion) < 0)
			return eWrongVersion;
	}

	dwSize = FILENAME_MAX;
	Res = MsiGetComponentPath(lpProductCode, _T("{6802889B-ADEB-45eb-885D-C55144ADE507}"), buf, &dwSize);
	if (Res == INSTALLSTATE_ABSENT || Res == INSTALLSTATE_UNKNOWN)
	{
		return eWTLDLGNotInstalled;
	}
	buf[dwSize] = 0;
	LPCTSTR lpEndPath = _tcsstr(buf, _T("\\HTML"));
	if (lpEndPath != NULL)
	{
		Path = CString(buf, (int)(lpEndPath - buf));
	}

	return eSuccess;
}

CString CConnect::GetActiveClass(EnvDTE::TextPointPtr& pCurPoint)
{
	EnvDTE::DocumentPtr pDoc = NULL;
	if (FAILED(m_pDTE->get_ActiveDocument(&pDoc)) || (pDoc == NULL))
	{
		return CString();
	}

	EnvDTE::ProjectItemPtr pItem = NULL;
	if (FAILED(pDoc->get_ProjectItem(&pItem)) || (pItem == NULL))
	{
		return CString();
	}

	EnvDTE::FileCodeModelPtr pFileModel = NULL;
	if (FAILED(pItem->get_FileCodeModel(&pFileModel)) || pFileModel == NULL)
	{
		return CString();
	}

	EnvDTE::TextSelectionPtr pSel;
	IDispatch* pDisp = NULL;
	if (FAILED(pDoc->get_Selection(&pDisp)) || !pDisp)
	{
		return CString();
	}
	pSel = pDisp;
	if (pSel != NULL)
	{
		EnvDTE::VirtualPointPtr pCurPos = NULL;
		if (FAILED(pSel->get_ActivePoint(&pCurPos)) || (pCurPos == NULL))
		{
			return CString();
		}

		EnvDTE::CodeElementPtr pElement = NULL;
		if (FAILED(pFileModel->CodeElementFromPoint(pCurPos, EnvDTE::vsCMElementClass, &pElement)) || (pElement == NULL))
		{
			pFileModel->CodeElementFromPoint(pCurPos, EnvDTE::vsCMElementFunction, &pElement);
		}
		if (pElement != NULL)
		{
			VSElement Elem(EnvDTE::vsCMElementOther);
			EnvDTE::vsCMElement ElemType;
			pElement->get_Kind(&ElemType);

			if (ElemType == EnvDTE::vsCMElementClass)
			{
				Elem.pElement = pElement;
				Elem.RetriveName(true);
				pCurPoint = pCurPos;
			}

			if (ElemType == EnvDTE::vsCMElementFunction)
			{
				EnvDTE::CodeElementPtr pParrentElem = GetClassFromMember(pElement);
				
				Elem.pElement = pParrentElem;
				Elem.RetriveName(true);
			}
			return Elem.Name;
		}
	}

	if (pFileModel != NULL)
	{
		EnvDTE::CodeElementsPtr Elements;
		pFileModel->get_CodeElements(&Elements);
		long Count;
		Elements->get_Count(&Count);
		EnvDTE::CodeElementPtr pElem;
		CString ClassName;
		for (long i = 1; i <= Count; i++)
		{
			Elements->Item(_variant_t(i), &pElem);
			
			EnvDTE::vsCMElement ElemType;
			pElem->get_Kind(&ElemType);
#ifdef _DEBUG
			_bstr_t bsName;
			pElem->get_Name(bsName.GetAddress());
#endif
			
			if (ElemType == EnvDTE::vsCMElementClass)
			{
				_bstr_t Name;
				pElem->get_FullName(Name.GetAddress());
				ClassName = (LPCTSTR)Name;
				break;
			}
			if (ElemType == EnvDTE::vsCMElementFunction)
			{
				EnvDTE::CodeElementPtr pClass = GetClassFromMember(pElem);
				_bstr_t Name;
				pClass->get_FullName(Name.GetAddress());
				ClassName = (LPCTSTR)Name;
				break;
			}
		}
		return ClassName;
	}
	return CString();
}

int CConnect::GetActiveClass(CSmartAtlArray<VSClass*>& Classes, CString ClassName)
{
	EnvDTE::TextPointPtr pCurPtr;
	CString CurrentClass;
	if (ClassName.IsEmpty())
	{
		CurrentClass = GetActiveClass(pCurPtr);
	}
	else
	{
		CurrentClass = ClassName;
	}
	int iCurClass = 0;

	for (size_t j = 0; j < Classes.GetCount(); j++)
	{
		if (Classes[j]->Name == CurrentClass)
		{
			if (pCurPtr != NULL)
			{
				//probably nested classes
				VSClass* pCurClass = Classes[j];
				bool bNestedClass = false;
				for (size_t k = 0; k < pCurClass->NestedClasses.GetCount(); k++)
				{
					VSClass* pNestedClass = pCurClass->NestedClasses[k];
					EnvDTE::EditPointPtr pStart, pEnd;
					pNestedClass->GetStartPoint(&pStart);
					pNestedClass->GetEndPoint(&pEnd);
					VARIANT_BOOL bInside = VARIANT_FALSE;
					pCurPtr->GreaterThan(pStart, &bInside);
					if (bInside == VARIANT_TRUE)
					{
						pCurPtr->LessThan(pEnd, &bInside);
						if (bInside == VARIANT_TRUE)
						{
							//found that active is nested class
							//change name and go to next step because
							//nested classes are after parent class
							CurrentClass = pNestedClass->Name;
							bNestedClass = true;
							break;
						}
					}
				}
				if (bNestedClass)
					continue;
			}
			iCurClass = (int)j;
			break;
		}
	}
	return iCurClass;
}

CString CConnect::GetActiveResourceType(CString& ResourceID, CString& FileName)
{
	EnvDTE::WindowPtr pCurWindow;
	m_pDTE->get_ActiveWindow(&pCurWindow);
	if (pCurWindow == NULL)
		return CString();

	_bstr_t WindowCaption;
	pCurWindow->get_Caption(WindowCaption.GetAddress());
	CString strCaption = WindowCaption;
	CString ResourceType;
	int OpenBracket = strCaption.Find(_T('('));
	int CloseBracket = strCaption.ReverseFind(_T(')'));
	if (OpenBracket != -1 && CloseBracket != -1)
	{
		FileName = strCaption.Left(OpenBracket);
		FileName.Trim();
		strCaption = strCaption.Mid(OpenBracket + 1, CloseBracket - OpenBracket-1);
		strCaption.Trim();
		int iDash = strCaption.ReverseFind(_T('-'));
		if (iDash == -1)
		{
			ResourceType = strCaption;
		}
		else
		{
			ResourceType = strCaption.Mid(iDash + 1);
			ResourceType.Trim();
			ResourceID = strCaption.Left(iDash);
			ResourceID.Trim();
		}
	}
	return ResourceType;
}

bool CConnect::IsPossibleResourceType(CString ResourceType)
{
	if (ResourceType == _T("Dialog") || ResourceType == _T("Menu") ||
		ResourceType == _T("Accelerator") || ResourceType == _T("Toolbar"))
	{
		return true;
	}
	return false;
}

bool CConnect::IsDialogSelected()
{
	EnvDTE::SelectedItemsPtr pSelItems;
	EnvDTE::SelectionContainerPtr pSelContainer;
	m_pDTE->get_SelectedItems(&pSelItems);

	IDispatchPtr pObject;
	pSelItems->get_SelectionContainer(&pSelContainer);
	if (pSelContainer == NULL)
		return false;

	long Count;
	pSelContainer->get_Count(&Count);
	bool bRes = false;
	if (Count)
	{
		pSelContainer->Item(_variant_t(1), &pObject);
		if (pObject == NULL)
		{
			return false;
		}
		ITypeInfoPtr pTypeInfo;
		pObject->GetTypeInfo(1, GetSystemDefaultLCID(), &pTypeInfo);
		if (pTypeInfo != NULL)
		{
			LPTYPEATTR pTypeAttr;
			pTypeInfo->GetTypeAttr(&pTypeAttr);
			if (pTypeAttr->guid == __uuidof(ResEditPKGLib::IDlgEditor) ||
				pTypeAttr->guid == __uuidof(ResEditPKGLib::IDlgRes))
			{
				bRes = true;
			}
			pTypeInfo->ReleaseTypeAttr(pTypeAttr);
		}
	}
	return bRes;
}

bool CConnect::IsMultipleSelected()
{
	EnvDTE::SelectedItemsPtr pSelItems;
	EnvDTE::SelectionContainerPtr pSelContainer;
	m_pDTE->get_SelectedItems(&pSelItems);

	pSelItems->get_SelectionContainer(&pSelContainer);
	long Count;
	pSelContainer->get_Count(&Count);
	return (Count > 1);
}

bool CConnect::GetActiveControlID(CAtlArray<CString>& ActiveControls)
{
	CString ResID;
	EnvDTE::SelectedItemsPtr pSelItems;
	EnvDTE::SelectionContainerPtr pSelContainer;
	m_pDTE->get_SelectedItems(&pSelItems);

	IDispatchPtr pObject;
	pSelItems->get_SelectionContainer(&pSelContainer);
	long Count;
	pSelContainer->get_Count(&Count);
	for (long i = 1; i <= Count; i++)
	{
		pSelContainer->Item(_variant_t(i), &pObject);
		if (pObject == NULL)
		{
			return false;
		}
		_variant_t varRes;
		HRESULT hr = GetDispatchProperty(pObject, L"ID", &varRes);
		if (hr == S_OK)
		{
			_bstr_t bsID = varRes;
			ResID = (LPCTSTR)bsID;
			ActiveControls.Add(ResID);
		}
	}
	return (Count > 0);
}

int CConnect::FindClassByDlgID(ClassVector Classes, CString DialogID)
{
	int iDlgClass = -1;
	for (size_t i = 0; i < Classes.GetCount(); i++)
	{
		VCCodeModelLibrary::VCCodeClassPtr pVCClass = Classes[i]->pElement;
		EnvDTE::CodeElementsPtr pEnums = pVCClass->Enums;
		long Count;
		pEnums->get_Count(&Count);
		for (long j = 1; j <= Count; j++ )
		{
			EnvDTE::CodeElementPtr pElem;
			pEnums->Item(_variant_t(j), &pElem);
			VCCodeModelLibrary::VCCodeEnumPtr pEnum = pElem;
			if (pEnum != NULL)
			{
				EnvDTE::CodeElementsPtr pMembers = pEnum->Members;
				EnvDTE::CodeVariablePtr pMember;
				pMembers->Item(_variant_t(L"IDD"), &pElem);
				pMember = pElem;
				if (pMember != NULL)
				{
					_bstr_t Value;
					_variant_t vt;
					pMember->get_InitExpression(&vt);
					Value = vt;
					if ((LPCTSTR)Value == DialogID)
					{
						iDlgClass = (int)i;
						break;
					}
				}
			}
		}
	}
	return iDlgClass;
}

void CConnect::SaveResourceDocuments()
{
	// save resource files
	// information about resources is got from files directly
	// so this step is important
	EnvDTE::DocumentsPtr pDocuments;
	m_pDTE->get_Documents(&pDocuments);
	if (pDocuments != NULL)
	{
		long Count;
		pDocuments->get_Count(&Count);
		for (long i = 1; i <= Count; i++)
		{
			EnvDTE::DocumentPtr pDoc;
			pDocuments->Item(_variant_t(i), &pDoc);
			_bstr_t str;
			pDoc->get_FullName(str.GetAddress());
			CString Name = str;
			if (Name.Right(3) == _T(".rc"))
			{
				VARIANT_BOOL bSaved = VARIANT_FALSE;
				pDoc->get_Saved(&bSaved);
				if (bSaved == VARIANT_FALSE)
				{
					EnvDTE::vsSaveStatus SaveStatus;
					pDoc->Save(NULL, &SaveStatus);
				}
			}
		}
	}
}

HRESULT CConnect::AddDialogHandler(CString RCFile, CString DialogID)
{
	CAtlArray<CString> Controls;
	CSmartAtlArray<VSClass*> Classes;
	EnvDTE::ProjectPtr pProj;
	int iDlgClass;

	CSmartAtlArray<InsDelPoints> Modifications;
	CResourceManager ResManager;
	HRESULT hRes = PrepareDlgClass(pProj, Classes, iDlgClass, Controls, &ResManager);
	if (hRes == S_FALSE)
	{
		bool bRes = ShowWTLHelper(pProj, Classes[iDlgClass]->Name, 0);
		for (size_t i = 0; i < Classes.GetCount(); i++)
		{
			delete Classes[i];
		}
		Classes.RemoveAll();
		return bRes ? S_OK : E_FAIL;
	}
	
	if (FAILED(hRes))
		return hRes;

	int iCurControl = -1;
	Modifications.SetCount(Classes.GetCount());

	CMessageManager MessageManager;
	MessageManager.Init(NULL, &ResManager, NULL);
	const CResDialog* pCurDlg = ResManager.GetDialog(DialogID);
		
	for (size_t i = 0; i < Controls.GetCount() ;i++)
	{
		CString ControlID = Controls[i];
		if (ControlID == _T("IDC_STATIC"))
			continue;
		
		const ResControl* pControl = ResManager.GetDlgControl(pCurDlg, ControlID);
		MessageManager.InsertDialogControlMessageHandler(pControl, Classes, Modifications, iDlgClass);
	}
	UpdateClasses(&Modifications, &Classes);
	
	for (size_t i = 0; i < Classes.GetCount(); i++)
	{
		delete Classes[i];
	}
	Classes.RemoveAll();
	return S_OK;
}

HRESULT CConnect::AddIDHandler(CString RCFile, CString ResID, CString ResType)
{
	CAtlArray<CString> Controls;
	if (!GetActiveControlID(Controls))
		return S_OK;

	_AtlModule.LoadAll();

	EnvDTE::ProjectPtr pProj;
	if (GetActiveProject(pProj) != S_OK)
	{
		return false;
	}

	CSmartAtlArray<VSClass*> Classes;
	if (GetClasses(pProj, Classes) != S_OK)
	{
		return false;
	}
	if (!Classes.GetCount())
	{
		MessageBox(NULL, _T("No classes to work with!"), _T("No classes"), MB_OK | MB_ICONINFORMATION);
		return false;
	}

	SaveResourceDocuments();

	CSmartAtlArray<InsDelPoints> Modifications;
	CResourceManager ResManager;

	EnvDTE::ProjectItemPtr pRCFile = FindItem(pProj, _bstr_t(RCFile), EnvDTE::ProjectItemPtr());
	if (pRCFile != NULL)
	{
		ResManager.LoadResources(pRCFile);
	}

	int iCurControl = -1;
	Modifications.SetCount(Classes.GetCount());
	CMessageManager MessageManager;
	CAtlArray<CString> ResIds;
	if (ResType == _T("Menu"))
	{
		ResManager.GetMenuIds(ResID, ResIds);
	}
	if (ResType == _T("Toolbar"))
	{
		ResManager.GetToolbarIds(ResID, ResIds);
	}
	if (ResType == _T("Accelerator"))
	{
		ResManager.GetAcceleratorIds(ResID, ResIds);
	}
	MessageManager.Init(NULL, &ResManager, &ResIds);

	int iDefClass = -1;
	// select default class
	CString DefClassName = _T("CMainFrame");
	EnvDTE::GlobalsPtr pGlobals;
	pProj->get_Globals(&pGlobals);
	if (pGlobals != NULL)
	{
		CString ParamName = _T("WTLHELPER.")+ ResType + _T(".") + ResID;
		_variant_t vt;
		HRESULT hr = pGlobals->get_VariableValue(_bstr_t(ParamName), &vt);
		_bstr_t Value = vt;
		if (Value.length())
		{
			DefClassName = (LPCTSTR)Value;
		}
	}

	// find class in class list
	for (size_t i = 0; i < Classes.GetCount(); i++)
	{
		if (Classes[i]->Name == DefClassName)
		{
			iDefClass = (int)i;
			break;
		}
	}
	if (iDefClass == -1)
		iDefClass = 0;

	bool bInsRes = false;
	for (size_t i = 0; i < Controls.GetCount() ;i++)
	{
		CString ControlID = Controls[i];
		bInsRes = MessageManager.InsertIDMessageHandler(Controls[i], Classes, Modifications, iDefClass);
	}
	UpdateClasses(&Modifications, &Classes);
	if (pGlobals != NULL && bInsRes)
	{
		CString ParamName = _T("WTLHELPER.")+ ResType + _T(".") + ResID;
		_variant_t vt = Classes[iDefClass]->Name;

		HRESULT hr = pGlobals->put_VariableValue(_bstr_t(ParamName), vt);
		pGlobals->put_VariablePersists(_bstr_t(ParamName), VARIANT_TRUE);
	}

	for (size_t i = 0; i < Classes.GetCount(); i++)
	{
		delete Classes[i];
	}
	Classes.RemoveAll();

	return S_OK;
}

HRESULT CConnect::AddClassToVector(EnvDTE::CodeElementPtr pItem, CSmartAtlArray<VSClass*>& Classes, VSClass* pParentClass /*  = NULL */)
{
	VSClass* pClass = new VSClass;
	pClass->pElement = pItem;
	pClass->pCodeModel = m_pCodeModel;
	pClass->RetriveName(true);
	if (pParentClass)
	{
		pParentClass->NestedClasses.Add(pClass);
	}
	Classes.Add(pClass);
	VCCodeModelLibrary::VCCodeClassPtr pVCClass = pItem;
	if (pVCClass != NULL)
	{
		EnvDTE::CodeElementsPtr pNestedClasses = pVCClass->Classes;
		long NestedCount;
		pNestedClasses->get_Count(&NestedCount);
		for (long j = 1; j <= NestedCount; j++ )
		{
			EnvDTE::CodeElementPtr pNestedClass;
			pNestedClasses->Item(_variant_t(j), &pNestedClass);
			AddClassToVector(pNestedClass, Classes, pClass);
		}
	}
	return S_OK;
}

HRESULT CConnect::AddNamespaceToVector(EnvDTE::CodeElementPtr pItem, CSmartAtlArray<VSClass*>& Classes)
{
	VCCodeModelLibrary::VCCodeNamespacePtr pNamespace = pItem;
	if (pNamespace != NULL)
	{
		EnvDTE::CodeElementsPtr pClasses, pNamespaces;
		pClasses = pNamespace->Classes;
		long Count;
		pClasses->get_Count(&Count);
		for (long i = 1; i <= Count; i++)
		{
			EnvDTE::CodeElementPtr pElem;
			pClasses->Item(_variant_t(i), &pElem);
			AddClassToVector(pElem, Classes);
		}
		pNamespaces = pNamespace->Namespaces;
		pNamespaces->get_Count(&Count);
		for (long i = 1; i <= Count; i++)
		{
			EnvDTE::CodeElementPtr pElem;
			pNamespaces->Item(_variant_t(i), &pElem);
			AddNamespaceToVector(pElem, Classes);
		}
	}
	return S_OK;
}

HRESULT CConnect::GetClasses(EnvDTE::ProjectPtr pProj, CSmartAtlArray<VSClass*>& Classes)
{
	EnvDTE::CodeElementsPtr pElements = NULL;
	EnvDTE::CodeElementPtr pItem;

	if (pProj == NULL)
	{
		return E_FAIL;
	}

	if (FAILED(pProj->get_CodeModel(&m_pCodeModel)))
	{
		return E_FAIL;
	}

#ifdef _FOR_VS2005
	EnvDTE80::CodeModel2Ptr pCodeModel2 = m_pCodeModel;
	pCodeModel2->Synchronize();
#endif

	if (FAILED(m_pCodeModel->get_CodeElements(&pElements)))
	{
		return E_FAIL;
	}

	long Count;
	pElements->get_Count(&Count);
	for (long i = 1; i <= Count; i++)
	{
		_variant_t vt = i;
		if (FAILED(pElements->Item(vt, &pItem)) || (pItem == NULL))
		{
			return E_FAIL;
		}

		EnvDTE::vsCMElement type;
		pItem->get_Kind(&type);
		if (type == EnvDTE::vsCMElementClass)
		{
			AddClassToVector(pItem, Classes);
		}
		if (type == EnvDTE::vsCMElementNamespace)
		{
			AddNamespaceToVector(pItem, Classes);
		}
	}

	return S_OK;
}

HRESULT CConnect::PrepareDlgClass(EnvDTE::ProjectPtr& pProj, CSmartAtlArray<VSClass*>& Classes, int& iDlgClass, CAtlArray<CString>& Controls, CResourceManager* pResManager)
{
	CString DialogID;
	CString RCFileName;
	
	if (GetActiveResourceType(DialogID, RCFileName) != _T("Dialog"))
		return E_FAIL;

	if (!GetActiveControlID(Controls))
		return E_FAIL;

	bool bDialogSelected = IsDialogSelected();
	_AtlModule.LoadAll();

	if (GetActiveProject(pProj) != S_OK)
	{
		return E_FAIL;
	}

	if (GetClasses(pProj, Classes) != S_OK)
	{
		return E_FAIL;
	}
	if (!Classes.GetCount())
	{
		MessageBox(NULL, _T("No classes to work with!"), _T("No classes"), MB_OK | MB_ICONINFORMATION);
		return E_FAIL;
	}

	iDlgClass = FindClassByDlgID(Classes, DialogID);
	if (iDlgClass == -1)
	{
		if (CreateDialogClass(pProj, DialogID) == EnvDTE::wizardResultSuccess)
		{
			for (size_t i = 0; i < Classes.GetCount(); i++)
			{
				delete Classes[i];
			}
			Classes.RemoveAll();
			if (GetClasses(pProj, Classes) != S_OK)
			{
				return E_FAIL;
			}
			iDlgClass = FindClassByDlgID(Classes, DialogID);
		}

		if (iDlgClass == -1)
			return E_FAIL;
	}
	if (bDialogSelected)
	{
		/*bool bRes = ShowWTLHelper(pProj, Classes[iDlgClass]->Name, 0);
		for (size_t i = 0; i < Classes.GetCount(); i++)
		{
			delete Classes[i];
		}
		Classes.RemoveAll();*/
		return S_FALSE;
	}

	SaveResourceDocuments();

	EnvDTE::ProjectItemPtr pRCFile = FindItem(pProj, _bstr_t(RCFileName), EnvDTE::ProjectItemPtr());
	if (pRCFile != NULL && pResManager)
	{
		pResManager->LoadResources(pRCFile);
	}
	return S_OK;
}

#ifdef _FOR_VS2005

HRESULT CConnect::UninstallAddin()
{
	HRESULT hr = S_OK;
	EnvDTE::CommandsPtr pCommands;
	UICommandBarsPtr pCommandBars;
	UICommandBarPtr pHostCmdBar;
		
	m_pDTE->get_Commands(&pCommands);
#ifdef _FOR_VS2005
	m_pDTE->get_CommandBars((IDispatch**)&pCommandBars);
#else
	m_pDTE->get_CommandBars(&pCommandBars);
#endif

	//removing Commands
	EnvDTE::CommandPtr pCmd;
	CString strBase = AddinString();
	for(size_t i =0; i < _countof(WtlHelperCommands); i++)
	{
		CString str = strBase + (LPCTSTR)WtlHelperCommands[i]->Name;
		pCommands->Item(_variant_t(str), 0, &pCmd);
		if (pCmd != NULL)
		{
			HRESULT hr = pCmd->Delete();
		}
	}

	//removing command bars
	for (size_t i = 0; i < _countof(WtlHelperCmdBars); i++)
	{
		pCommandBars->get_Item(_variant_t(WtlHelperCmdBars[i].lpName), &pHostCmdBar);
		if (pHostCmdBar != NULL)
		{
			RemoveCommandBar(pHostCmdBar, pCommands);
		}
	}

	m_pAddInInstance->Remove();
	m_pDTE->Quit();

	return hr;
}


HRESULT CConnect::RemoveCommandBar(UICommandBarPtr pHostCmdBar, EnvDTE::CommandsPtr pCommands)
{
	UICommandBarControlsPtr pControls;
	UICommandBarPtr pHelperCmdBar;
	pHostCmdBar->get_Controls(&pControls);
	if (pControls != NULL)
	{
		UICommandBarControlPtr pControl;
		pControls->get_Item(_variant_t(L"WTL Helper"), &pControl);
		while (pControl != NULL)
		{
			UICommandBarPopupControlPtr pPopup = pControl;
			if (pPopup != NULL)
			{
				pPopup->get_CommandBar(&pHelperCmdBar);
				if(pHelperCmdBar != NULL)
				{
					HRESULT hr = pCommands->RemoveCommandBar(pHelperCmdBar);

					if (hr != S_OK)
					{
						CString str;
						str.Format(_T("Error = %x"), hr);
						MessageBox(NULL, str, NULL, 0);
						break;
					}
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
			pControl = NULL;
			pControls->get_Item(_variant_t(L"WTL Helper"), &pControl);
		}
	}
	return S_OK;
}
#endif
//////////////////////////////////////////////////////////////////////////

void UpdateClasses(CSmartAtlArray<InsDelPoints>* pModifications, ClassVector* pClassVector)
{
	VSFunction* pLastFunction = NULL;
	for (size_t i = 0; i < (*pModifications).GetCount(); i++)
	{
		//сначала удаляем, затем добавляем
		CSmartAtlArray<VSElement*>& CurDelPoint = (*pModifications)[i].DeletePoint;
		CSmartAtlArray<InsertionPoint*>& CurInsPoint = (*pModifications)[i].InsertPoints;
		for (size_t l = 0; l < CurDelPoint.GetCount(); l++)
		{
			(CurDelPoint[l])->Remove();
			delete (CurDelPoint[l]);
		}
		CurDelPoint.RemoveAll();

		int Step = INSERT_STEP_ENVDTE;

		for (size_t j = 0; j < CurInsPoint.GetCount(); j++)
		{
			if ((CurInsPoint[j])->Insert((*pClassVector)[i], Step) == S_OK)
			{
				if ((CurInsPoint[j])->pElement)
				{
					if ((CurInsPoint[j])->pElement->ElementType == EnvDTE::vsCMElementFunction)
					{
						pLastFunction = (VSFunction*)(CurInsPoint[j])->pElement;
					}
				}
				if (CurInsPoint[j]->Type == INSERT_POINT_HANDLER)
				{
					VSFunction* pFunc = ((InsertPointHandler*)(CurInsPoint[j]))->pFunction;
					if (pFunc)
						pLastFunction = pFunc;
				}
			}
		}

		for (int k = INSERT_STEP_GLOBAL; k <= INSERT_STEP_MAP_ENTRY; k++)
		{
			for (size_t j = 0; j < CurInsPoint.GetCount(); j++)
			{
				(CurInsPoint[j])->Insert((*pClassVector)[i], k);
			}
		}

		// удаление объектов
		for (size_t j = 0; j < CurInsPoint.GetCount(); j++)
		{
			delete (CurInsPoint[j]);
		}
		CurInsPoint.RemoveAll();
	}
	if (!g_pSelectedFunction)
	{
		g_pSelectedFunction = pLastFunction;
	}
	if (g_pSelectedFunction)
	{
		EnvDTE::ProjectItemPtr pProjItem;
		VCCodeModelLibrary::VCCodeFunctionPtr pFunc;
		pFunc = g_pSelectedFunction->pElement;
		if(pFunc != NULL)
		{
			pProjItem = pFunc->GetProjectItem();

			EnvDTE::WindowPtr pWindow;
			HRESULT hRes = pProjItem->Open(_bstr_t(EnvDTE::vsViewKindPrimary), &pWindow);
			if (SUCCEEDED(hRes))
			{
				EnvDTE::EditPointPtr pEditPoint;
				if (g_pSelectedFunction->GetStartPoint(&pEditPoint) == S_OK)
				{
					VARIANT_BOOL bShow;
					pEditPoint->TryToShow(EnvDTE::vsPaneShowCentered, _variant_t(0), &bShow);
				}
			}
		}
	}
	pModifications->RemoveAll();
}

EnvDTE::ProjectItemPtr FindItem(EnvDTE::ProjectPtr pProject, _bstr_t ItemName, EnvDTE::ProjectItemPtr pPrevElem)
{
	EnvDTE::ProjectItemsPtr pItems = NULL;
	if (pPrevElem == NULL)
	{
		pProject->get_ProjectItems(&pItems);
	}
	else
	{
		pPrevElem->get_ProjectItems(&pItems);
	}
	if (pItems == NULL)
		return EnvDTE::ProjectItemPtr(NULL);
	long Count;
	pItems->get_Count(&Count);
	if (Count == 0)
		return EnvDTE::ProjectItemPtr(NULL);
	for (long i = 1; i <= Count; i++)
	{
		EnvDTE::ProjectItemPtr pItem;
		pItems->Item(_variant_t(i), &pItem);
		_bstr_t IName;
		pItem->get_Name(IName.GetAddress());

		if (!_wcsicmp(IName, ItemName))
		{
			return pItem;
		}

		EnvDTE::ProjectItemPtr pItem2 = FindItem(pProject, ItemName, pItem);
		if (pItem2 != NULL)
			return pItem2;
	}
	return EnvDTE::ProjectItemPtr(NULL);
}

EnvDTE::CodeElementPtr FindDefine(EnvDTE::ProjectItemPtr pItem, LPCWSTR Name)
{
	EnvDTE::FileCodeModelPtr pFileCodeModel;
	VCCodeModelLibrary::VCFileCodeModelPtr pVCFileCodeModel;
	HRESULT hr;
	hr = pItem->get_FileCodeModel(&pFileCodeModel);
	ATLASSERT(hr == S_OK);
	if (hr != S_OK)
		return EnvDTE::CodeElementPtr();

	pVCFileCodeModel = pFileCodeModel;
	ATLASSERT(pVCFileCodeModel != NULL);

	EnvDTE::CodeElementsPtr pDefines;
	hr = pVCFileCodeModel->get_Macros(&pDefines);
	ATLASSERT(hr == S_OK);
	EnvDTE::CodeElementPtr pDefine;
	if ((pDefines->Item(_variant_t(Name), &pDefine) == S_OK) && (pDefine != NULL))
	{
		return pDefine;
	}
	else
	{
		return EnvDTE::CodeElementPtr();
	}
}

EnvDTE::CodeElementPtr FindDefine(VSClass* pClass, LPCWSTR Name, bool bStdAfx /* = false */)
{
	EnvDTE::ProjectPtr pProject;
	EnvDTE::ProjectItemPtr pProjectItem;
	EnvDTE::CodeElementPtr pDefine;

	pClass->pElement->get_ProjectItem(&pProjectItem);
	pDefine = FindDefine(pProjectItem, Name);
	if (pDefine != NULL)
		return pDefine;
	if (bStdAfx)
	{
		pProjectItem->get_ContainingProject(&pProject);
		EnvDTE::ProjectItemPtr pStdAfxFile = FindItem(pProject, _bstr_t(L"stdafx.h"), EnvDTE::ProjectItemPtr(NULL));
		return FindDefine(pStdAfxFile, Name);
	}
	return pDefine;
}

EnvDTE::CodeElementPtr FindInclude(EnvDTE::ProjectItemPtr pItem, LPCWSTR Name)
{
	EnvDTE::FileCodeModelPtr pFileCodeModel;
	VCCodeModelLibrary::VCFileCodeModelPtr pVCFileCodeModel;
	HRESULT hr;
	hr = pItem->get_FileCodeModel(&pFileCodeModel);
	ATLASSERT(hr == S_OK);
	if (hr != S_OK)
		return EnvDTE::CodeElementPtr();

	pVCFileCodeModel = pFileCodeModel;
	ATLASSERT(pVCFileCodeModel != NULL);

	EnvDTE::CodeElementsPtr pIncludes;
	hr = pVCFileCodeModel->get_Includes(&pIncludes);
	ATLASSERT(hr == S_OK);
	EnvDTE::CodeElementPtr pInclude;
	if ((pIncludes->Item(_variant_t(Name), &pInclude) == S_OK) && (pInclude != NULL))
	{
		return pInclude;
	}
	else
	{
		return EnvDTE::CodeElementPtr();
	}
}

EnvDTE::CodeElementPtr FindInclude(VSClass* pClass, LPCWSTR Name, bool bStdAfx /* = false */)
{
	EnvDTE::ProjectPtr pProject;
	EnvDTE::ProjectItemPtr pProjectItem;
	EnvDTE::CodeElementPtr pInclude;

	pClass->pElement->get_ProjectItem(&pProjectItem);
	pInclude = FindInclude(pProjectItem, Name);
	if (pInclude != NULL)
		return pInclude;
	if (bStdAfx)
	{
		pProjectItem->get_ContainingProject(&pProject);
		EnvDTE::ProjectItemPtr pStdAfxFile = FindItem(pProject, _bstr_t(L"stdafx.h"), EnvDTE::ProjectItemPtr(NULL));
		return FindInclude(pStdAfxFile, Name);
	}
	return pInclude;
}

void RemoveCommands()
{
	CComPtr<EnvDTE::_DTE> pDTE;
	pDTE.CoCreateInstance(L"VisualStudio.DTE.8.0");
	
	if (pDTE == NULL)
		return;

	EnvDTE::CommandsPtr pCommands;
	UICommandBarsPtr pCommandBars;
	UICommandBarPtr pHelperCmdBar, pHostCmdBar;
	EnvDTE::CommandPtr pCmd;

	pDTE->get_Commands(&pCommands);
	

#ifdef _FOR_VS2005
	pDTE->get_CommandBars((IDispatch**)&pCommandBars);
#else
	pDTE->get_CommandBars(&pCommandBars);
#endif

	if (pCommandBars != NULL)
	{
		pCommandBars->get_Item(_variant_t(L"Tools"), &pHostCmdBar);
		if (pHostCmdBar != NULL)
		{
			
			UICommandBarControlsPtr pControls;
			pHostCmdBar->get_Controls(&pControls);
			if (pControls != NULL)
			{
				UICommandBarControlPtr pControl;
				pControls->get_Item(_variant_t(L"WTL Helper"), &pControl);
				if (pControl != NULL)
				{
					UICommandBarPopupControlPtr pPopup = pControl;
					if (pPopup != NULL)
					{
						pPopup->get_CommandBar(&pHelperCmdBar);
						pCommands->RemoveCommandBar(pHelperCmdBar);
					}
				}
			}
		}
		
		/*pCommandBars->get_Item(_variant_t(L"Class View Item.WTL Helper"), &pHelperCmdBar);
		if (pHelperCmdBar != NULL)
		{
			pCommands->RemoveCommandBar(pHelperCmdBar);
		}

		pCommandBars->get_Item(_variant_t(L"Resource Editors.WTL Helper"), &pHelperCmdBar);
		if (pHelperCmdBar != NULL)
		{
			pCommands->RemoveCommandBar(pHelperCmdBar);
		}

		pCommandBars->get_Item(_variant_t(L"Menu Designer.WTL Helper"), &pHelperCmdBar);
		if (pHelperCmdBar != NULL)
		{
			pCommands->RemoveCommandBar(pHelperCmdBar);
		}

		pCommandBars->get_Item(_variant_t(L"Resource View.WTL Helper"), &pHelperCmdBar);
		if (pHelperCmdBar != NULL)
		{
			pCommands->RemoveCommandBar(pHelperCmdBar);
		}*/

		/*if (pCommandBars->get_Item(_variant_t(L"Class View Item"), &pClassViewBar) == S_OK)
		{
			pCommands->AddCommandBar(_bstr_t(L"WTL Helper"), EnvDTE::vsCommandBarTypeMenu, pClassViewBar, 10, (IDispatch**)&m_pClassViewAddinBar);
		}
		if (pCommandBars->get_Item(_variant_t(L"Resource Editors"), &pResourceBar) == S_OK)
		{
			pCommands->AddCommandBar(_bstr_t(L"WTL Helper"), EnvDTE::vsCommandBarTypeMenu, pResourceBar, 1, (IDispatch**)&m_pResViewAddinBar);
		}
		if (pCommandBars->get_Item(_variant_t(L"Menu Designer"), &pMenuDesigner) == S_OK)
		{
			pCommands->AddCommandBar(_bstr_t(L"WTL Helper"), EnvDTE::vsCommandBarTypeMenu, pMenuDesigner, 1, (IDispatch**)&m_pMenuDesignerBar);
		}
		if (pCommandBars->get_Item(_variant_t(L"Resource View"), &pResView) == S_OK)
		{
			pCommands->AddCommandBar(_bstr_t(L"WTL Helper"), EnvDTE::vsCommandBarTypeMenu, pResView, 1, (IDispatch**)&m_pResViewContextBar);
		}*/
	}

	CString strBase = AddinString();
	for(size_t i =0; i < sizeof(WtlHelperCommands)/sizeof(const CommandStruct*); i++)
	{
		CString str = strBase + (LPCTSTR)WtlHelperCommands[i]->Name;
		pCommands->Item(_variant_t(str), -1, &pCmd);
		if (pCmd != NULL)
		{
			pCmd->Delete();
		}
	}

	pDTE->Quit();
}