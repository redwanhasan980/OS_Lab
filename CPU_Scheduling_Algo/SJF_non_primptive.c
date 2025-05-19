#include <stdio.h>
#include <stdbool.h>

#define MAX_TIME 1000  // For Gantt Chart

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
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
        printf("Enter Arrival Time for Process P%d: ", p[i].pid);
        scanf("%d", &p[i].arrival_time);
        printf("Enter Burst Time for Process P%d: ", p[i].pid);
        scanf("%d", &p[i].burst_time);
        p[i].completed = false;
    }

    int completed = 0, time = 0;
    int timeline[MAX_TIME];  // For Gantt chart
    int timeline_index = 0;

    while (completed < n) {
        int idx = -1;
        int min_burst = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && !p[i].completed) {
                if (p[i].burst_time < min_burst) {
                    min_burst = p[i].burst_time;
                    idx = i;
                } else if (p[i].burst_time == min_burst) {
                    if (p[i].arrival_time < p[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            p[idx].start_time = time;
            for (int t = 0; t < p[idx].burst_time; t++) {
                timeline[timeline_index++] = p[idx].pid;
            }

            p[idx].completion_time = p[idx].start_time + p[idx].burst_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].completed = true;
            time = p[idx].completion_time;
            completed++;
        } else {
            timeline[timeline_index++] = -1;  // CPU idle
            time++;
        }
    }

    // Print Table
    printf("\n%-5s %-14s %-12s %-12s %-18s %-18s %-14s\n",
           "PID", "Arrival Time", "Burst Time", "Start Time",
           "Completion Time", "Turnaround Time", "Waiting Time");

    for (int i = 0; i < n; i++) {
        printf("P%-4d %-14d %-12d %-12d %-18d %-18d %-14d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].start_time, p[i].completion_time,
               p[i].turnaround_time, p[i].waiting_time);
    }

    // Gantt Chart
    printf("\nGantt Chart:\n|");

    for (int i = 0; i < timeline_index; i++) {
        if (i == 0 || timeline[i] != timeline[i - 1]) {
            if (timeline[i] == -1)
                printf(" Id |");
            else
                printf(" P%d |", timeline[i]);
        }
    }

    printf("\n0");
    for (int i = 1; i < timeline_index; i++) {
        if (timeline[i] != timeline[i - 1]) {
            printf("    %d", i);
        }
    }
    printf("    %d\n", timeline_index);

    return 0;
}
