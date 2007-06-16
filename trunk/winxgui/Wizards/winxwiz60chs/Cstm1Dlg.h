#if !defined(AFX_CSTM1DLG_H__B79B3D6C_CBF7_416E_8E17_1574BF83354B__INCLUDED_)
#define AFX_CSTM1DLG_H__B79B3D6C_CBF7_416E_8E17_1574BF83354B__INCLUDED_

// cstm1dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustom1Dlg dialog

class CCustom1Dlg : public CAppWizStepDlg
{
private:
	CMapStringToString& m_Dictionary;

// Construction
public:
	CCustom1Dlg(CMapStringToString& Dictionary);
	virtual BOOL OnDismiss();

// Dialog Data
	//{{AFX_DATA(CCustom1Dlg)
	enum { IDD = IDD_CUSTOM1 };
	BOOL	m_bMenuBar;
	BOOL	m_bRebar;
	BOOL	m_bCommandBar;
	BOOL	m_bStatusBar;
	BOOL	m_bToolbar;
	int		m_nViewType;
	int		m_nAppType;
	BOOL	m_bAccel;
	BOOL	m_bDDX;
	BOOL	m_bActiveX;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustom1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCustom1Dlg)
	afx_msg void OnAdvance();
	afx_msg void OnAppTypeChanged();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSTM1DLG_H__B79B3D6C_CBF7_416E_8E17_1574BF83354B__INCLUDED_)
