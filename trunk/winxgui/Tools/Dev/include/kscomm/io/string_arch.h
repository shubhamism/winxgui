/* -------------------------------------------------------------------------
//	文件名		：	io/string_arch.h
//	创建者		：	许式伟
//	创建时间	：	5/5/2003 7:31:00 PM
//	功能描述	：	
//
// -----------------------------------------------------------------------*/
#ifndef __KFC_IO_STRING_ARCH_H__
#define __KFC_IO_STRING_ARCH_H__

#ifndef _KFC
#define _KFC
#define _KFC_BEGIN
#define _KFC_END
#endif

_KFC_BEGIN

template <class _E>
struct KStrArchiveTraits
{
	typedef _E char_type;
	typedef _E int_type;
	typedef unsigned char_type uchar_type;
	typedef unsigned pos_type;
	typedef unsigned size_type;
	typedef int off_type;
};

template <char>
struct KStrArchiveTraits
{
	typedef char _E;
	typedef _E char_type;
	typedef int int_type;
	typedef unsigned char_type uchar_type;
	typedef unsigned pos_type;
	typedef unsigned size_type;
	typedef int off_type;
};

template <WCHAR>
struct KStrArchiveTraits
{
	typedef WCHAR _E;
	typedef _E char_type;
	typedef int int_type;
	typedef unsigned short uchar_type;
	typedef unsigned pos_type;
	typedef unsigned size_type;
	typedef int off_type;
};

// -------------------------------------------------------------------------

template < class _E, class _Tr = KStrArchiveTraits<_E> >
class KStrReadArchive
{
public:
	typedef typename _Tr::char_type	char_type;
	typedef typename _Tr::uchar_type uchar_type;
	typedef typename _Tr::int_type	int_type;
	typedef typename _Tr::pos_type	pos_type;
	typedef typename _Tr::off_type	off_type;
	typedef typename _Tr::size_type	size_type;
	
	enum { endch = -1 };
	
public:
	KStrReadArchive(const _E* s) : _ptr(s), _begin(s)
	{
		while (*s)
			s++;
		_end = s;
	}
	KStrReadArchive(const _E* s, size_type cch)
		: _ptr(s), _begin(s), _end(s+cch)
	{
	}
	KStrReadArchive(const _E* s, const _E* end)
		: _ptr(s), _begin(s), _end(end)
	{
	}
	size_type get(_E* buf, size_type cch)
	{
		size_type i;
		for (i = 0; i < cch; ++i)
		{
			if (_ptr >= _end)
				break;
			*buf++ = *_ptr++;
		}
		return i;
	}
	int_type get()
	{
		if (_ptr < _end)
			return *(uchar_type*)_ptr++;
		return endch;
	}
	void unget()
	{
		if (_ptr > _begin)
			--_ptr;
	}
	void seek(pos_type pos)
	{
		if (pos <= (pos_type)(_end - _begin))
			_ptr = _begin + pos;
	}
	pos_type tell() const
	{
		return _ptr - _begin;
	}

private:
	const _E* _ptr;
	const _E* _end;
	const _E* _begin;
};

// -------------------------------------------------------------------------

class KAnsiStrReadArchive : public KStrReadArchive<char>
{
public:
	typedef char _E;
	typedef KStrReadArchive<_E> _Base;

	KAnsiStrReadArchive(const _E* s) : _Base(s)	{}
	KAnsiStrReadArchive(const _E* s, size_type cch) : _Base(s, cch) {}
	KAnsiStrReadArchive(const _E* s, const _E* end) : _Base(s, end) {}

public:
	size_type read(void* buf, size_type cch)
		{ return get((char*)buf, cch); }
};

typedef KStrReadArchive<WCHAR> KWideStrReadArchive;

// -------------------------------------------------------------------------

template < class _E, class _Tr = KStrArchiveTraits<_E> >
class KStrWriteArchive
{
public:
	typedef _Tr::char_type	char_type;
	typedef _Tr::uchar_type	uchar_type;
	typedef _Tr::int_type	int_type;
	typedef _Tr::pos_type	pos_type;
	typedef _Tr::size_type	size_type;
	
public:
	KStrWriteArchive(_E* s, size_type cch)
		: _ptr(s), _end(s+cch)
	{
	}
	KStrWriteArchive(_E* s, _E* end)
		: _ptr(s), _end(end)
	{
	}
	void put(const _E* s)
	{
		const _E* ptr = s;
		while (*ptr)
		{
			if (_ptr >= _end)
				break;
			*_ptr++ = *ptr++;
		}
		return ptr - s;
	}
	size_type put(const _E* s, size_type cch)
	{
		size_type i;
		for (i = 0; i < cch; ++i)
		{
			if (_ptr >= _end)
				break;
			*_ptr++ = *buf++;
		}
		return i;
	}
	size_type put(int cch, _E ch)
	{
		size_type i;
		for (i = 0; i < cch; ++i)
		{
			if (_ptr >= _end)
				break;
			*_ptr++ = ch;
		}
		return i;
	}
	size_type put(_E ch)
	{
		if (_ptr < _end)
		{
			*_ptr++ = ch;
			return 1;
		}
		return 0;
	}
	size_type size() const
	{
		return _end - _ptr;
	}
	
private:
	_E* _ptr;
	_E* _end;
};

// -------------------------------------------------------------------------

class KAnsiStrWriteArchive : public KStrWriteArchive<char>
{
public:
	typedef char _E;
	typedef KStrWriteArchive<_E> _Base;
	
	KAnsiStrWriteArchive(const _E* s, size_type cch) : _Base(s, cch) {}
	KAnsiStrWriteArchive(const _E* s, const _E* end) : _Base(s, end) {}
	
public:
	size_type write(const void* buf, size_type cch)
		{ return put((const char*)buf, cch); }
};

typedef KStrWriteArchive<WCHAR> KWideStrWriteArchive;

// -------------------------------------------------------------------------

_KFC_END

#endif /* __KFC_IO_STRING_ARCH_H__ */
