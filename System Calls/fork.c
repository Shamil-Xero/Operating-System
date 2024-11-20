#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        // Fork failed
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        // Child process
        // sleep(1);
        printf("Hello from the Child process! PID = %d\n", getpid());
    }
    else
    {
        // Parent process
        printf("Hello from the Parent process! PID = %d, Child PID = %d\n", getpid(), pid);
    }

    return 0;
}
