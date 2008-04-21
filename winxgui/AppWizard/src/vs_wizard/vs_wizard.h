// vs_wizard.h: interface for the vs_wizard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VS_WIZARD_H__8A8AB2C1_6A1D_4768_A013_A7984B116DD8__INCLUDED_)
#define AFX_VS_WIZARD_H__8A8AB2C1_6A1D_4768_A013_A7984B116DD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <map>
#include <set>
#include <string>

#include "../public/qevent.h"

typedef std::vector<CString>		str_vector;
typedef std::map<CString,CString>   str_map;
typedef std::set<CString>			str_set;

class vs_wizard_info
{
public:
	void save_cfg_int(LPCTSTR lpszkey, int val);
	int load_cfg_int(LPCTSTR lpszKey, int def);
	bool check_project_name(LPCTSTR lpszFileName);
	vs_wizard_info();

	static CString GetModulePath(HMODULE hMod);

	void save_cfg_str(LPCTSTR lpszKey, LPCTSTR lpszVal);
	CString load_cfg_str(LPCTSTR lpszKey, LPCTSTR lpszDef = _T(""));
	void save_cfg_bool(LPCTSTR lpszKey,bool bval);
	bool load_cfg_bool(LPCTSTR lpszKey,bool bdef);

	bool load_lang();
	std::vector<CString>	ar_lang;
	int			nAppLang;


	CString		templatePath;
	CString		cfgPath;
	CString		cfgApp;
	
	int			nWizardRet;

	QLib::Event<bool>	event_finish;
};

class vs_wizard  
{
public:
	CString make_include_guid();
	void clear();
	void get_output_info(CString & text);
	void get_define_info(CString & text);
	CString make_guid();
	CString FindSymbolVal(LPCTSTR lpszKey);
	bool FindSymbol(LPCTSTR lpszKey);
	void AddSymbol(LPCTSTR lpszDefine, bool bAdd);
	void AddSymbol(LPCTSTR lpszKey, LPCTSTR lpszValue);
	bool make_file(LPCTSTR lpszFileIn, LPCTSTR lpszFileOut);
	bool load_file_vector(LPCTSTR lpszFileIn, str_vector &array);
	bool get_vector_alltrue(std::vector<bool> &array);
	bool line_to_array(LPCTSTR lpszLine, str_vector & array, int & flag);
	bool get_define_line(LPCTSTR lpszLine);
	void replace_line(LPCTSTR in, CString &out);
	vs_wizard();
	virtual ~vs_wizard();

	str_map					m_output;	//[!output xxx]
	str_set					m_define;   //[!if xxx && xx]
};


template <class T, class TWizardInfo, class TBase = CWizard97PageWindow>
class ATL_NO_VTABLE CWizardPageImpl : public CPropertyPageImpl< T, TBase >, 
		public CWinDataExchange<T>, public CUpdateUI<T>
{
public:
// Typedefs
	typedef CWizardPageImpl<T, TWizardInfo, TBase> CWizardPageImplBase;
	typedef CWizard97InteriorPageImpl< T, TBase > thisClass;
	typedef CPropertyPageImpl< T, TBase > baseClass;
	DWORD	m_dwButton;
public:
	TWizardInfo	 * info;
// Constructors
	CWizardPageImpl(ATL::_U_STRINGorID title = (LPCTSTR)NULL) : baseClass(title)
	{
		m_psp.dwFlags &= ~PSP_HASHELP;
		m_psp.dwFlags &= ~PSP_HIDEHEADER;
		m_psp.dwFlags |= PSP_USEHEADERTITLE | PSP_USEHEADERSUBTITLE;

		// Be sure to have the derived class define this in the constructor.
		// We'll default it to something obvious in case its forgotten.
		baseClass::SetHeaderTitle(_T("Call SetHeaderTitle in Derived Class"));
		baseClass::SetHeaderSubTitle(_T("Call SetHeaderSubTitle in the constructor of the Derived Class."));
		m_dwButton = PSWIZB_BACK | PSWIZB_NEXT | PSWIZB_FINISH;
	}

	BEGIN_UPDATE_UI_MAP(thisClass)
	END_UPDATE_UI_MAP()
// Message Handling
	BEGIN_MSG_MAP(thisClass)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		if (uMsg == WM_COMMAND && ::GetParent(GetDlgItem(LOWORD(wParam))) == m_hWnd)
		{
			T * pT = static_cast<T*>(this);
			pT->DoUpdateUI(LOWORD(wParam));
			pT->UIUpdateChildWindows();
		}
		CHAIN_MSG_MAP(CUpdateUI<T>)
		CHAIN_MSG_MAP(baseClass)
	END_MSG_MAP()

	void DoUpdateUI(UINT id)
	{
	}

	void Enable(UINT nID, BOOL bEnable)
	{
		::EnableWindow(GetDlgItem(nID),bEnable);
	}

	int OnSetActive()
	{
		this->SetWizardButtons(m_dwButton);

		T * pT = static_cast<T*>(this);
		pT->DoDataExchange(false);
		pT->DoUpdateUI(-1);
		pT->UIUpdateChildWindows();
		return pT->ActiveInfo();
	}

	int OnWizardFinish()
	{
		T * pT = static_cast<T*>(this);
		if (pT->UpdateInfo(PSN_WIZFINISH) != 0)
			return -1;
		if (info->event_finish() == false)
		{
			info->nWizardRet = 2;
			return -1;
		}
		info->nWizardRet = 0;
		return 0;
	}
	int OnWizardBack()
	{
		T * pT = static_cast<T*>(this);
		return pT->UpdateInfo(PSN_WIZBACK);
	}
	int OnWizardNext()
	{
		T * pT = static_cast<T*>(this);
		return pT->UpdateInfo(PSN_WIZNEXT);
	}

	int UpdateInfo(int psn)
	{
		T * pT = static_cast<T*>(this);
		if (pT->DoDataExchange(true) == FALSE)
			return -1;
		return 0;
	}
	int ActiveInfo()
	{
		return 0;
	}

	BOOL OnQueryCancel()
	{
		// FALSE = allow cancel
		// TRUE = prevent cancel
		info->nWizardRet = 1;
		return FALSE;
	}

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T * pT = static_cast<T*>(this);
		pT->DoDataExchange(false);

		bHandled = FALSE;
		UIAddChildWindowContainer(m_hWnd);
		
		pT->OnInit();

		return 0;
	}

	void OnInit()
	{
	}

#define DDX_CBTEXT(nID, var) \
		if(nCtlID == (UINT)-1 || nCtlID == nID) \
		{ \
			if(!DDX_CBString(nID, var, sizeof(var), bSaveAndValidate)) \
				return FALSE; \
		}

	BOOL DDX_CBString(UINT nID, _CSTRING_NS::CString& strText, int /*cbSize*/, BOOL bSave, BOOL bValidate = FALSE, int nLength = 0)
	{
		T* pT = static_cast<T*>(this);
		BOOL bSuccess = TRUE;

		if(bSave)
		{
			HWND hWndCtrl = pT->GetDlgItem(nID);
			int nLen = ::GetWindowTextLength(hWndCtrl);
			int nRetLen = -1;
			LPTSTR lpstr = strText.GetBufferSetLength(nLen);
			if(lpstr != NULL)
			{
				nRetLen = ::GetWindowText(hWndCtrl, lpstr, nLen + 1);
				strText.ReleaseBuffer();
			}
			if(nRetLen < nLen)
				bSuccess = FALSE;
		}
		else
		{
			HWND hWndCtrl = pT->GetDlgItem(nID);
			if (::SendMessage(hWndCtrl, CB_SELECTSTRING, (WPARAM)-1,
				(LPARAM)(LPCTSTR)strText) == CB_ERR)
			{
				// just set the edit text (will be ignored if DROPDOWNLIST)
				bSuccess = pT->SetDlgItemText(nID, strText);
			}
			else
			{
				bSuccess = TRUE;
			}
		}

		if(!bSuccess)
		{
			pT->OnDataExchangeError(nID, bSave);
		}
		else if(bSave && bValidate)   // validation
		{
			ATLASSERT(nLength > 0);
			if(strText.GetLength() > nLength)
			{
				_XData data = { ddxDataText };
				data.textData.nLength = strText.GetLength();
				data.textData.nMaxLength = nLength;
				pT->OnDataValidateError(nID, bSave, data);
				bSuccess = FALSE;
			}
		}
		return bSuccess;
	}
};


#endif // !defined(AFX_VS_WIZARD_H__8A8AB2C1_6A1D_4768_A013_A7984B116DD8__INCLUDED_)
