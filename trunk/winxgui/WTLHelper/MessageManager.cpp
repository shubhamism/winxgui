////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2005 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	MessageManager.cpp
// Created:	11.07.2005 9:10
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
#include ".\messagemanager.h"
#include "InsertPoint.h"
#include "Dialog/AddAltMapDlg.h"
#include "Dialog/HandlerDlg.h"
#include "Dialog/DDXVariable.h"
#include "Dialog/ReflectionDlg.h"

CHandlerManager CMessageManager::m_sHandlerManager;

CMessageManager::CMessageManager(void) : m_bNewStyle(true), m_bSortMessages(true),
m_bInline(false), m_bUseAtlMisc(true), m_pClass(NULL), m_hParentWnd(NULL), m_pModifications(NULL),
m_pResManager(NULL), m_pMessageMap(NULL), m_pGeneralResources(NULL), m_bCheckMissingEndMap(TRUE)
{
}

CMessageManager::~CMessageManager(void)
{
}

bool CMessageManager::SetHeader(CString HeaderName)
{
	for (size_t i = 0; i < m_pClass->Headers.GetCount(); ++i)
	{
		if (m_pClass->Headers[i].CompareNoCase(HeaderName) == 0)
			return true;
	}
	EnvDTE::CodeElementPtr pIncludeElem = FindInclude(m_pClass, HeaderName, true);
	if (pIncludeElem == NULL)
	{
		VSInclude* pNewInclude = new VSInclude;
		pNewInclude->Name = HeaderName;
		InsertInclude* pInsInclude = new InsertInclude;
		pInsInclude->pElement = pNewInclude;
		m_pModifications->InsertPoints.Add(pInsInclude);
	}
	m_pClass->Headers.Add(HeaderName);
	return true;
}

bool CMessageManager::SetAtlCrack()
{
	return SetHeader(_T("<atlcrack.h>"));
}

bool CMessageManager::SetAtlMisc()
{
	for (size_t i = 0; i < m_pClass->Headers.GetCount(); ++i)
	{
		if (m_pClass->Headers[i] == _T("<atlmisc.h>") ||
			m_pClass->Headers[i] == _T("<atltypes.h>"))
			return true;
	}

	CString Name;
	if (FindInclude(m_pClass, L"<atlmisc.h>", true) == NULL &&
		FindInclude(m_pClass, L"<atltypes.h>", true) == NULL)
	{
		Name = m_bUseAtlMisc ? _T("<atlmisc.h>") : _T("<atltypes.h>");
		VSInclude* pNewInclude = new VSInclude;
		pNewInclude->Name = Name;
		InsertInclude* pInsInclude = new InsertInclude;
		pInsInclude->pElement = pNewInclude;
		m_pModifications->InsertPoints.Add(pInsInclude);
	}
	m_pClass->Headers.Add(Name);
	//m_pClass->m_bAtlMisc = true;
	return true;
}

bool CMessageManager::SetWinX()
{
	return SetHeader(_T("<atlwinx.h>"));
}

bool CMessageManager::InsertNewMap(bool bEx /* = false */)
{
	CString Postfix;
	if (bEx)
	{
		Postfix = _T("_EX");
	}

	VSMessageMap* pNewMap = new VSMessageMap;
	
	pNewMap->pParent = m_pClass;
	pNewMap->Name = _T("MSG");
	pNewMap->Postfix = Postfix;
	VSParameter* pParam = new VSParameter;

	VCCodeModelLibrary::VCCodeClassPtr pClass = m_pClass->pElement;
	_bstr_t DisplayName;
	pClass->get_DisplayName(DisplayName.GetAddress());
	pParam->Name = (LPCTSTR)DisplayName;
	pNewMap->MapParameters.Add(pParam);
	m_pClass->Maps.Add(pNewMap);
	InsertPointMap* pInsPt = new InsertPointMap;
	pInsPt->pElement = pNewMap;
	m_pModifications->InsertPoints.Add(pInsPt);
	return true;
}

CString CMessageManager::CreateHandlerBody(MessageStruct* pMes, bool bCracked /* = false */)
{
	CString Body;
	if (!bCracked)
	{
		for (size_t i = 0; i < pMes->Params.GetCount(); i++)
		{
			if (pMes->Params[i].ParamName != pMes->Params[i].ParamFunc)
			{
				if (pMes->Params[i].ParamType == _T("CPoint") || 
					pMes->Params[i].ParamType == _T("CSize") ||
					pMes->Params[i].ParamType == _T("CRect"))
					SetAtlMisc();
				Body += pMes->Params[i].ParamType + _T(" ") + pMes->Params[i].ParamName + _T(" = ") + pMes->Params[i].ParamFunc + _T(";\r\n");
			}
		}
	}
	if (!pMes->Comment.IsEmpty())
	{
		Body += pMes->Comment + _T("\r\n");
	}
	Body += _T("\r\n");
	if (!pMes->Body.IsEmpty())
	{
		Body += pMes->Body + _T("\r\n");
	}
	else
	{
		Body += _T("return 0;\r\n");
	}
	return Body;
}

int CMessageManager::GetAltMapNumber()
{
	VSMessageMap* pRootMap = (VSMessageMap*)m_pClass->GetMap(CString(_T("MSG")));

	int iNumber = 0;
	EnvDTE::CodeElementsPtr pMacros;//defines
	for (size_t i = 0; i < pRootMap->AltMaps.GetCount(); i++)
	{
		CString Name = pRootMap->AltMaps[i]->Name;
		int iNum;
		if (StrToIntEx(Name, STIF_SUPPORT_HEX, &iNum))
		{
			if (iNum > iNumber)
			{
				iNumber = iNum;
			}
		}
		else
		{
			VSMessageMap* pAltMap = pRootMap->AltMaps[i];
			if (!pAltMap->IsSelf())
			{
				CSmartAtlArray<InsertionPoint*>& CurInsPoints = m_pModifications->InsertPoints;
				for (size_t j = 0; j < CurInsPoints.GetCount(); j++)
				{
					if (CurInsPoints[j]->pElement == (VSElement*)pAltMap)
					{
						InsertPointAltMap* pInsAltMap = (InsertPointAltMap*)CurInsPoints[j];
						if (!pInsAltMap->DefineName.IsEmpty())
						{
							int iNum;
							if (StrToIntEx(pInsAltMap->DefineName, STIF_SUPPORT_HEX, &iNum))
							{
								if (iNum > iNumber)
								{
									iNumber = iNum;
								}
							}
						}
					}
				}
			}
			else
			{
				if (pMacros == NULL)
				{
					EnvDTE::ProjectItemPtr pProjItem;
					m_pClass->pElement->get_ProjectItem(&pProjItem);
					if (pProjItem != NULL)
					{
						EnvDTE::FileCodeModelPtr pCodeModel;
						pProjItem->get_FileCodeModel(&pCodeModel);
						if (pCodeModel != NULL)
						{
							VCCodeModelLibrary::VCFileCodeModelPtr pVCCodeModel = pCodeModel;
							pVCCodeModel->get_Macros(&pMacros);
						}
					}
				}
				if (pMacros == NULL)
				{
					break;
				}
				EnvDTE::CodeElementPtr pElem;
				pMacros->Item(_variant_t(Name), &pElem);
				if (pElem == NULL)
					break;
				VCCodeModelLibrary::VCCodeMacroPtr pMacro = pElem;
				_bstr_t Value = pMacro->Value;
				if (StrToIntExW(Value, STIF_SUPPORT_HEX, &iNum))
				{
					if (iNum > iNumber)
					{
						iNumber = iNum;
					}
				}
			}
		}
	}
	iNumber++;
	return iNumber;
}

bool CMessageManager::IsFunctionExists(CString Name)
{
	for (size_t i = 0; i < m_pClass->Functions.GetCount(); i++)
	{
		if (m_pClass->Functions[i]->Name == Name)
			return true;
	}
	return false;
}

void CMessageManager::AddDlgIDs(CString DialogID, MessageStruct* pMes, CAtlArray<CString>& Strings)
{
	int Type = pMes->Type & TYPE_MASK;
	if (Type == CUSTOM_COMMAND_HANDLER)
	{
		m_pResManager->GetCommandControls(DialogID, Strings);
	}

	if (Type == STD_COMMAND_HANDLER)
	{
		if (!pMes->pResWords)
			return;
		m_pResManager->GetTypedControls(DialogID, pMes->pResWords, Strings);
	}

	if (Type == CUSTOM_NOTIFY_HANDLER)
	{
		m_pResManager->GetNotifyControls(DialogID, Strings);
	}

	if (Type == STD_NOTIFY_HANDLER)
	{
		if (!pMes->pResWords)
			return;
		
		m_pResManager->GetTypedControls(DialogID, pMes->pResWords, Strings);
	}
	SortStringArray(Strings);
}

bool CMessageManager::IsNeedReflected(MessageStruct* pMes)
{
	int Type = pMes->Type & TYPE_MASK;
	if (Type == CUSTOM_NOTIFY_HANDLER || Type == CUSTOM_COMMAND_HANDLER
		|| Type == CUSTOM_MESSAGE_HANDLER || Type == STD_MESSAGE_HANDLER)
	{
		return false;
	}
	for (size_t i = 0; i < m_pClass->Parents.GetCount(); i++) 
	{
		if (m_pClass->Parents[i]->Name == _T("CWindowImpl"))
		{
			VSBase* pWindowImpl = m_pClass->Parents[i];
			if (!pWindowImpl->TemplateParameters.GetCount())
			{
				pWindowImpl->RetrieveTemplateParameters();
			}
			if (pWindowImpl->TemplateParameters.GetCount() > 1)
			{
				VSParameter* pParam = pWindowImpl->TemplateParameters[1];
				for (size_t i = 0; i < CDDXVariable::m_ControlClasses.GetCount(); i++)
				{
					CString ControlClass = CDDXVariable::m_ControlClasses[i].ControlName;
					CAtlArray<CString>& Classes = CDDXVariable::m_ControlClasses[i].Classes;
					for (size_t j = 0; j < Classes.GetCount(); j++)
					{
						if (pParam->Name == Classes[j])
							return true;
					}
				}
			}
		}
	}
	
	return false;
}

bool CMessageManager::AddCommandMessage(CHandlerIDDlg& dlg, OUT HandlerStruct& Handler, MessageStruct* pMes)
{
	InsertPointHandler* pInsPt = new InsertPointHandler;
	VSMapEntry* MapEntry = new VSMapEntry;

	Handler.Message = _T("WM_COMMAND");
	Handler.HandlerName = dlg.m_Function;

	if (dlg.m_bHandlerCode && dlg.m_bHandlerID)
	{
		if (!dlg.m_bRange)
		{
			MapEntry->Name = _T("COMMAND_HANDLER");
			Handler.Type = HANDLER_TYPE_COMMAND_MESSAGE | HANDLER_CODE | HANDLER_ID;
		}
		else
		{
			MapEntry->Name = _T("COMMAND_RANGE_CODE_HANDLER");
			Handler.Type = HANDLER_TYPE_COMMAND_MESSAGE | HANDLER_CODE | HANDLER_ID | HANDLER_RANGE;
		}
	}
	else
	{
		if (dlg.m_bHandlerCode)
		{
			MapEntry->Name = _T("COMMAND_CODE_HANDLER");
			Handler.Type = HANDLER_TYPE_COMMAND_MESSAGE | HANDLER_CODE;
		}
		else
		{
			if (!dlg.m_bRange)
			{
				MapEntry->Name = _T("COMMAND_ID_HANDLER");
				Handler.Type = HANDLER_TYPE_COMMAND_MESSAGE | HANDLER_ID;
			}
			else
			{
				MapEntry->Name = _T("COMMAND_RANGE_HANDLER");
				Handler.Type = HANDLER_TYPE_COMMAND_MESSAGE | HANDLER_ID | HANDLER_RANGE;
			}
		}
	}

	if (dlg.m_iSelectedHandler == -1)
	{
		if (dlg.m_Style)
		{
			MapEntry->Name += _T("_EX");
			Handler.Type |= HANDLER_EX;
			SetAtlCrack();
		}
	}
	else
	{
		if (dlg.m_SupHandlers[dlg.m_iSelectedHandler].Type & HANDLER_EX)
		{
			MapEntry->Name += _T("_EX");
			Handler.Type |= HANDLER_EX;
			SetAtlCrack();
		}
	}
	if (dlg.m_bReflected)
	{
		MapEntry->Name = _T("REFLECTED_") + MapEntry->Name;
		Handler.Type |= HANDLER_REFLECTED;
	}

	VSParameter* pParam;
	if (dlg.m_bHandlerID)
	{
		pParam = new VSParameter;
		pParam->Name = dlg.m_ID;
		MapEntry->Parameters.Add(pParam);
		Handler.FirstId = dlg.m_ID;
	}

	if (dlg.m_bRange)
	{
		pParam = new VSParameter;
		pParam->Name = dlg.m_LastID;
		MapEntry->Parameters.Add(pParam);
		Handler.LastId = dlg.m_LastID;
	}

	if (dlg.m_bHandlerCode)
	{
		pParam = new VSParameter;
		pParam->Name = dlg.m_Message;
		MapEntry->Parameters.Add(pParam);
		Handler.Code = dlg.m_Message;
	}

	pParam = new VSParameter;
	pParam->Name = dlg.m_Function;
	MapEntry->Parameters.Add(pParam);

	pInsPt->pElement = MapEntry;
	pInsPt->pParentMap = m_pMessageMap;

	m_pMessageMap->MapEntries.Add(MapEntry);

	VSFunction* Func;
	if (dlg.m_iSelectedHandler == -1)
	{
		Func = new VSFunction;
		MapEntry->pData = Func;
		Func->Name = dlg.m_Function;
		Func->Access = EnvDTE::vsCMAccessPublic;
		Func->Type = _T("LRESULT");
		Func->bInline = dlg.m_bInline;

		pParam = new VSParameter;

		pParam->Name = _T("wNotifyCode");
		pParam->Type = _T("WORD");
		Func->Parameters.Add(pParam);

		pParam = new VSParameter;
		pParam->Name = _T("wID");
		pParam->Type = _T("WORD");
		Func->Parameters.Add(pParam);

		pParam = new VSParameter;
		pParam->Name = _T("hWndCtl");
		pParam->Type = _T("HWND");
		Func->Parameters.Add(pParam);

		if (!dlg.m_Style)
		{
			pParam = new VSParameter;
			pParam->Name = _T("bHandled");
			pParam->Type = _T("BOOL&");
			Func->Parameters.Add(pParam);
		}

		m_pClass->Functions.Add(Func);
	}
	else
	{
		Func = dlg.m_SupHandlers[dlg.m_iSelectedHandler].pFunc;
	}
	pInsPt->Body = CreateHandlerBody(pMes);

	pInsPt->pFunction = Func;

	m_pModifications->InsertPoints.Add(pInsPt);

	Handler.pFunction = Func;
	Handler.pMapEntry = MapEntry;
	return true;
}

bool CMessageManager::AddNotifyMessage(CHandlerIDDlg& dlg, OUT HandlerStruct& Handler, MessageStruct* pMes)
{
	InsertPointHandler* pInsPt = new InsertPointHandler;
	VSMapEntry* MapEntry = new VSMapEntry;
	Handler.HandlerName = dlg.m_Function;
	Handler.Message = _T("WM_NOTIFY");

	if (dlg.m_bHandlerCode && dlg.m_bHandlerID)
	{
		if (!dlg.m_bRange)
		{
			MapEntry->Name = _T("NOTIFY_HANDLER");
			Handler.Type = HANDLER_TYPE_NOTIFY_MESSAGE | HANDLER_CODE | HANDLER_ID;
		}
		else
		{
			MapEntry->Name = _T("NOTIFY_RANGE_CODE_HANDLER");
			Handler.Type = HANDLER_TYPE_NOTIFY_MESSAGE | HANDLER_CODE | HANDLER_ID | HANDLER_RANGE;
		}
	}
	else
	{
		if (dlg.m_bHandlerCode)
		{
			MapEntry->Name = _T("NOTIFY_CODE_HANDLER");
			Handler.Type = HANDLER_TYPE_NOTIFY_MESSAGE | HANDLER_CODE;
		}
		else
		{
			if (!dlg.m_bRange)
			{
				MapEntry->Name = _T("NOTIFY_ID_HANDLER");
				Handler.Type = HANDLER_TYPE_NOTIFY_MESSAGE | HANDLER_ID;
			}
			else
			{
				MapEntry->Name = _T("NOTIFY_RANGE_HANDLER");
				Handler.Type = HANDLER_TYPE_NOTIFY_MESSAGE | HANDLER_ID | HANDLER_RANGE;
			}
		}
	}

	VSParameter* pParam;
	if (dlg.m_bHandlerID)
	{
		pParam = new VSParameter;
		pParam->Name = dlg.m_ID;
		MapEntry->Parameters.Add(pParam);
		Handler.FirstId = dlg.m_ID;
	}
	if (dlg.m_bRange)
	{
		pParam = new VSParameter;
		pParam->Name = dlg.m_LastID;
		MapEntry->Parameters.Add(pParam);
		Handler.LastId = dlg.m_LastID;
	}
	if (dlg.m_bHandlerCode)
	{
		pParam = new VSParameter;
		pParam->Name = dlg.m_Message;
		MapEntry->Parameters.Add(pParam);
		Handler.Code = dlg.m_Message;
	}

	pParam = new VSParameter;
	pParam->Name = dlg.m_Function;
	MapEntry->Parameters.Add(pParam);

	if (dlg.m_iSelectedHandler == -1)
	{
		if (dlg.m_Style)
		{
			MapEntry->Name += _T("_EX");
			SetAtlCrack();
			Handler.Type |= HANDLER_EX;
		}
	}
	else
	{
		if (dlg.m_SupHandlers[dlg.m_iSelectedHandler].Type & HANDLER_EX)
		{
			MapEntry->Name += _T("_EX");
			SetAtlCrack();
			Handler.Type |= HANDLER_EX;
		}
	}
	if (dlg.m_bReflected)
	{
		MapEntry->Name = _T("REFLECTED_") + MapEntry->Name;
		Handler.Type |= HANDLER_REFLECTED;
	}
	pInsPt->pElement = MapEntry;
	pInsPt->pParentMap = m_pMessageMap;

	m_pMessageMap->MapEntries.Add(MapEntry);

	VSFunction* Func;
	if (dlg.m_iSelectedHandler == -1)
	{
		Func = new VSFunction;
		MapEntry->pData = Func;
		Func->Name = dlg.m_Function;
		Func->Access = EnvDTE::vsCMAccessPublic;
		Func->Type = _T("LRESULT");
		Func->bInline = dlg.m_bInline;

		if (!dlg.m_Style)
		{
			pParam->Name = _T("idCtrl");
			pParam->Type = _T("int");
			Func->Parameters.Add(pParam);
		}

		pParam = new VSParameter;
		pParam->Name = _T("pnmh");
		pParam->Type = _T("LPNMHDR");
		Func->Parameters.Add(pParam);

		if (!dlg.m_Style)
		{
			pParam = new VSParameter;
			pParam->Name = _T("bHandled");
			pParam->Type = _T("BOOL&");
			Func->Parameters.Add(pParam);
		}

		m_pClass->Functions.Add(Func);
	}
	else
	{
		Func = dlg.m_SupHandlers[dlg.m_iSelectedHandler].pFunc;
	}

	pInsPt->pFunction = Func;

	pInsPt->Body = CreateHandlerBody(pMes);

	m_pModifications->InsertPoints.Add(pInsPt);

	Handler.pFunction = Func;
	Handler.pMapEntry = MapEntry;
	return true;
}

void CMessageManager::AddMessages(MessageStruct* pMes, CAtlArray<MessageStruct*>& Messages)
{
	for (size_t i = 0; i < pMes->Children.GetCount(); i++)
	{
		if (pMes->Children[i]->Type & TYPE_MASK)
		{
			Messages.Add(pMes->Children[i]);
		}
		else
		{
			AddMessages(pMes->Children[i], Messages);
		}
	}
}

void CMessageManager::AddSupportedMessages(const ResControl* pControl, MessageStruct* pMes, CAtlArray<MessageStruct*>& Messages)
{
	for (size_t i = 0; i < pMes->Children.GetCount(); i++)
	{
		int Type = pMes->Children[i]->Type & TYPE_MASK;
		int Flags = pMes->Children[i]->Type & FLAGS_MASK;
		bool bAddMessages = false;
		if (Type == ROOT_PLACE)
		{
			if (Flags & CONTAIN_RESOURCE_STRINGS && pMes->Children[i]->pResWords)
			{
				CAtlArray<CString>* pResWords = pMes->Children[i]->pResWords;
				for (size_t j = 0; j < pResWords->GetCount(); j++)
				{
					if (pResWords->GetAt(j) == pControl->m_Type)
					{
						bAddMessages = true;
						AddMessages(pMes->Children[i], Messages);
						break;
					}
				}
			}
			if (!bAddMessages)
			{
				AddSupportedMessages(pControl, pMes->Children[i], Messages);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////

void CMessageManager::Init(IN HWND hParentWnd, IN const CResourceManager* pResManager, IN CAtlArray<CString>* pGeneralResources)
{
	m_hParentWnd = hParentWnd;
	m_pResManager = pResManager;
	m_pGeneralResources = pGeneralResources;
}

bool CMessageManager::SetClass(IN VSClass* pClass, IN InsDelPoints* pModifications)
{
	m_pModifications = pModifications;
	m_pClass = pClass;
	m_pClass->RetriveItems();
	m_pMessageMap = (VSMessageMap*)m_pClass->GetMap(_T("MSG"));
	m_sHandlerManager.Init(&m_pClass->Functions);
	bool bRes = false;

	//replace END_MSG_MAP with END_MSG_MAP_EX if need
	if (m_pMessageMap && !m_pMessageMap->bCorrectEnd && m_bCheckMissingEndMap)
	{
		if (MessageBox(m_hParentWnd, _T("WTL Helper has detected that you are using macro BEGIN_MSG_MAP_EX without corresponding macro END_MSG_MAP_EX.\r\nIt can cause different issues for WTL Helper. It's highly recomeneded to replace this macro.\r\nDo you want to do this ?"), NULL, MB_YESNO) == IDYES)
		{
			if (ReplaceMessageMapEnd())
			{
				bRes = true;
			}
		}
		m_pMessageMap->bCorrectEnd = true;
	}
	return bRes;
}

void CMessageManager::SetMessageMap(VSMessageMap* pMap)
{
	m_pMessageMap = pMap;
}

bool CMessageManager::IsClassSet()
{
	return m_pClass != NULL;
}

bool CMessageManager::AddMessageMap()
{
	bool bExMap = false;
	int MesRes = MessageBox(m_hParentWnd, _T("Class has no message map!\r\nCreate old style map(Yes) or new style map(No)"), 
		NULL, MB_YESNOCANCEL);
	if (MesRes  == IDCANCEL)
	{
		return FALSE;
	}
	if (MesRes == IDNO)
	{
		CString MsgStr;
		MsgStr = _T("If you want use new style message map and use WtlHelper you need compile your application with precompiled header \"stdafx.h\".\r\nWtlHelper also need to create in the \"stdafx.h\" this line:\r\n#define END_MSG_MAP_EX END_MSG_MAP\r\nOtherwise the author do not guarantee that WtlHelper will work properly\r\nDo you agree?");
		MesRes = MessageBox(m_hParentWnd, MsgStr, NULL, MB_YESNO | MB_ICONINFORMATION);
		if (MesRes == IDYES)
		{
			//проверить существование stdafx.h
			EnvDTE::ProjectPtr pProject;
			EnvDTE::ProjectItemPtr pProjectItem;
			m_pClass->pElement->get_ProjectItem(&pProjectItem);
			pProjectItem->get_ContainingProject(&pProject);

			EnvDTE::ProjectItemPtr pStdAfxFile = FindItem(pProject, _bstr_t(L"stdafx.h"), EnvDTE::ProjectItemPtr(NULL));
			if (pStdAfxFile == NULL)
			{
				if (MessageBox(m_hParentWnd, _T("Cannot locate \"stdafx.h\"!\r\nCreate old style message map?"), NULL, MB_YESNO | MB_ICONERROR) == IDNO)
					return FALSE;
			}
			else
			{
				VCCodeModelLibrary::VCFileCodeModelPtr pVCFileCodeModel;
				EnvDTE::FileCodeModelPtr pFileCodeModel;
				pStdAfxFile->get_FileCodeModel(&pFileCodeModel);
				pVCFileCodeModel = pFileCodeModel;
				EnvDTE::CodeElementsPtr pMacros =  pVCFileCodeModel->Macros;
				EnvDTE::CodeElementPtr pMacro;
				if (pMacros->Item(_variant_t(_bstr_t(L"END_MSG_MAP_EX")), &pMacro) == S_OK)
				{
					bExMap = true;
				}
				else
				{
					VCCodeModelLibrary::VCCodeMacroPtr pMacro;
					pMacro = pVCFileCodeModel->AddMacro(_bstr_t(L"END_MSG_MAP_EX"), _bstr_t(L"END_MSG_MAP"), _variant_t(-1));
					if (pMacro != NULL)
					{
						bExMap = true;
					}
					else
					{
						if (MessageBox(m_hParentWnd, _T("Cannot add macro END_MSG_MAP_EX!\r\nCreate old style message map!"), NULL, MB_YESNO | MB_ICONERROR) == IDNO)
							return FALSE;
					}
				}
			}
		}
	}

	CString MesMapName = _T("MSG");
	if (InsertNewMap(bExMap))
	{
		m_pMessageMap = (VSMessageMap*)m_pClass->GetMap(MesMapName);
	}
	ATLASSERT(m_pMessageMap);
	m_pMessageMap->bSortItems = m_bSortMessages;
	return true;
}

bool CMessageManager::ReplaceMessageMapEnd()
{
	if (!m_pMessageMap)
	{
		return false;
	}
	CString MsgStr;
	MsgStr = _T("If you want to replace macro END_MSG_MAP with END_MSG_MAP_EX you need compile your application with precompiled header \"stdafx.h\".\r\nWtlHelper also need to create in the \"stdafx.h\" this line:\r\n#define END_MSG_MAP_EX END_MSG_MAP");
	int MesRes = MessageBox(m_hParentWnd, MsgStr, NULL, MB_OKCANCEL | MB_ICONQUESTION);
	if (MesRes == IDOK)
	{
		//проверить существование stdafx.h
		EnvDTE::ProjectPtr pProject;
		EnvDTE::ProjectItemPtr pProjectItem;
		m_pClass->pElement->get_ProjectItem(&pProjectItem);
		pProjectItem->get_ContainingProject(&pProject);

		EnvDTE::ProjectItemPtr pStdAfxFile = FindItem(pProject, _bstr_t(L"stdafx.h"), EnvDTE::ProjectItemPtr(NULL));
		if (pStdAfxFile == NULL)
		{
			MessageBox(m_hParentWnd, _T("Cannot locate \"stdafx.h\"!\r\nCreate old style message map?"), NULL, MB_OK | MB_ICONERROR);
			return false;
		}
		else
		{
			VCCodeModelLibrary::VCFileCodeModelPtr pVCFileCodeModel;
			EnvDTE::FileCodeModelPtr pFileCodeModel;
			pStdAfxFile->get_FileCodeModel(&pFileCodeModel);
			pVCFileCodeModel = pFileCodeModel;
			EnvDTE::CodeElementsPtr pMacros =  pVCFileCodeModel->Macros;
			EnvDTE::CodeElementPtr pMacro;
			if (pMacros->Item(_variant_t(_bstr_t(L"END_MSG_MAP_EX")), &pMacro) != S_OK)
			{
				VCCodeModelLibrary::VCCodeMacroPtr pMacro;
				pMacro = pVCFileCodeModel->AddMacro(_bstr_t(L"END_MSG_MAP_EX"), _bstr_t(L"END_MSG_MAP"), _variant_t(-1));
				if (pMacro == NULL)
				{
					MessageBox(m_hParentWnd, _T("Cannot add macro END_MSG_MAP_EX!"), NULL, MB_OK | MB_ICONERROR);
                    return false;
				}
			}
		}

		InsertPointReplaceEndMap* pInsPt = new InsertPointReplaceEndMap;
		pInsPt->pElement = m_pMessageMap;
		m_pModifications->InsertPoints.Add(pInsPt);
	}

	return true;
}

bool CMessageManager::InsertAltMap()
{
	CAddAltMapDlg dlg;

	VSMessageMap* pRootMap = (VSMessageMap*)m_pClass->GetMap(CString(_T("MSG")));

	int iNumber = GetAltMapNumber();

	dlg.m_iNumber.Format(_T("%d"), iNumber);
	if (dlg.DoModal() == IDOK)
	{
		VSMessageMap* pNewAltMap = new VSMessageMap;
		pNewAltMap->pParent = pRootMap;
		InsertPointAltMap* pAltMapInsertPoint = new InsertPointAltMap;
		pAltMapInsertPoint->pElement = pNewAltMap;
		pAltMapInsertPoint->pParentMap = pRootMap;

		dlg.m_iNumber.Trim();
		dlg.m_Name.Trim();
		if (dlg.m_Name.IsEmpty())
		{
			pNewAltMap->Name = dlg.m_iNumber;
		}
		else
		{
			pNewAltMap->Name = dlg.m_Name;
			pAltMapInsertPoint->DefineName = dlg.m_iNumber;
		}
		pRootMap->AltMaps.Add(pNewAltMap);
		m_pModifications->InsertPoints.Add(pAltMapInsertPoint);
	}
	else
	{
		return false;
	}
	return true;
}

bool CMessageManager::InsertCommandMessageHandler(IN MessageStruct* pMes, OUT HandlerStruct& Handler)
{
	CHandlerIDDlg dlg;
	CString FuncName = pMes->DefFuncName;
	int iNum = 0;
	while(IsFunctionExists(FuncName))
	{
		iNum++;
		FuncName.Format(_T("%s%d"), pMes->DefFuncName, iNum);
	}

	dlg.m_DefFunc = FuncName;
	dlg.m_Message = pMes->Message;
	dlg.m_Style = m_bNewStyle;
	dlg.m_bInline = m_bInline;
	dlg.m_bReflected = IsNeedReflected(pMes);
	dlg.m_Classes.Add(m_pClass->Name);

	m_sHandlerManager.GetHandlerFunctions(dlg.m_SupHandlers, HANDLER_TYPE_COMMAND_MESSAGE);
	
	if ((pMes->Type & TYPE_MASK) != CUSTOM_COMMAND_HANDLER)
	{
		dlg.m_bHandlerCode = TRUE;
		if (dlg.m_ResIDs.IsEmpty())
		{
			dlg.m_bHandlerID = FALSE;
		}
		else
		{
			dlg.m_bHandlerID = TRUE;
		}
	}
	else
	{
		dlg.m_bHandlerCode = FALSE;
		dlg.m_bHandlerID = TRUE;
		dlg.m_ResIDs.Append(*m_pGeneralResources);
		dlg.m_bCustom = TRUE;
	}

	if (m_pClass->m_eDialog == eTrue && !m_pClass->m_DialogID.IsEmpty())
	{
		AddDlgIDs(m_pClass->m_DialogID, pMes, dlg.m_ResIDs);
	}

	if (dlg.DoModal() == IDOK)
	{
		return AddCommandMessage(dlg, Handler, pMes);
	}
	return false;
}

bool CMessageManager::InsertNotifyMessageHandler(IN MessageStruct* pMes, OUT HandlerStruct& Handler)
{
	CHandlerIDDlg dlg;
	CString FuncName = pMes->DefFuncName;
	int iNum = 0;
	while(IsFunctionExists(FuncName))
	{
		iNum++;
		FuncName.Format(_T("%s%d"), pMes->DefFuncName, iNum);
	}
	dlg.m_DefFunc = FuncName;
	dlg.m_Message = pMes->Message;
	dlg.m_Style = m_bNewStyle;
	dlg.m_bInline = m_bInline;
	dlg.m_Classes.Add(m_pClass->Name);
	dlg.m_bReflected = IsNeedReflected(pMes);
	m_sHandlerManager.GetHandlerFunctions(dlg.m_SupHandlers, HANDLER_TYPE_NOTIFY_MESSAGE);

	if (m_pClass->m_eDialog == eTrue && !m_pClass->m_DialogID.IsEmpty())
	{
		AddDlgIDs(m_pClass->m_DialogID, pMes, dlg.m_ResIDs);
	}
	if ((pMes->Type & TYPE_MASK) != CUSTOM_NOTIFY_HANDLER)
	{
		dlg.m_bHandlerCode = TRUE;
		if (dlg.m_ResIDs.IsEmpty())
		{
			dlg.m_bHandlerID = FALSE;
		}
		else
		{
			dlg.m_bHandlerID = TRUE;
		}
	}
	else
	{
		dlg.m_bHandlerCode = FALSE;
		dlg.m_bHandlerID = TRUE;
		dlg.m_bCustom = TRUE;
	}
	if (dlg.DoModal() == IDOK)
	{
		return AddNotifyMessage(dlg, Handler, pMes);
	}
	return false;
}

bool CMessageManager::InsertWindowsMessageHandler(IN MessageStruct* pMes, OUT HandlerStruct& Handler)
{
	CHandlerDlg dlg;
	CString FuncName = pMes->DefFuncName;
	int iNum = 0;
	while(IsFunctionExists(FuncName))
	{
		iNum++;
		FuncName.Format(_T("%s%d"), pMes->DefFuncName, iNum);
	}
	dlg.m_DefFunc = FuncName;
	dlg.m_Message = pMes->Message;
	//TRUE - новый стиль, FALSE - старый
	dlg.m_Style = m_bNewStyle;
	dlg.m_bInline = m_bInline;
	m_sHandlerManager.FindSimilarFunctions(pMes, dlg.m_SupHandlers);
	if ((pMes->Type & TYPE_MASK) == CUSTOM_MESSAGE_HANDLER)
	{
		dlg.m_bCustom = TRUE;
	}
	if (dlg.DoModal() == IDOK)
	{
		//добавляем и MapEntry, и функцию в списки, но 
		//реальное добавление в текст программы будет в UpdateClasses()
		InsertPointHandler* pInsPt = new InsertPointHandler;
		Handler.Message = dlg.m_Message;
		Handler.HandlerName = dlg.m_Function;

		VSMapEntry* MapEntry = new VSMapEntry;
		if (dlg.m_iSelectedHandler != -1)
		{
			Handler.Type = dlg.m_SupHandlers[dlg.m_iSelectedHandler].Type;
		}
		else
		{
			if (dlg.m_Style && !(pMes->Type & NO_CRACK_MESSAGES))
			{
				Handler.Type = HANDLER_TYPE_CRACK_MESSAGE;
			}
			else
			{
				if (!dlg.m_Style)
				{
					Handler.Type = HANDLER_TYPE_MESSAGE;
				}
				else
				{
					Handler.Type = HANDLER_TYPE_MESSAGE | HANDLER_EX;
				}
			}
		}
		if (Handler.Type ==  HANDLER_TYPE_CRACK_MESSAGE)
		{
			MapEntry->Name = _T("MSG_") + pMes->Message;
			VSParameter* pParam = new VSParameter;
			pParam->Name = dlg.m_Function;
			MapEntry->Parameters.Add(pParam);
			SetAtlCrack();
		}
		else
		{
			if (HANDLER_TYPE_MESSAGE == Handler.Type)
			{
				MapEntry->Name = _T("MESSAGE_HANDLER");
			}
			else
			{
				MapEntry->Name = _T("MESSAGE_HANDLER_EX");
			}
			VSParameter* pParam = new VSParameter;
			pParam->Name = dlg.m_Message;
			MapEntry->Parameters.Add(pParam);
			pParam = new VSParameter;
			pParam->Name = dlg.m_Function;
			MapEntry->Parameters.Add(pParam);
		}

		pInsPt->pElement = MapEntry;
		pInsPt->pParentMap = m_pMessageMap;

		m_pMessageMap->MapEntries.Add(MapEntry);

		VSFunction* Func;
		if (dlg.m_iSelectedHandler == -1)
		{
			Func = new VSFunction;
			MapEntry->pData = Func;

			Func->Name = dlg.m_Function;
			Func->Access = EnvDTE::vsCMAccessPublic;
			Func->Type = _T("LRESULT");
			Func->bInline = dlg.m_bInline;
			if (Handler.Type == HANDLER_TYPE_CRACK_MESSAGE)
			{
				for (size_t i = 0; i < pMes->Params.GetCount(); i++)
				{
					VSParameter* pParam = new VSParameter;
					pParam->Name = pMes->Params[i].ParamName;
					pParam->Type = pMes->Params[i].ParamType;
					Func->Parameters.Add(pParam);
					if (pParam->Type == _T("CPoint") || pParam->Type == _T("CSize") ||
						pParam->Type == _T("CRect"))
						SetAtlMisc();
				}
			}
			else
			{
				VSParameter* pParam = new VSParameter;
				pParam->Name = _T("uMsg");
				pParam->Type = _T("UINT");
				Func->Parameters.Add(pParam);

				pParam = new VSParameter;
				pParam->Name = _T("wParam");
				pParam->Type = _T("WPARAM");
				Func->Parameters.Add(pParam);

				pParam = new VSParameter;
				pParam->Name = _T("lParam");
				pParam->Type = _T("LPARAM");
				Func->Parameters.Add(pParam);

				if (!(Handler.Type & HANDLER_EX))
				{
					pParam = new VSParameter;
					pParam->Name = _T("bHandled");
					pParam->Type = _T("BOOL&");
					Func->Parameters.Add(pParam);
				}
			}

			m_pClass->Functions.Add(Func);
		}
		else
		{
			Func = dlg.m_SupHandlers[dlg.m_iSelectedHandler].pFunc;
		}
		pInsPt->pFunction = Func;

		if (Handler.Type == HANDLER_TYPE_CRACK_MESSAGE)
		{
			pInsPt->Body = CreateHandlerBody(pMes, true);
		}
		else
		{
			pInsPt->Body = CreateHandlerBody(pMes);
		}

		m_pModifications->InsertPoints.Add(pInsPt);

		Handler.pFunction = Func;
		Handler.pMapEntry = MapEntry;

		return true;
	}
	return false;
}

bool CMessageManager::InsertDialogControlMessageHandler(IN const ResControl* pControl, ClassVector& Classes, CSmartAtlArray<InsDelPoints>& Modifications, int iCurClass)
{
	CHandlerIDDlg dlg;
	CAtlArray<MessageStruct*> Messages;
	SetClass(Classes[iCurClass], &Modifications[iCurClass]);

	// retrieve messages for control
	MessageStruct* pMes = m_sHandlerManager.GetRootMessage();
	AddSupportedMessages(pControl, pMes, Messages);
	if (!Messages.GetCount())
	{
		MessageBox(m_hParentWnd, _T("No messages for this control!"), NULL, MB_ICONWARNING);
		return false;
	}
	// set default message
	int iDefmessage = -1;
	for (size_t i = 0; i < Messages.GetCount(); i++)
	{
		dlg.m_Messages.Add(Messages[i]->Message);
		if (Messages[i]->Type & DEFAULT_MESSAGE)
		{
			iDefmessage = (int)i;
		}
	}
	if (iDefmessage == -1)
		iDefmessage = 0;

	dlg.m_iSelMessage = iDefmessage;
	CString FuncName = Messages[iDefmessage]->DefFuncName;
	int iNum = 0;
	while(IsFunctionExists(FuncName))
	{
		iNum++;
		FuncName.Format(_T("%s%d"), pMes->DefFuncName, iNum);
	}
	dlg.m_DefFunc = FuncName;
	dlg.m_Message = dlg.m_Messages[iDefmessage];
	dlg.m_Style = m_bNewStyle;
	dlg.m_bInline = m_bInline;
	dlg.m_bAllowSelectClasses = true;
	for (size_t i = 0; i < Classes.GetCount(); i++)
	{
		dlg.m_Classes.Add(Classes[i]->Name);
	}
	dlg.m_iSelectedClass = iCurClass;

	int TypeMask = 0;
	eControlType eCT = CResourceManager::GetControlType(pControl->m_Type);
	if (eCT == eCTCommand)
	{
		TypeMask = HANDLER_TYPE_COMMAND_MESSAGE;
	}
	if (eCT == eCTNotify)
	{
		TypeMask = HANDLER_TYPE_NOTIFY_MESSAGE;
	}
	
	m_sHandlerManager.GetHandlerFunctions(dlg.m_SupHandlers, TypeMask);
	dlg.m_bHandlerCode = TRUE;
	dlg.m_bHandlerID = TRUE;
	dlg.m_ID = pControl->m_ID;
	dlg.m_fEnabledFeatures = EF_ID | EF_CODE | EF_RANGE;

	AddDlgIDs(m_pClass->m_DialogID, Messages[iDefmessage], dlg.m_ResIDs);
	if (dlg.DoModal() == IDOK)
	{
		HandlerStruct hs;
		MessageStruct tmpMes;
		MessageStruct* pCurMes = &tmpMes;
		for (size_t i = 0; i < Messages.GetCount(); i++)
		{
			if (Messages[i]->Message == dlg.m_Message)
			{
				pCurMes = Messages[i];
				break;
			}
		}
		if (dlg.m_iSelectedClass != iCurClass)
		{
			iCurClass = dlg.m_iSelectedClass;
			SetClass(Classes[iCurClass], &Modifications[iCurClass]);
		}
		
		if (!m_pMessageMap)
		{
			if (!AddMessageMap())
				return false;
		}

		if (TypeMask == HANDLER_TYPE_COMMAND_MESSAGE)
			AddCommandMessage(dlg, hs, pCurMes);
		else
			AddNotifyMessage(dlg, hs, pCurMes);
		return true;
	}

	return false;
}

bool CMessageManager::InsertIDMessageHandler(IN CString ID, ClassVector& Classes, CSmartAtlArray<InsDelPoints>& Modifications, int& iCurClass)
{
	CHandlerIDDlg dlg;
	SetClass(Classes[iCurClass], &Modifications[iCurClass]);
	dlg.m_iSelectedClass = iCurClass;
	dlg.m_Style = m_bNewStyle;
	dlg.m_bInline = m_bInline;
	dlg.m_bHandlerCode = FALSE;
	dlg.m_bRange = FALSE;
	dlg.m_bHandlerID = TRUE;
	dlg.m_ID = ID;
	dlg.m_bAllowSelectClasses = true;
	dlg.m_bHandlerID = TRUE;
	dlg.m_fEnabledFeatures = EF_RANGE;
	for (size_t i = 0; i < Classes.GetCount(); i++)
	{
		dlg.m_Classes.Add(Classes[i]->Name);
	}
	ATLASSERT(m_pGeneralResources);
	dlg.m_ResIDs.Append(*m_pGeneralResources);
	if (dlg.DoModal() == IDOK)
	{
		HandlerStruct hs;
		MessageStruct ms;
		ms.Type = CUSTOM_COMMAND_HANDLER;

		if (dlg.m_iSelectedClass != iCurClass)
		{
			iCurClass = dlg.m_iSelectedClass;
			SetClass(Classes[iCurClass], &Modifications[iCurClass]);
		}

		if (!m_pMessageMap)
		{
			if (!AddMessageMap())
				return false;
		}

		return AddCommandMessage(dlg, hs, &ms);
	}
	return false;
}

bool CMessageManager::InsertReflectionHandler(IN MessageStruct* pMes, OUT HandlerStruct& Handler, CString ControlId /* = CString() */)
{
	CReflectionDlg dlg;
	int Type = pMes->Type & TYPE_MASK;
	if (Type == CUSTOM_REFLECTION_HANDLER)
	{
		dlg.m_dwFlags = RD_MESSAGE;
	}
	else if (Type == CUSTOM_COMMAND_REFLECTION_HANDLER)
	{
		dlg.m_dwFlags = RD_COMMAND;
	}
	else if (Type == CUSTOM_NOTIFY_REFLECTION_HANDLER)
	{
		dlg.m_dwFlags = RD_NOTIFY;
	}
	
	if (m_pClass->IsDialog() && !m_pClass->m_DialogID.IsEmpty())
	{
		m_pResManager->GetCommandControls(m_pClass->m_DialogID, dlg.m_CommandIds);
		m_pResManager->GetNotifyControls(m_pClass->m_DialogID, dlg.m_NotifyIds);
	}
	m_sHandlerManager.FindCommandMessages(dlg.m_CommandCodes);
	m_sHandlerManager.FindNotifyMessages(dlg.m_NotifyCodes);
	dlg.m_ID = ControlId;
	if (dlg.DoModal() == IDOK)
	{
		Handler.HandlerName = _T("Reflection Handler");
		Handler.Type = HANDLER_REFLECTION_MESSAGE;
		Handler.pFunction = NULL;
		
		VSMapEntry* pMapEntry = new VSMapEntry;
		Handler.pMapEntry = pMapEntry;
		pMapEntry->Name = _T("REFLECT_");

		if ((dlg.m_dwFlags & (RD_NOTIFY | RD_COMMAND) ) == 0)
		{
			pMapEntry->Name += _T("NOTIFICATIONS_");
			if (dlg.m_Message != _T("All"))
			{
				Handler.Message = dlg.m_Message;
				pMapEntry->Name += _T("MSG_");
				VSParameter* pParam = new VSParameter;
				pParam->pParent = pMapEntry;
				pParam->Name = dlg.m_Message;
				pMapEntry->Parameters.Add(pParam);
			}
			if (dlg.m_dwFlags & RD_WND)
			{
				pMapEntry->Name += _T("HWND_");
				Handler.Type |= HANDLER_HWND;
				Handler.HWND = dlg.m_Wnd;
				VSParameter* pParam = new VSParameter;
				pParam->pParent = pMapEntry;
				pParam->Name = dlg.m_Wnd;
				pMapEntry->Parameters.Add(pParam);
			}
			
			if (dlg.m_dwFlags & RD_ID)
			{
				pMapEntry->Name += _T("ID_");
				Handler.FirstId = dlg.m_ID;
				Handler.Type |= HANDLER_ID;
				VSParameter* pParam = new VSParameter;
				pParam->pParent = pMapEntry;
				pParam->Name = dlg.m_ID;
				pMapEntry->Parameters.Add(pParam);
			}
			pMapEntry->Name += _T("FILTERED");
		}
		else
		{
			Handler.Message = dlg.m_Message;
			if (dlg.m_dwFlags & RD_NOTIFY)
			{
				Handler.Type = HANDLER_REFLECTION_NOTIFY;
				pMapEntry->Name += _T("NOTIFY");
			}
			if (dlg.m_dwFlags & RD_COMMAND)
			{
				Handler.Type = HANDLER_REFLECTION_COMMAND;
				pMapEntry->Name += _T("COMMAND");
			}

			if (dlg.m_dwFlags & RD_ID)
			{
				Handler.FirstId = dlg.m_ID;
				Handler.Type |= HANDLER_ID;
				VSParameter* pParam = new VSParameter;
				pParam->pParent = pMapEntry;
				pParam->Name = dlg.m_ID;
				pMapEntry->Parameters.Add(pParam);
				if (dlg.m_dwFlags & RD_RANGE)
				{
					Handler.Type |= HANDLER_RANGE;
					Handler.LastId = dlg.m_Range;
					pMapEntry->Name += _T("_RANGE");
					VSParameter* pParam = new VSParameter;
					pParam->pParent = pMapEntry;
					pParam->Name = dlg.m_Range;
					pMapEntry->Parameters.Add(pParam);

					if (dlg.m_dwFlags & RD_CODE)
					{
						Handler.Code = dlg.m_Code;
						Handler.Type |= HANDLER_CODE;
						pMapEntry->Name += _T("_CODE");
						VSParameter* pParam = new VSParameter;
						pParam->pParent = pMapEntry;
						pParam->Name = dlg.m_Code;
						pMapEntry->Parameters.Add(pParam);
					}
				}
				else
				{
					if (dlg.m_dwFlags & RD_CODE)
					{
						Handler.Code = dlg.m_Code;
						Handler.Type |= HANDLER_CODE;
						VSParameter* pParam = new VSParameter;
						pParam->pParent = pMapEntry;
						pParam->Name = dlg.m_Code;
						pMapEntry->Parameters.Add(pParam);
					}
					else
					{
						pMapEntry->Name += _T("_ID");
					}
				}
			}
			else
			{
				if (dlg.m_dwFlags & RD_CODE)
				{
					Handler.Code = dlg.m_Code;
					Handler.Type |= HANDLER_CODE;
					pMapEntry->Name += _T("_CODE");
					
					VSParameter* pParam = new VSParameter;
					pParam->pParent = pMapEntry;
					pParam->Name = dlg.m_Code;
					pMapEntry->Parameters.Add(pParam);
				}
			}
		}
		
		InsertPointMapEntry* pInsPt = new InsertPointMapEntry;
		pInsPt->pElement = pMapEntry;
		pInsPt->pParentMap = m_pMessageMap;
		m_pMessageMap->MapEntries.Add(pMapEntry);
		m_pModifications->InsertPoints.Add(pInsPt);

		SetWinX();
		return true;
	}
	return false;
}

bool CMessageManager::DeleteMap(VSMessageMap* pMap)
{
	CSmartAtlArray<InsertionPoint*>& CurInsPoints = m_pModifications->InsertPoints;
	
	bool bFind = false;
	for (int i = (int)CurInsPoints.GetCount() - 1; i >= 0; i--)
	{
		if (CurInsPoints[i]->Type == INSERT_POINT_HANDLER)
		{
			bool bDelete = false;
			InsertPointHandler* pInsMapEntry = (InsertPointHandler*)CurInsPoints[i];
			if (pInsMapEntry->pParentMap == pMap)
			{
				bDelete = true;
			}
			size_t j;
			for (j = 0; j < pMap->AltMaps.GetCount(); j++)
			{
				if (pInsMapEntry->pParentMap == pMap->AltMaps[j])
				{
					bDelete = true;
					break;
				}
			}
			if (bDelete)
			{
				CurInsPoints.RemoveAt(i);
				delete pInsMapEntry;
				continue;
			}
		}
		if (CurInsPoints[i]->Type == INSERT_POINT_ALT_MAP)
		{
			InsertPointAltMap* pInsAltMap = (InsertPointAltMap*)CurInsPoints[i];
			if (pInsAltMap->pParentMap == pMap)
			{
				CurInsPoints.RemoveAt(i);
				delete pInsAltMap;
				continue;
			}
			if (pInsAltMap->pElement == (VSElement*)pMap)
			{
				CurInsPoints.RemoveAt(i);
				delete pInsAltMap;
				bFind = true;
				continue;
			}
		}
		if (CurInsPoints[i]->Type == INSERT_POINT_MAP)
		{
			InsertPointMap* pInsMap = (InsertPointMap*)CurInsPoints[i];
			if (pInsMap->pElement == (VSElement*)pMap)
			{
				CurInsPoints.RemoveAt(i);
				delete pInsMap;
				bFind = true;
				continue;
			}
		}
		if (CurInsPoints[i]->Type == INSERT_POINT_MAP_ENTRY)
		{
			InsertPointMapEntry* pInsMapEntry = (InsertPointMapEntry*)CurInsPoints[i];
			if (pInsMapEntry->pParentMap == pMap)
			{
				bool bDelete = false;
				InsertPointHandler* pInsMapEntry = (InsertPointHandler*)CurInsPoints[i];
				if (pInsMapEntry->pParentMap == pMap)
				{
					bDelete = true;
				}
				size_t j;
				for (j = 0; j < pMap->AltMaps.GetCount(); j++)
				{
					if (pInsMapEntry->pParentMap == pMap->AltMaps[j])
					{
						bDelete = true;
						break;
					}
				}
				if (bDelete)
				{
					CurInsPoints.RemoveAt(i);
					delete pInsMapEntry;
					continue;
				}
			}
		}
	}
	// search functions for map entries and delete them
	for (size_t i = 0; i < pMap->MapEntries.GetCount(); i++)
	{
		VSFunction* pFunc = (VSFunction*)pMap->MapEntries[i]->pData;
		if (pFunc)
		{
			for (size_t j = 0; j < m_pClass->Functions.GetCount(); j++)
			{
				if (pFunc == m_pClass->Functions[j])
				{
					if ((--pFunc->lParam) == 0)
					{
						m_pClass->Functions.RemoveAt(j);
						if (pFunc->pElement)
						{
							m_pModifications->DeletePoint.Add(pFunc);
						}
						else
						{
							delete pFunc;
						}
						
						break;
					}
				}
			}
		}
	}
	if (m_pMessageMap->pParent->ElementType == EnvDTE::vsCMElementClass)
	{
		//удаляем из класса
		for (size_t i = 0; i < m_pClass->Maps.GetCount(); i++)
		{
			if (m_pClass->Maps[i] == m_pMessageMap)
			{
				m_pClass->Maps.RemoveAt(i);
				break;
			}
		}
	}
	else
	{
		//удаляем из карты сообщений
		VSMessageMap* pParentMap = (VSMessageMap*)m_pMessageMap->pParent;
		for (size_t i = 0; i < pParentMap->AltMaps.GetCount(); i++)
		{
			if (pParentMap->AltMaps[i] == m_pMessageMap)
			{
				pParentMap->AltMaps.RemoveAt(i);

				break;
			}
		}
	}
	if (!bFind)
	{
		m_pModifications->DeletePoint.Add(m_pMessageMap);
	}
	return true;
}

bool CMessageManager::DeleteHandler(HandlerStruct* pHandler)
{
	ATLASSERT(pHandler);

	VSElement* pListEntry = pHandler->pMapEntry;
	CSmartAtlArray<InsertionPoint*>& pts = m_pModifications->InsertPoints;
	size_t i;
	for (i = 0; i < pts.GetCount(); i++)
	{
		if ((pts[i])->pElement == pListEntry)
		{
			break;
		}
	}
	VSFunction* pFunc = NULL;

	if (i != pts.GetCount())
	{
		//это добавленный в эту сессию обработчик
		//удаляем вместе с функцией
		InsertPointHandler* pInsHandler = (InsertPointHandler*)pts[i];
		VSMap* pMap = pInsHandler->pParentMap;
		//pFunc = pInsHandler->pFunction;
		pFunc = pHandler->pFunction;
		delete pInsHandler;
		pts.RemoveAt(i);

		for (size_t j = 0; j < pMap->MapEntries.GetCount(); j++)
		{
			if (pMap->MapEntries[j] == (VSMapEntry*)pListEntry)
			{
				pMap->MapEntries.RemoveAt(j);
			}
		}

		if (pFunc && !(--pFunc->lParam))
		{
			CSmartAtlArray<VSFunction*>& pf = m_pClass->Functions;
			for (size_t j = 0; j < pf.GetCount(); j++)
			{
				if ((pf[j]) == pFunc)
				{
					pf.RemoveAt(j);
					break;
				}
			}
			delete pFunc;
		}
		delete pListEntry;
	}
	else
	{
		//обработчик добавленный ранее
		//чистим функции и MapEntries
		//добавляем в список удаленных компонент
		for (size_t j = 0; j != m_pMessageMap->MapEntries.GetCount(); j++)
		{
			if ((m_pMessageMap->MapEntries[j]) == (VSMapEntry*)pListEntry)
			{
				m_pModifications->DeletePoint.Add(m_pMessageMap->MapEntries[j]);
				m_pMessageMap->MapEntries.RemoveAt(j);
				break;
			}
		}

		CSmartAtlArray<VSFunction*>& pf = m_pClass->Functions;
		VSFunction* pHandlerFunc = pHandler->pFunction;
		if (pHandlerFunc && !(--pHandlerFunc->lParam))
		{
			for (size_t j = 0; j != pf.GetCount(); j++)
			{
				if (pf[j] == pHandlerFunc)
				{
					m_pModifications->DeletePoint.Add(pf[j]);
					pf.RemoveAt(j);
					break;
				}
			}
		}
	}
	m_sHandlerManager.DeleteHandler(pHandler);
	//m_Handlers.DeleteItem(n);
	//SetModified(TRUE);
	return true;
}

bool CMessageManager::AddForwardReflect(CString Name, LPCTSTR lpHeaderFile /* = NULL */)
{
	ATLASSERT(m_pMessageMap);

	CSmartAtlArray<VSElement*>& DelPoints = m_pModifications->DeletePoint;
	for (size_t i = 0; i < DelPoints.GetCount(); i++)
	{
		if (DelPoints[i]->ElementType == EnvDTE::vsCMElementMapEntry &&
			DelPoints[i]->Name == Name)
		{
			VSMessageMap* pMap = (VSMessageMap*)DelPoints[i]->pParent;
			pMap->MapEntries.Add((VSMapEntry*)DelPoints[i]);
			DelPoints.RemoveAt(i);
			return true;
		}
	}

	VSMapEntry* pMapEntry = new VSMapEntry;
	pMapEntry->Name = Name;
	m_pMessageMap->MapEntries.Add(pMapEntry);

	InsertPointMapEntry* pNewMapEntryPoint = new InsertPointMapEntry;
	pNewMapEntryPoint->pElement = pMapEntry;
	pNewMapEntryPoint->pParentMap = m_pMessageMap;
	m_pModifications->InsertPoints.Add(pNewMapEntryPoint);
	if (lpHeaderFile)
		SetHeader(lpHeaderFile);
	return true;
}

bool CMessageManager::DeleteForwardReflect(CString Name)
{
	CSmartAtlArray<InsertionPoint*>& pts = m_pModifications->InsertPoints;
	for (size_t i = 0; i < pts.GetCount(); i++)
	{
		if (pts[i]->pElement->ElementType == EnvDTE::vsCMElementMapEntry && 
			pts[i]->pElement->Name == Name)
		{
			//нашли
			VSMapEntry* pMapEntry = (VSMapEntry*)pts[i]->pElement;
			VSMap* pMap = ((InsertPointMapEntry*)pts[i])->pParentMap;
			delete (InsertPointMapEntry*)pts[i];
			pts.RemoveAt(i);
			for (size_t j = 0; j < pMap->MapEntries.GetCount(); j++)
			{
				if (pMap->MapEntries[j] == pMapEntry)
				{
					pMap->MapEntries.RemoveAt(j);
					break;
				}
			}
			delete pMapEntry;
			return true;
		}
	}

	VSMapEntry* pMapEntry = NULL;
	for (size_t i = 0; i< m_pMessageMap->MapEntries.GetCount(); i++)
	{
		if (m_pMessageMap->MapEntries[i]->Name == Name)
		{
			pMapEntry = m_pMessageMap->MapEntries[i];
			m_pMessageMap->MapEntries.RemoveAt(i);
			break;
		}
	}
	if (pMapEntry)
	{
		m_pModifications->DeletePoint.Add(pMapEntry);
	}
	return true;
}