#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int data_array[] = {1, 2, 3, 4, 5, 6, 7, 8};
#define NUM_THREADS (sizeof(data_array) / sizeof(data_array[0]))

void* square_function(void* arg) {
    int* num_ptr = (int*)arg;
    int number = *num_ptr;
    int square = number * number;
    
    printf("Thread (for %d): Square of %d is %d\n", number, number, square);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    printf("Main thread: Starting %zu worker threads...\n", NUM_THREADS);
    
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, square_function, &data_array[i]) != 0) {
            perror("pthread_create");
            return 1;
        }
    }
    
    printf("Main thread: Waiting for all threads to join...\n");
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            return 1;
        }
    }

    printf("Main thread: All threads have completed.\n");
    return 0;
}
