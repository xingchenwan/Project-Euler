//Problem 85
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAXSIZE 1000
#define LIMIT 2000000
int main()
{
     int i;
     int j;
     int count, diff = INFINITY, LenStore, WidStore, CountStore;

     for (i = 1; i < MAXSIZE; i++)
          for (j = 1; j <= i; j++) {
               if ((count = (i * j * (i+1) * (j+1) / 4)) > (LIMIT + 10000))
                    break;
               else if (abs (count - LIMIT) < diff) {
                         diff = abs(count - LIMIT);
                         CountStore = count;
                         LenStore = i;
                         WidStore = j;
               }
          }
     printf ("Answer:\nL = %d, W = %d, Area = %d\nDifference to %d = %d\nRectangle Count = %d",
             LenStore, WidStore, LenStore*WidStore, LIMIT, diff, CountStore);
     return 0;
}

// Answer: 2772
// Observation method: for 3*2 grid, we have

// 6 4 2
// 3 2 1 (sum = 18)

// for 4*3 grid, we have
// 12 9 6 3
// 8  6 4 2
// 4  3 2 1 (sum = 60)
// Generalizing the result and applying formula of arithmatic sequence, for grid of mxn, we have formula ( (1+n)n/2 )( (1+m)m/2 );