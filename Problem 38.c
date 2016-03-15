// Project Euler: Problem 38

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define YES 1
#define NO 0

int DigitIncidence [10] = {0};
int ConcatenatedString [50];
void DigitListing (int, int *);
int concatenation (int *, int *);
int PandigitTester (int *);
int IntArraytoInt (int *, int);

int main()
{
     int i, DigitList[6] = {0}, StringLength=0, n, j;
     int Store = 0, PandigitNumber = 0;

     for (i=1; i<=9999; i++){
          for (j=0; j<50; j++)
               ConcatenatedString[j] = EOF;
          for (j=0; j<10; j++)
               DigitIncidence[j] = 0;
          n=1, StringLength = 0;
          while (StringLength < 9) {
               DigitListing(i*n, DigitList);
               StringLength = concatenation(ConcatenatedString, DigitList);
               n++;
          } if (StringLength == 9) {
               if (PandigitTester(ConcatenatedString)) {
                    PandigitNumber = IntArraytoInt(ConcatenatedString, StringLength);
                    if (PandigitNumber > Store)
                         Store = PandigitNumber;
               }
          } else
               PandigitNumber = 0;
     } printf ("%d", Store);
     return 0;
}

int concatenation (int *a, int *b)
// Concatenate string b to the back of string a, returning the length of the concatenated string
{
     int i=0, j;
     
     while (a[i] != EOF)
          i++;
     for (j=0;b[j]!=EOF;j++,i++)
          a[i] = b[j];
     return i;
}

int PandigitTester (int *DigitArray)
{
     int i,j;
     
     for (i=0; i<10; i++)
          DigitIncidence[DigitArray[i]]++;
     for (j=1; j<10; j++)
          if (DigitIncidence[j] != 1)
               return NO;
     return YES;
}

int IntArraytoInt (int *IntArray, int NumLength)
{
     int i, temp = 0,j;
     
     for (i=NumLength-1, j=0; i>=0; i--, j++)
          temp += IntArray[i] * pow(10, j);
     return temp;
}

void DigitListing (int num, int *DigitList)
{
     int i;
     int m, n, c;
     
     for (i=0; i<6; i++)
          DigitList[i] = EOF;
     i=0;
     DigitList [i++] = num % 10;
     while (num >= 10) {
          num /= 10;
          DigitList [i++] = num % 10;
     } for (m=0, n=i-1; m<n; m++, n--) {
          c = DigitList[m];
          DigitList[m] = DigitList[n];
          DigitList[n] = c;
     }
}

// The program gives answer 932718654
// Approach
// 1. Loop from 1 to 9999 (since we need to at least multiply the original number by 2, when original number exceeds 9999 it has five digits, and thus the concatenated string contains at least 10 digits which cannot be pandigital from 1 to 9)
// 2. While the number length is smaller than 9, multiply the number by 1,2,3.... Convert the number into a string and concatenate that string to a permanent string
// 3. When the number length is no longer smaller than 9. Check whether the length is exactly 9. If not, progress to the next number
// 4. If yes, check whether the number is panditigal. If yes and that number is larger than the number in the store, update the store with this number. Otherwise progress to the next number. When the entire loop finishes, print the value stored which is the largest pandital number we have found.