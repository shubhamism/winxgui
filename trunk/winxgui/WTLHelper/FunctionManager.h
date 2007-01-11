////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2005 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	FunctionManager.h
// Created:	14.07.2005 8:34
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

#pragma once

#include "VSElements.h"
#include "common.h"
#include "XMLSettingsArchive.h"

#define ID_MENU_PRE_TRANSLATE_MESSAGE	21000
#define ID_MENU_ON_IDLE					21001

struct FuncParam
{
	CString Name;
	CString Type;
	bool LoadParam(CXMLObject* pArchive)
	{
		Name = (LPCTSTR)pArchive->GetName();
		return pArchive->GetText(Type);
	}
};

struct SpecFunctionStruct
{
	CString FuncName;
	CString Type;
	CString Body;
	CString Comment;
	CString Parent;
	int Condition;//-1 for all (don't check conditions), 0 if all conditions are false
	CSmartAtlArray<FuncParam> Params;
	bool LoadFunction(CXMLObject* pArchive);
};

struct SpecFunctionParent
{
	CString ClassName;
	CSmartAtlArray<SpecFunctionStruct> SpecFunctions;
	CSmartAtlArray<int> Conditions;
	SpecFunctionParent& operator += (const SpecFunctionParent& prev)
	{
		SpecFunctions.Append(prev.SpecFunctions);
		Conditions.Append(prev.Conditions);
		return *this;
	}
};

class CFunctionManager : public CSettings<CFunctionManager>
{
	bool m_bAllowDlgIdle;

	VSClass* m_pClass;
	HWND m_hParentWnd;
	InsDelPoints* m_pModifications;
	CSmartAtlArray<SpecFunctionStruct> m_SelectedFunctions;
	CAtlArray<bool> m_ConditionResults;
	void FillConditionResults();
	void FillSpecFunctionArray();
	
protected:
	bool IsOnIdle(VSClass* pClass);
	bool IsPreTranslateMessage(VSClass* pClass);
	bool IsSpecFunction(VSClass* pClass, const SpecFunctionStruct& SpecFunc);
	VSFunction* AddOnIdle(CAtlArray<MessageStruct*>& InsertedHandlers);
	VSFunction* AddPreTransalateMessage(CAtlArray<MessageStruct*>& InsertedHandlers);
	VSFunction* AddSpecFunction(SpecFunctionStruct& SpecFunc);
	bool CheckSpecialCondition(int Condition);
	bool CheckPropPageHandlers(VSClass* pClass);
	static CAtlMap<CString, SpecFunctionParent > m_sSpecFunctions;
public:
	CFunctionManager(void);
	~CFunctionManager(void);

	void Init(IN HWND hParentWnd);
	void SetClass(IN VSClass* pClass, IN InsDelPoints* pModifications);

	VSFunction* AddFunction();
	bool DeleteFunction(VSFunction* pFunc);

	HMENU CreateSpecFunctionDropMenu();
	VSFunction* AddSpecFunction(int DropMenuCmd, CAtlArray<MessageStruct*>& InsertedHandlers);
	static bool LoadSpecFunctions(CXMLObject* pArchive, LPCTSTR lpName);
	static void DeleteSpecFunctions();

	BEGIN_SETTINGS_MAP()
		SETTINGS_VARIABLE_OPT_RO(m_bAllowDlgIdle)
	END_SETTINGS_MAP()
};
