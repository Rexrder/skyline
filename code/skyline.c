#include <stdio.h>
#include "skylib.h"

int main()
{
    int nbuilds = 0;
    int currB = 0;
    int lastB = 0;
    int allB[5000][3] = {0};
    int i = 0;

    nbuilds = inputBuild(allB);
    printf("%d, %d", allB[0][0], allB[0][1]);

    for (i = 1; i < nbuilds; i++)
    {
        lastB = searchlastB(lastB, currB, allB);
        currB = buildCollision(lastB, i, currB, allB);
    }
    currB = gap(lastB, i, currB, allB, 1);
    return 0;
}