#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

long long balance = 0;

pthread_mutex_t mutex;
pthread_spinlock_t spin;

int use_mutex = 1;
int use_spin = 0;
int long_cs = 0;

long long iters = 100000;

void timespec_diff(struct timespec *start, struct timespec *end, struct timespec *diff) {
    if ((end->tv_nsec - start->tv_nsec) < 0) {
        diff->tv_sec  = end->tv_sec - start->tv_sec - 1;
        diff->tv_nsec = end->tv_nsec - start->tv_nsec + 1000000000;
    }
    else {
        diff->tv_sec  = end->tv_sec - start->tv_sec;
        diff->tv_nsec = end->tv_nsec - start->tv_nsec;
    }
}

void *depositor(void *arg) {
    (void)arg;

    for (long long i = 0; i < iters; ++i) {
        if (use_mutex) {
            pthread_mutex_lock(&mutex);
    
            if (long_cs) {
                usleep(100);
            }
    
            balance++;
    
            pthread_mutex_unlock(&mutex);
        }
        else {
            pthread_spin_lock(&spin);
        
            if (long_cs) {
                usleep(100);
            }
        
            balance++;
        
            pthread_spin_unlock(&spin);
        }
    }
    
    return NULL;
}

void *withdrawer(void *arg) {
    (void)arg;
    
    for (long long i = 0; i < iters; ++i) {
        if (use_mutex) {
            pthread_mutex_lock(&mutex);
    
            if (long_cs) {
                usleep(100);
            }
    
            balance--;
    
            pthread_mutex_unlock(&mutex);
        }
        else {
            pthread_spin_lock(&spin);
            
            if (long_cs) {
                usleep(100);
            }

            balance--;
            
            pthread_spin_unlock(&spin);
        }
    }

    return NULL;
}

int main(int argc, char **argv) {
    int dep_threads = 4;
    int with_threads = 4;

    if (argc >= 2) {
        if (strcmp(argv[1], "mutex") == 0) { 
            use_mutex = 1;
            use_spin = 0;
        }
        else if (strcmp(argv[1], "spin") == 0) { 
            use_mutex = 0;
            use_spin = 1;
        }
        else {
            fprintf(stderr, "Unknown mode '%s'. Use: mutex | spin\n", argv[1]);
        
            return 1;
        }
    }

    if (argc >= 3) {
        if (strcmp(argv[2], "short") == 0) {
            long_cs = 0;
        }
        else if (strcmp(argv[2], "long") == 0) {
	    iters = 100;
            long_cs = 1;
        }
        else {
            fprintf(stderr, "Unknown cs_type '%s'. Use: short | long\n", argv[2]);
         
            return 1;
        }
    }

    if (use_mutex) {
        if (pthread_mutex_init(&mutex, NULL) != 0) {
            perror("pthread_mutex_init");
     
            return 1;
        }
    }
    else {
        if (pthread_spin_init(&spin, PTHREAD_PROCESS_PRIVATE) != 0) {
            perror("pthread_spin_init");
            
            return 1;
        }
    }

    balance = 0;

    pthread_t *deps = malloc(sizeof(pthread_t) * dep_threads);
    pthread_t *withs = malloc(sizeof(pthread_t) * with_threads);

    if (!deps || !withs) {
        perror("malloc");
    
        return 1;
    }

    struct timespec tstart, tend, tdiff;
    
    clock_gettime(CLOCK_MONOTONIC, &tstart);

    for (int i = 0; i < dep_threads; ++i) {
        if (pthread_create(&deps[i], NULL, depositor, NULL) != 0) {
            perror("pthread_create depositor");
    
            return 1;
        }
    }
    
    for (int i = 0; i < with_threads; ++i) {
        if (pthread_create(&withs[i], NULL, withdrawer, NULL) != 0) {
            perror("pthread_create withdrawer");
    
            return 1;
        }
    }

    for (int i = 0; i < dep_threads; ++i) {
        pthread_join(deps[i], NULL);
    }

    for (int i = 0; i < with_threads; ++i) {
        pthread_join(withs[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &tend);
    
    timespec_diff(&tstart, &tend, &tdiff);

    long long expected = 0;

    printf("Mode: %s\tCS: %s\n", use_mutex ? "mutex" : "spin", long_cs ? "long" : "short");
    printf("Deposit threads: %d, Withdraw threads: %d, Iterations/thread: %lld\n", dep_threads, with_threads, iters);
    printf("Expected final balance: %lld\n", expected);
    printf("Actual final balance:   %lld\n", balance);
    printf("Elapsed time: %lld.%03ld sec\n", (long long)tdiff.tv_sec, tdiff.tv_nsec / 1000000L);

    if (use_mutex) {
        pthread_mutex_destroy(&mutex);
    }
    else {
        pthread_spin_destroy(&spin);
    }

    free(deps);
    free(withs);
    
    return 0;
}
