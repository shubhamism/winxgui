////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2005 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	MessageManager.h
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

#pragma once

#include "VSElements.h"
#include "common.h"
#include "ResourceManager.h"
#include "Settings.h"
#include "Dialog/HandlerIDDlg.h"

class CMessageManager : public CSettings<CMessageManager>
{
	VSClass* m_pClass;
	HWND m_hParentWnd;
	InsDelPoints* m_pModifications;
	const CResourceManager* m_pResManager;
	VSMessageMap* m_pMessageMap;
	CAtlArray<CString>* m_pGeneralResources;

	bool m_bNewStyle;
	bool m_bSortMessages;
	bool m_bInline;
	bool m_bUseAtlMisc;
	BOOL m_bCheckMissingEndMap;

	bool SetHeader(CString HeaderName);
	bool SetAtlCrack();
	bool SetAtlMisc();
	bool SetWinX();
	bool InsertNewMap(bool bEx = false);
	CString CreateHandlerBody(MessageStruct* pMes, bool bCracked = false);
	int GetAltMapNumber();
	bool IsFunctionExists(CString Name);
	void AddDlgIDs(CString DialogID, MessageStruct* pMes, CAtlArray<CString>& Strings);
	bool IsNeedReflected(MessageStruct* pMes);
	bool AddCommandMessage(CHandlerIDDlg& dlg, OUT HandlerStruct& Handler, MessageStruct* pMes);
	bool AddNotifyMessage(CHandlerIDDlg& dlg, OUT HandlerStruct& Handler, MessageStruct* pMes);
	void AddMessages(MessageStruct* pMes, CAtlArray<MessageStruct*>& Messages);
	void AddSupportedMessages(const ResControl* pControl, MessageStruct* pMes, CAtlArray<MessageStruct*>& Messages);
public:
	CMessageManager(void);
	~CMessageManager(void);

	static CHandlerManager m_sHandlerManager;

	void Init(IN HWND hParentWnd, IN const CResourceManager* pResManager, IN CAtlArray<CString>* pGeneralResources);
	// return true if modified something
	bool SetClass(IN VSClass* pClass, IN InsDelPoints* pModifications);
	void SetMessageMap(VSMessageMap* pMap);
	bool IsClassSet();

	bool AddMessageMap();
	bool ReplaceMessageMapEnd();
	bool InsertAltMap();

	bool InsertWindowsMessageHandler(IN MessageStruct* pMes, OUT HandlerStruct& Handler);
	bool InsertCommandMessageHandler(IN MessageStruct* pMes, OUT HandlerStruct& Handler);
	bool InsertNotifyMessageHandler(IN MessageStruct* pMes, OUT HandlerStruct& Handler);
	bool InsertDialogControlMessageHandler(IN const ResControl* pControl, ClassVector& Classes, CSmartAtlArray<InsDelPoints>& Modifications, int iCurClass);
	bool InsertIDMessageHandler(IN CString ID, ClassVector& Classes, CSmartAtlArray<InsDelPoints>& Modifications, int& iCurClass);
	bool InsertReflectionHandler(IN MessageStruct* pMes, OUT HandlerStruct& Handler, CString ControlId = CString());

	bool DeleteMap(VSMessageMap* pMap);
	bool DeleteHandler(HandlerStruct* pHandler);

	bool AddForwardReflect(CString Name, LPCTSTR lpHeaderFile = NULL);
	bool DeleteForwardReflect(CString Name);

	BEGIN_SETTINGS_MAP()
		SETTINGS_VARIABLE_OPT_RO(m_bNewStyle)
		SETTINGS_VARIABLE_OPT_RO(m_bSortMessages)
		SETTINGS_VARIABLE_OPT_RO(m_bInline)
		SETTINGS_VARIABLE_OPT_RO(m_bUseAtlMisc)
		SETTINGS_VARIABLE_OPT_RO(m_bCheckMissingEndMap)
	END_SETTINGS_MAP()
};
