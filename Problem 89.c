//Problem 89
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int main()
{
     char tempbuf [30] = {0};
     int CharSaved (char *);
     int saved = 0;
     FILE *fp;
     
     fp = fopen("/Users/Stellar/Desktop/ProjectEuler/InputDocs/p089_roman.txt", "r");
     while (fgets(tempbuf, 30, fp) != NULL) {
          tempbuf[strlen(tempbuf)] = '\0';
          saved += CharSaved (tempbuf);
     }
     printf ("%d", saved);
     return 0;
}

int CharSaved (char *input) {
     int number = 0, original_num;
     int CurrentLength;
     int MinLength = 0;
     int numlist [20] = {0}, j = 0, DigitCount = 0;
     for (int i = 0; input[i] != '\0'; i++) {
          switch (input[i]) {
               case 'I':
                    numlist[j++] = 1;
                    break;
               case 'V':
                    numlist[j++] = 5;
                    break;
               case 'X':
                    numlist[j++] = 10;
                    break;
               case 'L':
                    numlist[j++] = 50;
                    break;
               case 'C':
                    numlist[j++] = 100;
                    break;
               case 'D':
                    numlist[j++] = 500;
                    break;
               case 'M':
                    numlist[j++] = 1000;
                    break;
          }
     }
     CurrentLength = j;
     for (int i = 0; numlist[i] != 0; i++) {
          if (numlist[i+1] != 0) {
               if (numlist[i] >= numlist[i+1])
                    number += numlist[i];
               else
                    number -= numlist[i];
          } else
               number += numlist[i];
     }
     original_num = number;
     while (number > 0) {
          if (DigitCount < 3) {
          switch (number % 10) {
               case 1: /* I, X, C and M */
                    MinLength += 1;
                    break;
               case 2:
                    MinLength += 2;
                    break;
               case 3:
                    MinLength += 3;
                    break;
               case 4:
                    MinLength += 2;
                    break;
               case 5:
                    MinLength += 1;
                    break;
               case 6:
                    MinLength += 2;
                    break;
               case 7:
                    MinLength += 3;
                    break;
               case 8:
                    MinLength += 4;
                    break;
               case 9:
                    MinLength += 2;
                    break;
               default:
                    break;
          }
          } else
               MinLength += (number % 10);
          DigitCount ++;
          number /= 10;
     }
     return CurrentLength - MinLength;
}

// Answer: 743
// Run-time: 2.0ms