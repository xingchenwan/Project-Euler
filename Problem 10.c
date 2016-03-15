//Project Euler: Problem 10

#include <stdio.h>
#include <stdlib.h>

int main()
{
    long *prime = malloc(2000000);
    unsigned long int i,j,k,sum;
    int counter=0;
    
    prime[0]=2;
    prime[1]=3;
    prime[2]=EOF;
    
    for (i=3;i<2000000;i=i+2)
    {
        counter = 0;
        for (j=0; prime[j]!=EOF;j++)
            if (i% (prime[j]))
                counter++;
            else {
                counter = 0;
                break;
            }
        
        if (counter == j) {
            prime[j] = i;
            prime[j+1] = EOF ;
        }
        
    }
    
    for (k=0; prime[k]!=EOF; k++)
        sum += prime[k];
    
    printf ("%lu\n", sum);
    
    
    return 0;
    
}

// The answer is 142 913 828 922.
// Sum of Prime under one million: 37 550 402 023
