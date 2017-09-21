/*
 * MatrixMutationApp.h
 *
 *  Created on: Nov 15, 2015
 *      Author: Ying Zhou
 */

#ifndef MATRIXMUTATIONAPP_H_
#define MATRIXMUTATIONAPP_H_
extern void mutationApp(int**, int);/*From Mutation.c*/
extern void vectorPrint(FILE*, int*, int);/*From Mutation.c*/
extern void matrixPrint(FILE*, int*, int, int);/*From Mutation.c*/
extern int* produceEMatrix(int*, int, int);/*From Mutation.c*/
extern int* produceFQEMatrix(int*, int);/*From Mutation.c*/
extern int* produceCQEMatrix(int*, int);/*From Mutation.c*/
extern int mutate (int*, int, int, int);/*From Mutation.c*/
extern int nextGreenVertex(int*, int, int);/*From Mutation.c*/
extern int* appendArray(int*, int*, int, int);/*From Mutation.c*/
extern int* getCVector(int*, int, int);/*From Mutation.c*/
extern int cExceedMax(int*, int, int);/*From Mutation.c*/
extern void printMGS(FILE*, int*, int, int, int, int);/*From Mutation.c*/
extern int* VQToBMatrix(int, int*, int);/*From vq2m.c*/
extern int* AnCVectorLabel(int*, int);/*From CVector.c*/
extern int* cVectorLabel(int*, int, int);/*From CVector.c*/
extern void printCVector(FILE*, int*, int, int);/*From CVector.c*/
#endif /* MATRIXMUTATIONAPP_H_ */
