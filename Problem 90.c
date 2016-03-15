//Problem 90
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define SELECTION 6
int Candidates [] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int Cube1 [6];
int Cube2 [6];
int count = 0;
int RequiredDigits [9][2] = {{0, 1}, {0, 4}, {0, 9}, {1, 6}, {2, 5}, {3, 6}, {4, 9}, {6, 4}, {8, 1}};
int main()
{
     void Combinations (int, int, int, int*);
     
     Combinations(0, SELECTION, 0, Cube1);
     printf ("%d", count/2); /* Every distinct combination of (Cube1, Cube2) is repeated exactly once for (Cube2, Cube1), thus the count needs to be halved to get the correct answer */
     return 0;
}

int CondTester (void);
void Combinations (int RecursiveLayer, int r, int StartingDigit, int *Result)
{
     int i;
     
     if (RecursiveLayer < r) {
          for (i = StartingDigit; i <= 4 + RecursiveLayer; i++) {
               Result[RecursiveLayer] = i;
               Combinations(RecursiveLayer+1, r, i+1, Result);
          }
     } else {
          if (Result == Cube1)
               Combinations(0, SELECTION, 0, Cube2);
          else if (CondTester())
               count ++;
     }
}

int CondTester (void)
{
     int Search (int, int *);
     int i;
     
     for (i = 0; i < 9; i++) {
          if ((Search(RequiredDigits[i][0], Cube1) && Search(RequiredDigits[i][1], Cube2)) ||
              (Search(RequiredDigits[i][0], Cube2) && Search(RequiredDigits[i][1], Cube1)))
               ;
          else return 0;
     } return 1;
}

int Search (int element, int *set)
{
     int i;
     for (i = 0; i < SELECTION; i++) {
          if (set[i] == element)
               return 1;
          if (set[i] == 6 && element == 9) /* 6 and 9 are inter-changeable */
               return 1;
          if (set[i] == 9 && element == 6)
               return 1;
     } return 0;
}
// Answer: 1217
// Running Time: 6.0ms
// Basically find all combinations of the two cubes, (10C6 ^ 2), test whether each combination fulfills the condition