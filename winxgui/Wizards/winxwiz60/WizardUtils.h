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
// DumpStringMap

inline void DumpStringMap(const CMapStringToString& aMap)
{
#ifdef _DEBUG
	aMap.Dump(afxDump);
#else
	CString key, value;
	for (POSITION pos = aMap.GetStartPosition(); pos; )
	{
		aMap.GetNextAssoc(pos, key, value);
		TRACE(_T("$(%s) = %s\n"), (LPCTSTR)key, (LPCTSTR)value);
	}
	TRACE(_T("\n"));
#endif
}

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
		DDX_CHECK(IDC_UNICODE_APP, m_bUnicode)
		DDX_CHECK(IDC_USE_WINSDK, m_bUseWinsdk)
		DDX_CHECK(IDC_USE_GDIPLUS, m_bGdiplus)
		DDX_CHECK(IDC_USE_XPTHEME, m_bXPTheme)
		DDX_CHECK(IDC_USE_MODELESS, m_bModeless)
		DDX_CHECK(IDC_USE_LOOKNFEEL, m_bLookNFeel)
		DDX_CHECK(IDC_WINX_IN_STDPATH, m_bWinxInStdPath)
	WINX_DDX_END();
private:
	CMapStringToString& m_Dictionary;
	std::tstring m_strFileHeader;
	BOOL m_bUnicode, m_bUseWinsdk, m_bGdiplus, m_bXPTheme, m_bLookNFeel;
	BOOL m_bModeless, m_bWinxInStdPath;

public:
	static BOOL IsWinxInStdPath() {
		BOOL bWinxInStdPath = 0;
		std::WinRegReadKey key(HKEY_CURRENT_USER, WINX_APPWIZ_KEY);
		key.getInt(_T("bWinxInStdPath"), bWinxInStdPath);
		return bWinxInStdPath;
	}

	static void SetWinxInStdPath(BOOL bWinxInStdPath = TRUE) {
		std::WinRegWriteKey key(HKEY_CURRENT_USER, WINX_APPWIZ_KEY);
		key.putInt(_T("bWinxInStdPath"), bWinxInStdPath);
	}

public:
	CAdvanceOptionsDlg(CMapStringToString& Dictionary)
		: m_Dictionary(Dictionary)
	{
		m_bUnicode = 0;
		m_bUseWinsdk = 1;
		m_bGdiplus = 0;
		m_bXPTheme = 0;
		m_bLookNFeel = 0;
		m_bWinxInStdPath = 0;
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
			key.getInt(_T("bUnicode"), m_bUnicode);
			key.getInt(_T("bUseWinsdk"), m_bUseWinsdk);
			key.getInt(_T("bGdiplus"), m_bGdiplus);
			key.getInt(_T("bXPTheme"), m_bXPTheme);
			key.getInt(_T("bLookNFeel"), m_bLookNFeel);
			key.getInt(_T("bModeless"), m_bModeless);
			key.getInt(_T("bWinxInStdPath"), m_bWinxInStdPath);
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

#define _winx_setBool(szKey, nVal) \
	if (nVal) \
		m_Dictionary[szKey] = _T("1"); \
	else \
		m_Dictionary.RemoveKey(szKey)

		_winx_setBool(_T("bUnicode"), m_bUnicode);
		_winx_setBool(_T("bUseWinsdk"), m_bUseWinsdk);
		_winx_setBool(_T("bGdiplus"), m_bGdiplus);
		_winx_setBool(_T("bXPTheme"), m_bXPTheme || m_bLookNFeel);
		_winx_setBool(_T("bModeless"), m_bModeless);
		_winx_setBool(_T("bLookNFeel"), m_bLookNFeel);
		_winx_setBool(_T("bWinxInStdPath"), m_bWinxInStdPath);
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
		key.putInt(_T("bUnicode"), m_bUnicode);
		key.putInt(_T("bUseWinsdk"), m_bUseWinsdk);
		key.putInt(_T("bGdiplus"), m_bGdiplus);
		key.putInt(_T("bXPTheme"), m_bXPTheme);
		key.putInt(_T("bModeless"), m_bModeless);
		key.putInt(_T("bLookNFeel"), m_bLookNFeel);
		key.putInt(_T("bWinxInStdPath"), m_bWinxInStdPath);

		UpdateDictionary();
		CloseDialog(hWnd);
	}
};

// -------------------------------------------------------------------------
// $Log: $

#endif /* __WIZARDUTILS_H__ */
