////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	VSElements.h
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

#pragma		once
#include <atlstr.h>
#include <crtdbg.h>

__inline LPTSTR ToTCHAR(_bstr_t str)
{
#ifdef _UNICODE
	return (wchar_t*)str;
#else
	return (char*)str;
#endif

}

struct VSElement;

struct VSElement
{
	CString Name;
	EnvDTE::CodeElementPtr pElement;
	VSElement* pParent;
	EnvDTE::vsCMElement ElementType;
	VSElement(EnvDTE::vsCMElement Type) : pElement(NULL), pParent(NULL), ElementType(Type)
	{
	}

	virtual ~VSElement()
	{
	}
	HRESULT RetriveName(bool bFullName = false)
	{
		_bstr_t str;
		HRESULT hRes;
		ATLASSERT(pElement != NULL);
		if (bFullName)
		{
			hRes = pElement->get_FullName(str.GetAddress());
			if (FAILED(hRes))
			{
				return hRes;
			}
			Name = ToTCHAR(str);
		}
		else
		{
			hRes = pElement->get_Name(str.GetAddress());
			if (FAILED(hRes))
			{
				return hRes;
			}
			Name = ToTCHAR(str);
		}
		return S_OK;
	}

	virtual HRESULT GetStartPoint(EnvDTE::EditPoint** ppEditPoint);
	virtual HRESULT GetEndPoint(EnvDTE::EditPoint** ppEditPoint);
	virtual HRESULT Remove(){return S_FALSE;};
	
};

struct VSVariable : public VSElement
{
	EnvDTE::vsCMAccess Access;
	BOOL bStatic;
	BOOL bConst;
	VSVariable(EnvDTE::vsCMElement Type = EnvDTE::vsCMElementVariable):VSElement(Type),
		Access(EnvDTE::vsCMAccessPrivate), bStatic(FALSE), bConst(FALSE){};
	HRESULT RetriveType();
	CString Type;
	HRESULT Remove();
};

struct VSParameter : public VSElement
{
	VSParameter():VSElement(EnvDTE::vsCMElementParameter){};
	CString Type;
	HRESULT RetriveType();
	//HRESULT RetriveName();
};

struct VSFunction : public VSElement
{
	EnvDTE::vsCMFunction Kind;
	BOOL bStatic;
	BOOL bVirtual;
	BOOL bConst;
	BOOL bInline;
	CString Type;
	EnvDTE::vsCMAccess Access;
	LPARAM lParam;
	VSFunction(EnvDTE::vsCMElement Type = EnvDTE::vsCMElementFunction):VSElement(Type), 
		Access(EnvDTE::vsCMAccessPublic), bStatic(FALSE), bConst(FALSE), 
		bVirtual(FALSE), bInline(FALSE), lParam(0){};
	CSmartAtlArray<VSParameter*> Parameters;
	VSFunction(VSFunction& Func);
	HRESULT RetriveParameters();
	HRESULT RetriveType();
	HRESULT RetrieveAccess();
	virtual HRESULT Remove();
	void DeleteAllItems();
	
	virtual ~VSFunction();
};

struct VSMapEntry : public VSFunction
{
	HRESULT GetStartPoint(EnvDTE::EditPoint** ppEditPoint);
	HRESULT GetEndPoint(EnvDTE::EditPoint** ppEditPoint);
	HRESULT Remove();
	VSMapEntry(EnvDTE::EditPoint* pStart = NULL, EnvDTE::EditPoint* pEnd = NULL):m_pEndPoint(pEnd), 
		m_pStartPoint(pStart), pData(NULL), VSFunction(EnvDTE::vsCMElementMapEntry){};
	VSMapEntry(const VSMapEntry& MapEntry);
	virtual ~VSMapEntry();

	EnvDTE::EditPointPtr m_pStartPoint;
	EnvDTE::EditPointPtr m_pEndPoint;
	void* pData;
};

struct VSMap : public VSElement
{
	CSmartAtlArray<VSMapEntry*> MapEntries;
	CSmartAtlArray<VSParameter*> MapParameters;
	CString Postfix;
	HRESULT RetriveMapEntries();
	VSMap():VSElement(EnvDTE::vsCMElementMap), m_pEndPoint(NULL), m_pStartPoint(NULL){};
	VSMap(EnvDTE::EditPointPtr pStartPoint) :VSElement(EnvDTE::vsCMElementMap), 
		m_pEndPoint(NULL), m_pStartPoint(pStartPoint){};
	virtual ~VSMap();
	HRESULT GetEndPoint(EnvDTE::EditPoint** ppEditPoint);
	HRESULT GetStartPoint(EnvDTE::EditPoint** ppEditPoint);
	HRESULT InsertNewMap(EnvDTE::EditPointPtr pInsertAfter, bool bAfter = true);
	HRESULT InsertMapEntry(VSMapEntry* MapEntry);
	HRESULT Remove();
	void DeleteAllItems();
	bool IsSelf();
protected:
	EnvDTE::EditPointPtr m_pEndPoint;
	EnvDTE::EditPointPtr m_pStartPoint;

	virtual HRESULT FindPlaceForNewItem(VSMapEntry* MapEntry, EnvDTE::EditPoint** ppStartPoint);
	//return false when end of map
	virtual bool AddMapEntry(VSMapEntry* pMapEntry);
};

enum MessageEntryType {MESSAGE_WINDOWS, MESSAGE_COMMAND, MESSAGE_NOTIFY, 
MESSAGE_UNKNOWN, MESSAGE_CHAIN_MAP, MESSAGE_FORWARD_REFLECT, MESSAGE_ANOTHER};

struct VSMessageMap : public VSMap
{
	bool bSortItems;
	bool bCorrectEnd;
	CSmartAtlArray<VSMessageMap*> AltMaps;
	VSMessageMap():bSortItems(true), bCorrectEnd(true){};
	VSMessageMap(EnvDTE::EditPoint* pStartPoint) : VSMap(pStartPoint), bSortItems(true), bCorrectEnd(true){};
	~VSMessageMap();
	HRESULT ReFormatItems();
	HRESULT GetEndPoint(EnvDTE::EditPoint** ppEditPoint);
	HRESULT InsertAltMap(VSMessageMap* pAltMap);
	HRESULT Remove();
	HRESULT ReplacePrefixEnd();
	//only windows messages
	static bool FindMapEntryByMessage(CString Message, VSMessageMap* pMap, CAtlArray<VSMapEntry*>& MapEntries);
protected:
	HRESULT FindPlaceForNewItem(VSMapEntry* MapEntry, EnvDTE::EditPoint** ppStartPoint);
	MessageEntryType GetEntryType(VSMapEntry* MapEntry);
	bool AddMapEntry(VSMapEntry* pMapEntry);
};

struct VSBase : public VSElement
{
	CSmartAtlArray<VSParameter*> TemplateParameters;

	VSBase():VSElement(EnvDTE::vsCMElementVCBase){};
	~VSBase();

	bool RetrieveTemplateParameters();
};

enum eBoolUnknown
{
	eUnknown,
	eFalse,
	eTrue	
};

struct VSClass : public VSElement
{
private:
	bool m_bRetrieved;
protected:
	CString GetDialogID(EnvDTE::CodeElementPtr pElem);
	bool FindPlaceForNewVar(_variant_t& Pos, EnvDTE::vsCMAccess NeededAccess);
	EnvDTE::EditPointPtr FindLastPublicElement();
	bool FindPlaceForNewMap(EnvDTE::EditPoint** ppEditPoint);
	bool FindPlaceForNewMessageMap(EnvDTE::EditPoint** ppEditPoint, VSMessageMap* pMap);
	void RemoveMapMacrosFromFunctions();
	void AddMessageMapMacros(VSMessageMap* pMap, CAtlMap<CString, int>& Strings);
	bool IsMapEntryName(CString Name);
public:
	CSmartAtlArray<VSVariable*> Variables;
	CSmartAtlArray<VSFunction*> Functions;
	CSmartAtlArray<VSMap*> Maps;
	CSmartAtlArray<VSBase*> Parents;
	CSmartAtlArray<VSClass*> NestedClasses;
	EnvDTE::CodeModel* pCodeModel;
	CSmartAtlArray<CString> Headers;
	//bool m_bAtlCrack;
	//bool m_bAtlMisc;
	//true если класс наследован от CWinDataExchange и включен файл atlddx.h
	bool m_bDDX;
	eBoolUnknown m_eDialog;
	CString m_DialogID;
	
	VSClass():VSElement(EnvDTE::vsCMElementClass), /*m_bAtlCrack(false), m_bAtlMisc(false),*/
	m_eDialog(eUnknown), m_bDDX(false), m_bRetrieved(false){};
	bool IsDialog();
	
	HRESULT AddElement(EnvDTE::CodeElementPtr pElement);
	HRESULT RetriveItems();
	void DeleteAllItems();
	VSMap* GetMap(CString MapName);
	HRESULT InsertFunction(VSFunction* pFunc, CString Comment, 
		EnvDTE::vsCMFunction FuncType = EnvDTE::vsCMFunctionFunction,
		_variant_t Position = _variant_t(VCCodeModelLibrary::vsCMAddPositionEnd));
	HRESULT InsertMap(VSMap* pMap);
	HRESULT InsertVariable(VSVariable* pVar);
	HRESULT InsertBase(VSBase* pBase);
	virtual ~VSClass();
};

struct VSInclude : public VSElement
{
	VSInclude() : VSElement(EnvDTE::vsCMElementIncludeStmt){};
};