// cstm1dlg.cpp : implementation file
//

#include "stdafx.h"
#include "winxwiz60.h"
#include "cstm1dlg.h"
#include "winxwiz60aw.h"
#include "WizardUtils.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustom1Dlg dialog


CCustom1Dlg::CCustom1Dlg(CMapStringToString& Dictionary)
	: m_Dictionary(Dictionary), CAppWizStepDlg(CCustom1Dlg::IDD)
{
	//{{AFX_DATA_INIT(CCustom1Dlg)
	m_bMenuBar = FALSE;
	m_bRebar = FALSE;
	m_bCommandBar = FALSE;
	m_bStatusBar = FALSE;
	m_bToolbar = FALSE;
	m_nViewType = 0;
	m_nAppType = 0;
	m_bAccel = FALSE;
	m_bDDX = FALSE;
	m_bActiveX = FALSE;
	//}}AFX_DATA_INIT

	std::WinRegReadKey key(HKEY_CURRENT_USER, WINX_APPWIZ_KEY);
	if (key.good())
	{
		key.getInt(_T("bMenuBar"), m_bMenuBar);
		key.getInt(_T("bRebar"), m_bRebar);
		key.getInt(_T("bCommandBar"), m_bCommandBar);
		key.getInt(_T("bStatusBar"), m_bStatusBar);
		key.getInt(_T("bToolbar"), m_bToolbar);
		key.getInt(_T("bDDX"), m_bDDX);
		key.getInt(_T("bAccel"), m_bAccel);
		key.getInt(_T("bActiveX"), m_bActiveX);
		key.getInt(_T("nViewType"), m_nViewType);
		key.getInt(_T("nAppType"), m_nAppType);
	}
	CAdvanceOptionsDlg(Dictionary).UpdateDictionary();
}


void CCustom1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CAppWizStepDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustom1Dlg)
	DDX_Check(pDX, IDC_UI_MENUBAR, m_bMenuBar);
	DDX_Check(pDX, IDC_UI_REBAR, m_bRebar);
	DDX_Check(pDX, IDC_UI_COMMANDBAR, m_bCommandBar);
	DDX_Check(pDX, IDC_UI_STATUSBAR, m_bStatusBar);
	DDX_Check(pDX, IDC_UI_TOOLBAR, m_bToolbar);
	DDX_CBIndex(pDX, IDC_VIEWTYPE, m_nViewType);
	DDX_Radio(pDX, IDC_DIALOG_APP, m_nAppType);
	DDX_Check(pDX, IDC_UI_ACCEL, m_bAccel);
	DDX_Check(pDX, IDC_UI_DDX, m_bDDX);
	DDX_Check(pDX, IDC_UI_ACTIVEX, m_bActiveX);
	//}}AFX_DATA_MAP
}

// This is called whenever the user presses Next, Back, or Finish with this step
//  present.  Do all validation & data exchange from the dialog in this function.
BOOL CCustom1Dlg::OnDismiss()
{
	if (!UpdateData(TRUE))
		return FALSE;

	std::WinRegWriteKey key(HKEY_CURRENT_USER, WINX_APPWIZ_KEY);

	const LPCTSTR ViewTypes[] = {
		_T("Window"),
		_T("ScrollWindow"),
		_T("HTMLPage"),
		_T("RichEdit"),
		_T("ListCtrl"),
		_T("TreeCtrl"),
	};

	const LPCTSTR AppTypes[] = {
		_T("DialogApp"),
		_T("SDIApp"),
		_T("MDIApp"),
		_T("ActiveXDll"),
	};

#define _winx_putBoolData(szKey, nVal) \
	key.putInt(szKey, nVal); \
	_winx_setBool(szKey, nVal)

#define _winx_putEnumData(szKey, nVal, coll) \
	key.putInt(szKey, nVal); \
	if (0); else for (int i = 0; i < countof(coll); ++i) { \
		CString pszKey = coll[i]; \
		if (i == nVal) \
			m_Dictionary[pszKey] = _T("1"); \
		else \
			m_Dictionary.RemoveKey(pszKey); \
	}

	_winx_putBoolData(_T("bMenuBar"), m_bMenuBar);
	_winx_putBoolData(_T("bRebar"), m_bRebar);
	_winx_putBoolData(_T("bCommandBar"), m_bCommandBar);
	_winx_putBoolData(_T("bStatusBar"), m_bStatusBar);
	_winx_putBoolData(_T("bToolbar"), m_bToolbar);
	_winx_putBoolData(_T("bDDX"), m_bDDX);
	_winx_putBoolData(_T("bAccel"), m_bAccel);
	_winx_putBoolData(_T("bActiveX"), m_bActiveX);
	_winx_putEnumData(_T("nViewType"), m_nViewType, ViewTypes);
	_winx_putEnumData(_T("nAppType"), m_nAppType, AppTypes);

	m_Dictionary[_T("ViewType")] = ViewTypes[m_nViewType];

	if (m_nAppType == 0) // DialogApp
	{
		m_Dictionary.RemoveKey(ViewTypes[m_nViewType]);
	}
	return TRUE;	// return FALSE if the dialog shouldn't be dismissed
}

BEGIN_MESSAGE_MAP(CCustom1Dlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CCustom1Dlg)
	ON_BN_CLICKED(IDC_ADVANCE, OnAdvance)
	ON_BN_CLICKED(IDC_DIALOG_APP, OnAppTypeChanged)
	ON_BN_DOUBLECLICKED(IDC_DIALOG_APP, OnAppTypeChanged)
	ON_BN_CLICKED(IDC_SDI_APP, OnAppTypeChanged)
	ON_BN_DOUBLECLICKED(IDC_SDI_APP, OnAppTypeChanged)
	ON_BN_CLICKED(IDC_MDI_APP, OnAppTypeChanged)
	ON_BN_DOUBLECLICKED(IDC_MDI_APP, OnAppTypeChanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CCustom1Dlg::OnAdvance() 
{
	CAdvanceOptionsDlg dlg(m_Dictionary);
	dlg.DoModal(m_hWnd);
}

/////////////////////////////////////////////////////////////////////////////

void CCustom1Dlg::OnAppTypeChanged()
{
	UpdateData(TRUE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_VIEWTYPE), m_nAppType != 0);
}

BOOL CCustom1Dlg::OnInitDialog() 
{
	CAppWizStepDlg::OnInitDialog();
	OnAppTypeChanged();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
