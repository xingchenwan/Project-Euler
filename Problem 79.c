//Problem 79
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAXGUESS 50
#define BUFSIZE 4
#define DIGITLENGTH 8

int *guess[MAXGUESS+1];
int main()
{
     int AppearedDigits[]= {1,2,3,6,7,8,9,0};
     void permutation (int *, int, int);
     int * intdup (int *);
     int n = 0, i;
     char buf[BUFSIZE];
     int intbuf[BUFSIZE-1] = {0};
     FILE *fp;
     
     fp = fopen ("/Users/Stellar/Desktop/ProjectEuler/InputDocs/p079_keylog.txt", "r");
     if (fp == NULL) {
          printf ("Error opening the file.\n");
          return 1;
     }
     while (fgets(buf, BUFSIZE, fp)!= '\0') {
          for (i = 0; buf[i] != '\0' && buf[i] != '\n'; i++)
               intbuf[i] = buf[i] - '0';
          guess[n++] = intdup (intbuf);
     }
     permutation (AppearedDigits,0,(sizeof(AppearedDigits)/sizeof(int)));
     return 0;
}

void permutation (int *digits, int CurrentDigit, int ArraySize)
{
     int i,j;
     void swap (int *, int *);
     int KeylogTester (int *);
     
     if (CurrentDigit == ArraySize) {
          if (KeylogTester(digits)) {
               for (j=0; j<ArraySize; j++)
                    printf ("%d",digits[j]);
               printf (" Found\n");
               return;
          }
     } else {
          for (i=CurrentDigit; i<ArraySize; i++) {
               swap (&digits[CurrentDigit], &digits[i]);
               permutation (digits,CurrentDigit+1, ArraySize);
               swap (&digits[CurrentDigit], &digits[i]);
          }
     }
}

int KeylogTester (int *digits)
{
     int i = 0,j,a,b,c;
     a = b = c = EOF;
     while (guess[i] != NULL) {
          for (j = 0; j < DIGITLENGTH; j++) {
               if (digits[j] == guess[i][0])
                    a = j;
               else if (digits[j] == guess[i][1])
                    b = j;
               else if (digits[j] == guess[i][2])
                    c = j;
          } if (a < b && b < c)
               i++;
          else
               return 0;
     }
     return 1;
}

void swap (int *a, int *b)
{
     int temp;
     
     temp = *a;
     *a = *b;
     *b = temp;
}

int * intdup (int *array) // strdup: int array version
{
     int i = 0;
     int *p;
     
     p = (int *) malloc ((sizeof(int)*BUFSIZE));
     for (i = 0; i < BUFSIZE-1; i++)
          p[i] = array[i];
     return p;
}

// The program gives answer 73162890
// Running Time: 3.0ms
