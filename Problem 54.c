// Problem 54

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int comp(const void*a,const void*b);
void OrderDeterminant (int (*Val)[2], int *);
int SameRankComparator (int Order, int (*A)[2], int (*B)[2]);
void Converter (char *RawInput, int(*Output1)[2], int(*Output2)[2]);

int main()
{
     int RankA[10] = {0}, RankB[10] = {0};
     int i;
     int Winner = 0, counterA = 0, counterB=0;
     int A[5][2]={0}, B[5][2]={0};
     char buf [40] = {0};
     FILE *fp;
     
     fp = fopen ("/Users/Stellar/Desktop/ProjectEuler/InputDocs/p054_poker.txt","r");
     if (fp == NULL) {
          printf ("Error opening the file.\n");
          return 1;
     }

     while (fgets (buf, 40, fp) != NULL) {
     Converter(buf, A, B);
     qsort(A, 5, sizeof(int)*2, comp);
     qsort(B, 5, sizeof(int)*2, comp)；
     OrderDeterminant (A, RankA);
     OrderDeterminant (B, RankB);
     for (i=0;i<10;i++) {
          if ((!(RankA[i]))&&(!(RankB[i])))
               ;
          else if ((RankA[i])&&(!(RankB[i]))) {
               Winner = 1, counterA++;
               break;
          } else if ((!(RankA[i]))&&(RankB[i])) {
               Winner = 2, counterB++;
               break;
          } else if ((RankA[i])&&(RankB[i])) {
               Winner = SameRankComparator(i, A, B);
               if (Winner == 1) counterA ++;
               else counterB++;
               break;
          }
        }
     }
     printf ("Number of Player 1 wins = %d.\nNumber of Player 2 wins = %d.", counterA, counterB);
     return 0;
}

void Converter (char *RawInput, int(*Output1)[2], int(*Output2)[2])
// Convert card notation to arrays readable by the program
{
     int i,counter = 0;
     char buf[3] = {0}, j=0;
     int a=0, b=0;
     for (i=0; i<=29; i++) {
          if (isalnum(RawInput[i])) {
               buf[j++] = RawInput[i];
               counter++;
          } else { // for blank
               j=0;
               if (counter <= 10) {
               switch (buf[0]) {
                    case '2':Output1[a][0]=2;break;
                    case '3':Output1[a][0]=3;break;
                    case '4':Output1[a][0]=4;break;
                    case '5':Output1[a][0]=5;break;
                    case '6':Output1[a][0]=6;break;
                    case '7':Output1[a][0]=7;break;
                    case '8':Output1[a][0]=8;break;
                    case '9':Output1[a][0]=9;break;
                    case 'T':Output1[a][0]=10;break;
                    case 'J':Output1[a][0]=11;break;
                    case 'Q':Output1[a][0]=12;break;
                    case 'K':Output1[a][0]=13;break;
                    case 'A':Output1[a][0]=14;break;
               } switch (buf[1]) {
                    case 'S':Output1[a++][1]=1;break;
                    case 'D':Output1[a++][1]=2;break;
                    case 'H':Output1[a++][1]=3;break;
                    case 'C':Output1[a++][1]=4;break;
               }
               } else {
               switch (buf[0]) {
                    case '2': Output2[b][0]=2;break;
                    case '3': Output2[b][0]=3;break;
                    case '4': Output2[b][0]=4;break;
                    case '5': Output2[b][0]=5;break;
                    case '6': Output2[b][0]=6;break;
                    case '7': Output2[b][0]=7;break;
                    case '8': Output2[b][0]=8;break;
                    case '9': Output2[b][0]=9;break;
                    case 'T': Output2[b][0]=10;break;
                    case 'J': Output2[b][0]=11;break;
                    case 'Q': Output2[b][0]=12;break;
                    case 'K': Output2[b][0]=13;break;
                    case 'A': Output2[b][0]=14;break;
               } switch (buf[1]) {
                    case 'S': Output2[b++][1]=1;break;
                    case 'D': Output2[b++][1]=2;break;
                    case 'H': Output2[b++][1]=3;break;
                    case 'C': Output2[b++][1]=4;break;
               }
               }
          }
     }
}

int SameRankComparator (int Order, int (*A)[2], int (*B)[2])
// This function is invoked when there is same order cards for both players. The order denotes the type of card that ties (e.g. Order = 2 denotes both players have Straight Flush, we then compare whose SF beats the other.)
{
     int i, j, AStore = 0, BStore = 0;
     switch (Order) {
          case 1: case 4: case 5: // SF, F and S. It's impossible to tie for RF given that the question states that all hands are unambiguous
          // We only need to compare the last element (i.e. Card with the largest value) since the cards are arranged in the ascending order. A Tie is impossible as all five cards are involved and that the question states there is a clear winner for each hand.
              if  (A[4][0] > B[4][0]) return 1;
               return 2;
          case 8: case 7://1 pair or 2 pairs
               for (i=0; i<5; i++)
                    for (j=i+1; j<5;j++) {
                         if ((A[i][0] == A[j][0]) && (A[i][0] > AStore))
                              AStore = A[i][0];
                         if ((B[i][0] == B[j][0]) && (B[i][0] > BStore))
                              BStore = B[i][0];
                    } if (AStore > BStore)
                              return 1;
                      else if (AStore < BStore)
                              return 2;
                      else goto HighCardComparator;
          case 6: case 3: // FH or 3 of a Kind
               i=0;
               while (i<3) {
                    if ((A[i][0] == A[i+1][0])&&(A[i][0]== A[i+2][0]))
                         AStore = A[i][0];
                    if ((B[i][0] == B[i+1][0])&&(B[i][0]== B[i+2][0]))
                         BStore = B[i][0];
                     i++;
               } if (AStore > BStore)
                    return 1;
               else if (AStore < BStore)
                    return 2;
               else goto HighCardComparator;
          case 2: // 4 of a Kind
               i=0;
               while (i<2) {
                    if ((A[i][0] == A[i+1][0])&&(A[i][0]== A[i+2][0])&&(A[i][0] == A[i+3][0]))
                         AStore = A[i][0];
                    if ((B[i][0] == B[i+1][0])&&(B[i][0]== B[i+2][0])&&(B[i][0] == B[i+3][0]))
                         BStore = B[i][0];
                    i++;
               } if (AStore > BStore)
                    return 1;
               else if (AStore < BStore)
                    return 2;
               else goto HighCardComparator;
          default: // High Card
               goto HighCardComparator;
     }
     HighCardComparator: // When two same-ranked card tie
     i=4;
     while (A[i][0] == B[i][0])
          i--;
     if (A[i][0] > B[i][0]) return 1;
     else if (A[i][0] < B[i][0]) return 2;
     else printf ("ERROR");
     return 0;
}

int isFlush (int (*Val)[2]);
int isStraight (int (*Val)[2]);
int NumofPairs (int (*Val)[2]);
void OrderDeterminant (int (*Val)[2], int *Rank)
// Determines the presence/absence of specially ranked cards in a given hand. If a particular card type is present, set the value to 1. Otherwise 0. Rank[0] to Rank[9] is structured in the hierarchy outlined in the comments at the bottom.
{
     int i;
     for (i=0; i<9; i++)
          Rank[i] = 0;
     Rank[9] = 1; // Always high card
     
     if (isFlush(Val)) {
          Rank[4] = 1; // Flush only
          if (isStraight(Val)) {
               Rank[1] = Rank[5] = 1; // SF
               if (Val[0][0] == 10)
                    Rank[0] = 1; // RF
          }
     } else if (isStraight(Val))
               Rank[5] = 1; // Straight only
     
     switch (NumofPairs(Val)) {
          case 1:
               Rank[8] = 1; // 1pair: 2C2
               break;
          case 2:
               Rank[7]=Rank[8]=1; // 2pair: 2C2 + 2C2
               break;
          case 3:
               Rank[6]=Rank[8]=1; // 3 of a kind: 3C2
               break;
          case 4:
               Rank[3]=Rank[7]=Rank[8]=1; // FH: 3C2 + 2C2
               break;
          case 6:
               Rank[2]=Rank[6]=Rank[7]=Rank[8]=1; // 4 of a kind: 4C2
               break;
          default:
               break;
     }
}
int isFlush (int (*Val)[2])
{
     int i;
     for (i=1; i<5; i++)
          if (Val[i][1] != Val[i-1][1])
               return 0;
     return 1;
}
int isStraight (int (*Val)[2])
{
     int i;
     for (i=1; i<5; i++)
          if (Val[i][0] - Val[i-1][0] != 1)
               return 0;
     return 1;
}
int NumofPairs (int (*Val)[2])
{
     int i, j, counter = 0;
     for (i=0; i<5; i++)
          for (j=i+1; j<5; j++)
               if (Val[i][0] == Val[j][0]) 
                   counter ++;
     return counter;
}

int comp(const void*a,const void*b)
// Compare the 1st column in a 2D array
{
     const int *A = a;
     const int *B = b;
     return A[0] - B[0];
}

// The program gives answer 376
// Runtime: 2.0ms

// Note: in Rank[i], the order of i is as followed
//8.One Pair: Two cards of the same value.
//7.Two Pairs: Two different pairs.
//6.Three of a Kind: Three cards of the same value.
//5.Straight: All cards are consecutive values.
//4.Flush: All cards of the same suit.
//3.Full House: Three of a kind and a pair.
//2.Four of a Kind: Four cards of the same value.
//1.Straight Flush: All cards are consecutive values of same suit.
//0.Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.
