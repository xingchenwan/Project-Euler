// Project Euler: Problem 22
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define YES 1
#define NO 0

int qsort_comp (const void *, const void *);
int main()
{
   char buf [1000000];
   char *NameStorage[5163]; // The series is found to contain 5192 names
   int ScoreStorage[5163];
   int op1=0;
   long sum = 0;
   int i = 0, j = 0, k = 0;
   FILE *fp;
   
   for (i=0; i<=5163; i++)
      NameStorage[i] = malloc(20);
   fp = fopen ("/Users/Stellar/Desktop/ProjectEuler/InputDocs/p022_names.txt","r");
      if (fp == NULL)
      {  printf ("Error opening the file.\n");
         return 1;
      }
   fgets (buf, 1500000, fp);
   for (i=0; (buf[i]!=EOF) && (buf[i]!='\0'); i++) {
      if (!isalpha (buf[i]))
            continue;
      else {
         while (isalpha(buf[i])) {
         NameStorage[j][k] = buf[i];
         i++,k++;
           }
         j++, k=0;
      }
   }
   qsort (NameStorage,5163,sizeof(NameStorage[0]),qsort_comp);
   for (i=0; i<=5163; i++) {
      op1 = 0;
      for (j=0; isalpha(NameStorage[i][j]); j++)
         op1 += (NameStorage[i][j] -'A' + 1);
      
      ScoreStorage[i] = op1 * (i+1);
      sum += ScoreStorage[i];
   }
   printf ("%lu", sum);
   return 0;
}

int qsort_comp(const void *a, const void *b)
{ return strcmp(*(char**)a, *(char**)b);}

// The answer given by the program is 871198282.