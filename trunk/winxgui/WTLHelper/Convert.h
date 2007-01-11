#pragma once

#include <comutil.h>

class CBSTRConvert
{
public:
	static _bstr_t ToString(char Value);
	static _bstr_t ToString(unsigned char Value);
	static _bstr_t ToString(short Value);
	static _bstr_t ToString(unsigned short Value);
	static _bstr_t ToString(int Value);
	static _bstr_t ToString(unsigned int Value);
	static _bstr_t ToString(long Value);
	static _bstr_t ToString(unsigned long Value);
	static _bstr_t ToString(__int64 Value);
	static _bstr_t ToString(unsigned __int64 Value);
	static _bstr_t ToString(float Value);
	static _bstr_t ToString(double Value);
	static _bstr_t ToString(bool Value);
	static _bstr_t ToString(const void* pData, size_t Len);
	static _bstr_t ToString(LPCTSTR Value);

	static bool FromString(const _bstr_t Str, char& Value);
	static bool FromString(const _bstr_t Str, unsigned char& Value);
	static bool FromString(const _bstr_t Str, short& Value);
	static bool FromString(const _bstr_t Str, unsigned short& Value);
	static bool FromString(const _bstr_t Str, int& Value);
	static bool FromString(const _bstr_t Str, unsigned int& Value);
	static bool FromString(const _bstr_t Str, long& Value);
	static bool FromString(const _bstr_t Str, unsigned long& Value);
	static bool FromString(const _bstr_t Str, __int64& Value);
	static bool FromString(const _bstr_t Str, unsigned __int64& Value);
	static bool FromString(const _bstr_t Str, float& Value);
	static bool FromString(const _bstr_t Str, double& Value);
	static bool FromString(const _bstr_t Str, bool& Value);
	static bool FromString(const _bstr_t Str, void* pData, size_t MaxLen);
#if defined(_WTL_USE_CSTRING) || defined(__ATLSTR_H__) || defined(__AFXSTR_H__)
	static bool FromString(const _bstr_t Str, CString& Value);
#endif
};

class _variant_ex : public _variant_t
{
};