// Project Euler Problem 78
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAXELEMENT 10000
#define MAXNUM 1000000
#define DIVIDER 1000000

struct pentagonal{ // GENERALIZED pentagonal numbers
     int index;
     int pentagonal;
}PentagonList [MAXELEMENT];
struct nlist{
     int num;
     int partitions;
};
struct nlist numlist[MAXNUM+1];
int main()
{
     void PentagonInitializer (void);
     void numlistInitializer (void);
     int i, n;
     signed sign;
     
     PentagonInitializer();
     numlistInitializer();
     for (i = 1; i < MAXNUM; i++) {
          long temp = 0;
          for (n = 1; PentagonList[n].pentagonal <= i; n++) {
               sign = (signed int) pow (-1, PentagonList[n].index - 1);
               temp += (sign * numlist[i - PentagonList[n].pentagonal].partitions);
          }
          numlist[i].partitions = temp % DIVIDER; // To avoid invoking bignum, we only care about the last few digits
          if (i > 0 && numlist[i].partitions == 0) {
               printf ("Found: %d", i);
               return 0;
          }
     }
     printf ("Not found in the prescribed range.\n");
     return 1;
}

void PentagonInitializer (void) // Generalized pentagonal number generator
{
     int i, j = 1, i_neg;
     for (i = 1; j < MAXELEMENT; i++) {
          i_neg = -i;
          PentagonList[j].index = i;
          PentagonList[j++].pentagonal = (3*i*i - i)/2;
          PentagonList[j].index = i_neg;
          PentagonList[j++].pentagonal = (3*i_neg*i_neg - i_neg)/2;
     }
}

void numlistInitializer (void)
{
     int i;
     for (i = 0; i < MAXNUM; i++) {
          numlist[i].num = i;
          numlist[i].partitions = 0;
     }
     numlist[0].partitions = 1;
}

// The program gives answer 55374
// Running Time: 159.0ms
// Source of algorithm: https://en.wikipedia.org/wiki/Partition_(number_theory) : "Generating Function" Section