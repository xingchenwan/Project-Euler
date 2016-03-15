//Problem 83
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MATRIXSIZE 80
#define MAXVAL 9999999

int main()
{
     char buf [500], *raw[500];
     int *Numbers[MATRIXSIZE], z = 0;
     int min_path[MATRIXSIZE][MATRIXSIZE], Tested[MATRIXSIZE][MATRIXSIZE] = {0};
     int m,n,i,j;
     int temp; /* temporary variable */
     int SmallestElement; /* to record the smallest element of the four adjacent cell of the current cell */
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
          for (n = 0; n < MATRIXSIZE; n++)
               min_path[m][n] = MAXVAL;
     min_path[0][0] = Numbers[0][0], Tested[0][0] = 1;
     i = 0; j = 0; /* Starting from the top-left origin */
     while (1) {
          SmallestElement= MAXVAL;
          if ((i > 0) && (!Tested[i-1][j]))  /* Test four adjacent and untested nodes, if applicable. */
               min_path[i-1][j] = ((temp = Numbers[i-1][j] + min_path[i][j]) < min_path[i-1][j])? temp : min_path[i-1][j];
          if ((i < MATRIXSIZE-1) && (!Tested[i+1][j]))
                min_path[i+1][j] = ((temp = Numbers[i+1][j] + min_path[i][j]) < min_path[i+1][j])? temp : min_path[i+1][j];
          if ((j > 0) && (!Tested[i][j-1]))
               min_path[i][j-1] = ((temp = Numbers[i][j-1] + min_path[i][j]) < min_path[i][j-1])? temp : min_path[i][j-1];
          if ((j < MATRIXSIZE-1) && (!Tested[i][j+1]))
               min_path[i][j+1] = ((temp = Numbers[i][j+1] + min_path[i][j]) < min_path[i][j+1])? temp : min_path[i][j+1];
          for (m = 0; m < MATRIXSIZE; m++)
               for (n = 0; n < MATRIXSIZE; n++) {
                    if (min_path[m][n] == MAXVAL) /* Since Dijkstra's algorithm expands from origin downwards and rightwards, once we reach a cell with infinite weight, all subsequent cells right or down to it will all have infinite weight so we can safely break the loop */
                         break;
                    else if (!Tested[m][n]) { /* Exclude tested nodes */
                         if (min_path[m][n] < SmallestElement) {
                              SmallestElement = min_path[m][n];
                              i = m, j = n; /* Choose the untested node with the smallest path sum to the origin */
                         }
                    } else
                         continue;
               }
               Tested[i][j] = 1; /* Mark the node as tested. A tested node will not be visited again */
          if (Tested[MATRIXSIZE-1][MATRIXSIZE-1]) { /* stop the program when the destination cell is tested */
               printf ("%d", min_path[MATRIXSIZE-1][MATRIXSIZE-1]);
               return 0;
          }
     }
     return 1;
}

void convert (char **input, int **output)
{
     int row = 0, column = 0;
     char buf [5], c;
     
     for (row = 0; row < MATRIXSIZE; row ++) {
          int m = 0, i = 0;
          output[row] = (int *) malloc (MATRIXSIZE*(sizeof(int)));
          for (column = 0; ; column ++) {
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

// Answer: 425185
// Running Time: 44.0ms
// Dijkstra's Algorithm for single-source shortest path finding
// Pseudocode from Wikipedia:

/*
function Dijkstra(Graph, source):
2
3      dist[source] <- 0                       // Distance from source to source
4      prev[source] <- undefined               // Previous node in optimal path initialization
5
6      create vertex set Q
7
8      for each vertex v in Graph:             // Initialization
9          if v ≠ source:                      // v has not yet been removed from Q (unvisited nodes)
10              dist[v] <- INFINITY             // Unknown distance from source to v
11              prev[v] <- UNDEFINED            // Previous node in optimal path from source
12          add v to Q                          // All nodes initially in Q (unvisited nodes)
13
14      while Q is not empty:
15          u <- vertex in Q with min dist[u]    // Source node in the first case
16          remove u from Q
17
18          for each neighbor v of u:           // where v is still in Q.
19              alt <- dist[u] + length(u, v)
20              if alt < dist[v]:               // A shorter path to v has been found
21                  dist[v] <- alt
22                  prev[v] <- u
23
24      return dist[], prev[]
 */
