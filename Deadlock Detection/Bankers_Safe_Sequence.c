#include <stdio.h>
#include <stdbool.h>

#define P 5 // Number of processes
#define R 3 // Number of resources

// Function to calculate Need matrix
void calculateNeed(int need[P][R], int max[P][R], int allocation[P][R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to check if a request can be safely granted
bool isSafe(int avail[], int max[][R], int allocation[][R]) {
    int need[P][R];
    calculateNeed(need, max, allocation);  // Calculate Need matrix

    bool finish[P] = {0};  // To keep track of completed processes
    int safeSeq[P];        // Safe sequence of processes
    int work[R];           // Temporary work array to store available resources
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];  // Initialize work array
    }

    int count = 0;  // To count the number of completed processes

    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            // If the process is not finished and its need can be satisfied
            if (!finish[p]) {
                bool canAllocate = true;
                for (int r = 0; r < R; r++) {
                    if (need[p][r] > work[r]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    // Add allocated resources to work
                    for (int r = 0; r < R; r++) {
                        work[r] += allocation[p][r];
                    }
                    safeSeq[count++] = p;  // Add process to safe sequence
                    finish[p] = 1;         // Mark process as finished
                    found = true;
                    break;
                }
            }
        }

        // If no process can be allocated resources, the system is in an unsafe state
        if (!found) {
            return false;  // The system is in an unsafe state
        }
    }

    // Print the safe sequence if needed
    printf("Safe Sequence: ");
    for (int i = 0; i < P; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");

    return true;  // The system is in a safe state
}

// Function to request resources for a process
bool requestResources(int process, int request[], int avail[], int max[][R], int allocation[][R]) {
    // Check if the request is less than or equal to the need
    for (int i = 0; i < R; i++) {
        if (request[i] > max[process][i] || request[i] > avail[i]) {
            printf("Request exceeds maximum claim or available resources\n");
            return false;
        }
    }

    // Temporarily allocate resources
    for (int i = 0; i < R; i++) {
        avail[i] -= request[i];
        allocation[process][i] += request[i];
    }

    // Check if the system is still in a safe state
    if (isSafe(avail, max, allocation)) {
        return true;
    } else {
        // Rollback the allocation if the state is unsafe
        for (int i = 0; i < R; i++) {
            avail[i] += request[i];
            allocation[process][i] -= request[i];
        }
        printf("Request cannot be granted due to unsafe state\n");
        return false;
    }
}

int main() {
    // Available resources
    int avail[] = {3, 3, 2}; // Example: 3 instances of resource 1, 3 of resource 2, and 2 of resource 3

    // Maximum resources that can be requested by processes
    int max[][R] = {
        {7, 5, 3}, // Max for P0
        {3, 2, 2}, // Max for P1
        {9, 0, 2}, // Max for P2
        {2, 2, 2}, // Max for P3
        {4, 3, 3}  // Max for P4
    };

    // Resources currently allocated to processes
    int allocation[][R] = {
        {0, 1, 0}, // Allocation for P0
        {2, 0, 0}, // Allocation for P1
        {3, 0, 2}, // Allocation for P2
        {2, 1, 1}, // Allocation for P3
        {0, 0, 2}  // Allocation for P4
    };

    // Request for process P1
    int request[] = {1, 0, 2};  // Example: Process P1 requests 1 unit of resource 1, 0 units of resource 2, and 2 units of resource 3.

    // Check if the request can be safely granted
    if (requestResources(1, request, avail, max, allocation)) {
        printf("Request granted\n");
    } else {
        printf("Request denied\n");
    }

    return 0;
}
