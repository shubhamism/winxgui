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
	//}}AFX_DATA_INIT

	std::WinRegReadKey key(HKEY_CURRENT_USER, WINX_APPWIZ_KEY);
	if (key.good())
	{
		key.getInt(_T("bMenuBar"), m_bMenuBar);
		key.getInt(_T("bRebar"), m_bRebar);
		key.getInt(_T("bCommandBar"), m_bCommandBar);
		key.getInt(_T("bStatusBar"), m_bStatusBar);
		key.getInt(_T("bToolbar"), m_bToolbar);
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
	DDX_Radio(pDX, IDC_DIALOG_APP, m_nAppType);
	DDX_CBIndex(pDX, IDC_VIEWTYPE, m_nViewType);
	//}}AFX_DATA_MAP
}

// This is called whenever the user presses Next, Back, or Finish with this step
//  present.  Do all validation & data exchange from the dialog in this function.
BOOL CCustom1Dlg::OnDismiss()
{
	if (!UpdateData(TRUE))
		return FALSE;

	TCHAR szVal[2] = { 0, 0 };
	std::WinRegWriteKey key(HKEY_CURRENT_USER, WINX_APPWIZ_KEY);

	_winx_putData(_T("bMenuBar"), m_bMenuBar);
	_winx_putData(_T("bRebar"), m_bRebar);
	_winx_putData(_T("bCommandBar"), m_bCommandBar);
	_winx_putData(_T("bStatusBar"), m_bStatusBar);
	_winx_putData(_T("bToolbar"), m_bToolbar);
	_winx_putData(_T("nViewType"), m_nViewType);
	_winx_putData(_T("nAppType"), m_nAppType);

	return TRUE;	// return FALSE if the dialog shouldn't be dismissed
}

BEGIN_MESSAGE_MAP(CCustom1Dlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CCustom1Dlg)
	ON_BN_CLICKED(IDC_ADVANCE, OnAdvance)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CCustom1Dlg::OnAdvance() 
{
	CAdvanceOptionsDlg dlg(m_Dictionary);
	dlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
