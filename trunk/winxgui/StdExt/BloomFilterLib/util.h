/*
 *  util.h
 *
 *	Copyright (C) 2007
 *	Ωπ√» <jimmyjiao@gmail.com>
 *	All Rights Reserved
 *
 *************************************************************************
 *
 *  Description:
 *      This file defines the prototypes of some utility functions.
 *      Please read the file util.c for more information.
 *
 °¡  History:
 *      Created, Ωπ√»<jimmyjiao@gmail.com>, 2007/05/11
 *
 */

#ifndef _UTIL_H_
#define _UTIL_H_

#define SHA1BITS 160  /* sha-1 hash value is of 160 bits long */

/*
 *  Function Prototypes
 */
int PowerOfTwo(unsigned);
int GenerateHashAddress(const unsigned char *, unsigned, 
						unsigned, char, unsigned *);
unsigned GetBits(unsigned *, unsigned, unsigned);
void SetBits(unsigned *, unsigned, unsigned, unsigned);

#endif