#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int available;
} Monitor;

Monitor monitor;

void monitorInit(Monitor *m) {
    pthread_mutex_init(&m->mutex, NULL);
    pthread_cond_init(&m->cond, NULL);
    m->available = 1;
}

void monitorEnter(Monitor *m) {
    pthread_mutex_lock(&m->mutex);
    while (m->available == 0) {
        pthread_cond_wait(&m->cond, &m->mutex);
    }
    m->available = 0;
    pthread_mutex_unlock(&m->mutex);
}

void monitorExit(Monitor *m) {
    pthread_mutex_lock(&m->mutex);
    m->available = 1;
    pthread_cond_signal(&m->cond);
    pthread_mutex_unlock(&m->mutex);
}

void *threadFunction(void *arg) {
    int threadNum = *((int *)arg);

    // Entry Section
    monitorEnter(&monitor);

    // Critical Section
    printf("Thread %d is in the critical section.\n", threadNum);
    sleep(1); // Simulating critical section

    // Exit Section
    printf("Thread %d is leaving the critical section.\n", threadNum);
    monitorExit(&monitor);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[5];
    int threadNums[5];

    // Initialize the monitor
    monitorInit(&monitor);

    // Create threads
    for (int i = 0; i < 5; i++) {
        threadNums[i] = i + 1;
        pthread_create(&threads[i], NULL, threadFunction, (void *)&threadNums[i]);
    }

    // Join threads
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the monitor (mutex and condition variable)
    pthread_mutex_destroy(&monitor.mutex);
    pthread_cond_destroy(&monitor.cond);

    return 0;
}
