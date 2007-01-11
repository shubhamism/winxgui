#include "StdAfx.h"
#include ".\filefilterdialog.h"

CFileFilterDialog::CFileFilterDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
									 LPCTSTR lpszDefExt /* = NULL */,
									 LPCTSTR lpszFileName /* = NULL */,
									 DWORD dwFlags /* = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT */,
									 LPCTSTR lpszFilter /* = NULL */,
									 HWND hWndParent /* = NULL */ ):
CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, hWndParent)
{
}

CFileFilterDialog::~CFileFilterDialog(void)
{
}

void CFileFilterDialog::AddFilter(LPCTSTR FilterName, LPCTSTR FilterMask)
{
	m_Filters += FilterName; m_Filters += _T('\0');
	m_Filters += FilterMask; m_Filters += _T('\0');
	m_ofn.lpstrFilter = m_Filters;
}

void CFileFilterDialog::SetDefaultFilter(DWORD dwFilter)
{
	m_ofn.nFilterIndex = dwFilter;
}