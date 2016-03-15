// Problem 45
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
void TriangularNumGenerator (long *);
int ProximityTester (double num);
long TriangularList [300000] = {0};
int main()
{
    long IndexStore[3];
    long NextNum, Pentagonal, Hexagonal, p, h, t;
    int ContinueTask = 0;
    
    TriangularNumGenerator(TriangularList);
    
    for (t=286; ;t++)
    {
        ContinueTask = 0;
        for (p=t-120; ;p--) {
            Pentagonal = p * (3*p-1) / 2;
            if (Pentagonal < TriangularList[t])
                break;
            else if (Pentagonal == TriangularList[t]) {
                ContinueTask = 1;
                break;
            }
        }
            if (ContinueTask) {
                for (h=t-132; ;h--){
                    Hexagonal = h * (2*h-1);
                    if (Hexagonal < TriangularList[t])
                        break;
                    else if (Hexagonal == TriangularList[t]) {
                        NextNum = TriangularList[t];
                        IndexStore[0] = t;
                        IndexStore[1] = p;
                        IndexStore[2] = h;
                        goto found;
                    }
            }
        }
    }
        found:
        printf ("%lu where t=%lu, p=%lu, h=%lu", NextNum,IndexStore[0], IndexStore[1], IndexStore[2]);
        return 0;
}

void TriangularNumGenerator (long *TriangularList)
{
    long t;
    for (t=0; t<300000; t++)
        TriangularList[t] = t * (t+1) / 2;
}

// The program gives answer 1533776805 where t=55385, p=31977, h=27693

