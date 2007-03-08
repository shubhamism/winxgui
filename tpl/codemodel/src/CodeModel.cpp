// src\CodeModel.cpp : Implementation of CCodeModel
#include "stdafx.h"
#include "CodeModel.h"

/////////////////////////////////////////////////////////////////////////////
// CCodeModel

STDMETHODIMP CCodeModel::get_CodeElements(CodeElements **pVal)
{
	return E_NOTIMPL;
}

STDMETHODIMP CCodeModel::get_IsCaseSensitive( 
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pSensitive)
{
	return E_NOTIMPL;
}

STDMETHODIMP CCodeModel::Remove( 
    /* [in] */ VARIANT Element)
{
	return E_NOTIMPL;
}

STDMETHODIMP CCodeModel::AddNamespace( 
    /* [in] */ BSTR Name,
    /* [in] */ VARIANT Location,
    /* [in] */ VARIANT Position,
    /* [retval][out] */ CodeNamespace __RPC_FAR *__RPC_FAR *ppCodeNamespace)
{
	return E_NOTIMPL;
}

STDMETHODIMP CCodeModel::AddClass( 
    /* [in] */ BSTR Name,
    /* [in] */ VARIANT Location,
    /* [in] */ VARIANT Position,
    /* [in] */ VARIANT Bases,
    /* [in] */ VARIANT ImplementedInterfaces,
    /* [retval][out] */ CodeClass __RPC_FAR *__RPC_FAR *ppCodeClass)
{
	return E_NOTIMPL;
}

STDMETHODIMP CCodeModel::AddFunction( 
    /* [in] */ BSTR Name,
    /* [in] */ VARIANT Location,
    /* [in] */ enum vsCMFunction Kind,
    /* [in] */ VARIANT Type,
    /* [in] */ VARIANT Position,
    /* [in] */ enum vsCMAccess Access,
    /* [retval][out] */ CodeFunction __RPC_FAR *__RPC_FAR *ppCodeFunction)
{
	return E_NOTIMPL;
}

STDMETHODIMP CCodeModel::AddVariable( 
    /* [in] */ BSTR Name,
    /* [in] */ VARIANT Location,
    /* [in] */ VARIANT Type,
    /* [in] */ VARIANT Position,
    /* [in] */ enum vsCMAccess Access,
    /* [retval][out] */ CodeVariable __RPC_FAR *__RPC_FAR *ppCodeVariable)
{
	return E_NOTIMPL;
}

STDMETHODIMP CCodeModel::IsValidID( 
    /* [in] */ BSTR Name,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pValid)
{
	return E_NOTIMPL;
}
