// Problem 44
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int PentagonalNumList [5000] = {0};
void PentagonalNumGenerator (int * NumList);
int ConditionTester (int num1, int num2);
int main()
{
    int i, Interval = 1, dStore = INFINITY, distance = 0, pairStore[2]={0};
    PentagonalNumGenerator(PentagonalNumList);
    
    while (PentagonalNumList[1+Interval]- PentagonalNumList[1] < dStore) {
      for (i=1;2*i+Interval<4999;i++) {
        distance = ConditionTester(PentagonalNumList[i], PentagonalNumList[i+Interval]);
            if (distance) {
                if (distance < dStore){
                    dStore = distance;
                    pairStore[0] = PentagonalNumList[i];
                    pairStore[1] = PentagonalNumList[i+Interval];
                    break;
            }
        }
    } Interval ++;
    }
    printf ("Minimum difference is %d between %d and %d", dStore, pairStore[0], pairStore[1]);
    return 0;
}

void PentagonalNumGenerator (int * NumList)
{
    int n;
    for (n=0;n<5000;n++)
        NumList[n] = n * (3*n-1) / 2;
            NumList[n+1] = EOF;
            return;
}

int PentagonalNumTester (int);
int ConditionTester (int num1, int num2)
// Test whether the sum and (absolute value) of difference of two numbers are pentagonal. If no, return 0; If yes, return the absolute value of the difference
{
    int sum = num1 + num2;
    int diff = abs (num1 - num2);
    if ((PentagonalNumTester(sum)==1) && (PentagonalNumTester(diff))==1)
        return diff;
    return 0;
}

int PentagonalNumTester (int num)
{
    int i;
    for (i=0; PentagonalNumList[i]<=num;i++)
        if (PentagonalNumList[i] == num)
            return 1;
    return 0;
}

// The program gives answer 5482660 (between paired numbers (1560090 and 7042750)
// Approach:
// 1. List the first n pentagonal numbers (for this question, n = 5000)
// 2. For interval of 1, check the first number in the series and the second number. If this pair does not satisfy the condition, continue with the second and third number and so on until the last number is reached. If no pair satisfying the condition is found, progress to Step 3 directly. If some pair is found, stop the loop and update the store (the minimal D thus found) with the difference of this pair and progreess to Step 3.
// 3. Increase interval by 1 and test once over from first number (with 3rd number). Similar to step 2, if this pair does not satisfy the condition, progress to test 2nd and 4th number and so on. If a pair satisfying the condition is found whose difference is smaller than that of the existing pair in the store (if no pair is found for interval = 1, replace "INFINITY" with this difference) , stop the loop and increase interval by 1, repeat step 3.
// 4. Repeat step 3 until the distance between the first element and the element "Interval" after it is larger than the difference stored. Stop the task and print the difference store (QED)