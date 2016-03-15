// Problem 65
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define LIMIT 100
#define MAXDIGIT 100

int main()
{
     int num1 [MAXDIGIT] = {0}, num2 [MAXDIGIT] = {0}, num3[MAXDIGIT] = {0};
     int temp [MAXDIGIT] = {0}, i;
     int multiple = 2, count = 3, sum = 0;
     void InttoIntArray (int, int*);
     void IntArrayAddition (int *, int *, int *); // Add array 1 and array 2 to get array 3
     void IntArrayMultiplication (int *, int *, int); // Multiply a number by n
     void Shift (int *, int *, int *, int *);
     
     InttoIntArray(2, num1), InttoIntArray(3, num2);
     while (count <= LIMIT)
     {
          if (!(count % 3)){
               IntArrayMultiplication(num2, temp, multiple);
               IntArrayAddition(num1, temp, num3);
               multiple += 2;
          } else {
               IntArrayAddition(num1, num2, num3);
          }
          i = 0;
          while (!num3[i])
               i++;
          printf ("%3d ", count);
          for (; i < MAXDIGIT; i++)
               printf ("%d", num3[i]);
          printf ("\n");
          Shift(num1, num2, num3, temp);
          count ++;
     }
     for (i = 0; i < MAXDIGIT; i++)
          sum += num2[i];
     printf ("\nSum of the digits of the %dth term is %d", count-1, sum);
     return 0;
}

void Shift (int * num1, int *num2, int *num3, int *temp) // Shift n2 to n1, n3 to n2, clear n3 and temp
{
     int i;
     for (i = 0; i < MAXDIGIT; i++) {
          num1[i] = num2[i];
          num2[i] = num3[i];
          num3[i] = temp[i] = 0;
     }
}
void SeriesFiller (long *t)
{
     int i, multiple = 2;
     t[0] = 0;
     t[1] = 2;
     t[2] = 3;
     for (i = 3; i < LIMIT; i++)
          if (!(i%3)) {
               t[i] = t[i-2] + multiple * t[i-1];
               multiple += 2;
          } else
               t[i] = t[i-2] + t[i-1];
}

void IntArrayAddition (int *Array1, int *Array2, int *Array3)
{
     int i, add = 0, cond;
     for (i= MAXDIGIT - 1; i >= 0; i--) {
          cond = Array1[i] + Array2[i] + add;
          Array3[i] = cond % 10;
          add = cond / 10;
     }
}

void IntArrayMultiplication (int *Array1, int *Array2, int multiplier)
{
     int i, add = 0, cond;
     for (i = MAXDIGIT - 1; i >= 0; i--) {
          cond = Array1[i] * multiplier + add;
          Array2[i] = cond % 10;
          add = cond / 10;
     }
}

void InttoIntArray (int num, int *DigitList) // Returning digit count
{
     int i;
     int m, n, c;
     
     for (i=0; i<MAXDIGIT; i++)
          DigitList[i] = 0;
     i=MAXDIGIT-1;
     DigitList [i--] = num % 10;
     while (num >= 10) {
          num /= 10;
          DigitList [i--] = num % 10;
     } for (m=0, n=i-1; m<n; m++, n--) {
          c = DigitList[m];
          DigitList[m] = DigitList[n];
          DigitList[n] = c;
     }
}

// The program gives answer 272
// Runtime: 3.0ms
// By observation,
// In the series of numerators, T:
// if n is integer multiple of 3, Tn = Tn-2 * (2k)(Tn-1), k = 2,4,6,8..... (when n=3, k=2; n=6, k=4...)
// Otherwise Tn = Tn-2 + Tn-1. Since long long is insufficient to accommodate all digits, we use array to complete the task