//Problem 94
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#define MAXDEPTH 14
#define MAXNUM 1000000000
long PerimeterSum = 0;
struct node {
     int *PythaTriple;
     struct node *Child1;
     struct node *Child2;
     struct node *Child3;
};
struct node *addtree (struct node *, int, int *, int);
int main ()
{
     struct node * root;
     
     printf ("%12s%12s%12s%15s\n","Side1","Side2","Side3","Perimeter");
     root = NULL;
     root = addtree(root, 0, NULL, 0);
     printf ("\nPerimeter sum below %d: %ld",MAXNUM,PerimeterSum);
     return 0;
}

int *intdrp (int *);
struct node * addtree (struct node *p, int depth, int *ParentTriple, int index)
/* Construct the ternary primitive Pythagorean tree (See "Tree of primitive Pythagorean triples") */
{
     int * LinTrans (int * input, int mode);
     int perimeter;
     
     if (depth < MAXDEPTH) {
          p = (struct node*) malloc (sizeof(struct node*));
          if (!depth) {
               int temp[3] = {3,4,5};
               p->PythaTriple = intdrp(temp);
          } else
               p->PythaTriple = LinTrans(ParentTriple, index);
         for (int i = 0; i < 2; i++) {
               if (abs(p->PythaTriple[2] - 2*p->PythaTriple[i]) <= 1) {
                    printf ("%12d %12d %12d", p->PythaTriple[2],p->PythaTriple[2], 2*p->PythaTriple[i]);
                    if ((perimeter = 2*p->PythaTriple[i] + 2*p->PythaTriple[2]) < MAXNUM) {
                        PerimeterSum += perimeter;
                        printf ("%12d\n", perimeter);
                        break;
                    } else
                         printf ("\nNumber Limit Exceeded! Decrease MAXDEPTH parameter\n");
               }
         }
          addtree (p->Child1, depth+1, p->PythaTriple, 1);
          addtree (p->Child2, depth+1, p->PythaTriple, 2);
          addtree (p->Child3, depth+1, p->PythaTriple, 3);
     }
     return p;
}

int * LinTrans (int *input, int mode) /* Linear Transformation to generate all primitive Pythagorean triples */
{
     int temp [3] = {0};
     if (mode == 1) {
          temp[0] = input[0]-2*input[1]+2*input[2];
          temp[1] = 2*input[0]-input[1]+2*input[2];
          temp[2] = 2*input[0]-2*input[1]+3*input[2];
     } else if (mode == 2) {
          temp[0] = input[0]+2*input[1]+2*input[2];
          temp[1] = 2*input[0]+input[1]+2*input[2];
          temp[2] = 2*input[0]+2*input[1]+3*input[2];
     } else {
          temp[0] = -input[0]+2*input[1]+2*input[2];
          temp[1] = -2*input[0]+input[1]+2*input[2];
          temp[2] = -2*input[0]+2*input[1]+3*input[2];
     }
     return intdrp(temp);
}

int * intdrp (int *input)
{
     int *p = malloc(sizeof(int)*3);
     for (int i = 0; i < 3; i++)
          p[i] = input[i];
     return p;
}

// Ans: 518408346
// Running-Time: 230.0ms
// Alternatively, by checking the formula of Heronian isoceles triangle (See wikipedia page), this problem can be solved with Pell's Equation (as in Problem 66)

/* Below is a brute force approach that generates almost-equilateral Heronian triangles up to 1 million. This can generate triangles up to 100 million based on the current try. However the implementation fails for 1 billion because the indexation size is too large */
/*
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#define MAXNUM 10000000
long long PerfectSq [MAXNUM/3] = {0};
long j;
int main()
{
     int i;
     long PerimeterSum = 0;
     int perimeter;
     bool hasIntegerArea (int, int);
 
     for (j = 1; j <= MAXNUM/3; j++)
          PerfectSq[j] = j*j;
     for (i = 3; i <= MAXNUM/3; i += 2) {
          if (hasIntegerArea(i, i-1) && ((perimeter = 3*i-1)<=MAXNUM)) {
               PerimeterSum += (3*i-1);
               printf ("%d %d %d %d\n", i,i,i-1, perimeter);
          } else if (hasIntegerArea(i, i+1) && ((perimeter = 3*i+1)<=MAXNUM)) {
               PerimeterSum += (3*i+1);
               printf ("%d %d %d %d\n", i,i,i+1, perimeter);
          }
     }
     printf ("%ld", PerimeterSum);
     return 0;
}

bool hasIntegerArea (int EqualSide, int DifferingSide)
{
     bool BinSearch (long long, long long *, long, long);
     long long HypotenuseSq = (long long)EqualSide * (long long)EqualSide;
     long long LegSq = (long long)(DifferingSide/2) * (long long)(DifferingSide/2);
     long long HeightSq = HypotenuseSq - LegSq;
     
     if (BinSearch(HeightSq, PerfectSq, 0, sqrt(j-1)))
          return true;
     return false;
}

bool BinSearch (long long element, long long * array, long Amin, long Amax)
{
     if (Amax < Amin)
          return false;
     else {
          long Amid = (Amin + Amax)/2;
          if (array[Amid] > element)
               return BinSearch(element, array, Amin, Amid-1);
          else if (array[Amid] < element)
               return BinSearch(element, array, Amid+1, Amax);
          else
               return true;
     }
}
*/