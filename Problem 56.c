// Problem 56

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

void IntArrayMultiplication (int *Array, int multiplier, int CurrentOrder, int *LocalMax);
void InttoIntArray (int num, int *DigitList);
int main()
{
     int i, Digit[250] = {0};
     int LocalLargestSum = 0; // Largest sum for a particular base number
     int GlobalLargestSum = 0; // Largest sum for all numbers. The answer to this question.
     
     for (i=2; i<100; i++) { // base
          InttoIntArray(i, Digit);
          IntArrayMultiplication(Digit, i, 1, &LocalLargestSum);
          GlobalLargestSum = (LocalLargestSum > GlobalLargestSum)? LocalLargestSum : GlobalLargestSum;
     } printf ("%d", GlobalLargestSum);
     return 0;
}

void IntArrayMultiplication (int *Array, int multiplier, int CurrentOrder, int *LocalMax)
{ // multiplier is the number itself, MaxOrder is 100
      int i,
          add = 0,
          tempArray[250], LocalSum = 0,
          k;
     static int MaxDigitStore = 0;

     if (CurrentOrder < 100) { // 100 is the max power
          if (CurrentOrder == 1)
               MaxDigitStore = 0;
          for (i = 0; i < 250; i++) tempArray[i] = Array[i];
          for (i = 249; i >= 0; i--) {
          if (Array[i] * multiplier + add < 10) {
               tempArray[i] = Array[i] * multiplier + add;
               add = 0;
          } else {
               tempArray[i] = (Array[i] * multiplier + add) % 10;
               add = (Array[i] * multiplier + add) / 10;
          }
     }    for (i = 0; i < 250; i++) Array[i] = tempArray[i];
          for (k = 0; k < 250; k++) LocalSum += Array[k];
          MaxDigitStore = (LocalSum > MaxDigitStore)? LocalSum : MaxDigitStore;
          IntArrayMultiplication(Array, multiplier, CurrentOrder+1, LocalMax);
          
     } else {
          *LocalMax = MaxDigitStore;
          return;
     }
}

void InttoIntArray (int num, int *DigitList)
{
     int i;
     int m, n, c;
     
     for (i=0; i<250; i++)
          DigitList[i] = 0;
     i=249;
     DigitList [i--] = num % 10;
     while (num >= 10) {
          num /= 10;
          DigitList [i--] = num % 10;
     } for (m=0, n=i-1; m<n; m++, n--) {
          c = DigitList[m];
          DigitList[m] = DigitList[n];
          DigitList[n] = c;
     }
}

int IntArraytoInt (int *IntArray, int NumLength)
{
     int i, j;
     int temp = 0;
     for (i=NumLength-1, j=0; i>=0; i--, j++)
          temp += IntArray[i] * pow(10, j);
     return temp;
}

// The program gives answer 972