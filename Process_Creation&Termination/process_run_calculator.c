#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
int main() {
    pid_t pid = fork();  // Create child process

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child PID: %d - Starting Calculator\n", getpid());
        execl("/usr/bin/gnome-calculator", "gnome-calculator", NULL);
        perror("execl failed");  // If execl fails
        exit(1);
    } else {
        // Parent process
        printf("Parent PID: %d - Child running Calculator with PID: %d\n", getpid(), pid);
        // Optionally write child PID to a file for later use
        FILE *fp = fopen("calc_pid.txt", "w");
        if (fp) {
            fprintf(fp, "%d\n", pid);
            fclose(fp);
        }
    }

    return 0;
}