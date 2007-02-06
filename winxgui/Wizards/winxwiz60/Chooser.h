#if !defined(AFX_CHOOSER_H__0B0F2629_2AD8_4881_9D79_4CE64F9B0B09__INCLUDED_)
#define AFX_CHOOSER_H__0B0F2629_2AD8_4881_9D79_4CE64F9B0B09__INCLUDED_

// chooser.h : declaration of the CDialogChooser class
//             This class keeps track of what dialogs to pop up when.

#define LAST_DLG 1

class CDialogChooser
{
public:
	CDialogChooser();
	~CDialogChooser();

	// All calls by mfcapwz.dll to CWinxwiz60AppWiz::Next
	//  & CWinxwiz60AppWiz::Back are delegated to these member
	//  functions, which keep track of what dialog is up
	//  now, and what to pop up next.
	CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
	CAppWizStepDlg* Back(CAppWizStepDlg* pDlg);

protected:
	// Current step's index into the internal array m_pDlgs
	int m_nCurrDlg;

	// Internal array of pointers to the steps
	CAppWizStepDlg* m_pDlgs[LAST_DLG + 1];
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSER_H__0B0F2629_2AD8_4881_9D79_4CE64F9B0B09__INCLUDED_)
