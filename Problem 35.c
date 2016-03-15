//Project Euler: Problem 35

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Rotation (int *, int *, long, int, int);
void DigitListing (long, int *, int *);
int IntArraytoInt (int *, int);
void primelist (long *);
long prime [50000] = {0};
int n = 1;

int main ()
{
    int num[7];
    int result [1000] = {0};
    int i, j, NumofDigits, StopTask = 0, k, counter = 0;
    
    primelist(prime);
    result[0] = 2;
    
    for (i=1; prime[i+1]!=EOF; i++) {
        DigitListing(prime[i], num, &NumofDigits);
        for (j=0; j<NumofDigits; j++)
            if (num[j]%2 == 0) {
                StopTask = 1;
            } if (!StopTask)
            Rotation (num, result, prime[i], NumofDigits, 0);
        StopTask = 0;
    }
    for (k=0; result[k]!=EOF; k++)
        if (result[k]!=0)
            counter ++;
    printf ("%d", counter);
    return 0;
}

int IntArraytoInt (int *IntArray, int NumLength)
{
    int i, temp = 0;
    
    for (i=0; i<NumLength; i++)
        temp += IntArray[i] * pow(10, i);
    return temp;
}

void DigitListing (long num, int *DigitList, int *NumofDigits)
{
    int i, j;
    
    for (i=0; i<7; i++)
        DigitList[i] = EOF;
    *NumofDigits = 0;
    i=0;
    DigitList [i++] = num % 10;
    while (num >= 10) {
        num /= 10;
        DigitList [i++] = num % 10;
    } for (j=0; DigitList[j]!=EOF; j++)
        ;
    *NumofDigits = j;
}

int primechecker (int, int *);
void Rotation (int *DigitArray, int *result, long OriginalNum, int NumLength, int TempIndex)
{
    int i,j,p, Number;
    int TempArray [7];
    static int TempResult[100] = {0};
    
    for (i=0; i<NumLength; i++)
        TempArray[i] = DigitArray[i];
    for (i=0; i<NumLength; i++)
        DigitArray [i+1] = TempArray [i];
    DigitArray [0] = TempArray[NumLength-1];
    Number = IntArraytoInt(DigitArray, NumLength);
    if (Number == OriginalNum) {
        result[n++] = Number;
        for (j=0; j<=TempIndex; j++)
            result[n++] = TempResult[j];
        result[n] = EOF;
        return;
    } else {
        if (primechecker(Number, &p)) {
            prime[p] = 0;
            TempResult[TempIndex++] = Number;
            Rotation (DigitArray, result, OriginalNum, NumLength, TempIndex);
        } else return;
    }
}

int primechecker (int num, int *primeindex) // Check whether a given number is prime
{
    int i;
    for (i=0; prime[i]<=num; i++)
        if (num == prime[i]) {
            *primeindex = i;
            return 1;
        }
    *primeindex = -1;
    return 0;
}
void primelist (long *prime)
{
    unsigned long i,j;
    int StopTask = 0;
    prime[0]=2;
    prime[1]=3;
    prime[2]=EOF;
    for (i=3; ;i=i+2)
    {
        for (j=0; prime[j]!=EOF;j++)
            if (i % (prime[j]) == 0) {
                StopTask = 1;
                break;
            } if (!StopTask) {
                prime[j] = i;
                prime[j+1] = EOF;
            } StopTask = 0;
        if (prime[j] > 1000000)
            return;
    }
}

// Program gives answer 55
// The program is a bit time-consuming as the current algorithm to compute the list of prime numbers consumes significantly much more time when the list grows long. However the program is still well within the 1 minute runtime limit.

// Approach :
// 1. Create a list of prime numbers below 1 million using the previously-found algorithm
// 2. From 2 onwards, decompose the number into digits. If any digits contain 2,4,6,8 or 0, one or more numbers formed by the  rotations of this number are bound to be non-prime. Remove such numbers.
// 3. Rotate the digits. Test every rotation by converting the digit array back to a number. If the rotated number IS found in the prime list, continue the rotation and store the number formed by the current rotation in a temp array inside the loop. Set this prime in the primelist to 0 so that it will not be double counted as the list of prime numbers progresses.  If no, break from the entire loop, test the next prime number.
// 4. If the rotation reaches the original sequence (e.g. 113 -> 131 -> 311 -> 113). Save the numbers in the temp store to the permanent store defined in main(). All rotations, including the original number, satisfy the condition set by the question;
// 5. Count the number of elements in the permanent store. This number gives the answer to the question.

// The list of prime number is: 2,3,5,7,11,13,31,17,71,37,73,79,97,113,131,311,197,971,719,199,991,919,3337,373,733,1193,1931,9311,3119,3779,7793,7937,9377,11939,19391,93911,39119,91193,19937,99371,93719,37199,71993,193939,939391,393919,939193,391939,919393,199933,999331,993319,933199,331999,319993 (In total 55, QED)