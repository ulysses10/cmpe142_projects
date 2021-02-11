#include "globals.h"

void parent(int fd[])
{
    char buffer[BUFFER_SIZE];

    printf("Parent started.\n");

    // Close the unused READ end of the pipe.
    close(fd[READ_END]);

    for (;;)
    {
        if (fgets(buffer, sizeof(buffer), stdin) <= 0) break;

        // Remove the '\n' at the end.
        buffer[strlen(buffer) - 1] = '\0';

        // Write to the WRITE end of the pipe.
        write(fd[WRITE_END], buffer, strlen(buffer));
    }

    // Close the WRITE end of the pipe.
    close(fd[WRITE_END]);

    printf("Parent done.\n");
}
