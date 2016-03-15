// Project Euler: Problem 12

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void prime_factor (long a, const long * prime1, long * factorstore);
void primelist (long *prime);
int count_primefactor (long *factor);

int main()
{
    long prime[10000]; // List of prime numbers
    long factor[200]; // Array of prime integers
    int i;
    int num_of_divisors; // Pre-set number of divisors. For this question, num_of_divisors is 500. If the number of divisors exceeds this, the program will quit from the loop and print the current value of the triangular number.
    long trinum [30000];

    primelist (prime);
    
    num_of_divisors = 500;

    for (i=0; i<1000000; i++) {
        trinum[i] = (i * (i + 1))/2; // An alternative way to define the ith triangular number from i
        prime_factor (trinum[i], prime, factor); // Generate the list of prime factors of the number
        if (count_primefactor(factor) > num_of_divisors); // Generate the number of factors
            goto print;
        else
            continue;
    }
    print: printf ("The first number of more than %d divisors is %ld", num_of_divisors, trinum[i]);
    return 0;
}


int count_primefactor (long *factor)
{
    int counter = 2;
    int i = 0;
    int k = 0;
    int divisor = 1;
    int counterlist[40];
    
    counter = 2;
    for (i=0; factor[i]!=EOF; i++) { // from the prime factor list generated by function prime_factor
        if (factor[i] == factor[i+1]) // EXAMPLRY NOTE: if there are two identical prime factors (e.g. for 300 = 2*2*3*5*5; factor = [2, 2, 3, 5, 5] The program will give array [3 (for two identical 2), 2 (only one 3), 3 (for two identical 5]. 3*2*3 = 18 gives the total number of factors for number 300
            counter++; // if the current element is equal to the next element, increase the counter by one
        else {
            counterlist[k++] = counter; // if not equal, pass the counter to the store of factors
            counter = 2; // reset the counter
        }
    }
    
    counterlist[k] = EOF;
    
    for (i=0; counterlist[i]!=EOF;i++)
        divisor *= counterlist[i]; //For mathematical reasoning, refer to the EXAMPLRY NOTE above
    
    return divisor;
}

void prime_factor (long num, const long * prime1, long * factorstore)
{
    int k = 0; /* factor store index */
    int i = 0;

    while (num>1) {
        if (num % prime1[i] == 0) { // if the number is divisible by the smallest prime number
            factorstore[k++] = prime1[i]; // divide the number by that prime number; record that prime number as a prime factor
            num /= (prime1[i]); //repeat the process
        } else { // if the number is not divisible
            i++; // try the next prime number in the prime number list
        }
    }
    factorstore[k] = EOF;
    
}


void primelist (long *prime) // generate a list of prime numbers
{
    unsigned long int i,j;
    int counter=0;
    
    prime[0]=2;
    prime[1]=3;
    prime[2]=EOF;
    for (i=3;i<100000;i++)
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

// The program gives answer 76576500.
// Note: need to re-initialise the parameters for every function especially if the function will be repetitively called for ! e.g. Initialise each parameter at the declaration.