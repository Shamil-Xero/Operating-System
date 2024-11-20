#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define NUM_PHILOSOPHERS 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2

typedef struct {
    int state;
    HANDLE left_fork;
    HANDLE right_fork;
} Philosopher;

Philosopher philosophers[NUM_PHILOSOPHERS];

void take_fork(Philosopher *philosopher) {
    WaitForSingleObject(philosopher->left_fork, INFINITE);
    WaitForSingleObject(philosopher->right_fork, INFINITE);
}

void put_fork(Philosopher *philosopher) {
    ReleaseSemaphore(philosopher->left_fork, 1, NULL);
    ReleaseSemaphore(philosopher->right_fork, 1, NULL);
}

DWORD WINAPI philosopher(void *param) {
    Philosopher *philosopher = (Philosopher *)param;
    while (1) {
        // Think
        Sleep(1000);
        take_fork(philosopher);
        // Eat
        printf("Philosopher %d is eating.\n", philosopher - philosophers);
        Sleep(1000);
        put_fork(philosopher);
    }
    return 0;
}

int main() {
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosophers[i].state = THINKING;
        philosophers[i].left_fork = CreateSemaphore(NULL, 1, 1, NULL);
        philosophers[i].right_fork = CreateSemaphore(NULL, 1, 1, NULL);
    }

    HANDLE threads[NUM_PHILOSOPHERS];
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        threads[i] = CreateThread(NULL, 0, philosopher, &philosophers[i], 0, NULL);
    }

    WaitForMultipleObjects(NUM_PHILOSOPHERS, threads, TRUE, INFINITE);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        CloseHandle(philosophers[i].left_fork);
        CloseHandle(philosophers[i].right_fork);
    }

    return 0;
}
