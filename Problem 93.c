//Problem 93
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#define SELECTION 4
#define MAXNUM 3024 /* 3024 = 6*7*8*9 */
int Digits [] = {1,2,3,4,5,6,7,8,9};
void Combinations (int, int, int, int *);
int main()
{
     int result [4] = {0};
     
     printf ("START\n");
     Combinations(0, SELECTION, 0, result);
     printf ("END");
     return 0;
}

void Combinations (int RecursiveLayer, int r, int StartingDigit, int *Result)
{
     int i;
     int LargestNum (int *);
     static int LongestSeq = 0;
     
     if (RecursiveLayer < r) {
          for (i = StartingDigit; i <= 5 + RecursiveLayer; i++) {
               Result[RecursiveLayer] = Digits[i];
               Combinations(RecursiveLayer+1, r, i+1, Result);
          }
     } else if (LargestNum(Result) > LongestSeq) {
          LongestSeq = LargestNum(Result);
          printf ("Longest Sequence = %d\nConcatenated Digits = ", LongestSeq);
          for (int i = 0; i < SELECTION; i++)
               printf ("%d", Result[i]);
          printf ("\n");
     }
}

int LargestNum (int * input) /* Returns the largest number in the consecutive chain from 1 to n */
{
     void OrderPermutations (int *, int, bool *);
     bool NumberOccurrence [MAXNUM] = {false};
     int i = 1;
     
     OrderPermutations(input, 0, NumberOccurrence);
     while (NumberOccurrence[++i])
          ;
     return i-1;
}

void OrderPermutations (int *input, int CurrentDigit, bool *Incidence)
/* 4! ways of arranging the 4 chosen digits for each iteration */
{
     int i;
     void swap (int *a, int *b);
     void SignPermutations (int *, bool*);
     
     if (CurrentDigit == 4)
          SignPermutations(input, Incidence);
     else {
          for (i = CurrentDigit; i < 4; i++) {
               swap(&input[CurrentDigit], &input[i]);
               OrderPermutations(input, CurrentDigit+1, Incidence);
               swap(&input[CurrentDigit], &input[i]);
          }
     }
}

void SignPermutations (int *input, bool * Incidence)
/* Insert signs into the 4 digits */
{
     double temp1,temp2,Final;
     double ArithOperation (int, double, double);
     int i,j,k;
     
     for (i = 1; i <= 4;i++) {
          temp1 = ArithOperation(i, input[0], input[1]);
          for (j = 1; j <= 4; j++) {
               temp2 = ArithOperation(j, temp1, input[2]);
               for (k = 1; k <= 4; k++) {
                    if ((Final = ArithOperation(k, temp2, input[3])) > 0) {
                         if (fabs(Final - (int)Final) < 0.001)
                              Incidence[(int)Final] = true;
                         else if (fabs(Final - (int)(Final+1)) < 0.001)
                              Incidence[(int)(Final+1)] = true; /* Implementations to avoid round-off errors with 'double'-typed numbers */
                    }
               }
          }
     }
     for (i = 1; i <= 4; i++) {
          temp1 = ArithOperation(i, input[0], input[1]);
          for (j = 1; j <= 4; j++) {
               temp2 = ArithOperation(j, input[2], input[3]);
               for (k = 1; k <= 4; k++) {
                    if ((Final = ArithOperation(k, temp1, temp2)) > 0) {
                         if (fabs(Final - (int)Final) < 0.001)
                              Incidence[(int)Final] = true;
                         else if (fabs(Final - (int)(Final+1)) < 0.001)
                              Incidence[(int)(Final+1)] = true;
                    }
               }
          }
     }
}

double ArithOperation (int mode, double operand1, double operand2)
{
     switch (mode) {
          case 1:
               return operand1 + operand2;
          case 2:
               return operand1 - operand2;
          case 3:
               return operand1 * operand2;
          case 4:
               if (!operand2) {
                    printf ("ERROR\n");
                    return 0;
               } return operand1 / operand2;
     }
     return 0;
}

void swap (int *a, int *b)
{
     int temp;
     
     temp = *a;
     *a = *b;
     *b = temp;
}

// Answer: 1258, with 51 consecutive numbers from 1 to 51
// Running-time: 5.0ms