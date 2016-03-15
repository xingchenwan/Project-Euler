//Problem 95
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#define MAXNUM 1000000
#define MAXFACTOR 19
#define MAXLENGTH 30 /* Max amicable sequence length */

int prime [100000];
int FactorSum [MAXNUM+1];
void PrimeInitializer (void);
void FindFactorSum (int, int, int, int);
int FindAmicableSequence (int, int*);
int main ()
{
     int i;
     int CurrLongestSequence = 0;
     int CurrFirstNum = 0, next;

     PrimeInitializer();
     for (i = 0; i < MAXNUM; i++)
          FactorSum[i] = 1;
     for (i = 2; i <= MAXFACTOR; i++)
          FindFactorSum(0, i, 0, 1);
     for (i = 2; i < MAXNUM; i++) {
          if ((next = FindAmicableSequence(i, &CurrFirstNum)) > CurrLongestSequence) {
               CurrLongestSequence = next;
               printf ("%d    %d\n",CurrLongestSequence, CurrFirstNum);
          }
     }
     return 0;
}

int FindAmicableSequence (int StartingNumber, int *FirstNum)
{
     int next, LengthCount = 0;
     int OriginalNum = StartingNumber;
     
     next = StartingNumber;
     while (next <= MAXNUM) {
          next = FactorSum[next];
          // printf ("%d\n", next);
          if (next == OriginalNum) { /* Has reached a previously looped number */
               *FirstNum = next;
               return LengthCount;
          } else if (LengthCount > MAXLENGTH)
               return 0;
          else if (next < 0)
               return 0;
          LengthCount++;
     }
     return 0;
}

void FindFactorSum (int StartingTerm, int NumberofTerm, int RecursiveLayer, int Product)
/* This routine exhaustively lists all factorisations of all numbers up to MAXNUM. A prime number has factorsum 1, and a number with factor sum exceeding one million will have sum -1*/
{
     int i,j,k;
     int temp = 0, interm1, multiplicity = 1;
     int interm2 = 1;
     static int PrimeFactors [MAXFACTOR] = {0};
     
     if (RecursiveLayer < NumberofTerm) {
          if (!RecursiveLayer)
               for (int j = 0; j <= MAXFACTOR; j++)
                    PrimeFactors[j] = 0;
          for (i = StartingTerm; prime[i] != 0; i++) {
               if (prime[i] * Product < MAXNUM && prime[i] * Product > 0) { /* Diagnostics: >0 condition is used in case of overflow: a number exceeding limit of "int" is recognized as -1 and will pass the logic test of <MAXNUM and go to the else part, where the program will crash */
                    PrimeFactors[RecursiveLayer] = prime[i];
                    FindFactorSum(i, NumberofTerm, RecursiveLayer+1, prime[i]*Product);
               } else return;
          }
     } else {
          for (k = 0; ; k++) {
               if (!k)
                    temp = PrimeFactors[k];
               else if (temp == PrimeFactors[k])
                    multiplicity++;
               else {
                    interm1 = 0;
                    for (j=0; j<=multiplicity; j++)
                         interm1 += pow(temp, j);
                    multiplicity = 1;
                    interm2 *= interm1;
                    if (interm2 > 2 * MAXNUM) {
                         FactorSum[Product] = -1;
                         return;
                    }
                    if (PrimeFactors[k])
                         temp = PrimeFactors[k];
                    else break;
               }
          }
          FactorSum[Product] = interm2 - Product;
     }
}

void PrimeInitializer (void)
{
     int i,j,k = 2;
     int StopTask = 0;
     prime[0]=2;
     prime[1]=3;
     prime[2]=EOF;
     for (i=5; ;i=i+2)
     {
          for (j=0;prime[j]<= sqrt(i) ;j++)
               if (i % (prime[j]) == 0) {
                    StopTask = 1;
                    break;
               } if (!StopTask) {
                    prime[k++] = i;
               } StopTask = 0;
          if (prime[k-1] >= (MAXNUM/2))
               return;
     }
}
//Answer: 14316 (An amicable sequence with 27 numbers)
//Running-Time: 328.0ms
