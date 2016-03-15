// Project Euler: Problem 36
// Useful functions: itob (integer to binary)

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define YES 1
#define NO 0

int PalindromeTest (int *, int);
void DigitListing (int num, int *DigitList, int *NumofDigits);
void itob (int, int *, int *);

int main()
{
     int i, sum=0;
     int DigitList[7] = {0};
     int NumLength = 0;
     int BinaryList [500] = {0}, BinaryLength;
     
     for (i=1; i<=999999; i++) {
          DigitListing (i, DigitList, &NumLength);
          if (PalindromeTest(DigitList, NumLength)) {
               itob (i, BinaryList, &BinaryLength);
               if (PalindromeTest(BinaryList, BinaryLength))
                    sum += i;
          }
     }
     printf ("%d", sum);
     return 0;
}

void itob (int num, int *BinaryList, int *BinaryLength)
{
     int i = num, j = 0;
     while (i > 0) {
          BinaryList[j++] = i % 2;
          i /= 2;
     } BinaryList[j] = EOF;
     *BinaryLength = j;
}

int PalindromeTest (int *DigitList, int DigitLength)
{
     int i, StopTask = NO;

     for (i=0; i<= (DigitLength/2); i++)
          if (DigitList[i] != DigitList[DigitLength-1-i]) {
               StopTask = YES;
               break;
          } if (!StopTask)
          return YES;
     return NO;
}

void DigitListing (int num, int *DigitList, int *NumofDigits)
{
     int i, j;
     
     for (i=0; i<7; i++)
          DigitList[i] = EOF;
     *NumofDigits = 0;
     i=0;
     DigitList [i++] = num % 10;
     while (num >= 10) {
          num /= 10;
          DigitList [i++] = num % 10;
     } for (j=0; DigitList[j]!=EOF; j++)
          ;
     *NumofDigits = j;
}

// The program gives answer 872187
