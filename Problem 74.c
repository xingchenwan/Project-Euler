// Problem 74
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAXNUM 1000000
#define MAXDIGIT 10
#define MAXITERATION 60
#define UNDEFINED -1
struct collection {
     int number;
     int step;
};
struct collection numlist [MAXNUM+1];

int main()
{
     int i, count = 0;
     void CalculateStep (int);
     void numlistInitializer ();
     
     numlistInitializer();
     for (i = 0; i <= MAXNUM; i++)
          if (numlist[i].step == UNDEFINED)
               CalculateStep(i);
     for (i = 2; i <= MAXNUM; i++)
          if (numlist[i].step == MAXITERATION)
               count ++;
     printf ("%d", count);
     return 0;
}

void numlistInitializer (void)
{
     for (int i = 0; i <= MAXNUM; i++) {
          numlist[i].number = i;
          numlist[i].step = UNDEFINED;
     }
     numlist[169].step = numlist[363601].step = numlist[1454].step = 3; //In-loop numbers
     numlist[871].step = numlist[45361].step = 2;
     numlist[872].step = numlist[45362].step = 2;
     numlist[1].step = numlist[2].step = 1; // 1! = 1, 2! = 2
     numlist[145].step = numlist[40585].step = 1; // 1!+4!+5! = 145, 4!+0!+5!+8!+5! = 40585. LoopSize = 1;
}

void CalculateStep (int num)
{
     int factorial (int), i;
     int Digits [MAXDIGIT+1];
     int Intermediates [MAXITERATION+1];
     int StoppingStep;
     int m = 1, n, *pD;
     
     for (i = 1; i <= MAXITERATION; i++)
          Intermediates[i] = -1;
     Intermediates[0] = num;
     while (1) {
          for (i = 0; i <= MAXDIGIT; i++)
               Digits[i] = UNDEFINED;
          pD = Digits; /* Reset Parameters after an iteration */
          if (num > MAXNUM || ((num < MAXNUM) && (numlist[num].step == UNDEFINED))) {
               do { *pD++ = num % 10;
                    num /= 10;
               } while (num > 0);
               num = 0;
               for (int j = 0; Digits[j] != -1; j++)
                    num += factorial(Digits[j]);
               Intermediates[m++] = num;
          } else
               break;
     }
     m--;
     StoppingStep = numlist[num].step;
     for (n = 0; m >= 0; m--, n++)
          if (Intermediates[m] < MAXNUM)
               numlist[Intermediates[m]].step = StoppingStep + n;
}

int factorial (int num)
{
     int i, product = 1;
     
     if (num == 0)
          return 1;
     for (i = num; i >= 1; i--)
          product *= i;
     return product;
}

// The program gives answer 402
// Runtime : 65.0ms (Achieved with Dynamic Programming)