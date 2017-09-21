/*
 * CVectors.c
 *
 *  Created on: Nov 19, 2015
 *      Author: Ying Zhou
 */
/* Warning: This function does not check whether the
 * c-vector is actually one of the possible
 * c-vectors of An! I only guarantee that the output will
 * be correct when it is indeed one of the allowed
 * c-vectors of An. For the vectors that are not allowed
 * the function will not check
 *
 * Label a c-vector in An.
 * Input:
 * cVector the c-vector
 * size the size of the c-vector
 * Output:
 * An array of size 3.
 * The first integer in the array is -1 if the vector is negative
 * Otherwise it is 1.
 * The rest are according to Igusa-Orr-Todorov-Weyman's and
 * Igusa-Todorov's papers:
 * \beta_{ij} is defined as the vector in Rn with
 * all entries between i+1 and j 1 and the rest 0.
 * */
#include <stdio.h>
int* AnCVectorLabel(int* cVector, int size)
{
	int* temp = cVector;
	static int label[3];
	for (; temp - cVector < size; temp++)
	{
		if (*temp == 1 || *temp == -1)
		{
			label[0] = *temp;
			label[1] = temp - cVector;
			break;
		}
	}
	for (; temp - cVector < size; temp++)
	{
		if (*temp == 0)
		{
			break;
		}
	}
	label[2] = temp - cVector;
	return label;
}
/*
 * */
int* BnCVectorLabel(int* cVector, int size)
{
	int* temp = cVector;
	static int label[3];
	if (*temp == 0)/*x_{ij} when i<j*/
	{
		for (; temp - cVector < size; temp++)
			{
				if (*temp == 1 || *temp == -1)
				{
					label[0] = *temp;
					label[1] = temp - cVector;
					break;
				}
			}
			for (; temp - cVector < size; temp++)
			{
				if (*temp == 0)
				{
					break;
				}
			}
			label[2] = temp - cVector;
	}
	else if (*temp == 1 || *temp == -1)/*x_{ij} when i=j*/
	{
		for (; temp - cVector < size && *temp != 0; temp++);
		label[0] = *cVector;/*The sign is determined by the first 1 or -1.*/
		label[1] = temp - cVector;
		label[2] = label[1];
	}
	else/*x_{ij} when i>j*/
	{
		for (; temp - cVector < size && *temp != 1 && *temp != -1; temp++);
		label[2] = temp - cVector;
		for (; temp - cVector < size && *temp != 0; temp++);
		label[1] = temp - cVector;
		label[0] = *(temp - 1);/*The sign is determined by the last 1 or -1.*/
	}
	return label;
}
int* cVectorLabel(int* cVector, int size, int type)
{
	switch(type)
	{
	case 1: return AnCVectorLabel(cVector, size); break;
	case 2: return BnCVectorLabel(cVector, size); break;
	default: return cVector;/*Default: not doing anything*/
	}
}
/* Whenever we have a predetermined method of printing
 * we transform 1 to nothing and -1 to -.
 * Otherwise we simply print the vector as is.
 * */
void printCVector(FILE* fp, int* cVector, int size, int type)
{
	int* cVectorL = NULL;
	int index;
	if (type <= 2)/*In the future all processed types.*/
	{
		cVectorL = cVectorLabel(cVector, size, type);
		if(*cVectorL == 1)
		{
			fprintf(fp, "%d%d", *(cVectorL + 1), *(cVectorL + 2));
		}
		else
		{
			fprintf(fp, "-%d%d", *(cVectorL + 1), *(cVectorL + 2));
		}
	}
	else/*Raw types.*/
	{
		fprintf(fp, "[ ");
		for(index = 0; index < size; index++)
		{
			fprintf(fp, "%d ", *(cVector + index));
		}
		fprintf(fp, "]");
	}
}
