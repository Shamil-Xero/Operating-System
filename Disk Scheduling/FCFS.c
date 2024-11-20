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
    int n, head;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the requests:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    // Call FCFS algorithm
    fcfs(requests, n, head);

    return 0;
}
