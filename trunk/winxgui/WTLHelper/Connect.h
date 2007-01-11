////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	Connect.h
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

// Connect.h : Declaration of the CConnect

#pragma once
#include "resource.h"       // main symbols
#include "VSElements.h"
#include "common.h"
#include <atlcoll.h>
#include "ResourceManager.h"

#ifdef _FOR_VS2005
typedef Microsoft_VisualStudio_CommandBars::CommandBarPtr UICommandBarPtr;
typedef Microsoft_VisualStudio_CommandBars::CommandBarControlPtr UICommandBarControlPtr;
typedef Microsoft_VisualStudio_CommandBars::_CommandBarsPtr UICommandBarsPtr;
typedef Microsoft_VisualStudio_CommandBars::CommandBarPopupPtr UICommandBarPopupControlPtr;
typedef Microsoft_VisualStudio_CommandBars::CommandBarControlsPtr UICommandBarControlsPtr;
#else
typedef Office::CommandBarPtr UICommandBarPtr;
typedef Office::CommandBarControlPtr UICommandBarControlPtr;
typedef Office::_CommandBarsPtr UICommandBarsPtr;
typedef Office::CommandBarPopupPtr UICommandBarPopupControlPtr;
typedef Office::CommandBarControlsPtr UICommandBarControlsPtr;
#endif

enum eWizardsErrors
{
	eSuccess = 0,
	eWizardsNotInstalled = 1,
	eWTLDLGNotInstalled = 2,
	eWrongVersion = 3,
	eError = -1
};


#define CMDBAR_TOOLS		0
#define CMDBAR_CLASSVIEW	1
#define CMDBAR_RESEDITORS	2
#define CMDBAR_MENUEDITORS	3
#define CMDBAR_RESVIEW		4
#define CMDBAR_NO			-1


struct WtlHelperCmdBar
{
	LPCWSTR lpName;
	int nPos;
	EnvDTE::vsCommandBarType CmdType;
	UICommandBarPtr  pCmdBar;
};

struct CommandStruct
{
	_bstr_t Name;
	_bstr_t ButtonText;
	_bstr_t ToolTip;
	_variant_t Bindings;
	VARIANT_BOOL bMSOButton;
	long lBitmapId;
	int iCmdBar;
	long lPos;
	CommandStruct(LPCWSTR lpName, LPCWSTR lpBText, LPCWSTR lpToolTip, LPCWSTR lpBindings, 
		int cmdBar = CMDBAR_NO, long Pos = -1, bool bMSO = true, long lBitmap = 59)
		: Name(lpName), ButtonText(lpBText), ToolTip(lpToolTip), Bindings(lpBindings), 
		iCmdBar(cmdBar), lPos(Pos),
		bMSOButton(bMSO ? VARIANT_TRUE : VARIANT_FALSE), lBitmapId(lBitmap)
	{
	}
};

// CConnect
class ATL_NO_VTABLE CConnect : 
	public CComObjectRootEx<CComSingleThreadModel>,
#ifdef _FOR_VS2005
	public CComCoClass<CConnect, &CLSID_Connect8>,
#else
	public CComCoClass<CConnect, &CLSID_Connect>,
#endif
	public IDispatchImpl<EnvDTE::IDTCommandTarget, &EnvDTE::IID_IDTCommandTarget, &EnvDTE::LIBID_EnvDTE, 7, 0>,
	public IDispatchImpl<AddInDesignerObjects::_IDTExtensibility2, &AddInDesignerObjects::IID__IDTExtensibility2, &AddInDesignerObjects::LIBID_AddInDesignerObjects, 1, 0>
{
private:
	UICommandBarPtr m_pAddinCommandBar;
	UICommandBarPtr m_pClassViewAddinBar;
	UICommandBarPtr m_pResViewAddinBar;
	UICommandBarPtr m_pMenuDesignerBar;
	UICommandBarPtr m_pResViewContextBar;
public:
	CConnect()
	{
	}
#ifdef _FOR_VS2005
	DECLARE_REGISTRY_RESOURCEID(IDR_ADDIN8)
#else
	DECLARE_REGISTRY_RESOURCEID(IDR_ADDIN)
#endif
	DECLARE_NOT_AGGREGATABLE(CConnect)

	BEGIN_COM_MAP(CConnect)
		COM_INTERFACE_ENTRY(AddInDesignerObjects::IDTExtensibility2)
		COM_INTERFACE_ENTRY(EnvDTE::IDTCommandTarget)
		COM_INTERFACE_ENTRY2(IDispatch, AddInDesignerObjects::IDTExtensibility2)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}
	HRESULT GetActiveProject(EnvDTE::ProjectPtr& pProj);
	HRESULT GetSelectedProject(EnvDTE::ProjectPtr& pProj);
	HRESULT GetClasses(EnvDTE::ProjectPtr pProj, CSmartAtlArray<VSClass*>& Classes);
	HRESULT AddClassToVector(EnvDTE::CodeElementPtr pItem, CSmartAtlArray<VSClass*>& Classes, VSClass* pParent = NULL);
	HRESULT AddNamespaceToVector(EnvDTE::CodeElementPtr pItem, CSmartAtlArray<VSClass*>& Classes);
	CString  GetActiveClass(EnvDTE::TextPointPtr& pCurPoint);
	int GetActiveClass(CSmartAtlArray<VSClass*>& Classes, CString ClassName);
	void GetBases(EnvDTE::CodeElementPtr pElem, CAtlArray<CString>& Bases);
	void GetAllBases(VSClass* pClass, CAtlArray<CString>& Bases);
	bool ShowWTLHelper(EnvDTE::ProjectPtr pProj, CString ActiveClass, int ActivePage);
	EnvDTE::CodeClassPtr GetSelectedClass(EnvDTE::ProjectPtr& pProj);
	// return resource type of current resource window or empty for no resource windows
	CString GetActiveResourceType(CString& ResourceID, CString& FileName);
	bool IsPossibleResourceType(CString ResourceType);
	bool IsDialogSelected();
	bool IsMultipleSelected();
	bool GetActiveControlID(CAtlArray<CString>& ActiveControls);
	int FindClassByDlgID(ClassVector Classes, CString DialogID);
	void SaveResourceDocuments();
	HRESULT AddDialogHandler(CString RCFile, CString DialogID);
	HRESULT AddIDHandler(CString RCFile, CString ResID, CString ResType);
	EnvDTE::CodeElementPtr GetClassFromMember(EnvDTE::CodeElementPtr pMember);
	EnvDTE::wizardResult CreateDialogClass(EnvDTE::ProjectPtr pProj, CString DialogID, bool bShow = false);
	eWizardsErrors GetWTLDLGWizardPath(CString& Path, LPCTSTR lpMinVersion);
	// return S_FALSE if showed main WTL Helper dialog, S_OK if it is need to continue or E_FAIL if any error
	HRESULT PrepareDlgClass(EnvDTE::ProjectPtr& pProj, CSmartAtlArray<VSClass*>& Classes, int& iDlgClass, CAtlArray<CString>& Controls, CResourceManager* pResManager);
public:
	//IDTExtensibility2 implementation:
	STDMETHOD(OnConnection)(IDispatch * Application, AddInDesignerObjects::ext_ConnectMode ConnectMode, IDispatch *AddInInst, SAFEARRAY **custom);
	STDMETHOD(OnDisconnection)(AddInDesignerObjects::ext_DisconnectMode RemoveMode, SAFEARRAY **custom );
	STDMETHOD(OnAddInsUpdate)(SAFEARRAY **custom );
	STDMETHOD(OnStartupComplete)(SAFEARRAY **custom );
	STDMETHOD(OnBeginShutdown)(SAFEARRAY **custom );
	
	//IDTCommandTarget implementation:
	STDMETHOD(QueryStatus)(BSTR CmdName, EnvDTE::vsCommandStatusTextWanted NeededText, EnvDTE::vsCommandStatus *StatusOption, VARIANT *CommandText);
	STDMETHOD(Exec)(BSTR CmdName, EnvDTE::vsCommandExecOption ExecuteOption, VARIANT *VariantIn, VARIANT *VariantOut, VARIANT_BOOL *Handled);
	STDMETHOD(DoAddin)();
	STDMETHOD(DoAddFunction)();
	STDMETHOD(DoAddVariable)();
	STDMETHOD(DoOptions)();
	STDMETHOD(DoClassViewHandler)();
	STDMETHOD(DoClassViewVariable)();
	STDMETHOD(DoResViewDDX)();
	STDMETHOD(DoResViewHandler)();
	STDMETHOD(DoResViewReflect)();
	STDMETHOD(DoResViewDialog)();
	STDMETHOD(DoResViewContextDDX)();
	STDMETHOD(DoResViewContextHandler)();
	STDMETHOD(DoResViewContextDialog)();
	STDMETHOD(CreateCommand)(EnvDTE::Commands* pCommands, const CommandStruct* pCmd);
#ifdef _FOR_VS2005
	STDMETHOD(UninstallAddin)();
	STDMETHOD(RemoveCommandBar)(UICommandBarPtr pHostCmdBar, EnvDTE::CommandsPtr pCommands);
#endif

	CComPtr<EnvDTE::_DTE> m_pDTE;
	CComPtr<EnvDTE::AddIn> m_pAddInInstance;
	EnvDTE::CodeModel* m_pCodeModel;
private:
	
};

#ifdef _FOR_VS2005
OBJECT_ENTRY_AUTO(__uuidof(Connect8), CConnect)
#else
OBJECT_ENTRY_AUTO(__uuidof(Connect), CConnect)
#endif

