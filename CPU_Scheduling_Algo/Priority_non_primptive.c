#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    bool completed;
} Process;

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time for P%d: ", p[i].pid);
        scanf("%d", &p[i].arrival_time);
        printf("Enter Burst Time for P%d: ", p[i].pid);
        scanf("%d", &p[i].burst_time);
        printf("Enter Priority (lower number = higher priority) for P%d: ", p[i].pid);
        scanf("%d", &p[i].priority);
        p[i].completed = false;
    }

    int time = 0, completed = 0;

    while (completed < n) {
        int idx = -1;
        int highest_priority = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && !p[i].completed) {
                if (p[i].priority < highest_priority) {
                    highest_priority = p[i].priority;
                    idx = i;
                } else if (p[i].priority == highest_priority) {
                    if (p[i].arrival_time < p[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            p[idx].start_time = time;
            time += p[idx].burst_time;
            p[idx].completion_time = time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].completed = true;
            completed++;
        } else {
            time++;
        }
    }

    // Output table
    printf("\n%-5s %-14s %-12s %-10s %-12s %-18s %-18s %-14s\n",
           "PID", "Arrival Time", "Burst Time", "Priority", "Start Time",
           "Completion Time", "Turnaround Time", "Waiting Time");

    for (int i = 0; i < n; i++) {
        printf("P%-4d %-14d %-12d %-10d %-12d %-18d %-18d %-14d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].priority,
               p[i].start_time, p[i].completion_time,
               p[i].turnaround_time, p[i].waiting_time);
    }

    return 0;
}
