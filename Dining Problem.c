#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5  // Number of philosophers

sem_t mutex;
sem_t S[N];

void* philosopher(void* num);
void take_fork(int);
void put_fork(int);
void test(int);

enum { THINKING, HUNGRY, EATING } state[N];
int phil[N] = {0, 1, 2, 3, 4}; // Philosopher numbers

void* philosopher(void* num) {
    while (1) {
        int* i = num;
        sleep(1);  // Thinking
        take_fork(*i);
        sleep(0);  // Eating
        put_fork(*i);
    }
}

void take_fork(int ph_num) {
    sem_wait(&mutex);
    state[ph_num] = HUNGRY;
    printf("Philosopher %d is HUNGRY\n", ph_num + 1);
    test(ph_num);
    sem_post(&mutex);
    sem_wait(&S[ph_num]);
    sleep(1);
}

void put_fork(int ph_num) {
    sem_wait(&mutex);
    state[ph_num] = THINKING;
    printf("Philosopher %d is THINKING\n", ph_num + 1);
    test((ph_num + 4) % N);
    test((ph_num + 1) % N);
    sem_post(&mutex);
}

void test(int ph_num) {
    if (state[ph_num] == HUNGRY && state[(ph_num + 4) % N] != EATING && state[(ph_num + 1) % N] != EATING) {
        state[ph_num] = EATING;
        printf("Philosopher %d takes fork %d and %d\n", ph_num + 1, (ph_num + 4) % N + 1, ph_num + 1);
        printf("Philosopher %d is EATING\n", ph_num + 1);
        sem_post(&S[ph_num]);
    }
}

int main() {
    int i;
    pthread_t thread_id[N];
    
    sem_init(&mutex, 0, 1);
    
    for (i = 0; i < N; i++)
        sem_init(&S[i], 0, 0);
    
    for (i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
        printf("Philosopher %d is THINKING\n", i + 1);
    }
    
    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);
}
