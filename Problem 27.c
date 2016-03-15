// Project Euler: Problem 27
// Prime Number Pre-calculation adapted from function in Problem 12

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define YES 1
#define NO 0

void primelist (long *prime);
long prime [50000] = {0};
int primetest (long);
int main()
{
     signed long num = 0;
     signed int a=0, b = 0;
     unsigned int n=0;
     signed int nStore=0, aStore=0, bStore=0;
     
     primelist (prime);
     
     for (a=-1000; a<=1000; a++)
          for (b=0; b<=1000; b++) {
               num = n * n + a * n + b;
               
               if ((num < 0)||(num%2==0)||(num%3==0)||(num%5==0))
                    // Exclude negative, even numbers and those with divisors that are the first few of the prime numbers
                    continue;
               
               else if (primetest(num)==NO)
                    continue;
               
               else {
                    
               while (primetest(n*n+a*n+b)==YES)
                    n++;

               if (n>nStore) {
                    nStore = n;
                    aStore = a;
                    bStore = b;
                    
               } n = 0;
                    
               }
          }
     
     printf ("Answer is %d.\n", aStore*bStore);
     printf ("n = %d, a = %d, b = %d",nStore,aStore,bStore);
     
     return 0;
                    
}

// Tells whether num is a prime number, return YES for prime number and NO for non-prime number
// return -1 for prime number index if num is non-prime, and the sequence number (e.g. index 1 for number 2, 2 for 3, 3 for 5, 5 for 7, 6 for 11 and so on) for prime numbers
int primetest (long num)
{
     int i;
     for (i=0; (prime[i]<=num) && (prime[i]!=EOF); i++)
          if (num == prime[i]) {
               return YES;
          }
     
     return NO;
}

void primelist (long *prime)
// Improved version of Prime Number Generator from Solution 12. The Counter is removed and once a number is divisible by any of the preceding prime numbers, it is immediately excluded from the list. In problem 12, the exclusion is not immediate, but needs to wait until all numbers are looped and a comparison between the counter and the number of prime numbers before is completed.

{
     unsigned long int i,j;
     int BreakLoop = NO;
     prime[0]=2;
     prime[1]=3;
     prime[2]=EOF;
     for (i=3; ;i++)
     {
          for (j=0; prime[j]!=EOF;j++)
               if (i % (prime[j]) == 0) {
                    BreakLoop = YES;
                    break;
               } if (BreakLoop == NO) {
               prime[j] = i;
               prime[j+1] = EOF;
          } BreakLoop = NO;
          if (prime[j] > 100000)
               return;
     }
}

// Program gives answer -59231 when a=-61 and b=971
// The length of chain of prime numbers is 71.