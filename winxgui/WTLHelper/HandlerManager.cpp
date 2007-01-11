////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	HandlerManager.cpp
// Created:	17.01.2005 9:58
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
#include ".\handlermanager.h"
#include "TextFile.h"
#include "common.h"

bool ParamStruct::LoadParam(CXMLObject* pXMLObject)
{
	ParamName = (LPCTSTR)pXMLObject->GetName();
	if (!pXMLObject->GetAttribute(_T("Type"), ParamType))
		return false;
	if (!pXMLObject->GetText(ParamFunc))
		return false;
	return true;
}

bool ParamStruct::SaveParam(CXMLObject* pXMLObject)
{
	if (pXMLObject->StartObject(ParamName, true)&&
		pXMLObject->SetAttribute(_T("Type"), ParamType) &&
		pXMLObject->SetText(ParamFunc))
		pXMLObject->EndObject();
	{
		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
bool MessageStruct::LoadMessage(CXMLObject* pXMLObject)
{
	if (!pXMLObject->GetAttribute(_T("Type"), Type))
		return false;
	if (!pXMLObject->GetAttribute(_T("IconIndex"), IconIndex))
		IconIndex = -1;
	if ((Type & TYPE_MASK) == ROOT_PLACE)
	{
		if (!pXMLObject->GetAttribute(_T("Name"), Message))
			return false;
	}
	else
	{
		Message = (LPCTSTR)pXMLObject->GetName();
		if (!pXMLObject->GetAttribute(_T("DefFuncName"), DefFuncName))
		{
			return false;
		}
	}
	if (pXMLObject->StartObject(_T("ResWords"), false))
	{
		pResWords = new CSmartAtlArray<CString>;
		for (CXMLObject::CXMLIterator i = pXMLObject->GetFirstChild(); i; i++)
		{
			pResWords->Add((LPCTSTR)i->GetName());
		}
		pXMLObject->EndObject();
	}
	pXMLObject->LoadTag(_T("Body"), Body);
	pXMLObject->LoadTag(_T("Comment"), Comment);
	Comment.Replace(_T("\n"), _T("\r\n"));

	if (pXMLObject->StartObject(_T("Params"), false))
	{
		for (CXMLObject::CXMLIterator i = pXMLObject->GetFirstChild(); i; i++)
		{
			ParamStruct ps;
			ps.LoadParam(&i);
			Params.Add(ps);
		}
		pXMLObject->EndObject();
	}
	if (pXMLObject->StartObject(_T("Messages"), false))
	{
		for (CXMLObject::CXMLIterator i = pXMLObject->GetFirstChild(); i; i++)
		{
			MessageStruct* pms = new MessageStruct;
			pms->pResWords = pResWords;
			if (pms->LoadMessage(&i))
			{
				Children.Add(pms);
			}
			else
			{
				delete pms;
			}
		}
		pXMLObject->EndObject();
	}
	int StdType = Type & FLAGS_MASK;
	
	switch(StdType) 
	{
	case WINDOWS_ROOT:
		{
			MessageStruct* pMes = new MessageStruct;
			pMes->Message = _T("Custom windows message");
			pMes->Type = CUSTOM_MESSAGE_HANDLER | NO_CRACK_MESSAGES | CUSTOM_MESSAGE;
			Children.Add(pMes);

			pMes = new MessageStruct;
			pMes->Message = _T("Custom reflection handler");
			pMes->Type = CUSTOM_REFLECTION_HANDLER | CUSTOM_MESSAGE | REFLECTION_MESSAGE;
			Children.Add(pMes);
		}
		break;
	case COMMAND_ROOT:
		{
			MessageStruct* pMes = new MessageStruct;
			pMes->Message = _T("Custom command message");
			pMes->Type = CUSTOM_COMMAND_HANDLER | CUSTOM_MESSAGE;
			Children.Add(pMes);

			pMes = new MessageStruct;
			pMes->Message = _T("Custom command reflection handler");
			pMes->Type = CUSTOM_COMMAND_REFLECTION_HANDLER | CUSTOM_MESSAGE | REFLECTION_MESSAGE;
			Children.Add(pMes);
		}
		break;
	case NOTIFY_ROOT:
		{
			MessageStruct* pMes = new MessageStruct;
			pMes->Message = _T("Custom notify message");
			pMes->Type = CUSTOM_NOTIFY_HANDLER | CUSTOM_MESSAGE;
			Children.Add(pMes);

			pMes = new MessageStruct;
			pMes->Message = _T("Custom notify reflection handler");
			pMes->Type = CUSTOM_NOTIFY_REFLECTION_HANDLER | CUSTOM_MESSAGE | REFLECTION_MESSAGE;
			Children.Add(pMes);
		}
		break;
	}
	return true;
}

bool MessageStruct::SaveMessage(CXMLObject* pXMLObject)
{
	int _type = (Type & TYPE_MASK);
	if (_type == CUSTOM_MESSAGE_HANDLER ||
		_type == CUSTOM_COMMAND_HANDLER ||
		_type == CUSTOM_NOTIFY_HANDLER)
		return true;
	if (IconIndex != -1)
		pXMLObject->SetAttribute(_T("IconIndex"), IconIndex);

	if ((Type & TYPE_MASK) == ROOT_PLACE)
	{
		if (!pXMLObject->StartObject(_T("MessageTree"), true))
		{
			return false;
		}
		if (!pXMLObject->SetAttribute(_T("Name"), Message))
		{
			pXMLObject->EndObject();
			return false;
		}
	}
	else
	{
		if (!pXMLObject->StartObject(Message, true))
			return false;
		if (!pXMLObject->SetAttribute(_T("DefFuncName"), DefFuncName))
		{
			pXMLObject->EndObject();
			return false;
		}
	}

	if (!pXMLObject->SetAttribute(_T("Type"), Type))
	{
		pXMLObject->EndObject();
		return false;
	}
	size_t Count;
	if (Type & CONTAIN_RESOURCE_STRINGS && (Count = pResWords->GetCount()))
	{
		if (pXMLObject->StartObject(_T("ResWords"), true))
		{
			for (size_t i = 0; i < Count; i++)
			{
				pXMLObject->SaveTag(pResWords->GetAt(i), (LPCTSTR)NULL);
			}
			pXMLObject->EndObject();
		}
	}
	if (!Body.IsEmpty())
	{
		pXMLObject->SaveTag(_T("Body"), Body);
	}
	if (!Comment.IsEmpty())
	{
		pXMLObject->SaveTag(_T("Comment"), Comment);
	}
	if (Count = Params.GetCount())
	{
		if (pXMLObject->StartObject(_T("Params"), true))
		{
			for (size_t  i = 0; i < Count; i++)
			{
				Params[i].SaveParam(pXMLObject);
			}
			pXMLObject->EndObject();
		}
	}
	if (Count = Children.GetCount())
	{
		if (pXMLObject->StartObject(_T("Messages"), true))
		{
			for (size_t i = 0; i < Count; i++)
			{
				Children[i]->SaveMessage(pXMLObject);
			}
			pXMLObject->EndObject();
		}
	}
	pXMLObject->EndObject();
	return true;
}

//////////////////////////////////////////////////////////////////////////

CHandlerManager::CHandlerManager(void) : m_pRootMessage(NULL), 
m_pFunctions(NULL), m_bReflectNotifications(false), m_bForwardNotifications(false), 
m_bExactEqual(false), m_bReflectNotificationsEx(false), m_bDefReflectHandler(false)
{
}

CHandlerManager::~CHandlerManager(void)
{
	Destroy();
}

void CHandlerManager::Reset()
{
	m_bReflectNotifications = false;
	m_bReflectNotificationsEx = false;
	m_bForwardNotifications = false;
	m_bDefReflectHandler = false;
}

void CHandlerManager::Destroy()
{
	if (m_pRootMessage)
	{
		DeleteMessage(m_pRootMessage);
		m_pRootMessage = NULL;
	}
	for (size_t i = 0; i < m_Handlers.GetCount(); i++)
	{
		delete m_Handlers[i];
	}
	m_SynonymMap.RemoveAll();
	m_Handlers.RemoveAll();
}

void CHandlerManager::DeleteMessage(MessageStruct* pMes)
{
	if (pMes->pResWords && ((pMes->Type & FLAGS_MASK) & CONTAIN_RESOURCE_STRINGS))
	{
		pMes->pResWords->RemoveAll();
		delete pMes->pResWords;
	}
	if ((pMes->Type & TYPE_MASK) == ROOT_PLACE)
	{
		for (size_t i = 0; i < pMes->Children.GetCount(); i++)
		{
			DeleteMessage(pMes->Children[i]);
		}
	}
	delete pMes;
}

bool CHandlerManager::LoadSettings(CXMLObject* pArchive, LPCTSTR lpObjectName)
{
	if (m_pRootMessage)
		return true;

	bool bRes = true;

	if (pArchive->StartObject(lpObjectName, false))
	{
		if (pArchive->StartObject(_T("MessageTree"), false))
		{
			m_pRootMessage = new MessageStruct;
			m_pRootMessage->LoadMessage(pArchive);
			pArchive->EndObject();//"Messages"
		}
		else
			bRes = false;

		if (pArchive->StartObject(_T("SynonymMap"), false))
		{
			for (CXMLObject::CXMLIterator i = pArchive->GetFirstChild(); i; i++)
			{
				CString Name = (LPCTSTR)i->GetName();
				CSmartAtlArray<CString> Strings;
				for (CXMLObject::CXMLIterator j = i->GetFirstChild(); j; j++)
				{
					CString str;
					j->GetText(str);
					Strings.Add(str);
				}
				m_SynonymMap.SetAt(Name, Strings);
			}
			pArchive->EndObject();//"SynonymMap"
		}
		else
			bRes = false;
		pArchive->EndObject();//lpObjectName			
	}
	else
		bRes = false;
	return bRes;
}

BOOL CHandlerManager::AddCrackMessage(VSMapEntry* pMapEntry, HandlerStruct* pHandler, CString RestPart)
{
	if (pMapEntry->Parameters.GetCount() == 1)
	{
		pHandler->Message = RestPart;
		pHandler->Type = HANDLER_TYPE_CRACK_MESSAGE;
		// HACK: ищем только по имени
		pHandler->HandlerName = pMapEntry->Parameters[0]->Name;
		for (size_t i = 0; i < m_pFunctions->GetCount(); i++)
		{
			if (m_pFunctions->GetAt(i)->Name == pHandler->HandlerName)
			{
				//нашли
				pHandler->pFunction = m_pFunctions->GetAt(i);
				pHandler->pFunction->lParam++;
				pMapEntry->pData = pHandler->pFunction;
				size_t Pos = m_Handlers.Add(pHandler);
				m_FuncMap[i] = Pos;
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CHandlerManager::AddWindowsMessage(VSMapEntry* pMapEntry, HandlerStruct* pHandler, CString RestPart)
{
	if (pMapEntry->Parameters.GetCount() == 2)
	{
		pHandler->Type |= HANDLER_TYPE_MESSAGE;
		pHandler->Message = pMapEntry->Parameters[0]->Name;
		pHandler->HandlerName = pMapEntry->Parameters[1]->Name;
		for (size_t i = 0; i < m_pFunctions->GetCount(); i++)
		{
			if (m_pFunctions->GetAt(i)->Name == pHandler->HandlerName)
			{
				//нашли
				VSFunction* pFunc = m_pFunctions->GetAt(i);
				size_t NeedParameters = 4;
				if (pHandler->Type & HANDLER_EX)
					NeedParameters--;
				if (pFunc->Parameters.GetCount() == NeedParameters)
				{
					bool bExact = true;
					if (m_bExactEqual)
					{
						// TODO: проверить на совпадение типов
						//установаить bExact в false, если не совпадает
					}
					if (bExact)
					{
						pHandler->pFunction = m_pFunctions->GetAt(i);
						pHandler->pFunction->lParam++;
						pMapEntry->pData = pHandler->pFunction;
						size_t Pos = m_Handlers.Add(pHandler);
						m_FuncMap[i] = Pos;
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}

BOOL CHandlerManager::AddCommandNotifyMessage(VSMapEntry* pMapEntry, HandlerStruct* pHandler, CString RestPart)
{
	int Sep = RestPart.Find(_T('_'));
	CString LeftPart;
	if (Sep != -1)
	{
		LeftPart = RestPart.Left(Sep);
		RestPart = RestPart.Mid(Sep + 1);
	}
	else
	{
		return FALSE;
	}

	if (LeftPart == _T("COMMAND"))
	{
		pHandler->Type |= HANDLER_TYPE_COMMAND_MESSAGE;
		pHandler->Message = _T("WM_COMMAND");
	}
	if (LeftPart == _T("NOTIFY"))
	{
		pHandler->Type |= HANDLER_TYPE_NOTIFY_MESSAGE;
		pHandler->Message = _T("WM_NOTIFY");
	}
	//RestPart.Delete(0, Sep + 1);
	Sep = RestPart.Find(_T('_'));

	if (Sep == -1)
	{
		if ((RestPart == _T("HANDLER")) && (pMapEntry->Parameters.GetCount() == 3))
		{
			pHandler->Type |= HANDLER_ID | HANDLER_CODE;
			pHandler->FirstId = pMapEntry->Parameters[0]->Name;
			pHandler->Code = pMapEntry->Parameters[1]->Name;
			pHandler->HandlerName = pMapEntry->Parameters[2]->Name;
		}
	}
	else
	{
		LeftPart = RestPart.Left(Sep);
		RestPart.Delete(0, Sep + 1);
		if (LeftPart == _T("RANGE"))
		{
			if (RestPart == _T("HANDLER") && pMapEntry->Parameters.GetCount() == 3)
			{
				pHandler->Type |= HANDLER_RANGE | HANDLER_ID;
				pHandler->FirstId = pMapEntry->Parameters[0]->Name;
				pHandler->LastId = pMapEntry->Parameters[1]->Name;
				pHandler->HandlerName = pMapEntry->Parameters[2]->Name;
			}
			if (RestPart == _T("CODE_HANDLER") && pMapEntry->Parameters.GetCount() == 4)
			{
				pHandler->Type |= HANDLER_RANGE | HANDLER_ID | HANDLER_CODE;
				pHandler->FirstId = pMapEntry->Parameters[0]->Name;
				pHandler->LastId = pMapEntry->Parameters[1]->Name;
				pHandler->Code = pMapEntry->Parameters[2]->Name;
				pHandler->HandlerName = pMapEntry->Parameters[3]->Name;
			}
		}
		if (LeftPart == _T("CODE"))
		{
			if (RestPart == _T("HANDLER") && pMapEntry->Parameters.GetCount() == 2)
			{
				pHandler->Type |= HANDLER_CODE;
				pHandler->Code = pMapEntry->Parameters[0]->Name;
				pHandler->HandlerName = pMapEntry->Parameters[1]->Name;
			}
		}
		if (LeftPart == _T("ID"))
		{
			if (RestPart == _T("HANDLER") && pMapEntry->Parameters.GetCount() == 2)
			{
				pHandler->Type |= HANDLER_ID;
				pHandler->FirstId = pMapEntry->Parameters[0]->Name;
				pHandler->HandlerName = pMapEntry->Parameters[1]->Name;
			}
		}
	}

	if (!pHandler->HandlerName.IsEmpty())
	{
		for (size_t i = 0; i < m_pFunctions->GetCount(); i++)
		{
			if (m_pFunctions->GetAt(i)->Name == pHandler->HandlerName)
			{
				//нашли
				VSFunction* pFunc = m_pFunctions->GetAt(i);
				size_t NeedParameters;
				if (pHandler->Type & HANDLER_TYPE_COMMAND_MESSAGE)
				{
					if (pHandler->Type & HANDLER_EX)
						NeedParameters = 3;
					else
						NeedParameters = 4;
				}
				if (pHandler->Type & HANDLER_TYPE_NOTIFY_MESSAGE)
				{
					if (pHandler->Type & HANDLER_EX)
						NeedParameters = 1;
					else
						NeedParameters = 3;
				}
				
				if (pFunc->Parameters.GetCount() == NeedParameters)
				{
					bool bExact = true;
					if (m_bExactEqual)
					{
						// TODO: проверить на совпадение типов
						//установаить bExact в false, если не совпадает
					}
					if (bExact)
					{
						pHandler->pFunction = m_pFunctions->GetAt(i);
						pHandler->pFunction->lParam++;
						pMapEntry->pData = pHandler->pFunction;
						size_t Pos = m_Handlers.Add(pHandler);
						m_FuncMap[i] = Pos;
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}

BOOL CHandlerManager::AddReflection(VSMapEntry* pMapEntry, HandlerStruct* pHandler, CString RestPart)
{
	pHandler->pMapEntry = pMapEntry;
	pHandler->pFunction = NULL;

	int Sep = RestPart.Find(_T('_'));
	CString LeftPart;
	if (Sep != -1)
	{
		LeftPart = RestPart.Left(Sep);
		RestPart = RestPart.Mid(Sep + 1);
	}
	else
	{
		LeftPart = RestPart;
		RestPart.Empty();
	}
	pHandler->HandlerName = _T("Reflection Handler");
	if (LeftPart == _T("NOTIFICATIONS"))
	{
		pHandler->Type = HANDLER_REFLECTION_MESSAGE;
		return AddMessageReflection(pMapEntry, pHandler, RestPart);
	} else if (LeftPart == _T("COMMAND"))
	{
		pHandler->Message = _T("WM_COMMAND");
		pHandler->Type |= HANDLER_REFLECTION_COMMAND;
		return AddCommandNotifyReflection(pMapEntry, pHandler, RestPart);
	} else if (LeftPart == _T("NOTIFY"))
	{
		pHandler->Message = _T("WM_NOTIFY");
		pHandler->Type |= HANDLER_REFLECTION_NOTIFY;
		return AddCommandNotifyReflection(pMapEntry, pHandler, RestPart);
	}

	return FALSE;
}

BOOL CHandlerManager::AddCommandNotifyReflection(VSMapEntry* pMapEntry, HandlerStruct* pHandler, CString RestPart)
{
	if (RestPart.IsEmpty())
	{
		if (pMapEntry->Parameters.GetCount() == 2)
		{
			pHandler->Code = pMapEntry->Parameters[1]->Name;
			pHandler->FirstId = pMapEntry->Parameters[0]->Name;
			pHandler->Type |= HANDLER_CODE | HANDLER_ID;
			return TRUE;
		}
		else
			return FALSE;
	} 
	else 
	{
		int Sep = RestPart.Find(_T('_'));
		CString LeftPart;
		if (Sep != -1)
		{
			LeftPart = RestPart.Left(Sep);
			RestPart = RestPart.Mid(Sep + 1);
		}
		else
		{
			LeftPart = RestPart;
			RestPart.Empty();
		}

		if (LeftPart == _T("RANGE"))
		{
			if (RestPart.IsEmpty())
			{
				if (pMapEntry->Parameters.GetCount() == 2)
				{
					pHandler->FirstId = pMapEntry->Parameters[0]->Name;
					pHandler->LastId = pMapEntry->Parameters[1]->Name;
					pHandler->Type |= HANDLER_ID | HANDLER_RANGE;
					return TRUE;
				}
				else
					return FALSE;
			}
			else
			{
				if (RestPart == _T("CODE"))
				{
					if (pMapEntry->Parameters.GetCount() == 3)
					{
						pHandler->FirstId = pMapEntry->Parameters[0]->Name;
						pHandler->LastId = pMapEntry->Parameters[1]->Name;
						pHandler->Code = pMapEntry->Parameters[2]->Name;
						pHandler->Type |= HANDLER_ID | HANDLER_RANGE | HANDLER_CODE;
						return TRUE;
					}
					else
						return FALSE;
				}
				else
					return FALSE;
			}
		}
		if (LeftPart == _T("ID"))
		{
			if (pMapEntry->Parameters.GetCount() == 1)
			{
				pHandler->FirstId = pMapEntry->Parameters[0]->Name;
				pHandler->Type |= HANDLER_ID;
				return TRUE;
			}
			else
				return FALSE;
		}
		if (LeftPart == _T("CODE"))
		{
			if (pMapEntry->Parameters.GetCount() == 1)
			{
				pHandler->Code = pMapEntry->Parameters[0]->Name;
				pHandler->Type |= HANDLER_CODE;
				return TRUE;
			}
			else
				return FALSE;
		}
	}
	return FALSE;
}

BOOL CHandlerManager::AddMessageReflection(VSMapEntry* pMapEntry, HandlerStruct* pHandler, CString RestPart)
{
	int Sep = RestPart.Find(_T('_'));
	CString LeftPart;
	if (Sep != -1)
	{
		LeftPart = RestPart.Left(Sep);
	}
	else
	{
		return FALSE;
	}
	int UsedParams = 0;
	if (LeftPart == _T("MSG"))
	{
		RestPart = RestPart.Mid(Sep + 1);
		if (pMapEntry->Parameters.GetCount() >= 1)
		{
			pHandler->Message = pMapEntry->Parameters[0]->Name;
			UsedParams++;
		}
		if (RestPart == _T("FILTERED"))
		{
			if (pMapEntry->Parameters.GetCount() - UsedParams == 0)
				return TRUE;
			else
				return FALSE;
		}
		Sep = RestPart.Find(_T('_'));
		if (Sep != -1)
		{
			LeftPart = RestPart.Left(Sep);
			//RestPart = RestPart.Mid(Sep + 1);
		}
		else
			return FALSE;
	}
	RestPart = RestPart.Mid(Sep + 1);
	if (LeftPart == _T("ID"))
	{
		if (pMapEntry->Parameters.GetCount() == UsedParams + 1)
		{
			pHandler->FirstId = pMapEntry->Parameters[UsedParams]->Name;
			pHandler->Type |= HANDLER_ID;
			if (RestPart == _T("FILTERED"))
				return TRUE;
			else
				return FALSE;
		}
		else
			return FALSE;
	}
	if (LeftPart == _T("HWND"))
	{
		if (pMapEntry->Parameters.GetCount() == UsedParams + 1)
		{
			pHandler->HWND = pMapEntry->Parameters[UsedParams]->Name;
			pHandler->Type |= HANDLER_HWND;
			if (RestPart == _T("FILTERED"))
				return TRUE;
			else
				return FALSE;
		}
		else
			return FALSE;
	}
	return FALSE;
}

void CHandlerManager::FindSimilarCommandFunctions(CAtlArray<HandlerFunction>& Handlers)
{
	static CString Params[] = {_T("WORD"), _T("WORD"), _T("HWND")};
	static const int CountParams = 3;
	static CString HandledStr = _T("BOOL &");
	for (size_t i = 0; i < m_pFunctions->GetCount(); i++)
	{
		VSFunction* pFunc = m_pFunctions->GetAt(i);
		size_t ParamCount = pFunc->Parameters.GetCount();
		if (ParamCount == CountParams || ParamCount == (CountParams + 1))
		{
			bool bCommand = true;
			for (size_t j = 0; j < CountParams; j++)
			{
				if (pFunc->Parameters[j]->Type != Params[j])
				{
					bCommand = false;
					CSmartAtlArray<CString> Synon;
					if (m_SynonymMap.Lookup(Params[j], Synon))
					{
						for (size_t k = 0; k < Synon.GetCount(); k++)
						{
							if (Synon[k] == pFunc->Parameters[j]->Type)
							{
								bCommand = true;
								break;
							}
						}
					}
					if (!bCommand)
						break;
				}
			}
			if (bCommand)
			{
				if (ParamCount == (CountParams + 1))
				{
					if (pFunc->Parameters[CountParams]->Type == HandledStr)
					{
						HandlerFunction hf;
						hf.pFunc = pFunc;
						hf.Type = HANDLER_TYPE_COMMAND_MESSAGE;
						Handlers.Add(hf);
					}
				}
				if (ParamCount == CountParams)
				{
					HandlerFunction hf;
					hf.pFunc = pFunc;
					hf.Type = HANDLER_TYPE_COMMAND_MESSAGE | HANDLER_EX;
					Handlers.Add(hf);
				}
			}
		}
	}
}

void CHandlerManager::FindSimilarNotifyFunctions(CAtlArray<HandlerFunction>& Handlers)
{
	static CString Params[] = {_T("int"), _T("LPNMHDR")};
	static const int CountParams = 2;
	static CString HandledStr = _T("BOOL &");
	for (size_t i = 0; i < m_pFunctions->GetCount(); i++)
	{
		VSFunction* pFunc = m_pFunctions->GetAt(i);
		size_t ParamCount = pFunc->Parameters.GetCount();
		if (ParamCount == CountParams || ParamCount == (CountParams + 1))
		{
			bool bCommand = true;
			for (size_t j = 0; j < CountParams; j++)
			{
				if (pFunc->Parameters[j]->Type != Params[j])
				{
					bCommand = false;
					CSmartAtlArray<CString> Synon;
					if (m_SynonymMap.Lookup(Params[j], Synon))
					{
						for (size_t k = 0; k < Synon.GetCount(); k++)
						{
							if (Synon[k] == pFunc->Parameters[j]->Type)
							{
								bCommand = true;
								break;
							}
						}
					}
					if (!bCommand)
						break;
				}
			}
			if (bCommand)
			{
				if (ParamCount == (CountParams + 1))
				{
					if (pFunc->Parameters[CountParams]->Type == HandledStr)
					{
						HandlerFunction hf;
						hf.pFunc = pFunc;
						hf.Type = HANDLER_TYPE_NOTIFY_MESSAGE;
						Handlers.Add(hf);
					}
				}
				if (ParamCount == CountParams)
				{
					HandlerFunction hf;
					hf.pFunc = pFunc;
					hf.Type = HANDLER_TYPE_NOTIFY_MESSAGE | HANDLER_EX;
					Handlers.Add(hf);
				}
			}
		}
	}
}

void CHandlerManager::FindSimilarMessageFunctions(CAtlArray<HandlerFunction>& Handlers)
{
	static CString Params[] = {_T("UINT"), _T("WPARAM"), _T("LPARAM")};
	static const int CountParams = 3;
	static CString HandledStr = _T("BOOL &");
	for (size_t i = 0; i < m_pFunctions->GetCount(); i++)
	{
		VSFunction* pFunc = m_pFunctions->GetAt(i);
		size_t ParamCount = pFunc->Parameters.GetCount();
		if (ParamCount == CountParams || ParamCount == (CountParams + 1))
		{
			bool bCommand = true;
			for (size_t j = 0; j < CountParams; j++)
			{
				if (pFunc->Parameters[j]->Type != Params[j])
				{
					bCommand = false;
					CSmartAtlArray<CString> Synon;
					if (m_SynonymMap.Lookup(Params[j], Synon))
					{
						for (size_t k = 0; k < Synon.GetCount(); k++)
						{
							if (Synon[k] == pFunc->Parameters[j]->Type)
							{
								bCommand = true;
								break;
							}
						}
					}
					if (!bCommand)
						break;
				}
			}
			if (bCommand)
			{
				if (ParamCount == (CountParams + 1))
				{
					if (pFunc->Parameters[CountParams]->Type == HandledStr)
					{
						HandlerFunction hf;
						hf.pFunc = pFunc;
						hf.Type = HANDLER_TYPE_MESSAGE;
						Handlers.Add(hf);
					}
				}
				if (ParamCount == CountParams)
				{
					HandlerFunction hf;
					hf.pFunc = pFunc;
					hf.Type = HANDLER_TYPE_MESSAGE | HANDLER_EX;
					Handlers.Add(hf);
				}
			}
		}
	}
}

void CHandlerManager::FindSimilarCrackMessageFunctions(MessageStruct* pMes, CAtlArray<HandlerFunction>& Handlers)
{
	for (size_t i = 0; i < m_pFunctions->GetCount(); i++)
	{
		VSFunction* pFunc = m_pFunctions->GetAt(i);
		if (pMes->Params.GetCount() == pFunc->Parameters.GetCount())
		{
			size_t Count = pMes->Params.GetCount();
			bool bMessage = true;
			for (size_t j = 0; j < Count; j++)
			{
				if (pMes->Params[j].ParamType != pFunc->Parameters[j]->Type)
				{
					CSmartAtlArray<CString> Synon;
					bMessage = false;
					if (m_SynonymMap.Lookup(pMes->Params[j].ParamType, Synon))
					{
						for (size_t k = 0; k < Synon.GetCount(); k++)
						{
							if (Synon[k] == pFunc->Parameters[j]->Type)
							{
								bMessage = true;
								break;
							}
						}
					}
					if (!bMessage)
					{
						break;
					}
				}
			}
			if (bMessage)
			{
				HandlerFunction hf;
				hf.pFunc = pFunc;
				hf.Type = HANDLER_TYPE_CRACK_MESSAGE;
				Handlers.Add(hf);
			}
		}
	}
}

void CHandlerManager::FindSimilarFunctions(MessageStruct* pMes, CAtlArray<HandlerFunction>& Handlers)
{
	switch(pMes->Type & TYPE_MASK) 
	{
	case STD_COMMAND_HANDLER:
		FindSimilarCommandFunctions(Handlers);
		break;
	case STD_NOTIFY_HANDLER:
		FindSimilarNotifyFunctions(Handlers);
		break;
	case STD_MESSAGE_HANDLER:
		{
			FindSimilarMessageFunctions(Handlers);
			FindSimilarCrackMessageFunctions(pMes, Handlers);
		}
		break;
	}
}

HandlerStruct* CHandlerManager::AddMapEntry(VSMapEntry* pMapEntry)
{
	CString Name = pMapEntry->Name;
	
	if (Name == _T("REFLECT_NOTIFICATIONS"))
	{
		m_bReflectNotifications = true;
		return NULL;
	}
	if (Name == _T("FORWARD_NOTIFICATIONS"))
	{
		m_bForwardNotifications = true;
		return NULL;
	}
	if (Name == _T("REFLECT_NOTIFICATIONS_EX"))
	{
		m_bReflectNotifications = true;
		m_bReflectNotificationsEx = true;
		return NULL;
	}
	
	if (Name == _T("DEFAULT_REFLECTION_HANDLER"))
	{
		m_bDefReflectHandler = true;
		return NULL;
	}
	if (Name == _T("CHAIN_MSG_MAP"))
	{
		m_Chains.Add(pMapEntry->Parameters[0]->Name);
		return NULL;
	}
	
	HandlerStruct* pHandler = new HandlerStruct;
	pHandler->Type = 0;
	if (Name.Right(3) == _T("_EX"))
	{
		pHandler->Type |= HANDLER_EX;
		Name.Delete(Name.GetLength() - 3, 3);
	}
	int Sep = Name.Find(_T('_'));
	if (Sep == -1)
	{
		//неизвестная ошибка
		delete pHandler;
		return NULL;
	}
	
	pHandler->pFunction = NULL;
	pHandler->pMapEntry = pMapEntry;

	CString FirstPart = Name.Left(Sep);
	BOOL bRes = FALSE;
	if (FirstPart == _T("REFLECTED"))
	{
		pHandler->Type |= HANDLER_REFLECTED;
		Name.Delete(0, Sep + 1);
		bRes = AddCommandNotifyMessage(pMapEntry, pHandler, Name);
	}
	if (FirstPart == _T("REFLECT"))
	{
		Name.Delete(0, Sep + 1);
		bRes = AddReflection(pMapEntry, pHandler, Name);
	}
	if (FirstPart == _T("COMMAND") || FirstPart == _T("NOTIFY"))
	{
		bRes = AddCommandNotifyMessage(pMapEntry, pHandler, Name);
	}
	if (FirstPart == _T("MESSAGE"))
	{
		bRes = AddWindowsMessage(pMapEntry, pHandler, Name);
	}
	if (FirstPart == _T("MSG"))
	{
		Name.Delete(0, Sep + 1);
		bRes = AddCrackMessage(pMapEntry, pHandler, Name);
	}
	if (bRes)
	{
		return pHandler;
	}
	else
	{
		delete pHandler;
		return NULL;
	}
}

MessageStruct* CHandlerManager::GetRootMessage()
{
	return m_pRootMessage;
}

MessageStruct* CHandlerManager::FindMessageStruct(MessageStruct* pRoot, CString MessageName, CString SubMessageName)
{
	int MesType = STD_MESSAGE_HANDLER;
	CString Name;
	if (MessageName == _T("WM_COMMAND") && !SubMessageName.IsEmpty())
	{
		MesType = STD_COMMAND_HANDLER;
		Name = SubMessageName;
	}
	else
		if (MessageName == _T("WM_NOTIFY") && !SubMessageName.IsEmpty())
		{
			MesType = STD_NOTIFY_HANDLER;
			Name = SubMessageName;
		}
		else
			Name = MessageName;

	for (size_t i = 0; i <pRoot->Children.GetCount(); i++)
	{
		int Type = pRoot->Children[i]->Type & TYPE_MASK;
		if (Type == ROOT_PLACE)
		{
			MessageStruct* pStuct = FindMessageStruct(pRoot->Children[i], MessageName, SubMessageName);
			if (pStuct)
				return pStuct;
		}
		else
		{
			if ((Type == MesType) &&
				(pRoot->Children[i]->Message == Name))
				return pRoot->Children[i];
		}
	}
	return NULL;
}

MessageStruct* CHandlerManager::FindMessageStruct(CString MessageName, CString SubMessageName /* = CString() */)
{
	return FindMessageStruct(m_pRootMessage, MessageName, SubMessageName);
}

void CHandlerManager::AddMessagesFromNode(MessageStruct* pMes, CAtlArray<CString>& StringCodes)
{
	for (size_t i = 0; i < pMes->Children.GetCount(); ++i)
	{
		int Type = pMes->Children[i]->Type & TYPE_MASK;
		if (Type == ROOT_PLACE)
		{
			AddMessagesFromNode(pMes->Children[i], StringCodes);
		}
		else
		{
			if (!(pMes->Children[i]->Type & (REFLECTION_MESSAGE | CUSTOM_MESSAGE)))
				StringCodes.Add(pMes->Children[i]->Message);
		}
	}
}

void CHandlerManager::Init(CAtlArray<VSFunction*>* pFunctions)
{
	Reset();
	m_pFunctions = pFunctions;
	m_FuncMap.SetCount(pFunctions->GetCount());
	m_Chains.RemoveAll();
	for (size_t i = 0; i < m_Handlers.GetCount(); i++)
	{
		delete m_Handlers[i];
	}
	m_Handlers.RemoveAll();

	for (size_t i = 0; i < m_FuncMap.GetCount(); i++)
	{
		m_FuncMap[i] = -1;
		m_pFunctions->GetAt(i)->lParam = 0;
	}
}

bool CHandlerManager::IsHandlerExist(MessageStruct* pMes, VSMessageMap* pMap)
{
	if ((pMes->Type & TYPE_MASK) != STD_MESSAGE_HANDLER)
	{
		return false;
	}
	for (size_t i = 0; i < m_Handlers.GetCount(); i++)
	{
		if (m_Handlers[i]->Type & (HANDLER_TYPE_CRACK_MESSAGE | HANDLER_TYPE_MESSAGE))
		{
			if (m_Handlers[i]->Message == pMes->Message)
			{
				if (m_Handlers[i]->pMapEntry->pParent == pMap || pMap == NULL)
					return true;
			}
		}
	}
	return false;
}

HandlerStruct* CHandlerManager::IsHandler(int iFunction)
{
	size_t iHandler = m_FuncMap[iFunction];
	if (iHandler != -1)
	{
		return m_Handlers[iHandler];
	}
	return NULL;
}

HandlerStruct* CHandlerManager::IsHandler(VSFunction* pFunc)
{
	for (size_t i = 0; i < m_pFunctions->GetCount(); i++)
	{
		if ((*m_pFunctions)[i] == pFunc)
		{
			return IsHandler((int)i);
		}
	}
	return NULL;
}

VSFunction* CHandlerManager::GetFunctionByMapEntry(VSMapEntry* pMapEntry)
{
	for (size_t i = 0; i < m_Handlers.GetCount(); i++)
	{
		if (m_Handlers[i]->pMapEntry == pMapEntry)
			return m_Handlers[i]->pFunction;
	}
	return NULL;
}

HandlerStruct* CHandlerManager::GetHandler(VSMapEntry* pMapEntry)
{
	for (size_t i = 0; i < m_Handlers.GetCount(); i++)
	{
		if (m_Handlers[i]->pMapEntry == pMapEntry)
			return m_Handlers[i];
	}
	return NULL;
}

HandlerStruct* CHandlerManager::AddHandler(HandlerStruct* pHandler)
{
	HandlerStruct* pNewHandler = new HandlerStruct(*pHandler);
	if (pHandler->pFunction)
	{
		pNewHandler->pFunction->lParam++;
	}
	m_Handlers.Add(pNewHandler);
	return pNewHandler;
}

void CHandlerManager::GetHandlerFunctions(CAtlArray<HandlerFunction>& Handlers, int TypeMask)
{
	for (size_t i = 0; i < m_Handlers.GetCount(); i++)
	{
		if ((m_Handlers[i]->Type & TypeMask) == TypeMask)
		{
			bool bFind = false;
			for (size_t j = 0; j < Handlers.GetCount(); j++)
			{
				if (Handlers[j].pFunc == m_Handlers[i]->pFunction)
				{
					bFind = true;
					break;
				}
			}
			if (!bFind)
			{
				HandlerFunction hf;
				hf.pFunc = m_Handlers[i]->pFunction;
				hf.Type = m_Handlers[i]->Type;
				Handlers.Add(hf);
			}
		}
	}
}

void CHandlerManager::DeleteHandler(HandlerStruct* pHandler)
{
	for (size_t i = 0; i < m_Handlers.GetCount(); i++)
	{
		if (m_Handlers[i] == pHandler)
		{
			m_Handlers.RemoveAt(i);
			delete pHandler;
			break;
		}
	}
}

bool CHandlerManager::FindCommandMessages(CAtlArray<CString>& StringCodes)
{
	for (size_t i = 0; i < m_pRootMessage->Children.GetCount(); ++i)
	{
		if (m_pRootMessage->Children[i]->Type & COMMAND_ROOT)
		{
			AddMessagesFromNode(m_pRootMessage->Children[i], StringCodes);
		}
	}
	return true;
}

bool CHandlerManager::FindNotifyMessages(CAtlArray<CString>& StringCodes)
{
	for (size_t i = 0; i < m_pRootMessage->Children.GetCount(); ++i)
	{
		if (m_pRootMessage->Children[i]->Type & NOTIFY_ROOT)
		{
			AddMessagesFromNode(m_pRootMessage->Children[i], StringCodes);
		}
	}
	return true;
}