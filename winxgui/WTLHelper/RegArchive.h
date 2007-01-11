#pragma once
#include "settings.h"
#include <atlcoll.h>

class CRegArchive //: public CBaseSettingsArchive<CRegArchive>
{
	bool m_bSave;
	HKEY m_hKey;
	CAtlList<HKEY> m_Path;
public:
	CRegArchive(void);
	~CRegArchive(void);

	bool Open(HKEY Root, LPCTSTR lpStartName, bool bSave = false);
	bool Close();
	bool StartObject(LPCTSTR lpName);
	bool EndObject();

	bool LoadVariable(LPCTSTR lpName, bool& Var);
	bool LoadVariable(LPCTSTR lpName, long& Var);
	bool LoadVariable(LPCTSTR lpName, unsigned long& Var);
	bool LoadVariable(LPCTSTR lpName, float& Var);
	bool LoadVariable(LPCTSTR lpName, double& Var);
	bool LoadVariable(LPCTSTR lpName, __int64& Var);
#if defined(_WTL_USE_CSTRING) || defined(__ATLSTR_H__) || defined(__AFXSTR_H__)
	bool LoadVariable(LPCTSTR lpName, CString& Var);
	bool LoadDefText(CString& Var);
	bool LoadText(LPCTSTR lpName, CString& Var);
#endif
	bool LoadBinary(LPCTSTR lpName, void* pData, size_t Size);
	template <typename T>
	bool LoadEnum(LPCTSTR lpName, T& Var)
	{
		int Value;
		if (!LoadVariable(lpName, Value))
			return false;
		Var = (T)Value;
		return true;
	}

	bool LoadVariable(LPCTSTR lpName, int& Var);
	bool LoadVariable(LPCTSTR lpName, short& Var);
	bool LoadVariable(LPCTSTR lpName, char& Var);
	bool LoadVariable(LPCTSTR lpName, unsigned int& Var);
	bool LoadVariable(LPCTSTR lpName, unsigned short& Var);
	bool LoadVariable(LPCTSTR lpName, unsigned char& Var);

	bool SaveVariable(LPCTSTR lpName, bool Var);
	bool SaveVariable(LPCTSTR lpName, long Var);
	bool SaveVariable(LPCTSTR lpName, unsigned long Var);
	bool SaveVariable(LPCTSTR lpName, float Var);
	bool SaveVariable(LPCTSTR lpName, double Var);
	bool SaveVariable(LPCTSTR lpName, __int64 Var);
#if defined(_WTL_USE_CSTRING) || defined(__ATLSTR_H__) || defined(__AFXSTR_H__)
	bool SaveVariable(LPCTSTR lpName, CString Var);
	bool SaveDefText(CString Var);
	bool SaveText(LPCTSTR lpName, CString Var);
#endif
	bool SaveBinary(LPCTSTR lpName, void* pData, size_t Size);
	template<typename T>
	bool SaveEnum(LPCTSTR lpName, T Var)
	{
		int Value = (int)Var;
		return SaveVariable(lpName, Value);
	}

	bool SaveVariable(LPCTSTR lpName, int Var);
	bool SaveVariable(LPCTSTR lpName, short Var);
	bool SaveVariable(LPCTSTR lpName, char Var);
	bool SaveVariable(LPCTSTR lpName, unsigned int Var);
	bool SaveVariable(LPCTSTR lpName, unsigned short Var);
	bool SaveVariable(LPCTSTR lpName, unsigned char Var);
};
