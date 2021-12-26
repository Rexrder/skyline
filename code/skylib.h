#include <stdio.h>

int inputBuild(int allB[][3]); //function to fill array with data according to rules
int searchlastB(int lastB, int currB, int allB[][3]); //function to keep the last important building data, so other functions don't have to pass through all buildings
int buildCollision(int lastB, int iBuild, int currB, int allB[][3]); //analyse if current highest building collides with building number i
int gap(int lastB, int iBuild, int currB, int allB[][3], int end);   //analyse buildings between current highest building and building number i. If end, gap between current highest building and end

int inputBuild(int allB[][3])
{
    int i = 0;
    int newBuild = 1;
    for (i = 0; i < 5000 && newBuild == 1; i++) //maximum of 5000 buildings, ending there or when user decides to stop
    {
        printf("\nInsert building data (Li, Hi, Ri): ");
        scanf("%d %d %d", &allB[i][0], &allB[i][1], &allB[i][2]); //write data into arrays
        //"while" with set of rules to be considered when inserting building data
        while (allB[i][0] >= 10000 || allB[i][1] >= 10000 || allB[i][1] <= 0 || allB[i][2] >= 10000 || allB[i][0] >= allB[i][2] || allB[i][0] <= i || (i != 0 && allB[i][0] <= allB[i - 1][0]))
        {
            fflush(stdin); //clean buffer to avoid infinte loop on scanf when different type input is inserted
            printf("\nInvalid input. Insert building data again(Li, Hi, Ri): ");
            scanf("%d %d %d", &allB[i][0], &allB[i][1], &allB[i][2]);
        }

        //query to stop adding buildings
        do
        {
            printf("\nInsert 1 to add new building, 0 to end input: ");
            scanf("%d", &newBuild);
        } while (newBuild != 0 && newBuild != 1);
    }
    return i; //return number of buildings
}

int searchlastB(int lastB, int currB, int allB[][3])
{
    int stop = 0;
    for (int i = lastB; i <= currB && stop == 0; i++) //condition takes into account all buildings between current last building and current highest building
    {
        if (allB[i][2] > allB[currB][0]) //if buildings collide
        {
            stop = 1;
            lastB = i;
        }
    }
    return lastB; //return new last important building
}

int buildCollision(int lastB, int iBuild, int currB, int allB[][3])
{
    if (allB[currB][2] >= allB[iBuild][0]) //if current highest building collides with i building...
    {
        if (allB[currB][1] < allB[iBuild][1]) //if current highest building is lower than i building...
        {
            printf(", %d, %d", allB[iBuild][0], allB[iBuild][1]); //print i building's left coordinate and height
            currB = iBuild; //i building is new highest building
        }
        if (allB[currB][1] == allB[iBuild][1]) //if same height...
        {
            currB = iBuild; //i building is new highest building
        }
        //if current building is higher than  i building, end function
    }
    else //if doesn't collide...
    {
        currB = gap(lastB, iBuild, currB, allB, 0); //deal with buildings between current and i building
    }
    return currB; //return current highest building position
}

int gap(int lastB, int iBuild, int currB, int allB[][3], int end)
{
    int max = -1; //position of the highest building in the inmediate space after current highest building. If -1, there isn't any building.
    for (int n = lastB; n < iBuild; n++) //take into account all the buildings between last important and i buildings
    {
        if (n != currB) //if n building is different than current building...
        {
            if (allB[n][0] <= allB[currB][2] && allB[n][2] > allB[currB][2]) //if Ln <= Ri and Rn > Ri...
            {
                if (allB[n][1] > allB[max][1] || max == -1) //if n building is higher than last highest n building or n is the first building to fulfill requirements...
                {
                    max = n; //n is the new highest building inmediately after current building
                }
            }
        }
    }
    if (max != -1) //if there's a building...
    {
        printf(", %d, %d", allB[currB][2], allB[max][1]); //print right coordinate of current building and height of new highest building
        if (end == 0) //if it's not the end...
        {
            currB = buildCollision(lastB, iBuild, max, allB); //analyse collisions between new current building and i building
        }
        else //if it's the end...
        {
            currB = gap(lastB, iBuild, max, allB, 1); //gap between current building and the end
        }
    }
    else //if there's no building
    {
        printf(", %d, %d", allB[currB][2], 0); //print right coordinate of current building and 0 (floor level height)
        if (end == 0) //if it's not the end...
        {
            currB = iBuild; //assign i building's position to current building
            printf(", %d, %d", allB[currB][0], allB[currB][1]); //print new current building's left coordinate and height
        }
    }
    return currB; //return current building position
}
