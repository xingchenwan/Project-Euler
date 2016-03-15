//Problem 91
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#define BOUNDARY 50
struct pt {
     signed x;
     signed y;
};
int main()
{
     struct pt A;
     struct pt B;
     int i, j;
     int m, n;
     int count = 0, DistinctPtPair = 0;
     int isRightAngled (struct pt, struct pt);
     bool Tested [BOUNDARY+1][BOUNDARY+1] = {0};
     
     Tested[0][0] = true;
     for (i = 0; i <= BOUNDARY; i++)
          for (j = 0; j <= BOUNDARY; j++) {
               if (Tested[i][j] == false) {
                    A.x = i;
                    A.y = j;
               for (m = 0; m <= BOUNDARY; m++)
                    for (n = 0; n <= BOUNDARY; n++) {
                         B.x = m;
                         B.y = n;
                         if ((m == i && n == j) || (Tested[m][n] == true))
                              ;
                         else {
                              DistinctPtPair ++;
                              if (isRightAngled(A, B)) {
                                   count ++;
                              }
                         }
                    }
               }
               Tested[i][j] = true;
          }
     printf ("Right Angle Triangle Count = %d when boundary is (0,0),(%d,0),(0,%d),and(%d,%d).\n", count, BOUNDARY,BOUNDARY,BOUNDARY,BOUNDARY);
     printf ("Number of distinct point pairs = %d\n", DistinctPtPair);
     return 0;
}

int isRightAngled (struct pt point1, struct pt point2) /* Test whether the triangle formed by origin, point1 and point 2 is right-angled */
{
     int
     a = point1.x*point1.x+point1.y*point1.y,
     b = point2.x*point2.x+point2.y*point2.y,
     c = (point1.x - point2.x) * (point1.x - point2.x)  + (point1.y - point2.y) * (point1.y - point2.y);
     
     if (a+b==c || a+c==b || b+c==a)
          return 1;
     return 0;
}

// Answer: 14234
// Running Time: 15.0ms

// Enumerate all possible point pairs
// Test whether the pairs along with the origin form a right-angle triangle