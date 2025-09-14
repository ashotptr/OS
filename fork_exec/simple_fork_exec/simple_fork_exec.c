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
        printf("Child process is running the 'ls' command...\n");
        printf("--------------------------------------------------\n");

        execl("/bin/ls", "ls", NULL);

        perror("execl failed");
        exit(1);
    }
    else {
        wait(NULL);

        printf("--------------------------------------------------\n");
        printf("Parent process: Child has finished.\n");
    }

    return 0;
}
