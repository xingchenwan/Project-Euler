// Problem 88
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAXNUM 12000
int MinK[MAXNUM+1];
void FactorMultipler (int, int, int, int, int);
int main()
{
    int i;
    int maxfactor = log(MAXNUM) / log(2);
    int sum = 0;
    int Search (int, int);
    
    for (i = 0; i <= MAXNUM; i++) {
        if (i < 2)
            MinK[i] = 0;
        else
            MinK[i] = INFINITY;
    }
    for (i = 2; i <= maxfactor; i++)
        FactorMultipler(2, i, 0, 1, 0); /* Each i denotes the number of factors. if i = 2; we check 2x2, 2x3, .... 2x6000, 3x3, 3x4 .... 3x4000). for i = 3, we start from 2x2x2, 2x2x3 .... until i = maxfactor, where the factorization is 2x2x2x....x2 (14 terms). This is the integer with largest number of factorised terms. This is achieved with the recursive routine defined below */
    for (i = 2; i < MAXNUM; i++)  {
        if (!Search(MinK[i],i))
            sum += MinK[i];
    }
    printf ("%d", sum);
    return 0;
}

int Search (int num, int index) { /* Check for repeated elements */
    int i;
    for (i = index/2; i < index; i++)
        if (MinK[i] == num)
            return 1;
    return 0;
}

void FactorMultipler (int StartingTerm, int NumberofTerm, int RecursiveLayer, int Product, int FactorSum)
/* This routine exhaustively lists all factorisations of all numbers up to MAXNUM */
{
    int i,k;
    
    if (RecursiveLayer < NumberofTerm) {
        for (i = StartingTerm; i <= MAXNUM; i++) {
            if ((i*Product) <= (2*MAXNUM))
                FactorMultipler(i, NumberofTerm, RecursiveLayer+1, i*Product, i+FactorSum);
            else
                return;
        }
    } else {
        if ((k = Product - FactorSum + NumberofTerm) < MAXNUM) /* Condition that k smaller than MAXNUM is crucial! */
            MinK[k] = (Product < MinK[k])? Product : MinK[k];
    }
}

// Answer: 7587457
// Running Time: 41.0ms