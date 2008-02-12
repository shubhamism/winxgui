/*
 *  CountingBloomFilter.h
 *
 *	Copyright (C) 2007
 *	Ωπ√» <jimmyjiao@gmail.com>
 *	All Rights Reserved
 *
 *************************************************************************
 *
 *  Description:
 *      This file defines the interface of the counting bloom filter.
 *      Please read the file CountingBloomFilter.c for more information.
 *
 °¡  History:
 *      Created, Ωπ√»<jimmyjiao@gmail.com>, 2007/05/13
 *
 */

#ifndef _COUNTINGBLOOMFILTER_H_
#define _COUNTINGBLOOMFILTER_H_

typedef struct CountingBloomFilter
{
	char *Counter_Array;    /* the counter array            */
	unsigned Length;        /* the length of counter array  */
	unsigned Counter_Size;  /* the counter size             */
	char Hash_Num;          /* the number of hash functions */
} CountingBloomFilter;

/*
 *  Function Prototypes
 */
int CBFInit(CountingBloomFilter *, unsigned, unsigned, char);
int CBFInsert(CountingBloomFilter *, const unsigned char *, unsigned);
int CBFDelete(CountingBloomFilter *, const unsigned char *, unsigned);
int CBFMembershipQuery(CountingBloomFilter *, const unsigned char *, unsigned);
unsigned CBFMultiplicityQuery(CountingBloomFilter *, const unsigned char *, unsigned);
void CBFDestroy(CountingBloomFilter *);

#endif