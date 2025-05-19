// terminate_calculator.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() {
    FILE *fp = fopen("calc_pid.txt", "r");
    if (!fp) {
        perror("Cannot open PID file");
        return 1;
    }

    pid_t pid;
    fscanf(fp, "%d", &pid);
    fclose(fp);

    if (kill(pid, SIGKILL) == 0) {
        printf("Successfully terminated calculator process with PID %d\n", pid);
    } else {
        perror("Failed to terminate process");
    }

    return 0;
}
