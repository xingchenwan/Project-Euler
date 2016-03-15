// Project Euler: Problem 40

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define YES 1
#define NO 0

void DigitListing (int num, int *DigitList);
int concatenation (int *a, int *b);

int main()
{
     int i, j, StringLength, product = 1;
     int GlobalString [100010];
     int LocalString [5] = {0};
     
     for (i=0; i<100010; i++)
          GlobalString[i] = EOF;
     
     for (i=0; ;i++) {
          DigitListing(i, LocalString);
          StringLength = concatenation(GlobalString, LocalString);
          if (StringLength > 100000)
               goto print;
     }
     print:
     for (j=0; j<6; j++)
          product *= GlobalString[(int) pow(10,j)];
     
     printf ("%d", product);
     
     return 0;
}

int concatenation (int *a, int *b)
// Concatenate string b to the back of string a, returning the length of the concatenated string
{
     int i=0, j;
     
     while (a[i] != EOF)
          i++;
     for (j=0;b[j]!=EOF;j++,i++)
          a[i] = b[j];
     return i;
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

// The program gives answer 210