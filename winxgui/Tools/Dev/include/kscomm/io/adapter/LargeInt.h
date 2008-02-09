/* -------------------------------------------------------------------------
//	�ļ���		��	io/adapter/LargeInt.h
//	������		��	2003-4-12 17:09:41
//	����ʱ��	��	2003-8-7 22:14:29
//	��������	��	
//		- changelog �콨��, 2003-7-18,�޸Ĳ��ִ���
// -----------------------------------------------------------------------*/
#ifndef __IO_ADAPTER_LARGEINT_H__
#define __IO_ADAPTER_LARGEINT_H__

#error "..."

_KFC_BEGIN

/*@
  @define LISet32, ULISet32
  @brief 32λ����ת��Ϊ64λ������ǰ��Ϊ�з��ţ������޷��š�
  */
#ifndef LISet32
#define LISet32(li, v) ((li).HighPart = (v) < 0 ? -1 : 0, (li).LowPart = (v))
#endif

#ifndef ULISet32
#define ULISet32(li, v) ((li).HighPart = 0, (li).LowPart = (v))
#endif

class KULargeInteger
{
private:
	ULARGE_INTEGER _data;
	typedef ULARGE_INTEGER _Base;
	typedef KULargeInteger _Myt;
	
public:
	friend class KLargeInteger;

	KULargeInteger(int i = 0)
	{
		ULISet32(_data, i);
	}
	KULargeInteger(const KLargeInteger& r);
	KULargeInteger(const _Base& li)
	{
		_data = li;
	}
	KULargeInteger(const _Myt& li)
	{
		_data = li._data;
	}

	// �������int��32 bits
	const _Myt& operator+=(LONG i) 
	{
		if(i < 0)//������λ�����
		{
			unsigned temp = -i;
			if(_data.LowPart < temp)//����λ���
			{
				_data.HighPart--;
			}
			_data.LowPart -= temp;
		}
		else//���ǽ�λ�����
		{
			if(_data.LowPart < (_data.LowPart < i ? i : _data.LowPart))//�н�λ���
			{
				_data.HighPart ++;
			}		
			_data.LowPart +=i;
		}
		return *this;
	}

	const _Myt&  operator+=(DWORD i)//����������λ���
	{
		_data.LowPart += i;
		if(_data.LowPart < (_data.LowPart < i ? i : _data.LowPart))// �����н�λ
		{
			_data.HighPart ++;
		}
		return *this;
	}

	bool operator==(const _Myt& li) const
	{
		return _data.LowPart == li._data.LowPart && 
			_data.HighPart == li._data.HighPart;
	}
	bool operator<(const _Myt& li) const
	{
		if (_data.HighPart < li._data.HighPart)
			return true;
		else if (li._data.HighPart < _data.HighPart)
			return false;
		else
			return _data.LowPart < li._data.LowPart;
	}
	bool operator<=(const _Myt& li) const
	{
		if (_data.HighPart < li._data.HighPart)
			return true;
		else if (li._data.HighPart < _data.HighPart)
			return false;
		else
			return _data.LowPart <= li._data.LowPart;
	}
	
public:
	operator _Base&()
	{
		return _data;
	}
	operator const _Base&() const
	{
		return _data;
	}
	const _Myt& operator=(const _Base& li)
	{
		_data = li;
		return *this;
	}
	const _Myt& operator-=(LONG i)
	{
		return operator+=(-i);
	}
	const _Myt& operator++()
	{
		return operator+=(1UL);
	}
	_Myt operator++(int)
	{
		_Myt li = *this;
		operator+=(1UL);
		return li;
	}

	const _Myt& operator--()
	{
		return operator+=(-1L);
	}
	_Myt operator--(int)
	{
		_Myt li = *this;
		operator+=(-1L);
		return li;
	}
	_Myt operator+(LONG i)
	{
		_Myt li = *this;
		return li += i;
	}
	_Myt operator-(LONG i)
	{
		_Myt li = *this;
		return li -= i;
	}

	bool operator!=(const _Myt& li) const
	{
		return !operator==(li);
	}
	
	bool operator>(const _Myt& li) const
	{
		return !operator<=(li);
	}

	bool operator>=(const _Myt& li) const
	{
		return !operator<(li);
	}
};


class KLargeInteger
{
private:
	LARGE_INTEGER _data;
	typedef LARGE_INTEGER _Base;
	typedef KLargeInteger _Myt;

	friend class KULargeInteger;

public:
	KLargeInteger(int i = 0)
	{
		LISet32(_data, i);
	}
	KLargeInteger(const _Base& li)
	{
		_data = li;
	}
	KLargeInteger(const _Myt& li)
	{
		_data = li._data;
	}
	KLargeInteger(const KULargeInteger& li)
	{
		_data = (_Base&)li._data;
	}

	// �������int��32 bits��
	const _Myt& operator+=(LONG i) 
	{
		if(i < 0) // ������λ�����
		{
			unsigned temp = -i;
			if(_data.LowPart < temp)//����λ���
			{
				_data.HighPart--;
			}
			_data.LowPart -= temp;
		}
		else//���ǽ�λ�����
		{
			if(_data.LowPart < (_data.LowPart < i ? i : _data.LowPart))//�н�λ���
			{
				_data.HighPart ++;
			}		
			_data.LowPart +=i;
		}
		return *this;
	}

	const _Myt& operator+=(DWORD i)//����������λ���
	{
		_data.LowPart += i;
		if(_data.LowPart < (_data.LowPart < i ? i : _data.LowPart))// �����н�λ
		{
			_data.HighPart ++;
		}
		return *this;
	}

	bool operator==(const _Myt& li) const
	{
		return _data.LowPart == li._data.LowPart && 
			_data.HighPart == li._data.HighPart;
	}

	bool operator<(const _Myt& li) const
	{
		if (_data.HighPart < li._data.HighPart)
			return true;
		else if (li._data.HighPart < _data.HighPart)
			return false;
		else
		{
			if (li._data.HighPart < 0)
				return li._data.LowPart < _data.LowPart;
			return _data.LowPart < li._data.LowPart;
		}
	}
	bool operator<=(const _Myt& li) const
	{
		if (_data.HighPart < li._data.HighPart)
			return true;
		else if (li._data.HighPart < _data.HighPart)
			return false;
		else
		{
			if (li._data.HighPart < 0)
				return li._data.LowPart <= _data.LowPart;
			return _data.LowPart <= li._data.LowPart;
		}
	}
	
public:
	operator _Base&()
	{
		return _data;
	}
	operator const _Base&() const
	{
		return _data;
	}
	const _Myt& operator=(const _Base& li)
	{
		_data = li;
		return *this;
	}
	const _Myt& operator-=(LONG i)
	{
		return operator+=(-i);
	}
	const _Myt& operator++()
	{
		return operator+=(1L);
	}
	const _Myt& operator--()
	{
		return operator+=(-1L);
	}
	_Myt operator++(int)
	{
		_Myt li = *this;
		operator+=(1L);
		return li;
	}
	_Myt operator--(int)
	{
		_Myt li = *this;
		operator+=(-1L);
		return li;
	}
	_Myt operator+(LONG i)
	{
		_Myt li = *this;
		return li += i;
	}
	_Myt operator-(LONG i)
	{
		_Myt li = *this;
		return li -= i;
	}
	bool operator!=(const _Myt& li) const
	{
		return !operator==(li);
	}
	bool operator>(const _Myt& li) const
	{
		return !operator<=(li);
	}

	bool operator>=(const _Myt& li) const
	{
		return !operator<(li);
	}
};


inline int ToInt(const KLargeInteger& li)
{
	const LARGE_INTEGER& _data = li;
	ASSERT(_data.HighPart == 0 || _data.HighPart == -1);
	
	return _data.LowPart;
}

inline UINT ToUInt(const KULargeInteger& li)
{
	const ULARGE_INTEGER& _data = li;
	ASSERT(_data.HighPart == 0);
	
	return _data.LowPart;
}

inline KLargeInteger operator-(const KULargeInteger& a, const KULargeInteger& b)
{
	const ULARGE_INTEGER& ali = a;
	const ULARGE_INTEGER& bli = b;
	ASSERT(ali.HighPart == 0 || bli.HighPart == 0);
	
	return KLargeInteger(ali.LowPart - bli.LowPart);
}

inline KULargeInteger::KULargeInteger(const KLargeInteger& r)
{
	_data = (ULARGE_INTEGER&)r._data;
}

// -------------------------------------------------------------------------

_KFC_END

#endif /* __IO_ADAPTER_LARGEINT_H__ */
