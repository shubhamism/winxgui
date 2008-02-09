/* -------------------------------------------------------------------------
//	文件名		：	adapter/IStreamAdapter.h
//	创建者		：	许式伟
//	创建时间	：	2003-4-12 17:06:34
//	功能描述	：	
//
// -----------------------------------------------------------------------*/
#ifndef __IO_ADAPTER_ISTREAMADAPTER_H__
#define __IO_ADAPTER_ISTREAMADAPTER_H__

#ifndef __IO_ADAPTER_LARGEINT_H__
#include "LargeInt.h"
#endif

// -------------------------------------------------------------------------

STDAPI _XCreateStreamOnFile(LPCWSTR szFile, DWORD grfMode, IStream** ppv);

#ifndef CreateStreamOnFile
#define CreateStreamOnFile(szFile, grfMode, ppv)							\
	_XCreateStreamOnFile(szFile, grfMode, ppv)
#endif

// -------------------------------------------------------------------------

_KFC_BEGIN

class IStreamAdapter
{
public:
	typedef int				int_type;
	typedef char			char_type;
	typedef unsigned char	uchar_type;
	typedef KULargeInteger	pos_type;
	typedef KLargeInteger	off_type;
	typedef unsigned		size_type;
	typedef char_type		_E;
	
	enum { endch = -1 };

protected:
	IStream* _pStrm;
	
public:
	IStreamAdapter()
	{
		_pStrm = NULL;
	}
	IStreamAdapter(IStream* pStrm)
	{
		_pStrm = pStrm;
		if(pStrm)
			pStrm->AddRef();
	}
	~IStreamAdapter()
	{
		if (_pStrm)
			_pStrm->Release();
	}

	void attach(IStream* pStrm)
	{
		if (_pStrm)
			_pStrm->Release();
		_pStrm = pStrm;
	}

	IStream* detach()
	{
		IStream* p = _pStrm;
		_pStrm = NULL;
		return p;
	}

	HRESULT open(LPCWSTR szFile, UINT nMode)
	{
		ASSERT(_pStrm == NULL);
		return _XCreateStreamOnFile(szFile, nMode, &_pStrm);
	}

	void close()
	{
		if (_pStrm)
		{
			_pStrm->Release();
			_pStrm = NULL;
		}
	}

	IStream** operator&()
	{
		ASSERT(_pStrm == NULL);
		return &_pStrm;
	}

	operator IStream*() const
	{
		return _pStrm;
	}
	
	int operator!() const
	{
		return _pStrm == NULL;
	}

	int bad() const
	{
		return _pStrm == NULL;
	}

	int good() const
	{
		return _pStrm != NULL;
	}
	
	void seek(const off_type& pos, int dir = SEEK_SET)
	{
		_pStrm->Seek(*(LARGE_INTEGER*)&pos, dir, NULL);
	}
	
	pos_type tell() const
	{
		ULARGE_INTEGER dlibPos;
		ULISet32(dlibPos, 0);
		_pStrm->Seek(*(LARGE_INTEGER*)&dlibPos, SEEK_CUR, &dlibPos);
		return dlibPos;
	}

	int_type get()
	{
		int_type ch = 0;
		ULONG stRead = 0;
		_pStrm->Read((void*)&ch, sizeof(char_type), &stRead);
		if (!stRead)
			return endch;
		return ch;
	}
	
	size_type get(char_type* buf, size_type cch)
	{
		ULONG stRead = 0;
		_pStrm->Read((void*)buf, sizeof(char_type)*cch , &stRead);
		return stRead;
	}
	
	size_type read(void* buf, size_type cb)
	{
		ULONG stRead = 0L;
		_pStrm->Read(buf, sizeof(char_type)*cb, &stRead);
		return stRead;
	}
	
	size_type put(const _E* s, size_type cch)
	{
		ULONG uWrite = 0L;
		_pStrm->Write((void*)s, cch, &uWrite);
		return uWrite;
	}

	void put(const _E* s)
	{
		const _E* ps = s;
		while(*ps)
			++ps;
		put(s, ps - s);
	}
	
	size_type put(size_type cch, _E ch)
	{
		_E* p0 = new _E[cch];
		_E* p = p0;
		while (cch--)
			*p++ = ch;
		cch = put(p0, p-p0);
		delete[] p0;
		return cch;
	}
	
	size_type put(_E ch)
	{
		ULONG uWrite = 0L;
		_pStrm->Write((void*)&ch, sizeof(_E), &uWrite);
		return uWrite;
	}

	size_type write(const void* buf, size_type cb)
	{
		ULONG uWrite = 0L;
		_pStrm->Write((void*)buf, cb, &uWrite);
		return uWrite;
	}

	void flush()
	{
		_pStrm->Commit(0);
	}
};

_KFC_END

// -------------------------------------------------------------------------

#endif /* __IO_ADAPTER_ISTREAMADAPTER_H__ */
