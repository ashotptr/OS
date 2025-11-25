#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5

sem_t semA;
sem_t semB;
sem_t semC;

void* thread_A(void* arg) {
    for (int i = 0; i < N; ++i) {
        sem_wait(&semA);

        printf("A %d\n", i);

        sem_post(&semB);
    }

    return NULL;
}

void* thread_B(void* arg) {
    for (int i = 0; i < N; ++i) {
        sem_wait(&semB);

        printf("B %d\n", i);

        sem_post(&semC);
    }

    return NULL;
}

void* thread_C(void* arg) {
    for (int i = 0; i < N; ++i) {
        sem_wait(&semC);
        
        printf("C %d\n", i);
        
        sem_post(&semA);
    }

    return NULL;
}

int main() {
    pthread_t tA, tB, tC;

    if (sem_init(&semA, 0, 1) != 0) {
        perror("sem_init A");
    }
    if (sem_init(&semB, 0, 0) != 0) {
        perror("sem_init B");
    }
    if (sem_init(&semC, 0, 0) != 0) {
        perror("sem_init C");
    }

    if (pthread_create(&tA, NULL, thread_A, NULL) != 0) {
        perror("create A");
    }
    if (pthread_create(&tB, NULL, thread_B, NULL) != 0) {
        perror("create B");
    }
    if (pthread_create(&tC, NULL, thread_C, NULL) != 0) {
        perror("create C");
    }

    pthread_join(tA, NULL);
    pthread_join(tB, NULL);
    pthread_join(tC, NULL);

    sem_destroy(&semA);
    sem_destroy(&semB);
    sem_destroy(&semC);

    return 0;
}
