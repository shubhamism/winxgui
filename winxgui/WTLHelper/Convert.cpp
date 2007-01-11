#include "StdAfx.h"
#include ".\convert.h"

const char Base64FillChar = '=';
const char Base64Alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const char Base64Dec[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 62, 0, 0, 0, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0, 0, 0, 0, 0, 0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 0, 0, 0, 0, 0};

size_t Base64Encode(char* data, size_t len, char* dest, size_t maxlen)
{
	size_t  i;
	char    c;
	size_t nCount = 0;

	for (i = 0; i < len; ++i)
	{
		c = (data[i] >> 2) & 0x3f;
		if (nCount >= maxlen)
		{
			return -1;
		}
		dest[nCount++] = Base64Alphabet[c];


		c = (data[i] << 4) & 0x3f;
		if (++i < len)
			c |= (data[i] >> 4) & 0x0f;

		if (nCount >= maxlen)
		{
			return -1;
		}
		dest[nCount++] = Base64Alphabet[c];

		if (i < len)
		{
			c = (data[i] << 2) & 0x3f;
			if (++i < len)
				c |= (data[i] >> 6) & 0x03;

			if (nCount >= maxlen)
			{
				return -1;
			}
			dest[nCount++] = Base64Alphabet[c];
		}
		else
		{
			++i;
			if (nCount >= maxlen)
			{
				return -1;
			}
			dest[nCount++] = Base64FillChar;
		}

		if (i < len)
		{
			c = data[i] & 0x3f;
			if (nCount >= maxlen)
			{
				return -1;
			}
			dest[nCount++] = Base64Alphabet[c];
		}
		else
		{
			if (nCount >= maxlen)
			{
				return -1;
			}
			dest[nCount++] = Base64FillChar;
		}
	}
	if (nCount >= maxlen)
	{
		return -1;
	}
	dest[nCount] = 0;
	return nCount;
}

int Base64Decode(char* data, size_t len, char* res, int MaxLen)
{
	size_t i;
	char c;
	char c1;
	int nCount = 0;

	for (i = 0; i < len; ++i)
	{
		c = Base64Dec[data[i]]; 
		++i;
		c1 = Base64Dec[data[i]];
		c = (c << 2) | ((c1 >> 4) & 0x3);
		if (nCount >= MaxLen)
		{
			return -1;
		}
		res[nCount++] = c;

		if (++i < len)
		{
			c = data[i];
			if (Base64FillChar == c)
				break;

			c = Base64Dec[data[i]];
			c1 = ((c1 << 4) & 0xf0) | ((c >> 2) & 0xf);
			if (nCount >= MaxLen)
			{
				return -1;
			}
			res[nCount++] = c1;
		}

		if (++i < len)
		{
			c1 = data[i];
			if (Base64FillChar == c1)
				break;

			c1 = Base64Dec[data[i]];
			c = ((c << 6) & 0xc0) | c1;
			if (nCount >= MaxLen)
			{
				return -1;
			}
			res[nCount++] = c;
		}
	}

	return nCount;
}

_bstr_t CBSTRConvert::ToString(long Value)
{
	wchar_t buf[64];
#ifdef _SECURE_ATL
	_ltow_s(Value, buf, 10);
#else
	_ltow(Value, buf, 10);
#endif
	return _bstr_t(buf);
}

_bstr_t CBSTRConvert::ToString(unsigned long Value)
{
	wchar_t buf[64];
#ifdef _SECURE_ATL
	_ultow_s(Value, buf, 10);
#else
	_ultow(Value, buf, 10);
#endif
	return _bstr_t(buf);
}

_bstr_t CBSTRConvert::ToString(__int64 Value)
{
	wchar_t buf[128];
#ifdef _SECURE_ATL
	_i64tow_s(Value, buf, 128, 10);
#else
	_i64tow(Value, buf, 10);
#endif
	return _bstr_t(buf);
}

_bstr_t CBSTRConvert::ToString(unsigned __int64 Value)
{
	wchar_t buf[128];
#ifdef _SECURE_ATL
	_ui64tow_s(Value, buf, 128, 10);
#else
	_ui64tow(Value, buf, 10);
#endif
	
	return _bstr_t(buf);
}

_bstr_t CBSTRConvert::ToString(char Value)
{
	return ToString((long)Value);
}

_bstr_t CBSTRConvert::ToString(unsigned char Value)
{
	return ToString((unsigned long)Value);
}

_bstr_t CBSTRConvert::ToString(short Value)
{
	return ToString((long)Value);
}

_bstr_t CBSTRConvert::ToString(unsigned short Value)
{
	return ToString((unsigned long)Value);
}

_bstr_t CBSTRConvert::ToString(int Value)
{
	return ToString((long)Value);
}

_bstr_t CBSTRConvert::ToString(unsigned int Value)
{
	return ToString((unsigned long)Value);
}

_bstr_t CBSTRConvert::ToString(double Value)
{
	char buf[512];
#ifdef _SECURE_ATL
	_gcvt_s(buf, Value, 12);
#else
	_gcvt(Value, 12, buf);
#endif
	return _bstr_t(buf);
}

_bstr_t CBSTRConvert::ToString(float Value)
{
	return ToString((double)Value);
}

_bstr_t CBSTRConvert::ToString(bool Value)
{
	if (Value)
		return _bstr_t(L"true");
	else
		return _bstr_t(L"false");
}

_bstr_t CBSTRConvert::ToString(const void* pData, size_t Len)
{
	size_t bufsize = ((Len+3)*4)/3 + 2;
	char* pBuf = new char[bufsize];
	Base64Encode((char*)pData, Len, pBuf, bufsize);
	_bstr_t Res(pBuf);
	delete pBuf;
	return Res;
}

_bstr_t CBSTRConvert::ToString(LPCTSTR Value)
{
	return _bstr_t(Value);
}

bool CBSTRConvert::FromString(const _bstr_t Str, long& Value)
{
	wchar_t* pEnd;
	Value = wcstol(Str, &pEnd, 10);
	if (!*pEnd)
		return true;
	else
		return false;
}

bool CBSTRConvert::FromString(const _bstr_t Str, unsigned long& Value)
{
	wchar_t* pEnd;
	Value = wcstoul(Str, &pEnd, 10);
	if (!*pEnd)
		return true;
	else
		return false;
}

bool CBSTRConvert::FromString(const _bstr_t Str, __int64& Value)
{
	wchar_t* pEnd;
	Value = _wcstoi64(Str, &pEnd, 10);
	if (!*pEnd)
		return true;
	else
		return false;
}

bool CBSTRConvert::FromString(const _bstr_t Str, unsigned __int64& Value)
{
	wchar_t* pEnd;
	Value = _wcstoui64(Str, &pEnd, 10);
	if (!*pEnd)
		return true;
	else
		return false;
}

bool CBSTRConvert::FromString(const _bstr_t Str, char& Value)
{
	long Val;
	if (!FromString(Str, Val))
		return false;
	Value = (char)Val;
	return true;
}

bool CBSTRConvert::FromString(const _bstr_t Str, unsigned char& Value)
{
	unsigned long Val;
	if (!FromString(Str, Val))
		return false;
	Value = (unsigned char)Val;
	return true;
}

bool CBSTRConvert::FromString(const _bstr_t Str, short& Value)
{
	long Val;
	if (!FromString(Str, Val))
		return false;
	Value = (short)Val;
	return true;
}

bool CBSTRConvert::FromString(const _bstr_t Str, unsigned short& Value)
{
	unsigned long Val;
	if (!FromString(Str, Val))
		return false;
	Value = (unsigned short)Val;
	return true;
}

bool CBSTRConvert::FromString(const _bstr_t Str, int& Value)
{
	long Val;
	if (!FromString(Str, Val))
		return false;
	Value = (int)Val;
	return true;
}

bool CBSTRConvert::FromString(const _bstr_t Str, unsigned int& Value)
{
	unsigned long Val;
	if (!FromString(Str, Val))
		return false;
	Value = (unsigned int)Val;
	return true;
}

bool CBSTRConvert::FromString(const _bstr_t Str, double& Value)
{
	wchar_t* pEnd;
	Value = wcstod(Str, &pEnd);
	if (!*pEnd)
		return true;
	else
		return false;
}

bool CBSTRConvert::FromString(const _bstr_t Str, float& Value)
{
	double Val;
	if (!FromString(Str, Val))
		return false;
	Value = (float)Val;
	return true;
}

bool CBSTRConvert::FromString(const _bstr_t Str, bool& Value)
{
	if (!wcscmp(Str, L"true"))
	{
		Value = true;
		return true;
	}
	if (!wcscmp(Str, L"false"))
	{
		Value = false;
		return true;
	}
	return false;
}

bool CBSTRConvert::FromString(const _bstr_t Str, void* pData, size_t MaxLen)
{
	Base64Decode(Str, Str.length(), (char*)pData, (int)MaxLen);
	return true;
}

#if defined(_WTL_USE_CSTRING) || defined(__ATLSTR_H__) || defined(__AFXSTR_H__)
bool CBSTRConvert::FromString(const _bstr_t Str, CString& Value)
{
#ifdef _UNICODE
	Value = (wchar_t*)Str;
#else
	Value = (char*)Str;
#endif
	return true;
}
#endif