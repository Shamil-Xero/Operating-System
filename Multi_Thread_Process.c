#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *threadFunction(void *arg)
{
    int threadNum = *(int *)arg;
    int i;
    printf("Thread %d started\n", threadNum);
    sleep(1); // Simulate some work
    printf("Thread %d is executed\n", threadNum);

    return NULL;
}

int main()
{
    pthread_t threads[5];
    int threadArgs[5];
    int status;
    for (int i = 0; i < 5; i++)
    {
        threadArgs[i] = i;
        pthread_create(&threads[i], NULL, threadFunction, &threadArgs[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        status = pthread_join(threads[i], NULL);
        if (status != 0) {
            fprintf(stderr, "Error joining thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}
