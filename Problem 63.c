// Problem 63

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int NumofDigits (int);
double power (int i, int j, int *e);
int main()
{
     int i, j, order;
     int count = 0;
     double cond;
     
     printf (" x  y       x^y    Digits\n");
     for (i = 1; i < 10; i++) // When i = 10, pow (10, i) yields a number with (i+1) digits. There will never be a case where pow (x, i) has x digits for x >= 10
         // 0 is excluded as the qn states positive number
          for (j = 1; ;j++) {
               cond = power (i, j, &order);
               if (order + 1 == j) {
                    count ++;
                    printf ("%2d %2d %10.4fxE%d  %2d\n", i, j, cond, order, order+1);
               } else break;
          }
     printf ("\nTotal Count: %d", count);
     return 0;
}

double power (int i, int j, int *e) // The largest number has 21 digits, exceeding limit for long long. Use scientific notation to bypass this limitation.
{
     double temp = i;
     int a;
     int power = 0;
     
     for (a = 1; a < j; a++) {
          temp *= i;
          if (temp > 10) {
               power += 1;
               temp /= 10;
          }
     }
     *e = power;
     return temp;
}
// Program gives answer 49