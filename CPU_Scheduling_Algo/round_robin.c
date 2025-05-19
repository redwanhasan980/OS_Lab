#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

int main() {
    int n, time_quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time for P%d: ", p[i].pid);
        scanf("%d", &p[i].arrival_time);
        printf("Enter Burst Time for P%d: ", p[i].pid);
        scanf("%d", &p[i].burst_time);
        p[i].remaining_time = p[i].burst_time;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &time_quantum);

    int time = 0;           // Current time
    int completed = 0;      // Number of completed processes
    int queue[1000];        // Ready queue for processes' indices
    int front = 0, rear = 0;
    bool in_queue[n];       // Track if process is already in queue

    for (int i = 0; i < n; i++) in_queue[i] = false;

    // Enqueue processes that arrive at time 0
    for (int i = 0; i < n; i++) {
        if (p[i].arrival_time == 0) {
            queue[rear++] = i;
            in_queue[i] = true;
        }
    }

    if (rear == 0) {
        // If no process arrives at 0, find earliest arrival process to start
        int earliest = 0;
        for (int i = 1; i < n; i++) {
            if (p[i].arrival_time < p[earliest].arrival_time) earliest = i;
        }
        time = p[earliest].arrival_time;
        queue[rear++] = earliest;
        in_queue[earliest] = true;
    }

    while (completed < n) {
        if (front == rear) {
            // Queue empty but not all completed, move time to next arriving process
            int next_arrival = 1e9;
            int idx = -1;
            for (int i = 0; i < n; i++) {
                if (!in_queue[i] && p[i].remaining_time > 0 && p[i].arrival_time < next_arrival) {
                    next_arrival = p[i].arrival_time;
                    idx = i;
                }
            }
            time = next_arrival;
            queue[rear++] = idx;
            in_queue[idx] = true;
        }

        int current = queue[front++];
        if (front == 1000) front = 0; // Circular queue wrap

        if (p[current].remaining_time > 0) {
            int exec_time = (p[current].remaining_time < time_quantum) ? p[current].remaining_time : time_quantum;
            p[current].remaining_time -= exec_time;
            time += exec_time;

            // Enqueue any new arrivals during execution
            for (int i = 0; i < n; i++) {
                if (!in_queue[i] && p[i].arrival_time <= time && p[i].remaining_time > 0) {
                    queue[rear++] = i;
                    if (rear == 1000) rear = 0;
                    in_queue[i] = true;
                }
            }

            // If process still has burst left, re-enqueue it
            if (p[current].remaining_time > 0) {
                queue[rear++] = current;
                if (rear == 1000) rear = 0;
            } else {
                p[current].completion_time = time;
                p[current].turnaround_time = p[current].completion_time - p[current].arrival_time;
                p[current].waiting_time = p[current].turnaround_time - p[current].burst_time;
                completed++;
            }
        }
    }

    // Print results
    printf("\n%-5s %-14s %-12s %-18s %-18s %-14s\n",
           "PID", "Arrival Time", "Burst Time", "Completion Time",
           "Turnaround Time", "Waiting Time");

    for (int i = 0; i < n; i++) {
        printf("P%-4d %-14d %-12d %-18d %-18d %-14d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
    }

    return 0;
}
