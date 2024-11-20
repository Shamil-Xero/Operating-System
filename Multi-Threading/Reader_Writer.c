#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t rw_mutex;     // Semaphore for reader-writer access
sem_t mutex;        // Semaphore for reader count access
int read_count = 0; // Number of readers currently accessing the resource

void *reader(void *arg)
{
    int reader_id = *(int *)arg;
    free(arg);

    while (1)
    {
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1)
        {
            sem_wait(&rw_mutex); // First reader locks access for writers
        }
        sem_post(&mutex);

        // Reading section
        printf("Reader %d is reading.\n", reader_id);
        sleep(1); // Simulate reading time

        sem_wait(&mutex);
        read_count--;
        if (read_count == 0)
        {
            sem_post(&rw_mutex); // Last reader unlocks access for writers
        }
        sem_post(&mutex);

        sleep(1); // Simulate time between reads
    }
}

void *writer(void *arg)
{
    int writer_id = *(int *)arg;
    free(arg);

    while (1)
    {
        sem_wait(&rw_mutex); // Writer locks access

        // Writing section
        printf("Writer %d is writing.\n", writer_id);
        sleep(1); // Simulate writing time

        sem_post(&rw_mutex); // Writer unlocks access

        sleep(1); // Simulate time between writes
    }
}

int main()
{
    pthread_t r_threads[5], w_threads[2];
    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);

    // Create reader threads
    for (int i = 0; i < 5; i++)
    {
        int *arg = malloc(sizeof(*arg));
        *arg = i + 1;
        pthread_create(&r_threads[i], NULL, reader, arg);
    }

    // Create writer threads
    for (int i = 0; i < 2; i++)
    {
        int *arg = malloc(sizeof(*arg));
        *arg = i + 1;
        pthread_create(&w_threads[i], NULL, writer, arg);
    }

    // Join threads (this won't happen in an infinite loop)
    for (int i = 0; i < 5; i++)
    {
        pthread_join(r_threads[i], NULL);
    }
    for (int i = 0; i < 2; i++)
    {
        pthread_join(w_threads[i], NULL);
    }

    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);

    return 0;
}
