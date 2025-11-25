#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PRINTERS 3
#define NUM_JOBS 10

sem_t printers;

int active_printers = 0;
pthread_mutex_t count_mutex;

void* print_job(void* arg) {
    long id = (long)arg;

    printf("Job %ld\n", id);

    sem_wait(&printers);
    
    pthread_mutex_lock(&count_mutex);

    active_printers++;

    printf("[Printer] Job %ld is printing. (Active printers: %d)\n", id, active_printers);
    
    if (active_printers > NUM_PRINTERS) {
        fprintf(stderr, "Too many active printers! (%d)\n", active_printers);
    }

    pthread_mutex_unlock(&count_mutex);

    usleep(2000);

    pthread_mutex_lock(&count_mutex);
    
    active_printers--;
    
    printf("[Done] Job %ld finished. (Active printers: %d)\n", id, active_printers);
    
    pthread_mutex_unlock(&count_mutex);
    
    sem_post(&printers);

    return NULL;
}

int main() {
    pthread_t threads[NUM_JOBS];

    if (sem_init(&printers, 0, NUM_PRINTERS) != 0) {
        perror("sem_init");
        
        return 1;
    }
    
    pthread_mutex_init(&count_mutex, NULL);

    printf("--- (Printers: %d, Jobs: %d) ---\n", NUM_PRINTERS, NUM_JOBS);

    for (long i = 0; i < NUM_JOBS; ++i) {
        if (pthread_create(&threads[i], NULL, print_job, (void*)i) != 0) {
            perror("pthread_create");

            return 1;
        }
    }
    
    for (int i = 0; i < NUM_JOBS; ++i) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&printers);

    pthread_mutex_destroy(&count_mutex);

    return 0;
}
