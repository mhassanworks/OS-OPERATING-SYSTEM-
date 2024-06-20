#include <stdio.h>

#define MAX_PROCESSES 100

typedef struct {
    int pid; // Process ID
    int arrival_time; // Arrival time
    int burst_time; // Burst time
    int waiting_time; // Waiting time
    int turnaround_time; // Turnaround time
} Process;

void calculateWaitingTimeFCFS(Process processes[], int n) {
    processes[0].waiting_time = 0;
    for (int i = 1; i < n; i++) {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
    }
}

void calculateTurnaroundTime(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
}

void calculateWaitingTimeSJF(Process processes[], int n) {
    int completed = 0, time = 0, min_burst_time = 10000, shortest = 0, finish_time;
    int waiting_time[MAX_PROCESSES], burst_remaining[MAX_PROCESSES];
    int is_completed[MAX_PROCESSES] = {0};

    for (int i = 0; i < n; i++) {
        burst_remaining[i] = processes[i].burst_time;
    }

    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if ((processes[i].arrival_time <= time) && (is_completed[i] == 0) && (burst_remaining[i] < min_burst_time) && burst_remaining[i] > 0) {
                min_burst_time = burst_remaining[i];
                shortest = i;
            }
        }

        if (min_burst_time == 10000) {
            time++;
            continue;
        }

        burst_remaining[shortest]--;

        min_burst_time = burst_remaining[shortest];
        if (min_burst_time == 0) {
            min_burst_time = 10000;
        }

        if (burst_remaining[shortest] == 0) {
            completed++;
            is_completed[shortest] = 1;
            finish_time = time + 1;
            waiting_time[shortest] = finish_time - processes[shortest].burst_time - processes[shortest].arrival_time;
            if (waiting_time[shortest] < 0) {
                waiting_time[shortest] = 0;
            }
        }
        time++;
    }

    for (int i = 0; i < n; i++) {
        processes[i].waiting_time = waiting_time[i];
    }
}

void printProcesses(Process processes[], int n) {
    printf("PID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
}

int main() {
    int n, choice;
    Process processes[MAX_PROCESSES];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].pid = i + 1;
    }

    printf("Choose Scheduling Algorithm:\n1. FCFS\n2. SJF\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            calculateWaitingTimeFCFS(processes, n);
            break;
        case 2:
            calculateWaitingTimeSJF(processes, n);
            break;
        default:
            printf("Invalid choice!\n");
            return 1;
    }

    calculateTurnaroundTime(processes, n);
    printProcesses(processes, n);

    return 0;
}
