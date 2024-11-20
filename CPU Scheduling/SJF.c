#include <stdio.h>

// Structure to represent a process
typedef struct
{
    int id;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
} Process;

// Function to calculate waiting time for all processes
void calculateWaitingTime(Process processes[], int n)
{
    processes[0].waitingTime = 0; // First process has no waiting time
    for (int i = 1; i < n; i++)
    {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
    }
}

// Function to calculate turnaround time for all processes
void calculateTurnaroundTime(Process processes[], int n)
{
    for (int i = 0; i < n; i++)
    {
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }
}

// Function to sort processes based on burst time
void sortProcessesByBurstTime(Process processes[], int n)
{
    Process temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (processes[i].burstTime > processes[j].burstTime)
            {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

// Function to perform SJF scheduling
void sjfScheduling(Process processes[], int n)
{
    sortProcessesByBurstTime(processes, n); // Sort processes by burst time

    calculateWaitingTime(processes, n);    // Calculate waiting time for all processes
    calculateTurnaroundTime(processes, n); // Calculate turnaround time for all processes

    float totalWaitingTime = 0;
    float totalTurnaroundTime = 0;

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].burstTime, processes[i].waitingTime, processes[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

// Main function
int main()
{
    Process processes[] = {{1, 6}, {2, 8}, {3, 7}, {4, 3}, {5, 4}};
    int n = sizeof(processes) / sizeof(processes[0]);

    printf("Shortest Job First (SJF) Scheduling Algorithm\n");
    sjfScheduling(processes, n);

    return 0;
}
