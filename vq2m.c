/*
 * vq2m.c

 *
 *  Created on: Nov 17, 2015
 *      Author: Ying Zhou
 */
#include <stdio.h>
#include <stdlib.h>
/* Warning:
 * Please NEVER directly use this function unless you are
 * sure the pointer, int* orientation, points to an array
 * of size n-1!
 *
 * This function converts a quiver A_n to its exchange matrix.
 * Input:
 * size Size of the quiver, which is n in A_n.
 * orientation A length (size - 1) array.
 * The only allowed values for the entries are -1 and 1.
 * 1 means the arrow goes from a lower-numbered vertex to
 * a higher-numbered one. -1 means the arrow goes from a
 * higher-numbered vertex to a lower numbered one.
 * All arrows are supposed to be between i and i+1.
 * Output:
 * The exchange matrix if the orientation is valid.
 * Otherwise return NULL.
 * */
int* AnToBMatrix(int size, int* orientation)
{
	int bSize = size * size;
	int* bMatrix = (int*) malloc(4 * bSize);
	int* tPointer = NULL; 
	/*Moving pointer that can point to unrelated locations,*/
	int diff, row, value; /*This is just some technicality.*/
	/* Check that orientation is valid.*/
	for (tPointer = orientation; tPointer - orientation < size - 1; tPointer++)
	{
		if (*tPointer != 1 && *tPointer != -1)
		{
			fprintf(stderr, "Error! Orientation is incorrect!\n");
			return NULL;
		}
	}
	/*Generate the B-matrix.*/
	for (tPointer = bMatrix; tPointer -  bMatrix < bSize; tPointer++)
	{
		row = (tPointer - bMatrix) / size + 1;
		diff = (tPointer - bMatrix) % (size + 1);
		if (diff == size)
		/*If the entry is just below the diagonal*/
		{
			value = *(orientation + row - 2);
			*tPointer = -value;
		}
		else if (diff == 1)
		/*If the entry is just below the diagonal*/
		{
			value = *(orientation + row - 1);
			*tPointer = value;
		}
		else
		{
			*tPointer = 0;
		}
	}
	return bMatrix;
}
/* Warning:
 * Please NEVER directly use this function unless you are
 * sure the pointer, int* orientation, points to an array
 * of size n-1!
 *
 * This function converts a valued quiver B_n to its exchange matrix.
 * Input:
 * size Size of the quiver, which is n in B_n. n > 1.
 * orientation A length (size - 1) array.
 * The only allowed values for the entries are -1 and 1.
 * 1 means the arrow goes from a lower-numbered vertex to
 * a higher-numbered one. -1 means the arrow goes from a
 * higher-numbered vertex to a lower numbered one.
 * All arrows are supposed to be between i and i+1.
 * 1 is the vertex with F_i = k, others are all k^2.
 * Output:
 * The exchange matrix if the orientation and size are valid.
 * Otherwise return NULL.
 * */
int* BnToBMatrix(int size, int* orientation)
{
	int bSize = size * size;
	int* bMatrix = (int*) malloc(4 * bSize);
	int* tPointer = NULL;
	/*Moving pointer that can point to unrelated locations,*/
	int diff, row, value; /*This is just some technicality.*/
	/* Check that orientation is valid.*/
	for (tPointer = orientation; tPointer - orientation < size - 1; tPointer++)
	{
		if (*tPointer != 1 && *tPointer != -1)
		{
			fprintf(stderr, "Error! Orientation is incorrect!\n");
			return NULL;
		}
	}
	if (size < 2)
	{
		fprintf(stderr,"For valued quiver B_n, n > 1. n should not be %d.\n", size);
		return NULL;
	}
	/*Generate the B-matrix.*/
	for (tPointer = bMatrix; tPointer -  bMatrix < bSize; tPointer++)
	{
		row = (tPointer - bMatrix) / size + 1;
		diff = (tPointer - bMatrix) % (size + 1);
		if (diff == size)
		/*If the entry is just below the diagonal*/
		{
			value = *(orientation + row - 2);
			*tPointer = -value;
		}
		else if (diff == 1)
		/*If the entry is just below the diagonal*/
		{
			value = *(orientation + row - 1);
			*tPointer = value;
		}
		else
		{
			*tPointer = 0;
		}
	}
	*(bMatrix + 1) = 2 * *(bMatrix + 1);//Doubling (1,2) entry.
	return bMatrix;
}
/* Warning:
 * Please NEVER directly use this function unless you are
 * sure the pointer, int* orientation, points to an array
 * of size n-1!
 *
 * This function converts a valued quiver C_n to its exchange matrix.
 * Input:
 * size Size of the quiver, which is n in C_n. n > 2.
 * orientation A length (size - 1) array.
 * The only allowed values for the entries are -1 and 1.
 * 1 means the arrow goes from a lower-numbered vertex to
 * a higher-numbered one. -1 means the arrow goes from a
 * higher-numbered vertex to a lower numbered one.
 * All arrows are supposed to be between i and i+1.
 * 1 is the vertex with F_i = k^2, others are all k.
 * Output:
 * The exchange matrix if the orientation and size are valid.
 * Otherwise return NULL.
 * */
int* CnToBMatrix(int size, int* orientation)
{
	int bSize = size * size;
	int* bMatrix = (int*) malloc(4 * bSize);
	int* tPointer = NULL;
	/*Moving pointer that can point to unrelated locations,*/
	int diff, row, value; /*This is just some technicality.*/
	/* Check that orientation is valid.*/
	for (tPointer = orientation; tPointer - orientation < size - 1; tPointer++)
	{
		if (*tPointer != 1 && *tPointer != -1)
		{
			fprintf(stderr, "Error! Orientation is incorrect!\n");
			return NULL;
		}
	}
	if (size < 3)
	{
		fprintf(stderr,"For valued quiver C_n, n > 2. n should not be %d.\n", size);
		return NULL;
	}
	/*Generate the B-matrix.*/
	for (tPointer = bMatrix; tPointer -  bMatrix < bSize; tPointer++)
	{
		row = (tPointer - bMatrix) / size + 1;
		diff = (tPointer - bMatrix) % (size + 1);
		if (diff == size)
		/*If the entry is just below the diagonal*/
		{
			value = *(orientation + row - 2);
			*tPointer = -value;
		}
		else if (diff == 1)
		/*If the entry is just below the diagonal*/
		{
			value = *(orientation + row - 1);
			*tPointer = value;
		}
		else
		{
			*tPointer = 0;
		}
	}
	*(bMatrix + size) = 2 * *(bMatrix + size);//Doubling (2,1) entry.
	return bMatrix;
}
/* Warning:
 * Please NEVER directly use this function unless you are
 * sure the pointer, int* orientation, points to an array
 * of size n-1!
 *
 * This function converts a quiver D_n to its exchange matrix.
 * Input:
 * size Size of the quiver, which is n in D_n. n > 3.
 * orientation A length (size - 1) array.
 * The only allowed values for the entries are -1 and 1.
 * 1 means the arrow goes from a lower-numbered vertex to
 * a higher-numbered one. -1 means the arrow goes from a
 * higher-numbered vertex to a lower numbered one.
 * All arrows are supposed to be between i and i+1 except
 * for one between 1 and 3.
 * Output:
 * The exchange matrix if the orientation and size are valid.
 * Otherwise return NULL.
 * */
int* DnToBMatrix(int size, int* orientation)
{
	int bSize = size * size;
	int* bMatrix = (int*) malloc(4 * bSize);
	int* tPointer = NULL;
	/*Moving pointer that can point to unrelated locations,*/
	int diff, row, value; /*This is just some technicality.*/
	/* Check that orientation is valid.*/
	for (tPointer = orientation; tPointer - orientation < size - 1; tPointer++)
	{
		if (*tPointer != 1 && *tPointer != -1)
		{
			fprintf(stderr, "Error! Orientation is incorrect!\n");
			return NULL;
		}
	}
	if (size < 4)
	{
		fprintf(stderr,"For valued quiver D_n, n > 3. n should not be %d.\n", size);
		return NULL;
	}
	/*Generate the B-matrix.*/
	for (tPointer = bMatrix; tPointer -  bMatrix < bSize; tPointer++)
	{
		row = (tPointer - bMatrix) / size + 1;
		diff = (tPointer - bMatrix) % (size + 1);
		if (diff == size && row > 2)
		/*If the entry is just below the diagonal*/
		{
			value = *(orientation + row - 2);
			*tPointer = -value;
		}
		else if (diff == 1 && row > 1)
		/*If the entry is just below the diagonal*/
		{
			value = *(orientation + row - 1);
			*tPointer = value;
		}
		else
		{
			*tPointer = 0;
		}
	}
	*(bMatrix + 2) = *orientation;
	*(bMatrix + 2 * size) = -*orientation;
	return bMatrix;
}
/* Warning:
 * Please NEVER directly use this function unless you are
 * sure the pointer, int* orientation, points to an array
 * of size n-1!
 *
 * This function converts a quiver F_n to its exchange matrix.
 * Input:
 * size Size of the quiver, which is n in F_n, which must be 4.
 * orientation A length 3 array.
 * The only allowed values for the entries are -1 and 1.
 * 1 means the arrow goes from a lower-numbered vertex to
 * a higher-numbered one. -1 means the arrow goes from a
 * higher-numbered vertex to a lower numbered one.
 * All arrows are supposed to be between i and i+1.
 * F_1 = F_2 = k. F_3 = F_4 = k^2.
 * Output:
 * The exchange matrix if the orientation and size are valid.
 * Otherwise return NULL.
 * */
int* FnToBMatrix(int size, int* orientation)
{
	int bSize = size * size;
	int* bMatrix = (int*) malloc(4 * bSize);
	int* tPointer = NULL;
	/*Moving pointer that can point to unrelated locations,*/
	int diff, row, value; /*This is just some technicality.*/
	/* Check that orientation is valid.*/
	for (tPointer = orientation; tPointer - orientation < size - 1; tPointer++)
	{
		if (*tPointer != 1 && *tPointer != -1)
		{
			fprintf(stderr, "Error! Orientation is incorrect!\n");
			return NULL;
		}
	}
	if (size != 4)
	{
		fprintf(stderr,"F_4 is the only valued quiver of type F_n. n should not be %d.\n", size);
		return NULL;
	}
	/*Generate the B-matrix.*/
	for (tPointer = bMatrix; tPointer -  bMatrix < bSize; tPointer++)
	{
		row = (tPointer - bMatrix) / size + 1;
		diff = (tPointer - bMatrix) % (size + 1);
		if (diff == size)
		/*If the entry is just below the diagonal*/
		{
			value = *(orientation + row - 2);
			*tPointer = -value;
		}
		else if (diff == 1)
		/*If the entry is just below the diagonal*/
		{
			value = *(orientation + row - 1);
			*tPointer = value;
		}
		else
		{
			*tPointer = 0;
		}
	}
	*(bMatrix + 6) = 2 * *(bMatrix + 6);
	return bMatrix;
}
/* Warning:
 * Please NEVER directly use this function unless you are
 * sure the pointer, int* orientation, points to an array
 * of size n-1!
 *
 * This function converts a valued quiver G_n to its exchange matrix.
 * Input:
 * size Size of the quiver, which is n in G_n. n = 2.
 * orientation A length 1 array.
 * The only allowed values for the entries are -1 and 1.
 * 1 means the arrow goes from a lower-numbered vertex to
 * a higher-numbered one. -1 means the arrow goes from a
 * higher-numbered vertex to a lower numbered one.
 * All arrows are supposed to be between i and i+1.
 * F_1 = k. F_2 = k^3.
 * Output:
 * The exchange matrix if the orientation and size are valid.
 * Otherwise return NULL.
 * */
int* GnToBMatrix(int size, int* orientation)
{
	int* bMatrix = (int *) malloc(16);
	if (size != 2)
	{
		fprintf(stderr,"G_2 is the only valued quiver of type G_n. n should not be %d.\n", size);
		return NULL;
	}
	if (*orientation != 1 && *orientation != -1)
	{
		fprintf(stderr, "Error! Orientation is incorrect!\n");
		return NULL;
	}
	*bMatrix = *(bMatrix + 3) = 0;
	if (*orientation == 1)
	{
		*(bMatrix + 1) = 3;
		*(bMatrix + 2) = -1;
	}
	else//orientation == -1
	{
		*(bMatrix + 1) = -3;
		*(bMatrix + 2) = 1;
	}
	return bMatrix;
}
/* Warning:
 * Please NEVER directly use this function unless you are
 * sure the pointer, int* orientation, points to an array
 * of size n + 1!
 *
 * This function converts an acyclic quiver TA_n to its exchange matrix.
 * Input:
 * n n in TA_n.
 * orientation A length (n + 1) array.
 * The only allowed values for the entries are -1 and 1.
 * 1 means the arrow goes from a lower-numbered vertex to
 * a higher-numbered one. -1 means the arrow goes from a
 * higher-numbered vertex to a lower numbered one.
 * n+1 is considered "lower than" 1.
 * All arrows are supposed to be between i and i+1.
 * (Including between n+1 and 1)
 * The orientation can not be cyclic, which means that at least
 * one 1 and one -1 have to exist unless n = 1.
 * Output:
 * The exchange matrix if the orientation is valid.
 * Otherwise return NULL.
 * */
int* TAnToBMatrix(int n, int* orientation)
{
	int size = n + 1;
	int bSize = size * size;
	int* bMatrix = (int*) malloc(4 * bSize);
	int* tPointer = NULL;
	int sumOr = 0;
	//Sum of orientation values, calculated in order
	//to remove cyclic orientations.
	/*Moving pointer that can point to unrelated locations,*/
	int diff, row, value; /*This is just some technicality.*/
	/* Check that orientation is valid.*/
	for (tPointer = orientation; tPointer - orientation < size; tPointer++)
	{
		sumOr = sumOr + *tPointer;
		if (*tPointer != 1 && *tPointer != -1)
		{
			fprintf(stderr, "Error! Orientation is incorrect!\n");
			return NULL;
		}
	}
	if (sumOr == size || sumOr == -size)
	{
		fprintf(stderr, "Error! Cyclic orientation of \\tilde{A_n} is not allowed!\n");
		return NULL;
	}
	/*Generate the B-matrix.*/
	for (tPointer = bMatrix; tPointer -  bMatrix < bSize; tPointer++)
	{
		row = (tPointer - bMatrix) / size + 1;
		diff = (tPointer - bMatrix) % (size + 1);
		if (diff == size)
		/*If the entry is just below the diagonal*/
		{
			value = *(orientation + row - 2);
			*tPointer = -value;
		}
		else if (diff == 1)
		/*If the entry is just below the diagonal*/
		{
			value = *(orientation + row - 1);
			*tPointer = value;
		}
		else
		{
			*tPointer = 0;
		}
	}
	*(bMatrix + n) += -*(orientation + n);
	*(bMatrix + n * (n + 1)) += *(orientation + n);
	return bMatrix;
}
/* Warning:
 * Please NEVER directly use this function unless you are
 * sure the pointer, int* orientation, points to an array
 * of size n!
 * This function converts a quiver TD_n to its exchange matrix.
 * Input:
 * n n of the quiver, which is n in TD_n. n > 3.
 * orientation A length n array.
 * The only allowed values for the entries are -1 and 1.
 * 1 means the arrow goes from a lower-numbered vertex to
 * a higher-numbered one. -1 means the arrow goes from a
 * higher-numbered vertex to a lower numbered one.
 * All arrows are supposed to be between i and i+1 except
 * for one between 1 and 3 and one from n-1 to n+1.
 * Output:
 * The exchange matrix if the size is valid.
 * Otherwise return NULL.
 * */
int* TDnToBMatrix(int n, int* orientation)
{
	int size = n + 1;
	int bSize = size * size;
	int* bMatrix = (int*) malloc(4 * bSize);
	int* tPointer = NULL;
	/*Moving pointer that can point to unrelated locations,*/
	int diff, row, value; /*This is just some technicality.*/
	/* Check that orientation is valid.*/
	for (tPointer = orientation; tPointer - orientation < n; tPointer++)
	{
		if (*tPointer != 1 && *tPointer != -1)
		{
			fprintf(stderr, "Error! Orientation is incorrect!\n");
			return NULL;
		}
	}
	if (n < 4)
	{
		fprintf(stderr,"For valued quiver \\tilde{D_n}, n > 3. n should not be %d.\n", n);
		return NULL;
	}
	/*Generate the B-matrix.*/
	for (tPointer = bMatrix; tPointer -  bMatrix < bSize; tPointer++)
	{
		row = (tPointer - bMatrix) / size + 1;
		diff = (tPointer - bMatrix) % (size + 1);
		if (diff == size && row > 2 && row <= n)
		/*If the entry is just below the diagonal*/
		{
			value = *(orientation + row - 2);
			*tPointer = -value;
		}
		else if (diff == 1 && row > 1 && row < n)
		/*If the entry is just below the diagonal*/
		{
			value = *(orientation + row - 1);
			*tPointer = value;
		}
		else
		{
			*tPointer = 0;
		}
	}
	*(bMatrix + 2) = *orientation;
	*(bMatrix + 2 * size) = -*orientation;
	*(bMatrix + n * n - 2) = *(orientation + n - 1);
	*(bMatrix + size * size - 3) = -*(orientation + n - 1);
	return bMatrix;
}
/* Warning:
 * Please NEVER directly use this function unless you are
 * sure the pointer, int* orientation, points to an array
 * of size n-1!
 *
 * This function converts a quiver S_n to its exchange matrix.
 * Input:
 * n n of the quiver, which is n in S_n. n > 4.
 * orientation A length n array.
 * The only allowed values for the entries are -1 and 1.
 * 1 means the arrow goes from a lower-numbered vertex to
 * a higher-numbered one. -1 means the arrow goes from a
 * higher-numbered vertex to a lower numbered one.
 * All arrows are supposed to be between 1 and i.
 * Output:
 * The exchange matrix if the orientation and size are valid.
 * Otherwise return NULL.
 * */
int* SnToBMatrix(int n, int* orientation)
{
	int size = n + 1;
	int bSize = size * size;
	int* bMatrix = (int*) malloc(4 * bSize);
	int* tPointer = NULL;
	/*Moving pointer that can point to unrelated locations,*/
	int row, column; /*This is just some technicality.*/
	/* Check that orientation is valid.*/
	for (tPointer = orientation; tPointer - orientation < n; tPointer++)
	{
		if (*tPointer != 1 && *tPointer != -1)
		{
			fprintf(stderr, "Error! Orientation is incorrect!\n");
			return NULL;
		}
	}
	if (n < 5)
	{
		fprintf(stderr,"For valued quiver S_n, n > 4. n should not be %d.\n", n);
		return NULL;
	}
	/*Generate the B-matrix.*/
	for (tPointer = bMatrix; tPointer -  bMatrix < bSize; tPointer++)
	{
		row = (tPointer - bMatrix) / size + 1;
		column = (tPointer - bMatrix) % size + 1;
		if (row == 1 && column > 1)
		{
			*tPointer = *(orientation + column - 2);
		}
		else if (column == 1 && row > 1)
		/*If the entry is just below the diagonal*/
		{
			*tPointer = -*(orientation + row - 2);
		}
		else
		{
			*tPointer = 0;
		}
	}
	return bMatrix;
}
int* VQToBMatrix(int size, int* orientation, int type)
{
	switch(type)
	{
	case 1: return AnToBMatrix(size, orientation);
	case 2: return BnToBMatrix(size, orientation);
	case 3: return CnToBMatrix(size, orientation);
	case 4: return DnToBMatrix(size, orientation);
	case 6: return FnToBMatrix(size, orientation);
	case 7: return GnToBMatrix(size, orientation);
	case 8: return TAnToBMatrix(size - 1, orientation);
	case 11: return TDnToBMatrix(size - 1, orientation);
	case 15: return SnToBMatrix(size - 1, orientation);
	default: return NULL;
	}
}
