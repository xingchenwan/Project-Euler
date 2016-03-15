//Problem 92
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAXNUM 10000000

int EndingDigits [MAXNUM] = {0};
int EndingNum (int);
/* 0 for untested numbers, 1 for chains ending at 1, 2 for those ending with 89 */
int main()
{
     int i;
     int count = 0;
     
     for (i = 1; i < MAXNUM; i++) {
          EndingDigits[i] = EndingNum(i);
          if (EndingNum(i) == 2)
               count ++;
     }
     printf ("%d", count);
     return 0;
}

int EndingNum (int num)
{
     int SqDigitSum (int num);
     int next;
     
     if ((next = SqDigitSum(num)) == 89)
          return 2;
     else if (SqDigitSum(num) == 1)
          return 1;
     else if (next <= MAXNUM && EndingDigits[next])
          return EndingDigits[next];
     else
          return EndingNum(next);
     return 0;
}

int SqDigitSum (int num)
{
     int temp = 0;
     
     while (num > 0) {
          temp += pow (num%10, 2);
          num /= 10;
     }
     return temp;
}

// Answer: 8581146
// Running Time: 692.0ms (Optimised with partial DP; could be optimised with complete DP algorithm)