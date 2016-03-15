//Project Euler: Problem 2

#include <stdio.h>

int main()
{   long unsigned fib[100];
    long unsigned sum;
    int i,j;
    
    fib[0] = 1;
    fib[1] = 2;
    
    i=1;
    
    while (fib[i] < 4000000)
    {
        ++i;
        fib[i] = fib[i-1] + fib[i-2];
    }
    
    fib[i] = '\0';
    
    for (j=0; j<i; j++)
    {
        if (fib[j]%2!=0)
            fib[j] = 0;
    }
    
    for (j=0; j<i;j++)
        sum += fib[j];
    
    printf ("%lu",sum);
    
    return 0;
    
}
