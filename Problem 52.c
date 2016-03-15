// Problem 52

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
int IntArraytoInt (int *, int);
void InttoIntArray (int, int *, int *);
void ConditionChecker (int, int, int*);

int DigitIncidence [10] = {0};
int main()
{
     int i, a=0, j;
     
     for (i=1; ;i++) {
          for (j=0; j<10; j++)
               DigitIncidence[j] = 0;
          ConditionChecker(i, 1, &a);
          if (a) {
               printf ("%d", i);
               return 0;
          }
     } return 1;
}

void ConditionChecker (int num, int multiplier, int *Result)
{
     int Digits [7] = {0}, NumLength;
     int i;
     
     if (multiplier < 2) {
          InttoIntArray(num, Digits, &NumLength);
          for (i=0; i<NumLength;i++)
               DigitIncidence[Digits[i]] = 1;
          ConditionChecker(num, multiplier+1, Result);
     }
     
     else if (multiplier < 6) {
          InttoIntArray(num * multiplier, Digits, &NumLength);
          for (i=0; i<NumLength;i++) {
               if (DigitIncidence[Digits[i]]!=0)
                    ;
               else {
                    *Result = 0;
                    return;
               }
          } ConditionChecker(num, multiplier+1, Result);
     }
     
     else {
          *Result = 1;
          return;
     }
}

int IntArraytoInt (int *IntArray, int NumLength)
{
     int i, j;
     int temp = 0;
     for (i=NumLength-1, j=0; i>=0; i--, j++)
          temp += IntArray[i] * pow(10, j);
     return temp;
}

void InttoIntArray (int num, int *DigitList, int *NumLength)
{
     int i;
     int m, n, c;
     
     for (i=0; i<8; i++)
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

// The program gives answer 142857
