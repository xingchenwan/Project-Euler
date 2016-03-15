// Project Euler: Problem 17

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    int i;
    long count = 0;
    int h, /* hundred digit */ t, /*ten digit*/ s, /*single digit*/ th; /*thousand digit*/
    
    for (i=1; i<=1000; i++) {
        
        th =i / 1000; //thousand's digit.
        h = i / 100; //hundred's digit
        t = (i - (100*h)) / 10;// ten's digit
        s = i - (100*h) - (10*t); // single digit
        
        if (th == 1) // for number 1000
            count += 11; // for "one thousand" -> 11 char
        
        else { // for everything below 1000
        
        switch (h) {
            case 1: case 2: case 6: // one, two, six -> 3 char
                count += 10; // hundred 7 digits
                break;
            case 4: case 5: case 9: // four, five, nine -> 4 char
                count += 11;
                break;
            case 0:
                break;
            default:
                count += 12; //three, seven, eight -> 5 char
                break;
        }
        
        if ((h >= 1) && ( i != 100 * h)) // if h is not integer multiple of 100
            count += 3; // for "and" in, for e.g., one hundred and thirty six
        
        
        switch (t) {
            case 2: case 3: case 8: case 9:  //twenty, thirty, eighty, ninety
                count += 6;
                break;
            case 4: case 5: case 6: //forty, fifty, sixty
                count += 5;
                break;
            case 7:
                count += 7; //seventy
                break;
            case 1:
              switch (s) {
                case 1: case 2:
                    count += 6; //for eleven and twelve
                    break;
                case 3: case 4: case 8: case 9:
                    count += 8; // thirteen, fourteen, eighteen, nineteen
                    break;
                case 5: case 6:
                    count += 7; //fifteen, sixteen
                    break;
                case 7:
                    count += 9; // nineteen
                    break;
                default: // for ten
                    count += 3;
                    break;
            }
                break;
            default: //t=0
                break;
        }
        
         if (t != 1) {
            switch (s) {
                case 1: case 2: case 6:
                    count += 3;
                    break;
                case 3: case 7: case 8:
                    count += 5;
                    break;
                case 0:
                    break;
                default: // 4, 5, 9
                    count +=4;
                    break;
            }
            }
        }
        }
    
    printf ("%lu", count);
    
    return 0;
    
 }
            

