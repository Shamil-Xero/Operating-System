#include <stdio.h>

#define MAX_PROCESSES 10

struct Process
{
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
};

void round_robin(struct Process processes[], int n, int quantum)
{
    int time = 0;
    int completed = 0;
    int i = 0;

    while (completed < n)
    {
        if (processes[i].remaining_time <= quantum && processes[i].remaining_time > 0)
        {
            time += processes[i].remaining_time;
            processes[i].remaining_time = 0;
            completed++;
            printf("Process %d completed at time %d\n", processes[i].id, time);
        }
        else if (processes[i].remaining_time > quantum)
        {
            time += quantum;
            processes[i].remaining_time -= quantum;
            printf("Process %d executed for %d units of time, remaining time: %d\n", processes[i].id, quantum, processes[i].remaining_time);
        }

        i = (i + 1) % n;
    }
}

int main()
{
    struct Process processes[MAX_PROCESSES] = {
        {1, 0, 10, 1, 10},
        {2, 2, 4, 2, 4},
        {3, 3, 9, 3, 9},
        {4, 4, 3, 1, 3}};

    int n = sizeof(processes) / sizeof(processes[0]);
    int quantum = 2;

    printf("Round Robin Scheduling\n");
    round_robin(processes, n, quantum);

    return 0;
}