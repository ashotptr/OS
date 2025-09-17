#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid = fork();
    int status1;

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) {
        printf("I am the child process, my PID is: %d\n", getpid());

        sleep(2);

        exit(4);
    }
    else {
        wait(&status1);

        printf("I am the parent process, my PID is: %d\n", getpid());
    }

    pid_t pid2 = fork();
    int status2;

    if (pid2 < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid2 == 0) {
        printf("I am the child process, my PID is: %d\n", getpid());

        sleep(2);

        exit(5);
    }
    else {
        waitpid(pid2, &status2, 0);

        printf("I am the parent process, my PID is: %d\n", getpid());
    }

    if (WIFEXITED(status1)) {
        printf("Exit status of first child was: %d\n", WEXITSTATUS(status1));
    }

    if (WIFEXITED(status2)) {
        printf("Exit status of second child was: %d\n", WEXITSTATUS(status2));
    }
    
    return 0;
}
