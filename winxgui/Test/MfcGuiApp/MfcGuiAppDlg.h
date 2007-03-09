// MfcGuiAppDlg.h : header file
//

#pragma once


// CMfcGuiAppDlg dialog
class CMfcGuiAppDlg : public CDialog
{
// Construction
public:
	CMfcGuiAppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFCGUIAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
public:
	afx_msg void OnBnClickedOk();
public:
	afx_msg void OnBnClickedCancel();
};
