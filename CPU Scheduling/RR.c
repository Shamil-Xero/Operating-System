#include <stdio.h>

#define MAX 10

// Structure to represent a process
typedef struct {
    int id;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
} Process;

// Function to calculate waiting time for all processes
void calculateWaitingTime(Process processes[], int n) {
    int totalTime = 0;
    processes[0].waitingTime = 0; // First process has no waiting time

    for (int i = 1; i < n; i++) {
        processes[i].waitingTime = totalTime;
        totalTime += processes[i - 1].burstTime;
    }
}

// Function to calculate turnaround time for all processes
void calculateTurnaroundTime(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }
}

// Function to perform Round Robin scheduling
void roundRobinScheduling(Process processes[], int n, int timeQuantum) {
    int completed = 0;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    int time = 0; // Time counter

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remainingTime > 0) {
                if (processes[i].remainingTime > timeQuantum) {
                    // Process will run for the time quantum
                    time += timeQuantum;
                    processes[i].remainingTime -= timeQuantum;
                } else {
                    // Process will finish execution
                    time += processes[i].remainingTime;
                    processes[i].waitingTime = time - processes[i].burstTime;
                    processes[i].remainingTime = 0;
                    completed++;
                }
            }
        }
    }

    // Calculate turnaround time
    calculateTurnaroundTime(processes, n);

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].burstTime, processes[i].waitingTime, processes[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);
}

// Main function
int main() {
    Process processes[] = {
        {1, 6, 6, 0, 0}, // Process 1: Burst Time=6
        {2, 8, 8, 0, 0}, // Process 2: Burst Time=8
        {3, 7, 7, 0, 0}, // Process 3: Burst Time=7
        {4, 3, 3, 0, 0}, // Process 4: Burst Time=3
        {5, 4, 4, 0, 0}  // Process 5: Burst Time=4
    };
    int n = sizeof(processes) / sizeof(processes[0]);
    int timeQuantum = 4;  // Time quantum for Round Robin scheduling

    printf("Round Robin Scheduling Algorithm\n");
    roundRobinScheduling(processes, n, timeQuantum);

    return 0;
}
