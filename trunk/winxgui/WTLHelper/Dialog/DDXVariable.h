////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	DDXVariable.h
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

// DDXVariable.h : Declaration of the CDDXVariable

#pragma once
#include "../resources/ResDialog.h"
#include "../resource.h"

// CDDXVariable
#define IDC_FIRST_STATIC	20001
#define IDC_SECOND_STATIC	20002
#define IDC_THIRD_STATIC	20003
#define IDC_FIRST_EDIT		21001
#define IDC_SECOND_EDIT		21002
#define IDC_THIRD_EDIT		21003

struct MemberTypeStruct : public CSettings<MemberTypeStruct>
{
	CString Type;
	CString Prefix;
	CString Initializer;
	BEGIN_SETTINGS_MAP()
		SETTINGS_VARIABLE(Type)
		SETTINGS_VARIABLE(Prefix)
		SETTINGS_DEFTEXT(Initializer)
	END_SETTINGS_MAP()
};

struct DDXMemberTypes : public CSettings<DDXMemberTypes>
{
	CString DDXType;
	CAtlArray<MemberTypeStruct> MemberTypes;
	DDXMemberTypes(){};
	DDXMemberTypes(const DDXMemberTypes& ddxmt)
	{
		DDXType = ddxmt.DDXType;
		MemberTypes.Copy(ddxmt.MemberTypes);
	}
	BEGIN_SETTINGS_MAP()
		SETTINGS_VARIABLE(DDXType)
		SETTINGS_OBJECT_RO(MemberTypes, CAtlArrayObjectSerializer<MemberTypeStruct>)
	END_SETTINGS_MAP()
};

struct DDXContols : public CSettings<DDXContols>
{
	CString ControlName;
	CAtlArray<CString> Classes;
	DDXContols(){};
	DDXContols(const DDXContols& ddxc)
	{
		ControlName = ddxc.ControlName;
		Classes.Copy(ddxc.Classes);
	}

	BEGIN_SETTINGS_MAP()
		SETTINGS_VARIABLE_RO(ControlName)
		SETTINGS_OBJECT_RO(Classes, CAtlArraySerializer<CString>)
	END_SETTINGS_MAP()
};

#define PROTECTION_PUBLIC		0
#define PROTECTION_PROTECTED	1
#define PROTECTION_PRIVATE		2

class CDDXVariable : 
	public CDialogImpl<CDDXVariable>,
	public CWinDataExchange<CDDXVariable>,
	public CSettings<CDDXVariable>
{
private:
	//count of edit & static which were created for input len, min, max, precision
	int m_iPrevAddCount;
	bool m_bUseTypePrefix;

	CComboBox m_ComboID;
	CComboBox m_ComboDDXType;
	CComboBox m_ComboMemberType;

	CString m_OldPrefix;
	bool LoadSettings();

	// Changes ID of control so set avalable DDX types
	void UpdateDDXTypes();
	// chnages DDX kind so set avalable type for member
	void UpdateMemberTypes();
	void UpdateVarName(bool bSelectVarName = true);
	CString SkipStdPrefix(CString ResID);
	CString GetTypePrefix();
public:
	CDDXVariable();
	~CDDXVariable(){};
	CAtlArray<ResControl> m_Controls;
	int m_iCurControl;

	CString m_ControlID;
	CString m_DDXType;
	CString m_MemberType;
	CString m_MemberName;
	CString m_Initializer;
	CString m_FirstEdit;
	CString m_SecondEdit;
	CString m_ThirdEdit;
	int m_iAddCount;
	int m_Protection;

	static CAtlArray<DDXMemberTypes> m_MemberTypes;
	static CAtlArray<DDXContols> m_ControlClasses;

	enum { IDD = IDD_DDXVARIABLE };

	BEGIN_MSG_MAP(CDDXVariable)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
		COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
		COMMAND_HANDLER(IDC_COMBO_DDX_TYPE, CBN_SELCHANGE, OnComboDdxTypeCbnSelchange)
		COMMAND_HANDLER(IDC_COMBO_ID, CBN_SELCHANGE, OnComboIdCbnSelchange);
		COMMAND_HANDLER(IDC_COMBO_ID, CBN_EDITCHANGE, OnComboIdCbnEditchange);
		COMMAND_HANDLER(IDC_COMBO_MEMBER_TYPE, CBN_SELCHANGE, OnComboMemberTypeCbnSelchange)
	END_MSG_MAP()
	
	BEGIN_DDX_MAP(CDDXVariable)
		DDX_TEXT(IDC_COMBO_ID, m_ControlID)
		DDX_TEXT(IDC_COMBO_DDX_TYPE, m_DDXType)
		DDX_TEXT(IDC_COMBO_MEMBER_TYPE, m_MemberType)
		DDX_TEXT(IDC_EDIT_MEMBER, m_MemberName)
		DDX_TEXT(IDC_EDIT_INITIALIZER, m_Initializer)
		DDX_RADIO(IDC_RADIO_PUBLIC, m_Protection)
	END_DDX_MAP()

	BEGIN_SETTINGS_MAP()
		SETTINGS_VARIABLE_OPT(m_bUseTypePrefix)
	END_SETTINGS_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnComboDdxTypeCbnSelchange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnComboIdCbnSelchange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnComboIdCbnEditchange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnComboMemberTypeCbnSelchange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};


