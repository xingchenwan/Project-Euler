//Problem 96
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

int SolveSudoku (int (*)[9]);
int main ()
{
     FILE *fp;
     char tempbuf[11], *raw[9] = {NULL};
     int z = 0, count = 0, SudoGrid[9][9];
     void convert (char **, int (*)[9]);
     int sum = 0;
     
     fp = fopen("/Users/Stellar/Desktop/ProjectEuler/InputDocs/p096_sudoku.txt", "r");
     while (fgets(tempbuf, 11, fp) != NULL) {
          tempbuf[strlen(tempbuf)-1] = '\0';
          if (!(count % 10)) {
               z = 0;
               if (!count)
                    ;
               else {
                    convert(raw, SudoGrid);
                    printf ("\nSukudo Number %d\n", count/10);
                    sum += SolveSudoku(SudoGrid);
               }
          } else
               raw[z++] = strdup (tempbuf);
          count ++;
     }
     printf ("\nRequired Sum = %d",sum);
     fclose(fp);
     return 0;
}

int SolveSudoku (int (* Grid)[9])
{
     int row, col, returnval;
     int NextUnfilledGrid (int (*)[9], int *, int *);
     bool hasConflict (int (*)[9], int, int, int);
     
     if (!NextUnfilledGrid(Grid, &row, &col)) { // If all grids are filled, solution is complete
          int temp = 100 * Grid[0][0] + 10 * Grid[0][1] + Grid[0][2];
          for (int i = 0; i < 9; i++) {
               for (int j = 0; j < 9; j++)
                    printf ("%d", Grid[i][j]);
               printf ("\n");
          }
          return temp;
     }
     for (int num = 1; num <= 9; num++) {
          if (hasConflict(Grid, row, col, num) == false) {
               Grid[row][col] = num;
               if ((returnval = SolveSudoku(Grid)))
                    return returnval;
               Grid[row][col] = 0;
          }
     }
     return 0;
}

bool hasConflict (int (*grid)[9], int row, int column, int val)
{
     void GridRange (int *, int *, int *, int *, int, int);
     int maxcol, mincol, maxrow, minrow; /* For locating the 3x3 grid area */
     
     for (int m = 0; m < 9; m++)
          if (grid[row][m] == val && m != column)
               return true; /* Check for conflicts in the current row */
     for (int n = 0; n < 9; n++)
          if (grid[n][column] == val && n != row)
               return true;  /* Check for conflicts in the current column */
     GridRange(&maxcol, &mincol, &maxrow, &minrow, row, column);
     for (int m = mincol; m <= maxcol; m++)
          for (int n = minrow; n <= maxrow; n++)
               if ((grid[n][m] == val) && (m != column) && (n != row)) /* Check for conflicts in the local 3x3 area */
                    return true;
     return false;
}

void GridRange (int *maxcol, int *mincol, int *maxrow, int *minrow, int row, int column)
{
     if (row >= 0 && row <= 2) {
          *minrow = 0;
          *maxrow = 2;
     } else if (row >= 3 && row <= 5) {
          *minrow = 3;
          *maxrow = 5;
     } else {
          *minrow = 6;
          *maxrow = 8;
     }
     if (column >= 0 && column <= 2) {
          *mincol = 0;
          *maxcol = 2;
     } else if (column >= 3 && column <= 5) {
          *mincol = 3;
          *maxcol = 5;
     } else {
          *mincol = 6;
          *maxcol = 8;
     }
}

int NextUnfilledGrid (int (*grid)[9], int *row, int *column) /* Find the next unfilled grid. Return 1 if there is unfilled grid, 0 otherwise*/
{
     for (int i = 0; i < 9; i++)
          for (int j = 0; j < 9; j++)
               if (!grid[i][j]) {
                    *row = i;
                    *column = j;
                    return 1;
               }
     return 0;
}

void convert (char **input, int (*output)[9])
{
     int row = 0, column = 0;

     for (row = 0; row < 9; row++)
          for (column = 0; column < 9; column++)
               output[row][column] = input[row][column] - '0';
}

// Ans: 24702
// Running Time: 242.0ms
// Solved using backtracking algorithm
// Pseudocode :

/*
 bool Solve(configuration conf)
 {
 if (no more choices)     // BASE CASE
 return (conf is goal state);
 for (all available choices) {
 try one choice c;
 // solve from here, if works out, you're done
 if (Solve(conf with choice c made) == true)
     return true;
 unmake choice c;
 }
 return false; // tried all choices, no soln found }

 Source: https://see.stanford.edu/materials/icspacs106b/Lecture11.pdf
*/
