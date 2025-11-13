#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <unistd.h>

void* thread_function(void* arg) {
    int* thread_num_ptr = (int*)arg;
    int thread_num = *thread_num_ptr;

    pthread_t p_id = pthread_self();
    pid_t tid = (pid_t) syscall(SYS_gettid);
    
    printf("Thread %d, Pthreads ID is %lu, Kernel TID is %d\n", thread_num, (unsigned long)p_id, tid);
    
    return NULL;
}

int main() {
    pthread_t threads[3];
    
    int thread_args[3] = {1, 2, 3};

    printf("Main thread: Starting 3 worker threads...\n");

    for (int i = 0; i < 3; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, &thread_args[i]) != 0) {
            perror("pthread_create");
            return EXIT_FAILURE;
        }
    }
    
    printf("Main thread: Waiting for threads to join...\n");
    for (int i = 0; i < 3; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            return EXIT_FAILURE;
        }
        printf("Main thread: Thread %d has joined.\n", i + 1);
    }

    printf("Main thread: All threads have completed. Exiting.\n");
    return 0;
}
