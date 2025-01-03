#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;
int in = 0;
int out = 0;

sem_t full;
sem_t empty;
sem_t mutex;

void *producer(void *arg)
{
    int item;
    for (item = 0; item < 10; item++)
    {
        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = item;
        printf("Produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;
        count++;

        sem_post(&mutex);
        sem_post(&full);
        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg)
{
    int item;
    for (item = 0; item < 10; item++)
    {
        sem_wait(&full);
        sem_wait(&mutex);

        item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        count--;

        sem_post(&mutex);
        sem_post(&empty);
        sleep(2);
    }
    return NULL;
}

int main()
{
    pthread_t producer_thread, consumer_thread;

    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&mutex, 0, 1);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&full);
    sem_destroy(&empty);
    sem_destroy(&mutex);

    return 0;
}