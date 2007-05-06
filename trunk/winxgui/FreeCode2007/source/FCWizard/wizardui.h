#ifndef _WIZARDUI_H__
#define _WIZARDUI_H__


#include <atlapp.h>
#include <atlwin.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atlsplit.h>
#include <atlmisc.h>

#include <map>

#include "../public/atltabex.h"
#include "../public/foxlib.h"
#include "../public/foxuilib.h"

#include "./codeparser.h"
#include "./resource.h"

class page_winx_event : public ui_page_dialog_t<page_winx_event, IDD_PAGE_WINX_EVENT>
{
public:
	codeparser * pcode;
	Token	   * m_tkcls;
	CListBox     m_tokenList;
	CListBox	 m_eventList;
public:
	BEGIN_DLGRESIZE_MAP(page_winx_event)
		DLGRESIZE_CONTROL(IDC_EVENT_LIST, DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_EVENT_TOKEN_LIST, DLSZ_SIZE_Y | DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_ADDEVENT_BTN, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_DELEVENT_BTN, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_EDITEVENT_BTN, DLSZ_MOVE_X)
	END_DLGRESIZE_MAP()
public:
	void OnInit()
	{
		m_eventList = GetDlgItem(IDC_EVENT_LIST);
		m_tokenList = GetDlgItem(IDC_EVENT_TOKEN_LIST);
	}
	void OnClassChange(Token * tkcls)
	{
		m_tkcls = tkcls;
		m_eventList.ResetContent();
		m_tokenList.ResetContent();
		if (tkcls)
		{
			pcode->EnumWinxEventList(QLib::Event<void,winx_event*>(this,&page_winx_event::AddWinxEventList));
			pcode->EnumWinxEventToken(tkcls,QLib::Event<void,Token*>(this,&page_winx_event::AddWinxEventToken));
		}
	}
protected:
	//Ìí¼Óevent list
	void AddWinxEventList(winx_event * ev)
	{
		int index = m_eventList.AddString(ev->name);
		m_eventList.SetItemData(index,(DWORD)ev);
	}
	//´¦Àíevnet token 
	int AddWinxEventToken(Token * tk)
	{
		if (tk->m_TokenUpdate == tuRemove) {
			return -1;
		}
		int index = m_tokenList.AddString(tk->m_Name);
		m_tokenList.SetItemData(index,(DWORD)tk);
		return index;
	}
public:
	BEGIN_MSG_MAP(member_page)
		COMMAND_ID_HANDLER(IDC_EDITEVENT_BTN, OnEditEventBtn)
		COMMAND_ID_HANDLER(IDC_ADDEVENT_BTN, OnAddEventBtn)
		COMMAND_ID_HANDLER(IDC_DELEVENT_BTN, OnDelEventBtn)
		COMMAND_HANDLER(IDC_EVENT_TOKEN_LIST, LBN_SELCHANGE, OnSelchangeEventTokenList)
		COMMAND_HANDLER(IDC_EVENT_LIST, LBN_SELCHANGE, OnSelchangeEventList)
		CHAIN_MSG_MAP(ui_page_dialog_base)
	END_MSG_MAP()	

	QLib::Event<void,Token*> EventGoToLine;

	LRESULT OnEditEventBtn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		int index = m_tokenList.GetCurSel();
		if (index == -1)
			return 0;
		Token * tk = (Token*)m_tokenList.GetItemData(index);
		EventGoToLine(tk);
		return 0;
	}
	LRESULT OnAddEventBtn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		int index = m_eventList.GetCurSel();
		if (index == -1) {
			return 0;
		}
		winx_event * ev = (winx_event*)m_eventList.GetItemData(index);
		OnAddnewEvent(ev);
		return 0;
	}
	LRESULT OnDelEventBtn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		int index = m_tokenList.GetCurSel();
		if (index == -1) {
			return 0;
		}
		Token * tk = (Token*)m_tokenList.GetItemData(index);
		if ( OnDeleteToken(tk) == true)
		{
			m_tokenList.DeleteString(index);
		}
		return 0;
	}
	LRESULT OnSelchangeEventTokenList(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		// TODO : Add Code for control notification handler.
		int index = m_tokenList.GetCurSel();
		if (index <= -1) {
			return 0;
		}
		Token * tk = (Token*)m_tokenList.GetItemData(index);
		m_eventList.SetCurSel(FindEventWinxList(tk));
		return 0;
	}
	LRESULT OnSelchangeEventList(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		// TODO : Add Code for control notification handler.
		int index = m_eventList.GetCurSel();
		if (index <= -1) {
			return 0;
		}
		winx_event * ev = (winx_event*)m_eventList.GetItemData(index);
		m_tokenList.SetCurSel(FindEventTokenList(ev));
		return 0;
	}
protected:
	int FindEventTokenList(winx_event * ev)
	{
		if (ev == NULL) {
			return -1;
		}
		for (int i = 0; i < m_tokenList.GetCount(); i++) {
			Token * tk = (Token*)m_tokenList.GetItemData(i);
			if (tk && ((CString)tk->m_Name == ev->name)) {
				return i;
			}
		}
		return -1;
	}
	int FindEventWinxList(Token * tk)
	{
		if (tk == NULL) {
			return -1;
		}
		for (int i = 0; i < m_eventList.GetCount(); i++) {
			winx_event * ev = (winx_event*)m_eventList.GetItemData(i);
			if (ev != NULL && (ev->name == (CString)tk->m_Name) ) {
				return i;
			}
		}
		return -1;
	}

	bool OnAddnewEvent(winx_event * ev)
	{
		if (FindEventTokenList(ev) != -1) {
			return false;
		}
		Token * tk = pcode->WinxAddEventToken(ev,m_tkcls);
		int index = AddWinxEventToken(tk);
		m_tokenList.SetCurSel(index);
		return true;
	}
	bool AskRemoveToken(Token * tk)
	{
		CString text;
		text = _T("Deleting this winx event is auto rename ");
		text += tk->m_Name;
		text += _T(" to _winxDEL_");
		text += tk->m_Name;
		text += _T(". Continue?");
		UINT id = ::MessageBox(m_hWnd,text,_T("Delete Winx Event"),MB_YESNOCANCEL | MB_ICONQUESTION);
		if (id == IDYES)
			return true;
		return false;
	}
	bool OnDeleteToken(Token * tk)
	{
		return pcode->WinxRemoveEventToken(tk,QLib::Event<bool,Token*>(this,&page_winx_event::AskRemoveToken));
	}
};

class add_notify_dlg : public ui_simple_dialog_t<add_notify_dlg,IDD_ADD_NOTIFY_DIALOG>
{
public:
	CString		m_notify;
	CString		m_function;
	CString		m_objectid;
public:
	void OnInit()
	{
		SetDlgItemText(IDC_NOTIFY_STATIC,m_notify);
		SetDlgItemText(IDC_OBJECTID_STATIC,m_objectid);
		SetDlgItemText(IDC_FUNCTIONNAME_EDIT,m_function);
		CEdit ed = GetDlgItem(IDC_FUNCTIONNAME_EDIT);
		ed.SetFocus();
		ed.SetSel(2,-1);
	}
	BOOL OnClose()
	{
		CEdit ed = GetDlgItem(IDC_FUNCTIONNAME_EDIT);
		TCHAR sz[256] = {0};
		ed.GetWindowText(sz,255);
		m_function = sz;
		if (m_function.IsEmpty())
			return FALSE;
		return TRUE;
	}
};

class page_winx_notify : public ui_page_dialog_t<page_winx_notify,IDD_PAGE_WINX_NOTIFY>
{
public:
	codeparser * pcode;
	Token	   * m_tkcls;
	CListBox	 m_ctrlList;
	CListBox     m_menuList;
	CListBox	 m_notifyList;
	CListBox	 m_tokenList;
	win32_notify	* m_wn;
public:
	BEGIN_DLGRESIZE_MAP(page_winx_notify)
		DLGRESIZE_CONTROL(IDC_CONTROL_LIST, 0)
		DLGRESIZE_CONTROL(IDC_MENU_LIST,0)
		DLGRESIZE_CONTROL(IDC_NOTIFY_LIST,DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_NOTIFY_TOKEN_LIST, DLSZ_SIZE_X|DLSZ_SIZE_Y)
		DLGRESIZE_CONTROL(IDC_ADDNOTIFY_BTN,DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_DELNOTIFY_BTN, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_EDITNOTIFY_BTN, DLSZ_MOVE_X)
	END_DLGRESIZE_MAP()

	void OnInit()
	{
		m_ctrlList = GetDlgItem(IDC_CONTROL_LIST);
		m_menuList = GetDlgItem(IDC_MENU_LIST);
		m_notifyList = GetDlgItem(IDC_NOTIFY_LIST);
		m_tokenList = GetDlgItem(IDC_NOTIFY_TOKEN_LIST);
	}

	int AddWinxNotifyToken(Token * tk)
	{
		int index = m_tokenList.AddString(tk->m_Name+tk->m_Args);
		m_tokenList.SetItemData(index,(DWORD)tk);
		return index;
	}
	void AddResControl(const ResControl * ctrl)
	{
		int index = m_ctrlList.AddString(ctrl->m_ID);
		m_ctrlList.SetItemData(index,(DWORD)ctrl);
	}
	void AddResMenuItem(const ResMenuItem * menu)
	{
		int index = m_menuList.AddString(menu->m_ID);
		m_menuList.SetItemData(index,(DWORD)menu);
	}
	void AddControlNotify(win32_notify_code * wnc)
	{
		int index = m_notifyList.AddString(wnc->code);
		m_notifyList.SetItemData(index,(DWORD)wnc);
	}

	void OnClassChange(Token * tkcls)
	{
		m_tkcls = tkcls;
		m_tokenList.ResetContent();
		m_notifyList.ResetContent();
		if (tkcls)	{
			pcode->EnumWinxMessageToken(tkcls,QLib::Event<void,Token*>(this,&page_winx_notify::AddWinxNotifyToken));
		}
	}

	void OnResDialogChange(CResDialog * dlg)
	{
		m_ctrlList.ResetContent();
		if (dlg) {
			pcode->EnumResDialogControl(dlg,QLib::Event<void,const ResControl*>(this,&page_winx_notify::AddResControl));
		}
	}
	
	void OnResMenuChange(CResMenu * menu)
	{
		m_menuList.ResetContent();
		if (menu) {
			pcode->EnumResMenuItem(menu,QLib::Event<void,const ResMenuItem*>(this,&page_winx_notify::AddResMenuItem));
		}
	}
public:
	BEGIN_MSG_MAP(page_winx_notify)
		COMMAND_ID_HANDLER(IDC_EDITNOTIFY_BTN, OnEditNotifyBtn)
		COMMAND_ID_HANDLER(IDC_ADDNOTIFY_BTN, OnAddNotifyBtn)
		COMMAND_ID_HANDLER(IDC_DELNOTIFY_BTN, OnDelNotifyBtn)
		COMMAND_HANDLER(IDC_CONTROL_LIST, LBN_SELCHANGE, OnSelchangeControlList)
		COMMAND_HANDLER(IDC_MENU_LIST, LBN_SELCHANGE, OnSelchangeMenuList)
		COMMAND_HANDLER(IDC_NOTIFY_LIST, LBN_SELCHANGE, OnSelchangeNotifyList)
		COMMAND_HANDLER(IDC_NOTIFY_TOKEN_LIST, LBN_SELCHANGE, OnSelchangeNotifyTokenList)
		CHAIN_MSG_MAP(ui_page_dialog_base)
	END_MSG_MAP()	

	QLib::Event<void,Token*> EventGoToLine;

	LRESULT OnEditNotifyBtn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		int index = m_tokenList.GetCurSel();
		if (index == -1)
			return 0;
		Token * tk = (Token*)m_tokenList.GetItemData(index);
		EventGoToLine(tk);
		return 0;
	}

	CString GetIDFunctionName(LPCTSTR id)
	{
		CString name = id;
		if (name.Left(4) == _T("IDC_"))
			name = name.Right(name.GetLength()-4);
		else if (name.Left(3) == _T("ID_"))
			name = name.Right(name.GetLength()-3);
		else if (name.Left(2) == _T("ID"))
			name = name.Right(name.GetLength()-2);
		CString func;
		for (int i = 0; i < name.GetLength(); i++)
		{
			CString ch = name.GetAt(i);
			if (i == 0)
			{
				ch.MakeUpper();
				func += ch;
			}
			else if (name.GetAt(i-1) == _T('_'))
			{
				ch.MakeUpper();
				func += ch;
			}
			else if (ch != _T("_"))
			{
				ch.MakeLower();
				func += ch;
			}
		}
		return func;
	}

	bool OnAddNotify(win32_notify_code * wnc, LPCTSTR id, bool bMenu)
	{
		add_notify_dlg dlg;
		dlg.m_notify = _T("Message: ")+wnc->code;
		dlg.m_objectid = _T("Object ID: ")+(CString)id;
		dlg.m_function = wnc->func+GetIDFunctionName(id);
		if (dlg.DoModal() == IDOK)
		{
			Token * tk = pcode->WinxAddNotifyToken(wnc,m_tkcls,id,dlg.m_function,bMenu);
			int item = AddWinxNotifyToken(tk);
			m_tokenList.SetCurSel(item);
		}
		//MessageBox(wnc->func,id);
		return true;
	}

	LRESULT OnAddNotifyBtn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		int index = m_notifyList.GetCurSel();
		if (index == -1) {
			return 0;
		}
		win32_notify_code * wnc = (win32_notify_code*)m_notifyList.GetItemData(index);
		int item = m_ctrlList.GetCurSel();
		if (item != -1)
		{
			ResControl * ctrl = (ResControl*)m_ctrlList.GetItemData(item);
			OnAddNotify(wnc,ctrl->m_ID,false);
		}
		item = m_menuList.GetCurSel();
		if (item != -1)
		{
			ResMenuItem * menu = (ResMenuItem*)m_menuList.GetItemData(item);
			OnAddNotify(wnc,menu->m_ID,true);
		}
		return 0;
	}

	CString GetNotifyTokenFuncitonName(Token * tk)
	{
		CString tmp = tk->m_Args;
		tmp.TrimLeft(_T("("));
		tmp.TrimRight(_T(")"));
		CAtlArray<CString> array;
		CutString(tmp,array,_T(","));
		if (array.GetCount() == 0)
			return _T("");
		for (int i = array.GetCount()-1; i >= 0; i++)
		{
			CString text = array[i];
			text.TrimLeft();
			text.TrimRight();
			if (!text.IsEmpty())
				return text;
		}
		return _T("");
	}
	bool AskRemoveToken(Token * tk)
	{
		CString text;
		text = _T("Deleting this handler requires manul removal of the implementation of\r\n");
		if (tk->m_pParent)
		{
			text += tk->m_pParent->m_Name;
			text += _T("::");
		}
		text += GetNotifyTokenFuncitonName(tk);
		text += _T(". Continue?");
		UINT id = ::MessageBox(m_hWnd,text,_T("Delete Winx Notify"),MB_YESNOCANCEL | MB_ICONQUESTION);
		if (id == IDYES)
			return true;
		return false;
	}
	
	LRESULT OnDelNotifyBtn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		int index = m_tokenList.GetCurSel();
		if (index == -1)
			return 0;
		Token * tk = (Token*)m_tokenList.GetItemData(index);
		bool bRet = pcode->WinxRemoveNotifyToken(tk,QLib::Event<bool,Token*>(this,&page_winx_notify::AskRemoveToken));
		if (bRet)
		{
			m_tokenList.DeleteString(index);
		}
		return 0;
	}

	LRESULT OnSelchangeControlList(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		int index = m_ctrlList.GetCurSel();
		if (index <= -1) { 
			return 0;
		}
		ResControl * ctrl = (ResControl*)m_ctrlList.GetItemData(index);
		m_wn = pcode->GetResControlNotify(ctrl);
		m_notifyList.ResetContent();
		pcode->EnumControlNofity(m_wn,QLib::Event<void,win32_notify_code*>(this,&page_winx_notify::AddControlNotify));
		m_menuList.SetCurSel(-1);
		return 0;
	}

	LRESULT OnSelchangeMenuList(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		int index = m_menuList.GetCurSel();
		if (index <= -1) {
			return 0;
		}
		m_wn = pcode->GetResMenuNotify();
		m_notifyList.ResetContent();
		pcode->EnumControlNofity(m_wn,QLib::Event<void,win32_notify_code*>(this,&page_winx_notify::AddControlNotify));
		m_ctrlList.SetCurSel(-1);
	}

	LRESULT OnSelchangeNotifyList(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		int index = m_notifyList.GetCurSel();
		if (index <= -1) {
			return 0;
		}
		return 0;
	}

	LRESULT OnSelchangeNotifyTokenList(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		return 0;
	}

};

class page_winx_prop : public ui_page_dialog_t<page_winx_prop,IDD_PAGE_WINX_PROP>
{
public:
	codeparser * pcode;
	CListBox	 m_propList;
	CListBox	 m_tokenList;
public:
	BEGIN_DLGRESIZE_MAP(page_winx_prop)
		DLGRESIZE_CONTROL(IDC_PROP_LIST, DLSZ_SIZE_Y)
		DLGRESIZE_CONTROL(IDC_PROP_TOKEN_LIST, DLSZ_SIZE_Y)
	END_DLGRESIZE_MAP()

	void OnInit()
	{
		m_propList = GetDlgItem(IDC_PROP_LIST);
		m_tokenList = GetDlgItem(IDC_PROP_TOKEN_LIST);
	}

	void AddPropTokenList(Token * tk)
	{
		int item = m_tokenList.AddString(tk->m_Name+tk->m_Args);
		m_tokenList.SetItemData(item,(DWORD)tk);
	}

	void OnClassChange(Token * tkcls)
	{
		m_tokenList.ResetContent();
		if (tkcls)
			pcode->EnumWinxProperty(tkcls,QLib::Event<void,Token*>(this,&page_winx_prop::AddPropTokenList));
	}
};

class page_class_info : public ui_page_dialog_t<page_class_info,IDD_PAGE_CLASSINFO>
{
public:
	codeparser * pcode;
public:
	BEGIN_DLGRESIZE_MAP(page_class_info)
		DLGRESIZE_CONTROL(IDC_INFO_STATIC, DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_INFO_BASECLASS, DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_INFO_RESOURCE, DLSZ_SIZE_X)
	END_DLGRESIZE_MAP()
	void OnInit()
	{
	}
	void OnClassChange(Token * tkcls)
	{
		if (tkcls)
			SetDlgItemText(IDC_INFO_BASECLASS,tkcls->m_AncestorsString);
		else
			SetDlgItemText(IDC_INFO_BASECLASS,_T(""));
	}
	void OnResDialogChange(CResDialog * dlg)
	{
		if (dlg)
			SetDlgItemText(IDC_INFO_RESOURCE,dlg->m_ID);
		else
			SetDlgItemText(IDC_INFO_RESOURCE,_T(""));
	}
};

class page_about : public ui_page_dialog_t<page_about,IDD_PAGE_ABOUT>
{
public:
	void OnInit()
	{
	}
};

class wizard_ui_item : public ui_item_dialog_t<wizard_ui_item,IDD_WIZARD_DIALOG,true,fox::ui::vs_item>
{
	struct vs60_dsp
	{
		CString name;
		CString path;
	};
public:
	codeparser		    m_code;
	fox::vs60_addin    * pVS60;
public:
	wizard_ui_item() : pVS60(NULL)
	{
	}
	virtual const char * name()
	{
		return "Winx Wizard";
	}
	virtual void set_vsaddin(fox::vs_addin * pvs)
	{
		pVS60 = NULL;
		if (pvs->get_version() == 0x60)
			pVS60 = (fox::vs60_addin*)pvs;
	}
protected:
	CTabCtrlEx			m_wndTab;

	page_winx_event		m_page_winx_event;
	page_winx_notify	m_page_winx_notify;
//	page_winx_prop		m_page_winx_prop;
	page_class_info		m_page_class_info;
	page_about			m_page_about;
public:
	QLib::Event<void,vs60_dsp*>		EventProjectChange;
	QLib::Event<void,Token*>		EventClassChange;
	QLib::Event<void,CResDialog*>	EventResDialogChange;
	QLib::Event<void,CResMenu*>		EventResMenuChange;
public:
	BEGIN_MSG_MAP(wizard_ui_item)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		COMMAND_HANDLER(IDC_CLASSNAME_COMBO, CBN_SELENDOK, OnSelchangeClassnameCombo)
		COMMAND_HANDLER(IDC_RESDIALOG_COMBO, CBN_SELENDOK, OnSelchangeResDialogCombo)
		COMMAND_HANDLER(IDC_RESMENU_COMBO,   CBN_SELENDOK, OnSelchangeResMenuCombo)
		CHAIN_MSG_MAP(ui_item_dialog_base)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	BEGIN_DLGRESIZE_MAP(wizard_ui_item)
		DLGRESIZE_CONTROL(IDC_PANE_TAB,DLSZ_SIZE_X | DLSZ_SIZE_Y)
		DLGRESIZE_CONTROL(IDOK,DLSZ_MOVE_Y)
		DLGRESIZE_CONTROL(IDCANCEL,DLSZ_MOVE_Y)
	END_DLGRESIZE_MAP()
public:
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		::EnableWindow(GetParent(),TRUE);
		ShowWindow(SW_HIDE);
		return 0;
	}
	struct insert_point
	{
		CSimpleArray<CString> array;
		int     line;
		void AddNewLine()
		{
			array.Add((CString)_T("\r\n"));
		}
		void AddLine(LPCTSTR lpszLine, int ntab)
		{
			CString tab;
			for (int i = 0; i < ntab; i++)
				tab += _T("\t");
			array.Add(tab+(CString)_T("\r\n"));
			if (lstrlen(lpszLine) != 0)
				array.Add(tab+(CString)lpszLine);
		}
		CString GetText()
		{
			CString text;
			for (int i = 0; i < array.GetSize(); i++)
			{
				text += array[i];
			}
			return text;
		}
	};
	typedef std::map<CString,CSimpleArray<insert_point*> > INSERTPT_MAP;

	void ProcessUpdateTokenFunction(Token * tkcls, Token * tk, INSERTPT_MAP & ptmap)
	{
		if (tk->m_TokenUpdate == tuRemove)
		{
			if (!tk->m_Filename.IsEmpty() && pVS60)
			{
				pVS60->replace_text(tk->m_Filename,tk->m_Line,tk->m_Name,"_winxDEL_"+tk->m_Name);
			}
			if (!tk->m_ImplFilename.IsEmpty() && pVS60)
			{
				pVS60->replace_text(tk->m_ImplFilename,tk->m_ImplLine,tk->m_Name,"_winxDEL_"+tk->m_Name);
			}
		}
		else if (tk->m_TokenUpdate == tuAddnew)
		{
			Token * last = m_code.GetLastTokenByScope(tkcls,tk->m_Scope);
			int line = 0;
			if (last == NULL)
			{
				line = tkcls->m_EndLine-1;
			}
			else
			{
				if (last->m_TokenKind == tkFunction)
				{
					if (last->m_ImplFilename.IsEmpty())
						line = last->m_EndLine;
					else
						line = last->m_Line;
				}
				else 
					line = last->m_Line;
			}
			insert_point * pt = new insert_point();
			pt->line = line;
			winx_event * ev = (winx_event*)tk->m_Data;
			if (last == NULL)
				pt->AddLine(tk->GetTokenScopeString()+_T(":"),0);
			pt->AddNewLine();
			pt->AddLine(ev->func,1);
			pt->AddLine(_T("{"),1);
			if (!ev->body.IsEmpty())
				pt->AddLine(ev->body,2);
			pt->AddLine(_T("}"),1);
			ptmap[(CString)tkcls->m_Filename].Add(pt);
		}
	}
	void ProcessUpdateNotifyTokenFunction(Token * tkcls, const CString & func, const CString & body,INSERTPT_MAP & ptmap)
	{
		Token * last = m_code.GetLastTokenByScope(tkcls,tsPublic);
		int line = 0;
		if (last == NULL)
		{
			line = tkcls->m_EndLine-1;
		}
		else
		{
			if (last->m_TokenKind == tkFunction)
			{
				if (last->m_ImplFilename.IsEmpty())
					line = last->m_EndLine;
				else
					line = last->m_Line;
			}
			else 
				line = last->m_Line;
		}
		insert_point * pt = new insert_point();
		pt->line = line;
		//if (last == NULL)
		//	pt->AddLine(_T("public:"),0);
		pt->AddNewLine();
		pt->AddLine(func,1);
		pt->AddLine(_T("{"),1);
		if (!body.IsEmpty())
			pt->AddLine(body,2);
		pt->AddLine(_T("}"),1);
		ptmap[(CString)tkcls->m_Filename].Add(pt);
	}

	int GetFirstInsertLine(Token * tkcls)
	{
		for (int i = 0; i < tkcls->m_Children.GetCount(); i++)
		{
			Token * tk = tkcls->m_Children[i];
			if (tk->m_TokenUpdate == tuNormal && 
				( tk->m_TokenKind == tkFunction || 
				  tk->m_TokenKind == tkVariable) )
			{
				return tk->m_Line-1;
			}
		}
		return tkcls->m_EndLine-1;
	}
	void ProcessUpdateTokenCmd(Token * tkcls, CSimpleArray<Token*> & cmd, INSERTPT_MAP & ptmap)
	{
		if (cmd.GetSize() == 0)
			return;
		int line = 0;
		Token * head = m_code.GetFirstTokenByName(tkcls,_T("WINX_CMDS_BEGIN_EX"));
		if (!head)
			head = m_code.GetFirstTokenByName(tkcls,_T("WINX_CMDS_BEGIN"));
		if (head)
			line = head->m_Line;
		else
			line = GetFirstInsertLine(tkcls);
		insert_point * pt = new insert_point();
		pt->line = line;
		int i = 0;
		if (head == NULL)
			pt->AddLine(_T("WINX_CMDS_BEGIN_EX()"),1);
		for (i = 0; i < cmd.GetSize(); i++)
		{
			Token * tk = cmd[i];
			pt->AddLine(tk->m_Name+tk->m_Args,2);
		}
		if (head == NULL)
			pt->AddLine(_T("WINX_CMDS_END_EX();\r\n"),1);

		ptmap[(CString)tkcls->m_Filename].Add(pt);	

		for (i = 0; i < cmd.GetSize(); i++)
		{
			Token * tk = cmd[i];
			ProcessUpdateNotifyTokenFunction(tkcls,(LPCTSTR)tk->m_String,_T(""),ptmap);
		}
	}
	void ProcessUpdateTokenNotify(Token * tkcls, CSimpleArray<Token*> & cmd, INSERTPT_MAP & ptmap)
	{
		if (cmd.GetSize() == 0)
			return;
		int line = 0;
		Token * head = m_code.GetFirstTokenByName(tkcls,_T("WINX_NOTIFY_BEGIN"));
		if (head)
			line = head->m_Line+1;
		else
			line = GetFirstInsertLine(tkcls);
		insert_point * pt = new insert_point();
		pt->line = line;
		int i = 0;
		if (head == NULL)
			pt->AddLine(_T("WINX_NOTIFY_BEGIN()"),1);
		for (i = 0; i < cmd.GetSize(); i++)
		{
			Token * tk = cmd[i];
			pt->AddLine(tk->m_Name+tk->m_Args,2);
		}
		if (head == NULL)
			pt->AddLine(_T("WINX_NOTIFY_END();\r\n"),1);

		ptmap[(CString)tkcls->m_Filename].Add(pt);	

		for (i = 0; i < cmd.GetSize(); i++)
		{
			Token * tk = cmd[i];
			ProcessUpdateNotifyTokenFunction(tkcls,(LPCTSTR)tk->m_String,_T(""),ptmap);
		}
	}
	void ProcessUpdateClass(Token * tkcls, INSERTPT_MAP & ptmap)
	{
		int i = 0;
		//pre process mapping
		CSimpleArray<Token*>  cmd;
		CSimpleArray<Token*>  notify;
		for (i = 0; i < tkcls->m_Children.GetCount(); i++)
		{
			Token * tk = tkcls->m_Children[i];
			if (tk->m_TokenKind == tkMapping)
			{
				//ProcessUpdateTokenMapping(tkcls,tk,ptmap);
				if (tk->m_TokenUpdate == tuRemove)
				{
					if (!tk->m_Filename.IsEmpty() && pVS60)
					{
						pVS60->replace_text(tk->m_Filename,tk->m_Line,tk->m_Name,"//"+tk->m_Name);
					}
				}
				else if (tk->m_TokenUpdate == tuAddnew)
				{
					if (tk->m_Name == _T("WINX_CMD") ||
						tk->m_Name == _T("WINX_CMD_EX"))
					{
						cmd.Add(tk);
					}
					else if (tk->m_Name == _T("WINX_NOTIFY"))
					{
						notify.Add(tk);
					}
				}
			}
		}
		ProcessUpdateTokenCmd(tkcls,cmd,ptmap);
		ProcessUpdateTokenNotify(tkcls,notify,ptmap);
		
		// process funciton
		for (i = 0; i < tkcls->m_Children.GetCount(); i++)
		{
			Token * tk = tkcls->m_Children[i];
			if (tk->m_TokenKind == tkFunction)
			{
				ProcessUpdateTokenFunction(tkcls,tk,ptmap);
			}
		}
	}
	void ProcessInsertPoint(INSERTPT_MAP & ptmap)
	{
		for (INSERTPT_MAP::iterator it = ptmap.begin(); it != ptmap.end(); it++)
		{
			const CString & filename = it->first;
			CSimpleArray<insert_point*> & ar = it->second;
			typedef std::multimap<int,insert_point*,std::greater<int> > MM_MAP;
			MM_MAP mm;
			for (int i = 0; i < ar.GetSize(); i++)
			{
				insert_point * pt = ar[i];
				mm.insert(MM_MAP::value_type(pt->line,pt));
			}
			int line = 0;
			for (MM_MAP::iterator it = mm.begin(); it != mm.end(); it++)
			{
				insert_point * pt = it->second;
				if (pVS60)
				{
					pVS60->insert_block(filename,pt->line,0,pt->GetText());
				}
			}
		}
	}
	void ProcessUpdate()
	{
		INSERTPT_MAP ptmap;
	
		for (int i = 0; i < m_code.m_Tokens.GetCount(); i++)
		{
			Token * tk = m_code.m_Tokens[i];
			if (tk->m_TokenKind == tkClass)
			{
				ProcessUpdateClass(tk,ptmap);
			}
		}

		ProcessInsertPoint(ptmap);

		for (INSERTPT_MAP::iterator it = ptmap.begin(); it != ptmap.end(); it++)
		{
			CSimpleArray<insert_point*> & ar = it->second;
			for (int i = 0; i < ar.GetSize(); i++)
				delete ar[i];
			ar.RemoveAll();
		}
	}
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		//enbale parent hwnd
		::EnableWindow(GetParent(),TRUE);
		ShowWindow(SW_HIDE);
		if (wID == IDCANCEL)
			return wID;
		ProcessUpdate();

		return wID;
	}
public:
	CComboBox	m_projectCmb;
	CComboBox	m_classCmb;
	CComboBox	m_dialogCmb;
	CComboBox   m_menuCmb;
	CSimpleArray<vs60_dsp>	m_projects;
public:
	int AddProject(const char * name, const char * dspfile)
	{
		vs60_dsp dsp;
		dsp.name = name;
		dsp.path = dspfile;
		m_projects.Add(dsp);
		vs60_dsp * pdsp = &m_projects[m_projects.GetSize()-1];
		int item = m_projectCmb.AddString(pdsp->name);
		m_projectCmb.SetItemData(item,(DWORD)pdsp);
		return item;
	}
	void AddProjectClass(Token * tk)
	{
		int index = m_classCmb.AddString(tk->m_Name);
		m_classCmb.SetItemData(index,(DWORD)tk);
	}
	void AddProjectDialog(CResDialog * dlg)
	{
		int index = m_dialogCmb.AddString(dlg->m_ID);
		m_dialogCmb.SetItemData(index,(DWORD)dlg);
	}
	void AddProjectMenu(CResMenu * menu)
	{
		int index = m_menuCmb.AddString(menu->m_ID);
		m_menuCmb.SetItemData(index,(DWORD)menu);
	}

	void OnGetToLine(Token * tk)
	{
		if (tk == NULL)
			return;
		if (tk->m_TokenUpdate != tuNormal)
			return;
		if (pVS60)
		{
			::EnableWindow(GetParent(),TRUE);
			ShowWindow(SW_HIDE);
			ProcessUpdate();
			if (!tk->m_ImplFilename.IsEmpty())
			{
				pVS60->goto_line(tk->m_ImplFilename,tk->m_ImplLine);
			}
			else if (!tk->m_Filename.IsEmpty())
			{
				pVS60->goto_line(tk->m_Filename,tk->m_Line);
			}
		}
	}
	void OnInit()
	{
		CenterWindow();
		//enbale parent hwnd
		m_wndTab.SubclassWindow(GetDlgItem(IDC_PANE_TAB));
		m_wndTab.SetMinTabWidth(100);

		m_projectCmb = GetDlgItem(IDC_PROJECT_COMBO);
		m_classCmb   = GetDlgItem(IDC_CLASSNAME_COMBO);
		m_dialogCmb  = GetDlgItem(IDC_RESDIALOG_COMBO);
		m_menuCmb    = GetDlgItem(IDC_RESMENU_COMBO);

		m_page_winx_event.Create(m_hWnd);
		m_page_winx_event.pcode = &this->m_code;

		m_page_winx_notify.Create(m_hWnd);
		m_page_winx_notify.pcode = &this->m_code;

	//	m_page_winx_prop.Create(m_hWnd);
	//	m_page_winx_prop.pcode = &this->m_code;

		m_page_class_info.Create(m_hWnd);
		m_page_class_info.pcode = &this->m_code;

		m_page_about.Create(m_hWnd);

		m_page_winx_event.EventGoToLine.bind(this,&wizard_ui_item::OnGetToLine);
		m_page_winx_notify.EventGoToLine.bind(this,&wizard_ui_item::OnGetToLine);

		EventProjectChange.bind(this,&wizard_ui_item::OnProjectChange);
		EventClassChange.bind(this,&wizard_ui_item::OnClassChange);

		EventClassChange.bind(&m_page_winx_event,&page_winx_event::OnClassChange);
		EventClassChange.bind(&m_page_winx_notify,&page_winx_notify::OnClassChange);
	//	EventClassChange.bind(&m_page_winx_prop,&page_winx_prop::OnClassChange);
		EventClassChange.bind(&m_page_class_info,&page_class_info::OnClassChange);

		EventResDialogChange.bind(&m_page_winx_notify,&page_winx_notify::OnResDialogChange);
		EventResDialogChange.bind(&m_page_class_info,&page_class_info::OnResDialogChange);
		EventResDialogChange.bind(this,&wizard_ui_item::OnResDialogChange);
		
		EventResMenuChange.bind(&m_page_winx_notify,&page_winx_notify::OnResMenuChange);

		m_wndTab.InsertItemEx(0,_T("Winx Event"),m_page_winx_event);
		m_wndTab.InsertItemEx(1,_T("Winx Message"),m_page_winx_notify);
	//	m_wndTab.InsertItemEx(2,_T("Winx Property"),m_page_winx_prop);
		m_wndTab.InsertItemEx(2,_T("Class Info"),m_page_class_info);
		m_wndTab.InsertItemEx(3,_T("About"),m_page_about);
		m_wndTab.SetActiveItem(0);

		
		if (!m_code.m_winxev.loadex(GetModulePath(_Module.m_hInst)+_T("\\winxevent.ini")))
		{
			MessageBox(_T("Load winxevent.ini false!"));
		}
		if (!m_code.m_notify.loadex(GetModulePath(_Module.m_hInst)+_T("\\message.ini")))
		{
			MessageBox(_T("Load message.ini false!"));
		}
		
	}
	
	virtual void load_project(const char * name, const char * dspfile, bool bAppend)
	{
		ShowWindow(SW_SHOW);
		::EnableWindow(GetParent(),FALSE);
		if (bAppend == false)
		{
			m_projects.RemoveAll();
			m_projectCmb.ResetContent();
			m_classCmb.ResetContent();
			m_dialogCmb.ResetContent();
			m_menuCmb.ResetContent();
		}
		
		int item  = AddProject(name,dspfile);
		vs60_dsp * pdsp = (vs60_dsp*)m_projectCmb.GetItemData(item);
		m_projectCmb.SetCurSel(item);
		EventProjectChange(pdsp);
	}

	bool SelectCombo(CComboBox * cmb, DWORD dwData)
	{
		for (int i = 0; i < cmb->GetCount(); i++)
		{
			if (cmb->GetItemData(i) == dwData) {
				cmb->SetCurSel(i);
				return true;
			}
		}
		cmb->SetCurSel(-1);
		return false;
	}

	void OnProjectChange(vs60_dsp * dsp)
	{
		m_classCmb.ResetContent();
		m_dialogCmb.ResetContent();
		m_menuCmb.ResetContent();

		if (dsp == NULL)
			return;

		m_code.LoadVS606DSP(dsp->path);
		//enum code
		m_code.EnumProjectClass(QLib::Event<void,Token*>(this,&wizard_ui_item::AddProjectClass));
		m_code.EnumResDialog(QLib::Event<void,CResDialog*>(this,&wizard_ui_item::AddProjectDialog));
		m_code.EnumResMenu(QLib::Event<void,CResMenu*>(this,&wizard_ui_item::AddProjectMenu));
		m_dialogCmb.AddString(_T("Null Dialog"));
		m_menuCmb.AddString(_T("Null Menu"));
		//init
		Token * tkcls = NULL;
		if (m_classCmb.GetCount() >= 1)
		{
			m_classCmb.SetCurSel(0);
			tkcls = (Token*)m_classCmb.GetItemData(0);
		}
		EventClassChange(tkcls);
	}

	void OnClassChange(Token * tkcls)
	{
		CResDialog * dlg = NULL;
		if (tkcls)
			dlg = m_code.GetResDialog(tkcls);
		SelectCombo(&m_dialogCmb,(DWORD)dlg);
		EventResDialogChange(dlg);
		if (tkcls)
			SetDlgItemText(IDC_FILENAME, tkcls->m_Filename+_T(";")+tkcls->m_ImplFilename);
		else
			SetDlgItemText(IDC_FILENAME,_T(""));
	}

	void OnResDialogChange(CResDialog * dlg)
	{
		CResMenu * menu = NULL;
		if (dlg && !dlg->m_Menu.IsEmpty()) {
			menu = m_code.GetResDialogMenu(dlg->m_Menu);
		}
		SelectCombo(&m_menuCmb,(DWORD)menu);
		EventResMenuChange(menu);
	}

	LRESULT OnSelchangeClassnameCombo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		int index = m_classCmb.GetCurSel();
		if (index == -1) {
			return 0;
		}
		Token * tk = (Token*)m_classCmb.GetItemData(index);
		if (tk != NULL) {
			EventClassChange(tk);
		}
		return 0;
	}

	LRESULT OnSelchangeResDialogCombo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		int index = m_dialogCmb.GetCurSel();
		if (index == -1) {
			return 0;
		}
		CResDialog * dlg = (CResDialog*)m_dialogCmb.GetItemData(index);
		EventResDialogChange(dlg);
		return 0;
	}

	LRESULT OnSelchangeResMenuCombo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		int index = m_menuCmb.GetCurSel();
		if (index == -1) {
			return 0;
		}
		CResMenu * menu = (CResMenu*)m_menuCmb.GetItemData(index);
		EventResMenuChange(menu);
		return 0;
	}
};

extern "C"
fox::ui::item * fox_get_interface()
{
	fox::ui::item * item =  new wizard_ui_item;
	return item;
}

#endif 
