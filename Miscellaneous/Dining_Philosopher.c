#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2

typedef struct {
    int state;
    sem_t *left_fork;
    sem_t *right_fork;
} Philosopher;

Philosopher philosophers[NUM_PHILOSOPHERS];

void take_fork(Philosopher *philosopher) {
    sem_wait(philosopher->left_fork);
    sem_wait(philosopher->right_fork);
}

void put_fork(Philosopher *philosopher) {
    sem_post(philosopher->left_fork);
    sem_post(philosopher->right_fork);
}

void *philosopher(void *param) {
    Philosopher *philosopher = (Philosopher *)param;
    while (1) {
        // Think
        sleep(1);
        take_fork(philosopher);
        // Eat
        printf("Philosopher %ld is eating.\n", philosopher - philosophers);
        sleep(1);
        put_fork(philosopher);
    }
    return NULL;
}

int main() {
    sem_t forks[NUM_PHILOSOPHERS];
    pthread_t threads[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
        philosophers[i].state = THINKING;
        philosophers[i].left_fork = &forks[i];
        philosophers[i].right_fork = &forks[(i + 1) % NUM_PHILOSOPHERS];
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&threads[i], NULL, philosopher, &philosophers[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}
