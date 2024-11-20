#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <pthread.h>

#define BUFFER_SIZE 3

// Shared memory structure
struct shmseg
{
    int buffer[BUFFER_SIZE];
    int in;
    int out;
};

// Semaphore operations
void sem_wait(int semid, int sem_num)
{
    struct sembuf sb = {sem_num, -1, 0}; // Decrement semaphore
    semop(semid, &sb, 1);
}

void sem_signal(int semid, int sem_num)
{
    struct sembuf sb = {sem_num, 1, 0}; // Increment semaphore
    semop(semid, &sb, 1);
}

int main()
{
    int shmid, semid;
    struct shmseg *shmptr;

    // Generate keys for shared memory and semaphores
    key_t shmkey = ftok("shmfile", 65);
    key_t semkey = ftok("semfile", 75);

    // Create shared memory segment
    shmid = shmget(shmkey, sizeof(struct shmseg), IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("Shared memory failed");
        exit(1);
    }

    // Attach the shared memory segment
    shmptr = (struct shmseg *)shmat(shmid, NULL, 0);
    if (shmptr == (void *)-1)
    {
        perror("Shared memory attach failed");
        exit(1);
    }

    // Initialize shared memory values
    shmptr->in = 0;
    shmptr->out = 0;

    // Create semaphores
    semid = semget(semkey, 2, IPC_CREAT | 0666);
    if (semid == -1)
    {
        perror("Semaphore creation failed");
        exit(1);
    }

    // Initialize semaphores: empty (BUFFER_SIZE slots), full (0 full slots)
    semctl(semid, 0, SETVAL, BUFFER_SIZE); // empty = BUFFER_SIZE
    semctl(semid, 1, SETVAL, 0);           // full = 0

    // Create the producer process
    if (fork() == 0)
    {
        // Producer process
        while (1)
        {
            int item = rand() % 100; // Produce a random item

            sem_wait(semid, 0); // Wait if buffer is full
            sem_wait(semid, 0); // Wait for mutual exclusion (critical section)

            // Add item to the buffer
            shmptr->buffer[shmptr->in] = item;
            printf("Producer produced item: %d at index %d\n", item, shmptr->in);

            shmptr->in = (shmptr->in + 1) % BUFFER_SIZE; // Update the 'in' index

            sem_signal(semid, 1); // Signal that the buffer has one more full slot
            sem_signal(semid, 0); // Release mutual exclusion (critical section)

            sleep(1); // Simulate time taken for producing
        }
        exit(0);
    }

    // Create the consumer process
    if (fork() == 0)
    {
        // Consumer process
        while (1)
        {
            sem_wait(semid, 1); // Wait if buffer is empty
            sem_wait(semid, 0); // Wait for mutual exclusion (critical section)

            // Consume item from the buffer
            int item = shmptr->buffer[shmptr->out];
            printf("Consumer consumed item: %d from index %d\n", item, shmptr->out);

            shmptr->out = (shmptr->out + 1) % BUFFER_SIZE; // Update the 'out' index

            sem_signal(semid, 0); // Signal that there is space in the buffer
            sem_signal(semid, 0); // Release mutual exclusion (critical section)

            sleep(2); // Simulate time taken for consuming
        }
        exit(0);
    }

    // Wait for processes to finish (in this case, they run indefinitely)
    wait(NULL);
    wait(NULL);

    // Detach and delete shared memory
    shmdt(shmptr);
    shmctl(shmid, IPC_RMID, NULL);

    // Remove semaphores
    semctl(semid, 0, IPC_RMID);

    return 0;
}
