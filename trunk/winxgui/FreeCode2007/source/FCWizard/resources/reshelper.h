#ifndef _RESHELPER_H__
#define _RESHELPER_H__

#include <atlapp.h>
#include <atlmisc.h>
#include "../../public/wtlfileex.h"



namespace ATL {

template <class T>
class WrapperT
{
public:
	WrapperT(T& _t) : t(_t)
	{
	}
	template <class _Ty>
	void *operator new(size_t, _Ty* p)
	{
		return p;
	}
	T t;
};

template <class T>
class CSimpleArray2
{
public:
	T* m_aT;
	int m_nSize;
	int m_nAllocSize;

// Construction/destruction
	CSimpleArray2() : m_aT(NULL), m_nSize(0), m_nAllocSize(0)
	{ }

	~CSimpleArray2()
	{
		RemoveAll();
	}

// Operations
	int GetSize() const
	{
		return m_nSize;
	}
	BOOL Add(T& t)
	{
		if(m_nSize == m_nAllocSize)
		{
			T* aT;
			int nNewAllocSize = (m_nAllocSize == 0) ? 1 : (m_nSize * 2);
			aT = (T*)realloc(m_aT, nNewAllocSize * sizeof(T));
			if(aT == NULL)
				return FALSE;
			m_nAllocSize = nNewAllocSize;
			m_aT = aT;
		}
		m_nSize++;
		SetAtIndex(m_nSize - 1, t);
		return TRUE;
	}
	BOOL Remove(T& t)
	{
		int nIndex = Find(t);
		if(nIndex == -1)
			return FALSE;
		return RemoveAt(nIndex);
	}
	BOOL RemoveAt(int nIndex)
	{
		if(nIndex != (m_nSize - 1))
		{
			m_aT[nIndex].~T();
			memmove((void*)&m_aT[nIndex], (void*)&m_aT[nIndex + 1], (m_nSize - (nIndex + 1)) * sizeof(T));
		}
		m_nSize--;
		return TRUE;
	}
	void RemoveAll()
	{
		if(m_aT != NULL)
		{
			for(int i = 0; i < m_nSize; i++)
				m_aT[i].~T();
			free(m_aT);
			m_aT = NULL;
		}
		m_nSize = 0;
		m_nAllocSize = 0;
	}
	T& operator[] (int nIndex) const
	{
		ATLASSERT(nIndex >= 0 && nIndex < m_nSize);
		return m_aT[nIndex];
	}
	T* GetData() const
	{
		return m_aT;
	}

// Implementation
	void SetAtIndex(int nIndex, T& t)
	{
		ATLASSERT(nIndex >= 0 && nIndex < m_nSize);
		new(&m_aT[nIndex]) WrapperT<T>(t);
	}
	int Find(T& t) const
	{
		for(int i = 0; i < m_nSize; i++)
		{
			if(m_aT[i] == t)
				return i;
		}
		return -1;  // not found
	}
};


template<typename E>
class CAtlArray : public ATL::CSimpleArray2<E>
{
protected:
	typedef CAtlArray thisClass;
	typedef ATL::CSimpleArray2<E> baseClass;

public:

	//Real CAtlArray:  size_t GetCount() const throw();
	size_t GetCount() const
	{
		return m_nSize;
	}

	//Real CAtlArray:  void InsertAt( size_t iElement, INARGTYPE element, size_t nCount = 1 );
	void InsertAt( size_t nIndex, E& element )
	{
		if(m_nSize == m_nAllocSize)
		{
			E* aT;
			int nNewAllocSize = (m_nAllocSize == 0) ? 1 : (m_nSize * 2);
			aT = (E*)realloc(m_aT, nNewAllocSize * sizeof(E));
			if(aT == NULL)
				return; // FALSE;
			m_nAllocSize = nNewAllocSize;
			m_aT = aT;
		}
		memmove((void*)&m_aT[nIndex+1], (void*)&m_aT[nIndex], (m_nSize - nIndex ) * sizeof(E));
		m_nSize++;
		SetAtIndex(nIndex, element);
		//return TRUE;
	}

	//Real CAtlArray:  void RemoveAt( size_t iElement, size_t nCount = 1 );
	void RemoveAt( size_t nIndex )
	{
		// This is an improvement over CSimpleArray::RemoveAt suggested
		//  by Jim Springfield on the ATL discussion list
		m_aT[nIndex].~E();
		if((int)nIndex != (m_nSize - 1))
		{
			memmove((void*)&m_aT[nIndex], (void*)&m_aT[nIndex + 1], (m_nSize - (nIndex + 1)) * sizeof(E));
		}
		m_nSize--;
		//return TRUE;
	}

	//Real CAtlArray:  const E& operator[]( size_t iElement ) const throw();
	const E& operator[]( size_t iElement ) const
	{
		ATLASSERT( iElement < (size_t)m_nSize );
		return( m_aT[iElement] );
	}

	//Real CAtlArray:  E& operator[]( size_t iElement ) throw();
	E& operator[]( size_t iElement )
	{
		ATLASSERT( iElement < (size_t)m_nSize );
		return( m_aT[iElement] );
	}

	const E & GetAt(size_t index) const
	{
		return m_aT[index];
	}

	void Append(CAtlArray<E> & array)
	{
		for (int i = 0; i < array.GetSize(); i++)
		{
			baseClass::Add(array.m_aT[i]);
		}
	}

	void Copy(const CAtlArray<E> & array)
	{
		baseClass::RemoveAll();
		for (int i = 0; i < array.GetSize(); i++)
		{
			baseClass::Add(array.m_aT[i]);
		}
	}
};

template<class T>
class CSmartAtlArray : public CAtlArray<T>
{
public:
	CSmartAtlArray(const CSmartAtlArray<T>& ar)
	{
		Copy(ar);
	}
	CSmartAtlArray() : CAtlArray<T>(){};
	CSmartAtlArray& operator =(const CSmartAtlArray<T> ar)
	{
		Copy(ar);
		return *this;
	}
};

inline int CutString(const CString InStr, CAtlArray<CString>& OutStrings, LPCTSTR Separators = _T(" \t,"))
{
	int Pos = 0;
	int StartPos = 0;
	bool bQuotas = false;
	OutStrings.RemoveAll();

	while (Pos < InStr.GetLength())
	{
		TCHAR ch = InStr[Pos];
		if (ch == _T('\"'))
		{
			if (Pos < InStr.GetLength()-1 && InStr[Pos + 1]  == _T('\"'))
			{
				Pos += 2;
				continue;
			}
			else
			{
				bQuotas = !bQuotas;
			}
		}
		if (!bQuotas && _tcsrchr(Separators, ch))
		{
			//нашл?сепарато?
			int WordLen = Pos - StartPos;
			if (WordLen)
			{
				CString NewWord = InStr.Mid(StartPos, WordLen);
				OutStrings.Add(NewWord);
			}
			StartPos = Pos + 1;
		}
		Pos++;
	}
	int WordLen = Pos - StartPos;
	if (WordLen)
	{
		CString NewWord = InStr.Mid(StartPos, WordLen);
		OutStrings.Add(NewWord);
	}
	else
	{
		OutStrings.Add(CString());
	}
	return (int)OutStrings.GetCount();
}

inline CString TokenizeString(const CString & InStr, LPCTSTR ken = _T(" \t,"), int iStart = 0)
{
	CAtlArray<CString> ar;
	CutString(InStr,ar,ken);
	if (ar.GetSize() >= iStart)
	{
		return ar[iStart];
	}
	return _T("");
}

}; // namespace ATL

#endif