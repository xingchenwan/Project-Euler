// Problem 47
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int prime [5000] = {0};
void primelist (int*);
int FindUniquePrimeFactors (int);

int main()
{
    int i, Store = 0;
    primelist(prime);
    
    for (i=210;;i++) {
        if (FindUniquePrimeFactors(i)!=4 ||
            FindUniquePrimeFactors(i+1)!=4 ||
            FindUniquePrimeFactors(i+2)!=4 ||
            FindUniquePrimeFactors(i+3)!=4)
            ;
        else {
            Store = i;
            goto found;
            }
    }
    
    found:
    if (Store)
        printf ("%d, %d, %d, %d",Store, Store+1, Store+2, Store+3);
    else printf ("Not Found");
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

int FindUniquePrimeFactors (int num)
{
    int k=0; /* factor store index */
    int i=0, j=0;
    int factorstore[50] ={0}, UniquePrimeFactors[10] = {0};
    int m=0, n=0, RepeatedElement=0;
    
    while (num>1) {
        if (num % prime[i] == 0) {
            factorstore[k++] = prime[i];
            num /= (prime[i]);
        } else
            i++;
    } factorstore[k] = EOF;
    for (m=0; factorstore[m]!=0; m++) {
        for (n=0; n<m; n++) {
            if (factorstore[m] == factorstore[n]) {
                RepeatedElement = 1;
                break;
            }
        }if (!RepeatedElement)
            UniquePrimeFactors[j++] = factorstore[m];
        RepeatedElement = 0;
    } return j-1;
}

// The programs proves that the four consecutive numbers are 134043 through 134046