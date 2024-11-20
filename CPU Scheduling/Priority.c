#include <stdio.h>

// Structure to represent a process
typedef struct {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
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

// Function to sort processes based on priority (ascending order)
void sortProcessesByPriority(Process processes[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].priority > processes[j].priority) {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

// Function to perform Priority scheduling
void priorityScheduling(Process processes[], int n) {
    sortProcessesByPriority(processes, n); // Sort processes by priority

    calculateWaitingTime(processes, n); // Calculate waiting time for all processes
    calculateTurnaroundTime(processes, n); // Calculate turnaround time for all processes

    float totalWaitingTime = 0;
    float totalTurnaroundTime = 0;

    printf("Process\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrivalTime, processes[i].burstTime, processes[i].priority, processes[i].waitingTime, processes[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

// Main function
int main() {
    Process processes[] = {
        {1, 0, 6, 2},  // Process 1: Arrival=0, Burst=6, Priority=2
        {2, 1, 8, 1},  // Process 2: Arrival=1, Burst=8, Priority=1
        {3, 2, 7, 3},  // Process 3: Arrival=2, Burst=7, Priority=3
        {4, 3, 3, 4},  // Process 4: Arrival=3, Burst=3, Priority=4
        {5, 4, 4, 2}   // Process 5: Arrival=4, Burst=4, Priority=2
    };
    int n = sizeof(processes) / sizeof(processes[0]);

    printf("Priority Scheduling Algorithm\n");
    priorityScheduling(processes, n);

    return 0;
}
