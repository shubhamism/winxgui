/* -------------------------------------------------------------------------
// 文件名		:	searcher.h
// 创建人		:	许式伟
// 创建时间		:	2006-1-8 16:58:49
// 功能描述     :	
//
// $Id: searcher.h,v 1.1 2006/01/09 01:22:26 xushiwei Exp $
// -----------------------------------------------------------------------*/
#ifndef __SEARCHER_H__
#define __SEARCHER_H__

// -------------------------------------------------------------------------
// LoadWebBrowserFromStream

inline
HRESULT LoadWebBrowserFromStream(IWebBrowser2* pWebBrowser, IStream* pStream)
{
	HRESULT hr;
	IDispatch* pHtmlDoc = NULL;
	IPersistStreamInit* pPersistStreamInit = NULL;

    // Retrieve the document object.
    hr = pWebBrowser->get_Document( &pHtmlDoc );
    if ( SUCCEEDED(hr) )
    {
        // Query for IPersistStreamInit.
        hr = pHtmlDoc->QueryInterface( IID_IPersistStreamInit,  (void**)&pPersistStreamInit );
        if ( SUCCEEDED(hr) )
        {
            // Initialize the document.
            hr = pPersistStreamInit->InitNew();
            if ( SUCCEEDED(hr) )
            {
                // Load the contents of the stream.
                hr = pPersistStreamInit->Load( pStream );
            }
            pPersistStreamInit->Release();
        }
    }

	return hr;
}

inline
HRESULT LoadWebBrowserFromString(IWebBrowser2* pWebBrowser, LPCTSTR szHTML)
{
	CStreamOnCString stream(szHTML);

	return LoadWebBrowserFromStream(pWebBrowser, &stream);
}

inline
HRESULT LoadWebBrowserBlank(IWebBrowser2* pWebBrowser)
{
	CStreamOnCString stream;

	return LoadWebBrowserFromStream(pWebBrowser, &stream);
}

// -------------------------------------------------------------------------

#include "../searcher/searcher.h"

// -------------------------------------------------------------------------
// $Log: searcher.h,v $
// Revision 1.1  2006/01/09 01:22:26  xushiwei
// 1、增加工程mfcie，其实改造为searcher的demo（GUI）
// 2、英文分词漏入文件，暂时屏蔽。
//

#endif /* __SEARCHER_H__ */
