//Project Euler: Problem 4

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, j;
    int a;
    unsigned long k;
    char s[7] ;
    char t[7] ;
    
    
    for (i=999; i>=100; i--)
        for (j=999; j>=100; j--) {
            k = i*j;
            sprintf (s, "%lu" ,k);
        
            for (a=0; a<=(strlen(s)/2) && s[a] == s[strlen(s)-1-a]; a++)
                ;
            
            if (a >= strlen(s)/2)
                if (atoi (s) > atoi (t))
                strcpy (t, s);
            
        }
    
    printf ("%s",t);
    
    return 0;
            
}