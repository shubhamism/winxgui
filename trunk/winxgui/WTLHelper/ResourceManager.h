#pragma once

#include "resources/Resources.h"

enum eControlType
{
	eCTCommand,
	eCTNotify,
	eCTScrollbar
};

class CResourceManager
{
	CResources m_Resources;

	void AddResourceFiles(EnvDTE::ProjectItemPtr pParentItem, CAtlArray<CString>& Files);
	void GetResourceFiles(EnvDTE::ProjectPtr pProj, CAtlArray<CString>& Files);
	static void LoadMenuItemIds(CResMenu& Menu, CAtlArray<CString>& ResIds);
public:
	CResourceManager(void);
	~CResourceManager(void);

	bool LoadResources(EnvDTE::ProjectPtr pProj);
	bool LoadResources(EnvDTE::ProjectItemPtr pProjItem);

	const CResources* GetResources();
	const CResDialog* GetDialog(const CString lpDlgID) const;
	const ResControl* GetDlgControl(const CString DlgId, const CString ControlId) const;
	const ResControl* GetDlgControl(const CResDialog* pDlg, const CString ControlId) const;

	static eControlType GetControlType(const CString Type);
	
	bool GetMenuIds(CAtlArray<CString>& StringIds, bool bAppend = true);
	bool GetMenuIds(const CString ResID, CAtlArray<CString>& StringIds);
	bool GetToolbarIds(CAtlArray<CString>& StringIds, bool bAppend = true);
	bool GetToolbarIds(const CString ResID, CAtlArray<CString>& StringIds);
	bool GetAcceleratorIds(CAtlArray<CString>& StringIds, bool bAppend = true);
	bool GetAcceleratorIds(const CString ResID, CAtlArray<CString>& StringIds);

	// get controls IDs from the dialog which send WM_COMMAND notification message
	bool GetCommandControls(const CString DialogID, CAtlArray<CString>& StringIds) const;
	// get controls IDs from the dialog which of type in the list of possible types
	bool GetTypedControls(const CString DialogID, const CAtlArray<CString>* pPosibleTypes, CAtlArray<CString>& StringIds) const;

	// get controls IDs from the dialog which send WM_NOTIFY notification message
	bool GetNotifyControls(const CString DialogID, CAtlArray<CString>& StringIds) const;

	bool GetAllControls(const CString DialogID, CAtlArray<ResControl>& Controls) const;
};
