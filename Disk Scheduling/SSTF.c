#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to calculate the absolute difference
int absoluteDifference(int a, int b)
{
    return (a > b) ? (a - b) : (b - a);
}

// SSTF Disk Scheduling Algorithm
void sstf(int requests[], int n, int head)
{
    bool serviced[n];
    int totalSeekTime = 0;

    // Mark all requests as unserviced
    for (int i = 0; i < n; i++)
    {
        serviced[i] = false;
    }

    printf("Seek Sequence: %d", head);

    for (int i = 0; i < n; i++)
    {
        int nearestRequestIndex = -1;
        int minimumSeekTime = 9999;

        // Find the unserviced request nearest to the current head
        for (int j = 0; j < n; j++)
        {
            if (!serviced[j])
            {
                int seekTime = absoluteDifference(head, requests[j]);
                if (seekTime < minimumSeekTime)
                {
                    minimumSeekTime = seekTime;
                    nearestRequestIndex = j;
                }
            }
        }

        // Move head to the nearest request and mark it as serviced
        if (nearestRequestIndex != -1)
        {
            serviced[nearestRequestIndex] = true;
            totalSeekTime += minimumSeekTime;
            head = requests[nearestRequestIndex];
            printf(" -> %d", head);
        }
    }

    printf("\nTotal Seek Time: %d\n", totalSeekTime);
}

int main()
{
    // Predefined inputs
    int requests[] = {98, 183, 41, 122, 14, 124, 65, 67};  // Predefined disk requests
    int n = sizeof(requests) / sizeof(requests[0]);  // Number of requests
    int head = 53;  // Predefined initial head position

    // Call SSTF algorithm with predefined inputs
    sstf(requests, n, head);

    return 0;
}
