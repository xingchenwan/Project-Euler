//Project Euler: Problem 9

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main()
{
    int a, b;
    double op1, op2;
    
    for (a=1; a<1000; a++)
        for (b=1000; b>0; b--) {
            op1 = sqrt ((a*a) + (b*b));
            op2 = op1 - (int)op1;
            if ( (a + b + op1) == 1000) {
                printf ("a = %d, b = %d, c = %d.\n",a, b, (int)op1);
                printf ("The product is %d", a*b*(int)op1);
                return 0;
            }
            }
    
    return 1;
}