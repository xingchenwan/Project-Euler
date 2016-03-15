// Project Euler: Problem 30

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define YES 1
#define NO 0

int power (int, int);
int SumofDigitPower (int num);

int main()
{
     int i, j=0;
     int Array[15] = {0}, sum=0;
     
     for (i=1; i<=350000; i++) {
          if (SumofDigitPower(i) == i)
               Array[j++] = i;
          else continue;
     }
     
     for (i=0; Array[i]!=0; i++)
          sum += Array[i];
     
     printf ("%d", sum-1); //The question stipulates that 1 should be excluded from the list
     
     return 0;
               
          }

int power (int num, int exp)
{
     int i;
     int base = num;
     for (i=1; i<exp; i++)
          num *= base;
     
     if (exp == 0)
          return 1;
     
     return num;
}

int SumofDigitPower (int num)
{
     int DigitArray [10] = {0};
     int ReturningValue = 0;
     int i = 0, j;
     
     DigitArray [i++] = num % 10;
     
     while (num > 1) {
          num /= 10;
          DigitArray [i++] = num % 10;
     }
     
     for (j=0; j<=i; j++)
          ReturningValue += power (DigitArray[j], 5);
     
     return ReturningValue;
}

// The program gives answer 443839

// Caution: It is possible to have more than 5 digits whose sum of digit to the power of 6 is equal to itself!