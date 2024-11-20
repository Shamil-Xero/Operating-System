#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void processFunction(int processNum) {
    printf("Hello from process %d\n", getpid());
    sleep(1);
}

int main() {
    pid_t pid;
    for (int i = 0; i < 5; i++) {
        pid = fork();
        if (pid == 0) {
            processFunction(i);
            exit(0);
        }
    }

    for (int i = 0; i < 5; i++) {
        wait(NULL);
    }

    return 0;
}

