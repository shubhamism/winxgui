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
// Module: tpl/toolbox/KeywordTblGen.h
// Creator: xushiwei
// Email: xushiweizh@gmail.com
// Date: 2006-7-28 01:40:05
// 
// $Id: $
// -----------------------------------------------------------------------*/
#ifndef __TPL_TOOLBOX_KEYWORDTBLGEN_H__
#define __TPL_TOOLBOX_KEYWORDTBLGEN_H__

#ifndef __STDEXT_STRING_H__
#include <stdext/String.h>
#endif

#ifndef _VECTOR_
#include <vector>
#endif

#ifndef _SET_
#include <set>
#endif

namespace tpl { namespace toolbox {

// -------------------------------------------------------------------------
// validateKeywordTbl

template <class E, class LogT>
inline bool validateKeywordTbl(
	LogT& logInfo, const E** keywords, size_t count)
{
	typedef std::basic_string<E> string_type;
	typedef std::set<string_type> string_set;

	string_set keyword_set;
	for (size_t i = 0; i < count; ++i) {
		if (!keyword_set.insert(keywords[i]).second) {
			logInfo.trace("\n--> Input error: keyword \"%s\" is repeated.\n", keywords[i]);
			return false;
		}
	}
	return true;
}

// -------------------------------------------------------------------------
// Hasher

template <class E>
class SumHasher
{
public:
	static DWORD winx_call hashOf(const E* s, size_t param)
	{
		DWORD h = 0;
		for ( ; *s; ++s)
			h = param*h + *s;
		return h;
	}

	static const char* winx_call getCode()
	{
		return
	"static DWORD winx_call hashOf(const E* s)\n\
	{\n\
		DWORD h = 0;\n\
		for ( ; *s; ++s)\n\
			h = param*h + *s;\n\
		return h;\n\
	}"
		;
	}
};

template <class E>
class XorHasher
{
public:
	static DWORD winx_call hashOf(const E* s, size_t param)
	{
		DWORD h = 0;
		for ( ; *s; ++s)
			h = param*h ^ *s;
		return h;
	}

	static const char* winx_call getCode()
	{
		return
	"static DWORD winx_call hashOf(const E* s)\n\
	{\n\
		DWORD h = 0;\n\
		for ( ; *s; ++s)\n\
			h = param*h ^ *s;\n\
		return h;\n\
	}"
		;
	}
};

// -------------------------------------------------------------------------
// class StaticHashMap

#define _Tpl_ToolBox_StaticHashMap_FormatBegin								\
"\n\
class %s // --> StaticHashMap\n\
{\n\
private:\n\
	typedef %s E;\n\
\n\
	enum { bucket = %d };\n\
	enum { param = %d };\n\
\n\
public:\n\
	typedef size_t size_type;\n\
	typedef %s data_type;\n\
\n\
	struct value_type\n\
	{\n\
		const E* first;\n\
		data_type second;\n\
	};\n\
\n\
	%s\n\
\n\
	static bool winx_call lookup(const E* key, data_type& val) const\n\
	{\n\
		%sstatic value_type data[] = {\n"

#define _Tpl_ToolBox_StaticHashMap_FormatEnd								\
"		};\n\
		const size_type h = hashOf(key) % bucket;\n\
		if (std::compare(data[h].first, key) == 0)\n\
		{\n\
			val = data[h].second;\n\
			return true;\n\
		}\n\
		return false;\n\
	}\n\
};"

#define _Tpl_ToolBox_StaticHashMap_Param									\
	szClass, szCharT, bucket, param, szDataT, szHasher, szInitData

// -------------------------------------------------------------------------
// class StaticHashSet

#define _Tpl_ToolBox_StaticHashSet_FormatBegin								\
"\n\
class %s // --> StaticHashSet\n\
{\n\
private:\n\
	typedef %s E;\n\
\n\
	enum { bucket = %d };\n\
	enum { param = %d };\n\
\n\
public:\n\
	typedef size_t size_type;\n\
\n\
	%s\n\
\n\
	static bool winx_call lookup(const E* key) const\n\
	{\n\
		static E const* const* data[] = {\n"

#define _Tpl_ToolBox_StaticHashSet_FormatEnd									\
"		};\n\
		const size_type h = hashOf(key) % bucket;\n\
		return std::compare(data[h].first, key) == 0;\n\
	}\n\
};"

#define _Tpl_ToolBox_StaticHashSet_Param										\
	szClass, szCharT, bucket, param, szHasher

// -------------------------------------------------------------------------
// class StaticHashMapWriter

template <class LogT>
class StaticHashMapWriter
{
private:
	LogT& log;
	const char* szClass;
	const char* szCharT;
	const char* szDataT;
	const char* szInitData;
	const char* szNullData;
	char const* const* szDataVals;
	const char* szStringPrefix;
	const char* szFileBegin;
	const char* szFileEnd;
	
public:
	StaticHashMapWriter(
		LogT& logArg,
		char const* const* szDataValsArg,
		const char* szDataTArg,
		const char* szNullDataArg = "0",
		const char* szInitDataArg = "",
		const char* szClassArg = "StaticHashMap",
		const char* szCharTArg = "char",
		const char* szStringPrefixArg = "",
		const char* szFileBeginArg = "",
		const char* szFileEndArg = ""
		)
		: log(logArg), szClass(szClassArg), szCharT(szCharTArg), szStringPrefix(szStringPrefixArg),
		  szDataT(szDataTArg), szNullData(szNullDataArg), szInitData(szInitDataArg), szDataVals(szDataValsArg),
		  szFileBegin(szFileBeginArg), szFileEnd(szFileEndArg)
	{
	}

	template <class E, class HasherT>
	void winx_call write(HasherT hasher, E const* const* keys, size_t n, size_t bucket, size_t param)
	{
		const char* szHasher = hasher.getCode();

		log.printString(szFileBegin);
		log.trace(_Tpl_ToolBox_StaticHashMap_FormatBegin, _Tpl_ToolBox_StaticHashMap_Param);

		std::vector< std::pair<const E*, size_t> > cont(bucket);
		for (size_t i = 0; i < n; ++i)
		{
			const UINT h = hasher.hashOf(keys[i], param) % bucket;
			cont[h].first = keys[i];
			cont[h].second = i;
		}
		for (size_t j = 0; j < bucket; ++j)
		{
			const E* key = cont[j].first;
			log.trace("\t\t\t{ %s\"", szStringPrefix);
			if (key)
				log.printString(key);
			log.printString("\", ");
			if (key)
				log.printString(szDataVals[cont[j].second]);
			else
				log.printString(szNullData);
			log.printString(" },\n");
		}
		
		log.printString(_Tpl_ToolBox_StaticHashMap_FormatEnd);
		log.printString(szFileEnd);
	}
};

// -------------------------------------------------------------------------
// class StaticHashSetWriter

template <class LogT>
class StaticHashSetWriter
{
private:
	LogT& log;
	const char* szClass;
	const char* szCharT;
	const char* szStringPrefix;
	const char* szFileBegin;
	const char* szFileEnd;
	
public:
	StaticHashSetWriter(
		LogT& logArg, 
		const char* szClassArg = "StaticHashSet",
		const char* szCharTArg = "char",
		const char* szStringPrefixArg = "",
		const char* szFileBeginArg = "",
		const char* szFileEndArg = ""
		)
		: log(logArg), szClass(szClassArg), szCharT(szCharTArg), szStringPrefix(szStringPrefixArg),
		  szFileBegin(szFileBeginArg), szFileEnd(szFileEndArg)
	{
	}

	template <class E, class HasherT>
	void winx_call write(HasherT hasher, E const* const* keys, size_t n, size_t bucket, size_t param)
	{
		const char* szHasher = hasher.getCode();

		log.printString(szFileBegin);
		log.trace(_Tpl_ToolBox_StaticHashSet_FormatBegin, _Tpl_ToolBox_StaticHashSet_Param);

		std::vector<const E*> cont(bucket);
		for (size_t i = 0; i < n; ++i)
		{
			const UINT h = hasher.hashOf(keys[i], param) % bucket;
			cont[h] = keys[i];
		}
		for (size_t j = 0; j < bucket; ++j)
		{
			const E* key = cont[j];
			log.trace("\t\t\t%s\"", szStringPrefix);
			if (key)
				log.printString(key);
			log.printString("\",\n");
		}
		
		log.printString(_Tpl_ToolBox_StaticHashSet_FormatEnd);
		log.printString(szFileEnd);
	}
};

// -------------------------------------------------------------------------
// class KeywordTblGen

template <class E>
class KeywordTblGen
{
private:
	E const* const* keywords;
	size_t count;
	size_t bucket;
	size_t param;
	
	std::vector<int> check;

private:
	template <class HasherT>
	BOOL winx_call __check(HasherT hasher)
	{
		std::fill(check.begin(), check.end(), 0);
		for (size_t i = 0; i < count; ++i)
		{
			const UINT h = hasher.hashOf(keywords[i], param) % bucket;
			if (check[h])
				return FALSE;
			check[h] = TRUE;
		}
		return TRUE;
	}

public:
	template <class LogT, class WriterT>
	inline void winx_call run(
		WriterT& wr, LogT& logInfo,
		E const* const* keys, size_t n, size_t paramLim = INT_MAX/128)
	{
		XorHasher<E> xorHasher;
		SumHasher<E> sumHasher;

		keywords = keys;
		count = n;
		check.resize(count);
		for (bucket = count; ; ++bucket)
		{
			for (param = 2; param < paramLim; ++param)
			{
				if (__check(xorHasher))		 wr.write(xorHasher, keys, n, bucket, param);
				else if (__check(sumHasher)) wr.write(sumHasher, keys, n, bucket, param);
				else {
					if (!(param & 0x1ffff))
						logInfo.step();
					continue;
				}
				return;
			}
			check.push_back(0);
			logInfo.newline();
		}
	}
};

// -------------------------------------------------------------------------
// class TestKeywordTblGen

template <class LogT>
class TestKeywordTblGen : public TestCase
{
	WINX_TEST_SUITE(TestKeywordTblGen);
		WINX_TEST(testSetAnsi);
		WINX_TEST(testSetUni);
		WINX_TEST(testMapAnsi);
		WINX_TEST(testMapUni);
	WINX_TEST_SUITE_END();

public:
	void testSetAnsi(LogT& log)
	{
		const char* keywords[] = { "if", "while", "for"	};
		std::ErrorLog logInfo;
		StaticHashSetWriter<LogT> wr(log);
		KeywordTblGen<char> gen;
		gen.run(wr, logInfo, keywords, countof(keywords));
	}

	void testSetUni(LogT& log)
	{
		const WCHAR* keywords[] = { L"if", L"while", L"for"	};
		std::ErrorLog logInfo;
		StaticHashSetWriter<LogT> wr(log, "StaticHashSet", "WCHAR", "L");
		KeywordTblGen<WCHAR> gen;
		gen.run(wr, logInfo, keywords, countof(keywords));
	}

	void testMapAnsi(LogT& log)
	{
		const char* keywords[] = { "if", "while", "for"	};
		const char* vals[] = { "10", "11", "12"	};
		std::ErrorLog logInfo;
		StaticHashMapWriter<LogT> wr(log, vals, "int");
		KeywordTblGen<char> gen;
		gen.run(wr, logInfo, keywords, countof(keywords));
	}

	void testMapUni(LogT& log)
	{
		const WCHAR* keywords[] = { L"if", L"while", L"for"	};
		const char* vals[] = { "10", "11", "12"	};
		std::ErrorLog logInfo;
		StaticHashMapWriter<LogT> wr(log, vals, "int", "0", "", "StaticHashMap", "WCHAR", "L");
		KeywordTblGen<WCHAR> gen;
		gen.run(wr, logInfo, keywords, countof(keywords));
	}
};

// -------------------------------------------------------------------------
// $Log: $

}; };

#endif /* __TPL_TOOLBOX_KEYWORDTBLGEN_H__ */
