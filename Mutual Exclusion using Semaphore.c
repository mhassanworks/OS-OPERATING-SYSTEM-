#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex;

void *threadFunction(void *arg) {
    int threadNum = *((int *)arg);

    // Entry Section
    sem_wait(&mutex); // Wait (P) operation

    // Critical Section
    printf("Thread %d is in the critical section.\n", threadNum);
    sleep(1); // Simulating critical section

    // Exit Section
    printf("Thread %d is leaving the critical section.\n", threadNum);
    sem_post(&mutex); // Signal (V) operation

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[5];
    int threadNums[5];

    // Initialize the semaphore to 1 (binary semaphore)
    sem_init(&mutex, 0, 1);

    // Create threads
    for (int i = 0; i < 5; i++) {
        threadNums[i] = i + 1;
        pthread_create(&threads[i], NULL, threadFunction, (void *)&threadNums[i]);
    }

    // Join threads
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the semaphore
    sem_destroy(&mutex);

    return 0;
}
