// Connect.h : Declaration of the CConnect

#pragma once
#include "resource.h"       // main symbols

using namespace AddInDesignerObjects;
using namespace Microsoft_VisualStudio_CommandBars;

/// <summary>The object for implementing an Add-in.</summary>
/// <seealso class='IDTExtensibility2' />
class ATL_NO_VTABLE CConnect : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CConnect, &CLSID_Connect>,
	public IDispatchImpl<EnvDTE::IDTCommandTarget, &EnvDTE::IID_IDTCommandTarget, &EnvDTE::LIBID_EnvDTE, 7, 0>,
	public IDispatchImpl<_IDTExtensibility2, &IID__IDTExtensibility2, &LIBID_AddInDesignerObjects, 1, 0>
{
public:
	/// <summary>Implements the constructor for the Add-in object. Place your initialization code within this method.</summary>
	CConnect()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_ADDIN)
	DECLARE_NOT_AGGREGATABLE(CConnect)

	BEGIN_COM_MAP(CConnect)
		COM_INTERFACE_ENTRY(IDTExtensibility2)
		COM_INTERFACE_ENTRY(IDTCommandTarget)
		COM_INTERFACE_ENTRY2(IDispatch, IDTExtensibility2)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:
//IDTExtensibility2 implementation:

	/// <summary>Implements the OnConnection method of the IDTExtensibility2 interface. Receives notification that the Add-in is being loaded.</summary>
	/// <param term='application'>Root object of the host application.</param>
	/// <param term='connectMode'>Describes how the Add-in is being loaded.</param>
	/// <param term='addInInst'>Object representing this Add-in.</param>
	/// <seealso class='IDTExtensibility2' />
	STDMETHOD(OnConnection)(IDispatch * Application, ext_ConnectMode ConnectMode, IDispatch *AddInInst, SAFEARRAY **custom);

	/// <summary>Implements the OnDisconnection method of the IDTExtensibility2 interface. Receives notification that the Add-in is being unloaded.</summary>
	/// <param term='disconnectMode'>Describes how the Add-in is being unloaded.</param>
	/// <param term='custom'>Array of parameters that are host application specific.</param>
	/// <seealso class='IDTExtensibility2' />
	STDMETHOD(OnDisconnection)(ext_DisconnectMode RemoveMode, SAFEARRAY **custom );

	/// <summary>Implements the OnAddInsUpdate method of the IDTExtensibility2 interface. Receives notification when the collection of Add-ins has changed.</summary>
	/// <param term='custom'>Array of parameters that are host application specific.</param>
	/// <seealso class='IDTExtensibility2' />	
	STDMETHOD(OnAddInsUpdate)(SAFEARRAY **custom );

	/// <summary>Implements the OnStartupComplete method of the IDTExtensibility2 interface. Receives notification that the host application has completed loading.</summary>
	/// <param term='custom'>Array of parameters that are host application specific.</param>
	/// <seealso class='IDTExtensibility2' />
	STDMETHOD(OnStartupComplete)(SAFEARRAY **custom );

	/// <summary>Implements the OnBeginShutdown method of the IDTExtensibility2 interface. Receives notification that the host application is being unloaded.</summary>
	/// <param term='custom'>Array of parameters that are host application specific.</param>
	/// <seealso class='IDTExtensibility2' />
	STDMETHOD(OnBeginShutdown)(SAFEARRAY **custom );
	
//IDTCommandTarget implementation:

	/// <summary>Implements the QueryStatus method of the IDTCommandTarget interface. This is called when the command's availability is updated</summary>
	/// <param term='commandName'>The name of the command to determine state for.</param>
	/// <param term='neededText'>Text that is needed for the command.</param>
	/// <param term='status'>The state of the command in the user interface.</param>
	/// <param term='commandText'>Text requested by the neededText parameter.</param>
	/// <seealso class='Exec' />
	STDMETHOD(QueryStatus)(BSTR CmdName, EnvDTE::vsCommandStatusTextWanted NeededText, EnvDTE::vsCommandStatus *StatusOption, VARIANT *CommandText);

	/// <summary>Implements the Exec method of the IDTCommandTarget interface. This is called when the command is invoked.</summary>
	/// <param term='commandName'>The name of the command to execute.</param>
	/// <param term='executeOption'>Describes how the command should be run.</param>
	/// <param term='varIn'>Parameters passed from the caller to the command handler.</param>
	/// <param term='varOut'>Parameters passed from the command handler to the caller.</param>
	/// <param term='handled'>Informs the caller if the command was handled or not.</param>
	/// <seealso class='Exec' />
	STDMETHOD(Exec)(BSTR CmdName, EnvDTE::vsCommandExecOption ExecuteOption, VARIANT *VariantIn, VARIANT *VariantOut, VARIANT_BOOL *Handled);

private:
	CComPtr<EnvDTE80::DTE2> m_pDTE;
	CComPtr<EnvDTE::AddIn> m_pAddInInstance;
};

OBJECT_ENTRY_AUTO(__uuidof(Connect), CConnect)
