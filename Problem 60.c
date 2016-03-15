// Problem 60

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

#define UPPER_BOUND 10000 // Test prime numbers below this arbitrarily set bound
#define SELECTION 5

int prime[20000] = {0};
int AnswerArray [SELECTION] = {0};

void primelist (int *);
int Combination (int, int);
int main()
{
     int i, sum = 0;

     primelist(prime);
     if (Combination(0, 1)) {
          printf ("Number found: \n");
          for (i = 0; i < SELECTION; i++) {
               printf ("%d ", AnswerArray[i]);
               sum += AnswerArray[i];
          }
          printf ("\nThe sum is %d.", sum);
     } else
          printf ("No answer found in the current range. Change UPPER_BOUND parameter.\n");
     return 0;
}

bool GO = true;
int Combination (int RecursiveLayer, int StartingIndex)
{
     int i, j;
     static int Result [SELECTION] = {0};
     int ConcatecationPrimeTest (int *, int);
     
     if (RecursiveLayer <= SELECTION && GO == true) {
          for (i = StartingIndex; prime[i] < UPPER_BOUND; i++) {
               Result[RecursiveLayer] = prime[i];
               if (RecursiveLayer == 0)
                    Combination(RecursiveLayer + 1, StartingIndex + 1);
               else if (RecursiveLayer > 0) {
                    if (!(ConcatecationPrimeTest(Result, RecursiveLayer)))
                         return 0;
                    else Combination(RecursiveLayer + 1, StartingIndex + 1);
               }
          }
     }
     if (RecursiveLayer > SELECTION && GO == true) {
          for (j = 0; j < SELECTION; j++)
               AnswerArray[j] = Result[j];
          GO = false;
          return 1;
     }
     if (GO == false)
          return 1;
     return 0;
}

int ConcatecationPrimeTest (int *PrimeArray, int Stop) // Concantecate digits and check the primality of the possible permutations
{
     int NumofDigit (int);
     int isPrime (long, int);
     int cond;
     int i, j;
     
     for (i = 0; i < Stop; i++)
          for (j = 0; j < Stop; j++) {
               if (i == j)
                    ;
               else {
                    cond = PrimeArray[i] * NumofDigit(PrimeArray[j]) + PrimeArray[j]; // Concatecate i to j
                    if (!isPrime(cond, 1))
                         return 0;
               }
          } return 1;
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

int NumofDigit (int num) // Returns the number of digits of the given numbers
{
     if (num >= 0 && num < 10)
          return 10;
     else if (num >= 10 && num < 99)
          return 100;
     else if (num >= 100 && num < 999)
          return 1000;
     else if (num >= 1000 && num < 9999)
          return 10000;
     else
          return 100000;
}

void primelist (int *prime)
{
     int i,j,k = 3;
     int StopTask = 0;
     prime[0]=2;
     prime[1]=3;
     prime[2]=5;
     prime[3]=EOF;
     for (i=7; ;i=i+2)
     {
          for (j=0 ;prime[j]<= sqrt(i) ;j++)
               if (i % (prime[j]) == 0) {
                    StopTask = 1;
                    break;
               } if (!StopTask) {
                    prime[k++] = i;
               } StopTask = 0;
          if (prime[k-1] > 10000)
               return;
     }
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

// Program gives answer 26033 (Prime set: 13, 5197, 5701, 6733, 8389)
// Runtime: 15.1s T_T
// To achieve better accuracy, the Rabin-Miller iteration constant should be increased (currently 1, giving a relatively high probability of misjudging a number's primality) and by increase the upper bound of primes. However both will significantly increase the runtime of the application.
