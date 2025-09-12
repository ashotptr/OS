#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    printf("Starting Program -> PID: %d\n", getpid());
    printf("----------------------------------\n");

    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("fork 1 failed");
        exit(1);
    }

    if (pid1 == 0) {
        printf("Fork 1 Child -> My PID is %d, my parent is %d\n", getpid(), getppid());
    } else {
        printf("Fork 1 Parent -> My PID is %d, I created child %d\n", getpid(), pid1);
    }

    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("fork 2 failed");
        exit(1);
    }

    if (pid2 == 0) {
        printf("Fork 2 Child -> My PID is %d, my parent is %d\n", getpid(), getppid());
    } else {
        printf("Fork 2 Parent -> My PID is %d, I created child %d\n", getpid(), pid2);
    }

    pid_t pid3 = fork();
    if (pid3 < 0) {
        perror("fork 3 failed");
        exit(1);
    }

    if (pid3 == 0) {
        printf("Fork 3 Child -> My PID is %d, my parent is %d\n", getpid(), getppid());
    } else {
        printf("Fork 3 Parent -> My PID is %d, I created child %d\n", getpid(), pid3);
    }

    wait(NULL);

    return 0;
}

