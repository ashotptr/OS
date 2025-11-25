#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 8
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
#define ITEMS_PER_PRODUCER 5
#define ITEMS_PER_CONSUMER ((NUM_PRODUCERS * ITEMS_PER_PRODUCER) / NUM_CONSUMERS)

int buffer[BUFFER_SIZE];
int in_pos = 0;
int out_pos = 0;

sem_t empty_slots;
sem_t full_slots;
pthread_mutex_t buffer_mutex;

void* producer(void* arg) {
    long id = (long)arg;

    for (int i = 0; i < ITEMS_PER_PRODUCER; ++i) {
        int item = (id * 100) + i;

        sem_wait(&empty_slots);

        pthread_mutex_lock(&buffer_mutex);

        buffer[in_pos] = item;

        printf("[Producer %ld] Inserted %d at index %d\n", id, item, in_pos);

        in_pos = (in_pos + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&buffer_mutex);

        sem_post(&full_slots);

        usleep(10000);
    }

    return NULL;
}

void* consumer(void* arg) {
    long id = (long)arg;

    for (int i = 0; i < ITEMS_PER_CONSUMER; ++i) {
        sem_wait(&full_slots);

        pthread_mutex_lock(&buffer_mutex);

        int item = buffer[out_pos];

        printf("[Consumer %ld] Removed %d from index %d\n", id, item, out_pos);

        out_pos = (out_pos + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&buffer_mutex);

        sem_post(&empty_slots);

        usleep(20000);
    }

    return NULL;
}

int main() {
    pthread_t prod_threads[NUM_PRODUCERS];
    pthread_t cons_threads[NUM_CONSUMERS];

    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&full_slots, 0, 0);

    pthread_mutex_init(&buffer_mutex, NULL);

    printf("Buffer Size: %d, Producers: %d, Consumers: %d\n", BUFFER_SIZE, NUM_PRODUCERS, NUM_CONSUMERS);

    for (long i = 0; i < NUM_PRODUCERS; ++i) {
        if (pthread_create(&prod_threads[i], NULL, producer, (void*)i) != 0) {
            perror("Failed to create producer");

            return 1;
        }
    }

    for (long i = 0; i < NUM_CONSUMERS; ++i) {
        if (pthread_create(&cons_threads[i], NULL, consumer, (void*)i) != 0) {
            perror("Failed to create consumer");

            return 1;
        }
    }

    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        pthread_join(prod_threads[i], NULL);
    }
    
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        pthread_join(cons_threads[i], NULL);
    }

    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);

    pthread_mutex_destroy(&buffer_mutex);

    return 0;
}
