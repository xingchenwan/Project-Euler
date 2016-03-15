//Problem 86
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#define MAXSIZE 2000
#define MAXSOLN 1000000

int main()
{
     int l, w, h; /* Length, Width and Hypotunese */
     int ShortestPathSq;
     int SolnCount = 0;
     bool isSquare (int num);
     
     for (l = 1; l < MAXSIZE; l++)
          for (w = 1; w <= l; w++)
               for (h = 1; h <= w; h++) { /* h <= w <= l */
                    ShortestPathSq =  (pow(l,2) + pow ((w + h), 2));
                    if (isSquare(ShortestPathSq))
                         SolnCount ++;
                    if (SolnCount > MAXSOLN)
                         goto print;
               }
     print:
     printf ("%d", l);
     return 0;
}

bool isSquare (int num)
{
     double rootsq = sqrt ((double) num);
     if (rootsq == (int)rootsq)
          return 1;
     return 0;
}
// Answer: 1818 (Brute-Force T_T)
// Using formula : Shortest path = sqrt (l^2 + (w+h)^2) where l >= w >= h

// Alternatively, using problem 75 algorithm to compute all primitive Pythagorean triples to an arbitrarily set limit, and find out the number of solutions for each of these triples. Any non-primitive Pythagorean triples (i.e. those multiples of primitive ones) will have the same number of solutions as their primitive parents. Keep adding until we reach 1 million.