////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	InsertPoint.h
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

#pragma	  once

#include "VSElements.h"
#include "HandlerManager.h"

//вставл€ютс€ только функции, переменные и прочие объекты, вставл€емые средствами EnvDTE
#define INSERT_STEP_ENVDTE		1
//вставл€ютс€ глобальные обьекты, которые пишутс€ ручками, например map и некоторые 
//макросы
#define INSERT_STEP_GLOBAL		2
//вставл€ютс€ map entry
#define INSERT_STEP_MAP_ENTRY	3

#define INSERT_POINT_UNKNOWN				0
#define INSERT_POINT_FUNC					1
#define INSERT_POINT_VAR					2
#define INSERT_POINT_MAP					3
#define INSERT_POINT_ALT_MAP				4
#define INSERT_POINT_MAP_ENTRY				5
#define INSERT_POINT_HANDLER				6
#define INSERT_POINT_DDX					7
#define INSERT_POINT_SPEC_FUNC				9
#define INSERT_POINT_INCLUDE				10
#define INSERT_POINT_DDXSUPPORT				11
#define INSERT_POINT_REPLACE_END_MSG_MAP	12

struct InsertionPoint
{
	VSElement* pElement;
	int Type;
	virtual HRESULT Insert(VSClass* pClass, int Step) = NULL;
	InsertionPoint(int iType = INSERT_POINT_UNKNOWN) : Type(iType)
	{
	}
	virtual ~InsertionPoint(){};
};

struct InsertPointFunc : public InsertionPoint
{
	CString Body;
	HRESULT Insert(VSClass* pClass, int Step);
	InsertPointFunc(int iType = INSERT_POINT_FUNC);
};

struct InsertPointVariable : public InsertionPoint
{
	HRESULT Insert(VSClass* pClass, int Step);
	InsertPointVariable(int iType = INSERT_POINT_VAR);
};

struct InsertPointMap : public InsertionPoint
{
	HRESULT Insert(VSClass* pClass, int Step);
	InsertPointMap(int iType = INSERT_POINT_MAP);
};

struct InsertPointAltMap : public InsertionPoint
{
	VSMessageMap* pParentMap;
	CString DefineName;
	HRESULT Insert(VSClass* pClass, int Step);
	InsertPointAltMap(int iType = INSERT_POINT_ALT_MAP);
};

struct InsertPointMapEntry : public InsertionPoint
{
	VSMap* pParentMap;
	HRESULT Insert(VSClass* pClass, int Step);
	InsertPointMapEntry(int iType = INSERT_POINT_MAP_ENTRY);
};

struct InsertPointHandler : public InsertPointMapEntry
{
	VSFunction* pFunction;
	CString Body;
	HRESULT Insert(VSClass* pClass, int Step);
	InsertPointHandler(int iType = INSERT_POINT_HANDLER);
};

struct InsertPointDDX : public InsertPointMapEntry
{
	VSVariable* pVariable;
	CString Initializer;
	HRESULT Insert(VSClass* pClass, int Step);
	InsertPointDDX(int iType = INSERT_POINT_DDX);
private:
	HRESULT AddInitializer(VSFunction* pFunc);
};

struct InsertSpecFunction : public InsertPointFunc
{
	VSBase* pBase;
	CString OnCreateBody;
	CString OnDestroyBody;
	MessageStruct* pMesCreate;
	MessageStruct* pMesDestroy;
	bool bInitDialog;
	HRESULT Insert(VSClass* pClass, int Step);
	InsertSpecFunction(int iType = INSERT_POINT_SPEC_FUNC);
};

struct InsertInclude : public InsertionPoint
{
	HRESULT Insert(VSClass* pClass, int Step);
	EnvDTE::ProjectItemPtr pProjectFile;
	_variant_t Pos;
	CString AdditionalMacro;
	InsertInclude(int iType = INSERT_POINT_INCLUDE);
	~InsertInclude();
private:
	EnvDTE::CodeElementPtr pInclude;
};

struct InsertPointDDXSupport : public InsertionPoint
{
	bool bUseFloat;
	VSBase* pBase;
	HRESULT Insert(VSClass* pClass, int Step);
	InsertPointDDXSupport(int Type = INSERT_POINT_DDXSUPPORT);
	~InsertPointDDXSupport();
private:
	EnvDTE::EditPointPtr pFloatPoint;
};

struct InsertPointReplaceEndMap : public InsertionPoint
{
	InsertPointReplaceEndMap();
	HRESULT Insert(VSClass* pClass, int Step);
};