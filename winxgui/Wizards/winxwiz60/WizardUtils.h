/* -------------------------------------------------------------------------
// WINX: a C++ template GUI library - MOST SIMPLE BUT EFFECTIVE
// 
// This file is a part of the WINX Library.
// The use and distribution terms for this software are covered by the
// Common Public License 1.0 (http://opensource.org/licenses/cpl.php)
// which can be found in the file CPL.txt at this distribution. By using
// this software in any fashion, you are agreeing to be bound by the terms
// of this license. You must not remove this notice, or any other, from
// this software.
// 
// Module: WizardUtils.h
// Creator: xushiwei
// Email: xushiweizh@gmail.com
// Date: 2007-2-8 9:43:38
// 
// $Id: $
// -----------------------------------------------------------------------*/
#ifndef __WIZARDUTILS_H__
#define __WIZARDUTILS_H__

// -------------------------------------------------------------------------
// GetWinxParentPath, MakeRelPath

#include <shlwapi.h>
#include <atlbase.h>
#include <algorithm>
#pragma comment(lib, "shlwapi")

template <class StringT>
inline int GetWinxParentPath(StringT& strPrjPath)
{
	int nLast = strPrjPath.GetLength()-1;
	if (strPrjPath.GetAt(nLast) == '\\')
		strPrjPath.Delete(nLast);

	int nLevel = 0;
	int pos;
	while ((pos = strPrjPath.ReverseFind('\\')) != -1)
	{
		++nLevel;
		strPrjPath = strPrjPath.Left(pos);
		if (PathIsDirectory(strPrjPath + _T("\\winx\\include")))
			return nLevel;
	}
	return -1;
}

template <class CharT>
inline CharT* MakeRelPath(
	int nLevel, CharT* szRelPath, const CharT* szPathName)
{
	int nNameLen = std::char_traits<CharT>::length(szPathName);
	while (nLevel--) {
		*szRelPath++ = '.';
		*szRelPath++ = '.';
		*szRelPath++ = '\\';
	}
	return std::copy(szPathName, szPathName+nNameLen+1, szRelPath)-1;
}

template <class CharT>
inline CharT* MakeRelPath(
	int nLevel, CharT* szRelPath, const CharT* szPathName,
	const CharT* szPre, int cchPre)
{
	szRelPath = std::copy(szPre, szPre+cchPre, szRelPath);
	return MakeRelPath(nLevel, szRelPath, szPathName);
}

// -------------------------------------------------------------------------
// ConvertFormat

template <class Iterator, class String>
inline void ConvertFormat(Iterator first, Iterator last, String& dest)
{
	const typename String::value_type controls[] = { '$', '$' };
	dest.reserve(last - first + 16);

Retry:
	Iterator it = std::find(first, last, '$');
	if (it != last)
	{
		if (it[1] == '(')
		{
			Iterator it2 = std::match_csymbol(it+2, last);
			if (it2 != it+2 && it2 != last && *it2 == ')')
			{
				dest.insert(dest.end(), first, it);
				dest.insert(dest.end(), controls, controls+2);
				dest.insert(dest.end(), it+2, it2);
				dest.insert(dest.end(), controls, controls+2);
				first = it2+1;
				goto Retry;
			}
			it = it2;
		}
		else if (it[1] == '$')
		{
			dest.insert(dest.end(), first, it+1);
			first = it+2;
			goto Retry;
		}
	}
	dest.insert(dest.end(), first, it);
	if (it != last)
		goto Retry;
}

// -------------------------------------------------------------------------
// CAdvanceOptionsDlg

class CAdvanceOptionsDlg : 
	public winx::ModalDialog<CAdvanceOptionsDlg, IDD_ADVANCEOPT>,
	public winx::WinDataExchange<CAdvanceOptionsDlg>
{
	WINX_DDX_BEGIN()
		DDX_TEXT(IDC_FILE_HEADER, m_strFileHeader)
		DDX_CHECK(IDC_UNICODE_APP, m_fUnicode)
		DDX_CHECK(IDC_USE_WINSDK, m_fUseWinsdk)
		DDX_CHECK(IDC_USE_GDIPLUS, m_fGdiplus)
	WINX_DDX_END();
private:
	CMapStringToString& m_Dictionary;
	std::tstring m_strFileHeader;
	BOOL m_fUnicode, m_fUseWinsdk, m_fGdiplus, m_fXPTheme;

public:
	CAdvanceOptionsDlg(CMapStringToString& Dictionary)
		: m_Dictionary(Dictionary)
	{
		m_fUnicode = 0;
		m_fUseWinsdk = 1;
		m_fGdiplus = 0;
		m_fXPTheme = 0;
		m_strFileHeader = _T("\
// -------------------------------------------------------------------------\n\
// Module: $(FileName)\n\
// Creator: xushiwei\n\
// Email: xushiweizh@gmail.com\n\
// Date: $(Date)\n\
// Description: \n\
// -------------------------------------------------------------------------");
		std::WinRegReadKey key(HKEY_CURRENT_USER, WINX_APPWIZ_KEY);
		if (key.good())
		{
			key.getInt(_T("fUnicode"), m_fUnicode);
			key.getInt(_T("fUseWinsdk"), m_fUseWinsdk);
			key.getInt(_T("fGdiplus"), m_fGdiplus);
			key.getInt(_T("fXPTheme"), m_fXPTheme);
			key.getString(_T("FileHeader"), m_strFileHeader);
		}
	}

	void UpdateDictionary()
	{
		std::tstring str;
		ConvertFormat(m_strFileHeader.begin(), m_strFileHeader.end(), str);
		m_Dictionary[_T("FileHeader")] = CString(str.c_str(), str.size());

		COleVariant date = COleDateTime::GetCurrentTime();
		date.ChangeType(VT_BSTR);
		m_Dictionary[_T("Date")] = date.bstrVal;
	}

public:
	BOOL OnInitDialog(HWND hDlg, HWND hWndDefaultFocus)
	{
		std::replaceText(m_strFileHeader, std::tstring(_T("\n")), std::tstring(_T("\r\n")));
		DoDataExchange();
		return TRUE;
	}

	void OnOK(HWND hWnd)
	{
		DoDataExchange(TRUE);
		std::replaceText(m_strFileHeader, std::tstring(_T("\r\n")), std::tstring(_T("\n")));

		std::WinRegWriteKey key(HKEY_CURRENT_USER, WINX_APPWIZ_KEY);
		key.putString(_T("FileHeader"), m_strFileHeader);
		
#define _winx_putBoolData(szKey, nVal) \
	key.putInt(szKey, nVal); \
	if (nVal) \
		m_Dictionary[szKey] = _T("1"); \
	else \
		m_Dictionary.RemoveKey(szKey)

#define _winx_putEnumData(szKey, nVal, coll) \
	key.putInt(szKey, nVal); \
	if (0); else for (int i = 0; i < countof(coll); ++i) { \
		CString pszKey = coll[i]; \
		if (i == nVal) \
			m_Dictionary[pszKey] = _T("1"); \
		else \
			m_Dictionary.RemoveKey(pszKey); \
	}

		_winx_putBoolData(_T("fUnicode"), m_fUnicode);
		_winx_putBoolData(_T("fUseWinsdk"), m_fUseWinsdk);
		_winx_putBoolData(_T("fGdiplus"), m_fGdiplus);
		_winx_putBoolData(_T("fXPTheme"), m_fXPTheme);

		UpdateDictionary();

		CloseDialog(hWnd);
	}
};

// -------------------------------------------------------------------------
// $Log: $

#endif /* __WIZARDUTILS_H__ */
