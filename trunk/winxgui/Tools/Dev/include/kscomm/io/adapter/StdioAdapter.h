/* -------------------------------------------------------------------------
//	文件名		：	io/adapter/StdioAdapter.h
//	创建者		：	许式伟
//	创建时间	：	2004-3-17 16:56:05
//	功能描述	：	
//
// -----------------------------------------------------------------------*/
#ifndef __IO_ADAPTER_STDIOADAPTER_H__
#define __IO_ADAPTER_STDIOADAPTER_H__

#error "..."

#if !defined(_INC_STDIO) && !defined(_STDIO_H)
#include <stdio.h>
#endif

// -------------------------------------------------------------------------

_KFC_BEGIN

class StdioAdapter
{
public:
	typedef int				int_type;
	typedef char			char_type;
	typedef unsigned char	uchar_type;
	typedef unsigned long	pos_type;
	typedef signed long		off_type;
	typedef unsigned		size_type;
	typedef char_type		_E;
	
	enum { endch = -1 };
	
protected:
	FILE* _pFile;
	
public:
	StdioAdapter(FILE* pFile) : _pFile(pFile)
	{
	}
	~StdioAdapter()
	{
		if (_pFile)
		{
			fclose(_pFile);
			_pFile = NULL;
		}
	}
	
	void attach(FILE* pFile)
	{
		_pFile = pFile;
	}

	FILE* detach()
	{
		FILE* pFile = _pFile;
		_pFile = NULL;
		return pFile;
	}

	void seek(const off_type& pos, int dir = SEEK_SET)
	{
		fseek(_pFile, pos, dir);
	}
	
	pos_type tell() const
	{
		return ftell(_pFile);
	}
	
	size_type get(_E* buf, size_type cch)
	{	
		return fread(buf, sizeof(char_type), cch, _pFile);
	}

	size_type put(const _E* s, size_type cch)
	{
		return fwrite(s, sizeof(char_type), cch, _pFile);
	}

	void flush()
	{
		fflush(_pFile);
	}

	void close()
	{
		if (_pFile)
		{
			fclose(_pFile);
			_pFile = NULL;
		}
	}

	operator FILE*() const
	{
		return _pFile;
	}

	int operator!() const
	{
		return _pFile == NULL;
	}

	int good() const
	{
		return _pFile != NULL;
	}

	int bad() const
	{
		return _pFile == NULL;
	}
};

_KFC_END

// -------------------------------------------------------------------------

#endif /* __IO_ADAPTER_STDIOADAPTER_H__ */
