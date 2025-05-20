// Why use a semaphore (roomEmpty) instead of just a mutex, even though the semaphore behaves similarly here?
// Semaphores are more general than mutexes
// A mutex is essentially a binary semaphore specifically designed for mutual exclusion between threads. But semaphores can have counts > 1, \
enabling them to represent more complex resource states (e.g., counting available slots in a buffer).

// In the Reader-Writer problem, semaphore usage gives more flexibility
// The roomEmpty semaphore here acts like a binary semaphore (mutex), but conceptually it’s signaling whether the room is empty or not.

// Writers wait until the room is empty to write (sem_wait on roomEmpty).

// Readers take the room if it’s empty (first reader sem_waits) and release it if they’re the last (last reader sem_post).

// This "empty/full" signaling is naturally expressed with semaphores.

// In real systems, semaphore implementations can offer fairness and priority controls
// Semaphores can be used in a way that prioritizes writers over readers or vice versa,
// depending on system needs. Mutexes generally don’t provide this built-in.

// Semaphores can be used across processes, mutexes are usually thread-specific
// If you want synchronization beyond threads (e.g., processes), semaphores are more flexible.
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t roomEmpty;   // Mutex to ensure room is empty for writers
pthread_mutex_t mutex;       // Protect readCount

int readCount = 0;

void* reader(void* arg) {
    pthread_mutex_lock(&mutex);
    readCount++;
    if (readCount == 1)
        pthread_mutex_lock(&roomEmpty); // First reader locks roomEmpty to block writers
    pthread_mutex_unlock(&mutex);

    // Reading...
    printf("Reader %ld is reading...\n", (long)arg);
    sleep(1);

    pthread_mutex_lock(&mutex);
    readCount--;
    if (readCount == 0)
        pthread_mutex_unlock(&roomEmpty); // Last reader unlocks roomEmpty to allow writers
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void* writer(void* arg) {
    pthread_mutex_lock(&roomEmpty);  // Writer needs exclusive access

    // Writing...
    printf("Writer %ld is writing...\n", (long)arg);
    sleep(1);

    pthread_mutex_unlock(&roomEmpty);
    return NULL;
}

int main() {
    pthread_t r1, r2, w1;

    pthread_mutex_init(&roomEmpty, NULL);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&r1, NULL, reader, (void*)1);
    pthread_create(&r2, NULL, reader, (void*)2);
    pthread_create(&w1, NULL, writer, (void*)1);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w1, NULL);

    pthread_mutex_destroy(&roomEmpty);
    pthread_mutex_destroy(&mutex);

    return 0;
}
