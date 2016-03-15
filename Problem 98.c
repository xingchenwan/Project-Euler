//Problem 98
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#define MAXWORD 1786
#define BUFSIZE 17000
#define MAXNUM 31622 // sqrt (10^9)

struct word {
     int index;
     char *word;
     int AlphaIncidence [26];
     int WordLength;
} wordlist [MAXWORD];
int SqTable [MAXNUM] = {0};
int LargestAnaNum = 0;
int main()
{
     void WordInitializer (struct word *);
     void FindAnagramicPairs (void);
     void SqTabInitializer (void);
     int i;
     
     for (i = 0; i < MAXNUM; i++)
          SqTable[i] = i*i;
     WordInitializer(wordlist);
     FindAnagramicPairs();
     printf ("Largest Anagramic Square is %d", LargestAnaNum);
     return 0;
}

void WordInitializer (struct word * List)
{
     FILE *fp;
     char *buf = (char *) malloc(sizeof(char)*BUFSIZE);
     int i, j = 0, k = 0;
     char temp [20];
     
     fp = fopen("/Users/Stellar/Desktop/ProjectEuler/InputDocs/p098_words.txt", "r");
     fgets(buf, BUFSIZE, fp);
     for (i=0; (buf[i]!=EOF) && (buf[i]!='\0'); i++) {
          if (!isalpha (buf[i]))
               continue;
          else {
               for (int a = 0; a < 26; a++)
                    List[j].AlphaIncidence[a] = 0;
               while (isalpha(buf[i])) {
                    temp[k] = buf[i++];
                    List[j].AlphaIncidence[temp[k]-'A'+1]++;
                    k++;
               }
               temp[k] = '\0';
               List[j].word = strdup (temp);
               List[j].WordLength = k;
               List[j].index = j;
               j++, k=0;
          }
     } fclose(fp);
}

bool hasSameComposition (int *, int *);
void FindAnagramicPairs (void)
{
     struct word *p = wordlist;
     void FindMatch (char *, char *, int);
     
     for (int i = 0; i < MAXWORD-1; i++)
          for (int j = i+1; j < MAXWORD; j++) {
               if (p[i].WordLength != p[j].WordLength)
                    ;
               else if (hasSameComposition(p[i].AlphaIncidence, p[j].AlphaIncidence)) // To exclude palindromes
                    FindMatch(p[i].word, p[j].word, p[i].WordLength);
          }
}

struct num {
     int number;
     char MappedLetter;
};
void FindMatch (char *word1, char *word2, int length) /* Length determines the order of magnitude of the resulting square numbers */
{
     struct num Digits[10];
     int PermutedNum;
     int temp, a, b;
     int MappedDigits (char *, struct num *, int);
     
     for (int i = sqrt(pow(10, length-1)); SqTable[i] < pow(10, length); i++) {
          temp = SqTable[i], a = 0, b = length-1;
          for (int j = 0; j < 10; j++) {
               Digits[j].number = EOF;
               Digits[j].MappedLetter = '\0';
          } while (temp > 0 && b >= 0) {
               Digits[a].MappedLetter = word1[a];
               Digits[b].number = temp % 10;
               a++, b--;
               temp /= 10;
          }
          PermutedNum = MappedDigits(word2, Digits, length);
          if ((int)sqrt(PermutedNum) == sqrt(PermutedNum) &&
              PermutedNum != SqTable[i]) {
               if (PermutedNum > LargestAnaNum)
                    LargestAnaNum = PermutedNum;
               else if (SqTable[i] > LargestAnaNum)
                    LargestAnaNum = SqTable[i];
               for (int k = 0; Digits[k].number != EOF; k++)
                    printf ("%c -> %d\n", Digits[k].MappedLetter, Digits[k].number);
               printf ("%s %s: %d %d\n\n", word1, word2, SqTable[i], PermutedNum);
          }
     }
}

int MappedDigits (char *word, struct num *Dictionary, int StringLength) /* Return the mapped digit given a letter */
{
     int temp [10] = {0}, m = 0, n;
     bool checked [10] = {0};
     int returnval = 0;
     
     for (int i = 0; i < 10; i++)
          for (int j = i+1; j < 10; j++) { // Check for multiple letter mapped to one number, or multiple number mapped to one letter
               if (Dictionary[i].number == Dictionary[j].number &&
                   Dictionary[i].MappedLetter != Dictionary[j].MappedLetter)
                    return -1;
               else if (Dictionary[i].number != Dictionary[j].number &&
                        Dictionary[i].MappedLetter == Dictionary[j].MappedLetter)
                    return -1;
          }
     
     for (int i = 0; i < StringLength; i++)
          for (int j = 0; Dictionary[j].number != EOF; j++)
               if (word[i] == Dictionary[j].MappedLetter && checked[i] == false) {
                    checked[i] = true;
                    temp[m++] = Dictionary[j].number;
                    if (!temp[0])
                         return -1; // First digit may not be 0
               }

     for (n = 0; n < m; n++)
          returnval += (temp[n] * pow(10, StringLength-1-n));
     if (returnval > 0) {
          return returnval;
     }
     return -1;
}

bool hasSameComposition (int *Incidence1, int *Incidence2)
{
     for (int i = 0; i < 26; i++)
          if (Incidence1[i] != Incidence2[i])
               return false;
     return true;
}

// Ans: 18769
// Running Time: 13.0ms