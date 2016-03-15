// Project Euler: Problem 42
// ReadFile section borrowed from Solution 22

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int TriangularList [72] = {0};
void TriangularNumGen ( int * TriangularList);
int TriangularTester (int num);

int main()
{
     char buf [16345];
     char *WordStorage[1786];
     FILE *fp;
     int i, j=0, k=0, LocalWordScore, GlobalCounter=0;
     
     TriangularNumGen(TriangularList);
     for (i=0; i<1786; i++)
          WordStorage[i] = malloc(20);
     fp = fopen ("/Users/Stellar/Desktop/ProjectEuler/InputDocs/p042_words.txt", "r");
     if (fp == NULL)
     {    printf ("Error opening files. \n");
          return 1;
     } fgets (buf, 16345, fp);
     for (i=0; (buf[i]!=EOF) && (buf[i]!='\0'); i++) {
          if (!isalpha (buf[i]))
               continue;
          else {
               while (isalpha(buf[i])) {
                    WordStorage[j][k] = buf[i];
                    i++,k++;
               } j++, k=0;
          }
     }
     for (i=0; i<1786; i++) {
          LocalWordScore = 0;
          for (j=0; isalpha(WordStorage[i][j]); j++)
               LocalWordScore += (WordStorage[i][j] -'A' + 1);
               if (TriangularTester(LocalWordScore))
                    GlobalCounter++;
     }
     printf ("%d", GlobalCounter);
     return 0;
}

int TriangularTester (int num)
{
     int i;
     for (i=0; TriangularList[i]<=num; i++)
          if (TriangularList[i] == num)
               return 1;
     return 0;
}
void TriangularNumGen ( int * TriangularList)
{
     int i;
     for (i=1; TriangularList[i]<=2600; i++)
          TriangularList [i] = i * (i+1) / 2;
}

// The Program gives answer 162
