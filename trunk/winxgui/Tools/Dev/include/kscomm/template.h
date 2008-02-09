/* -------------------------------------------------------------------------
//	文件名		：	templat/template.h
//	创建者		：	许式伟
//	创建时间	：	2002-12-21 23:54:17
//	功能描述	：	
//
// -----------------------------------------------------------------------*/
#ifndef __TEMPLAT_TEMPLATE_H__
#define __TEMPLAT_TEMPLATE_H__

#pragma warning(disable:4786)
#include <map>
#include <string>
#include <list>

#ifndef WARNING
#define WARNING(s)
#endif

#define __kfc_template_replace_begin	//namespace __kfc_template_replace {
#define __kfc_template_replace_end		//};

// -------------------------------------------------------------------------

__kfc_template_replace_begin

using std::map;
using std::list;
using std::string;

struct KVarInfo
{
	typedef const char* szVal_t;
	typedef list<KVarInfo> listVal_t;
	typedef  map<string, KVarInfo> structVal_t;
	enum
	{
		vtNone		= 0,
		vtInt		= 1,
		vtString	= 2,
		vtList		= 3,
		vtStruct	= 4
	};
	int vt;
	union
	{
		int intVal;
		szVal_t szVal;
		listVal_t* lstVal;
		structVal_t* structVal;
	};
	KVarInfo() {}
	KVarInfo(int intValA) : vt(vtInt), intVal(intValA) {}
	KVarInfo(szVal_t szValA) : vt(vtString), szVal(szValA) {}
	KVarInfo(listVal_t* lstValA) : vt(vtList), lstVal(lstValA) {}
	KVarInfo(structVal_t* strucValA) : vt(vtStruct), structVal(strucValA) {}
	KVarInfo(const KVarInfo& varA) : vt(varA.vt), lstVal(varA.lstVal) {}
};

typedef map<string, KVarInfo> KVars_t;

template <class StreamInput>
int GetSymbol(StreamInput& in, string& sym)
{
	char ch;
	sym.erase();
	while (1)
	{
		ch = in.get();
		if (
			(ch >= 'a' && ch <= 'z') ||
			(ch >= 'A' && ch <= 'Z') ||
			(ch == '_')
			)
		{
			sym.append(1, ch);
		}
		else
			break;
	}
	return ch;
}

inline
KVars_t::iterator FindVar(KVars_t& vars, string sym)
{
	KVars_t::iterator varFind;
	while (1)
	{
		varFind = vars.find(sym);
		if (varFind == vars.end())
		{
			WARNING("Warning: Unknown Variant, skiped.");
			break;
		}

		int vt = (*varFind).second.vt;
		if (vt != KVarInfo::vtList)
			break;

		sym.append(1, '\t');
	}
	return varFind;
}

template <class StreamInput>
int SkipLoopControl(StreamInput& in)
{
	int count = 1;
	int ch;
	while (1)
	{
		ch = in.get();
		switch (ch)
		{
		case '$':
			ch = in.get();
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
		case StreamInput::endch:
			return ch;
		}
	}
}

template <class StreamInput>
int SkipConditionControl(StreamInput& in)
{
	int count = 1;
	int ch;
	while (1)
	{
		ch = in.get();
		switch (ch)
		{
		case '$':
			ch = in.get();
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
		case StreamInput::endch:
			return ch;
		}
	}
}

template <class StreamInput, class StreamOutput>
HRESULT TemplateReplace(StreamInput& in, StreamOutput& out, KVars_t& vars, int* chRet = NULL)
{
	int ch;
	string sym;
	KVars_t::iterator varFind;
	while (1)
	{
		ch = in.get();
		switch (ch)
		{
		case '$':
			ch = in.get();
			switch (ch)
			{
			case '(':	// $(sym)
				ch = GetSymbol(in, sym); 
				if (ch != ')')
					return E_UNEXPECTED;
				varFind = FindVar(vars, sym);
				if (varFind != vars.end())
				{
					KVarInfo& var = (*varFind).second;
					switch (var.vt)
					{
					case KVarInfo::vtString:
						out.put(var.szVal);
						break;
					}
				}
				break;
			case '{':	// ${sym=...$}
				ch = GetSymbol(in, sym);
				if (ch != '=')
					return E_UNEXPECTED;

				varFind = vars.find(sym);
				if (varFind != vars.end())
				{
					KVarInfo& var = (*varFind).second;
					if (var.vt != KVarInfo::vtList)
						return E_UNEXPECTED;

					KVarInfo::listVal_t& lstVal = *var.lstVal;
					KVarInfo::listVal_t::iterator it;
					if (lstVal.empty())
					{
						if (SkipLoopControl(in) != '}')
							return E_UNEXPECTED;
					}
					else
					{
						sym.append(1, '\t');
						typename StreamInput::streampos pos = in.tellg();
						for (it = lstVal.begin(); it != lstVal.end(); ++it)
						{
							KVars_t varsNew = vars;
							if ((*it).vt == KVarInfo::vtStruct)
							{
								KVarInfo::structVal_t& structVal = *(*it).structVal;
								KVarInfo::structVal_t::iterator it2;
								for (it2 = structVal.begin(); it2 != structVal.end(); ++it2)
								{
									varsNew.insert(*it2);
								}
							}
							else
								varsNew[sym] = *it;
							in.seekg(pos);
							TemplateReplace(in, out, varsNew);
						}
					}
				}
				else
					WARNING("Warning: Unknown Variant, skiped.");
				break;
			case '}':	// $}
				return S_OK;
			case '<':	// $<sym=...$;...$;...$>
				ch = GetSymbol(in, sym);
				if (ch != '=')
					return E_UNEXPECTED;

				varFind = FindVar(vars, sym);
				if (varFind != vars.end())
				{
					KVarInfo& var = (*varFind).second;
					if (var.vt != KVarInfo::vtInt)
						return E_UNEXPECTED;
					
					int intVal = var.intVal;
					while (intVal)
					{
						ch = SkipConditionControl(in);
						if (ch != ';')
							break;
						--intVal;
					}
					if (intVal == 0)
					{
						TemplateReplace(in, out, vars, &ch);
						while (ch == ';')
							ch = SkipConditionControl(in);
					}
					if (ch != '>')
						return E_UNEXPECTED;
				}
				break;
			case ';':
			case '>':
				if (chRet == NULL)
					return E_UNEXPECTED;
				*chRet = ch;
				return S_OK;
			case '$':
				out.put('$');
				break;
			default:
				return E_UNEXPECTED;
			}
			break;
		case StreamInput::endch:
			return S_OK;
		default:
			out.put(ch);
		}
	}
}

// -------------------------------------------------------------------------

class KListVarInfo : public KVarInfo::listVal_t
{
public:
	KListVarInfo() {}
	KListVarInfo(const list<string>& src)
	{
		typedef std::list<string>::const_iterator iterator;
		for (iterator it = src.begin(); it != src.end(); ++it)
		{
			push_back((*it).c_str());
		}
	}
};

// -------------------------------------------------------------------------

__kfc_template_replace_end

#endif /* __TEMPLAT_TEMPLATE_H__ */

