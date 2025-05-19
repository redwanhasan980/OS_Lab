#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main() {
    pid_t pid = fork(); 
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child PID: %d - Starting Calculator\n", getpid());
        execl("/usr/bin/gnome-calculator", "gnome-calculator", NULL);
        perror("execl failed");  
        exit(1);
    } else {
        // Parent process
        printf("Parent PID: %d - Child running Calculator with PID: %d\n", getpid(), pid);
 
        FILE *fp = fopen("calc_pid.txt", "w");
        if (fp) {
            fprintf(fp, "%d\n", pid);
            fclose(fp);
        }
        int status;
        waitpid(pid, &status, 0);  

        if (WIFEXITED(status)) {
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child was killed by signal %d\n", WTERMSIG(status));
        } else {
            printf("Child terminated abnormally\n");
        }
    }

    return 0;
}