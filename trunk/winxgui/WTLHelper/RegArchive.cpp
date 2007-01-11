#include "StdAfx.h"
#include ".\regarchive.h"

CRegArchive::CRegArchive(void): m_hKey(NULL)
{
}

CRegArchive::~CRegArchive(void)
{
	if (m_hKey)
		RegCloseKey(m_hKey);
}

bool CRegArchive::Open(HKEY Root, LPCTSTR lpStartName, bool bSave /* = false */)
{
	m_bSave = bSave;
	if (bSave)
	{
		if (RegCreateKeyEx(Root, lpStartName, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE,
			NULL, &m_hKey, NULL) != ERROR_SUCCESS)
			return false;
	}
	else
	{
		if (RegOpenKeyEx(Root, lpStartName, 0, KEY_READ, &m_hKey) != ERROR_SUCCESS)
			return false;
	}
	m_Path.AddTail(m_hKey);
	return true;
}

bool CRegArchive::Close()
{
	while(!m_Path.IsEmpty())
	{
		RegCloseKey(m_Path.RemoveTail());
	}
	m_hKey = NULL;
	return true;
}

bool CRegArchive::StartObject(LPCTSTR lpName)
{
	ATLASSERT(m_hKey);
	HKEY hKey;
	if (m_bSave)
	{
		if (RegCreateKeyEx(m_hKey, lpName, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE,
			NULL, &hKey, NULL) != ERROR_SUCCESS)
			return false;
	}
	else
	{
		LONG Res = RegOpenKeyEx(m_hKey, lpName, 0, KEY_READ, &hKey);
		if (Res != ERROR_SUCCESS)
			return false;
	}
	m_hKey = hKey;
	m_Path.AddTail(m_hKey);
	return true;
}

bool CRegArchive::EndObject()
{
	RegCloseKey(m_Path.RemoveTail());
	m_hKey = m_Path.GetTail();
	return true;
}

bool CRegArchive::LoadVariable(LPCTSTR lpName, bool& Var)
{
	ATLASSERT(m_hKey);
	long tempvar;
	if (!LoadVariable(lpName, tempvar))
		return false;
	else
	{
		Var = tempvar?true:false;
		return true;
	}
}

bool CRegArchive::LoadVariable(LPCTSTR lpName, long& Var)
{
	ATLASSERT(m_hKey);

	DWORD Size = 4;
	if (RegQueryValueEx(m_hKey, lpName, 0, NULL, (LPBYTE)&Var, &Size) != ERROR_SUCCESS)
		return false;
	else
		return true;
}

bool CRegArchive::LoadVariable(LPCTSTR lpName, unsigned long& Var)
{
	return LoadVariable(lpName, (long&)Var);
}

bool CRegArchive::LoadVariable(LPCTSTR lpName, float& Var)
{
	ATLASSERT(m_hKey);

	DWORD Size = 4;
	if (RegQueryValueEx(m_hKey, lpName, 0, NULL, (LPBYTE)&Var, &Size) != ERROR_SUCCESS)
		return false;
	else
		return true;
}

bool CRegArchive::LoadVariable(LPCTSTR lpName, double& Var)
{
	return LoadBinary(lpName, &Var, 8);
}

bool CRegArchive::LoadVariable(LPCTSTR lpName, __int64& Var)
{
	return LoadBinary(lpName, &Var, 8);
}

bool CRegArchive::LoadBinary(LPCTSTR lpName, void* pData, size_t Size)
{
	ATLASSERT(m_hKey);

	DWORD rs = (LONG)Size;
	if (RegQueryValueEx(m_hKey, lpName, 0, NULL, (LPBYTE)pData, &rs) != ERROR_SUCCESS)
		return false;
	else
		return true;
}

#if defined(_WTL_USE_CSTRING) || defined(__ATLSTR_H__) || defined(__AFXSTR_H__)
bool CRegArchive::LoadVariable(LPCTSTR lpName, CString& Var)
{
	ATLASSERT(m_hKey);

	DWORD Size = 0;
	LONG Res = RegQueryValueEx(m_hKey, lpName, 0, NULL, NULL, &Size);
	if (Res == ERROR_MORE_DATA || Res == ERROR_SUCCESS)
	{
		if (RegQueryValueEx(m_hKey, lpName, 0, NULL, (LPBYTE)Var.GetBuffer(Size), &Size) != ERROR_SUCCESS)
		{
			Var.ReleaseBuffer();
			return false;
		}
		else
		{
			Var.ReleaseBuffer(Size - 1);
			return true;
		}
	}
	return false;
}

bool CRegArchive::LoadDefText(CString& Var)
{
	return LoadVariable(NULL, Var);
}

bool CRegArchive::LoadText(LPCTSTR lpName, CString& Var)
{
	return LoadVariable(lpName, Var);
}
#endif

bool CRegArchive::LoadVariable(LPCTSTR lpName, char& Var)
{
	long tvar;
	if (LoadVariable(lpName, tvar))
	{
		Var = (char)tvar;
		return true;
	}
	else
		return false;
}

bool CRegArchive::LoadVariable(LPCTSTR lpName, unsigned char& Var)
{
	unsigned long tvar;
	if (LoadVariable(lpName, tvar))
	{
		Var = (unsigned char)tvar;
		return true;
	}
	else
		return false;
}

bool CRegArchive::LoadVariable(LPCTSTR lpName, int& Var)
{
	long tvar;
	if (LoadVariable(lpName, tvar))
	{
		Var = (int)tvar;
		return true;
	}
	else
		return false;
}

bool CRegArchive::LoadVariable(LPCTSTR lpName, unsigned int& Var)
{
	unsigned long tvar;
	if (LoadVariable(lpName, tvar))
	{
		Var = (unsigned int)tvar;
		return true;
	}
	else
		return false;
}

bool CRegArchive::LoadVariable(LPCTSTR lpName, short& Var)
{
	long tvar;
	if (LoadVariable(lpName, tvar))
	{
		Var = (short)tvar;
		return true;
	}
	else
		return false;
}

bool CRegArchive::LoadVariable(LPCTSTR lpName, unsigned short& Var)
{
	unsigned long tvar;
	if (LoadVariable(lpName, tvar))
	{
		Var = (unsigned short)tvar;
		return true;
	}
	else
		return false;
}


bool CRegArchive::SaveVariable(LPCTSTR lpName, bool Var)
{
	return SaveVariable(lpName, (long)Var);
}

bool CRegArchive::SaveVariable(LPCTSTR lpName, long Var)
{
	ATLASSERT(m_hKey);

	if (RegSetValueEx(m_hKey, lpName, 0, REG_DWORD, (LPBYTE)&Var, 4) != ERROR_SUCCESS)
		return false;
	return true;
}

bool CRegArchive::SaveVariable(LPCTSTR lpName, unsigned long Var)
{
	return SaveVariable(lpName, (long)Var);
}

bool CRegArchive::SaveVariable(LPCTSTR lpName, float Var)
{
	ATLASSERT(m_hKey);

	if (RegSetValueEx(m_hKey, lpName, 0, REG_DWORD, (LPBYTE)&Var, 4) != ERROR_SUCCESS)
		return false;
	return true;
}

bool CRegArchive::SaveVariable(LPCTSTR lpName, double Var)
{
	ATLASSERT(m_hKey);

	LONG Res = RegSetValueEx(m_hKey, lpName, 0, REG_QWORD, (LPBYTE)&Var, 8);
	if (Res != ERROR_SUCCESS)
		return false;
	return true;
}

bool CRegArchive::SaveVariable(LPCTSTR lpName, __int64 Var)
{
	ATLASSERT(m_hKey);

	if (RegSetValueEx(m_hKey, lpName, 0, REG_QWORD, (LPBYTE)&Var, 8) != ERROR_SUCCESS)
		return false;
	return true;
}

#if defined(_WTL_USE_CSTRING) || defined(__ATLSTR_H__) || defined(__AFXSTR_H__)
bool CRegArchive::SaveVariable(LPCTSTR lpName, CString Var)
{
	ATLASSERT(m_hKey);

	if (RegSetValueEx(m_hKey, lpName, 0, REG_SZ, (LPBYTE)(LPCTSTR)Var, (Var.GetLength()+1)*sizeof(TCHAR)) != ERROR_SUCCESS)
		return false;
	return true;
}

bool CRegArchive::SaveDefText(CString Var)
{
	return SaveVariable(NULL, Var);
}

bool CRegArchive::SaveText(LPCTSTR lpName, CString Var)
{
	return SaveVariable(lpName, Var);
}
#endif
bool CRegArchive::SaveBinary(LPCTSTR lpName, void* pData, size_t Size)
{
	ATLASSERT(m_hKey);

	if (RegSetValueEx(m_hKey, lpName, 0, REG_BINARY, (LPBYTE)pData, (DWORD)Size) != ERROR_SUCCESS)
		return false;
	return true;
}

bool CRegArchive::SaveVariable(LPCTSTR lpName, char Var)
{
	long tvar = Var;
	if (SaveVariable(lpName, tvar))
	{
		return true;
	}
	else 
		return false;
}

bool CRegArchive::SaveVariable(LPCTSTR lpName, unsigned char Var)
{
	long tvar = Var;
	if (SaveVariable(lpName, tvar))
	{
		return true;
	}
	else 
		return false;
}

bool CRegArchive::SaveVariable(LPCTSTR lpName, int Var)
{
	long tvar = Var;
	if (SaveVariable(lpName, tvar))
	{
		return true;
	}
	else 
		return false;
}

bool CRegArchive::SaveVariable(LPCTSTR lpName, unsigned int Var)
{
	long tvar = Var;
	if (SaveVariable(lpName, tvar))
	{
		return true;
	}
	else 
		return false;
}

bool CRegArchive::SaveVariable(LPCTSTR lpName, short Var)
{
	long tvar = Var;
	if (SaveVariable(lpName, tvar))
	{
		return true;
	}
	else 
		return false;
}

bool CRegArchive::SaveVariable(LPCTSTR lpName, unsigned short Var)
{
	long tvar = Var;
	if (SaveVariable(lpName, tvar))
	{
		return true;
	}
	else 
		return false;
}