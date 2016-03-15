//Problem 100
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAXNUM 1000000000000
int main ()
{
     long a, b;
     long Prev_a = 1, Prev_b = 1, B; // Fundamental Solution to Pell's Equation a^2 - 2b^2 = -1
     long double T;
     int i;
     
     for (i = 0; ;i ++) {
          a = 3 * Prev_a + 4 * Prev_b;
          b = 2 * Prev_a + 3 * Prev_b; //(*)
          T = (a + 1.0)/2.0;
          if ((long)T == T)
               printf ("Total Disc = %ld, Blue Disc = %ld\n",(long)T,B = (b+1)/2);
          if (T > MAXNUM)
               return 0;
          Prev_a = a;
          Prev_b = b;
     }
     return 0;
}
// Ans: 756872327473
// Running Time: 2.0ms
// Approach:
// By principle of probability, P(two blue draws) = B/T * (B-1)/(T-1) (B = No. of Blue Disc, T = Total No. of Disc). Re-arranging B/T*(B-1)/(T-1) = 0.5, by expanding and completing the square, we have
// 2(B - 0.5)^2 - (T - 0.5)^2 = 0.25
// Multiply by 4 on both side, we have 8(B-0.5)^2 - 4(T-0.5)^2 = 1 -> 2(2B-1)^2 - (2T-1)^2 = 1; By Substituting a = 2B-1 and b = 2T-1, we have 2a^2 - b^2 = 1 -> b^2 - 2a^2 = -1. This is a standard negative Pell's equation.
// The fundamental solution to this equation when both a and b are positive is (1,1). Prior Literature shows that b(n) + a(n)sqrt(2) = (1 + sqrt(2)) ^ 2n-1, or recursively (*) expression shown in the main program. We print each probable answer until we first reach MAXNUM. This solution of b, from which T can be calculated, is the answer to this question