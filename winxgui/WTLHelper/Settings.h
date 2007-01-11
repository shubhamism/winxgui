#pragma once
#include <windows.h>

// if you want to use CString or CAtlString 
// you must include atlstr.h or afxstr.h in stdafx.h

//class CSettingsArchive;

template <typename T>
class CSettings
{
	bool m_bSkipPrefix;
protected:
	static LPCTSTR SkipPrefix(LPCTSTR lpName, LPCTSTR* Prefixes, int Count)
	{
		for (int i = 0; i < Count; i++)
		{
			int len = lstrlen(Prefixes[i]);
			if (!_tcsncmp(lpName, Prefixes[i], len))
			{
				//match prefix, check next character
				if (lpName[len] >= _T('A') && lpName[len] <= _T('Z'))
					return lpName + len;
			}
		}
		return NULL;
	}
public:
	CSettings(bool bSkipPrefix = true):m_bSkipPrefix(bSkipPrefix){};
	~CSettings(){};
	template<typename SettingsStorage>
	bool LoadSettings(SettingsStorage& Archive, LPCTSTR lpObjectName, int MapID = 0)
	{
		T* pThis = static_cast<T*>(this);
		return pThis->ProcessLoadSaveSettings(Archive, lpObjectName, false, MapID);
	}
	template<typename SettingsStorage>
	bool SaveSettings(SettingsStorage& Archive, LPCTSTR lpObjectName, int MapID = 0)
	{
		T* pThis = static_cast<T*>(this);
		return pThis->ProcessLoadSaveSettings(Archive, lpObjectName, true, MapID);
	}
	bool IsSkipPrefix()
	{
		return m_bSkipPrefix;
	}
	void SetSkipPrefix(bool bSkipPrefix)
	{
		m_bSkipPrefix = bSkipPrefix;
	}
	//skip prefix for Microsoft notation
	LPCTSTR SkipPrefix(LPCTSTR lpName)
	{
		ATLASSERT(lpName);

		while(*lpName == _T('&') || *lpName == _T('*'))
			lpName++;

		if (lpName[0] == _T('m') && lpName[1] == _T('_'))
		{
			static LPCTSTR Prefixes[] = {_T("dw"), _T("b"), _T("i"), _T("ui"), _T("sz"), _T("l"), _T("ul"), _T("c"), _T("n"), _T("cl"), _T("e")};
			//member prefix
			lpName += 2;
			if (*lpName == _T('p'))
			{
				if (lpName[1] >= _T('A') && lpName[1] <= _T('Z'))
				{
					return lpName + 1;
				}
				else
				{
					LPCTSTR lpSkip = SkipPrefix(lpName + 1, Prefixes, sizeof(Prefixes) / sizeof(LPCTSTR));
					if (lpSkip)
					{
						return lpSkip;
					}
					else
					{
						return lpName;
					}
				}
			}

			if (*lpName == _T('l') && lpName[1] == _T('p'))
			{
				if (lpName[2] >= _T('A') && lpName[2] <= _T('Z'))
				{
					return lpName + 2;
				}
				else
				{
					LPCTSTR lpSkip = SkipPrefix(lpName + 2, Prefixes, sizeof(Prefixes) / sizeof(LPCTSTR));
					if (lpSkip)
					{
						return lpSkip;
					}
					else
					{
						return lpName;
					}
				}
			}

			LPCTSTR lpSkip = SkipPrefix(lpName, Prefixes, sizeof(Prefixes) / sizeof(LPCTSTR));
			if (lpSkip)
			{
				return lpSkip;
			}
			else
			{
				return lpName;
			}
		}

		if (*lpName == _T('C'))
		{
			//class prefix
			if (lpName[1] >= _T('A') && lpName[1] <= _T('Z'))
				return lpName + 1;
		}
		return lpName;
	}
};

#define BEGIN_SETTINGS_MAP()\
	template<typename SettingsStorage>\
	bool ProcessLoadSaveSettings(SettingsStorage& Archive, LPCTSTR lpObjectName, bool bSave = true, int MapID = 0)\
	{\
		if (lpObjectName && !Archive.StartObject(lpObjectName)) return false;\
		switch(MapID)\
		{\
		case 0:\
		{

#define ALT_SETTINGS_MAP(mapid)\
		}\
		break;\
		case mapid:\
		{

#define SKIP_PREFIX(name)\
	LPCTSTR lpName;\
	if (IsSkipPrefix())\
		{\
		lpName = SkipPrefix(name);\
		}\
		else\
		{\
		lpName = name;\
		}\


#define SETTINGS_NAME_VARIABLE(name, variable)\
	{\
	if (bSave)\
		{\
		bool bRes = Archive.SaveVariable(name, variable);\
		if (!bRes)\
			{\
			ATLTRACE(_T("Cannot save variable %s"), name);\
			return false;\
			}\
		}\
		else\
		{\
		bool bRes= Archive.LoadVariable(name, variable);\
		if (!bRes)\
			{\
			ATLTRACE(_T("Cannot load variable %s"), name);\
			return false;\
			}\
		}\
	}

#define SETTINGS_VARIABLE(variable) \
	{\
		SKIP_PREFIX(_T(#variable))\
		SETTINGS_NAME_VARIABLE(lpName, variable)\
	}

#define SETTINGS_NAME_VARIABLE_RO(name, variable)\
	{\
	if (!bSave)\
		{\
		bool bRes = Archive.LoadVariable(lpName, variable);\
		if (!bRes)\
			{\
			ATLTRACE(_T("Cannot load variable %s"), lpName);\
			return false;\
			}\
		}\
	}

#define SETTINGS_VARIABLE_RO(variable)\
{\
	SKIP_PREFIX(_T(#variable))\
	SETTINGS_NAME_VARIABLE_RO(lpName, variable)\
}

#define SETTINGS_NAME_VARIABLE_OPT(name, variable)\
	{\
	if (bSave)\
		{\
		bool bRes = Archive.SaveVariable(name, variable);\
		if (!bRes)\
			{\
			ATLTRACE(_T("Cannot save variable %s"), name);\
			return false;\
			}\
		}\
		else\
		{\
		Archive.LoadVariable(name, variable);\
		}\
	}

#define SETTINGS_VARIABLE_OPT(variable)\
	{\
		SKIP_PREFIX(_T(#variable))\
		SETTINGS_NAME_VARIABLE_OPT(lpName, variable)\
	}

#define SETTINGS_NAME_VARIABLE_OPT_RO(name, variable)\
	{\
	if (!bSave)\
		{\
		Archive.LoadVariable(name, variable);\
		}\
	}

#define SETTINGS_VARIABLE_OPT_RO(variable)\
	{\
	SKIP_PREFIX(_T(#variable))\
	SETTINGS_NAME_VARIABLE_OPT_RO(lpName, variable)\
	}

#define SETTINGS_NAME_ENUM(name, variable)\
	{\
	if (bSave)\
		{\
		bool bRes = Archive.SaveEnum(name, variable);\
		if (!bRes)\
			{\
			ATLTRACE(_T("Cannot save variable %s"), name);\
			return false;\
			}\
		}\
		else\
		{\
		bool bRes= Archive.LoadEnum(name, variable);\
		if (!bRes)\
			{\
			ATLTRACE(_T("Cannot load variable %s"), name);\
			return false;\
			}\
		}\
	}

#define SETTINGS_ENUM(variable) \
	{\
	SKIP_PREFIX(_T(#variable))\
	SETTINGS_NAME_ENUM(lpName, variable)\
	}

#define SETTINGS_NAME_ENUM_RO(name, variable)\
	{\
	if (!bSave)\
		{\
		bool bRes = Archive.LoadEnum(lpName, variable);\
		if (!bRes)\
			{\
			ATLTRACE(_T("Cannot load variable %s"), lpName);\
			return false;\
			}\
		}\
	}

#define SETTINGS_ENUM_RO(variable)\
{\
	SKIP_PREFIX(_T(#variable))\
	SETTINGS_NAME_ENUM_RO(lpName, variable)\
}

#define SETTINGS_NAME_ENUM_OPT(name, variable)\
	{\
	if (bSave)\
		{\
		bool bRes = Archive.SaveEnum(name, variable);\
		if (!bRes)\
			{\
			ATLTRACE(_T("Cannot save variable %s"), name);\
			return false;\
			}\
		}\
		else\
		{\
		Archive.LoadEnum(name, variable);\
		}\
	}

#define SETTINGS_ENUM_OPT(variable)\
	{\
	SKIP_PREFIX(_T(#variable))\
	SETTINGS_NAME_ENUM_OPT(lpName, variable)\
	}

#define SETTINGS_NAME_ENUM_OPT_RO(name, variable)\
	{\
	if (!bSave)\
		{\
		Archive.LoadEnum(name, variable);\
		}\
	}

#define SETTINGS_ENUM_OPT_RO(variable)\
	{\
	SKIP_PREFIX(_T(#variable))\
	SETTINGS_NAME_ENUM_OPT_RO(lpName, variable)\
	}

#define SETTINGS_NAME_BINARY(name, variable, sizeofvariable)\
	{\
	if (bSave)\
		{\
		bool bRes = Archive.SaveBinary(name, variable, sizeofvariable);\
		if (!bRes)\
			{\
			ATLTRACE(_T("Cannot save binary %s"), name);\
			return false;\
			}\
		}\
		else\
		{\
		bool bRes = Archive.LoadBinary(name, variable, sizeofvariable);\
		if (!bRes)\
			{\
			ATLTRACE(_T("Cannot load binary %s"), name);\
			return false;\
			}\
		}\
	}

#define SKIP_BINARY_PREFIX(name)\
	LPCTSTR lpName = name;\
	if (*lpName == _T('&') || *lpName == _T('*'))\
		{\
		lpName++;\
		}\
		if (IsSkipPrefix())\
		{\
		lpName = SkipPrefix(lpName);\
		}\

#define SETTINGS_BINARY(variable, sizeofvariable)\
	{\
		SKIP_BINARY_PREFIX(_T(#variable))\
		SETTINGS_NAME_BINARY(lpName, variable, sizeofvariable)\
	}

#define SETTINGS_NAME_BINARY_RO(name, variable, sizeofvariable)\
	{\
	if (!bSave)\
		{\
		bool bRes = Archive.LoadBinary(name, variable, sizeofvariable);\
		if (!bRes)\
			{\
			ATLTRACE(_T("Cannot load binary %s"), name);\
			return false;\
			}\
		}\
	}

#define SETTINGS_BINARY_RO(variable, sizeofvariable)\
	{\
		SKIP_BINARY_PREFIX(_T(#variable))\
		SETTINGS_NAME_BINARY_RO(lpName, variable, sizeofvariable)\
	}

#define SETTINGS_NAME_BINARY_OPT(name, variable, sizeofvariable)\
	{\
	if (bSave)\
		{\
		bool bRes = Archive.SaveBinary(name, variable, sizeofvariable);\
		if (!bRes)\
			{\
			ATLTRACE(_T("Cannot save binary %s"), name);\
			return false;\
			}\
		}\
		else\
		{\
		Archive.LoadBinary(name, variable, sizeofvariable);\
		}\
	}

#define SETTINGS_BINARY_OPT(variable, sizeofvariable)\
	{\
		SKIP_BINARY_PREFIX(_T(#variable))\
		SETTINGS_NAME_BINARY_OPT(lpName, variable, sizeofvariable)\
	}

#define SETTINGS_NAME_BINARY_OPT_RO(name, variable, sizeofvariable, defvalue)\
	{\
	if (!bSave)\
		{\
		Archive.LoadBinary(name, variable, sizeofvariable)\
		}\
	}

#define SETTINGS_BINARY_OPT_RO(variable, sizeofvariable)\
	{\
		SKIP_BINARY_PREFIX(_T(#variable))\
		SETTINGS_NAME_BINARY_OPT_RO(lpName, variable, sizeofvariable)\
	}

#define SETTINGS_DEFTEXT(variable)\
	{\
		if (bSave)\
		{\
			bool bRes = Archive.SaveDefText(variable);\
			if (!bRes)\
			{\
				ATLTRACE(_T("Cannot save deftext "));\
				return false;\
			}\
		}\
		else\
		{\
			bool bRes = Archive.LoadDefText(variable);\
			if (!bRes)\
			{\
			ATLTRACE(_T("Cannot load deftext "));\
			return false;\
			}\
		}\
	}

#define SETTINGS_DEFTEXT_RO(variable)\
	{\
		if (!bSave)\
		{\
		bool bRes = Archive.LoadDefText(variable);\
		if (!bRes)\
			{\
			ATLTRACE(_T("Cannot load deftext "));\
			return false;\
			}\
		}\
	}

#define SETTINGS_DEFTEXT_OPT(variable)\
	{\
		if (bSave)\
		{\
			if (!variable.IsEmpty())\
			{\
				bool bRes = Archive.SaveDefText(variable);\
				if (!bRes)\
				{\
					ATLTRACE(_T("Cannot save deftext "));\
					return false;\
				}\
			}\
		}\
		else\
		{\
			Archive.LoadDefText(variable);\
		}\
	}

#define SETTINGS_DEFTEXT_OPT_RO(variable)\
	{\
	if (!bSave)\
		{\
		Archive.LoadDefText(variable);\
		}\
	}

#define SETTINGS_NAME_TEXT(name, variable)\
	{\
	if (bSave)\
		{\
		bool bRes = Archive.SaveText(name, variable);\
		if (!bRes)\
			{\
			ATLTRACE(_T("Cannot save text %s"), name);\
			return false;\
			}\
		}\
		else\
		{\
		bool bRes = Archive.LoadText(name, variable);\
		if (!bRes)\
			{\
			ATLTRACE(_T("Cannot load text %s"), name);\
			return false;\
			}\
		}\
	}

#define SETTINGS_TEXT(variable)\
	{\
	SKIP_PREFIX(_T(#variable))\
	SETTINGS_NAME_TEXT(lpName, variable)\
	}

#define SETTINGS_NAME_TEXT_OPT(name, variable)\
	{\
		if (bSave)\
		{\
			if (!(variable).IsEmpty())\
			{\
				bool bRes = Archive.SaveText(name, variable);\
				if (!bRes)\
				{\
					ATLTRACE(_T("Cannot save text %s"), name);\
					return false;\
				}\
			}\
		}\
		else\
		{\
			Archive.LoadText(name, variable);\
		}\
	}

#define SETTINGS_TEXT_OPT(variable)\
	{\
	SKIP_PREFIX(_T(#variable))\
	SETTINGS_NAME_TEXT_OPT(lpName, variable)\
	}

#define SETTINGS_NAME_TEXT_RO(name, variable)\
	{\
	if (!bSave)\
		{\
		bool bRes = Archive.LoadText(name, variable);\
		if (!bRes)\
			{\
			ATLTRACE(_T("Cannot load text %s"), name);\
			return false;\
			}\
		}\
	}

#define SETTINGS_TEXT_RO(variable)\
	{\
	SKIP_PREFIX(_T(#variable))\
	SETTINGS_NAME_TEXT_RO(lpName, variable)\
	}

#define SETTINGS_NAME_TEXT_OPT_RO(name, variable)\
	{\
	if (!bSave)\
		{\
		Archive.LoadText(name, variable);\
		}\
	}

#define SETTINGS_TEXT_OPT_RO(variable)\
	{\
	SKIP_PREFIX(_T(#variable))\
	SETTINGS_NAME_TEXT_OPT_RO(lpName, variable)\
	}

#define SETTINGS_NAME_CHILD(name, variable)\
	{\
		if (bSave)\
		{\
			if (!(variable).SaveSettings(Archive, name)) return false;\
		}\
		else\
		{\
			if (!(variable).LoadSettings(Archive, name)) return false;\
		}\
	}

#define SETTINGS_CHILD(variable)\
	{\
	SKIP_PREFIX(_T(#variable))\
	SETTINGS_NAME_CHILD(lpName, variable)\
	}
// Suffix USE_PARENT means that there is no sub name for child
// Variables will be got from parent storage

#define SETTINGS_CHILD_USE_PARENT(variable)\
	{\
	SETTINGS_NAME_CHILD(NULL, variable)\
	}

#define SETTINGS_NAME_CHILD_RO(name, variable)\
	{\
		if (!bSave)\
		{\
		if (!(variable).LoadSettings(Archive, name)) return false; \
		}\
	}

#define SETTINGS_CHILD_RO(variable)\
	{\
		SKIP_PREFIX(_T(#variable))\
		SETTINGS_NAME_CHILD_RO(lpName, variable)\
	}

#define SETTINGS_CHILD_RO_USE_PARENT(variable)\
	{\
	SETTINGS_NAME_CHILD_RO(NULL, variable)\
	}


#define SETTINGS_NAME_CHILD_OPT(name, variable)\
	{\
		if (bSave)\
		{\
			if (!(variable).SaveSettings(Archive, name)) return false;\
		}\
		else\
		{\
			(variable).LoadSettings(Archive, name);\
		}\
	}

#define SETTINGS_CHILD_OPT(variable)\
	{\
		SKIP_PREFIX(_T(#variable))\
		SETTINGS_NAME_CHILD_OPT(lpName, variable)\
	}

#define SETTINGS_CHILD_OPT_USE_PARENT(variable)\
	{\
	SETTINGS_NAME_CHILD_OPT(NULL, variable)\
	}

#define SETTINGS_NAME_CHILD_OPT_RO(name, variable)\
	{\
	if (!bSave)\
		{\
		(variable).LoadSettings(Archive, name);\
		}\
	}

#define SETTINGS_CHILD_OPT_RO(variable)\
	{\
	SKIP_PREFIX(_T(#variable))\
	SETTINGS_NAME_CHILD_OPT_RO(lpName, variable)\
	}

#define SETTINGS_CHILD_OPT_RO_USE_PARENT(variable)\
	{\
	SETTINGS_NAME_CHILD_OPT_RO(NULL, variable)\
	}

#define SETTINGS_NAME_ALT_CHILD(name, variable, mapid)\
	{\
		if (bSave)\
		{\
			if (!(variable).SaveSettings(Archive, name, mapid)) return false;\
		}\
		else\
		{\
			if (!(variable).LoadSettings(Archive, name, mapid)) return false;\
		}\
	}

#define SETTINGS_ALT_CHILD(variable, mapid)\
	{\
		SKIP_PREFIX(_T(#variable))\
		SETTINGS_NAME_ALT_CHILD(lpName, variable, mapid)\
	}

#define SETTINGS_ALT_CHILD_USE_PARENT(variable, mapid)\
	{\
	SETTINGS_NAME_ALT_CHILD(NULL, variable, mapid)\
	}

#define SETTINGS_NAME_ALT_CHILD_RO(name, variable, mapid)\
	{\
		if (!bSave)\
		{\
		if (!(variable).Load(Archive, name, mapid)) return false;\
		}\
	}

#define SETTINGS_ALT_CHILD_RO(variable, mapid) \
	{\
		SKIP_PREFIX(_T(#variable))\
		SETTINGS_NAME_ALT_CHILD_RO(lpName, variable, mapid)\
	}

#define SETTINGS_ALT_CHILD_RO_USE_PARENT(variable, mapid) \
	{\
	SETTINGS_NAME_ALT_CHILD_RO(NULL, variable, mapid)\
	}

#define SETTINGS_NAME_ALT_CHILD_OPT(name, variable, mapid)\
	{\
	if (bSave)\
		{\
		if (!(variable).SaveSettings(Archive, name, mapid)) return false;\
		}\
		else\
		{\
		(variable).LoadSettings(Archive, name, mapid);\
		}\
	}

#define SETTINGS_ALT_CHILD_OPT(variable, mapid)\
	{\
	SKIP_PREFIX(_T(#variable))\
	SETTINGS_NAME_ALT_CHILD_OPT(lpName, variable, mapid)\
	}

#define SETTINGS_ALT_CHILD_OPT_USE_PARENT(variable, mapid)\
	{\
	SETTINGS_NAME_ALT_CHILD_OPT(NULL, variable, mapid)\
	}

#define SETTINGS_NAME_ALT_CHILD_OPT_RO(name, variable, mapid)\
	{\
	if (!bSave)\
		{\
		(variable).LoadSettings(Archive, name, mapid);\
		}\
	}

#define SETTINGS_ALT_CHILD_OPT_RO(variable, mapid)\
	{\
	SKIP_PREFIX(_T(#variable))\
	SETTINGS_NAME_ALT_CHILD_OPT_RO(lpName, variable, mapid)\
	}

#define SETTINGS_ALT_CHILD_OPT_RO_USE_PARENT(variable, mapid)\
	{\
	SETTINGS_NAME_ALT_CHILD_OPT_RO(NULL, variable, mapid)\
	}

#define SETTINGS_OBJECT_NAME(array, name, Serializer)\
	if (bSave)\
	{\
	if (!Serializer::SaveVariable(name, Archive, array)) return false;\
	}\
	else\
	{\
	if (!Serializer::LoadVariable(name, Archive, array)) return false;\
	}

#define SETTINGS_OBJECT(array, Serializer)\
{\
	SKIP_PREFIX(_T(#array))\
	SETTINGS_OBJECT_NAME(array, lpName, Serializer)\
}

#define SETTINGS_OBJECT_NAME_OPT(array, name, Serializer)\
	if (bSave)\
{\
	if (!Serializer::SaveVariable(name, Archive, array)) return false;\
}\
	else\
{\
	Serializer::LoadVariable(name, Archive, array);\
}

#define SETTINGS_OBJECT_OPT(array, Serializer)\
{\
	SKIP_PREFIX(_T(#array))\
	SETTINGS_OBJECT_NAME_OPT(array, lpName, Serializer)\
}

// Read only

#define SETTINGS_OBJECT_NAME_RO(array, name, Serializer)\
	if (!bSave)\
{\
	if (!Serializer::LoadVariable(name, Archive, array)) return false;\
}

#define SETTINGS_OBJECT_RO(array, Serializer)\
{\
	SKIP_PREFIX(_T(#array))\
	SETTINGS_OBJECT_NAME_RO(array, lpName, Serializer)\
}

#define SETTINGS_OBJECT_NAME_OPT_RO(array, name, Serializer)\
	if (!bSave)\
{\
	Serializer::LoadVariable(name, Archive, array);\
}

#define SETTINGS_OBJECT_OPT_RO(array, Serializer)\
{\
	SKIP_PREFIX(_T(#array))\
	SETTINGS_OBJECT_NAME_OPT_RO(array, lpName, Serializer)\
}

#define END_SETTINGS_MAP() \
		}\
		break;\
		default:\
			ATLTRACE( _T("Invalid settings map ID \n")); \
			ATLASSERT(FALSE); \
			break; \
		}\
		if (lpObjectName)\
			Archive.EndObject();\
		return true;\
	}

