// Problem 49
// Flawed solution: Gives error SIGBRT. However the corrent answer can be obtained directly from the debugging console. 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

void DigitListing (long num, int *DigitList, int *NumLength);
void permutation (int *, int *, int , int, int);
int prime [1230] = {0};
void primelist (int*);
void DigitListing (long num, int *DigitList, int *NumLength);
int comp(const void*a,const void*b);

int main()
{
     int i, j;
     int NumberLength, DigitList[7] = {0};
     int result [400][10] = {0}, Answer[3] = {0};
     int a, b, c;
     
     primelist(prime);
     
     for (i=236, j=0; prime[i]<9999; i++) {
          if (prime[i] == 0);
          else {
               DigitListing(prime[i], DigitList, &NumberLength);
               permutation(DigitList, result[j], 0, NumberLength, 0);
               j++;
          }
     }
     
     for (i=0; i<399; i++)
     {
          if (*result[i] == 0);
          else {
               qsort(result[i], 9, sizeof(int), comp);
               for (a=0; result[i][a+1]!=0; a++)
               for (b=a+1; result[i][b+1]!=0; b++)
               for (c=b+1; result[i][c+1]!=0; c++) // Three nested loops for nC3 (choose 3 from n elements)
                    if ((result[i][a]-result[i][b] == result[i][b]-result[i][c])&&
                        (result[i][a]-result[i][b] != 0)) {
                     Answer[0] = result[i][c], Answer[1]=result[i][b], Answer[2]=result[i][a];
                    }
          }
     } printf ("%d%d%d", Answer[0],Answer[1],Answer[2]);
     return 0;
}

void DigitListing (long num, int *DigitList, int *NumLength)
{
     int i;
     int m, n, c;
     
     for (i=0; i<15; i++)
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
     } *NumLength = i;
}

int n = 0;
void swap (int *, int *);
int IntArraytoInt (int *, int);
int primechecker (int num);
void permutation (int*Element,int*result,int CurrentDigit,int ArraySize, int RecurseCount)
{
     int i, Num, k;
     static int j = 0;
     static int LocalStorage [10] = {0}, RepeatedElement=0;
     
     if (RecurseCount == 0) { // Reset each time the function is called.
          if (j >= 3) // Only include numbers with more than three permutations being prime
          for (k=0; k<j; k++)
               result[k] = LocalStorage[k];
          j = 0;
     } if (CurrentDigit >= ArraySize-1) {
          Num = IntArraytoInt(Element, ArraySize);
          if ((primechecker(Num) == 1)&&(Element[0]!=0)) {
               for (k=0; k<j; k++) {
                    if (Num == LocalStorage[k]) {
                         RepeatedElement = 1;
                         break;
                    }
               } if (!RepeatedElement) // Remove repeated iterations when there are identical digits in a prime number
                    LocalStorage[j++] = Num;
                    RepeatedElement = 0;
          }
     } else {
          for (i=CurrentDigit; i<ArraySize; i++) {
               swap (&Element[CurrentDigit], &Element[i]);
               permutation (Element, result, CurrentDigit+1, ArraySize, RecurseCount+1);
               swap (&Element[CurrentDigit], &Element[i]);
          }
     }
}

int IntArraytoInt (int *IntArray, int NumLength) //convert a digit array back to the number
{
     int i, temp = 0,j;
     for (i=NumLength-1, j=0; i>=0; i--, j++)
          temp += IntArray[i] * pow(10, j);
     return temp;
}

void swap (int *a, int *b) // swap function in permutation
{
     int temp;
     temp = *a;
     *a = *b;
     *b = temp;
}

void primelist (int *prime) // list primes
{
     int i,j;
     int StopTask = 0;
     prime[0]=2;
     prime[1]=3;
     prime[2]=EOF;
     for (i=3; ;i=i+2)
     {
          for (j=0;prime[j]!=EOF;j++)
               if (i % (prime[j]) == 0) {
                    StopTask = 1;
                    break;
               } if (!StopTask) {
                    prime[j] = i;
                    prime[j+1] = EOF;
               } StopTask = 0;
          if (prime[j] > 9999)
               return;
     }
}

int primechecker (int num) // Check whether a given number is prime
{
     int i;
     for (i=0; prime[i]<=num; i++)
          if (num == prime[i]) {
               prime[i] = 0;
               return 1;
          } return 0;
}

int comp(const void*a,const void*b)
{
     int c = *(int*)a-*(int*)b;
     return -c;
}

// The program gives answer 296962999629.(2969 6299 9629)

