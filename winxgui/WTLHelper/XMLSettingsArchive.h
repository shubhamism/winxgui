#pragma once
#include "settings.h"
#import <msxml3.dll>
#include "Convert.h"

class CXMLObject
{
protected:
	IXMLDOMDocumentPtr m_pXMLDoc;
	IXMLDOMElementPtr m_pXMLNode;
	CXMLObject(){};
public:
	class CXMLIterator;
	friend CXMLIterator;

	class CXMLIterator
	{
	private:
		CXMLObject* m_pObject;
	public:
		CXMLIterator(IXMLDOMDocumentPtr pDoc, IXMLDOMElementPtr pNode)
		{
			m_pObject = new CXMLObject(pDoc, pNode);
		}
		CXMLIterator(const CXMLIterator& Iterator)
		{
			m_pObject = new CXMLObject(*Iterator.m_pObject);
		}
		~CXMLIterator()
		{
			if (m_pObject)
				delete m_pObject;
		}
		CXMLObject* operator->()
		{
			return m_pObject;
		}
		CXMLObject& operator*()
		{
			return *m_pObject;
		}
		bool operator++(int)
		{
			ATLASSERT(m_pObject->m_pXMLNode != NULL);
			IXMLDOMNodePtr pNode;
			HRESULT hr;
			hr = m_pObject->m_pXMLNode->get_nextSibling(&pNode);
			m_pObject->m_pXMLNode = pNode;
			if (FAILED(hr))
				return false;
			return true;
		}
		operator bool()
		{
			return (m_pObject->m_pXMLNode != NULL);
		}
		CXMLObject* operator&()
		{
			return m_pObject;
		}
	};

	CXMLObject(IXMLDOMDocumentPtr pDoc, IXMLDOMElementPtr pNode) : 
	m_pXMLDoc(pDoc), m_pXMLNode(pNode)
	{
		ATLASSERT(pDoc != NULL);
	}
	bool StartObject(LPCTSTR lpName, bool bCreateNew);
	bool EndObject();
	CXMLIterator GetFirstChild()
	{
		ATLASSERT(m_pXMLDoc != NULL);

		IXMLDOMNodePtr pNode;
		if (m_pXMLNode != NULL)
		{
			m_pXMLNode->get_firstChild(&pNode);
		}
		else
		{
			m_pXMLDoc->get_firstChild(&pNode);
		}
		
		return CXMLIterator(m_pXMLDoc, pNode);
	}
	_bstr_t GetName()
	{
		ATLASSERT(m_pXMLNode != NULL);

		_bstr_t s1;
		m_pXMLNode->get_nodeName(s1.GetAddress());
		return s1;
	}
	template<typename T>
	bool SetAttribute(LPCTSTR lpName, T Value)
	{
		ATLASSERT(m_pXMLDoc != NULL);
		ATLASSERT(m_pXMLNode != NULL);

		_variant_t vt = Value;
		if (FAILED(m_pXMLNode->setAttribute(_bstr_t(lpName), vt)))
			return false;
		return true;
	}

	bool SaveBSTRTag(LPCTSTR lpName, _bstr_t Value)
	{
		ATLASSERT(m_pXMLDoc != NULL);

		IXMLDOMElementPtr pElem;
		HRESULT hr;

		hr = m_pXMLDoc->createElement(_bstr_t(lpName), &pElem);
		ATLASSERT(SUCCEEDED(hr));
		if (FAILED(hr) || pElem == NULL)
			return false;

		hr = pElem->put_text(Value);
		ATLASSERT(SUCCEEDED(hr));
		if (FAILED(hr))
			return false;

		if (m_pXMLNode == NULL)
		{
			hr = m_pXMLNode->appendChild(pElem, (IXMLDOMNode**)&m_pXMLNode);
		}
		else
		{
			hr = m_pXMLNode->appendChild(pElem, NULL);
		}
		ATLASSERT(SUCCEEDED(hr));
		if (FAILED(hr))
			return false;

		return true;
	}
	template<typename T>
	bool SaveTag(LPCTSTR lpName, T Value)
	{
		return SaveBSTRTag(lpName, CBSTRConvert::ToString(Value));
	}
	bool SeBSTRText(_bstr_t Text)
	{
		ATLASSERT(m_pXMLDoc != NULL);
		ATLASSERT(m_pXMLNode != NULL);

		HRESULT hr;
		hr = m_pXMLNode->put_text(Text);
		ATLASSERT(SUCCEEDED(hr));
		if (FAILED(hr))
			return false;

		return true;
	}
	template<typename T>
	bool SetText(T Value)
	{
		return SeBSTRText(CBSTRConvert::ToString(Value));
	}

	template<typename T>
	bool GetAttribute(LPCTSTR lpName, T& Value)
	{
		ATLASSERT(m_pXMLDoc != NULL);
		ATLASSERT(m_pXMLNode != NULL);

		_bstr_t s1;
		_variant_t vt;
		HRESULT hr =  m_pXMLNode->getAttribute(bstr_t(lpName), &vt);
		if (hr != S_OK)
			return false;
		s1 = vt;
		return CBSTRConvert::FromString(s1, Value);
	}

	bool LoadBSTRTag(LPCTSTR lpName, _bstr_t& Value)
	{
		ATLASSERT(m_pXMLNode != NULL);

		IXMLDOMNodePtr pSubElem;
		HRESULT hr;
		hr = m_pXMLNode->selectSingleNode(_bstr_t(lpName), &pSubElem);
		ATLASSERT(SUCCEEDED(hr));
		if (hr != S_OK)
			return false;

		ATLVERIFY(pSubElem->get_text(Value.GetAddress()) == S_OK);
		return true;
	}
	template<typename T>
	bool LoadTag(LPCTSTR lpName, T& Value)
	{
		_bstr_t s1;
		if (!LoadBSTRTag(lpName, s1))
			return false;
		return CBSTRConvert::FromString(s1, Value);
	}
	bool GetBSTRText(_bstr_t& Text)
	{
		return (m_pXMLNode->get_text(Text.GetAddress()) == S_OK);
	}
	template <typename T>
	bool GetText(T& Value)
	{
		_bstr_t s1;
		if (!GetBSTRText(s1))
			return false;
		return CBSTRConvert::FromString(s1, Value);
	}
};

class CXMLStorage : public CXMLObject
{
protected:
	LPTSTR m_pEncoding;
	bool m_bPreserveWhiteSpace;
public:
	CXMLStorage();
	~CXMLStorage();
	
	bool Create(bool bSetHeader = false);
	bool LoadFromFile(LPCTSTR FileName);
	bool LoadFromString(_bstr_t XML);
	bool SaveToFile(LPCTSTR FileName);
	bool SaveToString(_bstr_t& XML);
	void Destroy();

	void SetEncoding(LPCTSTR lpEncoding);
	LPCTSTR GetEncoding();
	void SetPreserveWhiteSpace(bool bNewVal);
	bool GetPreserveWhiteSpace();
};

class CXMLSettingsArchive : public CXMLStorage
{
	bool m_bSave;
	LPTSTR m_pFileName;
public:
	CXMLSettingsArchive();
	~CXMLSettingsArchive(void);
	
	bool Open(LPCTSTR lpStartName, bool bSave = false);
	bool Close();

	template<typename T>
	bool LoadVariable(LPCTSTR lpName, T& Var)
	{
		return GetAttribute(lpName, Var);
	}
	bool LoadBinary(LPCTSTR lpName, void* pData, size_t Size)
	{
		_bstr_t s1;
		if (!LoadBSTRTag(lpName, s1))
		{
			return false;
		}
		return CBSTRConvert::FromString(s1, pData, Size);
	}
	template<typename T>
	bool LoadText(LPCTSTR lpName, T& Var)
	{
		return LoadTag(lpName, Var);
	}
	template<typename T>
	bool LoadDefText(T& Var)
	{
		return GetText(Var);
	}

	template<typename T>
	bool LoadEnum(LPCTSTR lpName, T& Var)
	{
		int Value;
		if (!LoadVariable(lpName, Value))
			return false;
		Var = (T)Value;
		return true;
	}

	template<typename T>
	bool SaveVariable(LPCTSTR lpName, T Var)
	{
		return SetAttribute(lpName, Var);
	}

	bool SaveBinary(LPCTSTR lpName, void* pData, size_t len)
	{
		_bstr_t s1 = CBSTRConvert::ToString(pData, len);
		return SaveBSTRTag(lpName, s1);
	}

	template<typename T>
	bool SaveText(LPCTSTR lpName, T Var)
	{
		return SaveTag(lpName, Var);
	}

	template<typename T>
	bool SaveDefText(T Var)
	{
		return SetText(Var);
	}

	template<typename T>
	bool SaveEnum(LPCTSTR lpName, T Var)
	{
		int Value = (int)Var;
		return SaveVariable(lpName, Value);
	}

	bool StartObject(LPCTSTR lpName)
	{
		return CXMLStorage::StartObject(lpName, m_bSave);
	}
};
