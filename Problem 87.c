//Problem 87
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#define MAXNUM 50000000
#define LIMIT 1000
int mark[MAXNUM+1] = {0};
int prime [909] = {0};
void PrimeInitializer (void);
struct SWTC {
     bool SqSeriesDone;
     bool CubeSeriesDone;
     bool QuaterSeriesDone;
}LoopController = {false};
int main()
{
     PrimeInitializer();
     int SqSeries [LIMIT] = {0}, CubeSeries[LIMIT] = {0}, QuaterSeries[LIMIT] ={0};
     int i;
     int a, b, c;
     int temp, count = 0;
     
     for (i = 0; prime[i]!=0; i++) {
          if (LoopController.SqSeriesDone == false) {
               if ((temp = pow (prime[i], 2)) < MAXNUM)
                    SqSeries[i] = temp;
               else LoopController.SqSeriesDone = true;
          } if (LoopController.CubeSeriesDone == false) {
               if ((temp = pow (prime[i], 3)) < MAXNUM)
                    CubeSeries[i] = temp;
               else LoopController.CubeSeriesDone = true;
          } if (LoopController.QuaterSeriesDone == false) {
               if ((temp = pow (prime[i], 4)) < MAXNUM)
                    QuaterSeries[i] = temp;
               else LoopController.QuaterSeriesDone = true;
          }
     }
     for (a = 0; SqSeries[a]!=0; a++)
          for (b = 0; CubeSeries[b]!=0; b++)
               for (c = 0; QuaterSeries[c]!=0; c++) {
                    if ((temp = SqSeries[a] + CubeSeries[b] + QuaterSeries[c]) < MAXNUM)
                         mark[temp] = 1;
               }
     for (i = 0; i < MAXNUM; i++)
          if (mark[i])
               count ++;
     printf ("%d", count);
     return 0;
}

void PrimeInitializer (void)
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

// Answer: 1097343
// Running Time: 122.0ms