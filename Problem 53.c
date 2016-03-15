// Problem 53

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define UNREAD -1;

int main() // Dynamic Programming Method
{
     int grid [101][101];
     int n,r, counter = 0;
    
     for (n=0; n<101; n++)
          for (r=0;r<101;r++)
               grid[n][r] = UNREAD;
     for (n=0; n<101; n++)
          grid[n][0] = 1; // nC0=1, for n>=0
     for (n=0; n<101; n++)
          for (r=n+1; r<101; r++)
               grid[n][r] = 0; // for r>n, nCr = 0
     for (r=1; r<101; r++) // nCr = (n-1)Cr + (n-1)C(r-1)
          for (n=1; n<101; n++) {
               grid[n][r] = grid[n-1][r] + grid[n-1][r-1];
               if (grid[n][r] > 1000000) {
                    counter += (101 - n);
                    break;
               }
          } printf ("%d", counter);
     return 0;
}

// Brute force Method: Calculate all combinations
void Combination (int RecursiveLayer,int n,int r,int StartingDigit,int *Result) // for nCr
{
     int i;
     if (RecursiveLayer < r) {
          for (i = StartingDigit; i < n; i++) {
               Combination(RecursiveLayer+1, n, r, i+1, Result);
          }
     } else
          (*Result)++;
}
// The program gives answer 4075
// Runtime 2.0ms