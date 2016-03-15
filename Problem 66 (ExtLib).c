// Problem 66
// External library gmp.h invoked!
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <gmp.h>
#define MAXITERATION 1000

int main()
{
     void PellSolution (int, int, mpz_t *);
     mpz_t x, xMax;
     int i, numStore = 0;

     mpz_init (x); mpz_init (xMax);
     for (i = 1; i < 1000; i++) {
          if (sqrt(i) == (long long)sqrt(i))
               printf ("D = %d, x = NaN (D is perfect square) \n", i);
          else {
               PellSolution(i, 0, &x);
               if (mpz_cmp (x, xMax) > 0) {
                    mpz_set (xMax, x);
                    numStore = i;
               }
               printf ("D = %d, ", i);
               gmp_printf ("x = %Zd\n", x);
          }
     }
     gmp_printf ("\nMax minimal x = %Zd when D = ", xMax);
     printf ("%d", numStore);
     return 0;
}

void PellSolution (int num, int CurrentIndex, mpz_t *x) // Find x of theFundamental solutions of Pell's solution
{
     static int m, d, a;
     static int iterations [MAXITERATION];
     int i;
     static mpz_t CurrentDenominator, PvDenominator, PpvDenominator;
     static mpz_t Numerator; // Store denominators of the current try and the 2 convergents before the current try.

     static mpz_t ADenominator, DenominatorSq, NumeratorSq;
     static mpz_t comp_ADenominator, comp_DenominatorSq, comp_NumeratorSq;
     // These variables are calculation intermediates. The exact uses can be found in the comments below
     
     if (CurrentIndex < MAXITERATION) {
          if (CurrentIndex == 0) {
               mpz_init (CurrentDenominator);
               mpz_init (PvDenominator);
               mpz_init (PpvDenominator);
               mpz_init (ADenominator);
               mpz_init (DenominatorSq);
               mpz_init (NumeratorSq);
               mpz_init (comp_ADenominator);
               mpz_init (comp_DenominatorSq);
               mpz_init (comp_NumeratorSq);
               mpz_init (Numerator); // Initialisation
               for (i = 0; i < MAXITERATION; i++)
                    iterations [i] = 0; //Re-initialise iteration lists
               if ((int) sqrt(num) == sqrt(num)) {
                    return;
               } else {
                    m = 0, d = 1; a = sqrt(num);
                    mpz_set_ui (CurrentDenominator, 1);
                    mpz_set_ui (PpvDenominator, 0);
                    mpz_set_ui (PvDenominator, 0);
               }
          } else {
               m = d * a - m;
               d = (num - m * m) / d;
               a = (sqrt(num) + m) / d; // Core computations of this algorithm: Same as Problem 64
               if (CurrentIndex == 1)
                    mpz_set_ui (CurrentDenominator, a);
               else {
                    mpz_mul_ui (ADenominator, PvDenominator, a);
                    mpz_add (CurrentDenominator, ADenominator, PpvDenominator);
               }
          }
          mpz_pow_ui (DenominatorSq, CurrentDenominator, 2);
          mpz_mul_ui (DenominatorSq, DenominatorSq, num);
          mpz_add_ui (NumeratorSq, DenominatorSq, 1);
          mpz_root (Numerator, NumeratorSq, 2); // cond is the sqrt of CondSq with fractional parts truncated
          // numerator = sqrt (pow (denominators, 2) * num + 1); (1)
          mpz_pow_ui (comp_NumeratorSq, Numerator, 2);
          mpz_pow_ui (comp_DenominatorSq, CurrentDenominator, 2);
          mpz_mul_ui (comp_ADenominator, comp_DenominatorSq, num);
          mpz_add_ui (comp_ADenominator, comp_ADenominator, 1);
          // pow (denominators, 2) * num + 1; (2)
          // (1), (2) are derived from Pell's identity x^2 - Dy^2 = 1. Since (x/y) is the approximation of sqrt(D), x is numerator and y and denominator. Hence x = sqrt (1 + Dy^2) --- (1). We only keep the integer part of x.
          if (mpz_cmp (comp_NumeratorSq, comp_ADenominator) == 0) {
               // (1) == (2) implies that numerator w/o fraction parts is equal to cond itself, which implies that numerator does not have fractional part and is hence an integer. Given that denominator is set to be integer, this pair of Den and Num is a solution to the Pell's equation
               mpz_set (*x, Numerator);
               return;
          } else {
               iterations [CurrentIndex] = a;
               mpz_set (PpvDenominator, PvDenominator);
               mpz_set (PvDenominator, CurrentDenominator);
               mpz_set_ui (CurrentDenominator, 0); // Push one back
               PellSolution(num, CurrentIndex + 1, x);
          }
     } else {
          printf ("Number %d:Maximum Iteration Reached\n", num);
          return;
     }
}
// The program gives answer 661.
// Runtime: 13.0ms
// When D = 661, the fundamental solution of Pell's equation x^2 - Dy^2 = 1 is
// x = 16421658242965910275055840472270471049. This exceeds the limit of type "long long", while type "long double" loses required precision when x is very large. So library gmp.h for multiprecisional integral manipulation is invoked.
// Background knowledge: Pell's equation: Each solution set (x,y) gives an approximation of sqrt(D) in form x/y;
// Approach: We integrated previously found algorithm in Problem 64 to find the recycling iterations in the infinitely continued fraction of sqrt(n), (Fn void FindPeriod (int, int, int*)) and apply the pattern found in Problem 65 to a general case (if Dn is the denominator of the nth convergent and Dn+1 is that of the (n+1)th convergent, Dn+2 = Dn + xDn+1, where x is the iteration of the current term of expansion).
// Each Dn is possibly the y solution to the Pell's equation. With y fixed, we can then find the value of x. If x is an integer, this ordered pair (x,y) is the fundamental solution. Otherwise we repeat the process for the next convergent until an ordered pair (x,y) belong to integer domain is found).