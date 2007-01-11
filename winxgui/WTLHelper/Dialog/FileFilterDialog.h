#pragma once
#include <atldlgs.h>
#if !defined(_WTL_USE_CSTRING) && !defined(__ATLSTR_H__) && !defined(__AFXSTR_H__)
#include <atlmisc.h>
#endif
class CFileFilterDialog :
	public CFileDialog
{
	CString m_Filters;
public:
	CFileFilterDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		HWND hWndParent = NULL);
	~CFileFilterDialog(void);

	void AddFilter(LPCTSTR FilterName, LPCTSTR FilterMask);
	void SetDefaultFilter(DWORD dwFilter);
};
