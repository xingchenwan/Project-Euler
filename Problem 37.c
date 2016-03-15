// Project Euler: Problem 37

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define YES 1
#define NO 0

void primelist (int *);
int IntArraytoInt (int *, int);
void DigitListing (int, int *, int *);
void DigitTruncator (int, int *, int *, int, int *);

int m = 0;
int prime [100000] = {0};
int main()
{
     int i, DigitList[7]={0}, NumLength=0, StopTask=0, sum=0;
     int TruncatableArray[12] = {0};
     primelist(prime);
     
     for (i=4; ; i++) // Skip 2,3,5 and 7
     {
          if (m <= 10) {
          DigitListing(prime[i], DigitList, &NumLength);
          if (DigitList[0] == 1 ||
              DigitList[0] == 4 ||
              DigitList[0] == 6 ||
              DigitList[0] == 8 ||
              DigitList[0] == 9 ||
              DigitList[0] == 0 ||
              DigitList[NumLength-1] == 1 ||
              DigitList[NumLength-1] == 4 ||
              DigitList[NumLength-1] == 6 ||
              DigitList[NumLength-1] == 8 ||
              DigitList[NumLength-1] == 9 ||
              DigitList[NumLength-1] == 0)
               StopTask = 1;
               
          if (!StopTask)
               DigitTruncator(prime[i], DigitList, DigitList, NumLength, TruncatableArray);
          StopTask = 0;
     }
          else goto Summation;
     }
     
     Summation: for (i=0; i<11; i++)
          sum += TruncatableArray[i];
     
     printf ("%d", sum);
     
     return 0;
}

int primechecker (int);
int n = 0;
void DigitTruncator (int OriginalNum, int *LTruncation, int *RTruncation, int NumLength, int * TruncatableArray)
{
     int TempArrayL [7] = {0}; //Truncate from left
     int TempArrayR [7] = {0}; //Truncate from right
     int i, j, number1, number2;
     
     if (NumLength == 1) {
          TruncatableArray[m++] = OriginalNum;
          return;
     }
     
     for (i=1, j=0; i<=NumLength; i++, j++)
          TempArrayL[j] = LTruncation[i];
     for (i=0, j=0; i<NumLength-1; i++, j++)
          TempArrayR[j] = RTruncation[i];
     
     number1 = IntArraytoInt(TempArrayL, NumLength-1);
     number2 = IntArraytoInt(TempArrayR, NumLength-1);
     
     if ((primechecker(number1))&&((primechecker(number2)))) {
          DigitTruncator (OriginalNum, TempArrayL, TempArrayR, NumLength-1, TruncatableArray);
     }
     else return;
}


int primechecker (int num) // Check whether a given number is prime
{
     int i;
     for (i=0; prime[i]<=num; i++)
          if (num == prime[i])
              return 1;
     return 0;
}

void primelist (int *prime)
{
     int i,j;
     int StopTask = 0;
     prime[0]=2;
     prime[1]=3;
     prime[2]=EOF;
     for (i=3; ;i=i+2)
     {
          for (j=0; prime[j]!=EOF;j++)
               if (i % (prime[j]) == 0) {
                    StopTask = 1;
                    break;
               } if (!StopTask) {
                    prime[j] = i;
                    prime[j+1] = EOF;
               } StopTask = 0;
          if (prime[j] > 999999)
               return;
     }
}

int IntArraytoInt (int *IntArray, int NumLength)
{
     int i, temp = 0;
     
     for (i=0; i<NumLength; i++)
          temp += IntArray[i] * pow(10, i);
     return temp;
}

void DigitListing (int num, int *DigitList, int *NumofDigits)
{
     int i, j;
     
     for (i=0; i<7; i++)
          DigitList[i] = EOF;
     *NumofDigits = 0;
     i=0;
     DigitList [i++] = num % 10;
     while (num >= 10) {
          num /= 10;
          DigitList [i++] = num % 10;
     } for (j=0; DigitList[j]!=EOF; j++)
          ;
     *NumofDigits = j;
}

// The program gives answer 748317
// The 11 truncatable primes are: 2, 3, 5, 7, 23, 37, 53, 73, 313, 317, 373, 797, 3137, 3797, 739397

// Approach:
// 1. Create a list of Primes
// 2. Decompose the number into a digit store, each element representing a digit
// 3. If the first or last digit is non-prime, this number is bound not to be a both-side truncatable number. Thus prime numbers starting or ending with 1,4,6,8,9,0 are excluded.
// 4. For the remaining primes, truncate the first digit. Store the rest in the Lest-truncated array. Do the similar thing for the right-truncated array by truncate the last digit.
// 5 Convert both arrays back to integer to check the primality.
// 5.1 If yes, repeat step 4 and 5 until there is only one digit left (i.e. The last digit for left-truncated array, the first digit for right-truncated array). Because of step 3, the first and last digits are bound to be prime. Hence we conclude that if the loop goes uninterrupted to the last digit, the number satisfies the conditions in the question and is stored in the permanent array.
// 5.2 Otherwise, if in any step a non-prime number is obtained, the number is NOT a truncatable prime. The loop breaks and we progress to the next number
// 6. The sum is obtained by adding all elements in the permanent array in 5.1 together.