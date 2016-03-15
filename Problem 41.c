// Project Euler: Problem 41

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int prime[116340] = {0};

void primelist (int *);
void DigitListing (int, int *);
int comp(const void*,const void*);
void permutation (int *, int *, int, int);
int primechecker (int);

int main()
{
     int PandigitElement7[] = {1,2,3,4,5,6,7};
     int i, LargestPrime;
     int PandigitNum [2881] = {0}; // Storing all permutation of 1-7 pandigital numbers
     
     primelist(prime);
     permutation(PandigitElement7, PandigitNum, 0, 7);
     qsort(PandigitNum, 2881, sizeof(int), comp);
     for (i=0; i<2881; i++)
          if (primechecker(PandigitNum[i])) {
               LargestPrime = PandigitNum[i];
               goto print;
          }
     
     print: printf ("%d", LargestPrime);
     
     return 0;
     
}

void DigitListing (int num, int *DigitList)
{
     int i;
     int m, n, c;
     
     for (i=0; i<6; i++)
          DigitList[i] = EOF;
     i=0;
     DigitList [i++] = num % 10;
     while (num >= 10) {
          num /= 10;
          DigitList [i++] = num % 10;
     } for (m=0, n=i-1; m<n; m++, n--) {
          c = DigitList[m];
          DigitList[m] = DigitList[n];
          DigitList[n] = c;
     }
}


int n = 0;
void swap (int *, int *);
int IntArraytoInt (int *, int);
void permutation (int *element, int *result, int CurrentDigit, int ArraySize)
{
     int i, Num;
     
     if (CurrentDigit >= ArraySize-1) {
          Num = IntArraytoInt(element, ArraySize);
          if (Num%2) {
          result[n++] = Num;
          }
     } else {
          for (i=CurrentDigit; i<=ArraySize-1; i++) {
               swap (&element[CurrentDigit], &element[i]);
               permutation (element, result, CurrentDigit+1, ArraySize);
               swap (&element[CurrentDigit], &element[i]);
          }
     }
}

int IntArraytoInt (int *IntArray, int NumLength)
{
     int i, temp = 0,j;
     
     for (i=NumLength-1, j=0; i>=0; i--, j++)
          temp += IntArray[i] * pow(10, j);
     return temp;
}

void swap (int *a, int *b)
{
     int temp;
     
     temp = *a;
     *a = *b;
     *b = temp;
}

void primelist (int *prime) // Optimised Prime Listing Tool!
{
     int i,j, k=2;
     int StopTask = 0;
     prime[0]=2;
     prime[1]=3;
     prime[2]=EOF;
     for (i=5; i<1530864;i+=2)
     {
          for (j=0; (prime[j]<=(i/2)) && (prime[j]!=EOF);j++)
               if (!(i % prime[j])) {
                    StopTask = 1;
                    break;
               } if (!StopTask) {
                    prime[k++] = i;
                    prime[k] = EOF;
               } StopTask = 0;
     }
}

int primechecker (int num) // Specialised version of primechecker particular to this question.
{
     int i;
     for (i=0; prime[i]<=(num/5); i++)
          if (!(num%prime[i]))
               return 0;
     
     return 1;
}

int comp(const void*a,const void*b)
{
     int c = *(int*)a-*(int*)b;
     return -c;
}

// The program gives answer 7652413
// 9-, 8-, 6-, 5- panditigals are bound to be non-prime, as summation from 1 to 9, 8, 6, 5 are divisible by 3 (45, 36, 21, 15). Hence the number themselves are divisible by 3 (non-prime)
// All other pandigital are not divisible by 3. Numbers ending with 2, 4, 6 or 8 are excluded hence they are not divisible by 2. So the smallest possible divisor is 5. Thus the prime list can stop at the 1/5 of the largest panditigal (i.e. 7654321/5 = 153 0864)
