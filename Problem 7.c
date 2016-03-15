//Project Euler: Problem 7

#include <stdio.h>
#include <stdlib.h>

int main()
{
    long *prime = malloc(500000);
    unsigned long int i,j;
    int counter=0;
    
    prime[0]=2;
    prime[1]=3;
    prime[2]=EOF;
    
    for (i=3;i<110000;i++)
    {
        counter = 0;
        for (j=0; prime[j]!=EOF;j++)
            if (i% (prime[j]))
                 counter++;
        
        if (counter == j) {
            prime[j] = i;
            prime[j+1] = EOF ;
        }
    }
    
    printf ("%lu\n", prime[10000]);
    
    
    return 0;
    
}

// Result: The 10001st prime number is 104743.