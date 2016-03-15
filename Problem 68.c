// Problem 68
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAXGON 10

struct combi {
     int * Combinations [11]; /* Combinations that share the same sum */
     int num_of_elements;
};
void Combinations1 (struct combi *, int, int);
void Combinations2 (struct combi, int, int);
int main()
{
     struct combi class [21];
     int i, j;
     
     for (i = 0; i <= 20; i++)
          class[i].num_of_elements = 0; // Initialise the struct
     Combinations1(class, 0, 1);
     for (j = 13; j <= 20; j++) {
          if (!class[j].num_of_elements)
               ;
          else
               Combinations2(class[j], 0, 0);
     }
     return 0;
}

void Combinations1 (struct combi * class, int RecursiveLayer, int StartingDigit) // 10C3
{
     int i,j,sum = 0;
     static int temp[3] = {0};
     int *p;
     
     if (RecursiveLayer < 3) {
          if (!RecursiveLayer)
               temp[0] = temp[1] = temp[2] = 0;
          for (i = StartingDigit; i <= MAXGON; i++) {
               temp[RecursiveLayer] = i;
               Combinations1(class, RecursiveLayer+1, i+1);
          }
     } else {
          if ((sum = (temp[0] + temp[1] + temp[2])) >= 13 &&
              sum <= 20) {
               /* Preliminary calculations show that valid range of possible sum is between 13 and 20. Read comments at the bottom of the program for explanations */
               p = malloc (sizeof(int) * 3);
               for (j = 0; j < 3; j++)
                    p[j] = temp[j]; // intdrp
               class[sum].Combinations[class[sum].num_of_elements] = p;
               class[sum].num_of_elements ++;
          }
     }
}

void Combinations2 (struct combi class, int RecursiveLayer, int StartingElement) // xC5
{
     int i, j;
     int m, n, NumIncidence[MAXGON+1] = {0}; // 1 to 10
     int a, count1 = 0, count2 = 0;
     static int * temp[MAXGON/2];
     
     if (RecursiveLayer < MAXGON/2) {
          if (!RecursiveLayer)
               for (m = 0; m < MAXGON/2; m++)
                    temp[m] = NULL;
          for (i = StartingElement; i < class.num_of_elements; i++) {
               temp[RecursiveLayer] = class.Combinations[i];
               Combinations2(class, RecursiveLayer+1, i+1);
          }
     } else {
          for (m = 0; m < MAXGON/2; m++) // MAXGON/2 pointers...
               for (n = 0; n < 3; n++) { // ... pointing to int arrays of 3
                    NumIncidence[temp[m][n]] ++;
                    if (NumIncidence[temp[m][n]] > 2)
                         return;
               }
          for (a = 1; a < MAXGON+1; a++) {
               if (NumIncidence[a] == 1)
                    count1++;
               else if (NumIncidence[a] == 2)
                    count2++;
          }
          if (count1 == count2 && count2 == 5) { // Five numbers appear exactly once, five appear exactly twice
               for (m = 0; m < MAXGON/2; m++)
                    if ((NumIncidence[temp[m][0]] == NumIncidence[temp[m][1]] &&
                         NumIncidence[temp[m][1]] == NumIncidence[temp[m][2]]))
                         return;
               for (i = 0; i < MAXGON/2; i++) {
                    printf ("\t");
                    for (j = 0; j < 3; j++)
                         printf ("%d,",temp[i][j]);
               } printf ("\n");
          }
     }
}
// The program outputs read:

////////////////////////////////////////////
//1,3,10,	1,4,9,	2,4,8,	2,5,7,	3,5,6,//
//1,5,10,	1,7,8,	2,4,10,	3,4,9,	3,6,7,//
//1,5,10,	1,7,8,	2,5,9,	3,4,9,	3,6,7,//
//1,6,10,	1,7,9,	2,7,8,	3,4,10,	4,5,8,//
//1,6,10,	2,6,9,	2,7,8,	3,4,10,	4,5,8,//
//1,8,10,	2,7,10,	3,7,9,	4,6,9,	5,6,8,//
////////////////////////////////////////////

// The sum of any three numbers from 1 to 10 ranges from 6 to 27. However, to constitute a set of solution to the 5-gon ring, the following condition must be satisfied
// 1. The sum must share more than or equal to 5 different possible combinations (e.g. the only possible way to get sum 6 is 1,2,3. Hence 6 is excluded. Using this reasoning, sum = 6 thru 10 and 23 thru 27 is excluded.)
// 2. The five triplets must have all numbers from 1 - 10 (1 thru 10 pandigital) (e.g. for sum = 11; number 10 did not appear hence is excluded. using this reasoning, sum = 11, 12, 21, 22 are excluded).
// In function Combination2, we do further filtering on possible sums.
// 3. 5 of the numbers must appear exactly once, the other exactly twice. (once for external nodes, twice for internal nodes)
// 4. In each triplets, two of which must be internal nodes (appeared twice). If all three numbers have appeared the same time, this combination is rejected as it is not possible to have three internal or external nodes on the same line.
// After these four stages, we have narrowed down the search range to the output shown above. All six arragements are solution to the 5-gon ring and we now need to find the one with largest concatecated number.

// Next, We compare the smallest external node (smallest number that only appeared once) for each solution, which is the first digit in the concatecated 16- or 17-digits number. In first solution, 6. 2nd, 2. 3rd, 2. 4th, 2. 5th, 1, 6th, 1. Hence the largest first external node is found in the first solution
// In each solution, there are two possible arragements in clockwise direction from the smallest external node. They are
// 1) Internal nodes: 3,5,2,4,1. External nodes: 6,7,8,9,10 Concatecated number :6357528249411013
// 2) Internal nodes: 5,3,1,4,2. External nodes: 6,10,9,8,7 Concatecated number :6531031914842725
// We can see that the second number is larger in value. Hence it is the desired answer.

// Runtime: 2.0ms