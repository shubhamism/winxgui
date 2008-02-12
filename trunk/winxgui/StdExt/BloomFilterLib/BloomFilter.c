/*
 *  BloomFilter.c
 *
 *	Copyright (C) 2007
 *	Ωπ√» <jimmyjiao@gmail.com>
 *	All Rights Reserved
 *
 *************************************************************************
 *
 *  Description:
 *      This file implements the bloom filter, including 
 *      create, insert and query operations.
 *
 °¡  History:
 *      Created, Ωπ√»<jimmyjiao@gmail.com>, 2007/05/11
 *
 */

#include <stdlib.h>
#include "BloomFilter.h"
#include "util.h"

/*  
 *  BFInit
 *
 *  Description:
 *      This function will initialize a bloom filter with specified
 *      bit array size and hash function number.
 *
 *  Parameters:
 *      bf: [in/out]
 *          The bloom filter to be initialized.
 *      m: [in]
 *          The bit array size in bits.
 *      k: [in]
 *          The hash function number.
 *
 *  Returns:
 *      1 if successful, 0 if it failed.
 *
 *  Comments:
 *
 */
int BFInit(BloomFilter *bf, unsigned m, char k)
{
	if (m == 0 || !PowerOfTwo(m))  /* m must be power of 2 */
		return 0;

	/* 
	 * use calloc instead of malloc in order to  
	 * initialize the bit array to all 0s
	 */
	if (m < 8)
		m = 8;
	bf->Bit_Array = (char *)calloc(m/8, 1);
	bf->Length = m;
	bf->Hash_Num = k;
	return 1;
}

/*  
 *  BFDestroy
 *
 *  Description:
 *      This function will destroy the specified bloom filter.
 *
 *  Parameters:
 *      bf: [in/out]
 *          The bloom filter to be destroyed.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *
 */
void BFDestroy(BloomFilter *bf)
{
	bf->Hash_Num = 0;
	bf->Length = 0;
	free(bf->Bit_Array);
}

/*  
 *  BFMembershipQuery
 *
 *  Description:
 *      This function will query whether a specified element 
 *      is a member of the set represented by the specified 
 *      bloom filter.
 *
 *  Parameters:
 *      bf: [in]
 *          The bloom filter on which the query is done.
 *      element: [in]
 *          The element to be checked.
 *      length: [in]
 *          The bytes of the element.
 *
 *  Returns:
 *      1 if the element is a member of the set, otherwise 0.
 *
 *  Comments:
 *
 */
int BFMembershipQuery(BloomFilter *bf, const unsigned char *element, unsigned length)
{
	int result = 1, i;

	/*
	 * generate k hash addresses
	 */
	unsigned *hashAddress = (unsigned *)malloc(sizeof(unsigned) * bf->Hash_Num);
	if (!GenerateHashAddress(element, length, bf->Length, bf->Hash_Num, hashAddress))
	{
		free(hashAddress);
		return 0;
	}

	/*
	 * check the bit in each hash address
	 */
	for (i = 0; i < bf->Hash_Num; i++)
	{
		if (!GetBits((unsigned *)bf->Bit_Array, hashAddress[i], 1))
		{
			result = 0;
			break;
		}
	}

	free(hashAddress);
	return result;
}

/*  
 *  BFInsert
 *
 *  Description:
 *      This function will insert a specified element into
 *      the specified bloom filter.
 *
 *  Parameters:
 *      bf: [in/out]
 *          The bloom filter into which the element is inserted.
 *      element: [in]
 *          The element to be inserted.
 *      length: [in]
 *          The bytes of the element.
 *
 *  Returns:
 *      1 if the insertion is successful, otherwise 0.
 *
 *  Comments:
 *
 */
int BFInsert(BloomFilter *bf, const unsigned char *element, unsigned length)
{
	int i;

	/*
	 * generate k hash addresses
	 */
	unsigned *hashAddress = (unsigned *)malloc(sizeof(unsigned) * bf->Hash_Num);
	if (!GenerateHashAddress(element, length, bf->Length, bf->Hash_Num, hashAddress))
	{
		free(hashAddress);
		return 0;
	}

	/*
	 * set the bits in k hash positions to 1
	 */
	for (i = 0; i < bf->Hash_Num; i++)
		SetBits((unsigned *)bf->Bit_Array, hashAddress[i], 1, 1);

	free(hashAddress);
	return 1;
}