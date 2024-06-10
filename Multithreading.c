#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function to be executed by each thread
void *threadFunction(void *arg) {
    int threadID = *((int *)arg);
    printf("Thread %d: Hello, World!\n", threadID);
    pthread_exit(NULL);
}

int main() {
    int numThreads = 5;
    pthread_t threads[numThreads];
    int threadIDs[numThreads];
    int rc;

    for(int i = 0; i < numThreads; i++) {
        threadIDs[i] = i;
        printf("Main: Creating thread %d\n", i);
        rc = pthread_create(&threads[i], NULL, threadFunction, (void *)&threadIDs[i]);
        if (rc) {
            printf("Error: Unable to create thread %d, %d\n", i, rc);
            exit(-1);
        }
    }

    // Wait for all threads to complete
    for(int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Main: Program exiting.\n");
    return 0;
}
