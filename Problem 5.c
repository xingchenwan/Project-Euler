//Project Euler: Problem 5
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int i, j;
    int counter;
    unsigned long int k;
    
     for (i=1; ;i++)
    {
        k = 10 * i;
        counter = 0;
        for (j=1; j<20; j++)
            if (k%j==0)
            ++counter;
        if (counter >= 19) {
            printf("%lu",k);
            return 0;
        }
    }
    return 1;
}