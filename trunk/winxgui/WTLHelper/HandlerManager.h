////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	HandlerManager.h
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

#pragma once

#include "VSElements.h"
#include "XMLSettingsArchive.h"

#define ROOT_PLACE							0
#define STD_MESSAGE_HANDLER					1
#define STD_COMMAND_HANDLER					2
#define STD_NOTIFY_HANDLER					3
#define EX_MESSAGE_HANDLER					4
#define STD_COMMAND_ID_HANDLER				5
#define STD_COMMAND_CODE_HANDLER			6
#define STD_NOTIFY_ID_HANDLER				7
#define STD_NOTIFY_CODE_HANDLER				8
#define CUSTOM_MESSAGE_HANDLER				9
#define CUSTOM_COMMAND_HANDLER				10
#define CUSTOM_NOTIFY_HANDLER				11
#define RANGE_COMMAND_HANDLER				12
#define RANGE_COMMAND_CODE_HANDLER			13
#define RANGE_NOTIFY_HANDLER				14
#define RANGE_NOTIFY_CODE_HANDLER			15
#define CUSTOM_REFLECTION_HANDLER			16
#define CUSTOM_COMMAND_REFLECTION_HANDLER	17
#define CUSTOM_NOTIFY_REFLECTION_HANDLER	18

//flags
#define CONTAIN_RESOURCE_STRINGS	0x10000
#define NO_CRACK_MESSAGES			0x20000
#define DEFAULT_MESSAGE				0x40000
#define CUSTOM_MESSAGE				0x80000
#define REFLECTION_MESSAGE			0x100000

#define MESSAGE_ROOT				0x80000000
#define WINDOWS_ROOT				0x40000000
#define COMMAND_ROOT				0x20000000
#define NOTIFY_ROOT					0x10000000

#define TYPE_MASK					0xffff
#define FLAGS_MASK					0xffff0000

struct ParamStruct
{
	CString ParamName;
	CString ParamType;
	CString ParamFunc;

	bool LoadParam(CXMLObject* pXMLObject);
	bool SaveParam(CXMLObject* pXMLObject);
};

struct MessageStruct
{
	CString Message;
	CString DefFuncName;
	CString Comment;
	CString Body;
	UINT Type;
	int IconIndex;
	CSmartAtlArray<ParamStruct> Params;
	CSmartAtlArray<CString>* pResWords;
	CSmartAtlArray<MessageStruct*> Children;
	MessageStruct() : Type(0), pResWords(0), IconIndex(-1){};

	bool LoadMessage(CXMLObject* pXMLObject);
	bool SaveMessage(CXMLObject* pXMLObject);
};

#define HANDLER_TYPE_MESSAGE			0x1
#define HANDLER_TYPE_CRACK_MESSAGE		0x2
#define HANDLER_TYPE_COMMAND_MESSAGE	0x4
#define HANDLER_TYPE_NOTIFY_MESSAGE		0x8
#define HANDLER_REFLECTION_MESSAGE		0x10
#define HANDLER_REFLECTION_COMMAND		0x20
#define HANDLER_REFLECTION_NOTIFY		0x40

#define HANDLER_TYPE_MASK				0xff

#define HANDLER_EX						0x1000
#define HANDLER_REFLECTED				0x2000
#define HANDLER_CODE					0x4000
#define HANDLER_ID						0x8000
#define HANDLER_RANGE					0x10000
#define HANDLER_HWND					0x20000


struct HandlerStruct
{
	VSMapEntry* pMapEntry;
	VSFunction* pFunction;
	int Type;
	CString HandlerName;
	CString Message;
	CString Code;
	CString FirstId;
	CString LastId;
	CString HWND;
};

struct HandlerFunction
{
	VSFunction* pFunc;
	int Type; // the same as HandlerStruct::Type
};

class CHandlerManager
{
	MessageStruct* m_pRootMessage;
	CAtlArray<VSFunction*>* m_pFunctions;
	CAtlArray<HandlerStruct*> m_Handlers;
	//index of the handler for function or -1 if no such
	CAtlArray<size_t> m_FuncMap;
	//map of type synonyms
	CAtlMap<CString, CSmartAtlArray<CString> > m_SynonymMap;
	bool m_bExactEqual;

	void DeleteMessage(MessageStruct* pMes);

	BOOL AddCrackMessage(VSMapEntry* pMapEntry, HandlerStruct* pHandler, CString RestPart);
	BOOL AddWindowsMessage(VSMapEntry* pMapEntry, HandlerStruct* pHandler, CString RestPart);
	BOOL AddCommandNotifyMessage(VSMapEntry* pMapEntry, HandlerStruct* pHandler, CString RestPart);
	BOOL AddReflection(VSMapEntry* pMapEntry, HandlerStruct* pHandler, CString RestPart);
	BOOL AddCommandNotifyReflection(VSMapEntry* pMapEntry, HandlerStruct* pHandler, CString RestPart);
	BOOL AddMessageReflection(VSMapEntry* pMapEntry, HandlerStruct* pHandler, CString RestPart);

	void FindSimilarCommandFunctions(CAtlArray<HandlerFunction>& Handlers);
	void FindSimilarNotifyFunctions(CAtlArray<HandlerFunction>& Handlers);
	void FindSimilarMessageFunctions(CAtlArray<HandlerFunction>& Handlers);
	void FindSimilarCrackMessageFunctions(MessageStruct* pMes, CAtlArray<HandlerFunction>& Handlers);
	MessageStruct* FindMessageStruct(MessageStruct* pRoot, CString MessageName, CString SubMessageName);
	void AddMessagesFromNode(MessageStruct* pMes, CAtlArray<CString>& StringCodes);
public:
	CHandlerManager(void);
	~CHandlerManager(void);
	void Reset();
	void Destroy();

	bool m_bReflectNotifications;
	bool m_bReflectNotificationsEx;
	bool m_bForwardNotifications;
	bool m_bDefReflectHandler;
	CAtlArray<CString> m_Chains;
	bool LoadSettings(CXMLObject* pArchive, LPCTSTR lpObjectName);
	MessageStruct* GetRootMessage();
	MessageStruct* FindMessageStruct(CString MessageName, CString SubMessageName = CString());
	void Init(CAtlArray<VSFunction*>* pFunctions);
	HandlerStruct* AddMapEntry(VSMapEntry* pMapEntry);
	bool IsHandlerExist(MessageStruct* pMes, VSMessageMap* pMap = NULL);
	//iFunction - индекс функции
	HandlerStruct* IsHandler(int iFunction);
	HandlerStruct* IsHandler(VSFunction* pFunc);
	HandlerStruct* AddHandler(HandlerStruct* pHandler);
	VSFunction* GetFunctionByMapEntry(VSMapEntry* pMapEntry);
	HandlerStruct* GetHandler(VSMapEntry* pMapEntry);
	void GetHandlerFunctions(CAtlArray<HandlerFunction>& Handlers, int TypeMask);
	void FindSimilarFunctions(MessageStruct* pMes, CAtlArray<HandlerFunction>& Handlers);
	void DeleteHandler(HandlerStruct* pHandler);
	bool FindCommandMessages(CAtlArray<CString>& StringCodes);
	bool FindNotifyMessages(CAtlArray<CString>& StringCodes);
};
