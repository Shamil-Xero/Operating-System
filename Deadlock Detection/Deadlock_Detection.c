#include <stdio.h>
#include <stdbool.h>

#define P 5 // Number of processes
#define R 3 // Number of resources

// Function to check for deadlock
bool isDeadlocked(int allocation[][R], int request[][R], int avail[], int processes[])
{
    int work[R];
    bool finish[P] = {false}; // To track finished processes
    int deadlockDetected = 0;

    // Initialize the work array with available resources
    for (int i = 0; i < R; i++)
    {
        work[i] = avail[i];
    }

    // Try to find a process that can finish (its request is less than available resources)
    for (int i = 0; i < P; i++)
    {
        if (!finish[i])
        {
            bool canFinish = true;

            // Check if all requests can be satisfied with available resources
            for (int j = 0; j < R; j++)
            {
                if (request[i][j] > work[j])
                {
                    canFinish = false;
                    break;
                }
            }

            if (canFinish)
            {
                // Add allocated resources back to the available resources
                for (int j = 0; j < R; j++)
                {
                    work[j] += allocation[i][j];
                }
                finish[i] = true; // Mark process as finished
            }
            else
            {
                deadlockDetected++; // If the process cannot finish, it's part of the deadlock
            }
        }
    }

    // If there is a process that could not finish, deadlock exists
    if (deadlockDetected > 0)
    {
        printf("Deadlock detected! The following processes are deadlocked:\n");
        for (int i = 0; i < P; i++)
        {
            if (!finish[i])
            {
                printf("P%d ", processes[i]);
            }
        }
        printf("\n");
        return true;
    }

    printf("No deadlock detected.\n");
    return false;
}

int main()
{
    // Process IDs
    int processes[] = {0, 1, 2, 3, 4};

    // Allocation Matrix (how many resources are allocated to each process)
    int allocation[][R] = {
        {0, 1, 0}, // P0
        {2, 0, 0}, // P1
        {3, 0, 2}, // P2
        {2, 1, 1}, // P3
        {0, 0, 2}  // P4
    };

    // Request Matrix (how many resources each process is requesting)
    int request[][R] = {
        {1, 0, 0}, // P0
        {1, 0, 2}, // P1
        {2, 1, 1}, // P2
        {1, 1, 1}, // P3
        {1, 1, 0}  // P4
    };

    // Available resources
    int avail[] = {3, 3, 2}; // 3 instances of resource 1, 3 of resource 2, and 2 of resource 3

    // Function to detect deadlock
    isDeadlocked(allocation, request, avail, processes);

    return 0;
}
