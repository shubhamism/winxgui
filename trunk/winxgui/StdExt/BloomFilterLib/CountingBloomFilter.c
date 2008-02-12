/*
 *  CountingBloomFilter.c
 *
 *	Copyright (C) 2007
 *	Ωπ√» <jimmyjiao@gmail.com>
 *	All Rights Reserved
 *
 *************************************************************************
 *
 *  Description:
 *      This file implements the counting bloom filter, including 
 *      create and destroy, insert and delete, membership and 
 *      multiplicity query operations.
 *
 °¡  History:
 *      Created, Ωπ√»<jimmyjiao@gmail.com>, 2007/05/13
 *
 */

#include <math.h>
#include <stdlib.h>
#include "CountingBloomFilter.h"
#include "util.h"

/*  
 *  CBFInit
 *
 *  Description:
 *      This function will initialize a counting bloom filter.
 *
 *  Parameters:
 *      cbf: [in/out]
 *          The counting bloom filter to be initialized.
 *      length: [in]
 *          The number of counters.
 *      counterSize: [in]
 *          The counter size in bits.
 *      hashNum: [in]
 *          The hash function number.
 *
 *  Returns:
 *      1 if successful, 0 if it failed.
 *
 *  Comments:
 *
 */
int CBFInit(CountingBloomFilter *cbf, unsigned length, 
			unsigned counterSize, char hashNum)
{
	if (length == 0 || !PowerOfTwo(length))  /* length must be power of 2 */
		return 0;

	/* 
	 * use calloc instead of malloc in order to  
	 * initialize the counter array to all 0s
	 */
	if (length < 8)
		length = 8;
	cbf->Counter_Array = (char *)calloc(length / 8 * counterSize, 1);
	cbf->Length = length;
	cbf->Counter_Size = counterSize;
	cbf->Hash_Num = hashNum;
	return 1;
}

/*  
 *  CBFDestroy
 *
 *  Description:
 *      This function will destroy the specified counting bloom filter.
 *
 *  Parameters:
 *      cbf: [in/out]
 *          The counting bloom filter to be destroyed.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *
 */
void CBFDestroy(CountingBloomFilter *cbf)
{
	cbf->Counter_Size = 0;
	cbf->Hash_Num = 0;
	cbf->Length = 0;
	free(cbf->Counter_Array);
}

/*  
 *  CBFInsert
 *
 *  Description:
 *      This function will insert a specified element into
 *      the specified counting bloom filter.
 *
 *  Parameters:
 *      cbf: [in/out]
 *          The counting bloom filter into which the element is inserted.
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
int CBFInsert(CountingBloomFilter *cbf, const unsigned char *element, unsigned length)
{
	char i;
	unsigned *hashAddress;
	unsigned counter, overflow = 0;
	unsigned counterMax = (1 << cbf->Counter_Size) - 1;  /* maximum of a counter */

	/*
	 * generate k hash addresses
	 */
	hashAddress = (unsigned *)malloc(sizeof(unsigned) * cbf->Hash_Num);
	if (!GenerateHashAddress(element, length, cbf->Length, cbf->Hash_Num, hashAddress))
	{
		free(hashAddress);
		return 0;
	}

	/*
	 * increase the corresponding k counters
	 */
	for (i = 0; i < cbf->Hash_Num; i++)
	{
		counter = GetBits((unsigned *)cbf->Counter_Array, 
			              hashAddress[i] * cbf->Counter_Size, 
			              cbf->Counter_Size);
		if (counter == counterMax)  /* counter overflow */
		{
			overflow = 1;
			continue;
		}
		SetBits((unsigned *)cbf->Counter_Array, 
			    hashAddress[i] * cbf->Counter_Size, 
		        cbf->Counter_Size, counter + 1);
	}

	/*
	 * If any of the k counters overflows, we restore the other 
	 * non-overflow counters and return 0.
	 */
	if (overflow)
	{
		for (i = 0; i < cbf->Hash_Num; i++)
		{
			counter = GetBits((unsigned *)cbf->Counter_Array, 
				              hashAddress[i] * cbf->Counter_Size, 
					          cbf->Counter_Size);
			if (counter == counterMax)
				continue;
			SetBits((unsigned *)cbf->Counter_Array, 
				    hashAddress[i] * cbf->Counter_Size, 
					cbf->Counter_Size, counter - 1);
		}
	}

	free(hashAddress);
	return !overflow;
}

/*  
 *  CBFDelete
 *
 *  Description:
 *      This function will delete a specified element from
 *      the specified counting bloom filter.
 *
 *  Parameters:
 *      cbf: [in/out]
 *          The counting bloom filter from which the element is deleted.
 *      element: [in]
 *          The element to be deleted.
 *      length: [in]
 *          The bytes of the element.
 *
 *  Returns:
 *      1 if the deletion is successful, otherwise 0.
 *
 *  Comments:
 *
 */
int CBFDelete(CountingBloomFilter *cbf, const unsigned char *element, unsigned length)
{
	char i;
	unsigned counter, error = 0;

	/*
	 * generate k hash addresses
	 */
	unsigned *hashAddress = (unsigned *)malloc(sizeof(unsigned) * cbf->Hash_Num);
	if (!GenerateHashAddress(element, length, cbf->Length, cbf->Hash_Num, hashAddress))
	{
		free(hashAddress);
		return 0;
	}

	/*
	 * decrease the corresponding k counters
	 */
	for (i = 0; i < cbf->Hash_Num; i++)
	{
		counter = GetBits((unsigned *)cbf->Counter_Array, 
			              hashAddress[i] * cbf->Counter_Size, 
			              cbf->Counter_Size);
		if (counter == 0)
		{
			error = 1;
			continue;
		}
		SetBits((unsigned *)cbf->Counter_Array, 
			    hashAddress[i] * cbf->Counter_Size, 
		        cbf->Counter_Size, counter - 1);
	}

	/*
	 * If any of the k counters is 0, we restore the other 
	 * non-zero counters and return 0.
	 */
	if (error)
	{
		for (i = 0; i < cbf->Hash_Num; i++)
		{
			counter = GetBits((unsigned *)cbf->Counter_Array, 
				              hashAddress[i] * cbf->Counter_Size, 
					          cbf->Counter_Size);
			if (counter == 0)
				continue;
			SetBits((unsigned *)cbf->Counter_Array, 
				    hashAddress[i] * cbf->Counter_Size, 
					cbf->Counter_Size, counter + 1);
		}
	}

	free(hashAddress);
	return !error;
}

/*  
 *  CBFMembershipQuery
 *
 *  Description:
 *      This function will query whether a specified element 
 *      is a member of the set represented by the specified 
 *      counting bloom filter.
 *
 *  Parameters:
 *      cbf: [in]
 *          The counting bloom filter on which the query is done.
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
int CBFMembershipQuery(CountingBloomFilter *cbf, const unsigned char *element, 
					   unsigned length)
{
	char i;
	int result = 1;

	/*
	 * generate k hash addresses
	 */
	unsigned *hashAddress = (unsigned *)malloc(sizeof(unsigned) * cbf->Hash_Num);
	if (!GenerateHashAddress(element, length, cbf->Length, cbf->Hash_Num, hashAddress))
	{
		free(hashAddress);
		return 0;
	}

	/*
	 * check the counter in each hash position
	 */
	for (i = 0; i < cbf->Hash_Num; i++)
	{
		if (!GetBits((unsigned *)cbf->Counter_Array, 
			         hashAddress[i] * cbf->Counter_Size, 
					 cbf->Counter_Size))
		{
			result = 0;
			break;
		}
	}

	free(hashAddress);
	return result;
}

/*  
 *  CBFMultiplicityQuery
 *
 *  Description:
 *      This function will query the multiplicity of a specified
 *      element in the multi-set represented by the specified 
 *      counting bloom filter.
 *
 *  Parameters:
 *      cbf: [in]
 *          The counting bloom filter on which the query is done.
 *      element: [in]
 *          The element whose multiplicity is to be queried.
 *      length: [in]
 *          The bytes of the element.
 *
 *  Returns:
 *      The multiplicity of the specified element.
 *
 *  Comments:
 *      This function can be called only when the counting bloom
 *      filter is used to represent a multi-set.
 *
 */
unsigned CBFMultiplicityQuery(CountingBloomFilter *cbf, 
							  const unsigned char *element, unsigned length)
{
	char i;
	unsigned counter;
	unsigned min = -1;  /* FFFFFFFF */

	/*
	 * generate k hash addresses
	 */
	unsigned *hashAddress = (unsigned *)malloc(sizeof(unsigned) * cbf->Hash_Num);
	if (!GenerateHashAddress(element, length, cbf->Length, cbf->Hash_Num, hashAddress))
	{
		free(hashAddress);
		return 0;
	}

	/*
	 * find the minimum of the k corresponding counters
	 */
	for (i = 0; i < cbf->Hash_Num; i++)
	{
		counter = GetBits((unsigned *)cbf->Counter_Array, 
			              hashAddress[i] * cbf->Counter_Size, 
					      cbf->Counter_Size);
		if (counter < min)
			min = counter;
	}

	free(hashAddress);
	return min;
}