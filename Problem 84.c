//Problem 84
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#define MAXSIMULATION 10000000
#define DICEFACE 4

enum {GO,A1,CC1,A2,T1,R1,B1,CH1,B2,B3,JAIL,
     C1,U1,C2,C3,R2,D1,CC2,D2,D3,FP,
     E1,CH2,E2,E3,R3,F1,F2,U2,F3,G2J,
     G1,G2,CC3,G3,R4,CH3,H1,T2,H2};
int Incidence [40] = {0};
struct RK {
     int index;
     double odd;
};
bool isDouble = false;
int main()
{
     int MoveDeterminer (int, int, bool);
     int cmp( const void *a ,const void *b);
     int iteration = 0;
     int CurrentCell = 0;
     int ThrowDice (bool *), DiceMove;
     struct RK rank [40];
     int i;
     
     srand((unsigned int)time(NULL));
     for (iteration = 0; iteration < MAXSIMULATION; iteration++) {
          DiceMove = ThrowDice(&isDouble);
          CurrentCell = MoveDeterminer(CurrentCell, DiceMove, isDouble);
     }
     for (i = 0; i < 40; i++) {
          rank[i].index = i;
          rank[i].odd = (double)Incidence[i]/ (double)iteration*100;
     }
     qsort(rank, 40, sizeof(rank[0]), cmp);
     printf ("Dice has %d faces \nSimulated %d times:\n", DICEFACE, iteration);
     printf ("Rank  Cell    Odd    Incidence\n");
     for (i = 0; i < 40; i++) {
          if (i == 3)
               printf ("\n");
          printf ("%2d:    %2d   %7f  %6d\n", i+1, rank[i].index, rank[i].odd, Incidence[rank[i].index]);
     }
     return 0;
}

int CommunityChest (int);
int Chance (int);
int DoubleCount = 0;
int MoveDeterminer (int StartingCell, int DiceMove, bool isDouble)
{
     int tempmove, returnval;

     if (DiceMove) {
          if (isDouble) {
               if (DoubleCount > 3) { // The player goes to jail for 3 consecutive doubles
                    returnval = JAIL;
                    DoubleCount = 0;
                    goto nextstep;
               }
               else
                    DoubleCount++;
          } else
               DoubleCount = 0;
     }
     tempmove = (StartingCell + DiceMove) % 40;
     switch (tempmove) {
          case CC1: case CC2: case CC3: {
               returnval = CommunityChest(tempmove);
               goto nextstep;
          } case CH1: case CH2: case CH3: {
               returnval = Chance(tempmove);
               goto nextstep;
          } case G2J:
               returnval = JAIL;
               goto nextstep;
          default:
               returnval = tempmove;
               goto nextstep;
     }
     nextstep:
     Incidence[returnval]++;
     if (returnval == JAIL)
          DoubleCount = 0;
     return returnval;
}

int ThrowDice (bool *isDouble) {
     int dice1 = 1 + rand() % DICEFACE;
     int dice2 = 1 + rand() % DICEFACE;
     *isDouble = (dice1 == dice2)? true : false;
     return dice1 + dice2;
}

int CommunityChest (int CurrentPosition)
{
     int draw = rand() % 16;
     if (draw == 1)
          return GO;
     else if (draw == 2)
          return JAIL;
     return CurrentPosition;
}

int Chance (int CurrentPosition)
{
     int draw = rand() % 16;
     int GoBack;
     
     switch (draw) {
          case 1:
               return GO;
          case 2:
               return JAIL;
          case 3:
               return C1;
          case 4:
               return E3;
          case 5:
               return H2;
          case 6:
               return R1;
          case 7: case 8: { // Next Railway
               if (CurrentPosition == CH1)
                    return R2;
               else if (CurrentPosition == CH2)
                    return R3;
               else
                    return R1;
          }
          case 9: { // Next Utility
               if (CurrentPosition == CH1)
                    return U1;
               else if (CurrentPosition == CH2)
                    return U2;
               else
                    return U1;
          }
          case 10: {
               if ((GoBack = CurrentPosition - 3) < 0)
                    return MoveDeterminer(GoBack+40,0,isDouble);
               return MoveDeterminer(GoBack, 0, isDouble);
          }
          default:
               break;
     }
     return CurrentPosition;
}

int cmp( const void *a ,const void *b)
{ return (*(struct RK *)a).odd < (*(struct RK *)b).odd ? 1 : -1; }