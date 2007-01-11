#pragma	  once

class CStdSaveLoad
{
public:
	template<typename Storage, typename ObjectClass>
	inline static bool SaveVariable(LPCTSTR lpName, Storage& Archive, ObjectClass& object)
	{
		return Archive.SaveVariable(lpName, object);
	}

	template<typename Storage, typename ObjectClass>
	inline static bool LoadVariable(LPCTSTR lpName, Storage& Archive, ObjectClass& object)
	{
		return Archive.LoadVariable(lpName, object);
	}
};

class CObjectSaveLoad
{
public:
	template<typename Storage, typename ObjectClass>
	inline static bool SaveVariable(LPCTSTR lpName, Storage& Archive, ObjectClass& object)
	{
		return object.SaveSettings(Archive, lpName);
	}

	template<typename Storage, typename ObjectClass>
	inline static bool LoadVariable(LPCTSTR lpName, Storage& Archive, ObjectClass& object)
	{
		return object.LoadSettings(Archive, lpName);
	}
};

class CPObjectSaveLoad
{
public:
	template<typename Storage, typename ObjectClass>
	inline static bool SaveVariable(LPCTSTR lpName, Storage& Archive, ObjectClass* pObject)
	{
		return pObject->SaveSettings(Archive, lpName);
	}

	template<typename Storage, typename ObjectClass>
	inline static bool LoadVariable(LPCTSTR lpName, Storage& Archive, ObjectClass*& pObject)
	{
		pObject = new ObjectClass;
		if (!pObject->LoadSettings(Archive, lpName))
		{
			delete pObject;
			pObject = NULL;
			return false;
		}
		return true;
	}
};

template<typename BaseClass, typename SaveLoadClass = CStdSaveLoad>
class CArraySerializer
{
public:
	template<typename Storage, typename ObjectClass>
	static bool SaveVariable(LPCTSTR lpName, Storage& Archive, ObjectClass& object)
	{
		if (!Archive.StartObject(lpName))
			return false;

		size_t Count = BaseClass::GetCount(object);
		for (size_t i = 0; i < Count; i++)
		{
			TCHAR buf[512];
			wsprintf(buf, _T("Item%d"), i);
			if (!SaveLoadClass::SaveVariable(buf, Archive, object[i]))
			{
				Archive.EndObject();
				return false;
			}
		}
		Archive.EndObject();
		return true;
	}

	template<typename Storage, typename ObjectClass>
	static bool LoadVariable(LPCTSTR lpName, Storage& Archive, ObjectClass& object)
	{
		if (!Archive.StartObject(lpName))
			return false;

		int i = 0;
		while(true)
		{
			TCHAR buf[512];
			wsprintf(buf, _T("Item%d"), i);
			typename BaseClass::ElementType Var;
			if (!SaveLoadClass::LoadVariable(buf, Archive, Var))
			{
				break;
			}
			BaseClass::Add(object, Var);
			i++;
		}
		Archive.EndObject();
		return true;
	}
};

template <typename T, typename SaveLoadClass = CStdSaveLoad>
class CAtlArraySerializerCustom : public CArraySerializer<CAtlArraySerializerCustom<T, SaveLoadClass>, SaveLoadClass >
{
public:
	typedef T ElementType;
	inline static size_t GetCount(const CAtlArray<T>& object)
	{
		return object.GetCount();
	}
	inline static void Add(CAtlArray<T>& object, T var)
	{
		object.Add(var);
	}
};

template<typename T>
class CAtlArraySerializer : public CAtlArraySerializerCustom<T, CStdSaveLoad>
{

};

template<typename T>
class CAtlArrayObjectSerializer : public CAtlArraySerializerCustom<T, CObjectSaveLoad> {};

template<typename T>
class CAtlArrayPObjectSerializer : public CAtlArraySerializerCustom<T*, CPObjectSaveLoad> {};


template <typename T, typename SaveLoadClass = CStdSaveLoad>
class CSimpleArraySerializerCustom : public CArraySerializer<CSimpleArraySerializerCustom<T, SaveLoadClass>, SaveLoadClass >
{
public:
	typedef T ElementType;
	template <typename ArrayClass>
	inline static size_t GetCount(const ArrayClass& object)
	{
		return object.GetSize();
	}

	template <typename ArrayClass>
	inline static void Add(ArrayClass& object, T var)
	{
		object.Add(var);
	}
};

template <typename T>
class CSimpleArraySerializer : public CSimpleArraySerializerCustom<T, CStdSaveLoad>{};

template <typename T>
class CSimpleArrayObjectSerializer : public CSimpleArraySerializerCustom<T, CObjectSaveLoad>{};

template <typename T>
class CSimpleArrayPObjectSerializer : public CSimpleArraySerializerCustom<T*, CPObjectSaveLoad>{};

// Use for vector, list, deque
template <typename T, typename SaveLoadClass = CStdSaveLoad>
class CSTLSerializerCustom
{
public:
	template<typename Storage, typename ObjectClass>
	static bool SaveVariable(LPCTSTR lpName, Storage& Archive, ObjectClass& object)
	{
		if (!Archive.StartObject(lpName))
			return false;

		int n = 0;
		for (ObjectClass::iterator i = object.begin(); i != object.end(); i++, n++)
		{
			TCHAR buf[512];
			wsprintf(buf, _T("Item%d"), n);
			if (SaveLoadClass::SaveVariable(buf, Archive, (*i)))
			{
				Archive.EndObject();
				return false;
			}
		}
		Archive.EndObject();
		return true;
	}

	template<typename Storage, typename ObjectClass>
	static bool LoadVariables(LPCTSTR lpName, Storage& Archive, ObjectClass& object)
	{
		if (!Archive.StartObject(lpName))
			return false;

		int i = 0;
		while(true)
		{
			TCHAR buf[512];
			wsprintf(buf, _T("Item%d"), i);
			typename T Var;
			if (!SaveLoadClass::LoadVariable(buf, Archive, Var))
			{
				break;
			}
			object.push_back(Var);
			
			i++;
		}
		Archive.EndObject();
		return true;
	}
};

template <typename T>
class CSTLSerializer : public CSTLSerializerCustom<T, CStdSaveLoad>{};

template <typename T>
class CSTLObjectSerializer : public CSTLSerializerCustom<T, CObjectSaveLoad>{};

template <typename T>
class CSTLPObjectSerializer : public CSTLSerializerCustom<T*, CPObjectSaveLoad>{};
