#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *threadFunction(void *arg) {
    // int threadNum = *(int *)arg;
    pthread_t tid = pthread_self();
    printf("Hello from thread %lu\n", tid);
    sleep(1);
    return NULL;
}

int main() {
    pthread_t threads[5];
    // int threadArgs[5];

    for (int i = 0; i < 5; i++) {
        // threadArgs[i] = i;
        pthread_create(&threads[i], NULL, threadFunction, NULL);
    }

    // for (int i = 0; i < 5; i++) {
    //     pthread_join(threads[i], NULL);
    // }
    pthread_join(threads[0], NULL);

    return 0;
}

