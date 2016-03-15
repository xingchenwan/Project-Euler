// Project Euler: Problem 28
// Prime Number Pre-calculation adapted from function in Problem 12

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define YES 1
#define NO 0

int main()
{
     int i = 1;
     int step = 2, counter = 0; //Initial step size is 2; Increase step size by two every time when counter is 4
     long sum = 1; // Sum of diagonal values
     
     while (i < 1001*1001) {
          if (counter<4) {
          i += step;
          sum += i;
          counter ++;
          } else if (counter == 4) {
               step += 2;
               counter = 0;
          }
     }
     
     printf ("%lu", sum);
     
     return 0;
     
}

// The program gives answer 669171001
// By observation, the first few terms in the series are as followed:
//  Series 1, 3, 5, 7, 9, 13, 17, 21, 25, 31, 37, 43, 49...
// Counter 0, 1, 2, 3, 0, 1 , 2 ,  3,  0,  1,  2,  3,  0...
// Step    2, 2, 2, 2, 4, 4,  4,   4,  6,  6,  6,  6,  8...
// Initial step size is 2, and step size is increased by two every four elements. This pattern can be expanded to any value of i