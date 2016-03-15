// Problem 43
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int PandigitElement10[] = {0,1,2,3,4,5,6,7,8,9};

void FindSubStringDivisibleNum (int *, int[6][10], int, int);
long IntArraytoLong (int *IntArray, int NumLength);

int main()
{
    int i, j;
    long sum = {0};
    int SubStringDivisibleList [6][10] ={0};
    
    FindSubStringDivisibleNum(PandigitElement10, SubStringDivisibleList, 0, 9);
    for (i=0; i<6; i++) {
        for (j=0; j<10; j++) {
            printf ("%d", SubStringDivisibleList[i][j]);
        }printf ("\n");
    } for (i=0; i<6; i++)
        sum += IntArraytoLong(SubStringDivisibleList[i], 10);
    printf ("\nSum of these numbers is %ld", sum);
    return 0;
}

int n = 0;
void swap (int *a, int *b);
void FindSubStringDivisibleNum (int *element, int result[8][10], int CurrentDigit, int ArraySize)
{
    int i,j;
    
    if (CurrentDigit >= ArraySize) {
        if ((element[0] == 0 )||
            (element[3] % 2 != 0) ||
            (element[2]+element[3]+element[4]) % 3 != 0 ||
            (element[5] % 5 != 0) ||
            ((element[4] * 100 + element[5] * 10 + element[6]) % 7 != 0) ||
            ((element[5] * 100 + element[6] * 10 + element[7]) % 11 != 0) ||
            ((element[6] * 100 + element[7] * 10 + element[8]) % 13 != 0) ||
            ((element[7] * 100 + element[8] * 10 + element[9]) % 17 != 0))
            ;
        else {
            for (j=0; j<=ArraySize; j++)
                result[n][j] = element[j];
            n++;
        }
        } else {
        for (i=CurrentDigit; i<=ArraySize; i++) {
            swap (&element[CurrentDigit], &element[i]);
            FindSubStringDivisibleNum (element, result, CurrentDigit+1, ArraySize);
            swap (&element[CurrentDigit], &element[i]);
        }
    }
}

void swap (int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

long IntArraytoLong (int *IntArray, int NumLength)
{
    int i, j;
    long temp = 0;
    for (i=NumLength-1, j=0; i>=0; i--, j++)
        temp += IntArray[i] * pow(10, j);
    return temp;
}

// The program gives answer 16695334890