/* -------------------------------------------------------------------------
//	文件名		：	text/script_in.h
//	创建者		：	许式伟
//	创建时间	：	4/19/2003 11:50:19 PM
//	功能描述	：	
//
//	$Id: script_in.h,v 1.3 2006/06/10 05:37:55 xushiwei Exp $
// -----------------------------------------------------------------------*/
#ifndef __KFC_TEXT_SCRIPT_IN_H__
#define __KFC_TEXT_SCRIPT_IN_H__

#ifndef __KFC_TEXT_SCRIPT_PARSER_H__
#include "script_parser.h"
#endif

// -------------------------------------------------------------------------

#define E_RULE_REDECLARE			E_FAIL

#ifndef STATIC_SCRIPT_API
#define STATIC_SCRIPT_API			static HRESULT __stdcall
#define STATIC_SCRIPT_API_(type)	static type __stdcall
#endif

_TEXT_SCRIPT_BEGIN

// -------------------------------------------------------------------------

template
	<
	class _Archive,
	class _String,
	class _Rule = KRule<_String>,
	class _Variant = KVariant<_String>
	>
class KScriptInParser : 
	public KScriptParser<_Archive, _String, _Rule, _Variant>
{
public:
	typedef KScriptParser<_Archive, _String, _Rule, _Variant> _Base;
	typedef KScriptInParser Parser;

	typedef _Archive Archive;

	typedef typename _Base::char_type char_type;
	typedef typename _Base::pos_type pos_type;
	typedef typename _Base::Node Node;
	typedef typename _Base::NodeList NodeList;
	typedef typename _Base::RecycleBin VariantRecycleBin;
	typedef typename _Base::Rule Rule;
	typedef typename _Base::RuleList RuleList;
	typedef typename _Base::MatchRule MatchRule;
	typedef typename _Base::RuleMap RuleMap;
	typedef typename _Base::BuiltinRuleMap BuiltinRuleMap;
	typedef typename _Rule::RecycleBin RuleRecycleBin;
	
public:
	KScriptInParser(
		Archive& srcA,
		RuleMap& rulesA,
		BuiltinRuleMap& builtin_rulesA,
		VariantRecycleBin& recycleA
		)
		: _Base(srcA, rulesA, builtin_rulesA, recycleA)
	{
	}

public:
	static const char_type cint[];
	static const char_type csymbol[];
	static const char_type csymbol_or_all[];
	static const char_type matchrule[];
	static const char_type cstring[];
	static const char_type blank[];
	static const char_type quomark[];
	static const char_type eol[];
	static const char_type ceol[];
	static const char_type eof[];
	static const char_type include[];
	static const char_type incPath[];
	
	static const char_type szor[];
	static const char_type slashslash[];
	static const char_type eq[];
	static const char_type dollar[];
	static const char_type brLeft[];
	static const char_type brBigLeftOrNot[];
	static const char_type brRight[];
	static const char_type brMidLeft[];
	static const char_type brMidRight[];
	static const char_type brBigLeft[];
	static const char_type brBigRight[];
	static const char_type brCloseer[];
	static const char_type comma[];
	static const char_type doc[];
	static const char_type _doc[];
	static const char_type rule[];
	static const char_type ruleAnd[];
	static const char_type ruleOr[];
	static const char_type ruleRepeat[];
	static const char_type ruleRepeatOrNot[];
	static const char_type ruleHasOrNot[];
	static const char_type ruleCloseer[];
	static const char_type comment[];
	static const char_type aRule[];
	static const char_type aRuleName[];
	static const char_type ruleName[];
	static const char_type ruleFactor[];
	static const char_type _ruleFactor[];
	static const char_type matchRule[];
	static const char_type matchString[];
	static const char_type varName[];

public:
	STATIC_SCRIPT_API_(void) GetBuiltinRules(BuiltinRuleMap& default_rules)
	{
		default_rules[blank] = BuiltinRule(match_blank, assign_str);
		default_rules[quomark] = BuiltinRule(match_quomark, assign_str);
		default_rules[cint] = BuiltinRule(match_cint, assign_cint);
		default_rules[cstring] = BuiltinRule(match_cstring, assign_cstring);
		default_rules[csymbol] = BuiltinRule(match_csymbol, assign_str);
		default_rules[csymbol_or_all] = BuiltinRule(match_csymbol_or_all, assign_str);
		default_rules[matchrule] = BuiltinRule(match_matchrule, assign_str);
		default_rules[eol] = BuiltinRule(match_eol, assign_eol);
		default_rules[eof] = BuiltinRule(match_eof, assign_str);
		default_rules[ceol] = BuiltinRule(match_ceol, assign_str);
	}

public:
	STATIC_SCRIPT_API GetBasicParserRules(RuleMap& rules, RuleRecycleBin& recycle)
	{
		Rule* _ARule;
		RuleList* _RuleList;
		RuleList* _RuleAndList;
		MatchRule* _MatchRule;
		
		Rule _slashslash( match_string_const, recycle.NewString(slashslash) );
		Rule _include( match_string_const, recycle.NewString(include) );
		Rule _or( match_string_const, recycle.NewString(szor) );
		Rule _eq( match_string_const, recycle.NewString(eq) );
		Rule _comma( match_string_const, recycle.NewString(comma) );
		Rule _dollar( match_string_const, recycle.NewString(dollar) );
		Rule _brLeft( match_string_const, recycle.NewString(brLeft) );
		Rule _brRight( match_string_const, recycle.NewString(brRight) );
		Rule _brMidLeft( match_string_const, recycle.NewString(brMidLeft) );
		Rule _brMidRight( match_string_const, recycle.NewString(brMidRight) );
		Rule _brBigLeft( match_string_const, recycle.NewString(brBigLeft) );
		Rule _brBigLeftOrNot( match_string_const, recycle.NewString(brBigLeftOrNot) );
		Rule _brBigRight( match_string_const, recycle.NewString(brBigRight) );
		Rule _brCloseer( match_string_const, recycle.NewString(brCloseer) );

		_MatchRule = recycle.NewMRule();
		_MatchRule->rule_name = rule;
		Rule _rule( match_mrule, _MatchRule );
		
		_MatchRule = recycle.NewMRule();
		_MatchRule->rule_name = ruleAnd;
		Rule _ruleAnd( match_mrule, _MatchRule );
		
		_MatchRule = recycle.NewMRule();
		_MatchRule->rule_name = ruleOr;
		Rule _ruleOr( match_mrule, _MatchRule );

		// doc = { $(ARule) | "//" $(_eol) | "#include" $(_cstring=IncPath) };
		{
			_RuleList = recycle.NewRuleList();
			// $(ARule)
			{
				_MatchRule = recycle.NewMRule();
				_MatchRule->rule_name = aRule;
				_RuleList->push_back( Rule(match_mrule, _MatchRule) );
			}
			// "//" $(_eol)
			{
				_MatchRule = recycle.NewMRule();
				_MatchRule->rule_name = eol;
				_RuleAndList = recycle.NewRuleList();
				_RuleAndList->push_back( _slashslash );
				_RuleAndList->push_back( Rule(match_mrule, _MatchRule) );
				_RuleList->push_back( Rule(match_rule_and, _RuleAndList) );
			}
			// "#include" $(_cstring=IncPath)
			{
				_MatchRule = recycle.NewMRule();
				_MatchRule->rule_name = cstring;
				_MatchRule->var_name = incPath;
				_RuleAndList = recycle.NewRuleList();
				_RuleAndList->push_back( _include );
				_RuleAndList->push_back( Rule(match_mrule, _MatchRule) );
				_RuleList->push_back( Rule(match_rule_and, _RuleAndList) );
			}
			_ARule = recycle.NewOrRule(_RuleList);
			rules[doc] = Rule(match_rule_repeat, _ARule);
		}
		// ARule = $(_csymbol = ARuleName) "=" $(Rule) ";";
		{
			_MatchRule = recycle.NewMRule();
			_MatchRule->rule_name = csymbol;
			_MatchRule->var_name = aRuleName;
			_RuleAndList = recycle.NewRuleList();
			_RuleAndList->push_back( Rule(match_mrule, _MatchRule) );
			_RuleAndList->push_back( _eq );
			_RuleAndList->push_back( _rule );
			_RuleAndList->push_back( _comma );
			rules[aRule] = Rule(match_rule_and, _RuleAndList);
		}

		// RuleFactor = 
		//		$(_cstring = MatchString) |
		//		"$" "(" $(MatchRule) ")" |
		//		"{" $(RuleRepeat) "}" |
		//		"*{" $(RuleRepeatOrNot) "}" |
		//		"(" $(Rule) ")" |
		//		"[" $(RuleHasOrNot) "]"
		//		"*[" $(RuleCloseer) "]"
		//		;
		{
			_RuleList = recycle.NewRuleList();
			// $(_cstring = MatchString)
			{
				_MatchRule = recycle.NewMRule();
				_MatchRule->rule_name = cstring;
				_MatchRule->var_name = matchString;
				_RuleList->push_back( Rule(match_mrule, _MatchRule) );
			}
			// "$" "(" $(MatchRule) ")"
			{
				_MatchRule = recycle.NewMRule();
				_MatchRule->rule_name = matchRule;
				_RuleAndList = recycle.NewRuleList();
				_RuleAndList->push_back( _dollar );
				_RuleAndList->push_back( _brLeft );
				_RuleAndList->push_back( Rule(match_mrule, _MatchRule) );
				_RuleAndList->push_back( _brRight );
				_RuleList->push_back( Rule(match_rule_and, _RuleAndList) );
			}
			// "{" $(RuleRepeat) "}"
			{
				_MatchRule = recycle.NewMRule();
				_MatchRule->rule_name = ruleRepeat;
				_RuleAndList = recycle.NewRuleList();
				_RuleAndList->push_back( _brBigLeft );
				_RuleAndList->push_back( Rule(match_mrule, _MatchRule) );
				_RuleAndList->push_back( _brBigRight );
				_RuleList->push_back( Rule(match_rule_and, _RuleAndList) );
			}
			// "*{" $(RuleRepeatOrNot) "}"
			{
				_MatchRule = recycle.NewMRule();
				_MatchRule->rule_name = ruleRepeatOrNot;
				_RuleAndList = recycle.NewRuleList();
				_RuleAndList->push_back( _brBigLeftOrNot );
				_RuleAndList->push_back( Rule(match_mrule, _MatchRule) );
				_RuleAndList->push_back( _brBigRight );
				_RuleList->push_back( Rule(match_rule_and, _RuleAndList) );
			}
			// "(" $(Rule) ")"
			{
				_RuleAndList = recycle.NewRuleList();
				_RuleAndList->push_back( _brLeft );
				_RuleAndList->push_back( _rule );
				_RuleAndList->push_back( _brRight );
				_RuleList->push_back( Rule(match_rule_and, _RuleAndList) );
			}
			// "[" $(RuleHasOrNot) "]"
			{
				_MatchRule = recycle.NewMRule();
				_MatchRule->rule_name = ruleHasOrNot;
				_RuleAndList = recycle.NewRuleList();
				_RuleAndList->push_back( _brMidLeft );
				_RuleAndList->push_back( Rule(match_mrule, _MatchRule) );
				_RuleAndList->push_back( _brMidRight );
				_RuleList->push_back( Rule(match_rule_and, _RuleAndList) );
			}
			// "*[" $(RuleCloseer) "]"
			{
				_MatchRule = recycle.NewMRule();
				_MatchRule->rule_name = ruleCloseer;
				_RuleAndList = recycle.NewRuleList();
				_RuleAndList->push_back( _brCloseer );
				_RuleAndList->push_back( Rule(match_mrule, _MatchRule) );
				_RuleAndList->push_back( _brMidRight );
				_RuleList->push_back( Rule(match_rule_and, _RuleAndList) );
			}
			rules[ruleFactor] = Rule(match_rule_or, _RuleList);
		}
		// MatchRule =
		//		$(_matchrule = RuleName) [ "=" $(_csymbol = VarName) ];
		{
			_RuleAndList = recycle.NewRuleList();
			// $(_matchrule = RuleName)
			{
				_MatchRule = recycle.NewMRule();
				_MatchRule->rule_name = matchrule;
				_MatchRule->var_name = ruleName;
				_RuleAndList->push_back( Rule(match_mrule, _MatchRule) );
			}
			// [ "=" $(_csymbol = VarName) ]
			{
				_RuleList = recycle.NewRuleList();
				_MatchRule = recycle.NewMRule();
				_MatchRule->rule_name = csymbol;
				_MatchRule->var_name = varName;
				_RuleList->push_back( _eq );
				_RuleList->push_back( Rule(match_mrule, _MatchRule) );
				_ARule = recycle.NewAndRule(_RuleList);
				_RuleAndList->push_back( Rule(match_has_or_not, _ARule) );
			}
			rules[matchRule] = Rule(match_rule_and, _RuleAndList);
		}
		// RuleRepeat = $(Rule);
		// RuleRepeatOrNot = $(Rule);
		// RuleHasOrNot = $(Rule);
		{
			rules[ruleRepeat] = _rule;
			rules[ruleRepeatOrNot] = _rule;
			rules[ruleHasOrNot] = _rule;
			rules[ruleCloseer] = _rule;
		}
		// RuleAnd = { $(_RuleFactor) };
		{
			_MatchRule = recycle.NewMRule();
			_MatchRule->rule_name = _ruleFactor;
			_ARule = recycle.NewRule(_MatchRule);
			rules[ruleAnd] = Rule(match_rule_repeat, _ARule);
		}
		// RuleOr = { $(RuleAnd) "|" } $(RuleAnd);
		{
			_RuleList = recycle.NewRuleList();
			// RuleOr = { $(RuleAnd) "|" }
			{
				_RuleAndList = recycle.NewRuleList();
				_RuleAndList->push_back( _ruleAnd );
				_RuleAndList->push_back( _or );
				_ARule = recycle.NewAndRule(_RuleAndList);
				_RuleList->push_back( Rule(match_rule_repeat, _ARule) );
			}
			// $(RuleAnd)
			{
				_RuleList->push_back( _ruleAnd );
			}
			rules[ruleOr] = Rule(match_rule_and, _RuleList);
		}
		// Rule = $(RuleOr) | $(RuleAnd);
		{
			_RuleList = recycle.NewRuleList();
			_RuleList->push_back( _ruleOr );
			_RuleList->push_back( _ruleAnd );
			rules[rule] = Rule(match_rule_or, _RuleList);
		}
		return S_OK;
	}

public:
	struct InputScript
	{
	public:
		MatchRule mrule;
		RuleMap script_in_rules;
		BuiltinRuleMap builtin_rules;
		RuleRecycleBin recycleB;
		const char_type* base_path;
		
	public:
		InputScript(const char_type* base = NULL)
			: base_path(base)
		{
		}

		// load input script!
		STDMETHODIMP LoadScript(IN const char_type* incPath)
		{
			ASSERT(base_path);
			
			if (base_path)
			{
				char_type script_in_file[_MAX_PATH];
				MergePath(script_in_file, base_path, incPath);
				
				Archive script_in_ar(script_in_file);
				if (!script_in_ar)
				{
					ERRMSG("---> Open script file: %s failed.\n", script_in_file);
					return E_ACCESSDENIED;
				}
				return LoadScript(script_in_ar);
			}
			return E_UNEXPECTED;
		}

		// load input script!
		STDMETHODIMP LoadScript(IN Archive& script_in_ar)
		{
			HRESULT hr;
			
			GetBuiltinRules(builtin_rules);
			mrule.rule_name = _doc;
			
			RuleMap basic_rules;
			GetBasicParserRules(basic_rules, recycleB);
			//PrintRules(basic_rules);
			
			VariantRecycleBin recycleA;
			NodeList script_in_vars;
			Parser script_in_parser(script_in_ar, basic_rules, builtin_rules, recycleA);
			{
				hr = script_in_parser.Parse(mrule, script_in_vars);
				KS_CHECK(hr);
				
				hr = Parser::GetScriptInRules(this, script_in_vars, script_in_rules, recycleB);
				KS_CHECK(hr);
				//PrintVariantList(script_in_vars);
				//PrintRules(script_in_rules);
			}
KS_EXIT:	if (FAILED(hr))
			{
				ERRMSG("---> Invalid input script!\n");
				script_in_parser.ReportError(script_in_ar);
			}
			return hr;
		}
		
		// load source file!
		STDMETHODIMP LoadSource(
			IN NodeList& vars,
			IN Archive& ar,
			IN VariantRecycleBin& recycle)
		{
			Parser source_parser(ar, script_in_rules, builtin_rules, recycle);
			HRESULT hr = source_parser.Parse(mrule, vars);
			if (FAILED(hr))
			{
				ERRMSG("---> Invalid source file!\n");
				source_parser.ReportError(ar);
			}
			return hr;
		}
	};
	friend struct InputScript;
	
	STATIC_SCRIPT_API Load(
		NodeList& vars, Archive& ar, Archive& script_in_ar, VariantRecycleBin& recycle)
	{
		InputScript is;
		HRESULT hr = is.LoadScript(script_in_ar);
		if (SUCCEEDED(hr))
		{
			hr = is.LoadSource(vars, ar, recycle);
			//PrintVariantList(vars);
		}
		return hr;
	}

protected:
	static STDMETHODIMP_(BOOL) _IsA(const Node& node, const char_type* tag)
	{
		for (const char_type* t = node.name; *t == *tag; ++t, ++tag)
		{
			if (*t == '\0')
				return TRUE;
		}
		return FALSE;
	}
	STATIC_SCRIPT_API _GetRuleFactor(const Node& node, Rule& theRule, RuleRecycleBin& recycle)
	{
		// RuleFactor = 
		//		$(_cstring = MatchString) |
		//		"$" "(" $(MatchRule) ")" |
		//		"{" $(RuleRepeat) "}" |
		//		"*{" $(RuleRepeatOrNot) "}" |
		//		"(" $(Rule) ")" |
		//		"[" $(RuleHasOrNot) "]"
		//		;
		if (_IsA(node, matchString))
		{
			ASSERT(node.value.vt == Variant::vtAtom);
			theRule.op = match_string_const;
			theRule.string_const = recycle.NewString(node.value.atomVal);
			return S_OK;
		}
		else if (_IsA(node, matchRule))
		{
			// MatchRule =
			//		$(_csymbol_or_all = RuleName) [ "=" $(_csymbol = VarName) ];
			ASSERT(node.value.vt == Variant::vtElement);

			const NodeList* lst = node.value.lstVal;
			int size = lst->size();
			ASSERT(size == 1 || size == 2);

			typename Variant::Atom atomVal = (lst->front()).value.atomVal;
			theRule.mrule = recycle.NewMRule();
			if (*atomVal == '*')
				theRule.op = match_all;
			else
			{
				theRule.op = match_mrule;
				theRule.mrule->rule_name = atomVal;
			}
			if (size == 2)
				theRule.mrule->var_name = (lst->back()).value.atomVal;
			return S_OK;
		}
		else if (_IsA(node, rule))
		{
			ASSERT(node.value.vt == Variant::vtElement);
			return _GetRule(*node.value.lstVal, theRule, recycle);
		}
		else	
		{
			// RuleRepeat = $(Rule);
			// RuleRepeatOrNot = $(Rule);
			// RuleHasOrNot = $(Rule);
			// RuleCloseer = $(Rule);
			ASSERT(
				_IsA(node, ruleRepeat) || 
				_IsA(node, ruleHasOrNot) || 
				_IsA(node, ruleRepeatOrNot) ||
				_IsA(node, ruleCloseer)
				);
			ASSERT(node.value.vt == Variant::vtElement);

			theRule.op = _IsA(node, ruleRepeat) ? match_rule_repeat : 
						(_IsA(node, ruleRepeatOrNot) ? match_rule_repeat_or_not : 
						(_IsA(node, ruleHasOrNot) ? match_has_or_not : 
						match_rule_closeer));
			theRule.rule = recycle.NewRule();

			const NodeList* lst = node.value.lstVal;
			ASSERT(lst->size() == 1);
			
			Node node = lst->front();
			ASSERT(_IsA(node, rule) && node.value.vt == Variant::vtElement);

			return _GetRule(*node.value.lstVal, *theRule.rule, recycle);
		}
	}

	STATIC_SCRIPT_API _GetRuleAnd(const NodeList* lst, Rule& theRule, RuleRecycleBin& recycle)
	{
		// RuleAnd = { $(_RuleFactor) };

		if (lst->size() > 1)
		{
			RuleList* rules = recycle.NewRuleList();
			typename NodeList::const_iterator it;
			for (it = lst->begin(); it != lst->end(); ++it)
			{
				Rule ruleA;
				HRESULT hr = _GetRuleFactor(*it, ruleA, recycle);
				if (FAILED(hr))
					return hr;
				rules->push_back(ruleA);
			}
			theRule.op = match_rule_and;
			theRule.and_rules = rules;
			return S_OK;
		}
		else
		{
			return _GetRuleFactor(lst->front(), theRule, recycle);
		}
	}

	STATIC_SCRIPT_API _GetRule(const NodeList& vars, Rule& theRule, RuleRecycleBin& recycle)
	{
		// Rule =
		//		$(RuleOr) | $(RuleAnd);

		ASSERT(vars.size() == 1);
		
		Node node = *vars.begin();
		ASSERT(node.value.vt == Variant::vtElement);

		HRESULT hr;
		const NodeList* lst = node.value.lstVal;
		if ( _IsA(node, ruleAnd) )
		{
			return _GetRuleAnd(lst, theRule, recycle);
		}
		else
		{
			// RuleOr =
			//		{ $(RuleAnd) "|" } $(RuleAnd);
			ASSERT(_IsA(node, ruleOr));
			ASSERT(lst->size() > 1);

			RuleList* rules = recycle.NewRuleList();

			typename NodeList::const_iterator it;
			for (it = lst->begin(); it != lst->end(); ++it)
			{
				node = *it;
				ASSERT(_IsA(node, ruleAnd) && node.value.vt == Variant::vtElement);

				Rule ruleA;
				hr = _GetRuleAnd(node.value.lstVal, ruleA, recycle);
				if (FAILED(hr))
					return hr;
				rules->push_back(ruleA);
			}
			theRule.op = match_rule_or;
			theRule.and_rules = rules;
			return S_OK;
		}
	}

	STATIC_SCRIPT_API GetScriptInRules(
		InputScript* pIS, const NodeList& vars, RuleMap& rules, RuleRecycleBin& recycle)
	{
		HRESULT hr = S_OK;
		Node node;
		typename NodeList::const_iterator it;
		for (it = vars.begin(); it != vars.end(); ++it)
		{
			node = *it;
			if (_IsA(node, aRule))
			{
				ASSERT(node.value.vt == Variant::vtElement);

				// ARule = $(_csymbol = ARuleName) "=" $(Rule) ";";

				const NodeList* lst = node.value.lstVal;
				ASSERT(lst->size() == 2);
				
				node = lst->front();
				ASSERT(_IsA(node, aRuleName) && node.value.vt == Variant::vtAtom);

				Rule* theRule;
				const char_type* szRuleName = node.value.atomVal;
				if (*szRuleName == '_')
				{
					++szRuleName;
					theRule = &rules[szRuleName];
					theRule->f_no_subtag = 1;
				}
				else
				{
					theRule = &rules[szRuleName];
				}
				if (theRule->op != match_none)
				{
					ERRMSG("rule %s redeclare!\n", szRuleName);
					ASSERT(0);
					return E_RULE_REDECLARE;
				}

				node = lst->back();
				ASSERT(_IsA(node, rule) && node.value.vt == Variant::vtElement);
				hr = _GetRule(*node.value.lstVal, *theRule, recycle);
				if (FAILED(hr))
					break;
			}
			else
			{
				ASSERT(_IsA(node, incPath));
				ASSERT(node.value.vt == Variant::vtAtom);
				pIS->LoadScript(node.value.atomVal);
			}
		}
		return hr;
	}
};

// -------------------------------------------------------------------------

#define SCRIPT_CONST_STRING													\
template <class _Archive, class _String, class _Rule, class _Variant>		\
const typename KScriptInParser<_Archive, _String, _Rule, _Variant>::char_type \
	KScriptInParser<_Archive, _String, _Rule, _Variant>::

SCRIPT_CONST_STRING cint[] = { '_', 'c', 'i', 'n', 't', '\0' };
SCRIPT_CONST_STRING csymbol[] = { '_', 'c', 's', 'y', 'm', 'b', 'o', 'l', '\0' };
SCRIPT_CONST_STRING csymbol_or_all[] = { '_', 'c', 's', 'y', 'm', 'b', 'o', 'l', '_', 'o', 'r', '_', 'a', 'l', 'l', '\0' };
SCRIPT_CONST_STRING matchrule[] = { '_', 'm', 'a', 't', 'c', 'h', 'r', 'u', 'l', 'e', '\0' };
SCRIPT_CONST_STRING cstring[] = { '_', 'c', 's', 't', 'r', 'i', 'n', 'g', '\0' };
SCRIPT_CONST_STRING blank[]	  = { '_', 'b', 'l', 'a', 'n', 'k', '\0' };
SCRIPT_CONST_STRING quomark[] = { '_', 'q', 'u', 'o', 'm', 'a', 'r', 'k', '\0' };
SCRIPT_CONST_STRING eof[]	  = { '_', 'e', 'o', 'f', '\0' };
SCRIPT_CONST_STRING eol[]	  = { '_', 'e', 'o', 'l', '\0' };
SCRIPT_CONST_STRING ceol[]	  = { '_', 'c', 'e', 'o', 'l', '\0' };

SCRIPT_CONST_STRING slashslash[] = { '/', '/', '\0' };
SCRIPT_CONST_STRING szor[] = { '|', '\0' };
SCRIPT_CONST_STRING eq[] = { '=', '\0' };
SCRIPT_CONST_STRING comma[] = { ';', '\0' };
SCRIPT_CONST_STRING dollar[] = { '$', '\0' };
SCRIPT_CONST_STRING brLeft[] = { '(', '\0' };
SCRIPT_CONST_STRING brRight[] = { ')', '\0' };
SCRIPT_CONST_STRING brMidLeft[] = { '[', '\0' };
SCRIPT_CONST_STRING brCloseer[] = { '*', '[', '\0' };
SCRIPT_CONST_STRING brMidRight[] = { ']', '\0' };
SCRIPT_CONST_STRING brBigLeft[] = { '{', '\0' };
SCRIPT_CONST_STRING brBigLeftOrNot[] = { '*', '{', '\0' };
SCRIPT_CONST_STRING brBigRight[] = { '}', '\0' };
SCRIPT_CONST_STRING doc[] = { 'd', 'o', 'c', '\0' };
SCRIPT_CONST_STRING _doc[] = { '_', 'd', 'o', 'c', '\0' };
SCRIPT_CONST_STRING rule[] = { 'R', 'u', 'l', 'e', '\0' };
SCRIPT_CONST_STRING ruleAnd[] = { 'R', 'u', 'l', 'e', 'A', 'n', 'd', '\0' };
SCRIPT_CONST_STRING ruleOr[] = { 'R', 'u', 'l', 'e', 'O', 'r', '\0' };
SCRIPT_CONST_STRING ruleHasOrNot[] = { 'R', 'u', 'l', 'e', 'H', 'a', 's', 'O', 'r', 'N', 'o', 't', '\0' };
SCRIPT_CONST_STRING ruleRepeat[] = { 'R', 'u', 'l', 'e', 'R', 'e', 'p', 'e', 'a', 't', '\0' };
SCRIPT_CONST_STRING ruleRepeatOrNot[] = { 'R', 'u', 'l', 'e', 'R', 'e', 'p', 'e', 'a', 't', 'O', 'r', 'N', 'o', 't', '\0' };
SCRIPT_CONST_STRING ruleCloseer[] = { 'R', 'u', 'l', 'e', 'C', 'l', 'o', 's', 'e', 'e', 'r', '\0' };
SCRIPT_CONST_STRING comment[] = { 'C', 'o', 'm', 'm', 'e', 'n', 't', '\0' };
SCRIPT_CONST_STRING aRule[] = { 'A', 'R', 'u', 'l', 'e', '\0' };
SCRIPT_CONST_STRING aRuleName[] = { 'A', 'R', 'u', 'l', 'e', 'N', 'a', 'm', 'e', '\0' };
SCRIPT_CONST_STRING ruleName[] = { 'R', 'u', 'l', 'e', 'N', 'a', 'm', 'e', '\0' };
SCRIPT_CONST_STRING ruleFactor[] = { 'R', 'u', 'l', 'e', 'F', 'a', 'c', 't', 'o', 'r', '\0' };
SCRIPT_CONST_STRING _ruleFactor[] = { '_', 'R', 'u', 'l', 'e', 'F', 'a', 'c', 't', 'o', 'r', '\0' };
SCRIPT_CONST_STRING matchRule[] = { 'M', 'a', 't', 'c', 'h', 'R', 'u', 'l', 'e', '\0' };
SCRIPT_CONST_STRING matchString[] = { 'M', 'a', 't', 'c', 'h', 'S', 't', 'r', 'i', 'n', 'g', '\0' };
SCRIPT_CONST_STRING varName[] = { 'V', 'a', 'r', 'N', 'a', 'm', 'e', '\0' };
SCRIPT_CONST_STRING incPath[] = { 'I', 'n', 'c', 'P', 'a', 't', 'h', '\0' };
SCRIPT_CONST_STRING include[] = { '#', 'i', 'n', 'c', 'l', 'u', 'd', 'e', '\0' };

// -------------------------------------------------------------------------
// $Log: script_in.h,v $
// Revision 1.3  2006/06/10 05:37:55  xushiwei
// 引入NotAllowToFail机制。作为临时的一种提高出错处理的手段。
//

_TEXT_SCRIPT_END

#endif /* __KFC_TEXT_SCRIPT_IN_H__ */
