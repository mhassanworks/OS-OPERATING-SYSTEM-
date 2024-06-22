#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;        // Process ID
    int priority;   // Priority
    int burst_time; // Burst time
    int remaining_time; // Remaining time for round-robin
} Process;

void sort_by_priority(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void priority_round_robin(Process processes[], int n, int quantum) {
    int total_remaining = 0;
    for (int i = 0; i < n; i++) {
        total_remaining += processes[i].remaining_time;
    }
    
    while (total_remaining > 0) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                if (processes[i].remaining_time > quantum) {
                    printf("Process %d is executing with priority %d\n", processes[i].pid, processes[i].priority);
                    processes[i].remaining_time -= quantum;
                    total_remaining -= quantum;
                } else {
                    printf("Process %d is executing with priority %d\n", processes[i].pid, processes[i].priority);
                    total_remaining -= processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                }
            }
        }
    }
}

int main() {
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process processes[n];
    
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter burst time and priority for process %d: ", i + 1);
        scanf("%d %d", &processes[i].burst_time, &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time;
    }
    
    printf("Enter the time quantum for round-robin scheduling: ");
    scanf("%d", &quantum);
    
    sort_by_priority(processes, n);
    priority_round_robin(processes, n, quantum);
    
    return 0;
}
