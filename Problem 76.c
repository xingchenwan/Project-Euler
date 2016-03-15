// Problem 76
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXNUM 100
int main()
{
     long long grid [MAXNUM+1][MAXNUM+1] = {0};
     int m, n;
     long long k;
     
     for (m = 0; m <= MAXNUM; m++) {
          grid[m][0] = 0;
          grid[m][1] = 1;
     }
     for (m = 1; m <= MAXNUM; m++) {
          for (n = 0; n <= m; n++)
               grid[m][n] = grid[m][n-1] + grid[m-n][n]; /* DP Formula */
          k = grid[m][m-1];
          for (n = m ; n < MAXNUM; n++)
               grid[m][n] = k + 1;
     }
     printf ("%llu", grid[100][100]);
     return 0;
}

// The Program gives answer 190569291
// Runtime: 2.0ms (Achieved with DP Table)

// Each row is the number in ascending order to 100 (m = 0,1,2,3... 100)
// Each column is the number of ways using number below the column value (n = 0, 1,2,3.... 100)
// For e.g. cell [50][30] is the number of ways to express 50 in terms of numbers below and including 30. Thus cell [100][100] is the desired answer.
// The first two column for every number is the same. There is 0 ways to express any number below and including 0, there is only 1 way to express any number below and including 1 (using 1 only)
// For the rest, we use 7 as an example
// Using <0: 0 (<n denotes the number of ways to express a number in terms of sum with each term smaller than n)
// <1:1,1,1,1,1,1,1 (1)
// <2:2,1,1,1,1,1; 2,2,1,1,1; 2,2,2,1 (1+3 = 4)
// <3:3,1,1,1,1; 3,2,1,1,; 3,2,2; 3,3,1 (4+4 = 8)
// <4:4,1,1,1; 4,2,1; 4,3 (8+3=11)
// <5:5,1,1; 5,2 (11+2=13)
// <6:6,1 (13+1 = 14)
// <7:7 (14 + 1 = 15) Note: last number should not be included as it is not expressed in sum. However it is necessary to compute larger numbers.

// We can observe that, for example, for <3 expression of 7, the first number is constantly 3, followed by 1,1,1,1; 2,1,1; 2,2; 3,1. They are actually <3 expression of (7-3) = 4. Expanding this findings to a general case, we have DP formula : grid[m][n] = grid[m][n-1] + grid[m-n][n]. We can then find the desired number easily.