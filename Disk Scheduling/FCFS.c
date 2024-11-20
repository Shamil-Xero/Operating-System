#include <stdio.h>
#include <stdlib.h>

// FCFS Disk Scheduling Algorithm
void fcfs(int requests[], int n, int head)
{
    int seek_sequence[n + 1], total_seek_time = 0;

    // Add the initial head position to the seek sequence
    seek_sequence[0] = head;

    // Calculate the seek sequence and total seek time
    for (int i = 0; i < n; i++)
    {
        total_seek_time += abs(head - requests[i]);
        head = requests[i];
        seek_sequence[i + 1] = head;
    }

    // Display results
    printf("Seek Sequence: ");
    for (int i = 0; i <= n; i++)
    {
        printf("%d ", seek_sequence[i]);
    }
    printf("\nTotal Seek Time: %d\n", total_seek_time);
}

int main()
{
    // Predefined inputs
    int requests[] = {98, 183, 41, 122, 14, 124, 65, 67};  // Predefined disk requests
    int n = sizeof(requests) / sizeof(requests[0]);  // Number of requests
    int head = 53;  // Predefined initial head position

    // Call FCFS algorithm
    fcfs(requests, n, head);

    return 0;
}
