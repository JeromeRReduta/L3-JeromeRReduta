/**
 * 
 * Copied and pasted from Schedule page
 * 
 * fork.c
 *
 * Demonstrates using the fork() system call.
 *
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    pid_t my_pid = getpid();
    printf("Starting up, my PID is %d\n", my_pid);

    /* Creates a child process, which runs the if (child == 0) else block by itself */
    pid_t child = fork();
    if (child == 0) {
        /* I am the child */
        pid_t my_pid = getpid();
        printf("Hello from the child! PID = %d. Going to sleep.\n", my_pid);
        execl("/bin/ls", "ls", "-l", (char *) 0);
        printf("hi\n"); /* Will this print? */ /* Nothing prints past execl, unless execl has an error */
        sleep(5);
    } else if (child == -1) {
        /* Something went wrong */
        perror("fork");
    } else {

        /* Parent now runs */
        /* I am the parent */
        pid_t my_pid = getpid();
        printf("Hello from the parent! PID = %d\n", my_pid);
        printf("PID %d waiting for its child (%d)!\n", my_pid, child);
        wait(&child);
        printf("Child finished executing. Parent exiting.\n");
    }

    return 0;
}