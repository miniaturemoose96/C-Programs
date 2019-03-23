/* 
    Create a communication using Two pipes and the Parent & Child process 
    Here we define child as 0 and parent as 1
*/

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void)
{
    // Parent
    char parent_write_msg[BUFFER_SIZE] = "Hello Child.\n";
    char parent_read_msg[BUFFER_SIZE];
    // Child
    char child_write_msg[BUFFER_SIZE] = "Hello Parent.\n";
    char child_read_msg[BUFFER_SIZE];
    // Init pipe 
    int fd_parent[2];
    int fd_child[2];
    int parent_pipe, child_pipe;
    // Process ID
    pid_t pid;

    parent_pipe = pipe(fd_parent);

    // Create the parent pipe
    if (parent_pipe == -1)
    {
        fprintf(stderr, "Failed to create parent pipe.\n");
        return 1;
    }

    // Create child pipe
    child_pipe = pipe(fd_child);
    if (child_pipe == -1)
    {
        fprintf(stderr, "Failed to create child pipe.\n");
        return 1;
    }

    // Create the Fork
    pid = fork();
    // Error Handling for the Fork created 
    if (pid < 0)
    {
        fprintf(stderr, "Fork failed.\n");
        return 1;
    }

    // Parent process
    if (pid > 0)
    {
        // Closed unused end of the pipe
        close(fd_parent[READ_END]);
        close(fd_child[WRITE_END]);
        // Write to the pipe
        printf("Parent says: %s\n", parent_write_msg);
        write(fd_parent[WRITE_END], parent_write_msg, sizeof(parent_write_msg));
        // Read child's message
        read(fd_child[READ_END], parent_read_msg, sizeof(parent_read_msg));
        printf("Parent hears childs response: %s\n", parent_read_msg);

    }
    else {
        // Child Process starts
        close(fd_parent[WRITE_END]);
        close(fd_child[READ_END]);
        // Read Parent's Greeting
        read(fd_parent[READ_END], child_read_msg, sizeof(child_read_msg));
        printf("Child hears parents response: %s\n", child_read_msg);
        // Child write to parent
         printf("Child says: %s\n", child_write_msg);
        write(fd_child[WRITE_END], child_write_msg, sizeof(child_write_msg)); 
    }


    return 0;
}
