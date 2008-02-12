/* -------------------------------------------------------------------------
//	文件名		：	htmlout.cpp
//	创建者		：	许式伟
//	创建时间	：	2004-5-11 21:29:25
//	功能描述	：	
//
// -----------------------------------------------------------------------*/

#include "stdafx.h"
#include <atlconv.h>
#include <_backward/kscomm/msxml3.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------------------
// 以下代码copy自msdn: IXSLTemplate，作修改。

#ifndef RELEASE
#define RELEASE(pInterface)  \
{\
pInterface->Release();\
pInterface = NULL;\
}
#endif

inline
STDMETHODIMP_(void) InitUnknown(VARIANT& var, IUnknown* pUnk)
{
	VariantInit(&var);
	var.vt = VT_UNKNOWN;
	var.punkVal = pUnk;
}

class KBSTRVar : public VARIANT
{
public:
	KBSTRVar(LPCSTR str)
	{
		USES_CONVERSION;
		VariantInit(this);
		vt = VT_BSTR;
		bstrVal = SysAllocString(A2W(str));
	}
	KBSTRVar(LPCWSTR str)
	{
		USES_CONVERSION;
		VariantInit(this);
		vt = VT_BSTR;
		bstrVal = SysAllocString(str);
	}
	~KBSTRVar()
	{
		SysFreeString(bstrVal);
	}
};

// -------------------------------------------------------------------------

STDMETHODIMP XSLTConvert(LPCWSTR xslFile, LPCWSTR xmlFile, IStream* outStream)
{
	VARIANT_BOOL sResult = FALSE;
	IXMLDOMDocument2* pStyleSheet=NULL;
	IXSLTemplate* pIXSLTemplate=NULL;
	IXSLProcessor* pIXSLProcessor=NULL;
	IXMLDOMDocument2* pIXMLDOMDocument=NULL;
	
	HRESULT hr = CoCreateInstance(
		CLSID_XSLTemplate, NULL, CLSCTX_SERVER, IID_IXSLTemplate, (LPVOID*)(&pIXSLTemplate));
	KS_CHECK(hr);
	{
		// 1) load xsl file
		hr=CoCreateInstance(CLSID_FreeThreadedDOMDocument, NULL,
              CLSCTX_SERVER, IID_IXMLDOMDocument2,
              (LPVOID*)(&pStyleSheet));
		KS_CHECK(hr);
	 
		hr=pStyleSheet->put_async(VARIANT_FALSE);
		KS_CHECK(hr);

		kfc::ks_wstring xslFile2(xslFile);
		for (UINT i = 0; i < xslFile2.size(); ++i)
		{
			if (xslFile2.at(i) == '/')
				xslFile2.at(i) = '\\';
		}

		hr=pStyleSheet->load(KBSTRVar(xslFile2), &sResult);
		KS_CHECK(hr);
		KS_CHECK_BOOLEX(sResult==VARIANT_TRUE, hr=E_FAIL);

		// 2) load xml source file
        hr=CoCreateInstance(CLSID_DOMDocument, NULL,
              CLSCTX_SERVER, IID_IXMLDOMDocument2,
                    (LPVOID*)(&pIXMLDOMDocument));
		KS_CHECK(hr);

        hr=pIXMLDOMDocument->put_async(VARIANT_FALSE);
		KS_CHECK(hr);

		hr=pIXMLDOMDocument->load(KBSTRVar(xmlFile), &sResult);
		KS_CHECK(hr);
		KS_CHECK_BOOLEX(sResult==VARIANT_TRUE, hr=E_FAIL);

		// 3) transform
		hr=pIXSLTemplate->putref_stylesheet(pStyleSheet);
		KS_CHECK(hr);
		
        hr=pIXSLTemplate->createProcessor(&pIXSLProcessor);
		KS_CHECK(hr);
		
		VARIANT varInput;
		InitUnknown(varInput, pIXMLDOMDocument);
		hr=pIXSLProcessor->put_input(varInput);
		KS_CHECK(hr);
		
		VARIANT varOutput;
		InitUnknown(varOutput, outStream);
		hr=pIXSLProcessor->put_output(varOutput);
		KS_CHECK(hr);
		
		hr=pIXSLProcessor->transform(&sResult);
		KS_CHECK(hr);
		KS_CHECK_BOOLEX(sResult==VARIANT_TRUE, hr=E_FAIL);
	}
KS_EXIT:
	RELEASE(pIXSLProcessor);
	RELEASE(pStyleSheet);
    RELEASE(pIXSLTemplate);
    RELEASE(pIXMLDOMDocument);
	return hr;
}

// -------------------------------------------------------------------------
