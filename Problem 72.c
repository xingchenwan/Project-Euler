// Problem 72
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAXNUM 1000000
int prime [500] = {0}; // sqrt (MAXNUM) < 1000.
struct Factors{
     int number;
     int * DistinctPrimes;
     int phi;
};
static struct Factors numlist [MAXNUM + 1];

int main()
{
     void primelist (void);
     void UniquePrimeFactors(void);
     int den; // numerator and denominator
     long long count = 0;
     
     primelist();
     UniquePrimeFactors();
     for (den = 2; den <= MAXNUM ; den++)
          count += numlist[den].phi;
     printf ("%lld", count);
     return 0;
}

#define MAXFACTOR 8
void UniquePrimeFactors (void) // Version 2 (DP approach). Parameter is left void as the target struct is defined statically in the heap (not the stack). Simplified version of the main function in Problem 70.
{
     int i, j;
     int search (int, int*);
     void intcat(int *, int *);
     int isPrime (long, int);
     int FindPhi (struct Factors);

     for (i = 0; i <= MAXNUM; i ++) {
          numlist[i].number = i;
          numlist[i].DistinctPrimes = NULL;
          if (isPrime(i, 5)) { // For this quesiton, when the iteration is 1 wrong answer is given. So we need to change the iteration value here to avoid mis-judging of prime numbers
               numlist[i].DistinctPrimes = malloc(sizeof(int));
               *numlist[i].DistinctPrimes = i;
          } else {
               for (j = 0; prime[j] <= sqrt(i); j++) {
                    if (!(i % prime[j])) {
                         if (search(prime[j], numlist[i/prime[j]].DistinctPrimes))
                              numlist[i].DistinctPrimes = numlist[i/prime[j]].DistinctPrimes;
                         else {
                              numlist[i].DistinctPrimes = malloc(MAXFACTOR*sizeof(int));
                              *numlist[i].DistinctPrimes = prime[j];
                              intcat (numlist[i].DistinctPrimes, numlist[i/prime[j]].DistinctPrimes);
                         } break;
                    } else continue;
               }
          }numlist[i].phi = FindPhi(numlist[i]);
     }
}

int FindPhi (struct Factors num)
{
     int i;
     double product = num.number, quotient;
     if (!num.number)
          return 0;
     if (num.DistinctPrimes == NULL) {
          return num.number - 1;
     }
     for (i = 0; num.DistinctPrimes[i] != 0; i++) {
          quotient = 1 - (1 / ((double) num.DistinctPrimes[i]));
          product *= quotient;
     }
     return product;
}

void intcat (int *array1, int *array2) // strcat: int array version
{
     int i = 0, j;
     while (array1[i] != 0)
          i++;
     for (j = 0; array2[j]!=0; j++)
          array1[i++] = array2[j];
}

int search (int element, int *array) // linear search implementation
{
     int i;
     for (i = 0; array[i] != 0; i++)
          if (element == array[i])
               return 1;
     return 0;
}

void primelist (void)
{
     int i,j,k = 2;
     int StopTask = 0;
     prime[0]=2;
     prime[1]=3;
     prime[2]=EOF;
     for (i=5; ;i=i+2)
     {
          for (j=0;prime[j]<= sqrt(i) ;j++)
               if (i % (prime[j]) == 0) {
                    StopTask = 1;
                    break;
               } if (!StopTask) {
                    prime[k++] = i;
               } StopTask = 0;
          if (prime[k-1] >= sqrt(MAXNUM))
               return;
     }
}

int isPrime (long p,int iteration){ // Miller-Rabin Primality Test
     
     long mulmod(long a, long b, long c);
     int modulo(int a,int b,int c);
     
     if(p<2){
          return 0;
     }
     if(p!=2 && p%2==0){
          return 0;
     }
     long long s=p-1;
     while(s%2==0){
          s/=2;
     }
     for(int i = 0; i < iteration;i++){
          long a = rand()%(p-1)+1,temp=s;
          long mod = modulo (a,temp,p);
          while (temp !=p-1 && mod != 1 && mod != p-1){
               mod=mulmod(mod,mod,p);
               temp *= 2;
          }
          if(mod != p-1 && temp %2 ==0){
               return 0;
          }
     }
     return 1;
}
// Miller-Rabin Functions
long mulmod( long a, long b, long c){
     long x = 0,y=a%c;
     while(b > 0){
          if(b % 2 == 1){
               x = (x+y) % c;
          }
          y = (y*2) % c;
          b /= 2;
     }
     return x % c;
}

int modulo(int a,int b,int c){
     long x=1,y=a; // long long is taken to avoid overflow of intermediate results
     while(b > 0){
          if(b%2 == 1){
               x=(x*y)%c;
          }
          y = (y*y)%c; // squaring the base
          b /= 2;
     }
     return x % c;
}

// Program gives answer 303963552391
// Runtime: 756.0ms
// In essence, the question is asking for the sum of phi(n) for 1mil >= n >= 2 (if n = 1, all non-0 fractions m/n are improper). Phi(n) gives the number of integers below n that are co-prime to n, each of these integers divided by n produces a reduced proper number. Since the GCD of den and num is 1, every fraction is not repeated (e.g. no situations such as 4/8 = 2/4, in which we are getting duplicates).