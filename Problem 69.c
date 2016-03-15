// Problem 69
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAXNUM 100000

int prime [300] = {0};
int main()
{
     void primelist ();
     int pdt, i = 0;
     
     primelist();
     for (pdt = 1, i = 0; pdt < MAXNUM; i++) {
          pdt *= prime[i];
     }
     printf ("%d", pdt);
     return 0;
}
void primelist (void)
{
     int i,j,k = 2;
     int StopTask = 0;
     prime[0]=2;
     prime[1]=3;
     prime[2]=EOF;
     for (i=5; ;i=i+2)
     {
          for (j=0;prime[j]<= sqrt(i) ;j++)
               if (i % (prime[j]) == 0) {
                    StopTask = 1;
                    break;
               } if (!StopTask) {
                    prime[k++] = i;
               } StopTask = 0;
          if (prime[k-1] >= sqrt(MAXNUM))
               return;
     }
}

// The program gives answer 510510
// In general, more distinct prime factors a number has, more numbers below it are not co-prime to it. (smaller the phi(n) ). To maximise n/phi(n), we need to minimise n and maximise phi(n). Below 1 000 000, 510510 = 2*3*5*7*11*13*17 has the most number (7) of distinct prime factors and is the smallest number to have 7 distinct prime factors. So it is the answer. 

