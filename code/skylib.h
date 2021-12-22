#include <stdio.h>

int inputBuild(int allB[][3]); //function to fill array with data according to rules
void gapMax(int ultBuild, int iBuild, int maxBuild, int allB[][3]);

int inputBuild(int allB[][3])
{
    int newBuild = 1;
    for (int i = 0; i < 5000 && newBuild == 1; i++) //maximum of 5000 buildings, ending there or when user decides to stop
    {
        do
        {
            printf("\nInsert building data (Li, Hi, Ri): ");
            scanf("%d %d %d", &allB[i][0], &allB[i][1], &allB[i][2]);
        } while (allB[i][0] >= 10000 || allB[i][1] >= 10000 || allB[i][1] <= 0 || allB[i][2] >= 10000 || allB[i][0] >= allB[i][2] || allB[i][0] <= i || (i != 0 && allB[i][0] <= allB[i - 1][0]));
        //"while" with set of rules to be considered when inserting building data
        do
        {
            printf("\nInsert 1 to add new building, 0 to end input: ");
            scanf("%d", &newBuild);
        } while (newBuild != 0 && newBuild != 1);
        //query to stop adding buildings
    }
    return i; //return number of buildings
}

void gapMax(int ultBuild, int iBuild, int maxBuild, int allB[][3])
{
    if (allB[maxBuild][2] < allB[iBuild][0])
    {
        int max = -1;
        for (int i = ultBuild; i < iBuild; i++)
        {
            if (i != maxBuild)
            {
                if (allB[i][0] <= allB[maxBuild][2] && allB[i][2] > allB[maxBuild][2])
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
            printf(", %d, %d", allB[maxBuild][2], allB[max][1]);
            gapMax(ultBuild, iBuild, max, allB);
        }
        else
        {
            printf(", %d, %d", allB[maxBuild][2], 0);
        }
    }
    else{

    }
}