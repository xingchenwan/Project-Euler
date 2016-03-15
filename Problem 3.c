//Project Euler: Problem 3

#include <stdio.h>

int main()
{
    long unsigned int a = 600851475143;
    int i,j;
    long unsigned int s[50];
    
    j=0;
    
    for (i=2; i<a; i++)
        if (a%i == 0) {
            a /= i;
            s[j++] = a;
        } else
            continue;
    
    printf ("Largest prime factor is %lu\n\n",a);
    
    printf("For illustation of the solving process.\n");
    
    for (j=0; (int) j<strlen(s); j++)
        printf("%lu\n", s[j]);
    
    return 0;
    
}