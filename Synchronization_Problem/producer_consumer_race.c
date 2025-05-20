#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int count = 5;  // Shared variable

void* producer(void* arg) {
    int temp = count;  // Read count
    sleep(1);          // Simulate some delay (context switch)
    temp = temp + 1;   // Increment
    count = temp;      // Write back
    printf("Producer updated count to %d\n", count);
    return NULL;
}

void* consumer(void* arg) {
    int temp = count;  // Read count
    sleep(1);          // Simulate some delay (context switch)
    temp = temp - 1;   // Decrement
    count = temp;      // Write back
    printf("Consumer updated count to %d\n", count);
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;
    pthread_create(&cons_thread, NULL, consumer, NULL);
    pthread_create(&prod_thread, NULL, producer, NULL);
    

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    printf("Final count value: %d\n", count);
    return 0;
}
