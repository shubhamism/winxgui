#ifndef _ATL_TABCTRLEX_H_
#define _ATL_TABCTRLEX_H_

class CTabCtrlEx : public CWindowImpl<CTabCtrlEx,CTabCtrl>
{
protected:
	int		m_nCurSel;
	int		m_top;
public:
	CTabCtrlEx() : m_nCurSel(-1), m_top(70)
	{
	}
	DECLARE_WND_SUPERCLASS(NULL, CTabCtrl::GetWndClassName())

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		pMsg;
		return FALSE;
	}

public:
	int InsertItemEx(int nItem, LPCTSTR lpszItem, HWND hWnd, int iImage = 0)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		TCITEM tci = { 0 };
		tci.mask = TCIF_TEXT | TCIF_IMAGE;
		tci.pszText = (LPTSTR) lpszItem;
		tci.iImage = iImage;
		int nRet = (int)::SendMessage(m_hWnd, TCM_INSERTITEM, nItem, (LPARAM)&tci);
		if (nRet != -1)
		{
			SetItemClient(nItem,hWnd);
		}
		return nRet;
	}
	BOOL SetItemClient(int nItem, HWND hWnd)
	{	
		TCITEM tci = {0};
		tci.mask = TCIF_PARAM;
		tci.lParam = (DWORD)hWnd;
		::SendMessage(m_hWnd,TCM_SETITEM,nItem,(LPARAM)&tci);

		RECT rc;
		GetClientRect(&rc);
		AdjustRect(FALSE,&rc);
		rc.left -= 2;
		rc.top  += m_top;

		::SetParent(hWnd,m_hWnd);
		::MoveWindow(hWnd,rc.left,rc.top,rc.right-rc.left,rc.bottom-rc.top,TRUE);

		return TRUE;
	}
	HWND GetItemClient(int nItem)
	{
		TCITEM tci = {0};
		tci.mask = TCIF_PARAM;
		::SendMessage(m_hWnd,TCM_GETITEM,nItem,(LPARAM)&tci);
		return (HWND)tci.lParam;
	}
	BOOL SetActiveItem(int nItem)
	{
		if (m_nCurSel != nItem)
		{
			HWND hOldWnd = GetItemClient(m_nCurSel);
			::ShowWindow(hOldWnd,SW_HIDE);
			m_nCurSel = nItem;
		}
		SetCurSel(nItem);
		HWND hWnd = GetItemClient(nItem);
		::ShowWindow(hWnd,SW_SHOW);
		return hWnd != NULL;
	}

public:
	BEGIN_MSG_MAP(CTabCtrlEx)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		REFLECTED_NOTIFY_CODE_HANDLER(TCN_SELCHANGE, OnSelchangeTab)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	LRESULT OnSelchangeTab(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
		// TODO : Add Code for control notification handler.
		int nItem = GetCurSel();
		SetActiveItem(nItem);
		return 0;
	}
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		for (int i = 0; i < GetItemCount(); i++)
		{
			HWND hWnd = GetItemClient(i);
			RECT rc;
			GetClientRect(&rc);
			AdjustRect(FALSE,&rc);
			rc.left -= 2;
			rc.top  += m_top;

			::MoveWindow(hWnd,rc.left,rc.top,rc.right-rc.left,rc.bottom-rc.top,TRUE);
		}
		return 0;
	}
};

#endif //