/*Write a C program which creates a child process to run a Linux/Unix command or any user-defined program. The parent process sets the signal handler for the death of the child signal and alarm signal. If a child process does not complete its execution in 5 seconds, the parent process kills the child process.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t child_pid;

void child_exit_handler(int sig) {
    printf("Child process has completed.\n");
}

void alarm_handler(int sig) {
    printf("Child process took too long. Killing it...\n");
    kill(child_pid, SIGKILL);
}

int main() {
    signal(SIGCHLD, child_exit_handler);  // Signal handler for child death
    signal(SIGALRM, alarm_handler);       // Signal handler for alarm

    child_pid = fork();

    if (child_pid == 0) {
        // Child process
        printf("Child process running...\n");
        execlp("sleep", "sleep", "10", NULL);  // Example: Run a long command
    } else {
        // Parent process
        printf("Parent process waiting for child to finish...\n");
        alarm(5);  // Set an alarm after 5 seconds
        wait(NULL);  // Wait for the child to finish
    }

    return 0;
}

/*Parent process waiting for child to finish...
Child process running...
Child process took too long. Killing it...
*/