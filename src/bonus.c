﻿
#include "../includes/bonus.h"
#include "../includes/cipher.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

DiffTable *newDiffTable(int nbBits)
{
    DiffTable *diffTable = NULL;
    int nbElts = 1 << nbBits;

    diffTable = (DiffTable *)calloc(1, sizeof(DiffTable));
    if (!diffTable) goto ERROR_LABEL;

    diffTable->nbBits = nbBits;
    diffTable->nbElts = nbElts;
    diffTable->max = 0;

    diffTable->coeffs = (int **)calloc(nbElts, sizeof(int *));
    if (!diffTable->coeffs) goto ERROR_LABEL;

    for (int i = 0; i < nbElts; i++)
    {
        diffTable->coeffs[i] = (int *)calloc(nbElts, sizeof(int));
        if (!diffTable->coeffs[i]) goto ERROR_LABEL;
    }

    return diffTable;

ERROR_LABEL:
    printf("ERROR - newDiffTable()\n");
    freeDiffTable(diffTable);
    return NULL;
}

void freeDiffTable(DiffTable *diffTable)
{
    if (!diffTable) return;

    if (diffTable->coeffs)
    {
        int nbElts = diffTable->nbElts;
        for (int i = 0; i < nbElts; i++)
        {
            if (diffTable->coeffs[i])
                free(diffTable->coeffs[i]);
        }
        free(diffTable->coeffs);
    }

    // Clear the memory (security)
    memset(diffTable, 0, sizeof(*diffTable));
}

void swap(int * a, int * b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void shuffle(int * sBox, unsigned int size)
{
    for (int i = size - 1; i > 0; --i)
    {
        int j = rand() % (i + 1);
        swap(&sBox[i], &sBox[j]);
    }
}

void littleShuffle(int * sBox, unsigned int size, float percent)
{
    unsigned int newSize = size * percent;
    for (int i = newSize; i > 0; --i)
    {
        int j = rand() % (i + 1);
        swap(&sBox[i], &sBox[j]);
    }
}

int numberOfMax(int * sBox, unsigned int size, unsigned int max)
{
    int count = 0;
    for (int i = 0; i < size; ++i) if (sBox[i] == max) ++count;
    return count;
}

void randomSBox(int * sBox, int nbBits)
{
    unsigned int size = 1 << nbBits;
    for (int i = 0; i < size; ++i) sBox[i] = i;
    shuffle(sBox, size);
}

void initDiffTable(DiffTable *diffTable, int *sBox)
{
    DiffTable d = *diffTable;
    d.max = 0;
    for (int i = 0; i < d.nbElts; ++i)
        memset(d.coeffs[i], 0, sizeof(int) * d.nbElts);
    for (int i = 0; i < d.nbElts; ++i)
        for (int j = 0; j < d.nbElts; ++j)
        {
            int diff = sBox[j] ^ sBox[j ^ i];
            if (++d.coeffs[i][diff] > d.max && ((i + diff) != 0))
                d.max = d.coeffs[i][diff];
        }
    *diffTable = d;
}

void initFastCipher(FastCipherData *data, Block *cipherKey)
{
    // TODO
}

void fastEncryptBlock(FastCipherData *data, Block *block)
{
    // TODO
}
