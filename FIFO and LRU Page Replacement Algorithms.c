#include <stdio.h>
#include <limits.h>

void fifoPageReplacement(int pages[], int n, int capacity) {
    int frame[capacity];
    int front = 0, rear = 0, count = 0, pageFaults = 0;

    for (int i = 0; i < capacity; i++) {
        frame[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frame[rear] = pages[i];
            rear = (rear + 1) % capacity;
            if (count < capacity) {
                count++;
            } else {
                front = (front + 1) % capacity;
            }
            pageFaults++;
        }

        printf("Frame: ");
        for (int j = 0; j < capacity; j++) {
            if (frame[j] != -1) {
                printf("%d ", frame[j]);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

void lruPageReplacement(int pages[], int n, int capacity) {
    int frame[capacity];
    int time[capacity];
    int pageFaults = 0;

    for (int i = 0; i < capacity; i++) {
        frame[i] = -1;
        time[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int found = 0, lru = 0, minTime = INT_MAX;
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                time[j] = i + 1;
                break;
            }
        }

        if (!found) {
            for (int j = 0; j < capacity; j++) {
                if (time[j] < minTime) {
                    minTime = time[j];
                    lru = j;
                }
            }
            frame[lru] = pages[i];
            time[lru] = i + 1;
            pageFaults++;
        }

        printf("Frame: ");
        for (int j = 0; j < capacity; j++) {
            if (frame[j] != -1) {
                printf("%d ", frame[j]);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    int pages[] = {1, 3, 0, 3, 5, 6};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;
    int choice;

    printf("Choose Page Replacement Algorithm:\n");
    printf("1. FIFO\n");
    printf("2. LRU\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("FIFO Page Replacement:\n");
            fifoPageReplacement(pages, n, capacity);
            break;
        case 2:
            printf("LRU Page Replacement:\n");
            lruPageReplacement(pages, n, capacity);
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}
