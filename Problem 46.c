// Problem 46
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int prime [5000] = {0};
void primelist (int*);
void OddCompositeGenerator (int*);
int primechecker (int num); // Check whether a given number is prime

int main()
{
    int OddComposite [10000] = {0};
    int i,j,SubstractedNum, Store=0;
    
    primelist(prime);
    OddCompositeGenerator (OddComposite);
    
    for (i=1; OddComposite[i+1]!=EOF; i++) {
        if (!OddComposite[i])
            ;
        else {
        for (j=1; j<=sqrt((OddComposite[i]-2)/2);j++) {
             SubstractedNum = OddComposite[i] - (2 * j * j);
            if (primechecker(SubstractedNum))
                break;
        }
            if (2 * j * j + 2> OddComposite[i]) {
                Store = OddComposite[i];
                goto found;
        }
        }
    }

    found:
    if (Store > 0)
        printf ("%d", Store);
    else printf ("Not Found.\n");
    
    return 0;
}

void OddCompositeGenerator (int *list)
{
    int i,j;
    for (i=1,j=0; i<20000; i+=2,j++)
        list[j] = i;
    list[j] = EOF;
    for (i=0; list[i]!=EOF; i++) {
        for (j=0; prime[j]<=list[i]; j++)
            if (list[i] == prime[j]) {
                list[i] = 0;
                break;
            }}
}

int primechecker (int num) // Check whether a given number is prime
{
    int i;
    for (i=0; prime[i]<=num; i++)
        if (num == prime[i])
            return 1;
    return 0;
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
        if (prime[j] > 20000)
            return;
    }
}

// The program gives answer 5777
