//Project Euler: Problem 14

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    long int n, m=0; // Number
    long int i; // Counter
    long int max = 0, maxnumb = 0;
    double a; // log(2)(n)
    
    for (n=1000000,i=0; n>=1; n--) {
        m = n;
        i=0;
        while (m > 1) {
            if (m%2 == 0) { // if n is even
                a = (log(m)/log(2));
                if (a - (int)a == 0) { // Is n is integer power of 2
                    i += a;
                    break;
                } else { // Else execute the command
                    m /= 2;
                    i++;
                }
            } else { // if n is odd
                m = 3*m + 1;
                i++;
                  }
        }
        if (i > max) {
            max = i+1;
            maxnumb = n;
        }
    }
    printf ("The number with longest sequence is %lu, with number of steps %lu", maxnumb, max);
    return 0;
}

