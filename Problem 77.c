// Problem 77
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#define MAXNUM 100
int prime [500] = {0};
int main()
{
     void PrimeInitializer (void);
     int m, n, SeriesFiller, Answer = 0;
     int grid[MAXNUM+1][MAXNUM+1];
     
     PrimeInitializer();
     for (m = 1; m <= MAXNUM; m++) {
          grid[m][0] = (m % 2)? 0 : 1;
          for (n = 1; prime[n] < m; n++)
               grid[m][n] = grid[m][n-1] + grid[m-prime[n]][n];
          if (prime[n] == m)
               grid[m][n] = grid[m][n-1] + 1;
          else
               grid[m][n] = grid[m][n-1];
          SeriesFiller = grid[m][n];
          for (; n <= MAXNUM; n++)
               grid[m][n] = SeriesFiller;
          if (grid[m][MAXNUM] > 5000) {
               Answer = m;
               goto print;
          }
     } print:
     printf ("%d", Answer);
     return 0;
}

void PrimeInitializer (void)
{
     int i,j,k = 2;
     int StopTask = 0;
     prime[0]=2;
     prime[1]=3;
     for (i=5; ;i=i+2) {
          for (j=0;prime[j]<= sqrt(i) ;j++)
               if (i % (prime[j]) == 0) {
                    StopTask = 1;
                    break;
               } if (!StopTask) {
                    prime[k++] = i;
               } StopTask = 0;
          if (prime[k-1] >= MAXNUM)
               return;
     }
}
// The Program gives answer 71
// Runtime : 1.0ms (Similar approach to Problem 76)