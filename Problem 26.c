
// Project Euler: Problem 26

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define YES 1
#define NO 0

void FindRecurringCycleLength (int, int*, int, int, int*);
int FiniteNum (int num); // Test whether a number is finite from its divider
int main()
{
     int n = 1, m, temp; // Index (from 1 to 1000)
     int RecurringCycleLengthStore=0;
     int indexStore = 0;
     int RemainderStore [1000] = {0};
   
   for (n=1; n<1000; n++) {
      if (FiniteNum(n))
           continue;
      else {
           FindRecurringCycleLength (n, RemainderStore, 0, 1, &temp);
           for (m=0; m<=1000; m++)
                RemainderStore[m] = 0;
           if (temp > RecurringCycleLengthStore) {
                RecurringCycleLengthStore = temp;
                indexStore = n;
           } else continue;
      }
   } printf ("Index n = %d \nMax Length of Recurring cycle = %d", indexStore, RecurringCycleLengthStore);
     return 0;
     
   }

void FindRecurringCycleLength (int num, int *RemainderStore, int i, int divider, int *temp)
{
     int Remainder, j;

     if (divider/num<1)
          divider *= 10;
     while (divider/num<1){
          divider *= 10;
          i++;
          RemainderStore[i] = 0;
     }
     Remainder = divider % num;
     RemainderStore[i] = Remainder;
     for (j=0; j<i; j++)
          if (RemainderStore[j] == Remainder) {
               *temp = i-j;
               return;
          }
     FindRecurringCycleLength(num, RemainderStore, i+1, Remainder, temp);
}

int FiniteNum (int num)
{
   double op = (double) num;
   while ((op/2) == (int)(op/2))
      op /= 2;
   while ((op/5) == (int)(op/5))
      op /= 5;
   if (op == 1)
       return YES;
   return NO;
}
