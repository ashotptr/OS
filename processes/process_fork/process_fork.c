#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) {
        printf("I am the child process, my PID is: %d\n", getpid());

        exit(0);
    }
    else {
        printf("I am the parent process, my PID is: %d\n", getpid());
    }

    return 0;
}
