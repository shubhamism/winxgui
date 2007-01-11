#include "StdAfx.h"
#include ".\xmlsettingsarchive.h"
#include <atlbase.h>
#include <comutil.h>
#include <memory.h>

bool CXMLObject::StartObject(LPCTSTR lpName, bool bCreateNew)
{
	ATLASSERT(m_pXMLDoc != NULL);

	HRESULT hr;

	if (bCreateNew)
	{
		IXMLDOMElementPtr pNewElem = NULL;
		hr = m_pXMLDoc->createElement(_bstr_t(lpName), &pNewElem);
		ATLASSERT(SUCCEEDED(hr));
		if (FAILED(hr))
			return false;
		if (m_pXMLNode != NULL)
		{
			hr = m_pXMLNode->appendChild(pNewElem, NULL);
		}
		else
		{
			hr = m_pXMLDoc->appendChild(pNewElem, NULL);
		}

		ATLASSERT(SUCCEEDED(hr));
		if (FAILED(hr))
		{
			return false;
		}
		m_pXMLNode = pNewElem;
		return true;
	}
	else
	{
		IXMLDOMNodePtr pNewNode;
		_bstr_t XPath = lpName;
		if (m_pXMLNode != NULL)
		{
			hr = m_pXMLNode->selectSingleNode(XPath, &pNewNode);
		}
		else
		{
			hr = m_pXMLDoc->selectSingleNode(XPath, &pNewNode);
		}
		ATLASSERT(SUCCEEDED(hr));
		if (FAILED(hr) || pNewNode == NULL)
		{
			return false;
		}
		m_pXMLNode = pNewNode;

		return true;
	}
}

bool CXMLObject::EndObject()
{
	ATLASSERT(m_pXMLNode != NULL);

	HRESULT hr;
	IXMLDOMNodePtr pParent;
	hr = m_pXMLNode->get_parentNode(&pParent);
	ATLASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
	{
		return false;
	}
	m_pXMLNode = pParent;

	return true;
}

//////////////////////////////////////////////////////////////////////////

CXMLStorage::CXMLStorage() : m_pEncoding(NULL), m_bPreserveWhiteSpace(false)
{
}

CXMLStorage::~CXMLStorage()
{
	Destroy();
}

bool CXMLStorage::Create(bool bSetHeader /* = false */)
{
	ATLASSERT(m_pXMLDoc == NULL);
	HRESULT hr;

	hr = CoCreateInstance(CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER, 
		IID_IXMLDOMDocument, (void**)&m_pXMLDoc);
	if (FAILED(hr))
		return false;
	if (bSetHeader)
	{
		bstr_t Title(L"version=\"1.0\"");
		IXMLDOMProcessingInstructionPtr pProcInstr;
		//select encoding
		if (m_pEncoding)
		{
			Title += L" encoding=\"";
			Title += m_pEncoding;
			Title += L"\"";
		}
		hr = m_pXMLDoc->createProcessingInstruction(_bstr_t(L"xml"), Title, &pProcInstr);
		hr = m_pXMLDoc->appendChild(pProcInstr, NULL);
	}
	if (m_bPreserveWhiteSpace)
	{
		m_pXMLDoc->put_preserveWhiteSpace(VARIANT_TRUE);
	}
	return true;
}

bool CXMLStorage::LoadFromFile(LPCTSTR FileName)
{
	VARIANT_BOOL bLoad = VARIANT_TRUE;
	HRESULT hr;
	hr = m_pXMLDoc->load(_variant_t(FileName), &bLoad);
	return hr == S_OK;
}

bool CXMLStorage::LoadFromString(_bstr_t XML)
{
	return (m_pXMLDoc->put_text(XML) == S_OK);
}

bool CXMLStorage::SaveToFile(LPCTSTR FileName)
{
	return m_pXMLDoc->save(_variant_t(FileName)) == S_OK;
}

bool CXMLStorage::SaveToString(_bstr_t& XML)
{
	return m_pXMLDoc->get_text(XML.GetAddress()) == S_OK;
}

void CXMLStorage::Destroy()
{
	if (m_pXMLDoc != NULL)
		m_pXMLDoc.Release();
	if (m_pXMLNode != NULL)
		m_pXMLNode.Release();
}

void CXMLStorage::SetEncoding(LPCTSTR lpEncoding)
{
	ATLASSERT(lpEncoding);

	if (m_pEncoding)
	{
		delete[] m_pEncoding;
	}

	m_pEncoding = new TCHAR[lstrlen(lpEncoding) + 1];
	lstrcpy(m_pEncoding, lpEncoding);
}

LPCTSTR CXMLStorage::GetEncoding()
{
	return m_pEncoding;
}

void CXMLStorage::SetPreserveWhiteSpace(bool bNewVal)
{
	m_bPreserveWhiteSpace = bNewVal;
}

bool CXMLStorage::GetPreserveWhiteSpace()
{
	return m_bPreserveWhiteSpace;
}

//////////////////////////////////////////////////////////////////////////

CXMLSettingsArchive::CXMLSettingsArchive():m_bSave(false), 
m_pFileName(NULL)
{

}
CXMLSettingsArchive::~CXMLSettingsArchive(void)
{
	Close();
}

bool CXMLSettingsArchive::Open(LPCTSTR lpStartName, bool bSave /* = false */)
{
	Close();
	m_pFileName = new TCHAR[lstrlen(lpStartName)+1];
	lstrcpy(m_pFileName, lpStartName);
	if (!Create(bSave))
		return false;
	if (!bSave)
	{
		if (!LoadFromFile(lpStartName))
		return false;
	}
	m_bSave = bSave;
	return true;
}

bool CXMLSettingsArchive::Close()
{
	if (m_bSave)
	{
		if (!SaveToFile(m_pFileName))
			return false;
	}
	
	m_bSave = false;
	if (m_pFileName)
	{
		delete[] m_pFileName;
		m_pFileName = NULL;
	}
	Destroy();
	return true;
}
