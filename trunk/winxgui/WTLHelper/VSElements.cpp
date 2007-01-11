////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004 Sergey Solozhentsev
// Author: 	Sergey Solozhentsev e-mail: salos@mail.ru
// Product:	WTL Helper
// File:      	VSElements.cpp
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

#include "stdafx.h"
#include "VSElements.h"
//////////////////////////////////////////////////////////////////////////
// VSElement

HRESULT VSElement::GetEndPoint(EnvDTE::EditPoint** ppEditPoint)
{
	ATLASSERT(pElement != NULL);
	EnvDTE::TextPointPtr pt;
	HRESULT hr = pElement->get_EndPoint(&pt);
	if (FAILED(hr))
	{
		return hr;
	}
	
	hr = pt->CreateEditPoint(ppEditPoint);
	return hr;
}

HRESULT VSElement::GetStartPoint(EnvDTE::EditPoint** ppEditPoint)
{
	ATLASSERT(pElement != NULL);
	EnvDTE::TextPointPtr pt;

	HRESULT hr = pElement->get_StartPoint(&pt);
	if (FAILED(hr) || (pt == NULL))
	{
		*ppEditPoint = NULL;
		return E_FAIL;
	}
	
	hr = pt->CreateEditPoint(ppEditPoint);
	return hr;
}

// VSElement
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// VSBase

VSBase::~VSBase()
{
	for (size_t i = 0; i < TemplateParameters.GetCount(); i++)
	{
		delete TemplateParameters[i];
	}
	TemplateParameters.RemoveAll();
}

bool VSBase::RetrieveTemplateParameters()
{
	TemplateParameters.RemoveAll();
	VCCodeModelLibrary::VCCodeBasePtr pBase = pElement;
	ATLASSERT(pBase != NULL);
	if (pBase == NULL)
		return false;
	_bstr_t DeclText = pBase->DeclarationText;
	CString FullName = DeclText;
	int TemlPos = FullName.Find(_T('<'));
	if (TemlPos == -1)
		return false;
	FullName.Trim();
	if (FullName[FullName.GetLength() - 1] != _T('>'))
		return false;
	CString TempParams = FullName.Mid(TemlPos + 1, FullName.GetLength() - 2 - TemlPos);
	int TemplBracket = 0;
	int StartPos = 0;
	TempParams.Trim();
	for (int i = 0; i < TempParams.GetLength(); i++)
	{
		if (TempParams[i] == _T(','))
		{
			//separate template parameter
			if (TemplBracket == 0)
			{
				CString ParamName = TempParams.Mid(StartPos, i - StartPos);
				ParamName.Trim();
				StartPos = i + 1;
				VSParameter* pParam = new VSParameter;
				pParam->pParent = this;
				pParam->Name = ParamName;
				TemplateParameters.Add(pParam);
			}
		}
		// calc template brackets
		if (TempParams[i] == _T('<'))
		{
			TemplBracket++;
		}
		if (TempParams[i] == _T('>'))
		{
			TemplBracket--;
		}
	}
	VSParameter* pParam = new VSParameter;
	CString ParamName = TempParams.Mid(StartPos);
	ParamName.Trim();
	pParam->Name = ParamName;
	pParam->pParent = this;
	TemplateParameters.Add(pParam);
	return true;
}

// VSBase
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// VSClass

CString VSClass::GetDialogID(EnvDTE::CodeElementPtr pElem)
{
	_bstr_t ElemName;
	VCCodeModelLibrary::VCCodeClassPtr pClass = pElem;
	ATLASSERT(pClass != NULL);
	pClass->get_Name(ElemName.GetAddress());

	for (size_t i = 0; i < _AtlModule.m_DialogClasses.GetCount(); i++)
	{
		if (_bstr_t(_AtlModule.m_DialogClasses.GetAt(i)) == ElemName)
			return CString();
	}

	EnvDTE::CodeElementsPtr pEnums;
	pClass->get_Enums(&pEnums);
	if (pEnums)
	{		
		long Count;
		pEnums->get_Count(&Count);
		for (long i = 1; i <= Count; i++)
		{
			EnvDTE::CodeElementPtr pEnumElem;
			pEnums->Item(_variant_t(i), &pEnumElem);
			ATLASSERT(pEnumElem != NULL);
			VCCodeModelLibrary::VCCodeEnumPtr pEnum = pEnumElem;
			ATLASSERT(pEnum != NULL);
			EnvDTE::CodeElementsPtr pMembers;
			pEnum->get_Members(&pMembers);
			if (pMembers == NULL)
				continue;
			EnvDTE::CodeElementPtr pMemberElem;
			EnvDTE::CodeVariablePtr pMemberVar;
			pMembers->Item(_variant_t(L"IDD"), &pMemberElem);
			pMemberVar = pMemberElem;
			if (pMemberVar != NULL)
			{
				_variant_t vtValue;
				pMemberVar->get_InitExpression(&vtValue);
				CString Value = vtValue;
				return Value;
			}
		}
	}
	//не нашли в этом классе. поищем в предках
	EnvDTE::CodeElementsPtr pBases;
	pClass->get_Bases(&pBases);
	long BaseCount;
	pBases->get_Count(&BaseCount);
	for (long i1 = 1; i1 <= BaseCount; i1++)
	{
		EnvDTE::CodeElementPtr pBaseElem;
		pBases->Item(_variant_t(i1), &pBaseElem);
		if (pBaseElem != NULL)
		{
			VCCodeModelLibrary::VCCodeBasePtr pBase = pBaseElem;
			if (pBase != NULL)
			{
				EnvDTE::CodeTypePtr pType = pBase->Class;
				if(pType != NULL)
				{
					VCCodeModelLibrary::VCCodeClassPtr pBaseClass = pType;
					if (pBaseClass != NULL)
					{
						CString id = GetDialogID(pBaseClass);
						if (!id.IsEmpty())
							return id;
					}
				}
			}
		}
	}
	
	return CString();
}

bool VSClass::FindPlaceForNewVar(_variant_t& Pos, EnvDTE::vsCMAccess NeededAccess)
{
	VSVariable* pLastVar = NULL;
	for (size_t i = 0; i < Variables.GetCount(); i++)
	{
		VSVariable* pVar = Variables[i];
		if (pVar->pElement)
		{
			//уже реально существующий элемент
			VCCodeModelLibrary::VCCodeVariablePtr pVCVar = pVar->pElement;
			EnvDTE::vsCMAccess Access;
			pVCVar->get_Access(&Access);
			if (Access == NeededAccess)
			{
				pLastVar = pVar;
			}
		}
	}
	if (pLastVar)
	{
		Pos = (EnvDTE::CodeElement*)pLastVar->pElement;
		return true;
	}
	else
	{
		Pos = 0;
		return false;
	}
}

EnvDTE::EditPointPtr VSClass::FindLastPublicElement()
{
	//ищем последний public элемент
	VSElement* pLastElem = NULL;
	VSFunction* pLastFunc = NULL;
	VSVariable* pLastVar = NULL;
	EnvDTE::EditPointPtr pLastPoint;
	for (size_t i1 = 0; i1 < Functions.GetCount(); i1++)
	{
		EnvDTE::CodeFunctionPtr pFunc = Functions[i1]->pElement;
		if (pFunc == NULL)
		{
			continue;
		}
		pLastFunc = Functions[i1];

		EnvDTE::vsCMAccess Access;
		pFunc->get_Access(&Access);
		if (Access == EnvDTE::vsCMAccessPublic)
		{
			pLastElem = Functions[i1];
		}
	}
	if (pLastElem)
	{
		VCCodeModelLibrary::VCCodeFunctionPtr pFunc = pLastElem->pElement;
		EnvDTE::TextPointPtr pTextPoint;
		HRESULT hr = pFunc->get_EndPointOf(EnvDTE::vsCMPartHeader, VCCodeModelLibrary::vsCMWhereDeclaration, &pTextPoint);
		if (FAILED(hr))
		{
			return NULL;
		}
		pTextPoint->CreateEditPoint(&pLastPoint);

		return pLastPoint;
	}

	for (size_t i2 = 0; i2 < Variables.GetCount(); i2++)
	{
		EnvDTE::CodeVariablePtr pVar = Variables[i2]->pElement;
		if (pVar == NULL)
		{
			continue;
		}

		pLastVar = Variables[i2];
		EnvDTE::vsCMAccess Access;
		pVar->get_Access(&Access);
		if (Access == EnvDTE::vsCMAccessPublic)
		{
			pLastElem = Variables[i2];
		}
	}
	if (pLastElem)
	{
		if (FAILED(pLastElem->GetEndPoint(&pLastPoint)))
		{
			return NULL;
		}

		return pLastPoint;
	}
	//нет public элементов
	if (!pLastVar && !pLastFunc)
	{
		//нет ни фукнций ни переменных
		VCCodeModelLibrary::VCCodeClassPtr pCurClass = pElement;
		if (pCurClass == NULL)
		{
			return NULL;
		}

		EnvDTE::TextPointPtr pTextPoint = NULL;
		if (FAILED(pCurClass->get_StartPointOf(EnvDTE::vsCMPartBody, VCCodeModelLibrary::vsCMWhereDefault, &pTextPoint)) || (pTextPoint == NULL))
		{
			return NULL;	
		}
		pTextPoint->CreateEditPoint(&pLastPoint);
		pLastPoint->EndOfLine();
		_bstr_t ts = _T("public:");
		pLastPoint->Insert(ts);
		
		return pLastPoint;
	}
	if (pLastFunc && pLastVar)
	{
		//есть и функции и переменные
		EnvDTE::EditPointPtr pText1, pText2;
		pLastFunc->GetEndPoint(&pText1);
		pLastVar->GetEndPoint(&pText2);

		VARIANT_BOOL bText1;
		pText1->GreaterThan(pText2, &bText1);
		if (bText1)
		{
			pLastPoint = pText1;
		}
		else
		{
			pLastPoint = pText2;
		}
	}
	if (pLastFunc)
	{
		//только функции
		pLastFunc->GetEndPoint(&pLastPoint);
	}
	if (pLastVar)
	{
		//только переменные
		pLastVar->GetEndPoint(&pLastPoint);
	}

	pLastPoint->EndOfLine();
	_bstr_t ts = _T("public:");
	pLastPoint->Insert(ts);

	return pLastPoint;
}

bool VSClass::FindPlaceForNewMap(EnvDTE::EditPoint** ppEditPoint)
{
	if (Maps.GetCount())
	{
		for (int i1 = (int)Maps.GetCount() - 1; i1 >=0; i1--)
		{
			EnvDTE::EditPointPtr pStartPoint = NULL;
			VSMap* pMap = Maps[i1];
			if (pMap->IsSelf())
			{
				if (FAILED((Maps[i1])->GetEndPoint(&pStartPoint)) || pStartPoint == NULL)
				{
					return false;
				}
				*ppEditPoint = pStartPoint.Detach();
				return true;
			}
		}
	}

	

	*ppEditPoint = FindLastPublicElement().Detach();
	if (*ppEditPoint != NULL)
		return true;
	else
		return false;
}

bool VSClass::FindPlaceForNewMessageMap(EnvDTE::EditPoint** ppEditPoint, VSMessageMap* pMap)
{
	if (Maps.GetCount())
	{
		for (int i1 = (int)Maps.GetCount() - 1; i1 >=0; i1--)
		{
			EnvDTE::EditPointPtr pStartPoint = NULL;
			VSMap* pMap = Maps[i1];
			if (pMap->IsSelf())
			{
				if (FAILED((Maps[i1])->GetEndPoint(&pStartPoint)) || (pStartPoint == NULL))
				{
					return false;
				}
				*ppEditPoint = pStartPoint.Detach();
				return true;
			}
		}
	}

	EnvDTE::TextPointPtr pLastElem = NULL;
	for (size_t i = 0; i != pMap->MapEntries.GetCount(); i++)
	{
		VSFunction* pFunction = (VSFunction*)(pMap->MapEntries[i])->pData;
		if (pFunction && pFunction->pElement != NULL)
		{
			VCCodeModelLibrary::VCCodeFunctionPtr pFunc = pFunction->pElement;
			EnvDTE::TextPointPtr pTextPoint;
			HRESULT hr = pFunc->get_StartPointOf(EnvDTE::vsCMPartHeader, VCCodeModelLibrary::vsCMWhereDeclaration, &pTextPoint);
			if (FAILED(hr))
			{
				return false;
			}
			if (pLastElem == NULL)
			{
				pLastElem = pTextPoint;
			}
			else
			{
				VARIANT_BOOL bGreater;
				pLastElem->GreaterThan(pTextPoint, &bGreater);
				if (bGreater)
				{
					pLastElem = pTextPoint;
				}
			}
		}
	}
	for (size_t j = 0; j < pMap->AltMaps.GetCount(); j++)
	{
		VSMessageMap* pAltMap = pMap->AltMaps[j];
		for (size_t i = 0; i != pAltMap->MapEntries.GetCount(); i++)
		{
			VSFunction* pFunction = (VSFunction*)(pAltMap->MapEntries[i])->pData;
			if (pFunction && pFunction->pElement != NULL)
			{
				VCCodeModelLibrary::VCCodeFunctionPtr pFunc = pFunction->pElement;
				EnvDTE::TextPointPtr pTextPoint;
				HRESULT hr = pFunc->get_StartPointOf(EnvDTE::vsCMPartHeader, VCCodeModelLibrary::vsCMWhereDeclaration, &pTextPoint);
				if (FAILED(hr))
				{
					return false;
				}
				if (pLastElem == NULL)
				{
					pLastElem = pTextPoint;
				}
				else
				{
					VARIANT_BOOL bGreater;
					pLastElem->GreaterThan(pTextPoint, &bGreater);
					if (bGreater)
					{
						pLastElem = pTextPoint;
					}
				}
			}
		}
	}
	if (pLastElem != NULL)
	{
		HRESULT hr = pLastElem->CreateEditPoint(ppEditPoint);
		if (FAILED(hr))
			return false;
		else
			return true;
	}
	else
	{
		*ppEditPoint = NULL;
	}
	
	return false;
}

bool VSClass::IsDialog()
{
	if (m_eDialog != eUnknown)
	{
		return (m_eDialog == eTrue) ? true : false;
	}
	EnvDTE::CodeClassPtr pMyClass = pElement;
	ATLASSERT(pMyClass != NULL);
	VARIANT_BOOL bDerived = VARIANT_FALSE;
	
	if (GetMap(CString(_T("DDX"))))
	{
		bDerived = VARIANT_TRUE;
	}
	else
	{
		for (size_t i = 0; i < Parents.GetCount(); i++)
		{
			if (Parents[i]->Name == _T("CWinDataExchange"))
				bDerived = VARIANT_TRUE;
		}
	}
	if (bDerived != VARIANT_TRUE)
	{
		for (size_t i = 0; i < _AtlModule.m_DialogClasses.GetCount(); i++)
		{
			pMyClass->get_IsDerivedFrom(_bstr_t(_AtlModule.m_DialogClasses.GetAt(i)), &bDerived);
			if (bDerived == VARIANT_TRUE)
				break;
		}
	}
	
	if (bDerived != VARIANT_TRUE)
	{
		m_eDialog = eFalse;
		return false;
	}

	//класс - диалог
	m_eDialog = eTrue;
	//ищем идентификатор IDD
	EnvDTE::CodeElementPtr pelem = pElement;
	m_DialogID = GetDialogID(pelem);
	return true;
}

HRESULT VSClass::AddElement(EnvDTE::CodeElementPtr pElem)
{
	EnvDTE::vsCMElement type;
	pElem->get_Kind(&type);

	switch(type) 
	{
	case EnvDTE::vsCMElementMap:
		{
			VSMap* NewMap;
			VSElement Elem(EnvDTE::vsCMElementMap);
			Elem.pElement = pElem;
			Elem.RetriveName();
			if (Elem.Name == _T("MSG"))
				NewMap = new VSMessageMap;
			else
				NewMap = new VSMap;
			NewMap->pElement = pElem;
			Elem.pElement = NULL;

			NewMap->Name = Elem.Name;
			NewMap->pParent = (VSElement*)this;
			
			if (FAILED(NewMap->RetriveMapEntries()))
			{
				delete NewMap;
				return E_FAIL;
			}
			Maps.Add(NewMap);
		}
		break;
	case EnvDTE::vsCMElementFunction:
		{
			VSFunction* NewFunction = new VSFunction;
			NewFunction->pElement = pElem;
			NewFunction->pParent = (VSElement*)this;
			if (FAILED(NewFunction->RetriveName()))
			{
				delete NewFunction;
				return E_FAIL;
			}
			/*if (NewFunction->Name == _T("DECLARE_FRAME_WND_CLASS_EX"))
			{
				VCCodeModelLibrary::VCCodeFunctionPtr pVCFunc = pElem;
				if (pVCFunc != NULL)
				{
					_bstr_t bsStr;
					pVCFunc->get_BodyText(bsStr.GetAddress());
					pVCFunc->get_DeclarationText(bsStr.GetAddress());
				}
			}*/
			int EndMap;
			if ((NewFunction->Name.Left(6) == _T("BEGIN_")) && 
				((EndMap = NewFunction->Name.Find(_T("_MAP"))) != -1))
			{
				//find another map
				CString MapName = NewFunction->Name.Mid(6, EndMap - 6);
				CString MapPostfix = NewFunction->Name.Mid(EndMap + 4);
				EnvDTE::EditPointPtr pEdit1;
				NewFunction->GetStartPoint(&pEdit1);
				delete NewFunction;
				VSMap* pNewMap;
				if (MapName == _T("MSG"))
				{
					pNewMap = new VSMessageMap(pEdit1);
				}
				else
				{
					pNewMap = new VSMap(pEdit1);
				}
				pNewMap->Name = MapName;
				pNewMap->Postfix = MapPostfix;
				if (FAILED(pNewMap->RetriveMapEntries()))
				{
					delete pNewMap;
					return E_FAIL;
				}
				Maps.Add(pNewMap);
				return S_OK;
			}
			
			if (_AtlModule.IsMacro(NewFunction->Name))
			{
				delete NewFunction;
				return S_OK;
			}
			if (FAILED(NewFunction->RetriveParameters()))
			{
				delete NewFunction;
				return E_FAIL;
			}
			NewFunction->RetriveType();
			NewFunction->RetrieveAccess();

			Functions.Add(NewFunction);
		}
		break;
	case EnvDTE::vsCMElementVariable:
		{
			VSVariable* NewVar = new VSVariable;
			NewVar->pElement = pElem;
			NewVar->pParent = (VSElement*)this;
			if (FAILED(NewVar->RetriveName()))
			{
				delete NewVar;
				return E_FAIL;
			};
			if (FAILED(NewVar->RetriveType()))
			{
				delete NewVar;
				return E_FAIL;
			}
			Variables.Add(NewVar);
		}
		break;
	case EnvDTE::vsCMElementVCBase:
		{
			VSBase* NewParent = new VSBase;
			NewParent->pElement = pElem;
			NewParent->pParent = (VSElement*)this;
			if (FAILED(NewParent->RetriveName()))
			{
				delete NewParent;
				return E_FAIL;
			}
			Parents.Add(NewParent);
		}
		break;
	default:
		{
			/*CString s1;
			s1.Format("%d", type);
			MessageBox(NULL, s1, NULL, 0);*/
		}

	}
	return S_OK;
}

VSMap* VSClass::GetMap(CString MapName)
{
	for (size_t i = 0; i < Maps.GetCount(); i++)
	{
		if (Maps[i]->Name == MapName)
		{
			return Maps[i];
		}
	}
	return NULL;
}

HRESULT VSClass::InsertFunction(VSFunction* pFunc, CString Comment,
								EnvDTE::vsCMFunction FuncType/* = EnvDTE::vsCMFunctionFunction */,
								_variant_t Position /*= _variant_t(VCCodeModelLibrary::vsCMAddPositionEnd)*/)
{
	VCCodeModelLibrary::VCCodeClassPtr pClass = pElement;
	if (pClass == NULL)
	{
		return S_FALSE;
	}

	EnvDTE::CodeTypeRefPtr pTypeRef;
	if (FAILED(pCodeModel->CreateCodeTypeRef(_variant_t(_bstr_t(pFunc->Type)), &pTypeRef)) || (pTypeRef == NULL))
	{
		return S_FALSE;
	}
	
	_variant_t vtType = ((LPDISPATCH)pTypeRef);
	EnvDTE::CodeFunctionPtr pNewFunc = NULL;
	EnvDTE::ProjectItemPtr pItem;
	_bstr_t ClassFile;

	pClass->get_ProjectItem(&pItem);
	if (pItem == NULL)
	{
		MessageBox(NULL, _T("Cannot get project Item"), NULL, 0);
	}
	pItem->get_FileNames(0, ClassFile.GetAddress());
	CString ClassFile1 = ClassFile;
	ClassFile1.Replace(_T(".h"), _T(".cpp"));

	//создание имени
	CString StrName = pFunc->Name + _T('(');
	for (size_t i1 = 0; i1 != pFunc->Parameters.GetCount(); i1++)
	{
		StrName += pFunc->Parameters[i1]->Type + _T(" ") + pFunc->Parameters[i1]->Name + _T(", ");
	}
	
	if (pFunc->Parameters.GetCount())
	{
		StrName.SetAt(StrName.GetLength() - 2, _T(')'));
		StrName.Delete(StrName.GetLength() - 1);
	}
	else
	{
		StrName += _T(')');
	}
	//конец создания имени

	_bstr_t FName = StrName;
	int ft = FuncType;
			
	if (pFunc->bConst)
	{
		ft |= (int)EnvDTE::vsCMFunctionConstant;
	}
	if (pFunc->bVirtual)
	{
		ft |= (int)EnvDTE::vsCMFunctionVirtual;
	}
	if (pFunc->bStatic)
	{
		ft |= (int)EnvDTE::vsCMFunctionShared;
	}
	FuncType = (EnvDTE::vsCMFunction)ft;

	_variant_t vtLocation;
	if (pFunc->bInline)
	{
		vtLocation = _T("");
	}
	else
	{
		vtLocation = ClassFile1;
	}
	EnvDTE::vsCMAccess FuncAccess = EnvDTE::vsCMAccessDefault;

	HRESULT hr = pClass->raw_AddFunction(FName, FuncType, vtType, Position, FuncAccess, vtLocation, &pNewFunc);
	if (pNewFunc == NULL)
	{
		CString Str = _T("Cannot add function ") + StrName;
		MessageBox(NULL, Str, NULL, 0);
		return S_FALSE;
	}
	pNewFunc->get_Access(&FuncAccess);
	if (FuncAccess != pFunc->Access)
	{
		pNewFunc->put_Access(pFunc->Access);
	}
	pFunc->pParent = (VSElement*)this;
	pFunc->pElement = pNewFunc;
	
		
	VCCodeModelLibrary::VCCodeFunctionPtr pVCFunc = pNewFunc;
	if (pVCFunc == NULL)
	{
		return S_FALSE;
	}
	
	if (!Comment.IsEmpty())
	{
		pVCFunc->put_BodyText(_bstr_t(Comment));
	}
	
	/*if (pFunc->bConst)
	{
		pVCFunc->put_IsConstant(VARIANT_TRUE);
	}
	else
	{
		pVCFunc->put_IsConstant(VARIANT_FALSE);
	}
	
	if (pFunc->bStatic)
	{
		pVCFunc->put_IsShared(VARIANT_TRUE);
	}
	else
	{
		pVCFunc->put_IsShared(VARIANT_FALSE);
	}

	if (pFunc->bVirtual)
	{
		pVCFunc->put_IsVirtual(VARIANT_TRUE);
	}
	else
	{
		pVCFunc->put_IsVirtual(VARIANT_FALSE);
	}
	*/
	return S_OK;
}

HRESULT VSClass::InsertVariable(VSVariable* pVar)
{
	VCCodeModelLibrary::VCCodeClassPtr pClass = pElement;
	if (pClass == NULL)
	{
		return E_FAIL;
	}

	EnvDTE::CodeTypeRefPtr pTypeRef;
	if (FAILED(pCodeModel->CreateCodeTypeRef(_variant_t(_bstr_t(pVar->Type)), &pTypeRef)) || (pTypeRef == NULL))
	{
		return E_FAIL;
	}

	_variant_t vtType = ((LPDISPATCH)pTypeRef);
	EnvDTE::CodeVariablePtr pNewVar = NULL;
	EnvDTE::ProjectItemPtr pItem;
	_bstr_t ClassFile;

	pClass->get_ProjectItem(&pItem);
	if (pItem == NULL)
	{
		//MessageBox(NULL, "Cannot get Item", NULL, 0);
		return E_FAIL;
	}
	pItem->get_FileNames(0, ClassFile.GetAddress());
	CString ClassFile1 = ClassFile;
	ClassFile1.Replace(_T(".h"), _T(".cpp"));
	
	CString StrName = pVar->Name;

	_bstr_t FName = StrName;
	_variant_t vtPos;
	EnvDTE::vsCMAccess Access;
	if (FindPlaceForNewVar(vtPos, pVar->Access))
	{
		Access = EnvDTE::vsCMAccessDefault;
	}
	else
	{
		Access = pVar->Access;
	}
	_variant_t vtLocation;
	if (pVar->bStatic)
	{
		vtLocation = ClassFile1;
	}
	else
	{
		vtLocation.Clear();
	}
	HRESULT hr = pClass->raw_AddVariable(FName, vtType, vtPos, Access, vtLocation, &pNewVar);
	if (pNewVar == NULL)
	{
		CString Str = _T("Cannot add variable ") + StrName;
		MessageBox(NULL, Str, NULL, 0);
		return S_FALSE;
	}
	pVar->pParent = (VSElement*)this;
	pVar->pElement = pNewVar;
	VCCodeModelLibrary::VCCodeVariablePtr pVCVar = pNewVar;
	if (pVCVar == NULL)
	{
		return S_OK;
	}
	
	if (pVar->bConst)
	{
		pVCVar->put_IsConstant(VARIANT_TRUE);
	}
	else
	{
		pVCVar->put_IsConstant(VARIANT_FALSE);
	}

	if (pVar->bStatic)
	{
		pVCVar->put_IsShared(VARIANT_TRUE);
	}
	else
	{
		pVCVar->put_IsShared(VARIANT_FALSE);
	}
	
	return S_OK;
}

HRESULT VSClass::InsertMap(VSMap* pMap)
{
	EnvDTE::EditPointPtr pStartPoint;
	bool bAfter = true;
	if (pMap->Name == _T("MSG"))
	{
		if (!FindPlaceForNewMessageMap(&pStartPoint, (VSMessageMap*)pMap))
		{
			if (!FindPlaceForNewMap(&pStartPoint))
				return E_FAIL;
		}
		else
		{
			bAfter = false;
		}
	}
	else
	{
		if (!FindPlaceForNewMap(&pStartPoint))
			return E_FAIL;
	}
	pMap->InsertNewMap(pStartPoint, bAfter);
	return S_OK;
}

HRESULT VSClass::RetriveItems()
{
	if (m_bRetrieved)
		return S_OK;
	m_bRetrieved = true;

	EnvDTE::CodeElementsPtr pElements = NULL;
	DeleteAllItems();

	if (FAILED(pElement->get_Children(&pElements)) || (pElements == NULL))
	{
		return E_FAIL;
	}

	long Count = 0;
	pElements->get_Count(&Count);

	for (long i = 1; i <= Count; i++)
	{
		_variant_t vt = i;
		EnvDTE::CodeElementPtr pElem = NULL;
		if (FAILED(pElements->Item(vt, &pElem)) || (pElem == NULL))
		{
			return E_FAIL;
		}

		if (FAILED(AddElement(pElem)))
		{
			ATLTRACE(_T("FAILED AddAllement"));
			//return E_FAIL;
		}
	}
	IsDialog();
	RemoveMapMacrosFromFunctions();
	return S_OK;
}

void VSClass::RemoveMapMacrosFromFunctions()
{
	CAtlMap<CString, int> MapEntriesName;
	// collect all strings that should not be a function name
	for (size_t i = 0; i < Maps.GetCount(); i++)
	{
		VSMap* pMap = Maps[i];
		if (pMap->Name != _T("MSG"))
		{
			for (size_t j = 0; j < pMap->MapEntries.GetCount(); j++)
			{
				if (IsMapEntryName(pMap->MapEntries[j]->Name) &&
					!MapEntriesName.Lookup(pMap->MapEntries[j]->Name))
				{
					MapEntriesName.SetAt(pMap->MapEntries[j]->Name, 1);
				}
			}
		}
		else
		{
			VSMessageMap* pMesMap = (VSMessageMap*)pMap;
			AddMessageMapMacros(pMesMap, MapEntriesName);
			for (size_t j = 0; j < pMesMap->AltMaps.GetCount(); j++)
			{
				AddMessageMapMacros(pMesMap->AltMaps[j], MapEntriesName);
			}
			if (pMesMap->AltMaps.GetCount())
			{
				if (!MapEntriesName.Lookup(CString(_T("ALT_MSG_MAP"))))
				{
					MapEntriesName.SetAt(CString(_T("ALT_MSG_MAP")), 1);
				}
			}
			if (!MapEntriesName.Lookup(CString(_T("FORWARD_NOTIFICATIONS"))))
			{
				MapEntriesName.SetAt(CString(_T("FORWARD_NOTIFICATIONS")), 1);
			}
			if (!MapEntriesName.Lookup(CString(_T("REFLECT_NOTIFICATIONS"))))
			{
				MapEntriesName.SetAt(CString(_T("REFLECT_NOTIFICATIONS")), 1);
			}
		}
		CString FullMapName = _T("BEGIN_") + pMap->Name + _T("_MAP") + pMap->Postfix;
		if (!MapEntriesName.Lookup(FullMapName))
			MapEntriesName.SetAt(FullMapName ,1);
		CString EndName = _T("END_") + pMap->Name + _T("_MAP") + pMap->Postfix;
		if (!MapEntriesName.Lookup(EndName))
			MapEntriesName.SetAt(EndName, 1);
	}
	//clear function list
	for (int i = (int)Functions.GetCount() - 1; i >= 0; i--)
	{
		VSFunction* pFunc = Functions[i];
		if (MapEntriesName.Lookup(pFunc->Name))
		{
			Functions.RemoveAt(i);
			delete pFunc;
		}
	}
}

void VSClass::AddMessageMapMacros(VSMessageMap* pMap, CAtlMap<CString, int>& Strings)
{
	for (size_t i = 0; i < pMap->MapEntries.GetCount(); i++)
	{
		if (IsMapEntryName(pMap->MapEntries[i]->Name) &&
			!Strings.Lookup(pMap->MapEntries[i]->Name))
		{
			Strings.SetAt(pMap->MapEntries[i]->Name, 1);
		}
	}
}

bool VSClass::IsMapEntryName(CString Name)
{
	// Map Entry name should be in uppercase or _ or number
	for (int i = 0; i < Name.GetLength(); i++)
	{
		if ((Name[i] < _T('A') || Name[i] > _T('Z')) &&
			(Name[i] < _T('0') || Name[i] > _T('9')) &&
			Name[i] != _T('_'))
		{
			return false;
		}
	}
	return true;
}

void VSClass::DeleteAllItems()
{
	for (size_t i1 = 0; i1 < Maps.GetCount(); i1++)
	{
		delete Maps[i1];
	}
	Maps.RemoveAll();

	for (size_t i2 = 0; i2 < Functions.GetCount(); i2++)
	{
		delete Functions[i2];
	}
	Functions.RemoveAll();

	for (size_t i3 = 0; i3 < Variables.GetCount(); i3++)
	{
		delete Variables[i3];
	}
	Variables.RemoveAll();

	for (size_t i4 = 0; i4 < Parents.GetCount(); i4++)
	{
		delete Parents[i4];
	}
	Parents.RemoveAll();
}

HRESULT VSClass::InsertBase(VSBase* pBase)
{
	_variant_t vt(pBase->Name);
	EnvDTE::CodeClassPtr pClass = pElement;
	ATLASSERT(pClass != NULL);
	if (pClass == NULL)
		return E_FAIL;
	
	return pClass->AddBase(vt, _variant_t(-1), &pBase->pElement);
}

VSClass::~VSClass()
{
	DeleteAllItems();
}
// VSClass
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// VSVariable

HRESULT VSVariable::RetriveType()
{
	VCCodeModelLibrary::VCCodeVariablePtr pParam = pElement;

	if (pParam == NULL)
	{
		return S_FALSE;
	}

	_bstr_t str;
	pParam->get_TypeString(str.GetAddress());
	Type = ToTCHAR(str);

	return S_OK;
}

HRESULT VSVariable::Remove()
{
	EnvDTE::CodeClassPtr pClass = pParent->pElement;
	if (pClass == NULL)
	{
		return S_FALSE;
	}

	return pClass->RemoveMember(_variant_t((EnvDTE::CodeElement*)pElement));
}

// VSVariable
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// VSParameter

HRESULT VSParameter::RetriveType()
{
	VCCodeModelLibrary::VCCodeParameterPtr pParam = pElement;

	if (pParam == NULL)
	{
		return E_INVALIDARG;
	}

	_bstr_t str;
	HRESULT hRes = pParam->get_TypeString(str.GetAddress());
	if (FAILED(hRes))
		return hRes;
	Type = ToTCHAR(str);
	Type.Trim();

	return S_OK;
}

/*HRESULT VSParameter::RetriveName()
{
	_bstr_t str;
	VCCodeModelLibrary::VCCodeParameterPtr pParam = pElement;
	HRESULT hRes = pParam->get_DisplayName(str.GetAddress());
	if (FAILED(hRes))
	{
		return hRes;
	}
	Name = ToTCHAR(str);
	return S_OK;
}*/
// VSParameter
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// VSFunction

VSFunction::VSFunction(VSFunction& Func):VSElement(EnvDTE::vsCMElementFunction)
{
	Name = Func.Name;
	for (size_t i = 0; i < Func.Parameters.GetCount(); i++)
	{
		VSParameter* pNewParam = new VSParameter(*(Func.Parameters[i]));
		Parameters.Add(pNewParam);
	}
	
}

HRESULT VSFunction::RetriveType()
{
	VCCodeModelLibrary::VCCodeFunctionPtr pFunc = pElement;
	ATLASSERT(pFunc != NULL);
	_bstr_t s1;
	pFunc->get_TypeString(s1.GetAddress());
	Type = ToTCHAR(s1);
	Type.Trim();
	
	pFunc->get_FunctionKind(&Kind);

	return S_OK;
}

HRESULT VSFunction::RetrieveAccess()
{
	VCCodeModelLibrary::VCCodeFunctionPtr pVCFunc = pElement;
	ATLASSERT(pVCFunc != NULL);

	return pVCFunc->get_Access(&Access);
}

HRESULT VSFunction::RetriveParameters()
{
	EnvDTE::CodeElementsPtr pElements = NULL;

	DeleteAllItems();

	if (FAILED(pElement->get_Children(&pElements)) || (pElements == NULL))
	{
		return E_FAIL;
	}

	long Count = 0;
	pElements->get_Count(&Count);

	for (long i = 1; i <= Count; i++)
	{
		_variant_t vt = i;
		EnvDTE::CodeElementPtr pElem = NULL;
		if (FAILED(pElements->Item(vt, &pElem)) || (pElem == NULL))
		{
			return E_FAIL;
		}

		VSParameter* NewParameter = new VSParameter;
		NewParameter->pElement = pElem;
		NewParameter->pParent = (VSElement*)this;
		if (FAILED(NewParameter->RetriveName()))
		{
			//delete NewParameter;
			//return E_FAIL;
		}
		if (FAILED(NewParameter->RetriveType()))
		{
			//delete NewParameter;
			//return E_FAIL;
		}
		Parameters.Add(NewParameter);
		
	}
	return S_OK;
}

HRESULT VSFunction::Remove()
{
	EnvDTE::CodeClassPtr pClass = pParent->pElement;
	if (pClass == NULL)
	{
		return E_FAIL;
	}
	
	return pClass->RemoveMember(_variant_t((EnvDTE::CodeElement*)pElement));

}

void VSFunction::DeleteAllItems()
{
	for (size_t i = 0; i < Parameters.GetCount(); i++)
	{
		delete Parameters[i];
	}
	Parameters.RemoveAll();
}

VSFunction::~VSFunction()
{
	DeleteAllItems();
}
// VSFunction
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// VSMapEntry


HRESULT VSMapEntry::GetEndPoint(EnvDTE::EditPoint** ppEditPoint)
{
	if (pElement != NULL)
	{
		return VSElement::GetEndPoint(ppEditPoint);
	}
	else
	{
		ATLASSERT(m_pEndPoint != NULL);
		return m_pEndPoint->CreateEditPoint(ppEditPoint);
	}
}

HRESULT VSMapEntry::GetStartPoint(EnvDTE::EditPoint** ppEditPoint)
{
	if (pElement != NULL)
	{
		return VSElement::GetStartPoint(ppEditPoint);
	}
	else
	{
		ATLASSERT(m_pStartPoint != NULL);
		return m_pStartPoint->CreateEditPoint(ppEditPoint);
	}
}

HRESULT VSMapEntry::Remove()
{
	ATLASSERT(m_pEndPoint != NULL);
	ATLASSERT(m_pStartPoint != NULL);

	m_pEndPoint->CharRight(1);
	return m_pStartPoint->Delete(_variant_t((EnvDTE::EditPoint*)m_pEndPoint));
}

VSMapEntry::VSMapEntry(const VSMapEntry& MapEntry)
{
	ElementType = EnvDTE::vsCMElementMapEntry;
}

VSMapEntry::~VSMapEntry()
{
}
// VSMapEntry
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// VSMap

HRESULT VSMap::RetriveMapEntries()
{
	DeleteAllItems();
	
	EnvDTE::EditPointPtr pEdit1 = NULL;
	_bstr_t str;
	_variant_t vt;
	
	//if (FAILED(GetStartPoint(&pEdit1)))
	//{
	//	return E_FAIL;
	//}
	if (m_pStartPoint == NULL)
	{
		ATLASSERT(pElement != NULL);
		if (FAILED(VSElement::GetStartPoint(&pEdit1)))
			return E_FAIL;
		pElement.Release();
		pEdit1->CreateEditPoint(&m_pStartPoint);
	}
	else
	{
		m_pStartPoint->CreateEditPoint(&pEdit1);
	}
	
	do
	{
		if (pEdit1->LineDown(1) != S_OK)
		{
			return E_FAIL;
		}
		if (pEdit1->StartOfLine() != S_OK)
		{
			return E_FAIL;
		}

		long LineLen;
		pEdit1->get_LineLength(&LineLen);
		vt = LineLen;
		pEdit1->GetText(vt, str.GetAddress());
		CString Line = str;

		long trimleftcount = Line.GetLength();
		Line.TrimLeft();
		trimleftcount -= Line.GetLength();
		Line.TrimRight(_T(" \t\r;"));

		if (Line.IsEmpty())
		{
			continue;
		}

		//проверка коментариев
		if (Line[0] == '/' && Line[1] == '/')
		{
			continue;
		}

		if (Line[0] == '/' && Line[1] == '*')
		{
			int n;
			_bstr_t ts;
			do 
			{
				_variant_t vt = 128;

				pEdit1->GetText(vt, ts.GetAddress());
				CString Str1 = ts;

				n = Str1.Find(_T("*/"));
				if (n != -1)
				{
					pEdit1->CharRight(n+1);
				}
				else
				{
					pEdit1->CharRight(ts.length()-2);
				}
			} while(n == -1 &&  ts.length() == 128);
			continue;
		}

		pEdit1->CharRight(trimleftcount);

		EnvDTE::EditPointPtr pStart = NULL;
		if (FAILED(pEdit1->CreateEditPoint(&pStart)))
		{
			return E_FAIL;
		}
		EnvDTE::EditPointPtr pEnd = NULL;
		if (FAILED(pEdit1->CreateEditPoint(&pEnd)))
		{
			return E_FAIL;
		}

		pStart->StartOfLine();
		pEnd->EndOfLine();
		ATLASSERT(pStart != NULL);
		ATLASSERT(pEnd != NULL);

		VSMapEntry* MapEntry = new VSMapEntry(pStart, pEnd);
		MapEntry->pParent = (VSElement*)this;

		int OpenBracket = Line.Find(_T('('));
		if (OpenBracket == -1)
		{
			MapEntry->Name = Line;
		}
		else
		{
			int CloseBracket = Line.Find(_T(')'), OpenBracket);
			if (CloseBracket == -1)
			{
				delete MapEntry;
				continue;
			}
			//это MapEntry
			MapEntry->Name = Line.Left(OpenBracket);
			MapEntry->Name.Trim();
			CString Entry;
			if (CloseBracket - OpenBracket > 1)
			{
				Entry = Line.Mid(OpenBracket+1, CloseBracket - OpenBracket - 1);
				Entry.Trim();
			}

			if (!Entry.IsEmpty())
			{
				int Bracket = 0;
				int StartPos = 0;
				for (int i1 = 0; i1 < Entry.GetLength(); i1++)
				{
					if (Entry[i1] == _T('<'))
					{
						Bracket++;
					}
					if (Entry[i1] == _T('>'))
					{
						Bracket--;
					}
					if (Entry[i1] == _T(','))
					{
						if (!Bracket)
						{
							VSParameter* Param = new VSParameter;
							Param->Name = Entry.Mid(StartPos, i1 - StartPos);
							Param->Name.Trim();
							StartPos = i1 + 1;
							Param->pParent = (VSElement*)this;
							MapEntry->Parameters.Add(Param);
						}
					}
				}
				VSParameter* Param = new VSParameter;
				Param->Name = Entry.Mid(StartPos);
				Param->Name.Trim();
				Param->pParent = (VSElement*)this;
				MapEntry->Parameters.Add(Param);
			}
		}
		if (!AddMapEntry(MapEntry))
			break;
	}while(true);

	return S_OK;
}

bool VSMap::AddMapEntry(VSMapEntry* pMapEntry)
{
	CString EndName;
	EndName = _T("END_") + Name + _T("_MAP");
	if (pMapEntry->Name == EndName)
	{
		pMapEntry->GetEndPoint(&m_pEndPoint);
		delete pMapEntry;
		return false;
	}

	MapEntries.Add(pMapEntry);
	return true;
}

bool VSMap::IsSelf()
{
	return (m_pStartPoint != NULL);
}

HRESULT VSMap::GetEndPoint(EnvDTE::EditPoint** ppEditPoint)
{
	ATLASSERT(m_pEndPoint != NULL);
	return m_pEndPoint->CreateEditPoint(ppEditPoint);
}

HRESULT VSMap::GetStartPoint(EnvDTE::EditPoint** ppEditPoint)
{
	ATLASSERT(m_pStartPoint != NULL);
	return m_pStartPoint->CreateEditPoint(ppEditPoint);
}

HRESULT VSMap::FindPlaceForNewItem(VSMapEntry* MapEntry, EnvDTE::EditPoint** ppStartPoint)
{
	//////////////////////////////////////////////////////////////////////////
	//поиск места для вставки
	EnvDTE::EditPointPtr pEditPoint1 = NULL;
	VSMapEntry* LastEntry = NULL;
	*ppStartPoint = NULL;
	if (MapEntries.GetCount())
	{
		for (size_t i = 0; i < MapEntries.GetCount(); i++)
		{
			if ((MapEntries[i])->m_pEndPoint != NULL)
			{
				LastEntry = MapEntries[i];
			}
		}

		if (LastEntry)
		{
			if (FAILED(LastEntry->GetEndPoint(&pEditPoint1)))
			{
				return E_FAIL;
			}
		}
	}
	else
	{
		if (FAILED(GetStartPoint(&pEditPoint1)) || pEditPoint1 == NULL)
		{
			return E_FAIL;
		}
		pEditPoint1->EndOfLine();
	}

	if (pEditPoint1 == NULL)
	{
		if (FAILED(GetStartPoint(&pEditPoint1)) || pEditPoint1 == NULL)
		{
			return E_FAIL;
		}
		pEditPoint1->EndOfLine();
	}
	//конец поиска места для вставки
	//////////////////////////////////////////////////////////////////////////
	*ppStartPoint = pEditPoint1.Detach();
	return S_OK;
}

HRESULT VSMap::InsertMapEntry(VSMapEntry* MapEntry)
{
	//ATLASSERT(pElement);

	EnvDTE::EditPointPtr pEditPoint1 = NULL;
	EnvDTE::EditPointPtr pEditPoint2 = NULL;
	_bstr_t s2;

	if (FAILED(FindPlaceForNewItem(MapEntry, &pEditPoint1)))
		return E_FAIL;
	
	if (FAILED(pEditPoint1->CreateEditPoint(&pEditPoint2)))
	{
		return E_FAIL;
	}
	//////////////////////////////////////////////////////////////////////////
	//генерация имени

	s2 = _T("\r\n") + MapEntry->Name+ _T('(');
	//добавление параметров
	size_t i = 0;
	
	if (MapEntry->Parameters.GetCount())
	{
		s2 += (LPCTSTR)((MapEntry->Parameters[i])->Name);
		for (i++; i < MapEntry->Parameters.GetCount(); i++)
		{
			s2 += (LPCTSTR)(_T(", ") + (MapEntry->Parameters[i])->Name);
		}
	}
	s2 += _T(")");
	//конец генерации имени
	//////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////
	//вставка
	if (FAILED(pEditPoint1->Insert(s2)))
	{
		return E_FAIL;
	}
	if (FAILED(pEditPoint2->CharRight(1)))
	{
		return E_FAIL;
	}
	//конец вставки
	//////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////
	//поиск начальной и конечной точек для вставленной записи
	pEditPoint2->StartOfLine();

	EnvDTE::EditPointPtr p1, p2;
	if (FAILED(pEditPoint2->CreateEditPoint(&p1)))
	{
		return E_FAIL;
	}
	if (FAILED(p1->CreateEditPoint(&p2)))
	{
		return E_FAIL;
	}
	p2->EndOfLine();
	MapEntry->m_pStartPoint = p1;
	MapEntry->m_pEndPoint = p2;
	MapEntry->pParent = (VSElement*)this;
	//конец поиска начальной и конечной точек для вставленной записи
	//////////////////////////////////////////////////////////////////////////
	
	//сдвигаем на необходимое количество табов
	if (FAILED(pEditPoint2->Indent(pEditPoint1, 2)))
	{
		return E_FAIL;
	}
	
	return S_OK;
}

HRESULT VSMap::InsertNewMap(EnvDTE::EditPointPtr pInsertAfter, bool bAfter /* = true*/)
{
	_bstr_t s2;
	if (bAfter)
	{
		s2 = _T("\r\n\r\nBEGIN_") + Name+ _T("_MAP") + Postfix + _T('(');
	}
	else
	{
		s2 = _T("BEGIN_") + Name+ _T("_MAP") + Postfix + _T('(');
	}
	
	size_t i = 0;

	if (MapParameters.GetCount())
	{
		s2 += (LPCTSTR)((MapParameters[i])->Name);
		for (i++; i < MapParameters.GetCount(); i++)
		{
			s2 += (LPCTSTR)(_T(", ") + (MapParameters[i])->Name);
		}
	}
	if (bAfter)
	{
		s2 += LPCTSTR(_T(")\r\nEND_") + Name + _T("_MAP") + Postfix + _T("()"));
	}
	else
	{
		s2 += LPCTSTR(_T(")\r\nEND_") + Name + _T("_MAP") + Postfix + _T("()\r\n\r\n"));
	}
	
	EnvDTE::EditPointPtr pEditPoint2 = NULL, pEditPoint1;
	
	if (FAILED(pInsertAfter->CreateEditPoint(&pEditPoint1)))
	{
		return E_FAIL;
	}

	if (FAILED(pInsertAfter->CreateEditPoint(&pEditPoint2)))
	{
		return E_FAIL;
	}

	if (FAILED(pInsertAfter->Insert(s2)))
	{
		return E_FAIL;
	}
	if (bAfter)
	{
		pEditPoint2->LineDown(2);
		pEditPoint1->LineDown(3);
	}
	else
	{
		pEditPoint1->LineDown(1);
	}
	pEditPoint2->StartOfLine();
	pEditPoint1->EndOfLine();

	pEditPoint2->Indent(pEditPoint1, 1);
	
	m_pStartPoint = pEditPoint2;
	m_pEndPoint = pEditPoint1;

	return S_OK;
}

HRESULT VSMap::Remove()
{
	EnvDTE::EditPointPtr pStart, pEnd;
	GetStartPoint(&pStart);
	GetEndPoint(&pEnd);
	HRESULT hRes = pStart->Delete(_variant_t((EnvDTE::EditPoint*)pEnd));

	return S_OK;
}

void VSMap::DeleteAllItems()
{
	for (size_t i1 = 0; i1 < MapParameters.GetCount(); i1++)
	{
		delete MapParameters[i1];
	}
	MapParameters.RemoveAll();

	for (size_t i2 = 0; i2 != MapEntries.GetCount(); i2++)
	{
		delete MapEntries[i2];
	}
	MapEntries.RemoveAll();
}

VSMap::~VSMap()
{
	DeleteAllItems();
}
// VSMap
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// VSMessageMap

VSMessageMap::~VSMessageMap()
{
	for (size_t i = 0; i < AltMaps.GetCount(); i++)
	{
		delete AltMaps[i];
	}
	AltMaps.RemoveAll();
}

HRESULT VSMessageMap::GetEndPoint(EnvDTE::EditPoint** ppEditPoint)
{
	if (AltMaps.GetCount())
	{
		for (int i = (int)AltMaps.GetCount() - 1; i >= 0; i--)
		{
			if (AltMaps[i]->m_pEndPoint)
			{
				return AltMaps[i]->GetEndPoint(ppEditPoint);
			}
		}
		return VSMap::GetEndPoint(ppEditPoint);
	}
	else
	{
		return VSMap::GetEndPoint(ppEditPoint);
	}
}

HRESULT VSMessageMap::ReFormatItems()
{
	return S_OK;
}

HRESULT VSMessageMap::ReplacePrefixEnd()
{
	EnvDTE::EditPointPtr pEditPoint1 = NULL;
	EnvDTE::EditPointPtr pEditPoint2 = NULL;
	GetEndPoint(&pEditPoint1);
	ATLASSERT(pEditPoint1 != NULL);
	pEditPoint1->StartOfLine();
	pEditPoint1->CreateEditPoint(&pEditPoint2);
	ATLASSERT(pEditPoint2 != NULL);

	pEditPoint2->EndOfLine();
	_bstr_t Line;
	pEditPoint1->GetText(_variant_t((LPDISPATCH)pEditPoint2), Line.GetAddress());
	CString strLine = Line;
	strLine.Replace(_T("END_MSG_MAP"), _T("END_MSG_MAP_EX"));
	Line = strLine;
	// 3 = vsEPReplaceTextKeepMarkers |	vsEPReplaceTextNormalizeNewlines
	pEditPoint1->ReplaceText(_variant_t((LPDISPATCH)pEditPoint2), Line, 3);
	pEditPoint2->EndOfLine();
	m_pEndPoint = pEditPoint2;

	return S_OK;
}

HRESULT VSMessageMap::InsertAltMap(VSMessageMap* pAltMap)
{
	EnvDTE::EditPointPtr pEditPoint1 = NULL;
	EnvDTE::EditPointPtr pEditPoint2 = NULL;
	_bstr_t s2;

	GetEndPoint(&pEditPoint1);
	pEditPoint1->LineUp(1);
	pEditPoint1->EndOfLine();
	
	if (FAILED(pEditPoint1->CreateEditPoint(&pEditPoint2)))
	{
		return E_FAIL;
	}
	//////////////////////////////////////////////////////////////////////////
	//генерация имени

	s2 = _T("\r\nALT_MSG_MAP(") + pAltMap->Name+ _T(')');
	
	//конец генерации имени
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//вставка
	if (FAILED(pEditPoint1->Insert(s2)))
	{
		return E_FAIL;
	}
	if (FAILED(pEditPoint2->LineDown(1)))
	{
		return E_FAIL;
	}
	//конец вставки
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//поиск начальной и конечной точек для вставленной записи
	pEditPoint2->StartOfLine();
		
	EnvDTE::EditPointPtr p1, p2;
	if (FAILED(pEditPoint2->CreateEditPoint(&p1)))
	{
		return E_FAIL;
	}
	if (FAILED(p1->CreateEditPoint(&p2)))
	{
		return E_FAIL;
	}
	p2->EndOfLine();

	VSMessageMap* pCurMap = this;
	for (size_t i = 0; i < AltMaps.GetCount(); i++)
	{
		if (AltMaps[i]->m_pStartPoint != NULL)
		{
			ATLASSERT(AltMaps[i]->m_pEndPoint != NULL);
			pCurMap = AltMaps[i];
		}
	}
	EnvDTE::EditPointPtr pOldEnd = pCurMap->m_pEndPoint;
	pAltMap->m_pStartPoint = p1;
	pAltMap->m_pEndPoint = pOldEnd;
	pCurMap->m_pEndPoint = p2;

	//конец поиска начальной и конечной точек для вставленной записи
	//////////////////////////////////////////////////////////////////////////

	//сдвигаем на необходимое количество табов
	if (FAILED(pEditPoint2->Indent(pEditPoint1, 1)))
	{
		return E_FAIL;
	}

	return S_OK;
}

bool VSMessageMap::AddMapEntry(VSMapEntry* pMapEntry)
{
	CString EndName;
	EndName = _T("END_") + Name + _T("_MAP");
	VSMessageMap* pCurMap = this;
	if (AltMaps.GetCount())
	{
		pCurMap = AltMaps[AltMaps.GetCount() - 1];
	}
	if (pMapEntry->Name == EndName)
	{
		if (!Postfix.IsEmpty())
		{
			bCorrectEnd = false;
		}
		pMapEntry->GetEndPoint(&(pCurMap->m_pEndPoint));
		delete pMapEntry;
		return false;
	}
	if (!Postfix.IsEmpty())
	{
		EndName += Postfix;
		if (pMapEntry->Name == EndName)
		{
			pMapEntry->GetEndPoint(&(pCurMap->m_pEndPoint));
			delete pMapEntry;
			return false;
		}
	}
	if (pMapEntry->Name == _T("ALT_MSG_MAP"))
	{
		if (pMapEntry->Parameters.GetCount() == 1)
		{
			CString AltName = pMapEntry->Parameters[0]->Name;
			VSMessageMap* pNewAltMap = new VSMessageMap;
			pMapEntry->GetStartPoint(&pNewAltMap->m_pStartPoint);
			pMapEntry->GetEndPoint(&pCurMap->m_pEndPoint);
			pNewAltMap->Name = AltName;
			pNewAltMap->pParent = (VSElement*)this;
			AltMaps.Add(pNewAltMap);
		}
		delete pMapEntry;
		return true;
	}
	pMapEntry->pParent = pCurMap;
	pCurMap->MapEntries.Add(pMapEntry);
	
	return true;
}

MessageEntryType VSMessageMap::GetEntryType(VSMapEntry* MapEntry)
{
	if (MapEntry->Name.Left(4) == _T("MSG_"))
		return MESSAGE_WINDOWS;
	if (MapEntry->Name.Left(15) == _T("MESSAGE_HANDLER"))
	{
		VSParameter* pParam = MapEntry->Parameters[0];
		if (pParam->Name.Left(3) == _T("WM_"))
			return MESSAGE_WINDOWS;
		else
		{
			return MESSAGE_UNKNOWN;
		}
	}
	if (MapEntry->Name.Left(8) == _T("COMMAND_"))
		return MESSAGE_COMMAND;
	if (MapEntry->Name.Left(18) == _T("REFLECTED_COMMAND_"))
		return MESSAGE_COMMAND;
	if (MapEntry->Name.Left(7) == _T("NOTIFY_"))
		return MESSAGE_NOTIFY;
	if (MapEntry->Name.Left(17) == _T("REFLECTED_NOTIFY_"))
		return MESSAGE_NOTIFY;
	if (MapEntry->Name == _T("FORWARD_NOTIFICATIONS") ||
		MapEntry->Name == _T("DEFAULT_REFLECTION_HANDLER") ||
		MapEntry->Name.Left(8) == _T("REFLECT_"))
		return MESSAGE_FORWARD_REFLECT;
	if (MapEntry->Name == _T("CHAIN_MSG_MAP"))
		return MESSAGE_CHAIN_MAP;
	return MESSAGE_UNKNOWN;
}

HRESULT VSMessageMap::FindPlaceForNewItem(VSMapEntry* MapEntry, EnvDTE::EditPoint** ppStartPoint)
{
	//handlers are inserted by groups
	//1) Windows message
	//2) WM_COMMAND messages
	//3) WM_NOTIFY messages
	//4) All other messages ( user messages)
	//5) CHAIN_MSG_MAP
	//6) REFLECT_NOTIFICATIONS и FORWARD_NOTIFICATIONS etc
	
	if (!bSortItems)
		return VSMap::FindPlaceForNewItem(MapEntry, ppStartPoint);
	
	MessageEntryType NewEntryType, ExistEntryType;
	NewEntryType = GetEntryType(MapEntry);
	//if (NewEntryType == MESSAGE_CHAIN_MAP)
	//	return VSMap::FindPlaceForNewItem(MapEntry, ppStartPoint);
	if (NewEntryType == MESSAGE_FORWARD_REFLECT)
		return VSMap::FindPlaceForNewItem(MapEntry, ppStartPoint);
	
	VSMapEntry* pLastWindows = NULL, *pLastCommand = NULL, *pLastNotify = NULL,
		*pLastUnknown = NULL, *pLastForwardReflect = NULL;
	*ppStartPoint = NULL;
	
	//////////////////////////////////////////////////////////////////////////
	//поиск места для вставки
	EnvDTE::EditPointPtr pEditPoint1 = NULL;
	VSMapEntry* LastEntry = NULL;
	*ppStartPoint = NULL;
	if (MapEntries.GetCount())
	{
		for (size_t i = 0; i < MapEntries.GetCount(); i++)
		{
			//проверяем, чтобы не было новым элементом карты
			if ((MapEntries[i])->m_pEndPoint)
			{
				ExistEntryType = GetEntryType(MapEntries[i]);
				if (ExistEntryType == NewEntryType)
					LastEntry = MapEntries[i];
				switch(ExistEntryType) 
				{
				case MESSAGE_WINDOWS:
					pLastWindows = MapEntries[i];
					break;
				case MESSAGE_COMMAND:
					pLastCommand = MapEntries[i];
					break;
				case MESSAGE_NOTIFY:
					pLastNotify = MapEntries[i];
					break;
				case MESSAGE_UNKNOWN:
					pLastUnknown = MapEntries[i];
					break;
				case MESSAGE_FORWARD_REFLECT:
					pLastForwardReflect = MapEntries[i];
					break;
				}
			}
		}

		if (LastEntry)
		{
			HRESULT hr = LastEntry->GetEndPoint(&pEditPoint1);
			ATLASSERT(SUCCEEDED(hr));
			if (FAILED(LastEntry->GetEndPoint(&pEditPoint1)))
			{
				return E_FAIL;
			}
		}
		else
		{
			switch(NewEntryType) 
			{
			case MESSAGE_WINDOWS:
				{
					if (FAILED(GetStartPoint(&pEditPoint1)) || (pEditPoint1 == NULL))
					{
						return E_FAIL;
					}
					pEditPoint1->EndOfLine();
				}
				break;
			case MESSAGE_COMMAND:
				{
					if (pLastWindows)
					{
						pLastWindows->GetEndPoint(&pEditPoint1);
					}
					else
					{
						if (FAILED(GetStartPoint(&pEditPoint1)) || (pEditPoint1 == NULL))
						{
							return E_FAIL;
						}
						pEditPoint1->EndOfLine();
					}
				}
				break;
			case MESSAGE_NOTIFY:
				{
					if (pLastWindows)
						pLastNotify = pLastWindows;
					if (pLastCommand)
						pLastNotify = pLastCommand;
					if (pLastNotify)
					{
						pLastNotify->GetEndPoint(&pEditPoint1);
					}
					else
					{
						if (FAILED(GetStartPoint(&pEditPoint1)) || pEditPoint1 == NULL)
						{
							return E_FAIL;
						}
						pEditPoint1->EndOfLine();
					}
				}
				break;
			case MESSAGE_UNKNOWN:
				{
					if (pLastWindows)
						pLastUnknown = pLastWindows;
					if (pLastCommand)
						pLastUnknown = pLastCommand;
					if (pLastNotify)
						pLastUnknown = pLastNotify;
					if (pLastUnknown)
					{
						pLastUnknown->GetEndPoint(&pEditPoint1);
					}
					else
					{
						if (FAILED(GetStartPoint(&pEditPoint1)) || (pEditPoint1 == NULL))
						{
							return E_FAIL;
						}
						pEditPoint1->EndOfLine();
					}
				}
				break;
			case MESSAGE_CHAIN_MAP:
				{
					if (!pLastForwardReflect)
						return VSMap::FindPlaceForNewItem(MapEntry, ppStartPoint);
					else
					{
						pLastForwardReflect->GetEndPoint(&pEditPoint1);
					}
				}
				break;
			}
		}
	}
	else
	{
		if (FAILED(GetStartPoint(&pEditPoint1)) || (pEditPoint1 == NULL))
		{
			return E_FAIL;
		}
		pEditPoint1->EndOfLine();
	}

	//конец поиска места для вставки
	//////////////////////////////////////////////////////////////////////////
	*ppStartPoint = pEditPoint1.Detach();

	return S_OK;
}

HRESULT VSMessageMap::Remove()
{
	if (pParent->ElementType == EnvDTE::vsCMElementClass)
	{
		//удаляем всю карту сообщений, а не ALT карту
		return VSMap::Remove();
	}
	EnvDTE::EditPointPtr pStart, pEnd;
	GetEndPoint(&pEnd);
	GetStartPoint(&pStart);
	pEnd->StartOfLine();
	pStart->Delete(_variant_t((EnvDTE::EditPoint*)pEnd));

	return S_OK;
}

bool VSMessageMap::FindMapEntryByMessage(CString Message, VSMessageMap* pMap, CAtlArray<VSMapEntry*>& MapEntries)
{
	bool bFind = false;
	//only windows messages
	for (size_t i = 0; i < pMap->MapEntries.GetCount(); i++)
	{
		CString Name = pMap->MapEntries[i]->Name;
		if (Name == _T("MESSAGE_HANDLER") 
			|| Name == _T("MESSAGE_HANDLER_EX"))
		{
			if (pMap->MapEntries[i]->Parameters[0]->Name == Message)
			{
				MapEntries.Add(pMap->MapEntries[i]);
				bFind = true;
			}
		}
		if (Name.Left(4) == _T("MSG_"))
		{
			if (Message == Name.Mid(4))
			{
				MapEntries.Add(pMap->MapEntries[i]);
				bFind = true;
			}
		}
	}
	return bFind;
}