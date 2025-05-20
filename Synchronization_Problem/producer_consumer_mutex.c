#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int count = 5;  // Shared variable
pthread_mutex_t lock;  // Mutex lock

void* producer(void* arg) {
    pthread_mutex_lock(&lock);

    int temp = count;  // Read count
    sleep(1);          // Simulate some delay (context switch)
    temp = temp + 1;   // Increment
    count = temp;      // Write back
    printf("Producer updated count to %d\n", count);

    pthread_mutex_unlock(&lock);
    return NULL;
}

void* consumer(void* arg) {
    pthread_mutex_lock(&lock);

    int temp = count;  // Read count
    sleep(1);          // Simulate some delay (context switch)
    temp = temp - 1;   // Decrement
    count = temp;      // Write back
    printf("Consumer updated count to %d\n", count);

    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    pthread_mutex_init(&lock, NULL);
    
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);
    

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    pthread_mutex_destroy(&lock);

    printf("Final count value: %d\n", count);
    return 0;
}
