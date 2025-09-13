#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid1, pid2;

    printf("Parent starting...\n\n");

    pid1 = fork();

    if (pid1 < 0) {
        perror("fork 1 failed");
        exit(1);
    }

    if (pid1 == 0) {
        printf("Child 1 (PID: %d) is running 'ls -l'...\n", getpid());
        printf("----------------------------------------\n");
        execl("/bin/ls", "ls", "-l", NULL);

        perror("execl for ls failed");
        exit(1);
    } else {
        wait(NULL);
        printf("----------------------------------------\n");
        printf("Parent: Child 1 has finished.\n\n");
    }

    pid2 = fork();

    if (pid2 < 0) {
        perror("fork 2 failed");
        exit(1);
    }

    if (pid2 == 0) {
        printf("Child 2 (PID: %d) is running 'date'...\n", getpid());
        printf("----------------------------------------\n");
        execl("/bin/date", "date", NULL);

        perror("execl for date failed");
        exit(1);
    } else {
        wait(NULL);
        printf("----------------------------------------\n");
        printf("Parent: Child 2 has finished.\n\n");
    }

    printf("Parent process done.\n");

    return 0;
}
