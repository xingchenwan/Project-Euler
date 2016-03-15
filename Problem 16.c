// Project Euler: Problem 16

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define YES 1
#define NO 0


int num_of_digits = 500;

int main()
{
    int i,j,c=0;
    int limit = 1000;
    int digit [num_of_digits]; // Digit for the current number
    int digitstore [num_of_digits]; // Storing digit for the previous number
    long sum=0; // Sum of digits
    int add=NO; // Whether to add one to the previous digit
    
    for (i = 0; i< num_of_digits; i++) {
        digit [i] = 0; // Initialise Digit Sequence
        digitstore [i] = 0;
    }
    
    digit [num_of_digits-1] = 2; // Set the last digit to 2
    
    for (c=0; c<limit-1; c++) {
    
        for (i=num_of_digits-1; i>0 ; i--) {// From last digit
        
            if (digit[i] < 5) {
                if (add)
                    digitstore[i] = digit[i] * 2 + 1;
                else
                    digitstore[i] = digit[i] * 2;
                
                add = NO;
            }
            
            else
            {
                if (add)
                    digitstore[i] = digit[i] * 2 % 10 + 1;
                else
                    digitstore[i] = digit[i] * 2 % 10;
                
                add = YES;
            }
        
        }
        
        for (j=0; j<num_of_digits; j++)
            digit[j] = digitstore[j]; // Copy contents in digitstore to digit
    
    }
    
    for (i=0; i<num_of_digits; i++) {
        if (i == 0)
            continue; // Ignore the leading zero digits
        else
            sum += digit[i];
    }
        
    printf ("%lu", sum);
    
    return 0;
    
}

// The answer given by the program is 1366