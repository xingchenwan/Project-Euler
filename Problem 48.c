// Problem 48
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
long IntArraytoLong (int *, int);
void DigitListing (long, int *, int *);
int main()
{
    long term [1000] ={0}, temp, sum = 0;
    int DigitArray[15] ={0};
    int i, counter, NumLength = 0;
    
    for (i=1; i<1000; i++) {
        temp = 1, counter = 0;
        while (counter < i) {
            counter ++;
            temp *= i;
            DigitListing(temp, DigitArray, &NumLength);
            temp = IntArraytoLong(DigitArray, NumLength);
        } if (counter == i) {
            term[i] = IntArraytoLong(DigitArray, NumLength);
            sum += term[i];
        }
    } printf ("%lu", sum);
    return 0;
}

long IntArraytoLong (int *DigitList, int NumLength)
//Convert last 10 digits back to a 'long'. Convert all digits if there is fewer than 10 digits
{
    int i, j;
    long temp = 0;
    
    i=NumLength-1;
    while (DigitList[i] == EOF)
        i--;
    if (NumLength<10) {
        for (j=0; i>=0; i--, j++)
            temp += DigitList[i] * pow(10, j);
        return temp;
    } for (j=0; i>NumLength-11; i--, j++)
        temp += DigitList[i] * pow(10, j);
    return temp;
}

void DigitListing (long num, int *DigitList, int *NumLength)
{
    int i;
    int m, n, c;
    
    for (i=0; i<15; i++)
        DigitList[i] = EOF;
    i=0;
    DigitList [i++] = num % 10;
    while (num >= 10) {
        num /= 10;
        DigitList [i++] = num % 10;
    } for (m=0, n=i-1; m<n; m++, n--) {
        c = DigitList[m];
        DigitList[m] = DigitList[n];
        DigitList[n] = c;
    } *NumLength = i;
}
// The Program gives answer 462/9110846700, the last 13 digits of the desired number. Hence the last ten digits are 9110846700