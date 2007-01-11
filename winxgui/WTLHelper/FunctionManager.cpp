////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2005 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	FunctionManager.cpp
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

#include "StdAfx.h"
#include ".\functionmanager.h"
#include "dialog/AddMemberVar.h"
#include "MessageManager.h"
#include "dialog/AddSpecFuncDlg.h"

bool SpecFunctionStruct::LoadFunction(CXMLObject* pArchive)
{
	FuncName = (LPCTSTR)pArchive->GetName();
	if (!pArchive->GetAttribute(_T("Condition"), Condition))
		Condition = -1;
	if (!pArchive->LoadTag(_T("Type"), Type))
		return false;
	pArchive->LoadTag(_T("Body"), Body);
	pArchive->LoadTag(_T("Comment"), Comment);
	if (!Body.IsEmpty())
	{
		Body.Replace(_T("\n"), _T("\r\n"));
	}
	if (!Comment.IsEmpty())
	{
		Comment.Replace(_T("\n"), _T("\r\n"));
	}
	if (pArchive->StartObject(_T("Params"), false))
	{
		for (CXMLObject::CXMLIterator i = pArchive->GetFirstChild(); i; i++)
		{
			FuncParam Param;
			Param.LoadParam(&i);
			Params.Add(Param);
		}
		pArchive->EndObject();
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////

CAtlMap<CString, SpecFunctionParent > CFunctionManager::m_sSpecFunctions;

CFunctionManager::CFunctionManager(void) : m_pClass(NULL), m_pModifications(NULL), 
m_hParentWnd(NULL), m_bAllowDlgIdle(true)
{
}

CFunctionManager::~CFunctionManager(void)
{
}

bool CFunctionManager::CheckPropPageHandlers(VSClass* pClass)
{
	if (FindDefine(pClass, L"_WTL_NEW_PAGE_NOTIFY_HANDLERS", true) != NULL)
	{
		return true;
	}

	return false;
}

bool CFunctionManager::CheckSpecialCondition(int Condition)
{
	switch(Condition) 
	{
	case 1:
		return CheckPropPageHandlers(m_pClass);
		break;
	default:
		return false;
	}
	return false;
}

void CFunctionManager::FillSpecFunctionArray()
{
	m_SelectedFunctions.RemoveAll();
	for (size_t i = 0;i < m_pClass->Parents.GetCount(); i++)
	{
		SpecFunctionParent SpecParent;
		if (m_sSpecFunctions.Lookup(m_pClass->Parents[i]->Name, SpecParent))
		{
			CAtlMap<int, bool> ConditionResult;
			bool bDefault = true;
			for (size_t i = 0; i < SpecParent.Conditions.GetCount(); i++)
			{
				bool bRes = CheckSpecialCondition(SpecParent.Conditions[i]);
				bDefault &= !bRes;
				ConditionResult.SetAt(SpecParent.Conditions[i], bRes);
			}
			if (SpecParent.Conditions.GetCount())
			{
				ConditionResult.SetAt(0, bDefault);
			}
			CSmartAtlArray<SpecFunctionStruct>& SpecFunctions = SpecParent.SpecFunctions;
			for (size_t i = 0; i < SpecFunctions.GetCount(); i++)
			{
				if (SpecFunctions[i].Condition == -1)
				{
					m_SelectedFunctions.Add(SpecFunctions[i]);
				}
				else
				{
					bool bRes;
					if (ConditionResult.Lookup(SpecFunctions[i].Condition, bRes))
					{
						if (bRes)
						{
							m_SelectedFunctions.Add(SpecFunctions[i]);
						}
					}
				}
			}
		}
	}
}

bool CFunctionManager::IsOnIdle(VSClass* pClass)
{
	for (size_t i = 0; i < pClass->Functions.GetCount(); i++)
	{
		if (pClass->Functions[i]->Name == _T("OnIdle"))
		{
			if (!pClass->Functions[i]->Parameters.GetCount())
			{
				return true;
			}
		}
	}
	return false;
}

bool CFunctionManager::IsPreTranslateMessage(VSClass* pClass)
{
	for (size_t i = 0; i < pClass->Functions.GetCount(); i++)
	{
		if (pClass->Functions[i]->Name == _T("PreTranslateMessage"))
		{
			if (pClass->Functions[i]->Parameters.GetCount())
			{
				CString Type = pClass->Functions[i]->Parameters.GetAt(0)->Type;
				if (Type == _T("LPMSG") || Type == _T("MSG*") || Type == _T("MSG *"))
					return true;
			}
		}
	}
	return false;
}

bool CFunctionManager::IsSpecFunction(VSClass* pClass, const SpecFunctionStruct& SpecFunc)
{
	for (size_t i = 0; i < pClass->Functions.GetCount(); i++)
	{
		if (pClass->Functions[i]->Name == SpecFunc.FuncName)
		{
			if (pClass->Functions[i]->Parameters.GetCount() == SpecFunc.Params.GetCount())
			{
				//problem with type synonyms
				return true;
			}
		}
	}
	return false;
}

VSFunction* CFunctionManager::AddPreTransalateMessage(CAtlArray<MessageStruct*>& InsertedHandlers)
{
	CAddSpecFuncDlg dlg;
	dlg.m_Title = _T("Add PreTranslateMessage()");

	MessageStruct mes;
	mes.Type = STD_MESSAGE_HANDLER;
	CString CreateMessage;
	if (m_pClass->IsDialog() && !m_pClass->m_DialogID.IsEmpty())
	{
		dlg.m_bDialog = true;
		CreateMessage = _T("WM_INITDIALOG");
	}
	else
	{
		CreateMessage = _T("WM_CREATE");
	}

	mes.Message = CreateMessage;
	dlg.m_bCreate = dlg.m_bEnableCreate = !CMessageManager::m_sHandlerManager.IsHandlerExist(&mes);
	mes.Message = _T("WM_DESTROY");
	dlg.m_bDestroy = dlg.m_bEnableDestroy = !CMessageManager::m_sHandlerManager.IsHandlerExist(&mes);
	
	if (dlg.DoModal() == IDOK)
	{
		VSFunction* pFunc = new VSFunction;
		pFunc->pParent = m_pClass;
		pFunc->Name = _T("PreTranslateMessage");
		pFunc->Type = _T("BOOL");
		pFunc->Access = EnvDTE::vsCMAccessPublic;
		m_pClass->Functions.Add(pFunc);
		VSParameter* pParam = new VSParameter;
		pParam->Name = _T("pMsg");
		pParam->Type = _T("LPMSG");
		pParam->pParent = pFunc;
		pFunc->Parameters.Add(pParam);

		InsertSpecFunction* pInsPt = new InsertSpecFunction;
		pInsPt->pElement = pFunc;
		pInsPt->bInitDialog = dlg.m_bDialog;
		pInsPt->Body = _T("return FALSE;\r\n");
		if (dlg.m_bAddCreate)
			pInsPt->OnCreateBody = _T("_Module.GetMessageLoop()->AddMessageFilter(this);\r\n");
		if (dlg.m_bRemoveDestroy)
			pInsPt->OnDestroyBody = _T("_Module.GetMessageLoop()->RemoveMessageFilter(this);\r\n");
		pInsPt->pBase = NULL;

		VSBase* pBase = NULL;
		for (size_t i = 0; i < m_pClass->Parents.GetCount(); i++)
		{
			if (m_pClass->Parents[i]->Name == _T("CMessageFilter"))
			{
				pBase = m_pClass->Parents[i];
				break;
			}
		}
		if (!pBase)
		{
			VSBase* pBase = new VSBase;
			pBase->Name = _T("CMessageFilter");
			pInsPt->pBase = pBase;
			m_pClass->Parents.Add(pBase);
		}

		if (dlg.m_bCreate)
		{
			//no WM_CREATE handler, need to add
			MessageStruct* pMesStruct = NULL;
			pMesStruct = CMessageManager::m_sHandlerManager.FindMessageStruct(CreateMessage);
			ATLASSERT(pMesStruct);
			InsertedHandlers.Add(pMesStruct);
		}
		if (dlg.m_bDestroy)
		{
			MessageStruct* pMesStruct = CMessageManager::m_sHandlerManager.FindMessageStruct(CString(_T("WM_DESTROY")));
			ATLASSERT(pMesStruct);
			InsertedHandlers.Add(pMesStruct);
		}
		m_pModifications->InsertPoints.Add(pInsPt);
		return pFunc;
	}
	return NULL;
}

VSFunction* CFunctionManager::AddOnIdle(CAtlArray<MessageStruct*>& InsertedHandlers)
{
	CAddSpecFuncDlg dlg;
	dlg.m_Title = _T("Add OnIdle()");
	MessageStruct mes;
	CString CreateMessage;
	mes.Type = STD_MESSAGE_HANDLER;
	if (m_pClass->IsDialog() && !m_pClass->m_DialogID.IsEmpty())
	{
		dlg.m_bDialog = true;
		CreateMessage = _T("WM_INITDIALOG");
	}
	else
	{
		CreateMessage = _T("WM_CREATE");
	}
	mes.Message = CreateMessage;
	dlg.m_bCreate = dlg.m_bEnableCreate = !CMessageManager::m_sHandlerManager.IsHandlerExist(&mes);
	mes.Message = _T("WM_DESTROY");
	dlg.m_bDestroy = dlg.m_bEnableDestroy = !CMessageManager::m_sHandlerManager.IsHandlerExist(&mes);
	if (dlg.DoModal() == IDOK)
	{
		VSFunction* pFunc = new VSFunction;
		pFunc->pParent = m_pClass;
		pFunc->Name = _T("OnIdle");
		pFunc->Type = _T("BOOL");
		pFunc->Access = EnvDTE::vsCMAccessPublic;
		m_pClass->Functions.Add(pFunc);

		InsertSpecFunction* pInsPt = new InsertSpecFunction;
		pInsPt->pElement = pFunc;
		pInsPt->bInitDialog = dlg.m_bDialog;
		pInsPt->Body = _T("return FALSE;\r\n");
		if (dlg.m_bAddCreate)
			pInsPt->OnCreateBody = _T("_Module.GetMessageLoop()->AddIdleHandler(this);\r\n");
		if (dlg.m_bRemoveDestroy)
			pInsPt->OnDestroyBody = _T("_Module.GetMessageLoop()->RemoveIdleHandler(this);\r\n");
		pInsPt->pBase = NULL;

		VSBase* pBase = NULL;
		for (size_t i = 0; i < m_pClass->Parents.GetCount(); i++)
		{
			if (m_pClass->Parents[i]->Name == _T("CIdleHandler"))
			{
				pBase = m_pClass->Parents[i];
				break;
			}
		}
		if (!pBase)
		{
			VSBase* pBase = new VSBase;
			pBase->Name = _T("CIdleHandler");
			pInsPt->pBase = pBase;
			m_pClass->Parents.Add(pBase);
		}

		if (dlg.m_bCreate)
		{
			//no WM_CREATE handler, need to add
			MessageStruct* pMesStruct = CMessageManager::m_sHandlerManager.FindMessageStruct(CreateMessage);
			ATLASSERT(pMesStruct);
			InsertedHandlers.Add(pMesStruct);
		}
		if (dlg.m_bDestroy)
		{
			MessageStruct* pMesStruct = CMessageManager::m_sHandlerManager.FindMessageStruct(CString(_T("WM_DESTROY")));
			ATLASSERT(pMesStruct);
			InsertedHandlers.Add(pMesStruct);
		}
		m_pModifications->InsertPoints.Add(pInsPt);
		return pFunc;
	}
	return NULL;
}

VSFunction* CFunctionManager::AddSpecFunction(SpecFunctionStruct& SpecFunc)
{
	VSFunction* pFunc = new VSFunction;
	pFunc->pParent = m_pClass;
	pFunc->Name = SpecFunc.FuncName;
	pFunc->Type = SpecFunc.Type;
	m_pClass->Functions.Add(pFunc);
	for (size_t i = 0; i < SpecFunc.Params.GetCount(); i++)
	{
		VSParameter* pParam = new VSParameter;
		pParam->pParent = pFunc;
		pParam->Name = SpecFunc.Params[i].Name;
		pParam->Type = SpecFunc.Params[i].Type;
		pFunc->Parameters.Add(pParam);
	}
	InsertPointFunc* pInsPt = new InsertPointFunc;
	pInsPt->pElement = pFunc;
	
	if (!SpecFunc.Comment.IsEmpty())
	{
		pInsPt->Body = SpecFunc.Comment + _T("\r\n");
	}
	pInsPt->Body += _T("\r\n");
	if (!SpecFunc.Body.IsEmpty())
	{
		pInsPt->Body += SpecFunc.Body + _T("\r\n");
	}
	m_pModifications->InsertPoints.Add(pInsPt);
	
	return pFunc;
}
//////////////////////////////////////////////////////////////////////////

void CFunctionManager::Init(IN HWND hParentWnd)
{
	m_hParentWnd = hParentWnd;
}

void CFunctionManager::SetClass(IN VSClass* pClass, IN InsDelPoints* pModifications)
{
	m_pClass = pClass;
	m_pModifications = pModifications;
}

VSFunction* CFunctionManager::AddFunction()
{
	CAddMemberVar dlg;
	dlg.SetForFunction();
	if (dlg.DoModal() == IDOK)
	{
		VSFunction* pFunc = new VSFunction;
		pFunc->Type = dlg.m_Type;
		int n1 = dlg.m_Body.Find(_T('('));
		if (n1 == -1)
		{
			MessageBox(m_hParentWnd, _T("It's not a function"), NULL, MB_ICONWARNING);
			return 0;
		}
		pFunc->Name = dlg.m_Body.Left(n1);
		pFunc->Name.Trim();
		if (dlg.m_bPublic)
		{
			pFunc->Access = EnvDTE::vsCMAccessPublic;
		}
		else
		{
			if (dlg.m_bProtected)
			{
				pFunc->Access = EnvDTE::vsCMAccessProtected;
			}
			else
			{
				pFunc->Access = EnvDTE::vsCMAccessPrivate;
			}
		}

		CString Params = dlg.m_Body.Mid(n1+1, dlg.m_Body.GetLength() - n1 - 2);
		int StartPos = 0;
		VSParameter* pParam;
		Params.Trim();
		if (!Params.IsEmpty())
		{
			while(StartPos >=0)
			{
				// HACK: определение параметров не совсем правильное
				//может быть ситуация int a b, int c
				CString Param1;
				int n2 = Params.Find(_T(','), StartPos);
				if (n2 != -1)
				{
					Param1 = Params.Mid(StartPos, n2 - StartPos);
					StartPos = n2+1;
				}
				else
				{
					Param1 = Params.Mid(StartPos);
					StartPos = -1;
				}
				Param1.Trim();
				int n3 = -1;
				int i = Param1.GetLength()-1;
				CString Delim = _T(" \t\r\n");

				//находим первый разделитель с конца
				while(i >= 0)
				{
					if (Delim.Find(Param1[i]) != -1)
					{
						n3 = i;
						break;
					}
					i--;
				}

				if (n3 == -1)
				{
					MessageBox(m_hParentWnd, _T("Wrong parameter list"), NULL, MB_ICONWARNING);
					return 0;
				}

				pParam = new VSParameter;
				pParam->Name  = Param1.Mid(n3+1);
				pParam->Name.Trim();
				pParam->Type = Param1.Left(n3);
				pParam->Type.Trim();
				pFunc->Parameters.Add(pParam);

			};
		}
		//нужно добавить теперь функцию
		InsertPointFunc* pInsFunc = new InsertPointFunc;
		m_pClass->Functions.Add(pFunc);
		pInsFunc->pElement = pFunc;
		m_pModifications->InsertPoints.Add(pInsFunc);
		return pFunc;
	}
	return NULL;
}

bool CFunctionManager::DeleteFunction(VSFunction* pFunc)
{
	CSmartAtlArray<InsertionPoint*>& pts = m_pModifications->InsertPoints;
	size_t i;
	for (i = 0; i < pts.GetCount(); i++)
	{
		if ((pts[i])->pElement == pFunc)
		{
			break;
		}
	}

	bool bFind = false;
	if (i != pts.GetCount())
	{
		//это добавленная в эту сессию функция
		delete (InsertPointFunc*)(pts[i]);
		pts.RemoveAt(i);
		bFind = true;
	}
	CSmartAtlArray<VSFunction*>& pf = m_pClass->Functions;
	for (size_t j = 0; j < pf.GetCount(); j++)
	{
		if ((pf[j]) == pFunc)
		{
			if (!bFind)
			{
				m_pModifications->DeletePoint.Add(pf[j]);
			}
			pf.RemoveAt(j);
			break;
		}
	}
	return true;
}

HMENU CFunctionManager::CreateSpecFunctionDropMenu()
{
	bool bDialog = false;
	if (!m_bAllowDlgIdle)
	{
		bDialog = (m_pClass->IsDialog() && !m_pClass->m_DialogID.IsEmpty());
	}
	CMenu Menu;
	Menu.CreatePopupMenu();
	UINT uiFlags = MF_STRING;
	if (IsPreTranslateMessage(m_pClass) || bDialog)
		uiFlags |= MF_DISABLED | MF_GRAYED;
	Menu.AppendMenu(uiFlags, ID_MENU_PRE_TRANSLATE_MESSAGE, _T("PreTranslateMessage"));
	if (IsOnIdle(m_pClass) || bDialog)
		uiFlags = MF_DISABLED | MF_GRAYED;
	else
		uiFlags = MF_ENABLED;
	Menu.AppendMenu(uiFlags, ID_MENU_ON_IDLE, _T("OnIdle"));
	FillSpecFunctionArray();
	CString Parent;
	for (size_t i = 0; i < m_SelectedFunctions.GetCount(); i++)
	{
		if (m_SelectedFunctions[i].Parent != Parent)
		{
			Parent = m_SelectedFunctions[i].Parent;
			Menu.AppendMenu(MF_SEPARATOR, ID_SEPARATOR);
		}
		if (IsSpecFunction(m_pClass, m_SelectedFunctions[i]))
		{
			uiFlags = MF_DISABLED | MF_GRAYED;
		}
		else
		{
			uiFlags = MF_ENABLED;
		}
		Menu.AppendMenu(uiFlags, ID_MENU_ON_IDLE + 1 + i, m_SelectedFunctions[i].FuncName);
	}
	
	return Menu.Detach();
}

VSFunction* CFunctionManager::AddSpecFunction(int DropMenuCmd, CAtlArray<MessageStruct*>& InsertedHandlers)
{
	InsertedHandlers.RemoveAll();

	if (DropMenuCmd == ID_MENU_PRE_TRANSLATE_MESSAGE)
	{
		return AddPreTransalateMessage(InsertedHandlers);
	}
	else if (DropMenuCmd == ID_MENU_ON_IDLE)
	{
		return AddOnIdle(InsertedHandlers);
	}
	else 
	{
		int Index = DropMenuCmd - (ID_MENU_ON_IDLE + 1);
		return AddSpecFunction(m_SelectedFunctions[Index]);
	}
	return NULL;
}

bool CFunctionManager::LoadSpecFunctions(CXMLObject* pArchive, LPCTSTR lpName)
{
	if (!m_sSpecFunctions.IsEmpty())
		return true;

	if (!pArchive->StartObject(lpName, false))
		return false;
	
	for (CXMLObject::CXMLIterator i = pArchive->GetFirstChild(); i; i++)
	{
		CString Name = i->GetName();
		CString Parent;
		SpecFunctionParent SpecParent;
		SpecParent.ClassName = Name;
		if (i->StartObject(_T("Parents"), false))
		{
			for (CXMLObject::CXMLIterator j = i->GetFirstChild(); j; j++)
			{
				i->GetText(Parent);
				SpecFunctionParent SpParent;
				if (m_sSpecFunctions.Lookup(Parent, SpParent))
				{
					SpecParent += SpParent;
				}
			}
			i->EndObject();
		}
		if (i->StartObject(_T("Functions"), false))
		{
			for (CXMLObject::CXMLIterator j = i->GetFirstChild(); j; j++)
			{
				SpecFunctionStruct Func;
				Func.Parent = Name;
				Func.LoadFunction(&j);
				SpecParent.SpecFunctions.Add(Func);
			}
			i->EndObject();
		}
		if (i->StartObject(_T("Conditions"), false))
		{
			for (CXMLObject::CXMLIterator j = i->GetFirstChild(); j; j++)
			{
				int Condition;
				i->GetText(Condition);
				SpecParent.Conditions.Add(Condition);
			}
			i->EndObject();
		}
		m_sSpecFunctions.SetAt(Name, SpecParent);
	}
	pArchive->EndObject();

	return true;
}

void CFunctionManager::DeleteSpecFunctions()
{
	m_sSpecFunctions.RemoveAll();
}