/*
 * Mutation.c
 *
 *  Created on: Nov 15, 2015
 *      Author: Ying Zhou
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Mutation.h"
/* This function appends array after targetArray.
 * Warning: We assume there are enough space in the
 * place started from targetArray!
 *
 */
int* appendArray(int* array, int* targetArray, int lengthA, int lengthTA)
{
	int* tempT = targetArray + lengthTA;
	int* tempA = array;
	//targetArray = (int *) realloc(targetArray, 4 * (lengthA + lengthTA) );
	for(; tempA - array < lengthA; tempA++, tempT++)
	{
		*tempT = *tempA;
	}
	return targetArray;
}
/* Get c-vector from an eMatrix
 * Input:
 * eMatrix the extended exchange matrix
 * size the size of the matrix
 * column the column containing the c-vector
 * Output:
 * NULL if column is outside bounds.
 * Otherwise return the c-vector.
 */
int* getCVector(int* eMatrix, int size, int column)
{
	int eSize = 2 * size * size;
	int* tempE = eMatrix + eSize / 2 + column - 1;
	//Start with the first entry of the c-vector.
	int* cVector = (int*) malloc(4 * size);
	int* tempC = cVector;
	if (column <= 0 || column > size)
	{
		fprintf(stderr, "Error! column has to be between 1 and %d, it currently is %d.", size, column);
		return NULL;
	}
	for (; tempE - eMatrix < eSize; tempE = tempE + size, tempC++)
	{
		*tempC = *tempE;
	}
	return cVector;
}
/* This function exists so that row vectors can be printed.
 * Input:
 * nColumns The number of entries.
 * fp The pointer to the file to which the matrix is printed.
 * Output:
 * None.
 */
void vectorPrint(FILE* fp, int* vector, int nColumns)
{
	int* index = vector;
	for (; index - vector < nColumns; index++)
	{
		fprintf(fp, "%d,", *index);
	}
}
/* This function exists so that matrices can be printed.
 * Input:
 * matrix The matrix to print.
 * nRows The number of rows in the matrix.
 * nColumns The number of columns in the matrix.
 * fp The pointer to the file to which the matrix is printed.
 * Output:
 * None.
 */
void matrixPrint(FILE* fp, int* matrix, int nRows, int nColumns)
{
	int* index = matrix;
	for (; index - matrix < nRows * nColumns; index++)
	{
		fprintf(fp, "%d", *index);
		if ((index - matrix + 1) % nColumns == 0)
		{
			fprintf(fp, "\n");
		}
		else
		{
			fprintf(fp," ");
		}
	}
}
/* This function converts a B-Matrix into an extended exchange matrix
 * by adding -In/In.
 * Input:
 * bMatrix The B-Matrix.
 * size The size of the B-matrix.
 * cValue Whether you want to start from a framed quiver or a
 * coframed quiver. cValue = 1 if we start from a coframed quiver.
 * cValue = -1 if we start from a framed quiver.
 * Output:
 * If cValue is not anything other than 1 or -1 then the return is
 * The pointer to the beginning of the extended exchange matrix.
 * Otherwise we return NULL.
 */
int* produceEMatrix(int* bMatrix, int size, int cValue)
{
	 int* index = bMatrix;
	 int eSize = 2 * size * size;/* Size of the eMatrix.*/
	 int* eMatrix = (int *) malloc(4 * eSize);/* eMatrix means the extended exchange matrix. We need to allocate the space.*/
	 int* index2 = eMatrix;
	 if (cValue != -1 && cValue != 1)
	 {
		 fprintf(stderr, "Error! cValue has to be either 1 or -1. It currently equals to %d.", cValue);
		 return NULL;
	 }
	 /* Do the mutation.*/
	 for (; index - bMatrix < eSize / 2; index++, index2++)
	 {
		*index2 = *index;/*Copy the B-matrix.*/
	 }
	 for (; index2 - eMatrix < eSize; index2++)
	 {
		 if ((index2 - eMatrix - eSize / 2) % (size + 1) == 0)
		 /* This seemingly weird line means
		  * "If we are on the diagonal of the lower half
		  * of the extended exchange matrix?"*/
		 {
			 *index2 = cValue;
		 }
		 else
		 {
			 *index2 = 0;
		 }
	 }
	 /*matrixPrint(stderr, eMatrix, 2 * size, size);*/
	 return eMatrix;
}
/* This function converts a B-Matrix into an extended exchange matrix
 * by adding -In. In terms of valued quivers this function produces
 * the framed quiver of this quiver.
 * Input:
 * bMatrix The B-Matrix.
 * size The size of the B-matrix.
 * Output:
 * The pointer to the beginning of the extended exchange matrix.
 */
int* produceFQEMatrix(int* bMatrix, int size)
{
	return produceEMatrix(bMatrix, size, -1);
}
/* This function converts a B-Matrix into an extended exchange matrix
 * by adding In. In terms of valued quivers this function produces
 * the coframed quiver of this quiver.
 * Input:
 * bMatrix The B-Matrix.
 * size The size of the B-matrix.
 * Output:
 * The pointer to the beginning of the extended exchange matrix.
 */
int* produceCQEMatrix(int* bMatrix, int size)
{
	return produceEMatrix(bMatrix, size, 1);
}
/* This function does mutations.
 * Input:
 * eMatrix: The matrix on which we do the mutation.
 * nRow: The number of rows of the matrix.
 * nColumn: The number of columns of the matrix.
 * vertex: The vertex to mutate at.
 * Output:
 * 0 if successful
 * -1 if vertex is outside boundary.
 * */
int mutate(int* eMatrix, int nRow, int nColumn, int vertex) {
    int* index = eMatrix;
    int eSize = nRow * nColumn;/* Size of the ematrix.*/
    int* nEMatrix = (int *) malloc(4 * eSize);/* nEMatrix means New extended exchange matrix. We need to allocate the space.*/
    int* index2 = nEMatrix;
    int row, column, position;
    int temp1, temp2;
	if (vertex <= 0 || vertex > nColumn) {/*vertex is invalid*/
		fprintf(stderr, "Error 1: Vertex outside boundary. Size of the B-matrix is %d, your vertex label is %d.", nColumn, vertex);
        return -1;/* Mutation not successful.*/
	}
	//matrixPrint(stderr, eMatrix, 2 * size, size);
    /* Do the mutation.*/
    for (; index - eMatrix < eSize; index++,index2++)
    {
    	//fprintf(stderr, "Meow!");
        position = index - eMatrix;
        row = position / nColumn + 1;
        column = position % nColumn + 1;
        //fprintf(stderr,"position = %d, row = %d, column = %d.\n", position, row, column);
        /* position = size * (row - 1) + column - 1*/
        if (row == vertex || column == vertex)
        {
            *index2 = -*index;
            //fprintf(stderr,"Type 1 ori=%d new=%d\n", *index, *index2);
        }
        else
        {
            temp1 = *(eMatrix + nColumn * (row - 1) + vertex - 1);
            temp2 = *(eMatrix + nColumn * (vertex - 1) + column - 1);
            //fprintf(stderr, "row %d vertex %d column %d\n", row, vertex, column);
            //fprintf(stderr,"Type 2 ij=%d ik=%d kj=%d\n", *index, temp1, temp2);
            if (temp1 > 0 && temp2 > 0)
            {
                *index2 = *index + temp1 * temp2;

            }
            else if (temp1 < 0 && temp2 < 0)
            {
                *index2 = *index - temp1 * temp2;
                //fprintf(stderr,"%d %d %d %d\n", *index, temp1, temp2, *index2);
            }
            else
            {
            	*index2 = *index;
            }
        }
    }
    /*Copy the values back to eMatrix!*/
    for (index = eMatrix,index2 = nEMatrix; index - eMatrix < eSize; index++,index2++)
    {
          *index = *index2;
    }
    //free(nEMatrix);
    //fprintf(stderr,"Before leaving the function.\n\n");
    //matrixPrint(stderr, eMatrix, 2 * size, size);
	return 0;
}
/* Return the next green vertex after any particular vertex
 * Input:
 * eMatrix the extended exchange matrix.
 * size the number of columns in the matrix.
 * lastVertex the last green vertex. 0 if there was no last green vertex.
 * Output:
 * The next green vertex if it exists. Otherwise return 0.
 */
int nextGreenVertex(int* eMatrix, int size, int lastVertex)
{
	int eSize = 2 * size * size;
	int* column = eMatrix + lastVertex;
	/*The first search column, exactly the (vertex + 1)-th*/
	int* temp = column;
	if (lastVertex < 0 || lastVertex > size)
	{
		fprintf(stderr,"Error! Last vertex must be between 0 and %d, now it is %d.\n", size, lastVertex);
		return 0;
	}
	if (size <= 0)
	{
		fprintf(stderr, "Error! The size of the extended exchange matrix must be a positive integer. It should not be %d.\n", size);
	}
	for (; column - eMatrix < size; column++)
	{
		for (temp = column + eSize / 2; temp - eMatrix < eSize; temp = temp + size)
		{
			if (*temp > 0)/* Red c-vector!*/
			{
//				fprintf(stderr, "Red vertex: (%d,%d), %d\n\n", (temp - column - eSize / 2) / size + 1, column - eMatrix + 1, *temp);
				break;
			}
		}
		if (temp - eMatrix >= eSize)
		/* No break which means the c-vector is green.*/
		{
			return column - eMatrix + 1;
		}
		/*There was a break, hence the c-vector is not green.*/
	}
	/*No green c-vectors, hence return 0.*/
	return 0;
}
/* Check whether the absolute value of any element in the
 *  C-matrix exceeds a certain maximum
 * (Does not apply to valued quivers of finite type)
 * Input:
 * eMatrix the extended exchange matrix
 * size the size of the matrix
 * type the type of the valued quiver
 * Output:
 * 0 if nothing exceeds maximal
 * 1 if something exceeds maximal
 */
int cExceedMax(int* eMatrix, int size, int type)
{
	int max;
	int eSize = 2 * size * size;
	int* temp = eMatrix + eSize / 2;/*Skip the B-matrix*/
	switch(type)
	{
	case 0: max = 20; break;/*Tentative value.*/
	case 8: max = 1; break;/*TAn*/
	case 9: max = 6; break;/*Tentative value for TBn*/
	case 10: max = 6; break;/*Tentative value for TCn*/
	case 11: max = 3; break;/*TDn*/
	case 12: max = 6; break;/*We use TE8, TE6 and TE7 have smaller max*/
	case 13: max = 6; break;/*Tentative value for TF4*/
	case 14: max = 6; break;/*Tentative value for TG2*/
	default: max = 6; break;
	}
	for (; temp - eMatrix < eSize; temp++)
	{
		if (abs(*temp) > max)
		{
			return 1;
		}
	}
	return 0;
}
/* Check whether the C-matrix is completely red
 * Input:
 * eMatrix the extended exchange matrix
 * size the size of the matrix
 * Output:
 * 0 if there exists at least one non-red c-vector
 * 1 if all c-vectors are strictly red.
 */
int cVectorsAllRed(int* eMatrix, int size)
{
	int eSize = 2 * size * size;
	int* temp = eMatrix + eSize / 2;/*Skip the B-matrix*/
	for (; temp - eMatrix < eSize; temp++)
	{
		if (*temp < 0)
		{
			return 0;
		}
	}
	return 1;
}
/* Calculate the permutation of an extended exchange matrix
 * if the C-Matrix is a permutation of columns of either
 * In or -In.
 * Input:
 * eMatrix the extended exchange matrix
 * size the size of the matrix
 * Output:
 * NULL if the C-Matrix is not a permutation of
 * columns of In/-In.
 * The permutation in array notation if
 * such a permutation exists.
 * */
int* calculatePermutation(int* eMatrix, int size)
{
	int eSize = 2 * size * size;
	int* tempE = eMatrix + eSize / 2;/*Skip the B-matrix*/
	int* permutation = (int*) malloc(size);
	int* tempP = permutation;
	for (; tempE - eMatrix < eSize; tempE++)
	{
		if (*tempE == 1 || *tempE == -1)
		{
			*tempP = (tempE - eMatrix) % size + 1;
			tempP++;
		}
	}
	return permutation;
}
/* Print maximal green sequences.
 * Input:
 * fp The file pointer
 * bMatrix The B-matrix
 * size The size of the B-matrix
 * type Type of the valued quiver.
 * printIGS whether to print infinite green sequences.
 * 0 for general, 1 for An, 2 for Bn
 * 3 for Cn, 4 for Dn, 5 for En, n = 6,7,8
 * 6 for F4, 7 for G2, 8 for \tilde{An}
 * 9 for \tilde{Bn}, 10 for \tilde{Cn}
 * 11 for \tilde{Dn}, 12 for \tilde{En}
 * 13 for \tilde{F4}, 14 for \tilde{G2}.
 * Currently we only support Type 1. The reason for types
 * to appear here is that we do not always want to print
 * c-vectors as is in all valued quivers. For example
 * in An, 12 denotes 0,1,0,0,\cdots 0 which is way better than
 * actually printing everything.
 * maximalMGSLength The tentative maximal length of MGS.
 * It is only used for allocating space.
 * If it is exceeded we simply double the space.
 * */
void printMGS(FILE* fp, int* bMatrix, int size, int type, int maximalMGSLength, int printIGS)
{
	int* eMatrix = produceFQEMatrix(bMatrix, size);
	int eSize = 2 * size * size;
	//Produce the Framed quiver.
	int* vMGS = (int *) malloc(4 * (maximalMGSLength + 1));
	int* cMGS = (int *) malloc(4 * size * maximalMGSLength);
	int* eMGS = (int *) malloc(4 * eSize * (maximalMGSLength + 1));
	//int rMaximalMGSLength = maximalMGSLength;
	int* tempV = vMGS - 1;//tempV follows the end of a MGS.
	int* tempV2 = vMGS;//tempV2 is only used for printing.
	int* tempC2 = cMGS;//tempC is only used for printing.
	int* tempE = eMGS;//Follows the matrix being mutated.
	int vertex;
	//Initialize vMGS
	int MGSLength = 0;
	int MGSCount = 0;
	int IGSCount = 0;
	* (tempV + 1) = 0;//Start with 0.
	eMGS = appendArray(eMatrix, eMGS, eSize, 0);
	//The first matrix in eMGS is the extended exchange matrix.
	tempE = eMGS;
	int status = 1;//1 for growing, 0 for shrinking
	do{
		//fprintf(stderr, "Beginning.\nvMGS is ");
		//matrixPrint(stderr, vMGS, 1, MGSLength + 1);
		//matrixPrint(stderr, tempE, 2 * size, size);
		vertex = nextGreenVertex(tempE, size, *(tempV + 1));
		if (vertex == 0)//Shrinking
		{
			//fprintf(fp,"Shrinking...\n");
			if (status == 1)//MGS found!
			{
				status = 0;
				//fprintf(fp,"MGS found!\n");
				MGSCount++;
				fprintf(fp, "%d ", MGSCount);
				//TODO: Print the MGS
				for (tempV2 = vMGS, tempC2 = cMGS; tempV2 - vMGS < MGSLength; tempV2++, tempC2 = tempC2 + size)
				{
					fprintf(fp, "%d_", *tempV2);
					printCVector(fp, tempC2, size, type);
					fprintf(fp, " ");
				}
				fprintf(fp,"    ");
				vectorPrint(fp, calculatePermutation(tempE, size), size);
				fprintf(fp, "\n");
			}
			MGSLength--;
			tempV--;
			tempE = tempE - eSize;
		}
		else//Growing
		{
			//fprintf(fp,"Growing...\n");
			//fprintf(fp, "New vertex is %d.\n", vertex);
			eMGS = appendArray(tempE, eMGS, eSize, eSize * (MGSLength + 1));
			tempE = tempE + eSize;
			mutate(tempE, 2 * size, size, vertex);
			//Do mutation, change eMatrix.
			if ((type > 7 || type == 0) && cExceedMax(tempE, size, type) == 1)
			//Forbidden roots from tame and wild cases.
			{
				IGSCount++;
				if(printIGS != 0)
				{
					//fprintf(stderr,"Forbidden roots found!\n");
					//fprintf(stderr, "The forbidden mutation is at %d\nThe E-matrix is:\n", vertex);
					//matrixPrint(stderr, tempE, 2 * size, size);
					fprintf(fp,"I%d ", IGSCount);
					//TODO: Print the GS
					for (tempV2 = vMGS, tempC2 = cMGS; tempV2 - vMGS < MGSLength; tempV2++, tempC2 = tempC2 + size)
					{
						fprintf(fp, "%d_", *tempV2);
						printCVector(fp, tempC2, size, type);
						fprintf(fp, " ");
					}
					fprintf(fp, "%d_", vertex);
					printCVector(fp, getCVector(tempE, size, vertex), size, type);
					fprintf(fp,"\n");
					//exit(-1);
					//matrixPrint(stderr, vMGS, 1, MGSLength + 1);
				}
				tempE = tempE - eSize;
				*(tempV + 1) = vertex;//Next!
				status = 0;
			}
			else
			{
				cMGS = appendArray(getCVector(tempE, size, vertex), cMGS, size, MGSLength * size);
				tempV++;//Move tempV to the last of the green sequence
				*tempV = vertex;
				*(tempV + 1) = 0;//Make the next position 0 for growing
				MGSLength++;//Lengthen the green sequence.
				status = 1;
			}
		}
	/*fprintf(fp, "\nAll data:\n");
	fprintf(fp, "vMGS:");
	matrixPrint(stderr, vMGS, 1, MGSLength + 1);
	fprintf(fp, "\ncMGS:");
	matrixPrint(stderr, cMGS, MGSLength, size);
	fprintf(fp, "\ntempE:");
	matrixPrint(stderr, tempE, 2 * size, size);*/
	}while(MGSLength > -1);
}
/* The function to do all the mutations.
 * int* bmatrix B-matrix of the valued cluster quiver/cluster algebra
 */
void mutationApp(int* bmatrix)
{
	return;
}
