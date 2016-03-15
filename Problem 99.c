//Problem 99
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#define BUFSIZE 30
int main ()
{
     void ReadFile (char *, int *, int *);
     bool NumCmp (int *, int *);
     FILE *fp;
     char buf [30];
     int CurrentNum [2] = {0};
     int LargestNum [2] = {0};
     int CurrentIndex = 1, MaxIndex = 0;
     
     fp = fopen("/Users/Stellar/Desktop/ProjectEuler/InputDocs/p099_base_exp.txt", "r");
     while (fgets(buf, BUFSIZE, fp) != '\0') {
          buf[strlen(buf)-1] = '\0';
          ReadFile(buf, &CurrentNum[0], &CurrentNum[1]);
          if (NumCmp(CurrentNum, LargestNum)) {
               LargestNum[0] = CurrentNum[0];
               LargestNum[1] = CurrentNum[1];
               MaxIndex = CurrentIndex;
          }
          CurrentIndex++;
          for (int i = 0; i < BUFSIZE; i++)
               buf[i] = '\0';
     }
     printf ("Max number occurs at Line %d. Total Line: %d", MaxIndex, CurrentIndex);
     return 0;
}

void ReadFile (char *input, int *base, int *exp)
{
     char BaseTemp [10] = {0}, ExpTemp[10] = {0};
     int i = 0, j = 0;
     
     while (isnumber(input[i])) {
          BaseTemp[i] = input[i];
          i++;
     } BaseTemp[i] = '\0';
     *base = atoi(BaseTemp);
     while (isnumber(input[++i]))
          ExpTemp[j++] = input[i];
     ExpTemp[i] = '\0';
     *exp = atoi(ExpTemp);
}

bool NumCmp (int * Current, int * Max)
{
     if (!Max[0])
          return true;
     double ExpRatio = (double) Current[1] / (double) Max[1]; // Cell 1 is exponent
     if (pow(Current[0], ExpRatio) > Max[0])
          return true;
     return false;
}

// Ans: 709
// Running Time: 2.0ms