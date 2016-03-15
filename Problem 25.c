// Project Euler: Problem 25
// (Modified from solution to Problem 16 and Problem 20

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define YES 1
#define NO 0


int num_of_digits = 1000;

int main()
{
   int i,j,c=0;
   int digit1 [num_of_digits] = {0}; // Digit for the current number
   int digit2 [num_of_digits] = {0}; // Digit for the current number
   int digitstore [num_of_digits] = {0}; // Storing digit for the previous number
   int add=NO; // Whether to add one to the previous digit
   
   for (i = 0; i<50; i++) {
      digit1 [i] = 0; // Initialise Digit Sequence
      digit2 [i] = 0;
      digitstore [i] = 0;
   }
   
   digit1 [num_of_digits-1] = 1;
   digit2 [num_of_digits-1] = 1;
   
   for (c=2;; c++) {
      if (digitstore[0]!=0)
         goto print;
      
      for (i=num_of_digits-1; i>=0 ; i--) {// From last digit
         
         if (digit1[i] + digit2[i] + add < 10) {
            digitstore[i] = digit1[i] + digit2[i] + add;
            add = NO;
         }
         
         else
         {
            digitstore[i] = (digit1[i] + digit2[i]+add) % 10;
            add = YES;
         }
         
      }
      
      for (j=0; j<num_of_digits; j++) {
         digit1[j] = digit2[j];
         digit2[j] = digitstore[j];
      }
      
   }
   
   print: printf ("%d", c);
   
   return 0;
   
}

// The answer given by the program is 4782