#include <stdio.h>
#include <stdlib.h>
int procNum;
int resourceNum = 3;

void display(int m, int n, int arr[m][n])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int checkAvailability(int singleProcessNeed[], int resourceAvail[])
{
    int flag = 1;

    for (int i = 0; i < resourceNum; i++)
    {
        if (!(singleProcessNeed[i] <= resourceAvail[i]))
        {
            flag = 0;
            break;
        }
    }

    return flag;
}

void returnResources(int resourceAvail[], int singleProcessAlloc[])
{
    for (int i = 0; i < resourceNum; i++)
        resourceAvail[i] += singleProcessAlloc[i];
}

int checkSafeState(int resourceAvail[], int resources[], int satisfied[])
{
    for (int i = 0; i < resourceNum; i++)
    {
        if (!(resourceAvail[i] == resources[i] && satisfied[i]))
            return 0;

        return 1;
    }
}

void main()
{
    printf("No. of processes : ");
    scanf("%d", &procNum);

    int processAlloc[procNum][resourceNum];
    int processMax[procNum][resourceNum];
    int processNeed[procNum][resourceNum];
    int resourceAvail[resourceNum];
    int resources[resourceNum];
    int satisfied[procNum];

    for (int i = 0; i < procNum; i++)
        satisfied[i] = 0;

    resources[0] = 10;
    resources[1] = 5;
    resources[2] = 7;

    // MAXIMUM NUMBER OF RESOURCES
    for (int i = 0; i < procNum; i++)
    {
        printf("MAXIMUM No. of resources for process %d : \n", i + 1);
        for (int j = 0; j < resourceNum; j++)
        {
            printf("Resource %d : ", j + 1);
            scanf("%d", &processMax[i][j]);
        }
    }

    printf("\n\n");

    // NUMBER OF RESOURCES ALLOCATED
    for (int i = 0; i < procNum; i++)
    {
        printf("No. of resources allocated to process %d : \n", i + 1);
        for (int j = 0; j < resourceNum; j++)
        {
            printf("Resource %d : ", j + 1);
            scanf("%d", &processAlloc[i][j]);
        }
    }

    // CALCULATE NEED OF PROCESSES
    for (int i = 0; i < procNum; i++)
        for (int j = 0; j < resourceNum; j++)
            processNeed[i][j] = processMax[i][j] - processAlloc[i][j];

    // CALCULATE AVAILABLITY OF RESOURCES
    for (int i = 0; i < resourceNum; i++)
    {
        int sum = 0;

        for (int j = 0; j < procNum; j++)
            sum += processAlloc[j][i];

        resourceAvail[i] = resources[i] - sum;
    }
    printf("\nAvailable : ");
    for (int i = 0; i < resourceNum; i++)
        printf("%d ", resourceAvail[i]);

    printf("\n\nNEED : \n");
    display(procNum, resourceNum, processNeed);

    // CHECKING OF SAFE STATE
    for (int i = 0; i < procNum; i = (i + 1) % procNum)
    {
        if (!satisfied[i] && checkAvailability(processNeed[i], resourceAvail))
        {
            satisfied[i] = 1;

            returnResources(resourceAvail, processAlloc[i]);

            printf("Available %d : ", i + 1);
            for (int j = 0; j < resourceNum; j++)
                printf("%d ", resourceAvail[j]);
            printf("\n");

            if (checkSafeState(resourceAvail, resources, satisfied))
            {
                printf("Safe system\n");
                break;
            }
        }
    }

    if (!checkSafeState(resourceAvail, resources, satisfied))
        printf("Unsafe system\n");
}