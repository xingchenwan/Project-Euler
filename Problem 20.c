// Project Euler: Problem 20
// (Modified from the Solution to Problem 16)

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int num_of_digits = 300;

int main()
{
    int i,j;
    int limit = 100;
    int digit [500]; // Digit for the current number
    int digitstore [500]; // Storing digit for the previous number
    long sum=0; // Sum of digits
    int add = 0; // Whether to add one to the previous digit
    int multiplier, t/*ten's digit*/, s/*single digit*/;
    
    for (i = 0; i< num_of_digits; i++) {
        digit [i] = 0; // Initialise Digit Sequence
        digitstore [i] = 0;
    }
    
    digit [num_of_digits-1] = 2; // Set the last digit to 2
    
    for (multiplier=3;  multiplier<=limit; multiplier++) {
        
        t = multiplier / 10;
        s = multiplier % 10;
        
        for (i=num_of_digits-1; i>0 ; i--) {// From last digit
            
            if (digit[i] * multiplier + add < 10) {
                
                if (add!=0)
                    digitstore[i] = digit[i] * multiplier + add;
                else
                    digitstore[i] = digit[i] * multiplier;
                
                add = 0;
            }
            
            else
            {
                if (add!=0)
                    digitstore[i] = (digit[i] * multiplier + add) % 10;
                else
                    digitstore[i] = digit[i] * multiplier % 10;
                
                add = (int) (digit[i] * multiplier + add) / 10;
            }
            
        }
        
        for (j=0; j<num_of_digits; j++)
            digit[j] = digitstore[j]; // Copy contents in digitstore to digit
        
    }
    
    for (i=0; (i<num_of_digits) && digit[i]<10; i++) {
        if (i == 0)
            continue; // Ignore the leading zero digits
        else
            sum += digit[i];
    }
    
    printf ("%lu", sum);
    
    return 0;
    
}

// The answer given by the program is 648
// The programs used in this question and Q16 are rudimentary types of big number manipulations