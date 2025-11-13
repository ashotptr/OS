#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int data_array[] = {1, 10, 100, 2, 20, 200, 3, 30, 300, 4};

#define ARRAY_SIZE (sizeof(data_array) / sizeof(data_array[0]))

typedef struct {
    int* start_address;
    int count;
} ThreadArgs;

void* sum_thread_function(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;

    int* start = args->start_address;
    int count = args->count;

    long long partial_sum = 0;
    for (int i = 0; i < count; i++) {
        partial_sum += start[i];
    }
    
    pthread_t id = pthread_self();
    printf("Thread (ID: %lu) finished. Partial Sum: %lld\n", (unsigned long)id, partial_sum);
    
    return NULL;
}


int main() {
    pthread_t threads[2];
    ThreadArgs thread_args[2];
    
    int mid_point = ARRAY_SIZE / 2;

    printf("Main thread: Starting 2 worker threads...\n");
    printf("Main thread: Total array size is %d. Splitting at %d.\n", (int)ARRAY_SIZE, mid_point);

    thread_args[0].start_address = &data_array[0];
    thread_args[0].count = mid_point;

    thread_args[1].start_address = &data_array[mid_point];
    thread_args[1].count = ARRAY_SIZE - mid_point;

    if (pthread_create(&threads[0], NULL, sum_thread_function, &thread_args[0]) != 0) {
        perror("pthread_create (thread 1)");
        return EXIT_FAILURE;
    }
    if (pthread_create(&threads[1], NULL, sum_thread_function, &thread_args[1]) != 0) {
        perror("pthread_create (thread 2)");
        return EXIT_FAILURE;
    }

    printf("Main thread: Waiting for threads to join...\n");
    
    if (pthread_join(threads[0], NULL) != 0) {
        perror("pthread_join (thread 1)");
        return EXIT_FAILURE;
    }
    if (pthread_join(threads[1], NULL) != 0) {
        perror("pthread_join (thread 2)");
        return EXIT_FAILURE;
    }

    printf("Main thread: Both threads have completed.\n");
    return 0;
}
