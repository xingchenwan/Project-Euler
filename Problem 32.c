// Project Euler: Problem 33

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define YES 1
#define NO 0

int DigitIncidence [10] = {0};
int PandigitTester (int multiplicant, int multiplier, int product, int * DigitArray);

int main()
{
     int a; //Multiplicant
     int b; //Multiplier
     int DigitArray[10] = {0};
     int ProductStore[20] = {0};
     int i, j=0, StopTask = NO, sum=0;
     
     //Also, 1. No.of digits of a + No. of digits of b + No. of digits c = 9;
     //From rules of arthmatics, 2. No. of digits of c is either the sum of No. of digits of a and b, or (sum - 1) where "sum" has the same meaning.
     // Hence solving Digit(a) + Digit (b) = 9 - Digit (c) (I) and (Digit(a) + Digit(b) - 1 <= Digit(c) <= Digit (a) + Digit (b) (II), the only integer value Digit (c) can take is 4. Hence (Digit(a), Digit(b)) is either (1,4) or (2,3) (The order within the the bracket does not matter);
     
     // Starting from (1,4)
     for (a=1; a<=9; a++) {
          for (b=1000; b<= 9999; b++) {
               if (a*b > 9999 || a*b<1000) // c must be a four-digited number
                    break;
               
               for (i=0; i<20; i++)
                    if (a*b == ProductStore[i])
                         StopTask = YES;
               
               if (!StopTask) {
                    if (PandigitTester(a, b, a*b, DigitArray))
                         ProductStore[j++] = a*b;
               }
               StopTask = NO;
               for (i=0; i<10; i++)
                    DigitIncidence[i] = 0;
          }
     }
     
     // (2, 3)
     for (a=10; a<=99; a++){
          for (b=100; b<= 999; b++) {
               if (a*b > 9999|| a*b<1000) // c must be a four-digited number
                    break;
               
               for (i=0; i<20; i++)
                    if (a*b == ProductStore[i])
                         StopTask = YES;
               
               if (!StopTask) {
                    if (PandigitTester(a, b, a*b, DigitArray))
                         ProductStore[j++] = a*b;
               }
               StopTask = NO;
               for (i=0; i<10; i++)
                    DigitIncidence[i] = 0;
          }
     }
     
     for (i=0; ProductStore[i]!=0; i++)
          sum += ProductStore[i];
     
     printf ("%d", sum);
     
     return 0;
}

void DigitMapping (int num, int * DigitArray);
int PandigitTester (int multiplicant, int multiplier, int product, int * DigitArray)
{
     int i,j;
     
     DigitMapping(multiplicant, DigitArray);
     for (i=0; i<10; i++) {
          DigitIncidence[DigitArray[i]]++;
          DigitArray[i] = 0;
     }
     
     DigitMapping(multiplier, DigitArray);
     for (i=0; i<10; i++) {
          DigitIncidence[DigitArray[i]]++;
          DigitArray[i] = 0;
     }
     
     DigitMapping(product, DigitArray);
     for (i=0; i<10; i++) {
          DigitIncidence[DigitArray[i]]++;
          DigitArray[i] = 0;
     }
     
     for (j=1; j<10; j++)
          if (DigitIncidence[j] != 1)
               return NO;
     
     return YES;

}

void DigitMapping (int num, int * DigitStore)
{
     int i = 0;
     
     DigitStore [i++] = num % 10;
     
     while (num > 1) {
          num /= 10;
          DigitStore [i++] = num % 10;
     }
}

// The program gives answer 45228