/*
 *  DynamicCountFilter.h
 *
 *	Copyright (C) 2007
 *	Ωπ√» <jimmyjiao@gmail.com>
 *	All Rights Reserved
 *
 *************************************************************************
 *
 *  Description:
 *      This file defines the interface of the dynamic count filter.
 *      Please read the file DynamicCountFilter.c for more information.
 *
 °¡  History:
 *      Created, Ωπ√»<jimmyjiao@gmail.com>, 2007/05/13
 *
 */

#ifndef _DYNAMICCOUNTFILTER_H_
#define _DYNAMICCOUNTFILTER_H_

typedef struct Counter_Level_Item
{
	unsigned Below_Threshold;  /* number of counters below threshold            */
	unsigned Above_Threshold;  /* number of counters greater or equal threshold */
} Counter_Level_Item;

typedef struct DynamicCountFilter
{
	char *CBFV;                         /* counting bloom filter vector */
	char *OFV;                          /* overflow vector              */
	unsigned CBFV_Counter_Size;         /* the counter size of CBFV     */
	unsigned OFV_Counter_Size;          /* the counter size of  OFV     */
	unsigned Length;                    /* the length of CBFV and OFV   */
	char Hash_Num;                      /* the number of hash functions */
	double Lambda;                      /* adjust the rebuild threshold */
	Counter_Level_Item *Counter_Level;  /* the Counter Level structure  */
} DynamicCountFilter;

/*
 *  Function Prototypes
 */
int DCFInit(DynamicCountFilter *, unsigned, unsigned, char, double);
int DCFInsert(DynamicCountFilter *, const unsigned char *, unsigned);
int DCFDelete(DynamicCountFilter *, const unsigned char *, unsigned);
int DCFMembershipQuery(DynamicCountFilter *, const unsigned char *, unsigned);
unsigned DCFMultiplicityQuery(DynamicCountFilter *, const unsigned char *, unsigned);
void DCFDestroy(DynamicCountFilter *);

#endif