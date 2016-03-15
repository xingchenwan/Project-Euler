//Problem 81
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MATRIXSIZE 80

int main()
{
     char buf [500], *raw[500];
     int *Numbers[MATRIXSIZE], z = 0;
     int m = 0,n = 0,sum = 0;
     FILE *fp;
     void convert (char **, int **);
     
     fp = fopen ("/Users/Stellar/Desktop/ProjectEuler/InputDocs/p081_matrix.txt", "r");
     if (fp == NULL) {
          printf ("Error opening the file.\n");
          return 1;
     }
     while (fgets (buf, 500, fp)!= '\0')
          raw[z++] = strdup (buf);
     convert (raw, Numbers);
     for (m = 1; m < MATRIXSIZE; m++)
          Numbers[m][0] += Numbers[m-1][0];
     for (n = 1; n < MATRIXSIZE; n++)
          Numbers[0][n] += Numbers[0][n-1];
     for (m = 1; m < MATRIXSIZE; m++)
          for (n = 1; n < MATRIXSIZE; n++) {
               if (Numbers[m-1][n] < Numbers[m][n-1])
                    Numbers[m][n] += Numbers[m-1][n];
               else
                    Numbers[m][n] += Numbers[m][n-1];
          }
     printf ("%d", Numbers[MATRIXSIZE-1][MATRIXSIZE-1]);
     return 0;
}

void convert (char **input, int **output)
{
     int row = 0, column = 0;
     char buf [5], c;
     
     for (row = 0; row < MATRIXSIZE; row ++) {
          int m = 0, i = 0;
          output[row] = (int *) malloc (MATRIXSIZE*(sizeof(int)));
          for (column = 0; ; column ++){
               if (isnumber(input[row][column])) {
                    buf[i++] = input[row][column];
               } else {
                    output[row][m++] = atoi (buf);
                    i = 0;
                    for (c = 0; c < 5; c++)
                         buf[c] = 0;
                    if (input[row][column] == '\n')
                         break;
               }
          }
     }
}

// Answer: 427337
// DP approach