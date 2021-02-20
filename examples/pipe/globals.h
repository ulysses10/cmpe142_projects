#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 256

// File descriptors.
enum { READ_END = 0, WRITE_END = 1 };

// Parent and child processes.
// fd is the array of file descriptors.
void parent(int fd[]);
void child(int fd[]);

#endif /* GLOBALS_H_ */
