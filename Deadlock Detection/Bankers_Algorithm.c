#include <stdio.h>
#include <stdbool.h>

#define P 5 // Number of processes
#define R 3 // Number of resources

int available[R] = {3, 3, 2}; // Available instances of each resource
int max[P][R] = {             // Maximum demand of each process
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}};
int allocation[P][R] = { // Currently allocated resources
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}};
int need[P][R]; // Remaining resource needs

void calculateNeed()
{
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool isSafe()
{
    int work[R];
    bool finish[P] = {false};

    for (int i = 0; i < R; i++)
    {
        work[i] = available[i];
    }

    for (int i = 0; i < P; i++)
    {
        bool found = false;
        for (int j = 0; j < P; j++)
        {
            if (!finish[j])
            {
                bool safe = true;
                for (int k = 0; k < R; k++)
                {
                    if (need[j][k] > work[k])
                    {
                        safe = false;
                        break;
                    }
                }
                if (safe)
                {
                    for (int k = 0; k < R; k++)
                    {
                        work[k] += allocation[j][k];
                    }
                    finish[j] = true;
                    found = true;
                }
            }
        }
        if (!found)
        {
            return false; // System is not in a safe state
        }
    }
    return true; // System is in a safe state
}

int main()
{
    calculateNeed();

    if (isSafe())
    {
        printf("The system is in a safe state.\n");
    }
    else
    {
        printf("The system is not in a safe state.\n");
    }

    return 0;
}
