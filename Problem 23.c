// Project Euler: Problem 23
// Abundant number finder is adapted from the functions in Problem 21

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define YES 1
#define NO 0

int AllFactors (int num, const int * prime1);
void primelist (int *prime);

int main()
{
   int a, b=0, c=0, op1;
   int prime[1230]={0};
   
   long sum1 = 0;
   
   int AbundantNumList [6965];
   int AllNum [28124];
   
   for (a=1; a<28124; a++)
      AllNum[a] = a;
   
   primelist (prime);
   
   for (a=12; a<=28123; a++) { // The question instructs that the first abundant number is 12
      b = AllFactors(a, prime);
      if (b > a)
         AbundantNumList[c++] = a;
   } // 1. List all abundant numbers below 28123
   
   for (a=0; a<c; a++) {
      for (b=a; b<c; b++) {
         
         op1 = AbundantNumList[a] + AbundantNumList [b];
         
         if (op1 > 28123)
            break;
         
         else
            AllNum[op1] = 0;
         }
   }
   
       // 2. List all possibilities of sum of two abundant numbers below 28123
   
   for (a=1; a<28124; a++)
      sum1 += AllNum[a]; //Sum of all numbers
   
   printf ("%lu", sum1);
   
   return 0;
   
  }

int AllFactors (int num, const int * prime1)
{ // For working mechanism, refer to the solution to Problem 21. This function is a combination of the two central functions in Solution 21.
   int k = 0, i = 0;
   int *factorstore = malloc(1000);
   int multiplicity [100] = {0};
   
   int counter = 1, a=0, b=0, m=0, n=0, RepeatedElement=NO;
   int UniquePrimeFactor [100] = {0};
   int *uni_pri_fac = UniquePrimeFactor;
   
   int m1=0, n1=0, temp=1, op1[100]={0}, i1=0, sum = 1, numstore;
   
   numstore = num;
   
   while (num>1) {
      if (num % prime1[i] == 0) {
         factorstore[k++] = prime1[i];
         num /= (prime1[i]);
      }
      else
         i++;
   }
   
   factorstore[k] = EOF;
   
   for (a=0; factorstore[a]!= EOF; a++) {
      if (factorstore[a] == factorstore[a+1])
         counter ++;
      else {
         multiplicity[b++] = counter;
         counter = 1;
      }
   }
   
   multiplicity[b] = EOF;
   
   for (m=0; factorstore[m]!=0; m++) {
      for (n=0; n<m; n++) {
         if (factorstore[m] == factorstore[n]) {
            RepeatedElement = YES;
            break;
         }
      }
      if (!RepeatedElement)
         *uni_pri_fac++ = factorstore[m];
      RepeatedElement = NO;
   }
   
   *uni_pri_fac = EOF;
   
   for (m1=0; UniquePrimeFactor[m1]>0; m1++) {
      for (n1=0; n1<multiplicity[m1]; n1++) {
         temp *= UniquePrimeFactor[m1];
         op1[i1] += temp;
      }
      i1++;
      temp = 1;
   }
   
   for (m1=0; op1[m1]>0; m1++)
   {
      op1[m1] += 1;
      sum *= op1[m1];
   }
   
   free(factorstore);
   
   return sum-numstore;
}


void primelist (int *prime)
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

// Answer given by the program is 4179871


