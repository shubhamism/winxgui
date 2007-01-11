#pragma	  once

#include <atlctrls.h>

template <typename TBase, typename TToolTipClass = CToolTipCtrl>
class CToolTipMapImpl
{
	UINT m_uiInitFlags;
public:
	CToolTipMapImpl() : m_uiInitFlags(TTF_SUBCLASS){}
	
	TToolTipClass m_ToolTip;
	
	UINT GetInitFlags()
	{
		return m_uiInitFlags;
	}
	void SetInitFlags(UINT uiInitFlags)
	{
		m_uiInitFlags = uiInitFlags;
	}

	void OnInitToolTip()
	{
		m_ToolTip.Activate(TRUE);
	}

	void InitToolTip()
	{
		TBase* pThis = static_cast<TBase*>(this);
		ATLVERIFY(m_ToolTip.Create(pThis->m_hWnd));
		pThis->OnInitToolTip();
		pThis->ProcessToolTipMap();
	}

	void ProcessToolTipMap(bool bCreate = true)
	{
	}
	
	void UpdateAllTooltips()
	{
		TBase* pThis = static_cast<TBase*>(this);
		pThis->ProcessToolTipMap(false);
	}

	void AddToolTip(UINT ControlID, UINT TextID)
	{
		TBase* pThis = static_cast<TBase*>(this);
		AddToolTip(pThis->GetDlgItem(ControlID), MAKEINTRESOURCE(TextID));
	}

	void AddToolTip(UINT ControlID, LPCTSTR lpTextPtr)
	{
		TBase* pThis = static_cast<TBase*>(this);
		AddToolTip(pThis->GetDlgItem(ControlID), lpTextPtr);
	}

	void AddToolTip(HWND hWnd, UINT TextID)
	{
		AddToolTip(hWnd, MAKEINTRESOURCE(TextID));
	}

	void AddToolTip(HWND hWnd, LPCTSTR lpTextPtr)
	{
		CToolInfo ToolInfo(m_uiInitFlags, hWnd, 0, NULL, (LPTSTR)lpTextPtr);
		m_ToolTip.AddTool(&ToolInfo);
	}

	void AddToolTip(HWND hWnd, UINT ToolID, LPRECT lpRect, UINT TextID)
	{
		AddToolTip(hWnd, ToolID, lpRect, MAKEINTRESOURCE(TextID));
	}

	void AddToolTip(HWND hWnd, UINT ToolID, LPRECT lpRect, LPCTSTR lpTextPtr)
	{
		CToolInfo ToolInfo(m_uiInitFlags, hWnd, ToolID, lpRect, (LPTSTR)lpTextPtr);
		m_ToolTip.AddTool(&ToolInfo);
	}

	void UpdateToolTip(UINT ControlID, UINT TextID)
	{
		TBase* pThis = static_cast<TBase*>(this);
		UpdateToolTip(pThis->GetDlgItem(ControlID), MAKEINTRESOURCE(TextID));
	}

	void UpdateToolTip(UINT ControlID, LPCTSTR lpTextPtr)
	{
		TBase* pThis = static_cast<TBase*>(this);
		UpdateToolTip(pThis->GetDlgItem(ControlID), lpTextPtr);
	}

	void UpdateToolTip(HWND hWnd, UINT TextID)
	{
		UpdateToolTip(hWnd, MAKEINTRESOURCE(TextID));
	}

	void UpdateToolTip(HWND hWnd, LPCTSTR lpNewText)
	{
		CToolInfo ToolInfo(0, hWnd, 0, NULL, NULL);
		if (!m_ToolTip.GetToolInfo(&ToolInfo))
		{
			ATLTRACE(_T("Cannot find tool specified. Add new!"));
			AddToolTip(hWnd, lpNewText);
		}
		else
		{
			ToolInfo.lpszText = (LPTSTR)lpNewText;
			m_ToolTip.SetToolInfo(&ToolInfo);
		}
	}

	void UpdateToolTip(HWND hWnd, UINT ToolID, LPRECT lpRect, UINT TextID)
	{
		UpdateToolTip(hWnd, ToolID, lpRect, MAKEINTRESOURCE(TextID));
	}

	void UpdateToolTip(HWND hWnd, UINT ToolID, LPRECT lpRect, LPCTSTR lpNewText)
	{
		CToolInfo ToolInfo(0, hWnd, ToolID, NULL, NULL);
		if (!m_ToolTip.GetToolInfo(&ToolInfo))
		{
			ATLTRACE(_T("Cannot find tool specified. Add new!"));
			AddToolTip(hWnd, ToolID, lpRect, lpNewText);
		}
		else
		{
			ToolInfo.lpszText = (LPTSTR)lpNewText;
			ToolInfo.rect = * lpRect;
			m_ToolTip.SetToolInfo(&ToolInfo);
		}
	}
};

#define BEGIN_TOOLTIP_MAP(thisClass)\
	void ProcessToolTipMap(bool bCreate = true)\
	{

#define TIP_CHILDWND(childWnd, text)\
	if (bCreate)\
	{\
		AddToolTip(childWnd, text);\
	}\
	else\
	{\
		UpdateToolTip(childWnd, text);\
	}

#define TIP_RECT(ToolID, lpRect, lpTextPtr)\
	if (bCreate)\
	{\
		AddToolTip(m_hWnd, ToolID, lpRect, lpTextPtr);\
	}\
	else\
	{\
		UpdateToolTip(m_hWnd, ToolID, lpRect, lpTextPtr);\
	}

#define END_TOOLTIP_MAP() }
