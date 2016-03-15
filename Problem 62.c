// Problem 62

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

#define UPPER_BOUND 10000 // Test the cubes up to UPPER_BOUND
#define MAXDIGIT 20 // Maximum allowable number of digits for the cube.
#define NUMOFPERMUTES 5 // The question asks for five permutations

struct collection {
     int *cube; /* Pointer to the cube of the number (expressed in an array) */
     int incidence[10];
     int count; // Count of permuted cubes. Initially 1 for the number itself
     int NumofDigits;
};
int main()
{
     int i, sum = 0, j, k, a = 0;
     int * FindCube (int);
     bool SamePermutation (int *, int *);
     void IncidenceMapping (struct collection);
     struct collection list [UPPER_BOUND];

     for (i = 1; i < UPPER_BOUND; i++) {
          list[i].cube = FindCube(i); // Find i^3
          for (j = 0; j < 10; j++) // Mapping incidence of each digit
               list[i].incidence[j] = 0;
          j = 0;
          while (list[i].cube[j] == 0)
               j++;
          for (; j < MAXDIGIT; j++)
               list[i].incidence[list[i].cube[j]]++;
          list[i].count = 1; // Initialise count
          for (j = 0; j < 10; j++)
               sum += list[i].incidence[j];
          list[i].NumofDigits = sum;
          sum = 0; // Count number of digits.
     }
     printf ("Numbers with more than %d permuted cubes (in numerically ascending order):\nIndex  Cube\n", NUMOFPERMUTES);
     for (i = 1; i < UPPER_BOUND; i++)
          for (k = 1; k < i; k++) {
               if (list[k].NumofDigits < list[i].NumofDigits)
                    ;
               else if (list[k].NumofDigits == list[i].NumofDigits)
                    if (SamePermutation(list[i].incidence, list[k].incidence) == true) {
                         list[k].count ++;
               if (list[k].count >= NUMOFPERMUTES) { // Only check the cubes with the same number of digits
                    printf ("%6d   ", k);
                    while (!list[k].cube[a]) a++;
                    for (; a < MAXDIGIT; a++)
                         printf ("%d", list[k].cube[a]);
                    printf ("\n");
                    a = 0;
                    break;
               }
            }
          }
     return 0;
}

bool SamePermutation (int *List1, int *List2) // Check whether two numbers of the same digits are made up of the same composition of digits. If yes the digits of the two numbers are premutations of each other. The order does not matter
{
     int i;
     for (i=0; i<10; i++)
          if (List1[i] != List2[i])
               return false;
     return true;
}
int * FindCube (int num) /* Store the cube of the number in an int array, return the pointer to it */
{
     void InttoIntArray (int, int *);
     int Array [MAXDIGIT];
     int multiplier = pow (num, 2); // num * (num^2) = num^3
     int i, tempArray[MAXDIGIT], add = 0;
     int *p; // Pointer to the allocated memory
     
     InttoIntArray(num, Array);
     for (i = 0; i < MAXDIGIT; i++)
          tempArray[i] = Array[i];
     for (i = MAXDIGIT; i >= 0; i--) {
          if (Array[i] * multiplier + add < 10) {
               tempArray[i] = Array[i] * multiplier + add;
               add = 0;
          } else {
               tempArray[i] = (Array[i] * multiplier + add) % 10;
               add = (Array[i] * multiplier + add) / 10;
          }
     }
     p = (int *) malloc (sizeof(int) * (MAXDIGIT+1));
     for (i = 0; i < MAXDIGIT; i++)
          p[i] = tempArray[i];
     return p;
}
void InttoIntArray (int num, int *DigitList)
{
     int i;
     int m, n, c;
     
     for (i = 0; i<MAXDIGIT; i++)
          DigitList[i] = 0;
     i = MAXDIGIT - 1;
     DigitList [i--] = num % 10;
     while (num >= 10) {
          num /= 10;
          DigitList [i--] = num % 10;
     } for (m = 0, n = i - 1; m < n; m++, n--) {
          c = DigitList[m];
          DigitList[m] = DigitList[n];
          DigitList[n] = c;
     }
}
// Program gives answer 127035954683 (5027^3)
// Runtime : 125.0ms
