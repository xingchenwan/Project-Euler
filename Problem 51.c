// Problem 51

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

void combinations (int *, int*, int, int);
int IntArraytoInt (int *, int);
void primelist (int *);
void DigitListing (int, int *, int *);
int primechecker (int, int *);
int QuotientLastDigit (int, int); // Return the last digit of the quotient

int prime [100000] = {0};
int main()
{
    int i,j,a,Number,k;
    int NumLength = 0, counter = 0, PrimeCount;
    int StepStore [32] = {0}, PrimeIndex;
    int Digits[8]= {0};
    int Incidence [10][8] = {0};
    
    primelist(prime); // Step 1
    
    for (a=5683; prime[a]<200000 ; a++) {
        j=0;
        for (i=0; i<10; i++)
            for (k=0; k<8; k++)
                Incidence [i][k] = 0;
        for (i=0; i<32; i++)
            StepStore[i] = 0; // Reset memory of all parameters
        DigitListing(prime[a], Digits, &NumLength); // List all digits in the digit array
        for (i=0; i<NumLength-1; i++) {
            if (Digits[i] < 3) // If digit exceeds 2, it cannot be the first element of the eight-membered prime family
                Incidence[Digits[i]][j++] = 1;
            else
                j++;
        } for (i=0; i<10; i++)
            combinations(Incidence[i], StepStore, 0, NumLength);
        for (i=0; StepStore[i]!=0; i++) {
            Number = prime[a] - (QuotientLastDigit(prime[a], StepStore[i]) * StepStore[i]); // For rationale of this step, refer to Approach 5
            counter = 0, PrimeCount = 0;
            while (counter <= 9) {
                if ((primechecker(Number, &PrimeIndex))&&(Number >= prime[a])) {
                    PrimeCount++;
                    if (PrimeCount >= 8) {
                        printf ("Number found %d", prime[a]);
                        return 0;
                    }
                } Number += StepStore[i];
                counter ++; }
        }
    } printf ("Not Found, please modify the range of search");
    return 1;
}

void combinations (int *Element, int *CombinationStore, int CurrentDigit, int ArrayLength)
// 0 or 1 Combinations
{
    int number, m, StopTask=0;
    static int n;
    
    if (CurrentDigit == 0)
        n = 0;
    if (Element[CurrentDigit] == 0)
        combinations(Element, CombinationStore, CurrentDigit+1, ArrayLength);
    else {
        if (CurrentDigit <= ArrayLength) {
            for (Element[CurrentDigit]=0; Element[CurrentDigit]<=1; Element[CurrentDigit]++)
                combinations(Element, CombinationStore, CurrentDigit+1, ArrayLength);
        } else {
            number = IntArraytoInt(Element, ArrayLength);
            if (number != 0) {
                for (m=0; m<n; m++)
                    if (CombinationStore[m] == number) {
                        StopTask = 1;
                        break;
                    } if (!StopTask)
                        CombinationStore[n++] = number;
            }
        }
    }
}

int IntArraytoInt (int *IntArray, int NumLength)
{
    int i, j;
    int temp = 0;
    for (i=NumLength-1, j=0; i>=0; i--, j++)
        temp += IntArray[i] * pow(10, j);
    return temp;
}

void primelist (int *prime)
{
    int i,j;
    int StopTask = 0;
    prime[0]=2;
    prime[1]=3;
    prime[2]=EOF;
    for (i=3; ;i=i+2)
    {
        for (j=0;prime[j]!=EOF;j++)
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

int primechecker (int num, int *index)
{
    int i;
    for (i=0; prime[i]<=num; i++)
        if (num == prime[i]) {
            *index = i;
            return 1;
        }
    return 0;
}

void DigitListing (int num, int *DigitList, int *NumLength)
{
    int i;
    int m, n, c;
    
    for (i=0; i<8; i++)
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

int QuotientLastDigit (int dividend, int divisor) // Return the multiplicant to the step size we need to obtain the base number
{
    int a = 0;
    int i = 1;
    a = divisor / ( (int) pow (10, i)) % 10;
    while (a != 1) {
        a = divisor / ( (int) pow (10, i)) % 10;
        i++;
    } return dividend / ( (int) pow (10, i)) % 10;
}

// Program gives answer 121313.
// Members of the family 121313, 222323, 323333, 424343, 525353, 626363, 727373, 828383
// Runtime: 8890.0s / 27 Jul 2015 

// Approach
// 1. List all prime numbers under an arbitrary limit (if the number satisfying the condition is higher than the limit, we adjust the limit later
// 2. By observation, the interval between two numbers of the same family is the multiple of a constant (the Step Size). With this observation, we can calculate all possible intervals of a given number. Taking number 121313 as an example, last digit may not be replaced as 5 of which will be even hence we will not be able to find 8 members that are prime. The "3" in the 4th digit may also not be replaced, as starting from 3 thru 9 we will not have 8 elements even if every number is prime (Since the question is asking for the FIRST member. Otherwise digits larger than 3 may be replaced)
// 3. Now we have three replacable digits (1,2,1,1). Possible ways of replacements are *21313, 1*21313, 12*313, 1213*3 (one digit replaced) and *2*313, *213*3, 12*3*3 (2 digits replaced) and lastly *2*3*3 (3 digits replaced). This correspond to increment interval (step size) 100000,10000,1000,10,101000,100010, 1010, 101010. However note that replacements such as 1**313 are not acceptable, as the replaced digits must be the same.
// 4. The interval can be obtained by finding the ways of combinations of 1 and 0. (Since the question is asking for EIGHT families, which imply the step-size must be smaller than 10/8, the positive integer smaller than which can only be 1) For replacements that only involve one digit, the only ways are 1 and 0 (if the replaced digit occurs at the thousand's digit, we have increment step 1000, and 0 which is trivial). For replacements that involve two digits, there are four ways 11, 10, 01, 00(Trivial), and so on. By using previously developed tool to inter-convert int and intArrays, we can obtain all possible step sizes
// 5. For each step-size we found, to ensure that after adding the multiples of steps we do not exceed the limit (e.g. for step size 1000, if add 9 times of 1000 to 121313 we get 131313 which is not in form 12*313 and we have exceeded the limit), we decrement the original number to a base number (e.g. we decrement 121313 to 120313 for step size 1000, and to 20303 for step size 101010). We check primality of the sum of up to 9 multiples of the current step size and the base number (BaseNumber + n * Step, where n <= 9). Note that the prime count only starts if the number exceeds or is equal to the original prime number (i.e. for step size 101010, we do not check 20303's primality but we start check and record the number of primes only from 121313 through 929393). If the number of primes exceed or equal to 8, we have found the required number and we quit the program. Otherwise we progress to the next number. If no answer is found the range may be insufficient and we repeat all steps with a newer range.
