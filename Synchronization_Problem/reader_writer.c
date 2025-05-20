// 😬 The Real Problem (Race Condition Risk)
// The critical problem appears when the reader is scheduled right before the writer locks roomEmpty:

// Reader thread increments readCount and calls pthread_mutex_lock(&roomEmpty).

// Suppose the writer has not yet locked roomEmpty — the reader succeeds in locking it.

// Then the writer runs and locks roomEmpty — but oops, it shouldn't be allowed, because now the 
// writer and readers are in the critical section at the same time.

// This is because pthread_mutex_lock() has no mechanism for waiting based on priority or fairness — there's 
// no way to express the semantic “if the room is empty, I go in — otherwise I wait.” This semantic is 
// perfectly captured by a semaphore, but not a mutex.
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t roomEmpty;          // Semaphore to control writers and first/last reader
pthread_mutex_t mutex;    // Mutex to protect readCount
int readCount = 0;

void* reader(void* arg) {
    long id = (long)arg;

    // Entry section for reader
    pthread_mutex_lock(&mutex);
    readCount++;
    if (readCount == 1) {
        sem_wait(&roomEmpty);  // First reader locks the room
    }
    pthread_mutex_unlock(&mutex);

    // Critical section (reading)
    printf("Reader %ld is reading...\n", id);
    sleep(1);  // Simulate read time

    // Exit section for reader
    pthread_mutex_lock(&mutex);
    readCount--;
    if (readCount == 0) {
        sem_post(&roomEmpty);  // Last reader unlocks the room
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void* writer(void* arg) {
    long id = (long)arg;

    // Entry section for writer
    sem_wait(&roomEmpty);  // Wait until room is empty

    // Critical section (writing)
    printf("Writer %ld is writing...\n", id);
    sleep(1);  // Simulate write time

    // Exit section for writer
    sem_post(&roomEmpty);  // Release exclusive access

    return NULL;
}

int main() {
    pthread_t readers[5], writers[2];

    // Initialize synchronization primitives
    sem_init(&roomEmpty, 0, 1);            // Binary semaphore
    pthread_mutex_init(&mutex, NULL);      // For readCount

    // Create reader threads
    for (long i = 0; i < 5; i++) {
        pthread_create(&readers[i], NULL, reader, (void*)i);
    }

    // Create writer threads
    for (long i = 0; i < 2; i++) {
        pthread_create(&writers[i], NULL, writer, (void*)i);
    }

    // Wait for threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    // Clean up
    sem_destroy(&roomEmpty);
    pthread_mutex_destroy(&mutex);

    return 0;
}
