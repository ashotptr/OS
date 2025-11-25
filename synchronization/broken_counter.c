#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

long long counter = 0;

pthread_mutex_t mutex;
pthread_spinlock_t spin;

int mode_none = 1;
int mode_mutex = 0;
int mode_spin = 0;

long long increments = 1000000;

void *worker(void *arg) {
    long long i;
    (void)arg;

    if (mode_none) {
        for (i = 0; i < increments; ++i) {
            counter++;
        }
    }
    else if (mode_mutex) {
        for (i = 0; i < increments; ++i) {
            pthread_mutex_lock(&mutex);
    
            counter++;
    
            pthread_mutex_unlock(&mutex);
        }
    }
    else if (mode_spin) {
        for (i = 0; i < increments; ++i) {
            pthread_spin_lock(&spin);
    
            counter++;
    
            pthread_spin_unlock(&spin);
        }
    }
    
    return NULL;
}

int main(int argc, char **argv) {
    int num_threads = 4;

    if (argc >= 2) {
        if (strcmp(argv[1], "none") == 0) {
            mode_none = 1;
            mode_mutex = 0;
            mode_spin = 0;
        }
        else if (strcmp(argv[1], "mutex") == 0) {
            mode_none = 0;
            mode_mutex = 1;
            mode_spin = 0;
        }
        else if (strcmp(argv[1], "spin") == 0) {
            mode_none = 0;
            mode_mutex = 0;
            mode_spin = 1;
        }
        else {
            fprintf(stderr, "Unknown mode '%s'. Use: none | mutex | spin\n", argv[1]);

            return 1;
        }
    }

    pthread_t *threads = malloc(sizeof(pthread_t) * num_threads);

    if (!threads) {
        perror("malloc");

        return 1;
    }

    if (mode_mutex) {
        if (pthread_mutex_init(&mutex, NULL) != 0) {
            perror("pthread_mutex_init");

            return 1;
        }
    }
    if (mode_spin) {
        if (pthread_spin_init(&spin, PTHREAD_PROCESS_PRIVATE) != 0) {
            perror("pthread_spin_init");

            return 1;
        }
    }

    counter = 0;

    for (int t = 0; t < num_threads; ++t) {
        if (pthread_create(&threads[t], NULL, worker, NULL) != 0) {
            perror("pthread_create");

            return 1;
        }
    }

    for (int t = 0; t < num_threads; ++t) {
        pthread_join(threads[t], NULL);
    }

    if (mode_mutex) {
        pthread_mutex_destroy(&mutex);
    }
    if (mode_spin) {
        pthread_spin_destroy(&spin);
    }

    long long expected = (long long)num_threads * increments;

    printf("Mode: %s\n", mode_none ? "none" : mode_mutex ? "mutex" : "spin");
    printf("Threads: %d, Increments per thread: %lld\n", num_threads, increments);
    printf("Expected: %lld\n", expected);
    printf("Actual:   %lld\n", counter);

    free(threads);
    
    return 0;
}
