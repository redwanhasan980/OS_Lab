#include <stdio.h>

typedef struct {
    int pid;
    int burst_time;
    int arrival_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

void sort_by_arrival(Process p[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (p[i].arrival_time > p[j].arrival_time) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void print_table(Process p[], int n, int with_arrival) {
    printf("\n%-5s %-12s", "PID", "Burst Time");
    if (with_arrival) printf("%-14s", "Arrival Time");
    printf("%-14s %-18s %-18s %-14s\n", "Start Time", "Completion Time", "Turnaround Time", "Waiting Time");

    for (int i = 0; i < n; i++) {
        printf("P%-4d %-12d", p[i].pid, p[i].burst_time);
        if (with_arrival) printf("%-14d", p[i].arrival_time);
        printf("%-14d %-18d %-18d %-14d\n", 
               p[i].start_time, 
               p[i].completion_time, 
               p[i].turnaround_time, 
               p[i].waiting_time);
    }
}

void fcfs(Process p[], int n, int with_arrival) {
    if (with_arrival)
        sort_by_arrival(p, n);

    int time = 0;
    for (int i = 0; i < n; i++) {
        if (with_arrival && time < p[i].arrival_time)
            time = p[i].arrival_time;

        p[i].start_time = time;
        p[i].completion_time = p[i].start_time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - (with_arrival ? p[i].arrival_time : 0);
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;

        time = p[i].completion_time;
    }

    print_table(p, n, with_arrival);
}

int main() {
    int n, choice;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];

    printf("\nChoose scheduling mode:\n");
    printf("1. FCFS without Arrival Time\n");
    printf("2. FCFS with Arrival Time\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Burst Time for Process P%d: ", p[i].pid);
        scanf("%d", &p[i].burst_time);

        if (choice == 2) {
            printf("Enter Arrival Time for Process P%d: ", p[i].pid);
            scanf("%d", &p[i].arrival_time);
        } else {
            p[i].arrival_time = 0;  // default to 0
        }
    }

    fcfs(p, n, choice == 2);

    return 0;
}
