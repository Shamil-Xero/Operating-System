#include <stdio.h>

// Structure to represent a process
typedef struct {
    int id;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
} Process;

// Function to calculate waiting time for all processes
void calculateWaitingTime(Process processes[], int n) {
    processes[0].waitingTime = 0; // First process has no waiting time
    for (int i = 1; i < n; i++) {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
    }
}

// Function to calculate turnaround time for all processes
void calculateTurnaroundTime(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }
}

// Function to perform FCFS scheduling
void fcfsScheduling(Process processes[], int n) {
    calculateWaitingTime(processes, n); // Calculate waiting time for all processes
    calculateTurnaroundTime(processes, n); // Calculate turnaround time for all processes

    float totalWaitingTime = 0;
    float totalTurnaroundTime = 0;

    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrivalTime, processes[i].burstTime, processes[i].waitingTime, processes[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

// Main function
int main() {
    Process processes[] = {{1, 0, 6}, {2, 1, 8}, {3, 2, 7}, {4, 3, 3}, {5, 4, 4}};
    int n = sizeof(processes) / sizeof(processes[0]);

    printf("First-Come-First-Served (FCFS) Scheduling Algorithm\n");
    fcfsScheduling(processes, n);

    return 0;
}
