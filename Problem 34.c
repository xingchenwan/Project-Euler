// Project Euler: Problem 34

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define YES 1
#define NO 0

void factorial (long *);
long FactorialList [10] = {0};
void DigitListing (long, int *, int *);

int main()
{
     int DigitList[7];
     long i = 0, temp = 0;
     int j = 0, counter = 0, NumLength = 0;
     long sum = 0;
     
     factorial (FactorialList);
     for (i=10; i<2540160; i++) {
          temp = i;
          DigitListing(i, DigitList, &NumLength);
          for (j=0; DigitList[j]!=EOF; j++) {
               if (FactorialList[DigitList[j]] > i)
                    break;
               else {
                    temp -= FactorialList[DigitList[j]];
                    counter ++;
               }
          } if ((temp == 0) && (counter == NumLength))
              sum += i;
          counter = 0;
     } printf ("%lu", sum);
     return 0;
}

void factorial (long *FactorialList) // Factorial under 9
{
     int i = 1;

     FactorialList [0] = 1;
     FactorialList [1] = 1;
     for (i=2; i<=9; i++)
          FactorialList[i] = FactorialList[i-1] * i;
}

void DigitListing (long num, int *DigitList, int *NumofDigits)
{
     int i, j;
     
     for (i=0; i<=7; i++)
          DigitList[i] = EOF;
     i=0;
     DigitList [i++] = num % 10;
     while (num >= 10) {
          num /= 10;
          DigitList [i++] = num % 10;
     } for (j=0; DigitList[j]!=EOF; j++)
          ;
     *NumofDigits = j;
}

// The program gives answer 40730