#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* thread_function(void* arg) {
    int thread_num = *(int*)arg;
    pthread_t id = pthread_self();

    for (int i = 1; i <= 5; i++) {
        printf("Thread %d (ID: %lu) printing: %d\n", thread_num, (unsigned long)id, i);
    }

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
    }

    printf("Main thread: All threads have completed.\n");
    return 0;
}
