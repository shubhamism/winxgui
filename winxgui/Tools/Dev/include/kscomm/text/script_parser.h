/* -------------------------------------------------------------------------
//	文件名		：	text/script_parser.h
//	创建者		：	许式伟
//	创建时间	：	4/20/2003 19:10:13
//	功能描述	：	
//		1) 4/20/2003 19:10:13
//			输入脚本读取的核心模块，本文件内容不涉及具体的脚本语法，而针对抽象的Rule。
//			具体的脚本语法处理参考: text/script_in.h
//		2) 4/30/2003 13:19:03	移植到Linux
//		3) 5/3/2003	 19:29:01	通配符*支持, 见 _MatchAll()
//		4) 5/4/2003	 23:20:11	增加ErrorReport
//		5) 5/5/2003	 15:20:43 	支持()、[]、*{}
//		6) 8/22/2003 14:30:23	支持*[]，用于辅助通配符*
//	$Id: script_parser.h,v 1.6 2006/06/10 05:36:50 xushiwei Exp $
// -----------------------------------------------------------------------*/
#ifndef __KFC_TEXT_SCRIPT_PARSER_H__
#define __KFC_TEXT_SCRIPT_PARSER_H__

#ifndef __KFC_ALLOCATOR_AUTOFREE_H__
#include <kfc/allocator/autofree.h>
#endif

#ifndef __KFC_ALGO_KMPFIND_H__
#include "gpl/kmpfind.h"	// for _MatchAll()
#endif

#ifndef __KFC_TEXT_SCRIPT_BASE_H__
#include "script_base.h"
#endif

#ifndef __KFC_TEXT_SCRIPT_VARIANT_H__
#include "script_variant.h"
#endif

#ifndef __KFC_TEXT_SCRIPT_ERROR_REPORT_H__
#include "script_error_report.h"
#endif

#ifndef TEXT_SCRIPT_API
#define TEXT_SCRIPT_API				HRESULT __stdcall
#define TEXT_SCRIPT_API_(type)		type __stdcall
#endif

#ifndef SCRIPT_RULE_API
#define SCRIPT_RULE_API				static HRESULT __stdcall
#endif

#ifndef TEXT_SCRIPT_ERROR
#define TEXT_SCRIPT_ERROR(msg)
#endif

#ifndef E_UNKNOWN_SCRIPT_OP
#define E_UNKNOWN_SCRIPT_OP			E_FAIL
#endif

#ifndef E_UNKNOWN_RULE
#define E_UNKNOWN_RULE				E_FAIL
#endif

#define S_MATCH_EOF					0x123

// -------------------------------------------------------------------------

#ifndef ERRMSG
#define ERRMSG						printf
#endif

#define _CHECK_HR(hr)				NULL

// -------------------------------------------------------------------------

#if defined(_DEBUG) && defined(DEBUG_SCRIPT)
#define _StringImp					String
#define HR_TRACE					else printf
#define SCRIPT_TRACE				printf
#else
#define _StringImp					_NullString<char_type>
#define HR_TRACE(fmt, arg)			0
#define SCRIPT_TRACE				0
#endif

#if !defined(NO_PRETTY_PRINT)
#define _PrettyPrint(strc)			PrettyPrint(strc)
#else
#define _PrettyPrint(strc)
#endif

_TEXT_SCRIPT_BEGIN

// -------------------------------------------------------------------------

template <class _Archive, class _Variant, class _RecyleBin>
class KBuiltinRules
{
public:
	typedef _Variant Variant;
	typedef _Archive Archive;
	typedef _RecyleBin RecycleBin;
	typedef typename _Variant::String String;
	typedef typename _Archive::size_type size_type;
	typedef typename _Archive::char_type char_type;
	typedef typename _Archive::int_type int_type;
	typedef typename _Archive::pos_type pos_type;
	
	typedef KScriptErrorReport<Archive, String> ErrorReport;

	enum { endch = Archive::endch };
	
public:
	SCRIPT_RULE_API match_blank(Archive& src, ErrorReport& report)
	{
		int_type ch = GetChar(src);
		if (IsWhiteChar(ch))
			return S_OK;
		UngetChar(src, ch);
		report.Except(src, ErrorReport::blank);
		return E_UNEXPECTED;
	}

	SCRIPT_RULE_API match_quomark(Archive& src, ErrorReport& report)
	{
		SkipWhiteChars(src);
		int_type ch = GetChar(src);
		if (ch == '\"')
			return S_OK;
		UngetChar(src, ch);
		report.Except(src, ErrorReport::quomark);
		return E_UNEXPECTED;
	}

	SCRIPT_RULE_API match_csymbol(Archive& src, ErrorReport& report)
	{
		SkipWhiteChars(src);
		_StringImp sym;
		HRESULT hr = GetCLangSymbol(src, sym);
		if (FAILED(hr))
			report.Except(src, ErrorReport::csymbol);
		HR_TRACE("---> _csymbol: \"%s\"\n", ToCStr(sym));
		return hr;
	}

	SCRIPT_RULE_API match_matchrule(Archive& src, ErrorReport& report)
	{
		int_type ch = SkipWhiteCharsGetChar(src);
		if (ch == '*')
			return S_OK;
		if (ch != '!')
			UngetChar(src, ch);
		_StringImp sym;
		HRESULT hr = GetCLangSymbol(src, sym);
		if (FAILED(hr))
			report.Except(src, ErrorReport::csymbol_or_all);
		return hr;
	}

	SCRIPT_RULE_API match_csymbol_or_all(Archive& src, ErrorReport& report)
	{
		int_type ch = SkipWhiteCharsGetChar(src);
		if (ch == '*')
			return S_OK;
		UngetChar(src, ch);
		_StringImp sym;
		HRESULT hr = GetCLangSymbol(src, sym);
		if (FAILED(hr))
			report.Except(src, ErrorReport::csymbol_or_all);
		return hr;
	}

	SCRIPT_RULE_API match_cint(Archive& src, ErrorReport& report)
	{
		SkipWhiteChars(src);
		int intVal;
		HRESULT hr = GetCLangIntConst(src, intVal);
		if (FAILED(hr))
			report.Except(src, ErrorReport::cint);
		HR_TRACE("---> _cint: \"%d\"\n", intVal);
		return hr;
	}
	
	SCRIPT_RULE_API match_eol(Archive& src, ErrorReport& report)
	{
		SCRIPT_TRACE("---> _eol\n");
		for (;;)
		{
			switch ( GetChar(src) )
			{
			case '\n': case endch:
				return S_OK;
			}
		}
	}

	SCRIPT_RULE_API match_ceol(Archive& src, ErrorReport& report)
	{
		SCRIPT_TRACE("---> _ceol\n");
		int_type ch;
		for (;;)
		{
			switch ( GetChar(src) )
			{
			case '\\':
				while ( (ch = GetChar(src)) == '\r' || ch == '\n' );
				UngetChar(src, ch);
				break;

			case '\n': case endch:
				return S_OK;
			}
		}
	}

	SCRIPT_RULE_API match_eof(Archive& src, ErrorReport& report)
	{
		int_type ch = SkipWhiteCharsGetChar(src);
		UngetChar(src, ch);
		return ch == Archive::endch ? S_MATCH_EOF : E_UNEXPECTED;
	}
	
	SCRIPT_RULE_API match_cstring(Archive& src, ErrorReport& report)
	{
		SkipWhiteChars(src);
		_StringImp strc;
		HRESULT hr = GetCLangStringConst(src, strc);
		if (FAILED(hr))
			report.Except(src, ErrorReport::cstring);
		HR_TRACE("---> _cstring: \"%s\"\n", ToCStr(strc));
		return hr;
	}

	SCRIPT_RULE_API assign_cstring(
		Archive& src, Variant& var, pos_type here, RecycleBin& recycle)
	{
		SkipWhiteChars(src);
		String strc;
		HRESULT hr = GetCLangStringConst(src, strc);
		var.vt = Variant::vtAtom;
		var.atomVal = recycle.NewAtom(strc);
		return hr;
	}

	SCRIPT_RULE_API assign_cint(
		Archive& src, Variant& var, pos_type here, RecycleBin& recycle)
	{
		SkipWhiteChars(src);
		var.vt = Variant::vtInt;
		return GetCLangIntConst(src, var.intVal);
	}
	
	SCRIPT_RULE_API assign_str_pretty(
		Archive& src, Variant& var, pos_type here, RecycleBin& recycle)
	{
		String strc;
		size_type strc_size = here - src.tell();
		if ((int)strc_size > 0)
		{
			strc.resize(strc_size);
			src.get(&strc[0], strc_size);
			_PrettyPrint(strc);
		}
		var.vt = Variant::vtAtom;
		var.atomVal = recycle.NewAtom(strc);
		return S_OK;
	}

	SCRIPT_RULE_API assign_str(
		Archive& src, Variant& var, pos_type here, RecycleBin& recycle)
	{
		SkipWhiteChars(src);
		String strc;
		size_type strc_size = here - src.tell();
		if ((int)strc_size > 0)
		{
			strc.resize(strc_size);
			src.get(&strc[0], strc_size);
		}
		var.vt = Variant::vtAtom;
		var.atomVal = recycle.NewAtom(strc);
		return S_OK;
	}
	
	SCRIPT_RULE_API assign_eol(
		Archive& src, Variant& var, pos_type here, RecycleBin& recycle)
	{
		int_type ch;
		String strc;
		for (;;)
		{
			switch ( ch = GetChar(src) )
			{
			case '\r':
				if (PeekChar(src) == '\n')
					GetChar(src);
			case '\n': case endch:
				var.vt = Variant::vtAtom;
				var.atomVal = recycle.NewAtom(strc);
				return S_OK;
			}
			AppendChar(strc, ch);
		}
	}
};

// -------------------------------------------------------------------------

#pragma pack(1)

template <class _String>
struct KRule
{
	typedef _String String;
	typedef typename String::value_type char_type;
	typedef std::list<KRule> RuleList;
	typedef std::map<String, KRule> RuleMap;
	
	struct MatchRule
	{
		String	rule_name;
		String	var_name;
	};

	int op : 31;
	int f_no_subtag : 1;
	union
	{
		String*	string_const;
		MatchRule* mrule;
		KRule* rule;
		KRule* repeat_rule;
		RuleList* or_rules;
		RuleList* and_rules;
		void* lpVal;
	};

	enum RuleType
	{
		match_none = 0x0000,
		match_string_const = 0x0100,
		match_mrule = 0x0200,
		match_rule_and = 0x0300,
		match_rule_or = 0x0400,
		match_rule_repeat = 0x0501,
		match_rule_repeat_or_not = 0x0500,
		match_has_or_not = 0x0600,
		match_rule_closeer = 0x0700,
		match_all = 0x8000,
	};
	
	KRule() : op(match_none), f_no_subtag(0) {}
	KRule(int opA, void* rule) : op(opA), f_no_subtag(0), lpVal(rule) {}
	
	class RecycleBin
	{
	private:
		std::AutoFreeAlloc m_alloc;
	
#if defined(_DEBUG)
	private:
		RecycleBin(const RecycleBin&);
		void operator=(const RecycleBin&);
	public:
		RecycleBin() {
			static nCount = 0;
			TRACEA("====> %d) KRule::RecycleBin Construct...\n", ++nCount);
		}
		~RecycleBin() {
			static nCount = 0;
			TRACEA("====> %d) KRule::RecycleBin Destruct...\n", ++nCount);
		}
#endif

	public:
		STDMETHODIMP_(KRule*) NewRule()
		{
			return _AutoFreeNew(&m_alloc, KRule);
		}
		STDMETHODIMP_(KRule*) NewRule(MatchRule* mrule)
		{
			return _AutoFreeNew2Arg(&m_alloc, KRule, match_mrule, mrule);
		}
		STDMETHODIMP_(KRule*) NewRule(String* string_const)
		{
			return _AutoFreeNew2Arg(&m_alloc, KRule, match_string_const, string_const);
		}
		STDMETHODIMP_(KRule*) NewRepeatRule(KRule* rule)
		{
			return _AutoFreeNew2Arg(&m_alloc, KRule, match_rule_repeat, rule);
		}
		STDMETHODIMP_(KRule*) NewOrRule(RuleList* rules)
		{
			return _AutoFreeNew2Arg(&m_alloc, KRule, match_rule_or, rules);
		}
		STDMETHODIMP_(KRule*) NewAndRule(RuleList* rules)
		{
			return _AutoFreeNew2Arg(&m_alloc, KRule, match_rule_and, rules);
		}
		STDMETHODIMP_(KRule*) NewRuleMatchAll()
		{
			return _AutoFreeNew2Arg(&m_alloc, KRule, match_all, NULL);
		}
		STDMETHODIMP_(MatchRule*) NewMRule()
		{
			return _AutoFreeNew(&m_alloc, MatchRule);
		}
		STDMETHODIMP_(RuleList*) NewRuleList()
		{
			return _AutoFreeNew(&m_alloc, RuleList);
		}
		STDMETHODIMP_(String*) NewString(const char_type* val)
		{
			return _AutoFreeNew1Arg(&m_alloc, String, val);
		}
	};
};

#pragma pack()

// -------------------------------------------------------------------------

template
	<
	class _Archive,
	class _String,
	class _Rule = KRule<_String>,
	class _Variant = KVariant<_String>
	>
class KScriptParser
	: public KBuiltinRules< _Archive, _Variant, typename _Variant::RecycleBin>,
	  public KScriptLog
{
public:
	typedef typename _Archive::char_type char_type;
	typedef typename _Archive::pos_type pos_type;
	typedef char_type Char;

	typedef _Archive Archive;
	typedef _String String;

	typedef _Variant Variant;
	typedef typename _Variant::Node Node;
	typedef typename _Variant::NodeList NodeList;
	typedef typename _Variant::VariantType VariantType;

	typedef _Rule Rule;
	typedef typename _Rule::MatchRule MatchRule;
	typedef typename _Rule::RuleList RuleList;
	typedef typename _Rule::RuleMap RuleMap;

	typedef typename _Variant::RecycleBin RecycleBin;
	
	enum RuleType
	{
		match_none = Rule::match_none,
		match_string_const = Rule::match_string_const,
		match_mrule = Rule::match_mrule,
		match_rule_and = Rule::match_rule_and,
		match_rule_or = Rule::match_rule_or,
		match_rule_repeat = Rule::match_rule_repeat,
		match_rule_repeat_or_not = Rule::match_rule_repeat_or_not,
		match_rule_closeer = Rule::match_rule_closeer,
		match_all = Rule::match_all,
		match_has_or_not = Rule::match_has_or_not,
	};
	
	typedef HRESULT __stdcall FnBuiltinMatch(Archive& src, ErrorReport& report);
	typedef HRESULT __stdcall FnBuiltinAssign(
		Archive& src, Variant& var, pos_type here, RecycleBin& recycle);

	struct _BuiltinRule
	{
		FnBuiltinMatch* fnMatch;
		FnBuiltinAssign* fnAssign;
		_BuiltinRule() {}
		_BuiltinRule(FnBuiltinMatch* fnMatchA, FnBuiltinAssign* fnAssignA)
			: fnMatch(fnMatchA), fnAssign(fnAssignA) {}
	};
	typedef _BuiltinRule BuiltinRule;

	typedef std::map<String, BuiltinRule> BuiltinRuleMap;

	enum VariantAllocType
	{
		vat_none	= 0,
		vat_locale	= 1,
		vat_global	= 2,
	};

protected:
	Archive& src;
	RuleMap& rules;
	BuiltinRuleMap& builtin_rules;
	RecycleBin& recycle;
	ErrorReport report;

protected:
	STDMETHODIMP_(void) _AddVariant(NodeList& vars, const String& name, const Variant& value)
	{
		Node node;
		node.name = recycle.NewAtom(name);
		node.value = value;
		vars.push_back(node);
	}

	TEXT_SCRIPT_API _MatchAll(MatchRule& mrule, NodeList& vars, Rule& ruleNext)
	{
		// _MatchAll() effect taken on 'vars': depend on _MatchAllNoResult()

		BOOL fNoResult = mrule.var_name.empty();
		if (fNoResult)
		{
			pos_type pos_goto;
			HRESULT hr = _MatchAllNoResult(vars, ruleNext, &pos_goto, NULL);
			if (SUCCEEDED(hr))
			{
				src.seek(pos_goto);
			}
			return hr;
		}
		else
		{
			pos_type pos_goto;
			pos_type pos_next_rule_start;
			pos_type start = src.tell();
			HRESULT hr = _MatchAllNoResult(vars, ruleNext, &pos_goto, &pos_next_rule_start);
			if (SUCCEEDED(hr))
			{
				Variant varg;
				src.seek(start);
				assign_str_pretty(src, varg, pos_next_rule_start, recycle);
				src.seek(pos_goto);
				_AddVariant(vars, mrule.var_name, varg);
			}
			return hr;
		}
	}

	TEXT_SCRIPT_API _MatchAllNoResult(
		NodeList& vars, Rule& ruleNext, pos_type* pos_goto, pos_type* pos_next_rule_start_ret)
	{
		// _MatchAllNoResult() effect taken on 'vars': depend on [?]

		if (ruleNext.op != match_rule_or)
			return _MatchAllNoResultBase(ruleNext, -1, pos_goto, pos_next_rule_start_ret);

		// $(*) ("strc1" $(rule1) | "strc2" $(rule2) | *["strc3"|"strc4"] $(rule) | ...)

		RuleList& rule_list = *ruleNext.or_rules;
		Rule* rule_best_match = NULL;
		int limit = -1;

		HRESULT hr = E_STRING_UNMATCH;
		pos_type pos_next_rule_start;
		pos_type start = src.tell();

		typename RuleList::iterator it;
		for (it = rule_list.begin(); it != rule_list.end(); ++it)
		{
			src.seek(start);

			Rule& rule = *it;
			switch (rule.op)
			{
			case match_rule_and:	{
				RuleList& rule_and_list = *rule.and_rules;
				if ( S_OK == _MatchAllNoResultBase(
					*rule_and_list.begin(), limit, pos_goto, &pos_next_rule_start) )
				{
					hr = S_OK;
					rule_best_match = &rule;
					limit = src.tell() - start;
				}
				break;				}

			default:
				if ( S_OK == _MatchAllNoResultBase(
					rule, limit, pos_goto, &pos_next_rule_start) )
				{
					hr = S_OK;
					rule_best_match = NULL;
					limit = src.tell() - start;
				}
			}
		}

		if (pos_next_rule_start_ret)
			*pos_next_rule_start_ret = pos_next_rule_start;

		if (rule_best_match)
		{
			ASSERT(rule_best_match->op == match_rule_and);
			src.seek(pos_next_rule_start);
			hr = _MatchRuleAnd(*rule_best_match->and_rules, vars, FALSE);
		}
		if (SUCCEEDED(hr))
			*pos_goto = src.tell();
		return hr;
	}

	//
	//@@bugfix:
	//	将原先_MatchAllNoResultBase改名为__MatchAllNoResultBase。
	//	因为原先$(*)就算匹配0个字节也算成功，现在我们认为是错误。
	//	这样可以避免因为$(rule)匹配0字节而导致死循环问题。
	//
	TEXT_SCRIPT_API _MatchAllNoResultBase(
		Rule& ruleNext, int limit, pos_type* pos_goto, pos_type* pos_next_rule_start)
	{
		pos_type pos_old = src.tell();
		HRESULT hr = __MatchAllNoResultBase(ruleNext, limit, pos_goto, pos_next_rule_start);
		if (SUCCEEDED(hr))
		{
			if (*pos_goto <= pos_old)
				return E_FAIL;// 0字节匹配
		}
		return hr;
	}

	TEXT_SCRIPT_API __MatchAllNoResultBase(
		Rule& ruleNext, int limit, pos_type* pos_goto, pos_type* pos_next_rule_start)
	{
		// _MatchAllNoResultBase() effect taken on 'vars': no change!!!

		switch (ruleNext.op)
		{
		case match_string_const:			{
			// $(*) "strc"
			String& strc = *ruleNext.string_const;
			if (S_OK == kfc_algo::string_FindLimit(src, strc, limit))
			{
				*pos_goto = src.tell();
				if (pos_next_rule_start)
					*pos_next_rule_start = *pos_goto - strc.size();
				return S_OK;
			}
			return E_STRING_UNMATCH;		}

		case match_rule_closeer:
			switch (ruleNext.rule->op)
			{
			case match_string_const:		{
				// $(*) *[ "strc" ]
				String& strc = *((ruleNext.rule)->string_const);
				if (S_OK == kfc_algo::string_FindLimit(src, strc, limit))
				{
					*pos_goto = src.tell() - strc.size();
					if (pos_next_rule_start)
						*pos_next_rule_start = *pos_goto;
					return S_OK;
				}
				return E_STRING_UNMATCH;	}

			case match_rule_or:				{
				// $(*) *[ "strc1" | "strc2" | ... | "strcn" ]
				RuleList& rule_list = *ruleNext.rule->or_rules;
				size_type next_rule_size;
				if (S_OK == _MatchRuleCloseerOr(rule_list, limit, &next_rule_size))
				{
					*pos_goto = src.tell() - next_rule_size;
					if (pos_next_rule_start)
						*pos_next_rule_start = *pos_goto;
					return S_OK;
				}
				return E_STRING_UNMATCH;	}

			default:
				ASSERT(0);
				return E_NOTIMPL;
			}
			break;

		default:
			ASSERT(0);
			return E_FAIL;
		}
	}

	TEXT_SCRIPT_API _MatchRuleCloseerOr(
		RuleList& rule_list, int limit, size_type* next_rule_size)
	{
		// *[ "strc1" | "strc2" | ... | "strcn" ]
		// _MatchRuleCloseerOr() effect taken on 'vars': no change!!!
		
		HRESULT hr = E_STRING_UNMATCH;
		pos_type start = src.tell();

		typename RuleList::iterator it;
		for (it = rule_list.begin(); it != rule_list.end(); ++it)
		{
			Rule& rule = *it;
			ASSERT(rule.op == match_string_const);

			if (rule.op == match_string_const)
			{
				src.seek(start);
				String& strc = *rule.string_const;
				if (S_OK == kfc_algo::string_FindLimit(src, strc, limit))
				{
					hr = S_OK;
					*next_rule_size = strc.size();
					limit = src.tell() - start;
				}
			}
		}
		return hr;
	}
	
	TEXT_SCRIPT_API _MatchMRule(MatchRule& mrule, NodeList& vars, BOOL fNotAllowToFail)
	{
		// _MatchMRule() effect taken on 'vars': depend on _MatchMRuleNoResult()
		
		BOOL fNoResult = mrule.var_name.empty();
		FnBuiltinAssign* fnAssign;

		if (fNoResult)
			return _MatchMRuleNoResult(mrule, &vars, &fnAssign, fNotAllowToFail);
		else
		{
			pos_type start = src.tell();
			HRESULT hr = _MatchMRuleNoResult(mrule, &vars, &fnAssign, fNotAllowToFail);
			if (SUCCEEDED(hr))
			{
				pos_type here = src.tell();
				Variant varg;
				src.seek(start);
				fnAssign(src, varg, here, recycle);
				src.seek(here);
				_AddVariant(vars, mrule.var_name, varg);
			}
			return hr;
		}
	}

	TEXT_SCRIPT_API _MatchMRuleNoResult(
		MatchRule& mrule, NodeList* vars, FnBuiltinAssign** fn, BOOL fNotAllowToFail)
	{
		// _MatchMRuleNoResult() effect taken on 'vars': depend on _MatchRule()

		HRESULT hr;
		const char_type* rule_name = mrule.rule_name.c_str();

		VariantAllocType vat = vat_locale;
		if (*rule_name == '!') // todo: 暂时不允许'!'与'_'相连。
		{
			++rule_name;
			fNotAllowToFail |= TRUE;
		}
		else if (*rule_name == '_') // this rule doesn't need to create a subtag
		{
			++rule_name;
			vat = vat_none;
		}

		typename RuleMap::iterator it = rules.find(rule_name);
		if (it == rules.end()) // maybe is a builtin rule
		{
			if (vat == vat_none)
			{
				typename BuiltinRuleMap::iterator it = builtin_rules.find(--rule_name);
				if (it != builtin_rules.end())
				{
					*fn = (*it).second.fnAssign;
					report.SetContext(src, mrule.var_name);
					return (*it).second.fnMatch(src, report);
				}
			}
			ERRMSG("---> Invalid input script: rule '%s' not found.\n", rule_name);
			return E_UNKNOWN_RULE;
		}

		NodeList* alter_vars = NULL;
		if ( (*it).second.f_no_subtag )
		{
			*fn = assign_str_pretty;
			alter_vars = vars = recycle.NewVariantList();
		}
		else
		{
			*fn = assign_str;
		}

		if (vat != vat_none) // create a subtag
		{
			NodeList& varList = *recycle.NewVariantList();
			hr = _MatchRule((*it).second, varList, fNotAllowToFail);
			if (SUCCEEDED(hr))
				_AddVariant(*vars, rule_name, Variant(&varList));
			else if (fNotAllowToFail)
				_NotAllowToFail(rule_name, vars, varList);
		}
		else
		{
			hr = _MatchRule((*it).second, *vars, fNotAllowToFail);
		}

		if (alter_vars)
			recycle.Delete(alter_vars);

		return hr;
	}

	TEXT_SCRIPT_API _NotAllowToFail(
		const char_type* rule_name, NodeList* vars, NodeList& varList)
	{
		log.Print("  ===> !!! Error when processing <%s>\n", rule_name);
		PrintVariantListT(log, varList, 1);
		log.Print("\n");
	//	_AddVariant(*vars, rule_name, Variant(&varList));
		return S_OK;
	}

	TEXT_SCRIPT_API _MatchRuleAnd(RuleList& rule_list, NodeList& vars, BOOL fNotAllowToFail)
	{
		// _MatchRuleAnd() effect taken on 'vars': do it! [depend on _MatchRule()]
		
		HRESULT hr = S_OK;
		typename NodeList::size_type count = vars.size();
		typename RuleList::iterator it;
		for (it = rule_list.begin(); it != rule_list.end(); ++it)
		{
			switch ((*it).op)
			{
			case match_all:			{
				MatchRule& mrule = *(*it).mrule;
				++it;
				if (it == rule_list.end())
					return E_UNEXPECTED;
				hr = _MatchAll(mrule, vars, *it);
				break;				}
			default:
				hr = _MatchRule(*it, vars);
			}
			if (FAILED(hr) && !fNotAllowToFail)
			{
				vars.resize(count);
				break;
			}
		}
		_CHECK_HR(hr);
		return hr;
	}
	
	TEXT_SCRIPT_API _MatchRuleOr(RuleList& rule_list, NodeList& vars)
	{
		// _MatchRuleOr() effect taken on 'vars': do it! [depend on _MatchRule()]

		HRESULT hr = S_OK;
		_DEBUG_ONLY(
			typename NodeList::size_type count = vars.size()
			);

		pos_type here = src.tell();
		typename RuleList::iterator it;
		for (it = rule_list.begin(); it != rule_list.end(); ++it)
		{
			hr = _MatchRule(*it, vars);
			if (SUCCEEDED(hr))
				break;
			ASSERT(vars.size() == count); //_Resize(vars, size);
			src.seek(here);
		}
		_CHECK_HR(hr);
		return hr;
	}
	
	TEXT_SCRIPT_API _MatchRuleRepeat(Rule& rule, NodeList& vars, int minCount)
	{
		// _MatchRuleRepeat() effect taken on 'vars': do it! [depend on _MatchRule()]
		HRESULT hr = S_OK;
		int matchCount = 0;
		for (;;)
		{
			pos_type here = src.tell();
			_DEBUG_ONLY(
				typename NodeList::size_type count = vars.size()
				);
			hr = _MatchRule(rule, vars);
			if (FAILED(hr))
			{
				ASSERT(vars.size() == count); //_Resize(vars, size);
				src.seek(here);
				break;
			}
			else 
			{
				++matchCount;
				if (hr == S_MATCH_EOF)
					break;
			}
		}
		return matchCount >= minCount ? S_OK : E_FAIL;
	}
	
	TEXT_SCRIPT_API _MatchRuleCloseer(Rule& rule, NodeList& vars, int minCount)
	{
		return E_FAIL;
	}

	TEXT_SCRIPT_API _MatchRule(Rule& rule, NodeList& vars, BOOL fNotAllowToFail = FALSE)
	{
		// _MatchRule() effect taken on 'vars': 
		//		_MatchRuleAnd(), _MatchMRule(), _MatchRuleOr(), _MatchRuleRepeat()
	
		HRESULT hr;
		switch (rule.op)
		{
		case match_string_const:	{
			const char_type* strc = ToCStr(*rule.string_const);
			if (*strc == '\0')
				return S_OK;
			SkipWhiteChars(src);
			report.SetContext(src, *rule.string_const);
			hr = MatchString(src, strc);
			if (FAILED(hr))
				report.Except(src, NULL);
			HR_TRACE("---> _cstring: \"%s\"\n", strc);
			break;					}
		case match_rule_and:
			hr = _MatchRuleAnd(*rule.and_rules, vars, fNotAllowToFail);
			break;
		case match_mrule:
			hr = _MatchMRule(*rule.mrule, vars, fNotAllowToFail);
			break;
		case match_rule_or:
			hr = _MatchRuleOr(*rule.or_rules, vars);
			break;
		case match_rule_repeat:
		case match_rule_repeat_or_not:
			hr = _MatchRuleRepeat(*rule.rule, vars, rule.op & 0xff);
			break;
		case match_has_or_not:		{
			pos_type here = src.tell();
			hr = _MatchRule(*rule.rule, vars);
			if (FAILED(hr))
			{
				src.seek(here);
				hr = S_OK;
			}
			break;					}
		//case match_rule_closeer:
		//	hr = E_FAIL;
		//	break;
		default:
			TEXT_SCRIPT_ERROR("Unknown Script Rule Operator!!!");
			hr = E_UNKNOWN_SCRIPT_OP;
		}
		_CHECK_HR(hr);
		return hr;
	}

public:
	KScriptParser(
		Archive& srcA,
		RuleMap& rulesA,
		BuiltinRuleMap& builtin_rulesA,
		RecycleBin& recycleA
		)
		: src(srcA), rules(rulesA), builtin_rules(builtin_rulesA), recycle(recycleA)
	{
	}
	
	TEXT_SCRIPT_API Parse(MatchRule& mrule, NodeList& vars)
	{
		HRESULT hr = _MatchMRule(mrule, vars, FALSE);
		if (SUCCEEDED(hr))
			return SkipWhiteCharsGetChar(src) == Archive::endch ? S_OK : E_UNEXPECTED;
		return hr;
	}

	TEXT_SCRIPT_API_(void) ReportError(Archive& src)
	{
		report.ReportError(src);
	}
};

_TEXT_SCRIPT_END

// -------------------------------------------------------------------------
// $Log: script_parser.h,v $
// Revision 1.6  2006/06/10 05:36:50  xushiwei
// 1、支持多个Log终端同时输出: stderr, file("_ErrorLog_.txt")
// 2、引入NotAllowToFail机制。作为临时的一种提高出错处理的手段。
//
// Revision 1.5  2006/05/30 04:14:40  xushiwei
// 使用AutoFreeAlloc进行内存管理。
//
// Revision 1.4  2006/05/30 00:22:24  xushiwei
// bugfix:
// 	将原先_MatchAllNoResultBase改名为__MatchAllNoResultBase。
// 	因为原先$(*)就算匹配0个字节也算成功，现在我们认为是错误。
// 	这样可以避免因为$(rule)匹配0字节而导致死循环问题。
//

#endif /* __KFC_TEXT_SCRIPT_PARSER_H__ */
