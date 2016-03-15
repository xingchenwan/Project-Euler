//Problem 33
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#define BUFSIZE 30
#define MAXDIGIT 2
int main ()
{
     int i, j;
     bool isDigitCancelling (int, int);
     int denominators [4], m = 0, MaxDen = 0;
     
     for (i = 10; i <= 99; i++)
          for (j = i+1; j <= 99; j++)
               if (isDigitCancelling(i, j)) {
                    denominators[m++] = j;
                    printf ("%d/%d\n",i, j);
                    MaxDen = (j > MaxDen)? j : MaxDen;
               }
     return 0;
}

bool isDigitCancelling (int num, int den)
{
     int * FindDigits (int);
     int * DenDigit, * NumDigit;
     
     DenDigit = FindDigits(den);
     NumDigit = FindDigits(num);
     if (NumDigit[0] == DenDigit[1] &&
         (double)NumDigit[1]/(double)DenDigit[0] == (double)num/den)
          return true;
     else if (NumDigit[1] == DenDigit[0] &&
              (double)NumDigit[0]/(double)DenDigit[1] == (double)num/den)
          return true;
     return false;
}

int * FindDigits (int num)
{
     int i = 0;
     int *p  = (int *) malloc(sizeof(int) * 2);
     
     while (num > 0) {
          p[i++] = num % 10;
          num /= 10;
     }
     return p;
}
// Ans:100 (Obtained thru simple calculations by the output)
