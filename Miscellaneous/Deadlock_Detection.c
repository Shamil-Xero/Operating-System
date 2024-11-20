#include <stdio.h>

#define P 5 // Number of processes
#define R 3 // Number of resources

int allocation[P][R] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}};
int max[P][R] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}};
int available[R] = {2, 3, 3}; // Changing the available resources will lead to deadlocks

void calculateNeed(int need[P][R])
{
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

int isSafe()
{
    int need[P][R];
    calculateNeed(need);

    int work[R];
    int finish[P] = {0};

    for (int i = 0; i < R; i++)
    {
        work[i] = available[i];
    }

    for (int i = 0; i < P; i++)
    {
        if (finish[i] == 0)
        {
            int safe = 1;
            for (int j = 0; j < R; j++)
            {
                if (need[i][j] > work[j])
                {
                    safe = 0;
                    break;
                }
            }
            if (safe)
            {
                for (int j = 0; j < R; j++)
                {
                    work[j] += allocation[i][j];
                }
                finish[i] = 1;
                i = -1; // Reset loop to recheck all processes
            }
        }
    }

    for (int i = 0; i < P; i++)
    {
        if (finish[i] == 0)
        {
            return 0; // System is not in a safe state
        }
    }
    return 1; // System is in a safe state
}

int main()
{
    if (isSafe())
    {
        printf("System is in a safe state.\n");
    }
    else
    {
        printf("System is in a deadlock state.\n");
    }
    return 0;
}