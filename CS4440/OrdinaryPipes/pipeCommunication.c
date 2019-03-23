#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void)
{
    char write_msg[BUFFER_SIZE] = "Greetings Child\n";
    char read_msg[BUFFER_SIZE];
    int fd[2];
    pid_t pid;

    // Create the pipe
    if (pipe(fd) == -1)
    {
        fprintf(stderr, "Failed to create Pipe.");
        return 1;
    }

    // Create a fork for child process
    pid = fork();
    // error handling
    if (pid < 0)
    {
        fprintf(stderr, "Fork failed.");
        return 1;
    }
    // Parent process
    if (pid > 0)
    {
        // Closed unused end of the pipe
        close(fd[READ_END]);
        // Write to the pipe
        write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);
        // Close the write end of the pipe
        close(fd[WRITE_END]);
    }
    else {
        // Child Process starts
        close(fd[WRITE_END]);
        read(fd[READ_END], read_msg, BUFFER_SIZE);
        printf("Child read from Parent: %s", read_msg);
        close(fd[READ_END]);    
    }

    return 0;
}