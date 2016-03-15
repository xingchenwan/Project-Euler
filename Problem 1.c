// Project Euler: Problem 1

#include <stdio.h>
#include <stdlib.h>


int main()
{
    int i,j;
    
    int * multiple3 = malloc(500);
    int * multiple5  = malloc(500);
    int sum1 = 0; // sum for multiples of 3
    int sum2 = 0; // sum for multiples of 5
    int sum3 = 0; // sum for multples of both 3 and 5
    
    for (j=0, i=3; i<1000; i+=3)
    {
        *(multiple3+j) = i;
        sum1 += i;
    }
    
    for (j=0, i=5; i<1000; i+=5)
    {
        *(multiple5+j) = i;
        sum2 += i;
    }
    
    for (j=0, i=15; i<1000; i+=15)
    {
        sum3 += i;
    }
        printf ("%d", sum1+sum2-sum3);

    return 0;
}
