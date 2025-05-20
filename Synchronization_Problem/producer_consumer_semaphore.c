#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0;    // Next empty position for producer
int out = 0;   // Next filled position for consumer

sem_t empty;   // Count of empty slots
sem_t full;    // Count of full slots
pthread_mutex_t mutex;  // Mutex for buffer access

void* producer(void* arg) {
    int item = 1;  // Just a sample item to produce
    sem_wait(&empty);               // Wait for empty slot
    pthread_mutex_lock(&mutex);     // Lock the buffer

    buffer[in] = item;
    printf("Producer produced item %d at index %d\n", item, in);
    in = (in + 1) % BUFFER_SIZE;

    pthread_mutex_unlock(&mutex);   // Unlock the buffer
    sem_post(&full);                // Signal there's a new full slot

    return NULL;
}

void* consumer(void* arg) {
    sem_wait(&full);                // Wait for full slot
    pthread_mutex_lock(&mutex);    // Lock the buffer

    int item = buffer[out];
    printf("Consumer consumed item %d from index %d\n", item, out);
    out = (out + 1) % BUFFER_SIZE;

    pthread_mutex_unlock(&mutex);  // Unlock the buffer
    sem_post(&empty);              // Signal there's an empty slot now

    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    sem_init(&empty, 0, BUFFER_SIZE);  // Initially all slots empty
    sem_init(&full, 0, 0);             // Initially no full slots
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
// | Semaphore | Purpose                                               | Initial Value    | Modified By                      |
// | --------- | ----------------------------------------------------- | ---------------- | -------------------------------- |
// | `empty`   | Tracks number of **empty** slots in the buffer        | BUFFER\_SIZE (5) | Producer waits, Consumer signals |
// | `full`    | Tracks number of **full** slots (items) in the buffer | 0                | Consumer waits, Producer signals |
//What if you use only one semaphore + a count variable?
//race condition Without proper synchronization, simultaneous access to this count variable by producer and consumer will cause race conditions.
//  You’d need a mutex anyway to protect that count
// No built-in way to block producer when buffer is full:
