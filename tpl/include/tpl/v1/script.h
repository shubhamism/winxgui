/* -------------------------------------------------------------------------
// WINX: a C++ template GUI library - MOST SIMPLE BUT EFFECTIVE
// 
// This file is a part of the WINX Library.
// The use and distribution terms for this software are covered by the
// Common Public License 1.0 (http://opensource.org/licenses/cpl.php)
// which can be found in the file CPL.txt at this distribution. By using
// this software in any fashion, you are agreeing to be bound by the terms
// of this license. You must not remove this notice, or any other, from
// this software.
// 
// Module: tpl/v1/script.h
// Creator: xushiwei
// Email: xushiweizh@gmail.com
// Date: 2006-12-2 13:48:53
// 
// $Id: script.h,v 1.4 2006/12/24 11:03:44 xushiwei Exp $
// -----------------------------------------------------------------------*/
#ifndef __TPL_V1_SCRIPT_H__
#define __TPL_V1_SCRIPT_H__

// -------------------------------------------------------------------------

#ifndef __TPL_V1_SCRIPT_IN_H__
#include "script_in.h"
#endif

#ifndef __TPL_V1_SCRIPT_OUT_H__
#include "script_out.h"
#endif

// -------------------------------------------------------------------------

class _Text : public std::string
{
public:
	typedef std::string _Base;
	typedef _Base::value_type char_type;

	_Text() {}
	_Text(const char_type* str) : _Base(str) {}
	_Text(const std::string& str) : _Base(str) {}
};

// -------------------------------------------------------------------------

template <class ArchiveIn, class ArchiveOut>
STDMETHODIMP TextConvert(
						 ArchiveIn& script_in_ar,
						 ArchiveIn& script_out_ar,
						 ArchiveIn& in,
						 ArchiveOut& out
						 )
{
	typedef KScriptInParser<ArchiveIn, _Text> Parser;
	typedef typename Parser::NodeList NodeList;
	typedef typename Parser::VariantRecycleBin VariantRecycleBin;
	
	HRESULT hr;
	NodeList vars;
	VariantRecycleBin recycle;
	
	hr = Parser::Load(vars, in, script_in_ar, recycle);
	if (hr != S_OK)
		return hr;

	return TemplateReplace(script_out_ar, out, vars);
}

template <class ArchiveIn, class ArchiveOut>
STDMETHODIMP TextConvert2Pascal(
						 ArchiveIn& script_in_ar,
						 ArchiveIn& script_out_ar,
						 ArchiveIn& in,
						 ArchiveOut& out
						 )
{
	typedef KScriptInParser<ArchiveIn, _Text> Parser;
	typedef typename Parser::NodeList NodeList;
	typedef typename Parser::VariantRecycleBin VariantRecycleBin;
	
	HRESULT hr;
	NodeList vars;
	VariantRecycleBin recycle;
	
	hr = Parser::Load(vars, in, script_in_ar, recycle);
	if (hr != S_OK)
		return hr;

	if (S_OK != Node2Pascal(vars, recycle))
		return E_FAIL;
	else
	{
		PrintVariantList(vars);
		return TemplateReplace(script_out_ar, out, vars);
	}
}

// -------------------------------------------------------------------------

#ifndef __TPL_V1_SCRIPT_DEBUG_H__
#include "script_debug.h"
#endif

template <class ArchiveIn>
STDMETHODIMP TextConvertTest(
						 ArchiveIn& script_in_ar,
						 ArchiveIn& in
						 )
{
	typedef KScriptInParser<ArchiveIn, _Text> Parser;
	typedef typename Parser::NodeList NodeList;
	typedef typename Parser::VariantRecycleBin VariantRecycleBin;
	
	HRESULT hr;
	NodeList vars;
	VariantRecycleBin recycle;
	
	hr = Parser::Load(vars, in, script_in_ar, recycle);
	if (hr != S_OK)
		return hr;

	PrintVariantList(vars);
	return S_OK;
}

// -------------------------------------------------------------------------
// $Log: script.h,v $
// Revision 1.4  2006/12/24 11:03:44  xushiwei
// Manual Tool Version 1.0
//
// Revision 1.1  2006/12/02 06:44:18  xushiwei
// Text Processing Library - Version 1.0
//

#endif /* __TPL_V1_SCRIPT_H__ */
