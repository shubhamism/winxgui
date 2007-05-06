#ifndef _FOX_UI_ITEM_DIALOG_H_
#define _FOX_UI_ITEM_DIALOG_H_

#pragma once


#define COMMAND_ID_VOID(id, func) \
	if(uMsg == WM_COMMAND && id == LOWORD(wParam)) \
	{ \
		bHandled = TRUE; \
		lResult = 0;\
		func(); \
		if(bHandled) \
			return TRUE; \
	}

template <typename T, WORD t_IDD, bool t_bUseMinTrackSize = false>
class ui_view_dialog_t : public CDialogImpl<T>, public CDialogResize<T>, 
						 public fox::ui::view
{
public:
	enum { IDD = t_IDD };
public:
	virtual HWND create(HWND hParent, RECT rc = CWindow::rcDefault)
	{
		return Create(hParent);
	}
	virtual HWND handle()
	{
		return m_hWnd;
	}
public:
	ui_view_dialog_t()
	{
	}
	typedef ui_view_dialog_t<T,t_IDD, t_bUseMinTrackSize> ui_view_dialog_base;

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		return CWindow::IsDialogMessage(pMsg);
	}

	BEGIN_MSG_MAP(ui_view_dialog_base)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		CHAIN_MSG_MAP(CDialogResize<T>)
	END_MSG_MAP()

	BEGIN_DLGRESIZE_MAP(ui_view_dialog_base)
	END_DLGRESIZE_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		DlgResize_Init(false,t_bUseMinTrackSize);
		T * pT = static_cast<T*>(this);
	//	ModifyStyle(0,WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
	//	ModifyStyleEx(0,WS_EX_CLIENTEDGE);//|WS_EX_DLGMODALFRAME);
		pT->OnInit();
		return 0;
	}
	void OnInit()
	{
	}
};

template <typename T, WORD t_IDD, bool t_bUseMinTrackSize = true, typename fox_base = fox::ui::item>
class ui_item_dialog_t : public CDialogImpl<T>, public CDialogResize<T>, 
						 public fox_base
{
public:
	enum {IDD = t_IDD};
public:
	virtual HWND create(HWND hParent, RECT rc = CWindow::rcDefault)
	{
		return Create(hParent);
	}
	virtual HWND handle()
	{
		return m_hWnd;
	}
public:
	ui_item_dialog_t()
	{
	}
	typedef ui_item_dialog_t<T,t_IDD,t_bUseMinTrackSize,fox_base> ui_item_dialog_base;

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return CWindow::IsDialogMessage(pMsg);
	}

	BEGIN_MSG_MAP(ui_item_dialog_base)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	//	COMMAND_ID_CALL(IDC_CLOSE_BTN, ShowWindow(SW_HIDE);)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		CHAIN_MSG_MAP(CDialogResize<T>)
	END_MSG_MAP()

	BEGIN_DLGRESIZE_MAP(ui_item_dialog_base)
	END_DLGRESIZE_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		DlgResize_Init(false,t_bUseMinTrackSize);
		T * pT = static_cast<T*>(this);
	//	ModifyStyle(0,WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
	//	ModifyStyleEx(0,WS_EX_CLIENTEDGE);//|WS_EX_DLGMODALFRAME);
		pT->OnInit();
		return 0;
	}
	void OnInit()
	{
	}

	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		ShowWindow(SW_HIDE);
		return 0;
	}
};

template <typename T, WORD t_IDD, bool t_bUseMinTrackSize = false>
class ui_page_dialog_t : public CDialogImpl<T>, public CDialogResize<T>
{
public:
	enum {IDD = t_IDD};
public:
	BOOL CreateFromID(HWND hParent, UINT nID)
	{
		RECT rc;
		CWindow wnd = ::GetDlgItem(hParent, nID);
		wnd.ShowWindow(SW_HIDE);
		wnd.GetWindowRect(&rc);
		wnd.DestroyWindow();

		CWindow(hParent).ScreenToClient(&rc);
		if (!Create(hParent))
			return FALSE;

		SetDlgCtrlID(nID);
		MoveWindow(&rc);
		return TRUE;
	}
public:
	ui_page_dialog_t()
	{
	}
	typedef ui_page_dialog_t<T,t_IDD, t_bUseMinTrackSize> ui_page_dialog_base;

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		return CWindow::IsDialogMessage(pMsg);
	}

	BEGIN_MSG_MAP(ui_page_dialog_base)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	//	COMMAND_ID_CALL(IDC_CLOSE_BTN, ShowWindow(SW_HIDE);)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		CHAIN_MSG_MAP(CDialogResize<T>)
	END_MSG_MAP()

	BEGIN_DLGRESIZE_MAP(ui_page_dialog_base)
	END_DLGRESIZE_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		DlgResize_Init(false,t_bUseMinTrackSize);
		T * pT = static_cast<T*>(this);
	//	ModifyStyle(0,WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
	//	ModifyStyleEx(0,WS_EX_CLIENTEDGE);//|WS_EX_DLGMODALFRAME);
		pT->OnInit();
		return 0;
	}
	void OnInit()
	{
	}

	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		ShowWindow(SW_HIDE);
		return 0;
	}
};

template <typename T, WORD t_IDD, bool t_bUseMinTrackSize = true>
class ui_simple_dialog_t : public CDialogImpl<T>, public CDialogResize<T>
{
public:
	enum {IDD = t_IDD};
public:
	ui_simple_dialog_t()
	{
	}
	typedef ui_simple_dialog_t<T,t_IDD, t_bUseMinTrackSize> ui_simple_dialog_base;

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return CWindow::IsDialogMessage(pMsg);
	}
public:
	BEGIN_MSG_MAP(ui_simple_dialog_base)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		CHAIN_MSG_MAP(CDialogResize<T>)
	END_MSG_MAP()

	BEGIN_DLGRESIZE_MAP(ui_simple_dialog_base)
	END_DLGRESIZE_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		DlgResize_Init(false,t_bUseMinTrackSize);
		T * pT = static_cast<T*>(this);
		CenterWindow(GetParent());
		pT->OnInit();
		return 0;
	}

	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		T * pT = static_cast<T*>(this);
	
		if (wID == IDOK)
		{
			if (pT->OnClose() == FALSE)
				return 0;
		}
		else
			pT->OnCancel();

		EndDialog(wID);
		return 0;
	}
	void OnInit()
	{
	}
	BOOL OnClose()
	{
		return TRUE;
	}
	void OnCancel()
	{
	}
};






#endif