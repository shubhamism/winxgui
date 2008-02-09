/* -------------------------------------------------------------------------
//	文件名		：	example/script_parser.h
//	创建者		：	许式伟
//	创建时间	：	4/22/2003 1:55:33 AM
//	功能描述	：	
//
// -----------------------------------------------------------------------*/
#ifndef __EXAMPLE_SCRIPT_PARSER_H__
#define __EXAMPLE_SCRIPT_PARSER_H__

#ifndef __IO_STDIO_H__
#include "io/stdio.h"
#endif

#ifndef __KFC_TEXT_SCRIPT_IN_H__
#include "../script_in.h"
#endif

#ifndef __KFC_TEXT_SCRIPT_OUT_H__
#include "../script_out.h"
#endif

#ifndef __KFC_TEXT_SCRIPT_DEBUG_H__
#include "../script_debug.h"
#endif

#ifndef _STRING_
#include "string"
#endif

_TEXT_SCRIPT_BEGIN

class String : public std::string
{
public:
	typedef std::string _Base;
	typedef _Base::value_type char_type;

	String() {}
	String(const char_type* str) : _Base(str) {}
};

inline 
void _test_script_parser()
{
	typedef KStdioReadArchive Archive;
	typedef KScriptInParser<Archive, String> Parser;

	typedef Parser::RuleMap RuleMap;
	typedef Parser::BuiltinRuleMap BuiltinRuleMap;
	typedef Parser::VariantRecycleBin VariantRecycleBin;
	typedef Parser::RuleRecycleBin RuleRecycleBin;
	typedef Parser::MatchRule MatchRule;
	typedef Parser::NodeList Variants;
	
	Archive ar("binview.in");
	
	RuleMap rules;
	BuiltinRuleMap builtin_rules;
	VariantRecycleBin recycleA;
	RuleRecycleBin recycleB;
	MatchRule mrule;

	Parser::GetBasicParserRules(rules, recycleB);
	Parser::GetBuiltinRules(builtin_rules);
	PrintRules(rules);
	
	Parser parser(ar, rules, builtin_rules, recycleA);
	Variants vars;
	mrule.rule_name = Parser::_doc;
	HRESULT hr = parser.Parse(mrule, vars);

	PrintLine();	
	//PrintVariantList(vars);
	if (hr == S_OK)
		printf("\nSuccess!!!\n");
	else
	{
		parser.ReportError(ar);
	}

	RuleMap rulesNew;
	Parser::GetScriptInRules(vars, rulesNew, recycleB);
	PrintRules(rulesNew);
}

template <class _Variants, class _VariantRecycleBin>
void _test_load_c_source(_Variants& vars, _VariantRecycleBin& recycle)
{
	typedef KStdioReadArchive Archive;
	typedef KScriptInParser<Archive, String> Parser;
	typedef Parser::NodeList Variants;
	
	Archive script_in_ar("interface.in");
	Archive ar("datalayer.h");
	if (!ar || !script_in_ar)
	{
		TRACE("Unable to open file!\n");
		return;
	}
	Parser::Load(vars, ar, script_in_ar, recycle);
	PrintLine();
	PrintVariantList(vars);
}

template <class _Variants>
void _test_write_c_source(_Variants& vars)
{
	typedef KWriteArchiveImpl<FILE*, StdioAdapter> ArchiveOut;
	KStdioReadArchive script_out_ar("interface.out");
	ArchiveOut out(stdout);
	PrintLine();
	TemplateReplace(script_out_ar, out, vars);
}

inline 
void _test_load_source()
{
	typedef KStdioReadArchive Archive;
	typedef KScriptInParser<Archive, String> Parser;
	
	typedef Parser::VariantRecycleBin VariantRecycleBin;
	typedef Parser::NodeList Variants;
	
	Variants vars;
	VariantRecycleBin recyle;
	Archive script_in_ar("template.out");
	Archive ar("script.out");
	if (!ar || !script_in_ar)
	{
		TRACE("Unable to open file!\n");
		return;
	}
	Parser::Load(vars, ar, script_in_ar, recyle);
	PrintLine();
	PrintVariantList(vars);
}

_TEXT_SCRIPT_END

inline
void test_script_parser()
{
	_TEXT_SCRIPT _test_script_parser();
}

inline
void test_load_source()
{
	typedef KStdioReadArchive Archive;
	typedef KScriptInParser<Archive, String> Parser;
	typedef Parser::NodeList Variants;
	typedef Parser::VariantRecycleBin VariantRecycleBin;
	
	Variants vars;
	VariantRecycleBin recycle;
	_TEXT_SCRIPT _test_load_c_source(vars, recycle);
	_TEXT_SCRIPT _test_write_c_source(vars);
}

#endif /* __EXAMPLE_SCRIPT_PARSER_H__ */
