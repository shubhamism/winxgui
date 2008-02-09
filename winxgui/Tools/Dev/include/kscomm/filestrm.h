/* -------------------------------------------------------------------------
//	文件名		：	filestrm.h
//	创建者		：	牟翔
//	创建时间	：	2003-3-21 18:00:41
//	功能描述	：	
//
//	$Id: filestrm.h,v 1.2 2006/05/30 00:28:33 xushiwei Exp $
// -----------------------------------------------------------------------*/

#include "stdafx.h"
#include <stdio.h>
#include <_backward/kscomm/_base.h>

#ifndef LISet32
#define LISet32(li, v) ((li).HighPart = (v) < 0 ? -1 : 0, (li).LowPart = (v))
#define ULISet32(li, v) ((li).HighPart = 0, (li).LowPart = (v))
#endif

#ifndef REPORT
#define REPORT(s)
#endif

// -------------------------------------------------------------------------

class KWriteStream : public IStream
{
public:
	KWriteStream(LPCSTR szFile)
	{
		m_fp = fopen(szFile, "wb");
	}
	~KWriteStream()
	{
		if(m_fp)
		{
			fclose(m_fp);
			m_fp = NULL;
		}
	}

	STDMETHODIMP_(BOOL) IsOpened() const
	{
		return m_fp != NULL;
	}

	STDMETHODIMP Read( void *pv, ULONG cb, ULONG *pcbRead);
	STDMETHODIMP Write( const void *pv, ULONG cb, ULONG *pcbWritten);
	STDMETHODIMP Seek( LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition);
	STDMETHODIMP SetSize( ULARGE_INTEGER libNewSize);
	STDMETHODIMP CopyTo ( IStream *pstm, ULARGE_INTEGER cb, ULARGE_INTEGER *pcbRead, ULARGE_INTEGER *pcbWritten);
	STDMETHODIMP Commit( DWORD grfCommitFlags);
	STDMETHODIMP Revert( void);
	STDMETHODIMP LockRegion( ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType);
	STDMETHODIMP UnlockRegion( ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType);
	STDMETHODIMP Stat( STATSTG *pstatstg, DWORD grfStatFlag);
	STDMETHODIMP Clone( IStream  **ppstm);
	
	STDMETHODIMP_(ULONG) AddRef()
	{
		return 2;
	}
	STDMETHODIMP_(ULONG) Release()
	{
		return 2;
	}
	STDMETHODIMP QueryInterface(REFIID iid, void** ppv)
	{
		if (iid == IID_IStream || iid == IID_IUnknown)
		{
			*ppv = this;
			return S_OK;
		}
		return E_NOINTERFACE;
	}

protected:
	FILE* m_fp;
};

STDMETHODIMP KWriteStream::Read(void* pv, ULONG cb, ULONG* pcbRead)
{
	size_t cbRead = fread(pv, sizeof(char), cb, m_fp);
	if(pcbRead)
		*pcbRead = cbRead;
	return S_OK;
}

STDMETHODIMP KWriteStream::Write(const void *pv, ULONG cb, ULONG *pcbWritten)
{
	size_t cbWritten = fwrite(pv, sizeof(char), cb, m_fp);
	if (pcbWritten)
		*pcbWritten = cbWritten;
	return S_OK;
}

STDMETHODIMP KWriteStream::Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition)
{
	if (fseek(m_fp, dlibMove.LowPart, (int)dwOrigin))
		return E_FAIL;

	if(plibNewPosition)
	{
		plibNewPosition->HighPart = 0x00000000L;
		plibNewPosition->LowPart  = ftell(m_fp);
	}
	return S_OK;
}

STDMETHODIMP KWriteStream::SetSize(ULARGE_INTEGER libNewSize)
{
	REPORT(__L("KWriteStream::SetSize - NotImpl"));
	return E_NOTIMPL;
}

STDMETHODIMP KWriteStream::CopyTo(IStream* pstm, ULARGE_INTEGER cb, ULARGE_INTEGER* pcbRead, ULARGE_INTEGER* pcbWritten)
{
	HRESULT hr			= S_OK;
	DWORD cbRead		= 0;
	DWORD cbWrite		= 0;
	DWORD cbReadTotal	= 0;
	DWORD cbWriteTotal	= 0;
	ULARGE_INTEGER cbTatal;
	ULISet32(cbTatal, 0);
	
	const cbBuf = 4096;
	char* buf = new char[cbBuf];

	if(pcbRead)
		ULISet32(*pcbRead, 0);
	if(pcbWritten)
		ULISet32(*pcbWritten, 0);

	for(;cbTatal.LowPart < cb.LowPart;)
	{
		hr = Read(buf, cbBuf, &cbRead);
		KS_CHECK(hr);
		hr = pstm->Write(buf, cbRead, &cbWrite);
		KS_CHECK(hr);
		if(cbWrite != cbRead)
			break;
		cbReadTotal  += cbRead;
		cbWriteTotal += cbWrite;

		if( cbRead == 0 || cbWrite != cbRead)
			break;

		cbRead	= 0;
		cbWrite	= 0;
	}
KS_EXIT:

	if (pcbRead)
		ULISet32(*pcbRead, cbReadTotal);
	if(pcbWritten)
		ULISet32(*pcbWritten, cbWriteTotal);

	delete buf;
	return hr;
}

STDMETHODIMP KWriteStream::Commit(DWORD grfCommitFlags)
{
	fflush(m_fp);
	return S_OK;	
}

STDMETHODIMP KWriteStream::Revert(void)
{
	REPORT(__L("KWriteStream::Revert - NotImpl"));	
	return E_NOTIMPL;
}

STDMETHODIMP KWriteStream::LockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
{
	REPORT(__L("KWriteStream::LockRegion - NotImpl"));
	return E_NOTIMPL;
}

STDMETHODIMP KWriteStream::UnlockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
{
	REPORT(__L("KWriteStream::UnlockRegion - NotImpl"));
	return E_NOTIMPL;
}

STDMETHODIMP KWriteStream::Stat(STATSTG *pstatstg, DWORD grfStatFlag)
{	
	//Only support cbSize
	long lCurPos = ftell(m_fp);
	fseek(m_fp, 0, SEEK_END);
	long lEndPos = ftell(m_fp);	
	pstatstg->cbSize.HighPart = 0;
	pstatstg->cbSize.LowPart = lEndPos;
	fseek(m_fp, lCurPos, SEEK_SET);

	return S_OK;
}

STDMETHODIMP KWriteStream::Clone(IStream **ppstm)
{
	REPORT(__L("KWriteStream::Clone - NotImpl"));
	return E_NOTIMPL;
}

// -------------------------------------------------------------------------
// $Log: filestrm.h,v $
// Revision 1.2  2006/05/30 00:28:33  xushiwei
// class KWriteStream;
//
