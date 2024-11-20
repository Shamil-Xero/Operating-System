#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define SHARED_MEMORY_OBJECT_NAME "/shared_memory_object"
#define BUFFER_SIZE 100

int main()
{
    int fd;
    char *shared_memory_ptr;

    // Create a new shared memory object
    fd = shm_open(SHARED_MEMORY_OBJECT_NAME, O_CREAT | O_RDWR, 0666);
    if (fd == -1)
    {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Set the size of the shared memory object
    ftruncate(fd, BUFFER_SIZE);

    // Map the shared memory object into the address space of the current process
    shared_memory_ptr = mmap(NULL, BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shared_memory_ptr == MAP_FAILED)
    {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Process 1: Write data to the shared memory
    if (fork() == 0)
    {
        strcpy(shared_memory_ptr, "Hello, IPC using shared memory!");
        printf("Process 1 wrote: %s\n", shared_memory_ptr);
        exit(EXIT_SUCCESS);
    }

    // Process 2: Read data from the shared memory
    wait(NULL); // Wait for Process 1 to finish writing
    printf("Process 2 read: %s\n", shared_memory_ptr);

    // Unmap the shared memory object from the address space
    munmap(shared_memory_ptr, BUFFER_SIZE);

    // Close the shared memory object
    close(fd);

    // Remove the shared memory object
    shm_unlink(SHARED_MEMORY_OBJECT_NAME);

    return 0;
}