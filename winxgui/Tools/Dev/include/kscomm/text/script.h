/* -------------------------------------------------------------------------
//	文件名		：	text/script.h
//	创建者		：	许式伟
//	创建时间	：	2003-4-30 11:04:00
//	功能描述	：	
//
// -----------------------------------------------------------------------*/
#ifndef __KFC_TEXT_SCRIPT_H__
#define __KFC_TEXT_SCRIPT_H__

#ifndef __KFC_TEXT_SCRIPT_IN_H__
#include "script_in.h"
#endif

#ifndef __KFC_TEXT_SCRIPT_OUT_H__
#include "script_out.h"
#endif

_TEXT_SCRIPT_BEGIN

// -------------------------------------------------------------------------

class _Text : public std::string
{
public:
	typedef std::string _Base;
	typedef _Base::value_type char_type;

	_Text() {}
	_Text(const char_type* str) : _Base(str) {}
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

#ifndef __KFC_TEXT_SCRIPT_DEBUG_H__
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

_TEXT_SCRIPT_END

#endif /* __KFC_TEXT_SCRIPT_H__ */
