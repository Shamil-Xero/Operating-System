#include <stdio.h>

#define MAX_BLOCKS 5
#define MAX_PROCESSES 4

// Function to implement Best Fit Allocation
void bestFit(int blockSize[], int m, int processSize[], int n) {
    // Array to store the allocation of blocks to processes
    int allocation[MAX_PROCESSES];

    // Initially, no block is assigned to any process
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Find best fit block for each process
    for (int i = 0; i < n; i++) {
        // Find the best fit block for the current process
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[bestIdx] > blockSize[j]) {
                    bestIdx = j;
                }
            }
        }

        // If a suitable block is found, allocate it
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];  // Reduce the block size
        }
    }

    // Display the results
    printf("\nProcess No.\tProcess Size\tBlock No.\tBlock Size\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, processSize[i], allocation[i] + 1, blockSize[allocation[i]]);
        } else {
            printf("%d\t\t%d\t\tNot Allocated\n", i + 1, processSize[i]);
        }
    }
}

int main() {
    // Predefined input values
    int blockSize[MAX_BLOCKS] = {100, 500, 200, 300, 600}; // Predefined block sizes
    int processSize[MAX_PROCESSES] = {212, 417, 112, 426}; // Predefined process sizes

    int m = 5; // Number of blocks
    int n = 4; // Number of processes

    // Call the Best Fit function
    bestFit(blockSize, m, processSize, n);

    return 0;
}
