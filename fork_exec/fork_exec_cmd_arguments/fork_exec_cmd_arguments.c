#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) {
        printf("Child (PID: %d) is running 'grep main test.txt'...\n", getpid());
        printf("--------------------------------------------------\n");

        execl("/usr/bin/grep", "grep", "-n", "main", "test.txt", NULL);

        perror("execl for grep failed");
        exit(1);
    }
    else {
        wait(NULL);

        printf("--------------------------------------------------\n");
        printf("Parent process completed.\n");
    }

    return 0;
}

