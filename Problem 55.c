// Problem 55

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int LychrelNumbers [300], LNCounter = 0;

void InttoIntArray (int num, int *DigitList);
int IntArraytoInt (int *IntArray, int NumLength);
void isLychrel (int num, int RecursiveLayer);
int main()
{
     int i;
     
     for (i=0; i<10001; i++)
          isLychrel(i,0);
     
     printf ("There are %d lynchrel numbers below 10000, which are: \n", LNCounter);
     for (i=1; i<LNCounter; i++)
          printf ("%d,", LychrelNumbers[i]);
          
     return 0;
}

int isPalindrome (int *DigitList);
void IntArrayAddition (int *, int *, int, int, int *);
void ReverseArray (int *, int *); // Reverse the sequence of a given array
void isLychrel (int num, int RecursiveLayer)
{
     int i, ReversedArray [30] = {0};
     static int NumLength;
     static int OperatingArray [30] = {0};
     
     if (RecursiveLayer < 50) {
          
          if (RecursiveLayer == 0) {
               for (i=0; i<30; i++)
                    OperatingArray[i] =  0;
               NumLength = 0;
               InttoIntArray(num, OperatingArray);
          }
          
          ReverseArray(OperatingArray, ReversedArray);
          IntArrayAddition(ReversedArray, OperatingArray, 30, 30, &NumLength);
          
          if (isPalindrome(OperatingArray))
               return;
          else isLychrel(num, RecursiveLayer+1);
     }
     else
     LychrelNumbers[++LNCounter] = num;
     return;
}

void IntArrayAddition (int *Array1, int *Array2, const int Array1Size, const int Array2Size, int * NumLength)
{
      int i = Array1Size - 1,
          j = Array2Size - 1,
          add = 0,
          k=0,
          temp;

     for (; (j >= 0) && (i >= 0); i--, j--) {
          if (Array1[i] + Array2[j] + add < 10) {
               temp = Array1[i] + Array2[j] + add;
               Array2[j] = temp;
               add = 0;
          } else {
               temp = (Array1[i] + Array2[j] + add) % 10;
               Array2[j] = temp;
               add = 1;
          }
     } while (Array2[k] == 0) k++;
     *NumLength = Array2Size - k;
}

int isPalindrome (int *DigitList)
{
     int i = 0, StopTask = 0, j = 29;
     
     while (DigitList[i] == 0) i++;
     for (; i<=j; i++,j--)
          if (DigitList[i] != DigitList[j]) {
               StopTask = 1;
               break;
          } if (!StopTask) return 1;
     return 0;
}
void InttoIntArray (int num, int *DigitList)
{
     int i;
     int m, n, c;
     
     for (i=0; i<30; i++)
          DigitList[i] = 0;
     i=29;
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
void ReverseArray (int *Input, int *Output)
{
     int j, i = 0, temp;
     for (j = 0; j < 30; j++)
          Output[j] = Input[j];
     j--;
     while (Output[i] == 0) i++;
     for (; i <= j; i++, j--) {
          temp = Output[i];
          Output[i] = Output[j];
          Output[j] = temp;
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

// The program gives answer 249