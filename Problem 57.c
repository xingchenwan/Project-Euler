// Problem 57

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int SizeofDigitList = 500;
void IntArrayAddition (int *Array1, int *Array2, int *Array3, int *NumLength, int mode);
int InttoIntArray (int, int *);
int main()
{
     int CurrentNumeratorDigits [500] = {0}, CurrentDenominatorDigits [500] = {0};
     int PrevDenominatorDigits [500] = {0} , PPrevDenominatorDigits[500] = {0};
     int NumofTerms = 0, DenominatorLength, NumeratorLength;
     int Incidence = 0, j;
     
     InttoIntArray(1, PPrevDenominatorDigits);
     InttoIntArray(2, PrevDenominatorDigits);
     
     while (NumofTerms < 1000) { // For the first 1000 expansions
          IntArrayAddition(PPrevDenominatorDigits, PrevDenominatorDigits, CurrentDenominatorDigits, &DenominatorLength, 1);
          IntArrayAddition(PrevDenominatorDigits, CurrentDenominatorDigits, CurrentNumeratorDigits, &NumeratorLength, 2);
          NumofTerms ++;
          
          if (DenominatorLength < NumeratorLength)
               Incidence ++;
          
          for (j=0; j<SizeofDigitList; j++) { // pNum is now ppNum, nNum is now pNum. Clear memory of currentD and currentN
               PPrevDenominatorDigits[j] = PrevDenominatorDigits[j];
               PrevDenominatorDigits[j] = CurrentDenominatorDigits[j];
               CurrentDenominatorDigits[j] = CurrentNumeratorDigits[j] = 0;
          }
     } printf ("Number of incidences is %d", Incidence);
     return 0;
}

int InttoIntArray (int num, int *DigitList) // Returning digit count
{
     int i;
     int m, n, c;
     
     for (i=0; i<SizeofDigitList; i++)
          DigitList[i] = 0;
     i=SizeofDigitList-1;
     DigitList [i--] = num % 10;
     while (num >= 10) {
          num /= 10;
          DigitList [i--] = num % 10;
     } for (m=0, n=i-1; m<n; m++, n--) {
          c = DigitList[m];
          DigitList[m] = DigitList[n];
          DigitList[n] = c;
     } return SizeofDigitList-1 - i;
}

void IntArrayAddition (int *Array1, int *Array2, int *Array3, int *NumLength, int mode) {
     // Mode 1: to Calculate Denominator (With formula Dn = Dn-2 + 2Dn-1) Mode 2: to Calculate Numerators (With formula Nn = Dn-1 + Dn)
     int i, add1 = 0, Temp[500], j,
     add2 = 0,
     k=0;
     
     for (j=0; j<SizeofDigitList; j++) Temp[j] = Array2[j];
     if (mode == 1) {
     for (i=SizeofDigitList - 1; i >= 0; i--)
          if (2 * Temp[i] + add1 < 10) {
               Temp[i] = 2 * Temp[i] + add1;
               add1 = 0;
          } else {
               Temp[i] = (Temp[i] * 2 + add1) % 10;
               add1 = 1;
          } }
     for (i=SizeofDigitList - 1; i >= 0; i--) {
          if (Array1[i] + Temp[i] + add2 < 10) {
               Array3[i] = Array1[i] +  Temp[i] + add2;
               add2 = 0;
          } else {
               Array3[i] = (Array1[i] + Temp[i] + add2) % 10;
               add2 = 1;
          }
     } while (Array3[k] == 0) k++;
     *NumLength = SizeofDigitList - k;
}

// The program gives answer 153
// Approach: Discarding the integer part of each number, the following pattern is observed:
// T1 = 1/2, T2 1/(2+ 1/2),T3 1/(2 + 1/(2+1/2)),...Tn =1/(2 + Tn-1)
// The denominator of T is (1), 2, 5, 12, 29, 70.....
// Numerators are (1), 3, 7, 17, 41, 99... Numerators of the number with integer part deducted is (0), 1, 2, 5, 12, 29...
// Dn = Dn-2 + 2Dn-1
// The numerator of Tn with integer part discarded is the denominator of Tn-1. We can see that Numerator sequence is a re-iteration of the Denominaor sequence, with one term rolled back. Adding back the integer part,
// Nn = Dn-1 + Dn. (i.e Nn (w/o integer part) = Dn-1)
// Using DP, we can generate the sequence up to 1000 of the N and D of T. By comparing the number of digits of D and N we count and get the answer
