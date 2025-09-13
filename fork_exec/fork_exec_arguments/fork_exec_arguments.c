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
        printf("Child process executing 'echo'...\n");
        printf("----------------------------------\n");

        execl("/bin/echo", "echo", "Hello from the child process", NULL);

        perror("execl failed");
        exit(1);
    }
    else {
        wait(NULL);

        printf("----------------------------------\n");
        printf("Parent process done.\n");
    }

    return 0;
}
