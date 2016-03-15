// Project Euler: Problem 29

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define YES 1
#define NO 0

int main()
{
     int IntegerArray [11][230] = {0}; // Caution: [10] is the 11th array!
     int a, base, i, j=0, k=0, counter=0;
     double power = 1;
     int PowerofPreviousElement = NO;
     int BreakLoop = NO;
     
     for (a=2; a<=100; a++) {
          
          for (base=2; (base<a)&&(base<=10); base++) {
          // Caution! Base is smaller OR EQUAL to 10
               power = log(a) / log(base);
               if (power == (int)power) {
                    PowerofPreviousElement = YES;
                    break;
               }
          }
          
          if (PowerofPreviousElement) {
               j=0, PowerofPreviousElement = NO;
               while (IntegerArray[base][j] != 0)
                    ++j;
               for (i=100/power; i<=100; i++) {
                    if (i*power>100) {
                         for (k=0; k<j; k++)
                              if (i * power == IntegerArray[base][k]) {
                                   BreakLoop = YES;
                                   break;
                //To ensure that elements in IntergerArray[base] are not repeated
                              }
                    if (BreakLoop == NO) {
                    IntegerArray[base][j++] = i * power;
                    ++counter;
                    }
                    BreakLoop = NO;
                    }
               }
          }
          
          else
               counter += 99;
     }
     
     printf ("Number is distinctive numbers is %d", counter);
     
     return 0;
}

// The program gives answer 9183
// Thinking Routine: For any number that is not the integer of the previous element, its power from 2 to 99 is distinct -> add 99 to the counter for these numbers
// If a number that IS the integer power of any previous number (e.g. 8 = 2 ^ 3; 100 = 10 ^ 2), we cannot simply add 99. As some elements are repeated (e.g. 9^2 = (3^2)^2).Since any power below 100 is counted once already, we count those above 100 (e.g. 9^33 = (3^2)^33 = 3^66 is counted already, but 9^80 = 3^160 is not counted previously)
