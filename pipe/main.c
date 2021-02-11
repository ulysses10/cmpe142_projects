#include "globals.h"

int main(void)
{
    int fd[2];  // file descriptors for the pipe

    // Create the pipe.
    pid_t pipe_id = pipe(fd);
    if (pipe_id < 0)
    {
        fprintf(stderr,"pipe() failed");
        return pipe_id;
    }

    // Fork a child process.
    pid_t pid = fork();
    if (pid > 0)       parent(fd);
    else if (pid == 0) child(fd);
    else
    {
        fprintf(stderr, "fork() failed");
        return pid;
    }

    return 0;
}
