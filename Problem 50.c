// Problem 50

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int prime[150000] = {0};
void primelist (int *);
int primechecker (int);
void LongestPrimeSequence (int, int, int, int *);

int main()
{
    int i, Limit = 1000000, sum = 0, MaxTerm, Result = 0;
    primelist(prime);
    
    for (i=0; sum<Limit; i++)
        sum += prime[i];
    MaxTerm = i;
    
    if (primechecker(sum))
        Result = sum;
    else LongestPrimeSequence(MaxTerm, Limit, 0, &Result);
    
    if (!Result)
        printf ("Error\n");
    else printf ("%d", Result);
    
    return 0;
}

void LongestPrimeSequence (int MaxTerm, int UpperLimit, int StartingIndex, int *NumStore)
{
    int i, LocalSum = 0, j;
    static int SequenceStore = 0, Found = 0;
    
    if (MaxTerm <= 1)
        return;
    
    for (i=StartingIndex,j=0; i<StartingIndex+MaxTerm-1; i++,j++)
        LocalSum += prime[i];
    if ((primechecker(LocalSum))&&(LocalSum < UpperLimit)) {
        SequenceStore = (j>=SequenceStore)? j : SequenceStore;
        *NumStore = (j>=SequenceStore)? LocalSum : *NumStore;
        Found = 1;
    }

    if (LocalSum < UpperLimit)
        LongestPrimeSequence(MaxTerm, UpperLimit, StartingIndex+1, NumStore);
    else if (!Found)
        LongestPrimeSequence(MaxTerm-1, UpperLimit, 0, NumStore);
    else return;
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

int primechecker (int num) // Check whether a given number is prime
{
    int i;
    for (i=0; prime[i]<=num; i++)
        if (num == prime[i]) {
            prime[i] = 0;
            return 1;
        }
    return 0;
}

// The program gives answer 997651