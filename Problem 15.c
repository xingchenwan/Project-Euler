// Project Euler: Problem 15

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int main()
{
    int c=21, i, j=0, k=1;
    
    long int *exp_array [21]; // Expanding array
    long int *shr_array [21]; // Shrinking array
    
    for (i=0; i<c; i++) {
        exp_array [i] = malloc (100);
        shr_array [i] = malloc (100);
    }

    
    exp_array[0][0]= 1;
    
    for (i=0; i<2*c-1; i++) {
    
        if (i<=c-1) {
        
            exp_array[i][0] = exp_array[i][i] = 1;
            
            for (j=1; (j>0) && (j<i); j++)
                exp_array[i][j] = exp_array[i-1][j-1] + exp_array[i-1][j];
        }
        
        else if (i == c )
            for (j=0; j<c; j++)
                shr_array[0][j] = exp_array[c-1][j] + exp_array[c-1][j+1];
        
        else {
            for (j=0; j<c; j++)
                shr_array[k][j] = shr_array[k-1][j] + shr_array[k-1][j+1];
            k++;
        }
    }
    
    printf ("%lu",*shr_array[c-2]);
    
    return 0;

}

// Ref: http://www.robertdickau.com/lattices.html
// Ref: http://www.robertdickau.com/manhattan.html
// Ans: 137846528820