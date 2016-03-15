// Project Euler: Problem 31
// Solved by Dynamic Programming

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define YES 1
#define NO 0

int CoinValue[] = {1, 2, 5, 10, 20, 50, 100, 200};
void CoinCombinations (char **, int, char *,int);

int main()
{
     int Combinations [201][8] = {0}; // 201 for 0....200; 9 for the nine types of coins
     int j,i,k;
     
     for (i=0; i<=7; i++)
          Combinations[0][i] = 1;
     
     for (i=0; i<=200; i++)
          Combinations[i][0] = 1;
     
     for (i=1; i<=200; i++) //Current Sum calculated
          for (j=1; j<=7; j++) { // Current CoinValue looped
               if (i >= CoinValue[j])
               Combinations[i][j] = Combinations[i][j-1] + Combinations [i-CoinValue[j]][j];
               else
                    for (k=j; k<=7; k++)
                         Combinations[i][k] = Combinations[i][j-1];
          }

     printf ("%d", Combinations[200][7]);
     
     return 0;
}



// Brute Force Enumeration: Takes too long to give the answer!
void CoinCombinations (char *Comb_Store[], int MoneyLeft, char * SelectionArray, int CurrentPlace)
{
     char LocalSelectionArray [9];
     int i, j,k, Operand;
     
     for (i=1; i<4; i++) {
          if (MoneyLeft >= CoinValue[i]) {
               Operand = MoneyLeft - CoinValue[i];
               for (k=1;k<9;k++)
                    LocalSelectionArray[k] = SelectionArray[k]; // Reset Local Selection Array;
               LocalSelectionArray[i] = SelectionArray[i] + 1;
          } else break;
          
          if (Operand == 0) {
               Comb_Store[CurrentPlace] = LocalSelectionArray;
          for (j=1; j<9; j++)
               printf ("%d ",Comb_Store[CurrentPlace][j]);
          printf ("\n");
          break;
          
     } else
          CoinCombinations (Comb_Store, Operand, LocalSelectionArray, CurrentPlace+1);
     }
}
