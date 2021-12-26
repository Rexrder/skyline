#include <stdio.h>
#include "skylib.h" //include skylib functions

int main()
{
    int nbuilds = 0;
    int currB = 0;
    int lastB = 0;
    int allB[5000][3] = {0}; //create array for buildings' data storage
    int i = 0;

    nbuilds = inputBuild(allB); //fill array with data
    printf("%d, %d", allB[0][0], allB[0][1]); //print left coordinate and height of first building

    for (i = 1; i < nbuilds; i++) //analyse each building
    {
        lastB = searchlastB(lastB, currB, allB); //store last importante building
        currB = buildCollision(lastB, i, currB, allB); //analyse collisions between current highest building and i building
    }
    currB = gap(lastB, i, currB, allB, 1); //analyse buildings between current highest building and end
    return 0; //program's end
}