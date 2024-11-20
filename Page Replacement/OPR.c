#include <stdio.h>
#include <stdbool.h>

// Function to check if a page is already in the frame
bool isInFrame(int frames[], int frameCount, int page)
{
    for (int i = 0; i < frameCount; i++)
    {
        if (frames[i] == page)
        {
            return true;
        }
    }
    return false;
}

// Function to find the page to be replaced
int predict(int pages[], int frames[], int frameCount, int currentIndex, int totalPages)
{
    int farthest = currentIndex;
    int replaceIndex = -1;

    for (int i = 0; i < frameCount; i++)
    {
        int j;
        for (j = currentIndex + 1; j < totalPages; j++)
        {
            if (frames[i] == pages[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    replaceIndex = i;
                }
                break;
            }
        }
        // If the page is not found in the future, replace it
        if (j == totalPages)
        {
            return i;
        }
    }

    // If no page was found to replace, use the first frame
    return (replaceIndex == -1) ? 0 : replaceIndex;
}

// Main function to simulate Optimal Page Replacement
void optimalPageReplacement(int pages[], int totalPages, int frameCount)
{
    int frames[frameCount];
    int pageFaults = 0;

    for (int i = 0; i < frameCount; i++)
    {
        frames[i] = -1; // Initialize frames with -1 (empty)
    }

    for (int i = 0; i < totalPages; i++)
    {
        printf("\nPage %d: ", pages[i]);

        // Check if the page is already in the frame
        if (!isInFrame(frames, frameCount, pages[i]))
        {
            pageFaults++;

            // Find the index to replace if the frame is full
            if (i >= frameCount)
            {
                int replaceIndex = predict(pages, frames, frameCount, i, totalPages);
                frames[replaceIndex] = pages[i];
            }
            else
            {
                frames[i] = pages[i];
            }
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
    }

    printf("\n\nTotal Page Faults: %d\n", pageFaults);
}

// Driver function
int main()
{
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int totalPages = sizeof(pages) / sizeof(pages[0]);
    int frameCount = 3;

    printf("Optimal Page Replacement Algorithm\n");
    printf("Page Reference String: ");
    for (int i = 0; i < totalPages; i++)
    {
        printf("%d ", pages[i]);
    }
    printf("\n");

    optimalPageReplacement(pages, totalPages, frameCount);

    return 0;
}
