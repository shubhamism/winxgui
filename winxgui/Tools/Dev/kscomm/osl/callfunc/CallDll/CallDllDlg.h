// CallDllDlg.h : header file
//

#if !defined(AFX_CALLDLLDLG_H__A7E35F7B_2D3D_11D3_9E71_006097A311DB__INCLUDED_)
#define AFX_CALLDLLDLG_H__A7E35F7B_2D3D_11D3_9E71_006097A311DB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "RuntimeDll.h"

/////////////////////////////////////////////////////////////////////////////
// CCallDllDlg dialog

class CCallDllDlg : public CDialog
{
// Construction
public:
	CCallDllDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCallDllDlg)
	enum { IDD = IDD_CALLDLL_DIALOG };
	CListBox	m_lstArgs;
	CListBox	m_lstTypes;
	CString	m_strDll;
	CString	m_strFunction;
	CString	m_strValue;
	CString	m_strReturned;
	CString	m_strTypeText;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCallDllDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void TidyUp();
	HICON m_hIcon;
	RT_DLL_ARG m_RetVal;
	CRuntimeDll m_Dll;

	// Generated message map functions
	//{{AFX_MSG(CCallDllDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAdd();
	virtual void OnCall();
	virtual void OnCancel();
	afx_msg void OnSelChangeArgs();
	afx_msg void OnSetType();
	afx_msg void OnLoad();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALLDLLDLG_H__A7E35F7B_2D3D_11D3_9E71_006097A311DB__INCLUDED_)
