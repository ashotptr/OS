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
        printf("Child (PID: %d) is created and will now exit.\n", getpid());

        exit(0);
    }
    else {
        printf("Parent (PID: %d) is waiting for child (PID: %d) to finish.\n", getpid(), pid);
        
        wait(NULL);

        printf("No zombie was created.\n");

	sleep(10);
    }

    printf("Parent process end.");

    return 0;
}
