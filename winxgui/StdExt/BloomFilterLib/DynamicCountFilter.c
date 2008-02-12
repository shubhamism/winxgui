/*
 *  DynamicCountFilter.c
 *
 *	Copyright (C) 2007
 *	Ωπ√» <jimmyjiao@gmail.com>
 *	All Rights Reserved
 *
 *************************************************************************
 *
 *  Description:
 *      This file implements the dynamic count filter, including 
 *      create and destroy, insert and delete, membership and 
 *      multiplicity query operations.
 *
 °¡  History:
 *      Created, Ωπ√»<jimmyjiao@gmail.com>, 2007/05/14
 *
 */

#include <math.h>
#include <stdlib.h>
#include "DynamicCountFilter.h"
#include "util.h"

/*  
 *  GetOverflowLevel
 *
 *  Description:
 *      This function will return the level of the specified OFV counter.
 *
 *  Parameters:
 *      ofvCounter: [in]
 *          The OFV counter whose level is to be returned.
 *
 *  Returns:
 *      The level of the specified OFV counter.
 *
 *  Comments:
 *
 */
int GetOverflowLevel(unsigned ofvCounter)
{
	int i = 0;
	while (ofvCounter != 0)
	{
		ofvCounter = ofvCounter >> 1;
		i++;
	}
	return i;
}

/*  
 *  GetDCFThreshold
 *
 *  Description:
 *      This function will return the threshold of a specified counter.
 *
 *  Parameters:
 *      dcf: [in]
 *          The dynamic count filter to which the specified counter belongs.
 *      counter: [in]
 *          The counter whose threshold is to be returned.
 *
 *  Returns:
 *      The threshold of a specified counter.
 *
 *  Comments:
 *
 */
double GetDCFThreshold(DynamicCountFilter *dcf, unsigned counter)
{
	int x, y, power;
	int level = GetOverflowLevel(counter >> dcf->CBFV_Counter_Size);

	/*
	 * return (2^CBFV_Counter_Size - 1) * lambda for level 0
	 */
	if (level == 0)
		return ((1 << dcf->CBFV_Counter_Size) - 1) * dcf->Lambda;

	power = dcf->CBFV_Counter_Size + level;
	x = 1 << (power - 1);  /* 2^(power - 1) */
	y = 1 << power;        /* 2^power */
	return x + (y - x) * dcf->Lambda;
}

/*  
 *  GetDCFCounter
 *
 *  Description:
 *      This function will read a counter from a specified 
 *      position in a dynamic count filter.
 *
 *  Parameters:
 *      dcf: [in]
 *          The dynamic count filter whose counter is to be read.
 *      index: [in]
 *          The index of the counter to be read.
 *
 *  Returns:
 *      The counter in the specified position.
 *
 *  Comments:
 *
 */
unsigned GetDCFCounter(DynamicCountFilter *dcf, unsigned index)
{
	unsigned ofvCounter;
	unsigned cbfvCounter = GetBits((unsigned *)dcf->CBFV, 
			                       index * dcf->CBFV_Counter_Size, 
			                       dcf->CBFV_Counter_Size);
	if (dcf->OFV == NULL)
		return cbfvCounter;

	ofvCounter = GetBits((unsigned *)dcf->OFV, 
			             index * dcf->OFV_Counter_Size, 
			             dcf->OFV_Counter_Size);
	return (ofvCounter << dcf->CBFV_Counter_Size) | cbfvCounter;
}

/*  
 *  SetDCFCounter
 *
 *  Description:
 *      This function will set new value to a counter of a 
 *      specified position in a dynamic count filter.
 *
 *  Parameters:
 *      dcf: [in]
 *          The dynamic count filter whose counter is to be set.
 *      index: [in]
 *          The index of the counter to be set.
 *      value: [in]
 *          The new counter value to be set.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *
 */
void SetDCFCounter(DynamicCountFilter *dcf, unsigned index, unsigned value)
{
	if (dcf->OFV == NULL)
		SetBits((unsigned *)dcf->CBFV, index * dcf->CBFV_Counter_Size,
			    dcf->CBFV_Counter_Size, value);
	else
	{
		unsigned usize = sizeof(unsigned) * 8;
		unsigned offset = usize - dcf->CBFV_Counter_Size;

		SetBits((unsigned *)dcf->OFV, index * dcf->OFV_Counter_Size,
			    dcf->OFV_Counter_Size, value >> dcf->CBFV_Counter_Size);
		SetBits((unsigned *)dcf->CBFV, index * dcf->CBFV_Counter_Size,
			    dcf->CBFV_Counter_Size, (value << offset) >> offset);
	}
}

/*  
 *  RebuildOFV
 *
 *  Description:
 *      This function will rebuild the overflow vector of the 
 *      specified dynamic count filter with a new counter size.
 *
 *  Parameters:
 *      dcf: [in/out]
 *          The dynamic count filter whose overflow vector is 
 *          to be rebuilt.
 *      counterSize: [in]
 *          The new counter size of the overflow vector.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *
 */
void RebuildOFV(DynamicCountFilter *dcf, unsigned counterSize)
{
	if (counterSize == 0)  /* delete OFV */
	{
		free(dcf->OFV);
		dcf->OFV = NULL;
	}
	else if (counterSize == 1 && dcf->OFV_Counter_Size == 0)  /* create OFV */
	{
		dcf->OFV = (char *)calloc(dcf->Length / 8, 1);
	}
	else  /* rebuild OFV */
	{
		unsigned i, counter;
		char *newOFV = (char *)calloc(dcf->Length / 8 * counterSize, 1);
		for (i = 0; i < dcf->Length; i++)
		{
			counter = GetBits((unsigned *)dcf->OFV, 
				              i * dcf->OFV_Counter_Size, 
							  dcf->OFV_Counter_Size);
			if (counter > 0)
				SetBits((unsigned *)newOFV, i * counterSize, 
				        counterSize, counter);
		}
		free(dcf->OFV);
		dcf->OFV = newOFV;
	}

	dcf->OFV_Counter_Size = counterSize;
}

/*  
 *  DCFInit
 *
 *  Description:
 *      This function will initialize a dynamic count filter.
 *
 *  Parameters:
 *      dcf: [in/out]
 *          The dynamic count filter to be initialized.
 *      CBFVCounterSize: [in]
 *          The counter size of the Counting Bloom Filter Vector.
 *      length: [in]
 *          The number of counters.
 *      hashNum: [in]
 *          The hash function number.
 *      lambda: [in]
 *          Used to adjust the threshold for delayed OFV shrinking.
 *          Ranges from 0 to 1.
 *
 *  Returns:
 *      1 if successful, 0 if it failed.
 *
 *  Comments:
 *
 */
int DCFInit(DynamicCountFilter *dcf, unsigned CBFVCounterSize, 
			unsigned length, char hashNum, double lambda)
{
	if (length == 0 || !PowerOfTwo(length))  /* length must be power of 2 */
		return 0;
	if (lambda > 1 || lambda < 0)            /* lambda ranges from 0 to 1 */
		return 0;

	/* 
	 * use calloc instead of malloc in order to  
	 * initialize the allocated memory to all 0s
	 */
	if (length < 8)
		length = 8;
	dcf->CBFV = (char *)calloc(length / 8 * CBFVCounterSize, 1);
	dcf->CBFV_Counter_Size = CBFVCounterSize;
	dcf->OFV = NULL;
	dcf->OFV_Counter_Size = 0;
	dcf->Length = length;
	dcf->Hash_Num = hashNum;
	dcf->Lambda = lambda;
	dcf->Counter_Level = (Counter_Level_Item *)calloc(1, sizeof(Counter_Level_Item));
	if (lambda == 0)
		dcf->Counter_Level[0].Above_Threshold = dcf->Length;
	else
		dcf->Counter_Level[0].Below_Threshold = dcf->Length;
	return 1;
}

/*  
 *  DCFDestroy
 *
 *  Description:
 *      This function will destroy the specified dynamic count filter.
 *
 *  Parameters:
 *      dcf: [in/out]
 *          The dynamic count filter to be destroyed.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *
 */
void DCFDestroy(DynamicCountFilter *dcf)
{
	free(dcf->CBFV);
	if (dcf->OFV != NULL)
		free(dcf->OFV);
	dcf->CBFV_Counter_Size = 0;
	dcf->OFV_Counter_Size = 0;
	dcf->Length = 0;
	dcf->Hash_Num = 0;
	dcf->Lambda = 0;
	free(dcf->Counter_Level);
}

/*  
 *  DCFInsert
 *
 *  Description:
 *      This function will insert a specified element into
 *      the specified dynamic count filter.
 *
 *  Parameters:
 *      dcf: [in/out]
 *          The dynamic count filter into which the element is inserted.
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
int DCFInsert(DynamicCountFilter *dcf, const unsigned char *element, unsigned length)
{
	char i;
	unsigned *hashAddress;
	unsigned counter, ofvMax, ofvCounter;
	unsigned cbfvMax = (1 << dcf->CBFV_Counter_Size) - 1;
	int oldLevel, newLevel;
	double oldThreshold, newThreshold;

	/*
	 * generate k hash addresses
	 */
	hashAddress = (unsigned *)malloc(sizeof(unsigned) * dcf->Hash_Num);
	if (!GenerateHashAddress(element, length, dcf->Length, dcf->Hash_Num, hashAddress))
	{
		free(hashAddress);
		return 0;
	}

	/*
	 * increase the corresponding k counters and update 
	 * the counter level structure
	 */
	for (i = 0; i < dcf->Hash_Num; i++)
	{
		ofvMax = (1 << dcf->OFV_Counter_Size) - 1;
		counter = GetDCFCounter(dcf, hashAddress[i]) + 1;  /* get counter value */
		ofvCounter = counter >> dcf->CBFV_Counter_Size;
		oldLevel = GetOverflowLevel((counter - 1) >> dcf->CBFV_Counter_Size);
		newLevel = GetOverflowLevel(ofvCounter);
		newThreshold = GetDCFThreshold(dcf, counter);

		/*
		 * rebuild the overflow vector and counter level structure
		 * because of counter overflow
		 */
		if ((dcf->OFV == NULL && counter > cbfvMax) ||
			(dcf->OFV != NULL && ofvCounter > ofvMax))
		{
			RebuildOFV(dcf, dcf->OFV_Counter_Size + 1);
			dcf->Counter_Level = (Counter_Level_Item *)realloc(
				dcf->Counter_Level, 
				sizeof(Counter_Level_Item) * (dcf->OFV_Counter_Size + 1));
			dcf->Counter_Level[dcf->OFV_Counter_Size].Above_Threshold = 0;
			dcf->Counter_Level[dcf->OFV_Counter_Size].Below_Threshold = 0;
		}

		/*
		 * update the counter level structure
		 */
		if (oldLevel != newLevel)
		{
			oldThreshold = GetDCFThreshold(dcf, counter - 1);
			if (counter - 1 < oldThreshold)
				dcf->Counter_Level[oldLevel].Below_Threshold--;
			else
				dcf->Counter_Level[oldLevel].Above_Threshold--;
			if (counter < newThreshold)
				dcf->Counter_Level[newLevel].Below_Threshold++;
			else
				dcf->Counter_Level[newLevel].Above_Threshold++;
		}
		else if (counter - 1 < newThreshold && counter >= newThreshold)
		{
			dcf->Counter_Level[newLevel].Below_Threshold--;
			dcf->Counter_Level[newLevel].Above_Threshold++;
		}

		SetDCFCounter(dcf, hashAddress[i], counter);  /* update counter */
	}

	free(hashAddress);
	return 1;
}

/*  
 *  DCFDelete
 *
 *  Description:
 *      This function will delete a specified element from
 *      the specified dynamic count filter.
 *
 *  Parameters:
 *      dcf: [in/out]
 *          The dynamic count filter from which the element is deleted.
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
int DCFDelete(DynamicCountFilter *dcf, const unsigned char *element, unsigned length)
{
	char i;
	unsigned *hashAddress;
	unsigned counter;
	int oldLevel, newLevel;
	double oldThreshold, newThreshold;

	/*
	 * generate k hash addresses
	 */
	hashAddress = (unsigned *)malloc(sizeof(unsigned) * dcf->Hash_Num);
	if (!GenerateHashAddress(element, length, dcf->Length, dcf->Hash_Num, hashAddress))
	{
		free(hashAddress);
		return 0;
	}

	/*
	 * decrease the corresponding k counters and update 
	 * the counter level structure
	 */
	for (i = 0; i < dcf->Hash_Num; i++)
	{
		counter = GetDCFCounter(dcf, hashAddress[i]);
		oldLevel = GetOverflowLevel(counter >> dcf->CBFV_Counter_Size);
		newLevel = GetOverflowLevel((counter - 1) >> dcf->CBFV_Counter_Size);
		oldThreshold = GetDCFThreshold(dcf, counter);

		/*
		 * update the counter level structure
		 */
		if (oldLevel != newLevel)
		{
			newThreshold = GetDCFThreshold(dcf, counter - 1);
			if (counter < oldThreshold)
				dcf->Counter_Level[oldLevel].Below_Threshold--;
			else
				dcf->Counter_Level[oldLevel].Above_Threshold--;
			if (counter - 1 < newThreshold)
				dcf->Counter_Level[newLevel].Below_Threshold++;
			else
				dcf->Counter_Level[newLevel].Above_Threshold++;
		}
		else if (counter >= oldThreshold && counter - 1 < oldThreshold)
		{
			dcf->Counter_Level[oldLevel].Below_Threshold++;
			dcf->Counter_Level[oldLevel].Above_Threshold--;
		}

		SetDCFCounter(dcf, hashAddress[i], counter - 1);  /* update counter */

		/* 
		 * if there is no item in the highest level and no item equal or above 
		 * the threshold in the second highest level, the OFV is rebuilt 
		 */
		if (dcf->Counter_Level[dcf->OFV_Counter_Size].Above_Threshold == 0 &&
			dcf->Counter_Level[dcf->OFV_Counter_Size].Below_Threshold == 0 &&
			dcf->Counter_Level[dcf->OFV_Counter_Size - 1].Above_Threshold == 0)
		{
			RebuildOFV(dcf, dcf->OFV_Counter_Size - 1);
			dcf->Counter_Level = (Counter_Level_Item *)realloc(
				dcf->Counter_Level, 
				sizeof(Counter_Level_Item) * (dcf->OFV_Counter_Size + 1));
		}
	}

	free(hashAddress);
	return 1;
}

/*  
 *  DCFMembershipQuery
 *
 *  Description:
 *      This function will query whether a specified element 
 *      is a member of the multi-set represented by the 
 *      specified dynamic count filter.
 *
 *  Parameters:
 *      dcf: [in]
 *          The dynamic count filter on which the query is done.
 *      element: [in]
 *          The element to be checked.
 *      length: [in]
 *          The bytes of the element.
 *
 *  Returns:
 *      1 if the element is a member of the multi-set, otherwise 0.
 *
 *  Comments:
 *
 */
int DCFMembershipQuery(DynamicCountFilter *dcf, const unsigned char *element, 
					   unsigned length)
{
	char i;
	int result = 1;

	/*
	 * generate k hash addresses
	 */
	unsigned *hashAddress = (unsigned *)malloc(sizeof(unsigned) * dcf->Hash_Num);
	if (!GenerateHashAddress(element, length, dcf->Length, dcf->Hash_Num, hashAddress))
	{
		free(hashAddress);
		return 0;
	}

	/*
	 * check the counter in each hash position
	 */
	for (i = 0; i < dcf->Hash_Num; i++)
	{
		if (!GetDCFCounter(dcf, hashAddress[i]))
		{
			result = 0;
			break;
		}
	}

	free(hashAddress);
	return result;
}

/*  
 *  DCFMultiplicityQuery
 *
 *  Description:
 *      This function will query the multiplicity of a specified
 *      element in the multi-set represented by the specified 
 *      dynamic count filter.
 *
 *  Parameters:
 *      dcf: [in]
 *          The dynamic count filter on which the query is done.
 *      element: [in]
 *          The element whose multiplicity is to be queried.
 *      length: [in]
 *          The bytes of the element.
 *
 *  Returns:
 *      The multiplicity of the specified element.
 *
 *  Comments:
 *
 */
unsigned DCFMultiplicityQuery(DynamicCountFilter *dcf, 
							  const unsigned char *element, unsigned length)
{
	char i;
	unsigned counter;
	unsigned min = -1;  /* FFFFFFFF */

	/*
	 * generate k hash addresses
	 */
	unsigned *hashAddress = (unsigned *)malloc(sizeof(unsigned) * dcf->Hash_Num);
	if (!GenerateHashAddress(element, length, dcf->Length, dcf->Hash_Num, hashAddress))
	{
		free(hashAddress);
		return 0;
	}

	/*
	 * find the minimum of the k corresponding counters
	 */
	for (i = 0; i < dcf->Hash_Num; i++)
	{
		counter = GetDCFCounter(dcf, hashAddress[i]);
		if (counter < min)
			min = counter;
	}

	free(hashAddress);
	return min;
}