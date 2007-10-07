/***********************************************************************************
*	File		: NewBValArray.h
*	Description : Header for a MFC CArray-like class.
*				  This new class uses a pre-allocated memory pool for actual data
*				  of the array.This pool can be resized to a bigger capacity but
*				  that action requires a new larger memory pool and a memcpy().
*				  So you should avoid this as you can.
*
*	How to use:
*				  NewBValArray<MyClass,MyClass> rgMyArray(1000);
*				  So rgMyArray will pre-allocates a memory pool of 1000 MyClass items.
*				  NOTE: rgMyArray still a blank array, i.e rgMyArray.GetSize() = 0;as 
*				  long as you don't "add" item to it by Add(), or oprerator[]
*
*	              Others, it can be used the same as MFC CArray, i.e you can safely 
*				  replace all CArray with NewBArray.
*
*   Special features:
*				  I make use of placement new and delete as CArray. So it should works
*				  on others compilers support this C++ standard.(Not test yet)
*
*	Author		: Nguyen Binh		
*	Email       : Ngbinh@glassegg.com
*	Company		: GlassEgg Digital Media
*	Created:	: 15/03/2002.
*   Copyright   : You can use this small source as you like but please drop me a mail.
*   TODO        : 
*					+ Add double-linked list to hold actual data
*					+ Make it thread-safe
***********************************************************************************/

#ifndef __NEWB_VAL_ARRAY_H__
#define __NEWB_VAL_ARRAY_H__

#ifndef __NEWB_CONFIG_H__
#include "NewBConfig.h"
#endif

#ifndef _NEW_
	#include <new>
#endif

#if defined(_MSC_VER) && _MSC_VER > 1200
#define SUPPORT_PUSH_MACRO
#endif

#if defined(SUPPORT_PUSH_MACRO)
#pragma push_macro("new")
#undef new
#endif

template<class TYPE, class ARG_TYPE = const TYPE&>
class NewBValArray 
{
public:
// Construction
	NewBValArray();
	NewBValArray(NEWB_INT nMaxSize);

// Attributes
	NEWB_INT GetSize() const;
	NEWB_INT GetCount() const;
	NEWB_BOOL IsEmpty() const;
	NEWB_INT GetUpperBound() const;
	NEWB_INT SetSize(NEWB_INT nNewSize, NEWB_INT nGrowBy = -1);
	NEWB_INT GetCapacity() const;
	NEWB_INT GetFreeItems() const;

// Operations
	// Clean up
	NEWB_VOID FreeExtra();
	NEWB_VOID RemoveAll();

	// Accessing elements
	const TYPE& GetAt(NEWB_INT nIndex) const;
	TYPE& GetAt(NEWB_INT nIndex);
	NEWB_VOID SetAt(NEWB_INT nIndex, ARG_TYPE newElement);
	const TYPE& ElementAt(NEWB_INT nIndex) const;
	TYPE& ElementAt(NEWB_INT nIndex);

	// Direct Access to the element data (may return NULL)
	const TYPE* GetData() const;
	TYPE* GetData();

	// Potentially growing the array
	NEWB_VOID SetAtGrow(NEWB_INT nIndex, ARG_TYPE newElement);
	NEWB_INT Add(ARG_TYPE newElement);
	NEWB_INT Append(const NewBValArray& src);
	NEWB_VOID Copy(const NewBValArray& src);

	// overloaded operator helpers
	const TYPE& operator[](NEWB_INT nIndex) const;
	TYPE& operator[](NEWB_INT nIndex);

	// Operations that move elements around
	NEWB_VOID InsertAt(NEWB_INT nIndex, ARG_TYPE newElement, NEWB_INT nCount = 1);
	NEWB_VOID RemoveAt(NEWB_INT nIndex, NEWB_INT nCount = 1);
	NEWB_VOID InsertAt(NEWB_INT nStartIndex, NewBValArray* pNewArray);

// Implementation
protected:
	TYPE* m_pData;   // the actual array of data
	NEWB_INT m_nSize;     // # of elements (upperBound - 1)
	NEWB_INT m_nMaxSize;  // max allocated
	NEWB_INT m_nGrowBy;   // grow amount

public:
	~NewBValArray();
};

/////////////////////////////////////////////////////////////////////////////
// NewBValArray<TYPE, ARG_TYPE> inline functions

template<class TYPE, class ARG_TYPE>
NEWB_INLINE NEWB_INT NewBValArray<TYPE, ARG_TYPE>::GetSize() const
{ 
	return m_nSize; 
}

template<class TYPE, class ARG_TYPE>
NEWB_INLINE NEWB_INT NewBValArray<TYPE, ARG_TYPE>::GetCount() const
{ 
	return m_nSize; 
}

template<class TYPE, class ARG_TYPE>
NEWB_INLINE NEWB_BOOL NewBValArray<TYPE, ARG_TYPE>::IsEmpty() const
{ 
	return m_nSize == 0; 
}

template<class TYPE, class ARG_TYPE>
NEWB_INLINE NEWB_INT NewBValArray<TYPE, ARG_TYPE>::GetUpperBound() const
{ 
	return m_nSize-1; 
}

template<class TYPE, class ARG_TYPE>
NEWB_INLINE NEWB_INT NewBValArray<TYPE, ARG_TYPE>::GetCapacity() const
{ 
	return m_nMaxSize; 
}

template<class TYPE, class ARG_TYPE>
NEWB_INLINE NEWB_INT NewBValArray<TYPE, ARG_TYPE>::GetFreeItems() const
{ 
	return m_nMaxSize - m_nSize; 
}

template<class TYPE, class ARG_TYPE>
NEWB_INLINE NEWB_VOID NewBValArray<TYPE, ARG_TYPE>::RemoveAll()
{ 
	if (m_pData != NULL)
	{
		for( int i = 0; i < m_nSize; i++ )
			(m_pData + i)->~TYPE();

//			delete[] (NEWB_BYTE*)m_pData;
//			m_pData = NULL;
	}

	m_nSize = 0;
}

template<class TYPE, class ARG_TYPE>
NEWB_INLINE TYPE& NewBValArray<TYPE, ARG_TYPE>::GetAt(NEWB_INT nIndex)
{ 
	NEWB_ASSERT(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex]; 
}

template<class TYPE, class ARG_TYPE>
NEWB_INLINE const TYPE& NewBValArray<TYPE, ARG_TYPE>::GetAt(NEWB_INT nIndex) const
{ 
	NEWB_ASSERT(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex]; 
}

template<class TYPE, class ARG_TYPE>
NEWB_INLINE NEWB_VOID NewBValArray<TYPE, ARG_TYPE>::SetAt(NEWB_INT nIndex, ARG_TYPE newElement)
{ 
	NEWB_ASSERT(nIndex >= 0 && nIndex < m_nSize);
	m_pData[nIndex] = newElement; 
}

template<class TYPE, class ARG_TYPE>
NEWB_INLINE const TYPE& NewBValArray<TYPE, ARG_TYPE>::ElementAt(NEWB_INT nIndex) const
{ 
	NEWB_ASSERT(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex]; 
}

template<class TYPE, class ARG_TYPE>
NEWB_INLINE TYPE& NewBValArray<TYPE, ARG_TYPE>::ElementAt(NEWB_INT nIndex)
{ 
	NEWB_ASSERT(nIndex >= 0 && nIndex < m_nSize);
		return m_pData[nIndex]; 
}

template<class TYPE, class ARG_TYPE>
NEWB_INLINE const TYPE* NewBValArray<TYPE, ARG_TYPE>::GetData() const
{ 
	return (const TYPE*)m_pData; 
}

template<class TYPE, class ARG_TYPE>
NEWB_INLINE TYPE* NewBValArray<TYPE, ARG_TYPE>::GetData()
{ 
	return (TYPE*)m_pData; 
}

template<class TYPE, class ARG_TYPE>
NEWB_INLINE NEWB_INT NewBValArray<TYPE, ARG_TYPE>::Add(ARG_TYPE newElement)
{ 
	NEWB_INT nIndex = m_nSize;

	SetAtGrow(nIndex, newElement);

	m_nSize ++;

	return nIndex; 
}

template<class TYPE, class ARG_TYPE>
NEWB_INLINE const TYPE& NewBValArray<TYPE, ARG_TYPE>::operator[](NEWB_INT nIndex) const
{ 
	return GetAt(nIndex); 
}

template<class TYPE, class ARG_TYPE>
NEWB_INLINE TYPE& NewBValArray<TYPE, ARG_TYPE>::operator[](NEWB_INT nIndex)
{ 
	return ElementAt(nIndex); 
}

/////////////////////////////////////////////////////////////////////////////
// NewBValArray<TYPE, ARG_TYPE> out-of-line functions

template<class TYPE, class ARG_TYPE>
NewBValArray<TYPE, ARG_TYPE>::NewBValArray()
{
	m_pData = NULL;
	m_nSize = m_nMaxSize = m_nGrowBy = 0;
}

template<class TYPE, class ARG_TYPE>
NewBValArray<TYPE, ARG_TYPE>::NewBValArray(NEWB_INT nMaxSize)
{
	m_pData = NULL;
	m_nSize = m_nGrowBy = 0;
	m_nMaxSize = nMaxSize;

	// create buffer big enough to hold number of requested elements or
	// m_nGrowBy elements, whichever is larger.
#ifdef SIZE_T_MAX
		NEWB_ASSERT(m_nMaxSize <= SIZE_T_MAX/sizeof(TYPE));    // no overflow
#endif
	m_pData = (TYPE*) new NEWB_BYTE[(size_t)m_nMaxSize * sizeof(TYPE)];
	memset((NEWB_VOID*)m_pData, 0, (size_t)m_nMaxSize * sizeof(TYPE));
}

template<class TYPE, class ARG_TYPE>
NewBValArray<TYPE, ARG_TYPE>::~NewBValArray()
{
	NEWB_ASSERT_VALID(this);

	if (m_pData != NULL)
	{
		for( int i = 0; i < m_nSize; i++ )
			(m_pData + i)->~TYPE();
//			delete ((NEWB_BYTE*)m_pData) (TYPE*)(m_pData + i);
		delete[] (NEWB_BYTE*)m_pData;
	}
}

template<class TYPE, class ARG_TYPE>
NEWB_INT NewBValArray<TYPE, ARG_TYPE>::SetSize(NEWB_INT nNewSize, NEWB_INT nGrowBy)
{
	NEWB_ASSERT_VALID(this);
	NEWB_ASSERT(nNewSize >= 0);

	NEWB_INT i = 0;// iterator

	NEWB_INT nOldSize = m_nSize;
	

	if (nGrowBy != -1)
		m_nGrowBy = nGrowBy;  // set new size

	if (nNewSize == 0) // Array now contains 0 elements
	{
	//  [3/15/2002]
	//	Remove all "allocate" object but not destroy the main memory

		if (m_pData != NULL)
		{
			// Effective call destructor of each elements
			// i.e counterpart of placement new.
			for(i = 0; i < m_nSize; i++ )
				(m_pData + i)->~TYPE(); 
		}

		m_nSize = 0;
	}
	else if (m_pData == NULL)
	{
		//  [3/15/2002]
		//	Call SetSize() after create object using default constructor
		//  i.e no preserved memory
#ifdef SIZE_T_MAX
		NEWB_ASSERT(nNewSize <= SIZE_T_MAX/sizeof(TYPE));    // no overflow
#endif
		size_t nAllocSize = max(nNewSize, m_nGrowBy);

		//  [3/15/2002]
		//  Really allocate memory to m_pData
		m_pData = (TYPE*) new NEWB_BYTE[(size_t)nAllocSize * sizeof(TYPE)];
		memset((NEWB_VOID*)m_pData, 0, (size_t)nAllocSize * sizeof(TYPE));

		//  [3/15/2002]
		//  Call placement new to "construct" elements
		for(i = 0; i < nNewSize; i++ )
			::new( (NEWB_VOID*)( m_pData + i ) ) TYPE;

		m_nSize = nNewSize;
		m_nMaxSize = nAllocSize;

	}
	else if (nNewSize <= m_nMaxSize)
	{
		// The new size is fits current allocated pool.
		if (nNewSize > m_nSize)
		{
			// initialize the new elements
			memset((NEWB_VOID*)(m_pData + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));

			for(i = 0; i < nNewSize-m_nSize; i++ )
				::new( (NEWB_VOID*)( m_pData + m_nSize + i ) ) (TYPE);
		}
		else if (m_nSize > nNewSize)
		{
			// Need to truncate array -> destroy the old elements
			for(i = 0; i < m_nSize-nNewSize; i++ )
				(m_pData + nNewSize + i)->~TYPE();
		}

		m_nSize = nNewSize;
	}
	else // nNewSize > m_nMaxSize
	{
		// Need to allocate a larger pool -> bad things here

		nGrowBy = m_nGrowBy;

		//  [3/15/2002]
		// Calculate m_nGrowBy
		if (nGrowBy == 0)
		{
			// heuristically determine growth when nGrowBy == 0
			//  (this avoids heap fragmentation in many situations)
			nGrowBy = m_nSize / 8;
			nGrowBy = (nGrowBy < 4) ? 4 : ((nGrowBy > 1024) ? 1024 : nGrowBy);
		}

		//  [3/15/2002]
		//  Calculate new size in bytes of pool
		NEWB_INT nNewMax = 0;
		if (nNewSize < m_nMaxSize + nGrowBy)
			nNewMax = m_nMaxSize + nGrowBy;  // granularity
		else
			nNewMax = nNewSize;  // no slush

		NEWB_ASSERT(nNewMax >= m_nMaxSize);  // no wrap around
#ifdef SIZE_T_MAX
		NEWB_ASSERT(nNewMax <= SIZE_T_MAX/sizeof(TYPE)); // no overflow
#endif
		//  [3/15/2002]
		//  Allocate a new memory pool has enough size
		TYPE* pNewData = (TYPE*) new NEWB_BYTE[(size_t)nNewMax * sizeof(TYPE)];

		// copy new data from old pool
		memcpy(pNewData, m_pData, (size_t)m_nSize * sizeof(TYPE));

		// construct remaining elements by calling placement new
		NEWB_ASSERT(nNewSize > m_nSize);
		memset((NEWB_VOID*)(pNewData + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));

		for( int i = 0; i < nNewSize-m_nSize; i++ )
			::new( (NEWB_VOID*)( pNewData + m_nSize + i ) ) TYPE;

		// get rid of old stuff (note: no destructors called)
		delete[] (NEWB_BYTE*)m_pData;
		m_pData = pNewData;
		m_nSize = nNewSize;
		m_nMaxSize = nNewMax;
	}

	return nOldSize;
}

template<class TYPE, class ARG_TYPE>
NEWB_INT NewBValArray<TYPE, ARG_TYPE>::Append(const NewBValArray& src)
{
	NEWB_ASSERT_VALID(this);
	NEWB_ASSERT(this != &src);   // cannot append to itself

	NEWB_INT nOldSize = m_nSize;
	SetSize(m_nSize + src.m_nSize);
	CopyElements<TYPE>(m_pData + nOldSize, src.m_pData, src.m_nSize);
	return nOldSize;
}

template<class TYPE, class ARG_TYPE>
NEWB_VOID NewBValArray<TYPE, ARG_TYPE>::Copy(const NewBValArray& src)
{
	NEWB_ASSERT_VALID(this);
	NEWB_ASSERT(this != &src);   // cannot append to itself

	SetSize(src.m_nSize);
	CopyElements<TYPE>(m_pData, src.m_pData, src.m_nSize);
}

template<class TYPE, class ARG_TYPE>
NEWB_VOID NewBValArray<TYPE, ARG_TYPE>::FreeExtra()
{
	NEWB_ASSERT_VALID(this);

	if (m_nSize != m_nMaxSize)
	{
		// shrink to desired size
#ifdef SIZE_T_MAX
		NEWB_ASSERT(m_nSize <= SIZE_T_MAX/sizeof(TYPE)); // no overflow
#endif
		TYPE* pNewData = NULL;
		if (m_nSize != 0)
		{
			pNewData = (TYPE*) new NEWB_BYTE[m_nSize * sizeof(TYPE)];
			// copy new data from old
			memcpy(pNewData, m_pData, m_nSize * sizeof(TYPE));
		}

		// get rid of old stuff (note: no destructors called)
		delete[] (NEWB_BYTE*)m_pData;
		m_pData = pNewData;
		m_nMaxSize = m_nSize;
	}
}

template<class TYPE, class ARG_TYPE>
NEWB_VOID NewBValArray<TYPE, ARG_TYPE>::SetAtGrow(NEWB_INT nIndex, ARG_TYPE newElement)
{
	NEWB_ASSERT_VALID(this);
	NEWB_ASSERT(nIndex >= 0);

	if (nIndex >= m_nMaxSize)
		SetSize(nIndex+1, -1); // Need to grow. Bad!!!!

	::new( (NEWB_VOID*)( m_pData + nIndex ) ) TYPE;

	m_pData[nIndex] = newElement;
}

template<class TYPE, class ARG_TYPE>
NEWB_VOID NewBValArray<TYPE, ARG_TYPE>::InsertAt(NEWB_INT nIndex, ARG_TYPE newElement, NEWB_INT nCount /*=1*/)
{
	NEWB_ASSERT_VALID(this);
	NEWB_ASSERT(nIndex >= 0);    // will expand to meet need
	NEWB_ASSERT(nCount > 0);     // zero or negative size not allowed
	
	int i = 0;

	//  [3/15/2002] 
	//  Insert at a position outside current upperbound of elements array
	if (nIndex >= m_nSize)
	{
		// adding after the end of the array
		SetSize(nIndex + nCount, -1);   // grow so nIndex is valid
	}
	else
	{
		// inserting in the middle of the array
		NEWB_INT nOldSize = m_nSize;
		SetSize(m_nSize + nCount, -1);  // grow it to new element size

		// destroy intial data before copying over it
		for( i = 0; i < nCount; i++ )
			(m_pData + nOldSize + i)->~TYPE();

		// shift old data up to fill gap
		memmove(m_pData + nIndex + nCount, m_pData + nIndex,
			(nOldSize-nIndex) * sizeof(TYPE));

		// re-init slots we copied from
		memset((NEWB_VOID*)(m_pData + nIndex), 0, (size_t)nCount * sizeof(TYPE));

		for( i = 0; i < nCount; i++ )
			::new( (NEWB_VOID*)( m_pData + nIndex + i ) ) TYPE;
	}

	// insert new value in the gap
	NEWB_ASSERT(nIndex + nCount <= m_nSize);

	while (nCount--)
		m_pData[nIndex++] = newElement;
}

template<class TYPE, class ARG_TYPE>
NEWB_VOID NewBValArray<TYPE, ARG_TYPE>::RemoveAt(NEWB_INT nIndex, NEWB_INT nCount)
{
	NEWB_ASSERT_VALID(this);
	NEWB_ASSERT(nIndex >= 0);
	NEWB_ASSERT(nCount >= 0);
	NEWB_ASSERT(nIndex + nCount <= m_nSize);

	// just remove a range
	NEWB_INT nMoveCount = m_nSize - (nIndex + nCount);

	for( int i = 0; i < nCount; i++ )
		(m_pData + nIndex + i)->~TYPE();

	if (nMoveCount)
		memmove( m_pData + nIndex, m_pData + nIndex + nCount,
			(size_t)nMoveCount * sizeof(TYPE));

	m_nSize -= nCount;
}

template<class TYPE, class ARG_TYPE>
NEWB_VOID NewBValArray<TYPE, ARG_TYPE>::InsertAt(NEWB_INT nStartIndex, NewBValArray* pNewArray)
{
	NEWB_ASSERT_VALID(this);
	NEWB_ASSERT(pNewArray != NULL);
	NEWB_ASSERT_VALID(pNewArray);
	NEWB_ASSERT(nStartIndex >= 0);

	if (pNewArray->GetSize() > 0)
	{
		InsertAt(nStartIndex, pNewArray->GetAt(0), pNewArray->GetSize());
		for (NEWB_INT i = 0; i < pNewArray->GetSize(); i++)
			SetAt(nStartIndex + i, pNewArray->GetAt(i));
	}
}

#if defined(SUPPORT_PUSH_MACRO)
#pragma pop_macro("new")
#endif

#endif __NEWB_VAL_ARRAY_H__
