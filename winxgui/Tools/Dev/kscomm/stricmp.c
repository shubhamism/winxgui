/***
*stricmp.c - contains case-insensitive string comp routine _stricmp/_strcmpi
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       contains _stricmp(), also known as _strcmpi()
*
*******************************************************************************/

#include "stdafx.h"

/***
*int _stricmp(dst, src), _strcmpi(dst, src) - compare strings, ignore case
*
*Purpose:
*       _stricmp/_strcmpi perform a case-insensitive string comparision.
*       For differences, upper case letters are mapped to lower case.
*       Thus, "abc_" < "ABCD" since "_" < "d".
*
*Entry:
*       char *dst, *src - strings to compare
*
*Return:
*       <0 if dst < src
*        0 if dst = src
*       >0 if dst > src
*
*Exceptions:
*
*******************************************************************************/

#undef StrCmpI

STDMETHODIMP_(int) StrCmpI(LPCTSTR dst, LPCTSTR src)
{
    int f,l;
    do {
        if (((f = (unsigned char)(*(dst++))) >= 'A') && (f <= 'Z'))
        {
			f -= ('A' - 'a');
		}
        if (((l = (unsigned char)(*(src++))) >= 'A') && (l <= 'Z'))
        {
			l -= ('A' - 'a');
		}
	}
	while ( f && (f == l) );
    return(f - l);
}
