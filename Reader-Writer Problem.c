#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

// Shared resource
int shared_data = 0;

// Semaphores and mutex
sem_t resource_access;  // Semaphore to control access to the resource
sem_t read_count_access; // Semaphore to control access to read_count
int read_count = 0;

void* reader(void* arg) {
    int reader_id = *((int*)arg);

    while (1) {
        // Entry section for readers
        sem_wait(&read_count_access);
        read_count++;
        if (read_count == 1) {
            sem_wait(&resource_access); // First reader locks the resource
        }
        sem_post(&read_count_access);

        // Critical section for readers
        printf("Reader %d: read shared data = %d\n", reader_id, shared_data);
        usleep(rand() % 1000);

        // Exit section for readers
        sem_wait(&read_count_access);
        read_count--;
        if (read_count == 0) {
            sem_post(&resource_access); // Last reader unlocks the resource
        }
        sem_post(&read_count_access);

        usleep(rand() % 1000); // Simulate reader doing something else
    }

    return NULL;
}

void* writer(void* arg) {
    int writer_id = *((int*)arg);

    while (1) {
        // Entry section for writers
        sem_wait(&resource_access);

        // Critical section for writers
        shared_data = rand() % 100;
        printf("Writer %d: wrote shared data = %d\n", writer_id, shared_data);
        usleep(rand() % 1000);

        // Exit section for writers
        sem_post(&resource_access);

        usleep(rand() % 1000); // Simulate writer doing something else
    }

    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    // Initialize semaphores
    sem_init(&resource_access, 0, 1);
    sem_init(&read_count_access, 0, 1);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        if (pthread_create(&readers[i], NULL, reader, &reader_ids[i]) != 0) {
            perror("Failed to create reader thread");
            exit(1);
        }
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        if (pthread_create(&writers[i], NULL, writer, &writer_ids[i]) != 0) {
            perror("Failed to create writer thread");
            exit(1);
        }
    }

    // Join threads (in this case, they will run indefinitely)
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&resource_access);
    sem_destroy(&read_count_access);

    return 0;
}
