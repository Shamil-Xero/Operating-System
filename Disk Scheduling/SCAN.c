#include <stdio.h>
#include <stdlib.h>

// Function to sort the requests array
void sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// SCAN Disk Scheduling Algorithm
void scan(int requests[], int n, int head, int disk_size, int direction)
{
    int seek_sequence[n + 2], seek_count = 0, index = 0;

    // Adding head position to seek sequence
    seek_sequence[index++] = head;

    // Sort the requests
    sort(requests, n);

    // Partition requests into two parts based on the current head position
    int left[n], right[n], left_count = 0, right_count = 0;
    for (int i = 0; i < n; i++)
    {
        if (requests[i] < head)
        {
            left[left_count++] = requests[i];
        }
        else
        {
            right[right_count++] = requests[i];
        }
    }

    // If moving towards the smaller numbers first
    if (direction == 0)
    {
        // Process left then right
        for (int i = left_count - 1; i >= 0; i--)
        {
            seek_sequence[index++] = left[i];
        }
        seek_sequence[index++] = 0; // Reaches the start of the disk
        for (int i = 0; i < right_count; i++)
        {
            seek_sequence[index++] = right[i];
        }
    }
    // If moving towards the larger numbers first
    else
    {
        // Process right then left
        for (int i = 0; i < right_count; i++)
        {
            seek_sequence[index++] = right[i];
        }
        seek_sequence[index++] = disk_size - 1; // Reaches the end of the disk
        for (int i = left_count - 1; i >= 0; i--)
        {
            seek_sequence[index++] = left[i];
        }
    }

    // Calculate total seek time
    for (int i = 1; i < index; i++)
    {
        seek_count += abs(seek_sequence[i] - seek_sequence[i - 1]);
    }

    // Display results
    printf("Seek Sequence: ");
    for (int i = 0; i < index; i++)
    {
        printf("%d ", seek_sequence[i]);
    }
    printf("\nTotal Seek Time: %d\n", seek_count);
}

int main()
{
    // Predefined inputs
    int requests[] = {98, 183, 41, 122, 14, 124, 65, 67};  // Predefined disk requests
    int n = sizeof(requests) / sizeof(requests[0]);  // Number of requests
    int head = 53;  // Predefined initial head position
    int disk_size = 200;  // Predefined disk size
    int direction = 1;  // Predefined direction (1 for right)

    // Call SCAN algorithm with predefined inputs
    scan(requests, n, head, disk_size, direction);

    return 0;
}
