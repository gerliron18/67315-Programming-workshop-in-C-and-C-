/**
 * @file Structs.c
 * @author  Liron Gershuny <liron.gershuny@mail.huji.ac.il>
 * @version 1.0
 * @date 12 Dec 2019
 *
 * @brief A generic implementation of vectors struct. Has implementations of compare function
 *        between vectors, free allocated memory, copying one vector to another and norm
 *        calculations. Can be used by a generic RBTree to save its data.
 *
 * @section LICENSE
 * This program is not a free software; bla bla bla...
 *
 * @section DESCRIPTION
 * The program has few implementations of generic functions that can be used by the user to
 * work with vectors.
 * Input  :
 * Process:
 * Output :
 */

// ------------------------------ includes ------------------------------
#include "Structs.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

// -------------------------- const definitions -------------------------

// ------------------------------ functions -----------------------------

/**
 * CompFunc for Vectors, compares element by element, the vector that has the first larger
 * element is considered larger. If vectors are of different lengths and identify for the length
 * of the shorter vector, the shorter vector is considered smaller.
 * @param a - first vector
 * @param b - second vector
 * @return equal to 0 iff a == b. lower than 0 if a < b. Greater than 0 iff b < a.
 */
int vectorCompare1By1(const void *a, const void *b)
{
    Vector *firstVec = (Vector *) a;
    Vector *secondVec = (Vector *) b;

    int firstLen = firstVec->len;
    int secondLen = secondVec->len;

    int firstCount = 0;
    int secondCount = 0;

    while (firstCount <= (firstLen - 1) && secondCount <= (secondLen - 1))
    {
        if (firstVec->vector[firstCount] > secondVec->vector[secondCount])
        {
            return 1;
        }
        else if (firstVec->vector[firstCount] < secondVec->vector[secondCount])
        {
            return -1;
        }

        firstCount++;
        secondCount++;
    }

    if (firstCount < firstLen)
    {
        return 1;
    }
    else if (secondCount < secondLen)
    {
        return -1;
    }

    return 0;
}

/**
 * Calculate the norm of given vector.
 * @param pVector The given vector
 * @return The norm of the given vector
 */
double normCalculator(Vector *pVector)
{
    double norm = 0;

    for (int i = 0; i < pVector->len; i++)
    {
        norm += (double) (pVector->vector[i] * pVector->vector[i]);
    }

    norm = sqrt(norm);

    return norm;
}

/**
 * copy pVector to pMaxVector if : 1. The norm of pVector is greater then the norm of pMaxVector.
 * 								   2. pMaxVector == NULL.
 * @param pVector pointer to Vector
 * @param pMaxVector pointer to Vector
 * @return 1 on success, 0 on failure (if pVector == NULL: failure).
 */
int copyIfNormIsLarger(const void *pVector, void *pMaxVector)
{
    if (pVector == NULL)
    {
        return 0;
    }

    Vector *firstVec = (Vector *) pVector;
    Vector **maxVec = (Vector **) pMaxVector;

    if (*maxVec == NULL)
    {
        *maxVec = (Vector *)malloc(sizeof(Vector));
        (*maxVec)->len = firstVec->len;
        (*maxVec)->vector = (double *)malloc(sizeof(double) * (firstVec->len));
        if ((*maxVec)->vector == NULL)
        {
            return 0;
        }

        memcpy((*maxVec)->vector, firstVec->vector, sizeof(double) * (firstVec->len));

        return 1;
    }

    else if (normCalculator(firstVec) > normCalculator(*maxVec))
    {
        (*maxVec)->vector = (double *)realloc((*maxVec)->vector, sizeof(double) * (firstVec->len));
        if ((*maxVec)->vector == NULL)
        {
            return 0;
        }

        memcpy((*maxVec)->vector, firstVec->vector, sizeof(double) * (firstVec->len));
        (*maxVec)->len = firstVec->len;

        return 1;
    }

    return 1;
}

/**
 * FreeFunc for vectors
 */
void freeVector(void *pVector)
{
    if (pVector == NULL)
    {
        return;
    }

    Vector *vec = (Vector *) pVector;

    if (vec->vector != NULL)
    {
        free(vec->vector);
    }

    free(vec);
}

/**
 * @param tree a pointer to a tree of Vectors
 * @return pointer to a *copy* of the vector that has the largest norm (L2 Norm).
 */
Vector *findMaxNormVectorInTree(RBTree *tree)
{
    if (tree == NULL)
    {
        return NULL;
    }

    Vector *res = NULL;

    forEachRBTree(tree, copyIfNormIsLarger, &res);

    return res;
}

/**
 * CompFunc for strings (assumes strings end with "\0")
 * @param a - char* pointer
 * @param b - char* pointer
 * @return equal to 0 iff a == b. lower than 0 if a < b. Greater than 0 iff b < a. (lexicographic
 * order)
 */
int stringCompare(const void *a, const void *b)
{
    char *firstStr = (char *) a;
    char *secondStr = (char *) b;

    return strcmp(firstStr, secondStr);
}

/**
 * ForEach function that concatenates the given word to pConcatenated.
 * pConcatenated is already allocated with enough space.
 * @param word - char* to add to pConcatenated
 * @param pConcatenated - char*
 * @return 0 on failure, other on success
 */
int concatenate(const void *word, void *pConcatenated)
{
    if (word == NULL || pConcatenated == NULL)
    {
        return 0;
    }

    char *pWord = (char *) word;
    char *pConcat = (char *) pConcatenated;

    char *pSemiUnited = strcat(pConcat, pWord);
    if (pSemiUnited == NULL)
    {
        return 0;
    }

    char *pFullUnited = strcat(pSemiUnited, "\n");
    if (pFullUnited == NULL)
    {
        return 0;
    }

    return 1;
}

/**
 * FreeFunc for strings
 */
void freeString(void *s)
{
    if (s == NULL)
    {
        return;
    }

    char *string = (char *) s;
    free(string);
}