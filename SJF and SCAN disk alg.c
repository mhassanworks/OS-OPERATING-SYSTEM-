#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

typedef struct {
    int request_time;
    int cylinder;
} DiskRequest;

void sort_by_cylinder(DiskRequest requests[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j].cylinder > requests[j + 1].cylinder) {
                DiskRequest temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
}

void sjf_schedule(DiskRequest requests[], int n) {
    sort_by_cylinder(requests, n);

    printf("SJF Disk Scheduling Order:\n");
    for (int i = 0; i < n; i++) {
        printf("Request at time %d for cylinder %d\n", requests[i].request_time, requests[i].cylinder);
    }
}

void scan_schedule(DiskRequest requests[], int n, int start, int direction) {
    sort_by_cylinder(requests, n);

    printf("SCAN Disk Scheduling Order:\n");
    if (direction == 1) { // Scan towards larger cylinder numbers
        for (int i = 0; i < n; i++) {
            if (requests[i].cylinder >= start) {
                printf("Request at time %d for cylinder %d\n", requests[i].request_time, requests[i].cylinder);
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i].cylinder < start) {
                printf("Request at time %d for cylinder %d\n", requests[i].request_time, requests[i].cylinder);
            }
        }
    } else { // Scan towards smaller cylinder numbers
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i].cylinder <= start) {
                printf("Request at time %d for cylinder %d\n", requests[i].request_time, requests[i].cylinder);
            }
        }
        for (int i = 0; i < n; i++) {
            if (requests[i].cylinder > start) {
                printf("Request at time %d for cylinder %d\n", requests[i].request_time, requests[i].cylinder);
            }
        }
    }
}

int main() {
    DiskRequest requests[MAX_REQUESTS];
    int n, choice, start, direction;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter request time and cylinder for request %d: ", i + 1);
        scanf("%d %d", &requests[i].request_time, &requests[i].cylinder);
    }

    printf("Enter the starting cylinder: ");
    scanf("%d", &start);

    printf("Choose the scheduling algorithm:\n");
    printf("1. Shortest Job First (SJF)\n");
    printf("2. SCAN\n");
    scanf("%d", &choice);

    if (choice == 1) {
        sjf_schedule(requests, n);
    } else if (choice == 2) {
        printf("Enter the scan direction (1 for increasing, 0 for decreasing): ");
        scanf("%d", &direction);
        scan_schedule(requests, n, start, direction);
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}
