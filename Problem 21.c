// Project Euler: Problem 21
// {Fuction void (prime_factorise) modified from the solution to Problem 16}
// This program uses prime factor factorisation to solve the problem. This is more time-efficient in computation but time-consuming in compiling. One may use brute force method as well, i.e. test each and every number up to sqrt of that number.
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define YES 1
#define NO 0
void primelist (int *);
void prime_factorise (int, const int *, int *, int *);
int AmicableNumTester (int num, int * unique_prime_fac, int * multi);

int main()
{
    int a, b, c;
    int prime[1230]={0};
    int UniquePrimeFactor [100] = {0};
    int multiplicity [100] = {0};
    int sum = 0;
   
    primelist (prime);
    for (a=3; a<=10000; a++) {
       prime_factorise (a, prime, UniquePrimeFactor, multiplicity);
       b = AmicableNumTester(a, UniquePrimeFactor, multiplicity);
       prime_factorise (b, prime, UniquePrimeFactor, multiplicity);
       c = AmicableNumTester(b, UniquePrimeFactor, multiplicity);
       if ((c == a) && (c < 10000) && (c != b)) // to exclude numbers such as 28, where the sum of its factors except the number itself is equal to it self (Factor sum of 28 = 2+4+7+14 = 28. )
          sum += c;
    }
   printf ("%d",sum);
   return 0;
}

int AmicableNumTester (int num, int * unique_prime_fac, int * multi)
{ //Using the arithmatic principle that for any number q where
   // q = (m^a)(n^b), the factor sum is (1+m+m^2+...+m^a)(1+n+n^2+...+n^b)...
// e.g. for 200 = 2*2*2*5*5 = (2)^3 *(5)^2, its sum of factors is (1+2+4+8)(1+5+25)
   int m=0, n=0;
   int temp=1, op1[100]={0};
   int i=0;
   int sum;
   
   for (m=0; unique_prime_fac[m]>0; m++) {
      for (n=0; n<multi[m]; n++) {
         temp *= unique_prime_fac[m];
         op1[i] += temp;
      }
      i++;
      temp = 1;
   }
   for (m=0; op1[m]>0; m++) {
      op1[m] += 1;
      sum *= op1[m];
   }
   return sum-num; // The sum above includes the number itself. Deduct it from the result
}

void prime_factorise (int num, const int * prime1, int * unique_prime_fac, int *multi)
{
   int k = 0; /* factor store index */
   int i = 0;
   int *factorstore = malloc(1000);
   
   int counter = 1;
   int a=0, b=0, m=0, n=0, RepeatedElement=NO;
   
   while (num>1) {
      if (num % prime1[i] == 0) {
         factorstore[k++] = prime1[i];
         num /= (prime1[i]);
      } else
         i++;
   }
   factorstore[k] = EOF; // A list of prime factors with possibly repeated elements for e.g. 2, 2, 3, 3, 5 [180]
   for (a=0; factorstore[a]!= EOF; a++) {
      if (factorstore[a] == factorstore[a+1])
         counter ++;
      else {
         multi[b++] = counter;
         counter = 1;
      }
   }
   multi[b] = EOF; // List of multiplicity for the power to each unique prime factors in form for e.g. 2, 2, 1 (for 2x2, 2x3 and 1x5) [180]
   for (m=0; factorstore[m]!=0; m++) {
      for (n=0; n<m; n++) {
         if (factorstore[m] == factorstore[n]) {
            RepeatedElement = YES;
            break;
         }
      } if (!RepeatedElement)
         *unique_prime_fac++ = factorstore[m];
      RepeatedElement = NO;
   }
   *unique_prime_fac = EOF; // A list of unique prime factors in form for e.g. 2, 3, 5 [180]
}

void primelist (int *prime) // Generate a list of prime numbers
{
   unsigned int i,j;
   int counter=0;
    
   prime[0]=2;
   prime[1]=3;
   prime[2]=EOF;
   for (i=3;i<10000;i++)
   {
      counter = 0;
      for (j=0; prime[j]!=EOF;j++)
         if (i% (prime[j]))
            counter++;
      
      if (counter == j) {
         prime[j] = i;
         prime[j+1] = EOF ;
      }
   }
}

// The answer given by this programme is 31626
