//Problem 97
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
int main ()
{
     int i;
     long TruncationFactor = pow (10, 10);
     long num = 1;
     
     for (i = 1; i <= 7830457; i++) {
          num *= 2;
          num %= TruncationFactor;
     }
     num *= 28433;
     num %= TruncationFactor;
     printf ("%lu", num+1);
     return 0;
}
// Ans: 7830457
// Running Time: 96.0ms