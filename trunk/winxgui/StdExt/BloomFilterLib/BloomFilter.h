/*
 *  BloomFilter.h
 *
 *	Copyright (C) 2007
 *	Ωπ√» <jimmyjiao@gmail.com>
 *	All Rights Reserved
 *
 *************************************************************************
 *
 *  Description:
 *      This file defines the interface of the bloom filter.
 *      Please read the file BloomFilter.c for more information.
 *
 °¡  History:
 *      Created, Ωπ√»<jimmyjiao@gmail.com>, 2007/05/11
 *
 */

#ifndef _BLOOMFILTER_H_
#define _BLOOMFILTER_H_

typedef struct BloomFilter
{
	char *Bit_Array;  /* the bit array                     */
	unsigned Length;  /* the length (in bits) of bit array */
	char Hash_Num;    /* the number of hash functions      */
} BloomFilter;

/*
 *  Function Prototypes
 */
int BFInit(BloomFilter *, unsigned, char);
int BFMembershipQuery(BloomFilter *, const unsigned char *, unsigned);
int BFInsert(BloomFilter *, const unsigned char *, unsigned);
void BFDestroy(BloomFilter *);

#endif