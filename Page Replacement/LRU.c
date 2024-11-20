#include <stdio.h>
#include <limits.h>

// Function to find the least recently used page index
int findLRU(int time[], int frameCount)
{
    int minTime = INT_MAX, lruIndex = -1;
    for (int i = 0; i < frameCount; i++)
    {
        if (time[i] < minTime)
        {
            minTime = time[i];
            lruIndex = i;
        }
    }
    return lruIndex;
}

// LRU Page Replacement Function
void lruPageReplacement(int pages[], int totalPages, int frameCount)
{
    int frames[frameCount], time[frameCount];
    int pageFaults = 0, currentTime = 0;

    // Initialize frames and time arrays
    for (int i = 0; i < frameCount; i++)
    {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("Page Reference String: ");
    for (int i = 0; i < totalPages; i++)
    {
        printf("%d ", pages[i]);
    }
    printf("\n\n");

    // Iterate through page references
    for (int i = 0; i < totalPages; i++)
    {
        int page = pages[i];
        int found = 0;

        printf("Page %d: ", page);

        // Check if the page is already in the frame
        for (int j = 0; j < frameCount; j++)
        {
            if (frames[j] == page)
            {
                found = 1;
                time[j] = ++currentTime; // Update usage time
                break;
            }
        }

        // If the page is not in the frame, replace it
        if (!found)
        {
            int replaceIndex;
            if (i < frameCount)
            {
                replaceIndex = i; // Use the next empty slot for initial pages
            }
            else
            {
                replaceIndex = findLRU(time, frameCount); // Find the LRU page
            }

            frames[replaceIndex] = page;
            time[replaceIndex] = ++currentTime;
            pageFaults++;
        }

        // Print the current state of frames
        for (int j = 0; j < frameCount; j++)
        {
            if (frames[j] == -1)
            {
                printf(" - ");
            }
            else
            {
                printf("%d ", frames[j]);
            }
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
}

// Main function
int main()
{
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int totalPages = sizeof(pages) / sizeof(pages[0]);
    int frameCount = 3;

    printf("LRU Page Replacement Algorithm\n");
    lruPageReplacement(pages, totalPages, frameCount);

    return 0;
}
