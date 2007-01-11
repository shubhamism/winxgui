////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	DDXVariable.cpp
// Created:	16.11.2004 8:55
// 
//   Using this software in commercial applications requires an author
// permission. The permission will be granted to everyone excluding the cases
// when someone simply tries to resell the code.
//   This file may be redistributed by any means PROVIDING it is not sold for
// profit without the authors written consent, and providing that this notice
// and the authors name is included.
//   This file is provided "as is" with no expressed or implied warranty. The
// author accepts no liability if it causes any damage to you or your computer
// whatsoever.
//
////////////////////////////////////////////////////////////////////////////////

// DDXVariable.cpp : Implementation of CDDXVariable

#include "stdafx.h"
#include "DDXVariable.h"
#include "../TextFile.h"
#include "../common.h"
#include "../RegArchive.h"

extern LPCTSTR RegPath;
LPCTSTR DDXRegName = _T("DDX");

CAtlArray<DDXMemberTypes> CDDXVariable::m_MemberTypes;
CAtlArray<DDXContols> CDDXVariable::m_ControlClasses;

CDDXVariable::CDDXVariable(): m_iPrevAddCount(0), m_iCurControl(0), m_iAddCount(0),
m_Protection(0), m_bUseTypePrefix(true)
{
}

bool CDDXVariable::LoadSettings()
{
	CRegArchive RegArchive;
	if (RegArchive.Open(HKEY_CURRENT_USER, RegPath))
	{
		CSettings<CDDXVariable>::LoadSettings(RegArchive, DDXRegName);
		RegArchive.Close();
	}
	return true;
}

void CDDXVariable::UpdateDDXTypes()
{
	m_ComboDDXType.ResetContent();
	CString CurType;
	if (m_iCurControl == -1)
	{
		m_ComboMemberType.ResetContent();
		m_ComboDDXType.AddString(_T("Text"));
	}
	else
	{
		CurType = m_Controls[m_iCurControl].m_Type;
		CurType.Trim(_T("\" \t\r\n"));
		if (CurType == _T("LTEXT") ||
			CurType == _T("RTEXT") ||
			CurType == _T("CTEXT") ||
			CurType == _T("EDITTEXT") ||
			CurType == _T("COMBOBOX"))
		{
			m_ComboDDXType.AddString(_T("Text"));
			m_ComboDDXType.AddString(_T("Int"));
			m_ComboDDXType.AddString(_T("UINT"));
			m_ComboDDXType.AddString(_T("Float"));
		}
		if (CurType == "Button")
		{
			CString BS = m_Controls[m_iCurControl].m_Create;
			if (BS.Find(_T("BS_AUTOCHECKBOX")) != -1 || BS.Find(_T("BS_CHECKBOX")) != -1 ||
				BS.Find(_T("BS_3STATE")) != -1 || BS.Find(_T("BS_AUTO3STATE")) != -1)
			{
				m_ComboDDXType.AddString(_T("Check"));
			}
			if (BS.Find(_T("BS_AUTORADIOBUTTON")) != -1 || BS.Find(_T("BS_RADIOBUTTON")) != -1)
			{
				m_ComboDDXType.AddString(_T("Radio"));
				m_ComboDDXType.AddString(_T("Check"));
			}
		}
	}
	//== DDX_CONTROL_HANDLE
	m_ComboDDXType.AddString(_T("Control handle"));
	//== DDX_CONTROL
	m_ComboDDXType.AddString(_T("Control"));

	if (CurType == _T("EDITTEXT") && m_Controls[m_iCurControl].m_Create.Find(_T("ES_NUMBER")) != -1)
	{
		m_ComboDDXType.SetCurSel(2);
		m_ComboDDXType.GetLBText(2, m_DDXType);
	}
	else
	{
		m_ComboDDXType.SetCurSel(0);
		m_ComboDDXType.GetLBText(0, m_DDXType);
	}
	
	UpdateMemberTypes();
}

void CDDXVariable::UpdateMemberTypes()
{
	CString DDXType = m_DDXType;
	m_ComboMemberType.ResetContent();
	int iNewAddCount = 0;
	CAtlArray<CString> AddStrings;
	AddStrings.SetCount(3);

	if (DDXType == _T("Control") || DDXType == _T("Control handle"))
	{
		if (m_iCurControl != -1)
		{
			CString ResType = m_Controls[m_iCurControl].m_Type;
			ResType.Trim(_T("\""));
			for (size_t i = 0; i < m_ControlClasses.GetCount(); i++)
			{
				if (m_ControlClasses[i].ControlName == ResType)
				{
					for (size_t j = 0; j < m_ControlClasses[i].Classes.GetCount(); j++)
					{
						CString Class = m_ControlClasses[i].Classes[j];
						m_ComboMemberType.AddString(Class);
					}
					break;
				}
			}
			m_ComboMemberType.SetCurSel(0);
			m_Initializer.Empty();
			DoDataExchange(TRUE, IDC_COMBO_DDX_TYPE);
			DoDataExchange(FALSE, IDC_EDIT_INITIALIZER);
		}
	}
	else
	{
		for (size_t i = 0; i < m_MemberTypes.GetCount(); i++)
		{
			if (m_MemberTypes.GetAt(i).DDXType == DDXType)
			{
				//нашли наш тип
				for (size_t j = 0; j < m_MemberTypes[i].MemberTypes.GetCount(); j++)
				{
					m_ComboMemberType.AddString(m_MemberTypes[i].MemberTypes[j].Type);					
				}
				if (m_MemberTypes[i].MemberTypes.GetCount())
				{
					m_MemberType = m_MemberTypes[i].MemberTypes[0].Type;
					m_Initializer = m_MemberTypes[i].MemberTypes[0].Initializer;
				}
				else
				{
					m_Initializer.Empty();
				}
				m_ComboMemberType.SetCurSel(0);
				DoDataExchange(FALSE, IDC_EDIT_INITIALIZER);
				break;
			}
		}
		if (DDXType == _T("Int") || DDXType == _T("UINT"))
		{
			iNewAddCount = 2;
			AddStrings[0] = _T("Min");
			AddStrings[1] = _T("Max");
		}
		if (DDXType == _T("Float"))
		{
			iNewAddCount = 3;
			AddStrings[0] = _T("Min");
			AddStrings[1] = _T("Max");
			AddStrings[2] = _T("Precision");
		}
		if (DDXType == _T("Text"))
		{
			iNewAddCount = 1;
			AddStrings[0] = _T("Length");
		}
	}
	CRect r, templrc;
	if (iNewAddCount > m_iPrevAddCount)
	{
		templrc.left = 7;
		templrc.right = 116;
		int j;
		for (j = m_iPrevAddCount; j < iNewAddCount; j++)
		{
			templrc.top = 137 + j*26;
			templrc.bottom = templrc.top + 8;
			r = templrc;
			MapDialogRect(r);
			CStatic s1;
			s1.Create(m_hWnd, r, AddStrings[j], WS_VISIBLE | WS_CHILD, 0, IDC_FIRST_STATIC + j);
			s1.SetFont(GetFont());
			s1.Detach();
			CEdit e1;
			templrc.top += 8;
			templrc.bottom = templrc.top + 12;
			r = templrc;
			MapDialogRect(r);
			e1.Create(m_hWnd, r, NULL, WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL, 
				WS_EX_CLIENTEDGE, IDC_FIRST_EDIT + j);
			e1.SetFont(GetFont());
			e1.Detach();
		}
		for (j = 0; j < m_iPrevAddCount; j++)
		{
			GetDlgItem(IDC_FIRST_STATIC + j).SetWindowText(AddStrings[j]);
			GetDlgItem(IDC_FIRST_EDIT + j).SetWindowText(NULL);
		}
	}
	if (iNewAddCount < m_iPrevAddCount)
	{
		int j;
		for (j = iNewAddCount; j < m_iPrevAddCount; j++)
		{
			GetDlgItem(IDC_FIRST_STATIC + j).DestroyWindow();
			GetDlgItem(IDC_FIRST_EDIT + j).DestroyWindow();
		}
		for (j = 0; j < iNewAddCount; j++)
		{
			GetDlgItem(IDC_FIRST_STATIC + j).SetWindowText(AddStrings[j]);
			GetDlgItem(IDC_FIRST_EDIT + j).SetWindowText(NULL);
		}
	}
	GetWindowRect(r);
	m_iPrevAddCount = iNewAddCount;
	templrc.left = 0;
	templrc.right = 182;
	templrc.top = 0;
	templrc.bottom = 111 + 26*(iNewAddCount) + 20 + 8;
	MapDialogRect(templrc);
	AdjustWindowRect(templrc, GetStyle(), FALSE);
	r.bottom = r.top + templrc.Height();
	MoveWindow(r);
}

CString CDDXVariable::SkipStdPrefix(CString ResID)
{
	if (!_tcsncmp(ResID, _T("IDC_"), 4))
	{
		ResID.Delete(0, 4);
	}
	else
	{
		if (!_tcsncmp(ResID, _T("ID_"), 3))
		{
			ResID.Delete(0, 3);
		}
	}
	static LPCTSTR StdPrefixes[] = {_T("BUTTON"), _T("EDIT"), _T("COMBO"), _T("CHECK"),
		_T("RADIO"), _T("STATIC"), _T("LIST"), _T("SCROLLBAR"), _T("SLIDER"), _T("HOTKEY"),
		_T("TREE"), _T("TAB"), _T("ANIMATE"), _T("RICHEDIT"), _T("DATETIMEPICKER"),
		_T("MONTHCALENDAR"), _T("IPADDRESS"), _T("COMBOBOXEX"), _T("CUSTOM")};
	int iUndercScore = ResID.Find(_T('_'));
	if (iUndercScore == -1)
		return ResID;

	CString Ctrl = ResID.Left(iUndercScore);
	for (size_t i = 0; i < sizeof(StdPrefixes) / sizeof(LPCTSTR); i++)
	{
		if (Ctrl == StdPrefixes[i])
		{
			if (iUndercScore != ResID.GetLength() - 1)
			{
				return ResID.Mid(iUndercScore + 1);
			}
		}
	}
	return ResID;
}

CString CDDXVariable::GetTypePrefix()
{
	if (m_bUseTypePrefix)
	{
		int iDDX = m_ComboDDXType.GetCurSel();
		CString DDXType;
		m_ComboDDXType.GetLBText(iDDX, DDXType);
		if (DDXType == _T("Control") || DDXType == _T("Control handle"))
			return CString(_T("wnd"));
		for (size_t i = 0; i < m_MemberTypes.GetCount(); i++)
		{
			if (m_MemberTypes[i].DDXType == DDXType)
			{
				int iType = m_ComboMemberType.GetCurSel();
				return m_MemberTypes[i].MemberTypes[iType].Prefix;
			}
		}
	}
	
	return CString();
}

void CDDXVariable::UpdateVarName(bool bSelectVarName /* = true */)
{
	CString ResID;
	CString OldPrefix;
	DoDataExchange(TRUE, IDC_EDIT_MEMBER);
	if (!m_MemberName.IsEmpty())
	{
		if (m_MemberName.Left(2) == _T("m_"))
		{
			if (!m_OldPrefix.IsEmpty())
			{
				if (m_MemberName.Mid(2, m_OldPrefix.GetLength()) == m_OldPrefix)
				{
					m_OldPrefix = GetTypePrefix();
					OldPrefix = _T("m_") + m_OldPrefix;
					ResID = CreateIDName(SkipStdPrefix(m_Controls.GetAt(m_iCurControl).m_ID));
				}
				else
				{
					m_OldPrefix.Empty();
					OldPrefix = _T("m_");
					ResID = m_MemberName.Mid(2);
				}
			}
			else
			{
				OldPrefix = _T("m_");
				ResID = m_MemberName.Mid(2);
			}
		}
		else
		{
			ResID = m_MemberName;
		}
	}
	else
	{
		m_OldPrefix = GetTypePrefix();
		OldPrefix = _T("m_") + m_OldPrefix;
		ResID = CreateIDName(SkipStdPrefix(m_Controls.GetAt(m_iCurControl).m_ID));
	}
	
	m_MemberName = OldPrefix + ResID;

	DoDataExchange(FALSE, IDC_EDIT_MEMBER);
	if (bSelectVarName)
	{
		int Start = 2;
		if (m_MemberName.Left(2) != _T("m_"))
			Start = 0;
		GetDlgItem(IDC_EDIT_MEMBER).SendMessage(EM_SETSEL, Start, m_MemberName.GetLength());
		GetDlgItem(IDC_EDIT_MEMBER).SetFocus();
	}
}

//////////////////////////////////////////////////////////////////////////

// CDDXVariable
LRESULT CDDXVariable::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	size_t i;
	CenterWindow();

	if (!LoadSettings())
	{
		MessageBox(_T("Cannot load settings!"), NULL, MB_ICONERROR);
		EndDialog(IDCANCEL);
		return 0;
	}

	m_ComboID.Attach(GetDlgItem(IDC_COMBO_ID));
	m_ComboDDXType.Attach(GetDlgItem(IDC_COMBO_DDX_TYPE));
	m_ComboMemberType.Attach(GetDlgItem(IDC_COMBO_MEMBER_TYPE));
	for (i = 0; i < m_Controls.GetCount(); i++)
	{
		m_ComboID.AddString(m_Controls.GetAt(i).m_ID);	
	}
	if (m_iCurControl != -1)
	{
		m_ComboID.SetCurSel(m_iCurControl);
	}
	
	DoDataExchange(FALSE, IDC_RADIO_PUBLIC);
	OnComboIdCbnSelchange(CBN_SELCHANGE, 0, NULL, bHandled);
	
	return 0;  
}

LRESULT CDDXVariable::OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	DoDataExchange(TRUE);
	m_iAddCount = m_iPrevAddCount;
	if (m_DDXType == _T("Text"))
	{
		GetDlgItem(IDC_FIRST_EDIT).GetWindowText(m_FirstEdit);
		m_FirstEdit.Trim();
		if (m_FirstEdit.IsEmpty())
		{
			m_iAddCount = 0;
		}
	}
	if (m_DDXType == _T("Int") || m_DDXType == _T("UINT"))
	{
		GetDlgItem(IDC_FIRST_EDIT).GetWindowText(m_FirstEdit);
		m_FirstEdit.Trim();
		GetDlgItem(IDC_SECOND_EDIT).GetWindowText(m_SecondEdit);
		m_SecondEdit.Trim();
		if ((m_FirstEdit.IsEmpty() && m_SecondEdit.IsEmpty()) ||
			(!m_FirstEdit.IsEmpty() && !m_SecondEdit.IsEmpty()))
		{
			if (m_FirstEdit.IsEmpty())
				m_iAddCount = 0;
		}
		else
		{
			MessageBox(_T("\"min\" and \"max\" must be either both not empty or both empty!"));
			return 0;
		}
	}
	if (m_DDXType == _T("Float"))
	{
		GetDlgItem(IDC_FIRST_EDIT).GetWindowText(m_FirstEdit);
		m_FirstEdit.Trim();
		GetDlgItem(IDC_SECOND_EDIT).GetWindowText(m_SecondEdit);
		m_SecondEdit.Trim();
		GetDlgItem(IDC_THIRD_EDIT).GetWindowText(m_ThirdEdit);
		m_ThirdEdit.Trim();
		if (m_ThirdEdit.IsEmpty())
			m_iAddCount--;
		if ((m_FirstEdit.IsEmpty() && m_SecondEdit.IsEmpty()) ||
			(!m_FirstEdit.IsEmpty() && !m_SecondEdit.IsEmpty()))
		{
			if (m_FirstEdit.IsEmpty())
				m_iAddCount -= 2;
		}
		else
		{
			MessageBox(_T("\"min\" and \"max\" must be either both not empty or both empty!"));
			return 0;
		}
	}
	EndDialog(wID);
	return 0;
}

LRESULT CDDXVariable::OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}

LRESULT CDDXVariable::OnComboDdxTypeCbnSelchange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int iCurSel = m_ComboDDXType.GetCurSel();
	if (iCurSel != -1)
	{
		m_ComboDDXType.GetLBText(iCurSel, m_DDXType);
		UpdateMemberTypes();
		UpdateVarName();
	}
	
	return 0;
}

LRESULT CDDXVariable::OnComboIdCbnSelchange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_iCurControl = m_ComboID.GetCurSel();
	if (m_iCurControl != -1)
	{
		UpdateDDXTypes();
		UpdateVarName();
	}
	return 0;
}

LRESULT CDDXVariable::OnComboIdCbnEditchange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CString ID;
	m_ComboID.GetWindowText(ID);
	int iCurControl = m_ComboID.FindStringExact(-1, ID);
	if (iCurControl != m_iCurControl)
		UpdateDDXTypes();

	m_ControlID = ID;
	UpdateVarName(false);
	return 0;
}

LRESULT CDDXVariable::OnComboMemberTypeCbnSelchange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	DoDataExchange(TRUE);
	int iSelType = m_ComboMemberType.GetCurSel();
	if (iSelType == -1)
		return 0;
	for (size_t i = 0; i < m_MemberTypes.GetCount(); i++)
	{
		if (m_MemberTypes.GetAt(i).DDXType == m_DDXType)
		{
			if (m_MemberTypes[i].MemberTypes.GetCount())
			{
				m_MemberType = m_MemberTypes[i].MemberTypes[iSelType].Type;
				m_Initializer = m_MemberTypes[i].MemberTypes[iSelType].Initializer;
			}
			else
			{
				m_Initializer.Empty();
				m_ComboMemberType.SetCurSel(0);
			}
			DoDataExchange(FALSE, IDC_EDIT_INITIALIZER);
			break;
		}
	}
	UpdateVarName();
	
	return 0;
}