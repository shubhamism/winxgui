// src\CodeElement.cpp : Implementation of CCodeElement
#include "stdafx.h"
#include "Codemodel.h"
#include "src\CodeElement.h"

/////////////////////////////////////////////////////////////////////////////
// CCodeElement


STDMETHODIMP CCodeElement::get_Kind(enum vsCMElemen *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CCodeElement::put_Kind(enum vsCMElemen newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CCodeElement::get_IsCodeType(VARIANT_BOOL *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CCodeElement::put_IsCodeType(VARIANT_BOOL newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CCodeElement::get_InfoLocation(enum vsCMInfoLocation *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CCodeElement::get_Children(CodeElements **pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CCodeElement::put_Children(CodeElements *newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CCodeElement::get_StartPoint(TextPoint **pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CCodeElement::get_EndPoint(TextPoint **pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}
