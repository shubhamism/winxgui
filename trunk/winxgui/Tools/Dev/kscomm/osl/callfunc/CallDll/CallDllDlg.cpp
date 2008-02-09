// CallDllDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CallDll.h"
#include "CallDllDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCallDllDlg dialog

CCallDllDlg::CCallDllDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCallDllDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCallDllDlg)
	m_strDll = _T("testdll.dll");
	m_strFunction = _T("");
	m_strValue = _T("");
	m_strReturned = _T("");
	m_strTypeText = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_RetVal.eType = ARG_NONE;
	m_RetVal.lVal=0L;
}

void CCallDllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCallDllDlg)
	DDX_Control(pDX, IDC_ARGS, m_lstArgs);
	DDX_Control(pDX, IDC_TYPES, m_lstTypes);
	DDX_Text(pDX, IDC_DLL, m_strDll);
	DDX_Text(pDX, IDC_FUNCTION, m_strFunction);
	DDX_Text(pDX, IDC_VALUE, m_strValue);
	DDX_Text(pDX, IDC_RETURNED, m_strReturned);
	DDX_Text(pDX, IDC_TYPE_TXT, m_strTypeText);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCallDllDlg, CDialog)
	//{{AFX_MSG_MAP(CCallDllDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_LBN_SELCHANGE(IDC_ARGS, OnSelChangeArgs)
	ON_BN_CLICKED(IDC_SET_TYPE, OnSetType)
	ON_BN_CLICKED(IDC_CLEAR, TidyUp)
	ON_BN_CLICKED(IDC_CALL, OnCall)
	ON_BN_CLICKED(IDC_LOAD, OnLoad)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCallDllDlg message handlers

BOOL CCallDllDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_lstTypes.AddString("unsigned char");
	m_lstTypes.AddString("signed char");
	m_lstTypes.AddString("unsigned short");
	m_lstTypes.AddString("signed short");
	m_lstTypes.AddString("unsigned long");
	m_lstTypes.AddString("signed long");
	m_lstTypes.AddString("float");
	m_lstTypes.AddString("unsigned char*");
	m_lstTypes.AddString("signed char*");
	m_lstTypes.AddString("unsigned short*");
	m_lstTypes.AddString("signed short*");
	m_lstTypes.AddString("unsigned long*");
	m_lstTypes.AddString("signed long*");
	m_lstTypes.AddString("float*");
	m_lstTypes.SetCurSel(0);
	
	GetDlgItem(IDC_CALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_SET_TYPE)->EnableWindow(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCallDllDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCallDllDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCallDllDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCallDllDlg::OnAdd() 
{
	CString str;
	RT_DLL_ARG* pArgs = new RT_DLL_ARG;
	DWORD dwIndex;
	
	UpdateData();
	
	pArgs->eType = (ARGTYPE)m_lstTypes.GetCurSel();
	switch(pArgs->eType)
	{
	// integers
	case ARG_UI1:
	case ARG_I1:
		if (3 == m_strValue.GetLength() && 
			'\'' == m_strValue[0] &&
			'\'' == m_strValue[2])
		{
			pArgs->cVal = m_strValue[1];
			break;
		}
	case ARG_UI2:
	case ARG_I2:
	case ARG_UI4:
	case ARG_I4:
		pArgs->lVal = atol((LPCSTR)m_strValue);
	break;
	// reals
	case ARG_R4: 
		pArgs->fltVal = (float)atof((LPCSTR)m_strValue);
	break;
	// pointers, we allocate memory in this way so when we free it
	// we do not need to know the type
	case ARG_PUI1:
	case ARG_PI1:
		pArgs->pcVal = new char[m_strValue.GetLength()+1];
		strcpy((char*)pArgs->pcVal, (LPCSTR)m_strValue);
	break;
	// integer pointers
	case ARG_PUI2:
	case ARG_PI2:
	case ARG_PUI4:
	case ARG_PI4:
		pArgs->pcVal = new char[sizeof(long)];
		*pArgs->plVal = atol((LPCSTR)m_strValue);
	break;
	// real pointers
	case ARG_PR4:
		pArgs->pcVal = new char[sizeof(float)];
		*pArgs->pfltVal = (float)atof((LPCSTR)m_strValue);
	break;

	default:
		TRACE("Bad voodo #1: should not be here\n");
		ASSERT(FALSE);
		delete pArgs;
	}
	
	m_lstTypes.GetText(pArgs->eType, str);
	dwIndex = m_lstArgs.AddString(str);
	m_lstArgs.SetItemData(dwIndex, (DWORD)pArgs);
}

void CCallDllDlg::OnCall() 
{
	UpdateData();
	RT_DLL_ARG* pArgs = NULL;
	DWORD dwArgs;

	if (m_strDll.IsEmpty() || m_strFunction.IsEmpty())
	{
		AfxMessageBox("DLL filename & function required");
		return;
	}
	
	GetDlgItem(IDC_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_CALL)->EnableWindow(FALSE);
	
	dwArgs = m_lstArgs.GetCount();
	if(dwArgs)
	{
		pArgs = new RT_DLL_ARG[dwArgs];
		for (DWORD i=0; i<dwArgs; i++)
		{
			pArgs[i] = *(RT_DLL_ARG*)m_lstArgs.GetItemData(i);
			// no need to copy the data in the case of strings, the pointer will do
		}
	}
	
	try
	{
		m_Dll.Call((LPCSTR)m_strFunction, pArgs, (short)dwArgs, &m_RetVal);
	}
	catch(CRuntimeDllException ex)
	{
		AfxMessageBox(ex.m_strError);
	}
}

void CCallDllDlg::OnCancel() 
{
	TidyUp();	
	CDialog::OnCancel();
}

void CCallDllDlg::OnSelChangeArgs() 
{
	DWORD dwIndex = m_lstArgs.GetCurSel();
	if(dwIndex != -1)
	{
		RT_DLL_ARG* pArgs = (RT_DLL_ARG*)m_lstArgs.GetItemData(dwIndex);
		char szValue[255];// a bad, hack I know
		if (pArgs)
		{
			switch(pArgs->eType)
			{
			// integers
			case ARG_UI1:
			case ARG_I1:
			case ARG_UI2:
			case ARG_I2:
			case ARG_UI4:
			case ARG_I4:
				ltoa(pArgs->lVal, szValue, 10);
			break;
			// reals
			case ARG_R4: 
				sprintf(szValue, "%f", pArgs->fltVal);
			break;
			case ARG_PUI1:
			case ARG_PI1:
				strncpy(szValue, (LPCTSTR)pArgs->pcVal,254);
			break;

			// integer pointers
			case ARG_PUI2:
			case ARG_PI2:
			case ARG_PUI4:
			case ARG_PI4:
				ltoa(*pArgs->plVal, szValue, 10);
			break;
			// real pointers
			case ARG_PR4:
				sprintf(szValue, "%f", *pArgs->pfltVal);
			break;

			default:
				TRACE("Bad voodo #2: should not be here\n");
				ASSERT(FALSE);
			}

			m_strValue = szValue;
			UpdateData(FALSE);
		}
	}
}

void CCallDllDlg::OnSetType() 
{
	UpdateData();
	m_RetVal.eType = (ARGTYPE)m_lstTypes.GetCurSel();
	
	m_lstTypes.GetText(m_RetVal.eType, m_strTypeText);

	switch(m_RetVal.eType)
	{
	case ARG_UI1:
	case ARG_I1:
		m_strReturned.Format("%c [0x%0x]",m_RetVal.cVal,m_RetVal.cVal);
		break;
	case ARG_I2:
	case ARG_UI2:
		m_strReturned.Format("%d",m_RetVal.sVal);
		break;
	case ARG_I4:
	case ARG_UI4:
		m_strReturned.Format("%d",m_RetVal.lVal);
		break;
	case ARG_R4:
		m_strReturned.Format("%f",m_RetVal.fltVal);
		break;
	// pointers
	case ARG_PUI1:
	case ARG_PI1:
		m_strReturned.Format("%s",(LPCSTR)m_RetVal.pcVal);
		break;
	case ARG_PI2:
	case ARG_PUI2:
		m_strReturned.Format("%d",*m_RetVal.psVal);
		break;
	case ARG_PI4:
	case ARG_PUI4:
		m_strReturned.Format("%d",*m_RetVal.plVal);
		break;
	case ARG_PR4:
		m_strReturned.Format("%f",*m_RetVal.pfltVal);
		break;
	default:
		TRACE("Bad voodo #3: should not be here\n");
		ASSERT(FALSE);
	}

	UpdateData(FALSE);
}

void CCallDllDlg::TidyUp()
{
	DWORD i,dwArgs = m_lstArgs.GetCount();
	RT_DLL_ARG* pArgs;

	GetDlgItem(IDC_ADD)->EnableWindow();
	GetDlgItem(IDC_CALL)->EnableWindow();

	for(i=0;i<dwArgs;i++)
	{
		pArgs = (RT_DLL_ARG*)m_lstArgs.GetItemData(i);
		if ((long)pArgs->eType >= (long)ARG_PUI1)// i.e. a pointer
			delete[] pArgs->pcVal;
		delete pArgs;
	}
	// empty the list box
	m_lstArgs.ResetContent();
	m_strValue.Empty();
	UpdateData(FALSE);
}

void CCallDllDlg::OnLoad() 
{
	UpdateData();
	if (m_strDll.IsEmpty())
		AfxMessageBox("Enter a Valid Dll or exe name");
	else
	{
		bool b = m_Dll.IsLoaded();
		if (!b)
			b = m_Dll.Load(m_strDll);
		else
		{
			m_Dll.Unload();
			b = false;
		}
		GetDlgItem(IDC_CALL)->EnableWindow(b);
		GetDlgItem(IDC_ADD)->EnableWindow(b);
		GetDlgItem(IDC_SET_TYPE)->EnableWindow(b);
		if (b)
			SetDlgItemText(IDC_LOAD,"Unload");
		else
			SetDlgItemText(IDC_LOAD,"Load");
	}
}
