/* -------------------------------------------------------------------------
//	文件名		：	text/script_error_report.h
//	创建者		：	许式伟
//	创建时间	：	5/5/2003 12:35:54 AM
//	功能描述	：	
//
//	$Id: script_error_report.h,v 1.2 2006/06/10 05:37:09 xushiwei Exp $
// -----------------------------------------------------------------------*/
#ifndef __KFC_TEXT_SCRIPT_ERROR_REPORT_H__
#define __KFC_TEXT_SCRIPT_ERROR_REPORT_H__

#ifndef __KFC_TEXT_SCRIPT_DEBUG_H__
#include "script_debug.h"
#endif

_TEXT_SCRIPT_BEGIN

// -------------------------------------------------------------------------
// log file

class DefaultLog : public MultiLog<2>
{
public:
	DefaultLog()
	{
		m_log[0].Open(stderr);
		m_log[1].Open("_ErrorLog_.txt");
	}
};

template <class Unused>
class KScriptLogT
{
public:
	static DefaultLog log;
};

template <class Unused>
DefaultLog KScriptLogT<Unused>::log;

typedef KScriptLogT<void> KScriptLog;

// -------------------------------------------------------------------------

template <class _Archive, class _String>
class KScriptErrorReport : public KScriptLog
{
public:
	typedef _String String;
	typedef _Archive Archive;
	typedef typename _Archive::char_type char_type;
	typedef typename _Archive::pos_type pos_type;

	static const char_type cint[];
	static const char_type csymbol[];
	static const char_type csymbol_or_all[];
	static const char_type cstring[];
	static const char_type blank[];
	static const char_type quomark[];

	enum error_type
	{
		error_except = 0,
		error_unexcept = 1,
	};
	
public:
	KScriptErrorReport()
	{
		_error_type = error_except;
		_error_pos = 0;
	}
	STDMETHODIMP_(void) SetContext(Archive& src, const String& context)
	{
		_pos = src.tell();
		_context = context;
	}
	STDMETHODIMP_(void) Except(Archive& src, const char_type* szMsg)
	{
		if (_error_pos < _pos)
		{
			_error_type = error_except;
			_error_pos = _pos;
			_error_context = _context;
			_error_msg = szMsg;
		}
		else if (_error_pos == _pos && _error_context != _context)
		{
			_error_type = error_unexcept;
		}
	}
	STDMETHODIMP_(int) ErrorLine(Archive& src) const
	{
		int line_no = 1;
		src.seek(0);
		for (pos_type pos = 0; pos <= _error_pos; ++pos)
		{
			switch ( src.get() )
			{
			case '\n':
				++line_no;
			}
		}
		return line_no;
	}
	STDMETHODIMP_(void) ReportError(Archive& src)
	{
		int errline = ErrorLine(src);
		if (_error_type == error_except)
		{
			const char_type* context = _error_context.c_str();
			if (_error_msg)
				log.Print("Line(%d) Error: '%s(%s)' is excepted.\n", errline, context, _error_msg);
			else
				log.Print("Line(%d) Error: '%s' is excepted.\n", errline, context);
		}
		else
		{
			src.unget();			
			log.Print("Line(%d) Error: unexcepted character '%c'.\n", errline, src.get());
		}
	}

protected:
	pos_type _error_pos, _pos;
	error_type _error_type;
	const char_type* _error_msg;
	String _error_context;
	String _context;
};

// -------------------------------------------------------------------------

#define ERROR_REPORT_CONST_STRING											\
template <class _Archive, class _String>									\
const typename KScriptErrorReport<_Archive, _String>::char_type				\
	KScriptErrorReport<_Archive, _String>::

ERROR_REPORT_CONST_STRING cint[] = { 'i', 'n', 't', 'c', 'o', 'n', 's', 't', '\0' };
ERROR_REPORT_CONST_STRING csymbol[] = { 's', 'y', 'm', 'b', 'o', 'l', '\0' };
ERROR_REPORT_CONST_STRING csymbol_or_all[] = { 's', 'y', 'm', 'b', 'o', 'l', ' ', 'o', 'r', ' ', '*', '\0' };
ERROR_REPORT_CONST_STRING cstring[] = { 'c', 'o', 'n', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g', '\0' };
ERROR_REPORT_CONST_STRING blank[]	  = { 'b', 'l', 'a', 'n', 'k', '\0' };
ERROR_REPORT_CONST_STRING quomark[]	  = { 'q', 'u', 'o', 'm', 'a', 'r', 'k', '\0' };

// -------------------------------------------------------------------------
// $Log: script_error_report.h,v $
// Revision 1.2  2006/06/10 05:37:09  xushiwei
// 支持多个Log终端同时输出: stderr, file("_ErrorLog_.txt")
//

_TEXT_SCRIPT_END

#endif /* __KFC_TEXT_SCRIPT_ERROR_REPORT_H__ */
