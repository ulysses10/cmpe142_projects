#include "globals.h"

void child(int fd[])
{
    char buffer[BUFFER_SIZE];

    printf("Child started.\n");

    // Close the unused WRITE end of the pipe.
    close(fd[WRITE_END]);

    // Read from the READ end of the pipe.
    ssize_t size;
    for (;;)
    {
        size = read(fd[READ_END], buffer, BUFFER_SIZE);
        if (size <= 0) break;

        if (size < BUFFER_SIZE) buffer[size] = '\0';
        printf("Child: Read '%s' from the pipe.\n", buffer);
    }

    // Close the READ end of the pipe.
    close(fd[READ_END]);

    printf("Child done.\n");
}
