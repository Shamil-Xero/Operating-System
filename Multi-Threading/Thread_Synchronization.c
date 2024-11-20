#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5
#define NUM_ITERATIONS 2

int counter = 0;
pthread_mutex_t mutex;

void *incrementCounter(void *arg)
{
    pthread_t tid = pthread_self(); // Get the thread ID

    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        pthread_mutex_lock(&mutex); // Lock the mutex
        counter++;
        printf("\nThread ID: %lu, Counter: %d", tid, counter);
        sleep(1);
        pthread_mutex_unlock(&mutex); // Unlock the mutex
    }
    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, incrementCounter, NULL);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    // Print the final counter value
    printf("\nFinal counter value: %d\n", counter);

    return 0;
}
