/*
 * MatrixMutationApp.c
 *
 *  Created on: Nov 15, 2015
 *      Author: Ying Zhou
 */
#include <stdio.h>
#include <stdlib.h>
#include "MatrixMutationApp.h"
/* This C file only deals with I/O.*/
void help()
{
	fprintf(stderr,"TODO: Write help message");
	/* Display help message*/
}
int main(int argc, char** argv)
{
	int *bmatrix, *orientation, *index, *label;//, *ematrix, *index, ,*appended,  *label;/* B matrix.*/
	FILE* fp = NULL;
	if (argc == 1) /* No nontrivial arguments*/
	{
		help();
		return -1;/*Invalid input.*/
	}
	fp = fopen("/Users/tzefanYah_Yahuchanan/Public/Qovatzim/Academia/Research/Tochnit_1-Cluster_algebra_project/Mutation_Data/S5.txt","a");
	orientation = (int*) malloc(6 * 6);
	*orientation = 1;
	*(orientation + 1) = 1;
	*(orientation + 2) = 1;
	*(orientation + 3) = 1;
	*(orientation + 4) = -1;
	//*(orientation + 5) = 1;
	/* Do mutations there inside the file*/
	bmatrix = VQToBMatrix(6, orientation, 15);
	matrixPrint(fp, bmatrix, 6, 6);
	//printMGS(fp, bmatrix, 6, 15, 100, 0);
	index = (int*) malloc(4 * 4);
	*index = 0;
	*(index + 1) = 0;
	*(index + 2) = 1;
	*(index + 3) = 1;
	label = cVectorLabel(index, 4, 2);
	fclose(fp);
	fprintf(stderr, "%d%d%d\n", *label, *(label + 1), *(label + 2));
	printCVector(stderr, index, 3, 2);
	//matrixPrint(stdout, bmatrix, 4, 4);
	//fprintf(stdout,"Meow!\n\n");
	//ematrix = produceFQEMatrix(bmatrix, 4);

	/*mutate(bmatrix, 4, 4, 1);
	fprintf(stdout,"Meow!\n\n");
	matrixPrint(stdout, bmatrix, 4, 4);
	mutate(bmatrix, 4, 4, 3);
	fprintf(stdout,"Meow!\n\n");
	matrixPrint(stdout, bmatrix, 4, 4);
	mutate(bmatrix, 4, 4, 2);
	fprintf(stdout,"Meow!\n\n");
	matrixPrint(stdout, bmatrix, 4, 4);
	mutate(bmatrix, 4, 4, 3);
	fprintf(stdout,"Meow!\n\n");
	matrixPrint(stdout, bmatrix, 4, 4);*/
	return 0;
}
