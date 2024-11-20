#include <stdio.h>

// FIFO Page Replacement Function
void fifoPageReplacement(int pages[], int totalPages, int frameCount)
{
    int frames[frameCount];
    int pageFaults = 0, currentIndex = 0;

    // Initialize all frames to -1 (empty)
    for (int i = 0; i < frameCount; i++)
    {
        frames[i] = -1;
    }

    printf("Page Reference String: ");
    for (int i = 0; i < totalPages; i++)
    {
        printf("%d ", pages[i]);
    }
    printf("\n\n");

    // Iterate through each page reference
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
                break;
            }
        }

        // If the page is not in the frame, replace the oldest page
        if (!found)
        {
            frames[currentIndex] = page;
            currentIndex = (currentIndex + 1) % frameCount; // Circular indexing
            pageFaults++;
        }

        // Display the current state of frames
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

    printf("FIFO Page Replacement Algorithm\n");
    fifoPageReplacement(pages, totalPages, frameCount);

    return 0;
}
