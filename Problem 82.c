//Problem 82
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MATRIXSIZE 80

int main()
{
     char buf [500], *raw[500];
     int *Numbers[MATRIXSIZE], z = 0;
     int min_path[MATRIXSIZE][MATRIXSIZE] = {0};
     int m,n,i,j,LocalStore = 0, LocalMin = 0, min_sum = INFINITY;
     FILE *fp;
     void convert (char **, int **);
     
     fp = fopen ("/Users/Stellar/Desktop/ProjectEuler/InputDocs/p082_matrix.txt", "r");
     if (fp == NULL) {
          printf ("Error opening the file.\n");
          return 1;
     }
     while (fgets (buf, 500, fp)!= '\0')
          raw[z++] = strdup (buf);
     convert (raw, Numbers);
     for (m = 0; m < MATRIXSIZE; m++)
          min_path[m][0] = Numbers[m][0];
     for (n = 1; n < MATRIXSIZE; n++)
          for (m = 0; m < MATRIXSIZE; m++) {
               LocalStore = INFINITY;
               for (i = 0; i < MATRIXSIZE; i++) {
                    LocalMin = min_path[i][n-1] + Numbers[m][n];
                    if (i < m)
                         for (j = i; j < m; j++)
                              LocalMin += Numbers[j][n];
                    else if (i > m)
                         for (j = m + 1; j <= i; j++)
                              LocalMin += Numbers[j][n];
                    LocalStore = (LocalMin < LocalStore)? LocalMin : LocalStore;
               }
               min_path[m][n] = LocalStore;
          }
     for (n = 0; n < MATRIXSIZE; n++)
          min_sum = (min_path[n][MATRIXSIZE-1] < min_sum)? min_path[n][MATRIXSIZE-1] : min_sum;
     printf ("%d", min_sum);
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
// Answer: 260324
// Running Time: 14.0ms

// Approach: (Taking this 5x5 matrix for illustration purposes)
// NUMBER MATRIX
// 16    42     8     4    79
// 6      7     8    23    10
// 13    23    13    14    15
// 16    80    18    43    20
// 21    22    34    24    8

// We need to find the miminally-valued path from any cell from the left to the right. We now have a 5x5 matrix of min_path[5][5], with each cell representing the minimal distance from the leftist column to the current element (e.g. min_path[3][4] represents the minimally-valued path from cell numbered 14 to any cell in the leftist column).
// Since the distance to itself is always 0, the min_path for the first column is same as the number value itself. Thus for the min_path column, we have
// MIN_PATH MATRIX
// 16 >   ?     ?    ?    ?
//        v
// 6  >   ?     ?    ?    ?
//        v
// 13 >  [?]    ?    ?    ?
//        ^
// 16 >   ?     ?    ?    ?
//        ^
// 21 >   ?     ?    ?    ?
// We then need to consider the second column. Starting from the first row, we calculate the min_path for each element of column 2 by checking the min_path values for the previous column. For the min value from (0,0) to (0,1), we have 16+42 = 58. Although we may choose other paths but 16 and 42 are inevitably included so the sum of any other path is definitely larger than 58 so they can be safely ignored.
// We then continue to calculate the min val from (1,0) to (0,1). Note that the first move is always to the right, as if we go upwards we have 6->16->42, which repeats 16->42. Also we cannot go downwards for 6->13->23->7->42, as this detour is definitely larger in value than 6->7->42. Thus, the min value of (1,0) to (0,1) is 55.
// Likewise we do the same for (2,0), (3,0)... The smallest min value from these gives the min_path. Taking the above diagram for example, to compute min_path[2][1], we compare values min_path[0][0]+numbers[0][1]+numbers[1][1]+numbers[2][1]; minpath[1][0] + numbers[1][1]+numbers[1][2]; minpath[2][0]+numbers[1][2]; minpath[3][0] + numbers[3][1] + numbers[2][1] and lastly minpath[4][0]+numbers[4][1]+numbers[3][1]+numbers[2][1]. The smallest of the above would be min_path[2][1].
// We then repeat the entire process for the second row, third row until we have the second column for min_path matrix. We then repeat the process until min_path is completely filled. Each cell of the last column of min_path represents a route from the 1st column to the last. Then we find the answer, which is the smallest-valued cell of the last column.

