//Project Euler: Problem 6

#include <stdio.h>
#include <stdlib.h>

int main()
{
    long signed int sum_of_square = 0;
    long signed int square_of_sum = 0;
    int sum = 0;
    int i;
    
    for (i=1; i<=100; i++) {
        sum_of_square += i*i;
        sum += i;
    }
    
    square_of_sum = sum * sum;
    
    printf ("%ld", sum_of_square - square_of_sum);
    
    return 0;
    
}