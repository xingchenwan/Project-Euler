// Project Euler: Problem 39

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define YES 1
#define NO 0

int main()
{
     int p, a, b, counter = 0, MaxStore = 0, pStore = 0;
     
     for (p=12; p<=1000; p++) {
          if (counter > MaxStore) {
               MaxStore = counter;
               pStore = p-1;
          } counter = 0;
          for (a=1; a<p; a++){
          for (b=a; b<p; b++)
          if ((sqrt (a*a+ b*b) == (int)sqrt (a*a +b*b)) && (p-a-b == sqrt (a*a + b*b)))
               counter ++;
          }
     }
printf ("The p with max number of Pythagorean combinations is %d with %d combinations", pStore, MaxStore);
     return 0;
}

// The program gives answer 840.