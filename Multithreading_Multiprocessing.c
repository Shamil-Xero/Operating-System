#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void *threadFunction(void *arg) {
    int threadNum = *(int *)arg;
    printf("Thread %d is executing\n", threadNum);
    sleep(1);
    return NULL;
}

void processFunction(int processNum) {
    printf("Process %d is executing\n", processNum);

    pthread_t threads[5];
    int threadArgs[5];
    for (int i = 0; i < 5; i++) {
        threadArgs[i] = i + (processNum * 2);
        pthread_create(&threads[i], NULL, threadFunction, &threadArgs[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    exit(0);
}

int main() {
    pid_t pid;
    for (int i = 0; i < 3; i++) {
        pid = fork();
        if (pid == 0) {
            processFunction(i);
        }
    }

    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    return 0;
}
