#include <stdio.h>

int inputBuild(int allB[][3]); //function to fill array with data according to rules
int searchlastB(int lastB, int currB, int allB[][3]);
int buildCollision(int lastB, int iBuild, int currB, int allB[][3]); //analyse if highest building considered collides with building number i
int gap(int lastB, int iBuild, int currB, int allB[][3], int end);   //analyse buildings between highest building considered and building number i

int inputBuild(int allB[][3])
{
    int i = 0;
    int newBuild = 1;
    for (i = 0; i < 5000 && newBuild == 1; i++) //maximum of 5000 buildings, ending there or when user decides to stop
    {
        //"while" with set of rules to be considered when inserting building data

        printf("\nInsert building data (Li, Hi, Ri): ");
        scanf("%d %d %d", &allB[i][0], &allB[i][1], &allB[i][2]);
        while (allB[i][0] >= 10000 || allB[i][1] >= 10000 || allB[i][1] <= 0 || allB[i][2] >= 10000 || allB[i][0] >= allB[i][2] || allB[i][0] <= i || (i != 0 && allB[i][0] <= allB[i - 1][0]))
        {
            fflush(stdin);
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
    for (int i = lastB; i <= currB && stop == 0; i++)
    {
        if (allB[i][2] > allB[currB][0])
        {
            stop = 1;
            lastB = i;
        }
    }
    return lastB;
}

int buildCollision(int lastB, int iBuild, int currB, int allB[][3])
{
    if (allB[currB][2] >= allB[iBuild][0])
    {
        if (allB[currB][1] < allB[iBuild][1])
        {
            printf(", %d, %d", allB[iBuild][0], allB[iBuild][1]);
            currB = iBuild;
        }
        if (allB[currB][1] == allB[iBuild][1])
        {
            currB = iBuild;
        }
    }
    else
    {
        currB = gap(lastB, iBuild, currB, allB, 0);
    }
    return currB;
}

int gap(int lastB, int iBuild, int currB, int allB[][3], int end)
{
    int max = -1;
    for (int i = lastB; i < iBuild; i++)
    {
        if (i != currB)
        {
            if (allB[i][0] <= allB[currB][2] && allB[i][2] > allB[currB][2])
            {
                if (allB[i][1] > allB[max][1] || max == -1)
                {
                    max = i;
                }
            }
        }
    }
    if (max != -1)
    {
        printf(", %d, %d", allB[currB][2], allB[max][1]);
        if (end == 0)
        {
            currB = buildCollision(lastB, iBuild, max, allB);
        }
        else
        {
            currB = gap(lastB, iBuild, max, allB, 1);
        }
    }
    else
    {
        printf(", %d, %d", allB[currB][2], 0);
        if (end == 0)
        {
            currB = iBuild;
            printf(", %d, %d", allB[currB][0], allB[currB][1]);
        }
    }
    return currB;
}
