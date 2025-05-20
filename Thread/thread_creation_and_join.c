#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 300
#define NUM_THREADS 3
#define PART_SIZE (ARRAY_SIZE / NUM_THREADS)

int array[ARRAY_SIZE];
int partial_sums[NUM_THREADS];  // Shared result array

void* sum_array_part(void* arg) {
    int index = *(int*)arg; //here we are casting the arg back to int
    int start = index * PART_SIZE;
    int end = start + PART_SIZE;
    int sum = 0;

    for (int i = start; i < end; i++) {
        sum += array[i];
        printf("Thread %d adding %d, current sum = %d\n", index, array[i], sum);
    }

    partial_sums[index] = sum;
    free(arg);
    return NULL;
}

int main() {
    // Initialize the array with values 1 to 30
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i + 1;
    }

    pthread_t threads[NUM_THREADS];

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        int* idx = malloc(sizeof(int));
        *idx = i;
        if (pthread_create(&threads[i], NULL, sum_array_part, idx) != 0) {// here &threads[i] is the address of the thread variable or thread identifier
             //NULL means default attributes which means the thread will be created with default attributes
             // if we want to set the attributes of the thread, we can use pthread_attr_t
             
            perror("Failed to create thread");
            return 1;//if failed to create thread, return 1 
        }
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);// here we are waiting for all the thread to finish
    }

    // Compute the final sum
    int total_sum = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        printf("Partial sum from thread %d = %d\n", i, partial_sums[i]);
        total_sum += partial_sums[i];
    }

    printf("Total sum of array = %d\n", total_sum);

    return 0;
}

//gcc thread_creation_and_join.c -o thread_creation_and_join -pthread
//./thread_creation_and_join
//execl() (and other exec*() functions) replaces the entire process image.

// So if we call execl() from any thread, 
// it doesn't just affect that thread  it replaces the entire process, 
// including all threads, with the new program (e.g., gnome-calculator).
// That means: you lose your original program — it becomes the new program.
// from the output of the program, we can see that the threads are created and calculating simultaneously.