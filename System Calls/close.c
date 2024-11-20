#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("foo.txt", O_WRONLY | O_CREAT, 0644);
    if (fd < 0)
    {
        perror("Failed to open file");
        return 1;
    }

    printf("File opened with descriptor: %d\n", fd);

    if (close(fd) == 0)
    {
        printf("File descriptor closed successfully.\n");
    }
    else
    {
        perror("Failed to close file descriptor");
    }

    return 0;
}
