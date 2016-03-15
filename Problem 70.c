// Problem 70
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAXNUM 10000000
#define MAXFACTOR 8

int prime [500] = {0};
struct Factors{
     int number;
     int * DistinctPrimes;
     int phi;
};
static struct Factors num [MAXNUM];
int isPrime (long, int);

int main()
{
     void primelist ();
     int search (int, int*);
     void intcat(int *, int *);
     int FindPhi (struct Factors);
     int isPermutation (int, int);
     int i,j;
     double MinimalRatio = 1.1;
     double ratio;
     
     primelist();
     for (i = 0; i < MAXNUM; i ++) {
          num[i].number = i;
          num[i].DistinctPrimes = NULL;
          if (isPrime(i, 1)) {
               num[i].DistinctPrimes = malloc(sizeof(int));
               *num[i].DistinctPrimes = i;
          } else {
               for (j = 0; prime[j] <= sqrt(i); j++) {
                    if (!(i % prime[j])) {
                         if (search(prime[j], num[i/prime[j]].DistinctPrimes))
                              num[i].DistinctPrimes = num[i/prime[j]].DistinctPrimes;
                         else {
                              num[i].DistinctPrimes = malloc(MAXFACTOR*sizeof(int));
                              *num[i].DistinctPrimes = prime[j];
                              intcat (num[i].DistinctPrimes, num[i/prime[j]].DistinctPrimes);
                         }
                         break;
                    } else
                         continue;
               }
          }
          num[i].phi = FindPhi(num[i]);
          if (num[i].phi != 0 && (ratio = (double) num[i].number / (double) num[i].phi) < MinimalRatio)
               if (isPermutation(num[i].number, num[i].phi)) {
                    printf ("%7d  %7d  %6f\n", num[i].number, num[i].phi, ratio);
                    MinimalRatio = ratio;
               }
     }
     return 0;
}

int isPermutation (int a, int b)
{
     int incidenceA [10] = {0};
     int incidenceB [10] = {0};
     int i;
     if (a == b)
          return 0; // Permutation excldes same number
     do {
          incidenceA [a%10]++;
          a /= 10;
     } while (a > 0);
     while (b > 0) {
          if (!incidenceA [b%10])
               return 0;
          incidenceB [b%10]++;
          b /= 10;
     }
     for (i = 0; i < 10; i++)
          if (incidenceB[i] != incidenceA[i])
               return 0;
     return 1;
}

int FindPhi (struct Factors num)
{
     int i;
     double product = num.number, quotient;
     if (num.DistinctPrimes == NULL) {
          num.phi = 0;
          return 0;
     }
     for (i = 0; num.DistinctPrimes[i] != 0; i++) {
          quotient = 1 - (1 / ((double) num.DistinctPrimes[i]));
          product *= quotient;
     }
     return product;
}

void intcat (int *array1, int *array2)
{
     int i = 0, j;
     while (array1[i] != 0)
          i++;
     for (j = 0; array2[j]!=0; j++)
          array1[i++] = array2[j];
}

int search (int element, int *array)
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
     
     if(p < 2){
          return 0;
     } if(p != 2 && p % 2 == 0){
          return 0;
     }
     long long s = p-1;
     while(s % 2 == 0){
          s /= 2;
     }
     for(int i = 0; i < iteration;i++){
          long a = rand() % (p - 1) + 1,temp = s;
          long mod = modulo (a,temp,p);
          while (temp != p-1 && mod != 1 && mod != p-1){
               mod = mulmod(mod,mod,p);
               temp *= 2;
          } if(mod != p-1 && temp %2 == 0){
               return 0;
          }
     }
     return 1;
}
// Miller-Rabin Functions
long mulmod(long a, long b, long c){
     long x = 0,y = a % c;
     while(b > 0){
          if(b % 2 == 1){
               x = (x + y) % c;
          }
          y = (y * 2) % c;
          b /= 2;
     }
     return x % c;
}

int modulo(int a,int b,int c){
     long x = 1,y = a;
     while(b > 0){
          if(b % 2 == 1){
               x = (x * y) % c;
          }
          y = (y * y) % c;
          b /= 2;
     }
     return x % c;
}

// Program output reads as followed
/* n      phi(n)  ratio
 20617    20176  1.021858
 45421    44512  1.020421
 69271    67912  1.020011
 75841    75184  1.008739
 162619   161296  1.008202
 176569   175696  1.004969
 284029   282940  1.003849
 400399   399040  1.003406
 474883   473488  1.002946
 732031   730312  1.002354
 778669   776896  1.002282
 783169   781396  1.002269
 1014109  1011904  1.002179
 1288663  1286368  1.001784
 1504051  1501504  1.001696
 1514419  1511944  1.001637
 1924891  1921984  1.001512
 1956103  1953160  1.001507
 2006737  2003776  1.001478
 2044501  2041504  1.001468
 2094901  2091904  1.001433
 2239261  2236192  1.001372
 2710627  2707216  1.001260
 2868469  2864896  1.001247
 3582907  3578920  1.001114
 3689251  3685192  1.001101
 4198273  4193728  1.001084
 4696009  4690960  1.001076
 5050429  5045920  1.000894
 5380657  5375860  1.000892
 5886817  5881876  1.000840
 6018163  6013168  1.000831
 6636841  6631684  1.000778
 7026037  7020736  1.000755
 7357291  7351792  1.000748
 7507321  7501732  1.000745
 8316907  8310976  1.000714
 8319823  8313928  1.000709
*/
// We can see that the last column shows the pair of n and phi(n) with the smallest ratio. Hence the answer to the question is n = 8319823.
// Runtime: 6983.0ms (6.9s T_T)
