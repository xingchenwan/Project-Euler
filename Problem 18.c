// Problem 18

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

void convert (char *input, int output[15][15]);

int main()
{
     int Triangular [15][15] = {0};
     int i, j, a, b;
     char SourceFile [] = "75 95 64 17 47 82 18 35 87 10 20 04 82 47 65 19 01 23 75 03 34 88 02 77 73 07 63 67 99 65 04 28 06 16 70 92 41 41 26 56 83 40 80 70 33 41 48 72 33 47 32 37 16 94 29 53 71 44 65 25 43 91 52 97 51 14 70 11 33 28 77 73 17 78 39 68 17 57 91 71 52 38 17 14 91 43 58 50 27 29 48 63 66 04 68 89 53 67 30 73 16 69 87 40 31 04 62 98 27 23 09 70 98 73 93 38 53 60 04 23";

     convert(SourceFile, Triangular);
     for (i=13; i>=0; i--)
          for (j=0; Triangular[i][j]!=0; j++) {
               a = Triangular[i][j] + Triangular[i+1][j];
               b = Triangular[i][j] + Triangular[i+1][j+1];
               Triangular[i][j] = (a>b)? a:b;
          } printf ("%d", Triangular[0][0]);
     return 0;
}

void convert (char *input, int output[15][15])
{
     int i = 0, row = 0, column = 0, temp, m=0;
     char buf[2];
     buf[0] = EOF;
     
     while (input[i]!='\0') {
          if (input[i] == '\n' || input[i] == ' ') {
               if (buf[0] != EOF) {
                    temp = atoi (buf);
                    if (column < row)
                    output[row][column++] = temp;
                    else {
                         output[row][column] = temp;
                         ++ row;
                         column = 0;
                    } buf[0] = EOF;
                    m = 0;
                    i++;
               } else i++;
          }
          
          else if (isnumber(input[i]))
               while (isnumber(input[i])) {
                    buf[m++] = input[i++];
               }
          
          else i++;
          
          output [14][14] = 23;
     }
}

// Approach: DP: From bottom line upwards.