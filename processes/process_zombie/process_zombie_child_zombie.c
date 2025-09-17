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
        printf("Child (PID: %d) is created and will now exit.\n", getpid());
        
        exit(0);
    }
    else {
        printf("Parent (PID: %d) is sleeping, not waiting for child (PID: %d).\n", getpid(), pid);
        sleep(30);

        printf("Parent is done sleeping and will now exit.\n");
    }

    return 0;
}
