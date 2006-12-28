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
// Module: tpl/v1/script_out.h
// Creator: xushiwei
// Email: xushiweizh@gmail.com
// Date: 2002-12-21 23:54:17
// History: 
//		1) 2002-12-21 23:54:17	建立初步的输出脚本，支持:
//			a) 普通变量: $(Var)
//			b) 循环: ${Var=...$}
//			c) 条件选择指令: $<Var=...$;...$;...$>
//			d) 普通字符: $$
//		2) 4/29/2003 23:37:03	与text/script_in整合，并功能增加:
//			a) 循环体最后一个循环特处理控制： $[...$]
//			b) 条件指令增强: 由原 $<Var=...$;...$> 扩展到: $<Var?a,b,c=...$;...$>
//		3) 4/30/2003 13:19:03	移植到Linux
//		4) 8/20/2003 10:59:33	增加实序输出语法等 (by nature)
//			a) 将所有结点按实际顺序输出：${*...$[var-...$]...$}
//          b) 修正：忽略不存在变量，( ${var=...} )
//		5) 9/2/2003 11:36:34	语法结构化
//
// $Id: script_out.h,v 1.1 2006/12/02 06:44:18 xushiwei Exp $
// -----------------------------------------------------------------------*/
#ifndef __TPL_V1_SCRIPT_OUT_H__
#define __TPL_V1_SCRIPT_OUT_H__

#ifndef __TPL_V1_SCRIPT_BASE_H__
#include "script_base.h"
#endif

#ifndef __TPL_V1_SCRIPT_VARIANT_H__
#include "script_variant.h"
#endif

#ifndef _STACK_
#include <stack>
#endif

#ifndef WARNING
#define WARNING(s)
#endif

#ifndef TEXT_SCRIPT_API
#define TEXT_SCRIPT_API				HRESULT __stdcall
#define TEXT_SCRIPT_API_(type)		type __stdcall
#endif

// -------------------------------------------------------------------------

template <class Script>
STDMETHODIMP SkipCondition(Script& in)	// a,b,c=...
{
	typedef typename Script::char_type char_type;
	typename Script::int_type ch;
	_NullString<char_type> _nullStr;
	for (;;)
	{
		if (GetCLangStringConst(in, _nullStr) == S_OK)
		{
			switch (SkipWhiteCharsGetChar(in))
			{
			case ',':
				break;
			case '=':
				return S_OK;
			default:
				return E_UNEXPECTED;
			}
		}
		else
		{
			for (;;)
			{
				ch = GetChar(in);
				if (ch == ',')
					break;
				if (ch == '=')
					return S_OK;
				if (ch == Script::endch)
					return E_UNEXPECTED;
			}
		}
	}
}

template <class Script>	// ...$}
STDMETHODIMP_(typename Script::int_type) SkipLoopControl(Script& in)
{
	int count = 1;
	typename Script::int_type ch;
	enum { endch = Script::endch };
	for (;;)
	{
		ch = GetChar(in);
		switch (ch)
		{
		case '$':
			ch = GetChar(in);
			switch (ch)
			{
			case '}':
				if (--count == 0)
					return ch;
				break;
			case '{':
				++count;
				break;
			}
			break;
		case endch:
			return ch;
		}
	}
}

template <class Script> // ...$; ...$>
STDMETHODIMP_(typename Script::int_type) SkipConditionControl(Script& in)
{
	int count = 1;
	typename Script::int_type ch;
	enum { endch = Script::endch };
	for (;;)
	{
		ch = GetChar(in);
		switch (ch)
		{
		case '$':
			ch = GetChar(in);
			switch (ch)
			{
			case ';':
				if (count == 1)
					return ch;
				break;
			case '>':
				if (--count == 0)
					return ch;
				break;
			case '<':
				++count;
				break;
			}
			break;
		case endch:
			return ch;
		}
	}
}

template <class Script>	// ...$]
STDMETHODIMP_(void) SkipLoopCondControl(Script& in)
{
	typename Script::int_type ch;
	enum { endch = Script::endch };
	for (;;)
	{
		ch = GetChar(in);
		switch (ch)
		{
		case '$':
			ch = GetChar(in);
			switch (ch)
			{
			case ']':
				return;
			case '{':
				ch = SkipLoopControl(in);
				UngetChar(in, ch);
				break;
			}
			break;
		case endch:
			return;
		}
	}
}

template <class Script, class String>	// ${*...$[var-...$]...$}
STDMETHODIMP_(typename Script::int_type) SkipActualControl(Script& in, String name)
{
	//Script::int_type pos = Script::endch;
	Script::int_type ch  = '{';
	Script::int_type count = 0;
	Script::int_type index = 0;
	for (;;)
	{
		//pos = in.tell();
		ch = GetChar(in);
		if (ch == '$')
		{
			ch = GetChar(in);
			switch(ch)
			{
			case '<':
			case '{':
				++count;
				break;
			case '[':
				++count;
				for (index = 0; index < name.size(); ++index)
					if (name.at(index) != GetChar(in))
						break;
				if (index == name.size() && count == 1 && '=' !=GetChar(in))
					return ch;
				break;
			case '@':
			case '>':
			case ']':
			case '}':
				--count;
				if (count < 0)
					return '}';
				break;
			default: ;
			}
		}
		else if (ch == Script::endch)
			return '}';
	}
	return '}';
}

// -------------------------------------------------------------------------

template <class Script, class EntriesList>
STDMETHODIMP CreateEntries(EntriesList& entriesList, Script& in)
{
	enum { endch = Script::endch };
	typename Script::int_type ch = '{';
	typename Script::pos_type pos;
	typename std::string sym;

	pos = in.tell();
	for (; endch != ch; )
	{
		ch = GetChar(in);
		switch (ch)
		{
		case '$':
			ch = GetChar(in);
			switch(ch)
			{
			case '@':
				if (GetCLangSymbol(in, sym) != S_OK || GetChar(in) != '=')
					goto EXIT_FALSE;
				entriesList[sym] = in.tell();
				SkipActualControl(in, (std::string)"}");
				break;
			default:;
			}
			break;
		default:;
		}
	}

	in.seek(pos);
	return S_OK;

EXIT_FALSE:
	in.seek(pos);
	return S_FALSE;
}

template <class Script, class String, class EntriesList>
STDMETHODIMP EnterEntries(const EntriesList& entriesList, 
						  Script& in, 
						  const String& entryName)
{
	typename EntriesList::const_iterator itFind = entriesList.find(entryName);
	if (itFind == entriesList.end())
		return S_FALSE;
	in.seek((*itFind).second);
	return S_OK;
}

// -------------------------------------------------------------------------

template <class _NodeList>
class KVariantNodeMap
{
public:
	typedef _NodeList NodeList;
	typedef typename NodeList::value_type Node;
	typedef typename Node::Variant Variant;
	typedef typename Variant::String String;

	enum VariantType
	{
		vtNone		= Variant::vtNone,
		vtInt		= Variant::vtInt,
		vtAtom		= Variant::vtAtom,
		vtElement	= Variant::vtElement,
	};
	
protected:
	typedef std::map<String, NodeList*> Map;
	typedef struct tagNodeState
	{
		const NodeList* nodeList;
		Map* nodeMap;
		int index;
		int count;
	} NodeState;

	// 注释后令只有当前结点下数据可视	
	// Map _nodeMap;

	std::stack<NodeState> _nodeStates;

public:
	KVariantNodeMap(const NodeList& nodeList)
	{
		Enter(nodeList, 1, 1);
	}
	
	void Enter(const NodeList& nodeList, int index, int count)
	{
		Map& nodeMap = *new Map;
		NodeState nodeState;
		{
			typename NodeList::const_iterator it;
			for (it = nodeList.begin(); it != nodeList.end(); ++it)
			{
				NodeList*& lst = nodeMap[(*it).name];
				if (lst == NULL)
					lst = new NodeList;
				lst->push_back( (*it) );
			}
		}
		/*
		// 注释后令只有当前结点下数据可视
		{
			typename Map::iterator it;
			for (it = nodeMap.begin(); it != nodeMap.end(); ++it)
			{
				std::swap(_nodeMap[(*it).first], (*it).second);
			}
		}
		*/
		nodeState.nodeList = &nodeList;
		nodeState.nodeMap = &nodeMap;
		nodeState.index = index;
		nodeState.count = count;
		_nodeStates.push(nodeState);
	}
	
	void Leave()
	{
		ASSERT(!_nodeStates.empty());

		typename Map::iterator it;
		Map& nodeMap = *_nodeStates.top().nodeMap;
		
		/*
		// 注释后令只有当前结点下数据可视
		for (it = nodeMap.begin(); it != nodeMap.end(); ++it)
		{
			typename Map::iterator it2 = _nodeMap.find( (*it).first );
			delete (*it2).second;
			if ( (*it).second )
				(*it2).second = (*it).second;
			else
				_nodeMap.erase(it2);
		}
		*/

		// 增加后令只有当前结点下数据可视
		for (it = nodeMap.begin(); it != nodeMap.end(); ++it)
			delete (*it).second;

		delete &nodeMap;
		_nodeStates.pop();
	}

	BOOL IsLastLoop() const
	{
		NodeState state = _nodeStates.top();
		return state.index == state.count;
	}
	
	const NodeList* GetAllNodes() const
	{
		ASSERT(!_nodeStates.empty());
		return _nodeStates.top().nodeList;
	}
	
	const NodeList* GetNodeList(const String& sym) const
	{
		// 加上下面这行后令只有当前结点下数据可视
		Map& _nodeMap = *_nodeStates.top().nodeMap;

//		printf("-- %s:\n",sym.c_str());
//		for (Map::iterator it=_nodeMap.begin(); it!=_nodeMap.end();++it)
//			printf("%s\n",(*it).first.c_str());
//		printf("---------------------------------<end\n");

		typename Map::const_iterator itFind = _nodeMap.find(sym);
		if (itFind == _nodeMap.end())
			return NULL;
		return (*itFind).second;
	}

	template <class ArchiveOut>
	STDMETHODIMP PutVar(ArchiveOut& out, const String& sym)
	{
		// 加上下面这行后令只有当前结点下数据可视
		Map& _nodeMap = *_nodeStates.top().nodeMap;
		
		typename Map::const_iterator itFind = _nodeMap.find(sym);
		if (itFind == _nodeMap.end())
		{
			WARNING("Warning: Unknown Variant, skiped.");
			return S_FALSE;
		}

		NodeList* pList = (*itFind).second;
//		ASSERT(pList->size() == 1);
		Variant& var = pList->front().value;
		switch( var.vt )
		{
		case vtAtom:
			out.put( var.atomVal );
			break;
		case vtInt:
			char tmp[32];
			itoa(var.intVal, tmp, 10);
			out.put( tmp );
			break;
		default:
			ASSERT(FALSE);
			return E_FAIL;
		}
		return S_OK;
	}

	// $<sym=...$;...$;...$> | $<sym?a,b,c=...$;...$;...$>
	template <class Script>
	STDMETHODIMP GetCondition(Script& in, int* nVal)
	{
		String sym;
		GetCLangSymbol(in, sym);

		Variant* var = NULL;
		
		// 加上下面这行后令只有当前结点下数据可视
		Map& _nodeMap = *_nodeStates.top().nodeMap;
		
		typename Map::const_iterator itFind = _nodeMap.find(sym);
		if (itFind != _nodeMap.end())
		{
			NodeList* pList = (*itFind).second;
			ASSERT(pList->size() == 1);
			var = &pList->front().value;
		}

		typename Script::int_type ch = SkipWhiteCharsGetChar(in);
		switch (ch)
		{
		case '?':
			*nVal = 0;
			for (;;)
			{
				if (var)
				{
					int val;
					if (GetCLangStringConst(in, sym) == S_OK)
					{
						String strVal;
						if (ChangeTypeToString(*var, strVal) == S_OK && strVal == sym)
							break;
					}
					else if (GetCLangIntConst(in, val) == S_OK)
					{
						int intVal;
						if (ChangeTypeToInt(*var, intVal) == S_OK && intVal == val)
							break;
					}
					else if (GetCLangSymbol(in, sym) == S_OK)
					{
						if (sym == "any")
							break;
					}
				}
				else if (GetCLangSymbol(in, sym) == S_OK)
				{
					if (sym == "null")
						break;
				}
				else
					return E_UNEXPECTED;

				++ *nVal;
				switch (SkipWhiteCharsGetChar(in))
				{
				case ',':
					break;
				case '=':
					return S_OK;
				default:
					return E_UNEXPECTED;
				}
			}
			return SkipCondition(in);

		case '=':
			if (itFind == _nodeMap.end())
				return S_FALSE;
			return ChangeTypeToInt(*var, *nVal);

		default:
			return E_UNEXPECTED;
		}
	}
};

template <class Script, class ArchiveOut, class NodeMap, class EntriesList>
STDMETHODIMP TemplateReplaceImpl(
								 Script& in,
								 ArchiveOut& out,
								 NodeMap& vars,
								 typename Script::int_type* chRet,
								 const EntriesList& entriesList
								 )
{
	typedef typename NodeMap::NodeList NodeList;
	typedef typename NodeMap::Variant Variant;
	typename Script::int_type ch;
	typename NodeMap::String sym;
	enum { endch = Script::endch };
	for (;;)
	{
		ch = GetChar(in);
		switch (ch)
		{
		case '$':
			ch = GetChar(in);
			switch (ch)
			{
			case '(':		// $(sym)
				ch = GetChar(in);
				if (ch == '@') 
				{           // $(@sym)
					if (GetCLangSymbol(in, sym) != S_OK || GetChar(in) != ')')
						return E_UNEXPECTED;
					Script::pos_type pos = in.tell();
					if (EnterEntries(entriesList, in, sym) == S_OK)
						TemplateReplaceImpl(in, out, vars, 
							(typename Script::int_type*)NULL, entriesList);
					else
						break;
					in.seek(pos);
					break;
				}
				else
					UngetChar(in, ch);
				if (GetCLangSymbol(in, sym) != S_OK || GetChar(in) != ')')
					return E_UNEXPECTED;
				vars.PutVar(out, sym);
				break;
			case '{':		// ${sym=...$[...$]...$}
				const NodeList* pList;
				int fgActualFlag;
				fgActualFlag = 0;
				if (GetCLangSymbol(in, sym) == S_OK)
				{
					pList = vars.GetNodeList(sym);
					if (!pList || pList->size() <=0)
					{
						SkipActualControl(in, (typename NodeMap::String)"}");
						continue;
					}
				}
				else if (GetChar(in) == '*')
				{
					pList = vars.GetAllNodes();
					fgActualFlag = 1;
				}
				else
					return E_UNEXPECTED;
				ch = GetChar(in);
				if (ch != '=')
				{
					if (!fgActualFlag)
						return E_UNEXPECTED;
					else	// ${*...$[var-...$]...$}
					{
						typename Script::pos_type pos = in.tell();
						typename NodeList::const_iterator it;	
						int index = 0;
						int count = pList->size();
						for (it = pList->begin(); it != pList->end(); ++it)
						{
							const Variant& var = (*it).value;
							NodeMap::String& strTemp = (typename NodeMap::String)(*it).name;
							if (var.vt != Variant::vtElement)
								continue;
							in.seek(pos);
							if (SkipActualControl(in, (typename NodeMap::String)(*it).name) != '}')
							{
								vars.Enter(*var.lstVal, ++index, count);
								if (S_OK != TemplateReplaceImpl(in, out, vars,
										(typename Script::int_type*)NULL, entriesList))
									return E_UNEXPECTED;
								vars.Leave();
							}
						}
						in.seek(pos);
						SkipActualControl(in, (NodeMap::String)"}");
						break;
					}
				}
				if (pList == NULL)
				{
					if (SkipLoopControl(in) != '}')
						return E_UNEXPECTED;
				}
				else
				{
					typename Script::pos_type pos = in.tell();
					typename NodeList::const_iterator it;
					int count = pList->size();
					int index = 0;
					for (it = pList->begin(); it != pList->end(); ++it)
					{
						const Variant& var = (*it).value;
						if (var.vt != Variant::vtElement)
							return E_UNEXPECTED;
						vars.Enter(*var.lstVal, ++index, count);
						in.seek(pos);
						if (S_OK != TemplateReplaceImpl(in, out, vars,
							(typename Script::int_type*)NULL, entriesList))
							return E_UNEXPECTED;
						vars.Leave();
					}
				}
				break;
			case '}':		// $}
				return S_OK;
			case '<':	{	// $<sym=...$;...$;...$>, $<sym?a,b,c=...$;...$;...$>
				int intVal = -1;
				HRESULT hr = vars.GetCondition(in, &intVal);
				if (hr < S_OK)
					return hr;
				else
				{
					while (intVal)
					{
						ch = SkipConditionControl(in);
						if (ch != ';')
							break;
						--intVal;
					}
					if (intVal == 0)
					{
						if (S_OK != TemplateReplaceImpl(in, out, vars, &ch, entriesList))
							return E_UNEXPECTED;
						while (ch == ';')
							ch = SkipConditionControl(in);
					}
					if (ch != '>')
						return E_UNEXPECTED;
				}
				break;	}
			case ';':
			case '>':
				if (chRet == NULL)
					return E_UNEXPECTED;
				*chRet = ch;
				return S_OK;
			case '$':
				out.put('$');
				break;
			case '[':
				if (vars.IsLastLoop())
					SkipLoopCondControl(in);
				break;
			case ']':
				return S_OK;
			case '@':
				return S_OK;
			default:
				return E_UNEXPECTED;
			}
			break;
		case endch:
			return S_OK;
		default:
			out.put(ch);
		}
	}
}

template <class Script, class ArchiveOut, class NodeList>
STDMETHODIMP TemplateReplace(
							 Script& in,
							 ArchiveOut& out,
							 const NodeList& nodeList
							 )
{
	std::map<std::string, int> entriesMap;
	CreateEntries(entriesMap, in);
	EnterEntries(entriesMap, in, "doc");
	int i = entriesMap["doc"];
	KVariantNodeMap<NodeList> nodeMap(nodeList);
	return TemplateReplaceImpl(in, out, nodeMap, (typename Script::int_type*)NULL, entriesMap);
}

// -------------------------------------------------------------------------
// $Log: script_out.h,v $
// Revision 1.1  2006/12/02 06:44:18  xushiwei
// Text Processing Library - Version 1.0
//

#endif /* __TPL_V1_SCRIPT_OUT_H__ */
