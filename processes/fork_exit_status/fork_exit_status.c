#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid1, pid2;
    int status;

    printf("Parent process starting with PID: %d\n", getpid());

    pid1 = fork();
    if (pid1 < 0) {
        perror("fork 1 failed");
        exit(1);
    }

    if (pid1 == 0) {
        printf("Child 1 (PID: %d) is running.\n", getpid());
        sleep(1);
        printf("Child 1 exiting with status 15.\n");
        exit(15);
    }

    pid2 = fork();
    if (pid2 < 0) {
        perror("fork 2 failed");
        exit(1);
    }

    if (pid2 == 0) {
        printf("Child 2 (PID: %d) is running.\n", getpid());
        sleep(2);
        printf("Child 2 exiting with status 25.\n");
        exit(25);
    }

    pid_t pid_arr[2] = {pid1, pid2};

    printf("Parent is now waiting for its children...\n\n");

    for (int i = 0; i < 2; i++) {
        pid_t terminated_pid = waitpid(pid_arr[i], &status, 0);

        if (terminated_pid < 0) {
            perror("waitpid failed");
            exit(1);
        }

        if (WIFEXITED(status)) {
            printf("Child with PID %d.\n", terminated_pid);
            printf("Exit code: %d\n\n", WEXITSTATUS(status));
        } 
        else {
            printf("Child with PID %d.\n", terminated_pid);
            printf("Exit code: %d\n\n", WEXITSTATUS(status));
            printf("Child exited with an error.\n\n");
        }
    }

    printf("Parent will now exit.\n");

    return 0;
}

