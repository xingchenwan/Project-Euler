// Problem 61

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

int nGon [6][141];

void ListFiller (void);
void Search (int, int *, int, int);
int main()
{
     int i, cond;
     int Checked [5] = {0};
     ListFiller();
     
     for (i = 19; i <= 58; i++) { // When 19 <= i <= 58, the range of numbers is 1000-9999
          if ((cond = nGon[5][i] % 100) < 10) // If the remainder is less than 10 (for e.g. 3204), the next cyclical number won't be a 4-digit number (e.g. 04XX = 4XX)
               ;
          else Search(cond, Checked, 0, nGon[5][i]);
     }
     return 0;
}

int Answers [6];
void Search
(int StartingDigits, /* First 2 digits of the 4-digit number */
 int Checked[5], /* Array to tell whether a n-Gon array has already been checked. If yes, skip this array. Since we start from the 8-gon array in main, the 8-gon array (nGon[5]) is always marked as "checked" so we only need an array of 5 elements to check nGon[0] to nGon[4] */
 int RecursiveLayer, /* Number of layers into the recursion. Initial 0 */
 int OriginalNum)
{
     int i, j, k;
     int NextStartingDigits;
     int LocalChecked [5];
     static int sum = 0;
     
     if (RecursiveLayer < 5) {
          for (i = 0; i < 5; i++) { // Check the 5 arrays from 3- to 7-gon only (nGon[0] to nGon[4])
               if (Checked[i] == 1) // If the current array is checked, progress to the next
                    ;
               else { // Otherwise, check this array
                    for (k = 0; k < 5; k ++)
                         LocalChecked[k] = Checked[k];
                    LocalChecked[i] = 1; // The array is now checked
          
                    for (j = 19; nGon[i][j] < (StartingDigits + 1) * 100; j++) {
                         if (!nGon[i][j])
                              ;
                         else if ((nGon[i][j] / 100 == StartingDigits) && ((NextStartingDigits = nGon[i][j] % 100) >= 10)) { // Check for any possible next cyclical number (with first 2 digits equal to the last 2 digits of the previous number)
                              Answers[RecursiveLayer + 1] = nGon[i][j];
                              Search(NextStartingDigits, LocalChecked, RecursiveLayer + 1, OriginalNum);
                         }
                    }
               }
          }
     } else { // After the program repeats itself for more than 5 iterations, check whether the last element and the initial number are in order
          if ((OriginalNum / 100) == (Answers[5] % 100)) {
               Answers[0] = OriginalNum;
               printf ("Found! The list of numbers are:\n");
               for (i = 0; i < 6; i++) {
                    printf (" %d", Answers[i]);
                    sum += Answers[i];
               }
               printf (",\nand the sum of which is %d.", sum);
               return;
          }
     }
}

void ListFiller (void)
{
     int n;
     for (n = 0; n < 141; n++)
     {
          if (n >= 45)
          nGon[0][n] = n * ( n + 1)/ 2;
          if (n >= 32 && n <= 99)
          nGon[1][n] = n*n;
          if (n >= 26 && n <= 81)
          nGon[2][n] = n*(3*n-1)/2;
          if (n >= 23 && n <= 70)
          nGon[3][n] = n*(2*n-1);
          if (n >= 21 && n <= 63)
          nGon[4][n] = n*(5*n-3)/2;
          if (n >= 19 && n <= 58)
          nGon[5][n] = n*(3*n-2);
     }
}

// The program gives answer 28684. Runtime 2.0ms
// The list of figurate cyclical numbers are 1281 8128 2882 8256 5625 2512