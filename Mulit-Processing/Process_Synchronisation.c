#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>

sem_t *sem;

int main()
{
    sem = sem_open("/sem_example", O_CREAT, 0666, 1); // Create or open a binary semaphore
    if (sem == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    if (fork() == 0)
    {                  // Child Process
        sem_wait(sem); // Enter critical section
        printf("Child id %d: In critical section\n", getpid());
        sleep(2); // Simulate work
        printf("Child: Leaving critical section\n");
        sem_post(sem); // Exit critical section
        exit(0);
    }
    else
    {                  // Parent Process
        sem_wait(sem); // Enter critical section
        printf("Parent id %d: In critical section\n", getpid());
        sleep(2); // Simulate work
        printf("Parent: Leaving critical section\n");
        sem_post(sem); // Exit critical section

        wait(NULL); // Wait for child process to finish
        sem_close(sem);
        sem_unlink("/sem_example"); // Clean up semaphore
    }

    return 0;
}
