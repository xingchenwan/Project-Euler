// Problem 64
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#define MAXITERATION 500

int main()
{
     int PeriodLength, i, count = 0;
     void FindPeriod (int, int, int *);
    
     for (i = 1; i <= 10000; i++) {
          FindPeriod(i, 0, &PeriodLength);
          if (PeriodLength % 2) // Odd period length
               count ++;
     }
     printf ("Number of square root with odd period is %d.", count);
     return 0;
}

void FindPeriod (int num, int CurrentIndex, int *PeriodLength)
{
     static int m, d, a;
     int SameElementSearch (int *, int *, int *, int);
     static int mList[MAXITERATION], dList[MAXITERATION], aList[MAXITERATION];
     static int iterations [MAXITERATION];
     int i, cond;
     
     if (CurrentIndex < MAXITERATION) {
          if (CurrentIndex == 0) {
               for (i = 0; i < MAXITERATION; i++)
               iterations [i] = mList [i] = dList[i] = aList[i] = 0; //Re-initialise iteration lists
               if ((int) sqrt(num) == sqrt(num)) {
                    *PeriodLength = 0;
                    return;
               } else
                    m = 0, d = 1; a = (int)sqrt(num);
          } else {
               m = d * a - m;
               d = (num - m * m) / d;
               a = (int)((sqrt(num) + m)/d); // Core computations of this algorithm
          }
          iterations [CurrentIndex] = a;
          mList[CurrentIndex] = m, dList[CurrentIndex] = d, aList[CurrentIndex] = a;
          if ((cond = SameElementSearch(mList, dList, aList, CurrentIndex))) {
               *PeriodLength = cond;
               return;
          } else
               FindPeriod(num, CurrentIndex + 1, PeriodLength);
     } else {
          printf ("Error: Maximum Iteration Reached");
          return;
     }
}

int SameElementSearch (int *a, int *b, int *c, int Stop) // Check whether the current triplet repeats any of the previous triplet. If yes, the difference between the current index and the index where repetition occurs is the size of period
{
     int i = 0;
     for (i = 0; i < Stop; i++)
          if (a[Stop] == a[i] && b[Stop] == b[i] && c[Stop] == c[i])
               return Stop - i;
     return 0;
}
// Program gives answer 1322
// Runtime: 18.0ms
// Source of algorithm: https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Continued_fraction_expansion
