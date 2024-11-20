#include <stdio.h>
#include <unistd.h>

int main()
{
    char *args[] = {"date", NULL}; // Argument array
    // char *args[] = {"ls", "-l", NULL}; // Argument array

    printf("Before execvp()\n");

    // Replace current process with "ls" program
    execvp("date", args);

    printf("After execvp()\n");

    // If exec() fails
    perror("execvp failed");
    return 1;
}
