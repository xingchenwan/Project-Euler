// Problem 67
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAXLINE 100

int main()
{
     char buf [300];
     char *raw [100];
     int n = 0, *Numbers[100];
     int row, column;
     int choice1, choice2;
     void convert (char ** input, int **output);
     FILE *fp;
     
     fp = fopen("/Users/Stellar/Desktop/ProjectEuler/InputDocs/p067_triangle.txt", "r");
     if (fp == NULL) {
          printf ("Error opening the file.\n");
          return 1;
     }
     while (fgets (buf, 300, fp) != '\0')
          raw[n++] = strdup (buf);
     convert(raw, Numbers);
     for (row = MAXLINE - 2; row >= 0; row --) {
          for (column = 0; column <= row; column ++) {
               choice1 = Numbers[row][column] + Numbers[row+1][column];
               choice2 = Numbers[row][column] + Numbers[row+1][column+1];
               Numbers[row][column] = (choice1 > choice2) ? choice1 : choice2;
          }
     }
     printf ("%d", Numbers[0][0]);
     return 0;
}

void convert (char *input[], int *output[])
{
     int row = 0, column = 0;
     char buf [3];
     int i = 0, m = 0;
     
     for (row = 0; row < MAXLINE; row ++) {
          m = 0, i = 0;
          output[row] = (int *) malloc ((row + 1)*(sizeof(int)));
          for (column = 0; ; column ++) {
               if (isnumber(input[row][column])) {
                    buf[i++] = input[row][column];
               } else {
                    output[row][m++] = atoi (buf);
                    i = 0;
                    buf[0] = buf[1] = 0;
                    if (input[row][column] == '\n')
                         break;
               }
          }
     }
}

// Program gives answer 7273
// Runtime: 2.0ms