#if !defined(AFX_WINXWIZ60AW_H__C380E50C_9015_47CF_BB40_C954A0005B57__INCLUDED_)
#define AFX_WINXWIZ60AW_H__C380E50C_9015_47CF_BB40_C954A0005B57__INCLUDED_

// winxwiz60aw.h : header file
//

#define WINX_APPWIZ_KEY		_T("Software\\winx\\WinxWiz60")

class CDialogChooser;

// All function calls made by mfcapwz.dll to this custom AppWizard (except for
//  GetCustomAppWizClass-- see winxwiz60.cpp) are through this class.  You may
//  choose to override more of the CCustomAppWiz virtual functions here to
//  further specialize the behavior of this custom AppWizard.
class CWinxwiz60AppWiz : public CCustomAppWiz
{
public:
	virtual CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
	virtual CAppWizStepDlg* Back(CAppWizStepDlg* pDlg);
		
	virtual void InitCustomAppWiz();
	virtual void ExitCustomAppWiz();
	virtual void CustomizeProject(IBuildProject* pProject);
	virtual void ProcessTemplate(LPCTSTR lpszInput, DWORD dwSize, OutputStream* pOutput);

	BOOL IsUnicode() const {
		CString strVal;
		return m_Dictionary.Lookup(_T("bUnicode"), strVal);
	}

protected:
	CDialogChooser* m_pChooser;
	int m_nLevel;
};

// This declares the one instance of the CWinxwiz60AppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global Winxwiz60aw.  (Its definition is in winxwiz60aw.cpp.)
extern CWinxwiz60AppWiz Winxwiz60aw;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINXWIZ60AW_H__C380E50C_9015_47CF_BB40_C954A0005B57__INCLUDED_)
