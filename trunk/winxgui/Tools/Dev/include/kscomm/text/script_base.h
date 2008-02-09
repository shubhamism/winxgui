/* -------------------------------------------------------------------------
//	文件名		：	text/script_base.h
//	创建者		：	许式伟
//	创建时间	：	4/19/2003 11:51:25 PM
//	功能描述	：	
//
// -----------------------------------------------------------------------*/
#ifndef __KFC_TEXT_SCRIPT_BASE_H__
#define __KFC_TEXT_SCRIPT_BASE_H__

#ifndef _INC_LIMITS
#include <limits.h>
#endif

// -------------------------------------------------------------------------

#ifndef _KFC
#define _KFC
#define _KFC_BEGIN
#define _KFC_END
#endif

#ifndef _KFC_TEXT_SCRIPT
#define _KFC_TEXT_SCRIPT
#define _KFC_TEXT_SCRIPT_BEGIN
#define _KFC_TEXT_SCRIPT_END
#endif

#ifndef E_INVALID_SYMBOL
#define E_INVALID_SYMBOL		E_UNEXPECTED
#endif

#ifndef E_INVALID_STRING_CONST
#define E_INVALID_STRING_CONST	E_INVALID_SYMBOL
#endif

#ifndef E_INVALID_INT_CONST
#define E_INVALID_INT_CONST		E_INVALID_SYMBOL
#endif

#ifndef E_INVALID_ESCCHAR
#define E_INVALID_ESCCHAR		E_INVALID_SYMBOL
#endif

#ifndef E_MISSING_QUOTE
#define E_MISSING_QUOTE			E_INVALID_SYMBOL
#endif

#ifndef E_STRING_UNMATCH
#define E_STRING_UNMATCH		E_UNEXPECTED
#endif

_KFC_TEXT_SCRIPT_BEGIN

// -------------------------------------------------------------------------

template <class int_type> inline
STDMETHODIMP_(int) IsWhiteChar(int_type ch)
{
	switch (ch)
	{
	case ' ':	case '\t':	case '\r':	case '\n':	return TRUE;
	default:	return FALSE;
	}
}

template <class int_type>
STDMETHODIMP_(int) ToHex(int_type ch)
{
	static const char g_hex_chars[] =
	{
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'a', 'b', 'c', 'd', 'e', 'f', 'A', 'B', 'C', 'D', 'E', 'F'
	};
	for (int i = 0; i < countof(g_hex_chars); ++i)
	{
		if (g_hex_chars[i] == ch)
		{
			return (i < 16 ? i : i - 6);
		}
	}
	return -1;
}

template <class char_type>
STDMETHODIMP_(int) StrCompare(const char_type* src, const char_type* dst)
{
	int ret = 0 ;
	
	while( ! (ret = (int)(*src - *dst)) && *dst)
		++src, ++dst;
	
	return ret;
}

// -------------------------------------------------------------------------

template <class Archive> inline 
STDMETHODIMP_(typename Archive::int_type) GetChar(Archive& src)
{
	return src.get();
}

template <class Archive> inline 
STDMETHODIMP_(void) UngetChar(Archive& src, typename Archive::int_type ch)
{
	if (ch != Archive::endch)
		src.unget();
}

template <class Archive> inline 
STDMETHODIMP_(typename Archive::int_type) PeekChar(Archive& src)
{
	return src.peek();
}

template <class char_type, class String> inline
STDMETHODIMP_(void) AppendChar(String& str, char_type ch)
{
	str.append(1, (typename String::value_type)ch);
}

template <class String> inline
STDMETHODIMP_(void) ClearString(String& str)
{
	str.erase();
}

template <class String> inline
STDMETHODIMP_(typename String::const_pointer) ToCStr(const String& str)
{
	return str.c_str();
}

// -------------------------------------------------------------------------

template <class String>
STDMETHODIMP_(void) IntToString(String& str, int val, int radix)
{
	static const char g_chars[] =
	{
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
#	if !defined(USES_UPPERCASE_HEX)
		'a', 'b', 'c', 'd', 'e', 'f', 'g',
		'h', 'i', 'j', 'k', 'l', 'm', 'n',
		'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
#	else
		'A', 'B', 'C', 'D', 'E', 'F', 'G',
		'H', 'I', 'J', 'K', 'L', 'M', 'N',
		'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
#	endif
	};
	ASSERT(radix <= 26+10);
	ClearString(str);
	do
	{
		AppendChar(str, g_chars[val % radix]);
		val /= radix;
	}
	while (val);
}

// -------------------------------------------------------------------------

template <class Archive> inline
STDMETHODIMP LookupChar(Archive& src, typename Archive::int_type chLookup)
{
	typename Archive::int_type ch;
	while ((ch = GetChar(src)) != chLookup)
	{
		if (ch == Archive::endch)
			return S_FALSE;
	}
	return S_OK;
}

template <class Archive>
STDMETHODIMP MatchString(Archive& src, const typename Archive::char_type* szMatch)
{
	typename Archive::int_type ch;
	while (*szMatch)
	{
		ch = GetChar(src);
		if (ch != *szMatch)
			return E_STRING_UNMATCH;
		++szMatch;
	}
	return S_OK;
}

template <class Archive>
STDMETHODIMP_(typename Archive::int_type) SkipWhiteCharsGetChar(Archive& src)
{
	typename Archive::int_type ch;

	do
	{
		ch = GetChar(src);
	}
	while ( IsWhiteChar(ch) );
	
	return ch;
}

template <class Archive> inline
STDMETHODIMP_(void) SkipWhiteChars(Archive& src)
{
	UngetChar(
		src,
		SkipWhiteCharsGetChar(src)
		);
}

template <class Archive, class String>
STDMETHODIMP GetSymbol(
					   Archive& src,
					   String& sym,
					   const typename Archive::char_type* sym_chars,
					   const typename Archive::char_type* first_chars_max,
					   const typename Archive::char_type* sym_chars_max
					   )
{
	const typename Archive::char_type* p;

	// 1) get first char:
	typename Archive::int_type ch = SkipWhiteCharsGetChar(src);
	ClearString(sym);
	for (p = sym_chars; p < first_chars_max; ++p)
	{
		if (*p == ch)
			goto lzStep2;
	}
	UngetChar(src, ch);
	return E_INVALID_SYMBOL;
	
lzStep2:
	AppendChar(sym, ch);
	// 2) get others
	for (;;)
	{
		ch = GetChar(src);
		for (p = sym_chars; p < sym_chars_max; ++p)
		{
			if (*p == ch)
				goto lzStep2;
		}
		UngetChar(src, ch);
		return S_OK;
	}
}

template <class Archive, class String>
STDMETHODIMP GetXMLSymbol(Archive& src, String& sym)
{
	static const typename Archive::char_type sym_chars[] =
	{
		'a', 'b', 'c', 'd', 'e', 'f', 'g',
		'h', 'i', 'j', 'k', 'l', 'm', 'n',
		'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'A', 'B', 'C', 'D', 'E', 'F', 'G',
		'H', 'I', 'J', 'K', 'L', 'M', 'N',
		'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'-', '_', ':', '.',
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
	};
	return GetSymbol(
		src, 
		sym, 
		sym_chars, 
		sym_chars + (countof(sym_chars) - 10),
		sym_chars + countof(sym_chars)
		);
}

template <class Archive, class String>
STDMETHODIMP GetCLangSymbol(Archive& src, String& sym)
{
	static const typename Archive::char_type sym_chars[] =
	{
		'a', 'b', 'c', 'd', 'e', 'f', 'g',
		'h', 'i', 'j', 'k', 'l', 'm', 'n',
		'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'A', 'B', 'C', 'D', 'E', 'F', 'G',
		'H', 'I', 'J', 'K', 'L', 'M', 'N',
		'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'_',
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
	};
	return GetSymbol(
		src, 
		sym, 
		sym_chars, 
		sym_chars + (countof(sym_chars) - 10),
		sym_chars + countof(sym_chars)
		);
}

template <class Archive>
STDMETHODIMP_(typename Archive::int_type) GetCLangEscChar(Archive& src)
{
	int i;
	typename Archive::int_type ch = GetChar(src);

	static const char esc_chars[] =
	{
		'\\', 'a',  'b',  'f',	'n',  'r',  't',  '\'', '\"'
	};
	static const char esc_char_values[] =
	{
		'\\', '\a', '\b', '\f',	'\n', '\r', '\t', '\'', '\"'
	};
	for (i = 0; i < countof(esc_chars); ++i)
	{
		if (esc_chars[i] == ch)
			return esc_char_values[i];
	}

	// '\x'
	// '\0', '\1', '\2', '\3', '\4', '\5', '\6', '\7',
	typename Archive::int_type esc;
	if (ch == 'x')
	{
		esc = 0;
		for (;;)
		{
			i = ToHex(ch = GetChar(src));
			if (i < 0)
				break;
			esc = (esc << 4) | i;
			if (esc > 0x100)
				return Archive::endch;
		}
	}
	else if (ch >= '0' && ch <= '7')
	{
		esc = (ch - '0');
		ch = GetChar(src);
		if (ch >= '0' && ch <= '7')
		{
			esc = (esc << 3) | (ch - '0');
			ch = GetChar(src);
			if (ch >= '0' && ch <= '7')
				return (esc << 3) | (ch - '0');
		}
	}
	else
		esc = Archive::endch;

	UngetChar(src, ch);
	return esc;
}

template <class Archive, class String>
STDMETHODIMP GetCLangStringConst(
								 Archive& src,
								 String& strc,
								 typename Archive::int_type chQuote = '\"'
								 )
{
	typename Archive::int_type ch = SkipWhiteCharsGetChar(src);
	ClearString(strc);
	if (ch != chQuote)
	{
		UngetChar(src, ch);
		return E_INVALID_STRING_CONST;
	}

	while ( (ch = GetChar(src)) != chQuote )
	{
		if (ch == '\\')
		{
			ch = GetChar(src);
			switch (ch)
			{
			case '\r': case '\n':
				break;
			default:
				UngetChar(src, ch);
				ch = GetCLangEscChar(src);
				if (ch == Archive::endch)
					return E_INVALID_ESCCHAR;
				AppendChar(strc, ch);
			}
		}
		else
			AppendChar(strc, ch);
	}
	return S_OK;
}

template <class Archive, class IntType>
STDMETHODIMP GetCLangIntConst(	// 0x???, 0??, 123
							  Archive& src,
							  IntType& intVal
							  )
{
	int radix, b;
	IntType val;
	typename Archive::int_type ch = SkipWhiteCharsGetChar(src);
	if (ch >= '1' && ch <= '9')
	{
		radix = 10;
		val = ch - '0';
	}
	else if (ch == '0')
	{
		ch = GetChar(src);
		if (ch == 'x' || ch == 'X')
		{
			val = 0;
			radix = 16;
		}
		else if (ch >= '0' && ch <= '7')
		{
			val = ch - '0';
			radix = 8;
		}
		else
		{
			val = 0;
			goto lzDone;
		}
	}
	else
	{
		UngetChar(src, ch);
		return E_INVALID_INT_CONST;
	}

	for (;;)
	{
		ch = GetChar(src);
		b = ToHex(ch);
		if ( (unsigned)b >= (unsigned)radix )
			break;
		val = val * radix + b;
	}

lzDone:
	UngetChar(src, ch);
	intVal = val;
	return S_OK;
}

// -------------------------------------------------------------------------

template <class _Ty>
class _NullString
{
public:
	typedef _Ty char_type;
	typedef unsigned size_type;
	typedef char_type value_type;

	void append(size_type cch, char_type ch) {}
	void erase() {}
};

// -------------------------------------------------------------------------

template <class _E>
STDMETHODIMP_(void) LineInfo(
							 const _E* sz,
							 const _E** pszLineEnd,
							 const _E** pszNextLine,
							 const _E** pszFirstNonBlankChar,
							 int* pLineFirstBlankCount,
							 int tab = 4
							 )
{
	int count = 0;
	for (;;)
	{
		switch (*sz)
		{
		case ' ':
			++count;
			break;
		case '\t':
			count += tab;
			break;
		default:
			*pszFirstNonBlankChar = sz;
			*pLineFirstBlankCount = count;
			for (;;)
			{
				switch (*sz)
				{
				case 0x0d:
					*pszLineEnd = sz;
					if (*++sz == 0x0a)
						++sz;
					*pszNextLine = sz;
					return;
				case 0x0a:
					*pszLineEnd = sz;
					*pszNextLine = ++sz;
					return;
				case '\\':
					*pszLineEnd = sz; // 只是有遇到eol的可能。
					switch (*++sz)
					{
					case 0x0d:
						if (*++sz == 0x0a)
							++sz;
						*pszNextLine = sz;
					case 0x0a:
						*pszNextLine = ++sz;
						return;
					case '\0':
						*pszLineEnd = *pszNextLine = sz;
						return;
					}
					break;
				case '\0':
					*pszLineEnd = *pszNextLine = sz;
					return;
				}
				++sz;
			}
		}
		++sz;
	}
}

template <class String>
STDMETHODIMP_(void) PrettyPrint(
								String& dest,
								const typename String::char_type* szText,
								int tab = 4
								)
{
	int blank;
	int min_blank = INT_MAX;
	const typename String::char_type* szFirstNonBlankChar;
	const typename String::char_type* szLineEnd;
	const typename String::char_type* szNextLine;
	int n_black_line;
	
	// 取非空白的行的行首空格数的最小值。
	szNextLine = szText;
	while (*szNextLine)
	{
		LineInfo(
			szNextLine,
			&szLineEnd,
			&szNextLine,
			&szFirstNonBlankChar,
			&blank,
			tab);
		if (szLineEnd != szFirstNonBlankChar)
		{
			if (blank < min_blank)
				min_blank = blank;
		}
	}

	// 1) 过滤开始的空白行：
	szNextLine = szText;
	while (*szNextLine)
	{
		LineInfo(
			szNextLine,
			&szLineEnd,
			&szNextLine,
			&szFirstNonBlankChar,
			&blank,
			tab);
		if (szLineEnd != szFirstNonBlankChar)
		{
			dest.append(szFirstNonBlankChar, szLineEnd - szFirstNonBlankChar);
			goto lzNext;
		}
	}
	return;

lzNext:
	// 2) 对文本重新排版，使其变得好看一些：
	n_black_line = (*szLineEnd != '\\' ? 1 : 0);
	while (*szNextLine)
	{
		LineInfo(
			szNextLine,
			&szLineEnd,
			&szNextLine,
			&szFirstNonBlankChar,
			&blank,
			tab);
		if (szLineEnd != szFirstNonBlankChar)
		{
			dest.append(n_black_line, '\n');
			dest.append(blank - min_blank, ' ');
			dest.append(szFirstNonBlankChar, szLineEnd - szFirstNonBlankChar);
			n_black_line = (*szLineEnd != '\\' ? 1 : 0);
		}
		else if (*szLineEnd != '\\')
		{
			++n_black_line;
		}
	}
}

template <class String>
inline
STDMETHODIMP_(void) PrettyPrint(String& strc, int tab = 4)
{
	String dest;
	PrettyPrint(dest, strc.c_str(), tab);
	strc = dest;
}

// -------------------------------------------------------------------------

_KFC_TEXT_SCRIPT_END

#endif /* __KFC_TEXT_SCRIPT_BASE_H__ */
