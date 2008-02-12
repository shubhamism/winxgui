/*
 *  util.c
 *
 *	Copyright (C) 2007
 *	Ωπ√» <jimmyjiao@gmail.com>
 *	All Rights Reserved
 *
 *************************************************************************
 *
 *  Description:
 *      This file implements some utility functions.
 *
 °¡  History:
 *      Created, Ωπ√»<jimmyjiao@gmail.com>, 2007/05/11
 *
 */

#include <math.h>
#include <malloc.h>
#include <memory.h>
#include "util.h"
#include "sha1.h"

/*  
 *  PowerOfTwo
 *
 *  Description:
 *      This function will check whether the specified
 *      value is power of 2.
 *
 *  Parameters:
 *      val: [in]
 *          The value to be checked.
 *
 *  Returns:
 *      1 if the value is power of 2, otherwise 0.
 *
 *  Comments:
 *
 */
int PowerOfTwo(unsigned val)
{
	return !(val & (val - 1));
}

/*  
 *  Log2
 *
 *  Description:
 *      This function will calculate the logarithm (base 2) 
 *      of the specified value if it is a power of 2.
 *
 *  Parameters:
 *      val: [in]
 *          The value whose logarithm (base 2) is calculated.
 *
 *  Returns:
 *      If the value is a power of 2, return the logarithm 
 *      (base 2) of it; otherwise return -1.
 *
 *  Comments:
 *
 */
int Log2(unsigned val)
{
	int i = 0;
	if (!PowerOfTwo(val))
		return -1;
	do
	{
		val = val >> 1;
		i++;
	} while (val != 0);
	return i - 1;
}

/*  
 *  GetBits
 *
 *  Description:
 *      This function will retrieve a snippet of bits from 
 *      a given bit string.
 *
 *  Parameters:
 *      data: [in]
 *          The given bit string.
 *      start: [in]
 *          The start position of the bit snippet.
 *      length: [in]
 *          The length of the bit snippet.
 *
 *  Returns:
 *      A snippet of bits from the specified bit string.
 *
 *  Comments:
 *
 */
unsigned GetBits(unsigned *data, unsigned start, unsigned length)
{
	unsigned usize = sizeof(unsigned) * 8;
	unsigned n = start / usize;
	unsigned offset = start % usize;
	data += n;
	if (offset + length <= usize)  /* within one unsigned integer */
		return (data[0] << offset) >> (usize - length);
	else                          /* across two unsigned integer */
	{
		unsigned lowerBits = (data[0] << offset) >> offset;
		unsigned overflowBits = length - (usize - offset);
		lowerBits = lowerBits << overflowBits;
		return lowerBits | (data[1] >> (usize - overflowBits));
	}
}

/*  
 *  SetBits
 *
 *  Description:
 *      This function will change a snippet of bits in 
 *      a given bit string.
 *
 *  Parameters:
 *      data: [in/out]
 *          The given bit string to be changed.
 *      start: [in]
 *          The start position of the bit snippet to be changed.
 *      length: [in]
 *          The length of the bit snippet to be changed.
 *      value: [in]
 *          The new value to be set to the bit snippet.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *
 */
void SetBits(unsigned *data, unsigned start, unsigned length, unsigned value)
{
	unsigned newVal;
	unsigned usize = sizeof(unsigned) * 8;
	unsigned n = start / usize;
	unsigned offset = start % usize;
	data += n;
	newVal = *data;
	if (offset + length <= usize)  /* within one unsigned integer */
	{
		unsigned mask = -1;                           /* FFFFFFFF        */
		mask = ((mask << offset) >> (usize - length)) 
			<< (usize - length - offset);             /* 0...01...10...0 */
		newVal = newVal & (~mask);                    /* X...X0...0X...X */
		*data = newVal | (value << (usize - offset - length));
	}
	else                          /* across two unsigned integer */
	{
		/*
		 °¡ set lower bits of the first unsigned integer
		 */
		unsigned lowerBits = usize - offset;
		unsigned overflowBits = length - lowerBits;
		newVal = (newVal >> lowerBits) << lowerBits;  /* X...X0...0 */
		*data = newVal | (value >> overflowBits);

		/*
		 °¡ set higher bits of the second unsigned integer
		 */
		data++;
		newVal = *data;
		newVal = (newVal << overflowBits) >> overflowBits;  /* 0...0X...X */
		*data = newVal | (value << (usize - overflowBits));
	}
}

/*  
 *  GenerateHashSequence
 *
 *  Description:
 *      This function will generate a bit sequence used for
 *      k hash addresses.
 *
 *  Parameters:
 *      element: [in]
 *          The element to be hashed.
 *      length: [in]
 *          The bytes of the element.
 *      hashTimes: [in]
 *          The number of SHA-1 hashes needed.
 *      hashSequence: [in/out]
 *          The bit sequence to be generated.
 *
 *  Returns:
 *      1 if successful, 0 if it failed.
 *
 *  Comments:
 *
 */
int GenerateHashSequence(const unsigned char *element, unsigned length,
						 int hashTimes, unsigned *hashSequence)
{
	int i, j;
	SHA1Context context;

	/*
	 °¡ If one SHA-1 hash does not suffice, we repeat the element
	 * and concatenate it to the original element as new SHA-1 
	 * input to generate new hashes. For example, if we need to 
	 * hash 3 times and the element is 'a', the hash inputs are
	 * 'a', 'aa' and 'aaa'.
	 */
	for (i = 1; i <= hashTimes; i++)
	{
		SHA1Reset(&context);
		for (j = 0; j < i; j++)  /* i represents the repeat times */
			SHA1Input(&context, element, length);
		if (!SHA1Result(&context))
			return 0;
		memcpy(hashSequence, context.Message_Digest, SHA1BITS / 8);
		hashSequence += 5;
	}
	
	return 1;
}

/*  
 *  GenerateHashAddress
 *
 *  Description:
 *      This function will generate k hash addresses.
 *
 *  Parameters:
 *      element: [in]
 *          The element to be hashed.
 *      length: [in]
 *          The bytes of the element.
 *      bitArraySize: [in]
 *          The hash range.
 *      hashNum: [in]
 *          The number of hash addresses.
 *      hashAddress: [in/out]
 *          The k hash addresses to be generated.
 *
 *  Returns:
 *      1 if successful, 0 if it failed.
 *
 *  Comments:
 *
 */
int GenerateHashAddress(const unsigned char *element,
						unsigned length,
						unsigned bitArraySize,
						char hashNum,
						unsigned *hashAddress)
{
	unsigned *hashSequence, offset = 0;
	int addressBits = Log2(bitArraySize), hashTimes;
	if (addressBits == -1)
		return 0;

	/*
	 * Generate a bit sequence containing k hash addresses.
	 */
	hashTimes = (int)ceil((double)(addressBits * hashNum) / SHA1BITS);
	hashSequence = (unsigned *)malloc(SHA1BITS * hashTimes);
	if (!GenerateHashSequence(element, length, hashTimes, hashSequence))
	{
		free(hashSequence);
		return 0;
	}

	/*
	 * Read k hash addresses from the bit sequence.
	 */
	while (hashNum > 0)
	{
		*(hashAddress++) = GetBits(hashSequence, offset, addressBits);
		offset += addressBits;
		hashNum--;
	}

	free(hashSequence);
	return 1;
}