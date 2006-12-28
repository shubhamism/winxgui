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

#ifndef _STRING_
#include <string>
#endif

#ifndef _VECTOR_
#include <vector>
#endif

#ifndef _SET_
#include <set>
#endif

// -------------------------------------------------------------------------
// hashOfString

#define __DM_CODE_HASH_SUM	\
	"DWORD h = 0;\n\
	for ( ; *s; ++s)\n\
		h = param*h + *s;"

#define __DM_CODE_HASH_XOR	\
	"DWORD h = 0;\n\
	for ( ; *s; ++s)\n\
		h = param*h ^ *s;"

template <class E>
inline DWORD hashOfStringBySum(const E* s, size_t param)
{
	DWORD h = 0;
	for ( ; *s; ++s)
		h = (param^h) + *s;
	return h;
}

template <class E>
inline DWORD hashOfStringByXor(const E* s, size_t param)
{
	DWORD h = 0;
	for ( ; *s; ++s)
		h = param*h ^ *s;
	return h;
}

#define __DM_FMT_HASH_OF_STRING(szHashFunc, hash) "\n\
// -------------------------------------------------------------------------\n\
// %s - [hashOfString]\n\
\n\
template <class E>\n\
inline DWORD %s(const E* s)\n\
{\n\
	enum { param = %d };\n\
	%s\n\
	return h;\n\
}\n\
\n", szHashFunc, szHashFunc, hash.param, hash.code

// -------------------------------------------------------------------------
// isKeyword

#if (0)

DWORD hashOfString(const E* s, size_t param);

template <class E, int BUCKET>
inline bool isKeyword(const E* s)
{
	static const E* keywords[BUCKET] =
	{
		"KEYWORD-1",
		"KEYWORD-2",
		...,
		"KEYWORD-BUCKET",
	};
	DWORD h = hashOfString(s) % BUCKET;
	return strcmp(keywords[h], s) == 0;
}

#endif

#define __DM_FMT_IS_KEYWORD_BGN(szIsKeywordFunc, bucket, T, E)	"\
// -------------------------------------------------------------------------\n\
// %s - [isKeyword]\n\
\n\
%s\
inline bool %s(const %s* s)\n\
{\n\
	static const %s* keywords[%d] =\n\
	{\n", szIsKeywordFunc, T, szIsKeywordFunc, E, E, bucket

#define __DM_FMT_IS_KEYWORD_END(bucket, strcmp) "\
	};\n\
	DWORD h = hashOfString(s) %% %d;\n\
	return %s(keywords[h], s) == 0;\n\
}\n\
\n", bucket, strcmp

// -------------------------------------------------------------------------
// validateInput

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
// calcKeywordTblParam

struct HashParamT
{
	size_t param;
	const char* code;
	int ch;
};

#define __DM_KEYWORD_GEN_PARAM_LIM	(INT_MAX/128)
#define __DM_CHECK_PARAM(hashOfString, scode, c)							\
{																			\
	std::fill(check.begin(), check.end(), 0);								\
	for (i = 0; i < count; ++i)												\
	{																		\
		h = hashOfString(keywords[i], param) % bucket;						\
		if (check[h])														\
			break;															\
		check[h] = 1;														\
	}																		\
	if (i == count)															\
	{																		\
		hash.param = param;													\
		hash.code = scode;													\
		hash.ch = c;														\
		return bucket;														\
	}																		\
}

template <class E, class LogT>
inline size_t calcKeywordTblParam(
	LogT& logInfo,
	HashParamT& hash,
	const E** keywords, size_t count,
	size_t paramLim = __DM_KEYWORD_GEN_PARAM_LIM)
{
	size_t h, i, param;
	std::vector<int> check(count);
	for (size_t bucket = count; ; ++bucket)
	{
		for (param = 2; param < paramLim; ++param)
		{
			__DM_CHECK_PARAM(hashOfStringByXor, __DM_CODE_HASH_XOR, '^');
			__DM_CHECK_PARAM(hashOfStringBySum, __DM_CODE_HASH_SUM, '+');
			if (!(param & 0x1ffff))
				logInfo.step();
		}
		logInfo.trace("\n");
		check.push_back(0);
	}
}

// -------------------------------------------------------------------------
// genKeywordTbl

template <class LogT, class LogT2>
inline void genKeywordTbl(
	LogT& log, LogT2& logInfo,
	const char** keywords, size_t count,
	const char* szHashFunc = "hashOfString",
	const char* szIsKeywordFunc = "isKeyword",
	size_t paramLim = __DM_KEYWORD_GEN_PARAM_LIM)
{
	if (!validateKeywordTbl(logInfo, keywords, count))
		return;

	HashParamT hash;
	size_t bucket = calcKeywordTblParam(logInfo, hash, keywords, count, paramLim);
	
	log.trace(__DM_FMT_HASH_OF_STRING(szHashFunc, hash));

	log.trace(__DM_FMT_IS_KEYWORD_BGN(szIsKeywordFunc, bucket, "", "char"));
	size_t i;
	std::vector<const char*> cont;
	cont.resize(bucket);
	switch (hash.ch)
	{
	case '+':
		for (i = 0; i < count; ++i) {
			size_t h = hashOfStringBySum(keywords[i], hash.param) % bucket;
			cont[h] = keywords[i];
		}
		break;
	case '^':
		for (i = 0; i < count; ++i) {
			size_t h = hashOfStringByXor(keywords[i], hash.param) % bucket;
			cont[h] = keywords[i];
		}
		break;
	}
	for (size_t j = 0; j < bucket; ++j)
	{
		const char* key = cont[j];
		log.trace("\t\t\"%s\",\n", (key ? key : ""));
	}
	log.trace(__DM_FMT_IS_KEYWORD_END(bucket, "strcmp"));

	logInfo.trace(
		"\ncount = %d, bucket = %d, param = %d, op = %c\n",
		count, bucket, hash.param, hash.ch);
}

// -------------------------------------------------------------------------
// class TestKeywordTblGen

template <class LogT>
class TestKeywordTblGen
{
public:
	static void doTest(LogT& log)
	{
		const char* keywords[] = {
			"if", "while", "for", "sizeof",
			"int", "char", "long", "double", "float", "signed", "unsigned",
			"void", "do", "static",
			"template", "typename",
			"class", "struct", "interface", "namespace",// "enum", //"define"
		};
		std::ErrorLog logInfo;
		size_t count = sizeof(keywords)/sizeof(const char*);
		genKeywordTbl(log, logInfo, keywords, count);
	}
};

// -------------------------------------------------------------------------
// $Log: $

#endif /* __TPL_TOOLBOX_KEYWORDTBLGEN_H__ */
