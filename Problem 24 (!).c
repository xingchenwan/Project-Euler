// Project Euler: Problem 24
//(Flawed solution)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define YES 1
#define NO 0

void swap (int *, int *);
void permutation (int *, int **, int, int);
long factorial (int a);
void findpermutation (char *, char *, int, int, long);

int main()
{
   char digit [] = "0123456789";
   char num [10] = {0};
   int i;
   long PermutationLimit = 1000000;

   findpermutation (num, digit, 10, 0, PermutationLimit);
   
   for (i=0; i<10; i++)
      printf ("%c",num[i]);
   
   return 0;
   
}

void findpermutation (char *num, char *digit, int FactorialLimit, int CurrentDigit, long PermutationLimit)
{
   int i=0, j=0, k=0;
   long op1;
   
   for (i=0; PermutationLimit>0; i++)
      PermutationLimit -= factorial (FactorialLimit-1);
   
   if (i>=1)
      i-= 1;
   else
      i=0;
   
   PermutationLimit += factorial (FactorialLimit - 1);
   
   while (j<10) {
      if (isnumber(digit[j])) {
         j++, k++;
         if (k == i) {
            while (isalpha(digit[j]))
               j++;
            
            num[CurrentDigit] = digit[j];
            break;
         }
      }
      if (isalpha(digit[j]))
         j++;
   }
   
   digit[j] = 'E';
   
   op1 = PermutationLimit;
   
   if (FactorialLimit>0)
   findpermutation(num, digit, FactorialLimit-1, CurrentDigit+1, op1);
}


long factorial (int a)
{
   long op = 1;
   int i;
   
   for (i=2; i<=a; i++)
      op *= i;
   
   return op;
   
}


// Note: For computation of all permutations of a given array. This implementation is not used in this question, but is nevertheless relevant in solving similar problems.
void permutation (int *num, int *result[], int CurrentDigit, int n)
{
   int i,j;
   static int ArraySize = 3;
   
   if (CurrentDigit >= ArraySize) {
      for (j=0; j<=ArraySize; j++) {
         result[n][j] = num[j];
         printf ("%d",result[n][j]);
      }
      printf ("\n");
      n++;
   }
   
   else {
   for (i=CurrentDigit; i<=ArraySize; i++) {
      swap (&num[CurrentDigit], &num[i]);
      permutation (num, result, CurrentDigit+1, n);
      swap (&num[CurrentDigit], &num[i]);
      }
   }
}


void swap (int *a, int *b)
{
   int temp;
   
   temp = *a;
   *a = *b;
   *b = temp;
}

// Answer given by the program: 278391546 (Missing trailing zero) .
