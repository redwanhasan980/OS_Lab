#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Define a struct to hold thread parameters
typedef struct {
    int thread_id;
    char message[50];
} ThreadData;

// Thread function
void* thread_function(void* arg) {
    ThreadData* data = (ThreadData*) arg;

    printf("Thread ID: %d\n", data->thread_id);
    printf("Message: %s\n", data->message);
   
    free(data);  // Free memory allocated in main
    return NULL;
}

int main() {
    pthread_t threads[3];

    for (int i = 0; i < 3; i++) {
        // Dynamically allocate memory for thread data
        ThreadData* data = malloc(sizeof(ThreadData));
        if (data == NULL) {
            perror("malloc failed");// what perror does is to print the error message 
            exit(EXIT_FAILURE);//exit(EXIT_FAILURE) is used to terminate the program with a failure status
        }

        data->thread_id = i + 1;
        snprintf(data->message, sizeof(data->message), "Hello from thread %d", i + 1);

        // Create the thread
        if (pthread_create(&threads[i], NULL, thread_function, data) != 0) {
            perror("Failed to create thread");
            free(data);  // Clean up on failure
            exit(EXIT_FAILURE);
        }
    }

    // Join all threads
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
