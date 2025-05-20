#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

void* thread1_func(void* arg) {
    pthread_mutex_lock(&mutex1);
    printf("Thread 1: locked mutex1\n");
    sleep(1);  // Give Thread 2 a chance to lock mutex2

    printf("Thread 1: trying to lock mutex2\n");
    pthread_mutex_lock(&mutex2);  // This will wait if mutex2 is already locked
    printf("Thread 1: locked mutex2\n");

    // Critical section
    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);
    return NULL;
}

void* thread2_func(void* arg) {
    pthread_mutex_lock(&mutex2);
    printf("Thread 2: locked mutex2\n");
    sleep(1);  // Give Thread 1 a chance to lock mutex1

    printf("Thread 2: trying to lock mutex1\n");
    pthread_mutex_lock(&mutex1);  // This will wait if mutex1 is already locked
    printf("Thread 2: locked mutex1\n");

    // Critical section
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);

    pthread_create(&thread1, NULL, thread1_func, NULL);
    pthread_create(&thread2, NULL, thread2_func, NULL);
printf("Thread 1 and Thread 2 created\n");
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);

    return 0;
}
