// Problem 58

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

const static int MaxSideLength = 27000;
int prime[20000] = {0};

struct Diagonal {
     int num;
     int primality;
} DiagonalNum ;

void DiagonalNumGen (struct Diagonal *);
void primelist (int *);
int main()
{
     struct Diagonal DiagonalList [100000];
     int i, SideLength=1, PrimeCounter = 0;
     double ratio = 0.0;
     
     primelist(prime);
     DiagonalNumGen(DiagonalList);
     
     for (i=1; DiagonalList[i].num < MaxSideLength * MaxSideLength ;i++) {
          if (DiagonalList[i].primality)
               PrimeCounter ++;
          if ((i-1)%4 == 0) { // 1, 9, 25, 49... ...
               if (((ratio = (double)PrimeCounter / (double)i) < 0.1) && (ratio != 0))
                    break;
               else SideLength += 2;
          }
     }
     printf ("Side Length = %d, Ratio = %f", SideLength, ratio);
     printf ("\nCount of Diagonal Numbers = %d, Count of Prime Diagonal Numbers = %d", i, PrimeCounter);
     return 0;
}

int isPrime (struct Diagonal);
void DiagonalNumGen (struct Diagonal * List)
{
     int i = 1, counter = 0, step = 2;
     struct Diagonal *p = &List[2];
     
     List[1].num = 1, List[1].primality = 0;
     
     while (i < pow (MaxSideLength, 2)) {
          if (counter < 4) {
               i += step;
               (*p).num = i;
               (*p).primality = isPrime(*p);
               p++, counter++;
          } else if (counter == 4) {
               step += 2;
               counter = 0;
          }
     }
}
int isPrime (struct Diagonal NumberPair)// Decide primality of the "num" member of struct "Diagonal". Trial Division
{
     int i;
     
     for (i = 0; prime[i] <= sqrt(NumberPair.num); i++)
          if (NumberPair.num % prime[i] == 0) // If divisible by any previous prime
               return 0;
     
     return 1;
}
void primelist (int *prime)
{
     int i,j,k = 4;
     int StopTask = 0;
     prime[0]=2;
     prime[1]=3;
     prime[2]=5;
     prime[3]=7;
     prime[4]=EOF;
     for (i=9; ;i=i+2)
     {
          for (j=0 ;prime[j]<= (i/3) ;j++)
               if (i % (prime[j]) == 0) {
                    StopTask = 1;
                    break;
               } if (!StopTask) {
                    prime[k++] = i;
               } StopTask = 0;
          if (prime[j] > MaxSideLength)
               return;
     }
}

// Program gives answer 26241, when there is a total of 52481 diagonal numbers and 5248 prime diagonal numbers
// Runtime: 86.0ms