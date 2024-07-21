#include <stdio.h>
#include <stdlib.h>

int n, m, max[20][20], alloc[20][20], need[20][20], avail[20], finish[20], count = 0;

void safety() {
    int i, j, k;
    int progress, iterationCount = 0;

    while (count < n) {
        progress = 0;

        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int canAllocate = 1;

                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        canAllocate = 0;
                        break;
                    }
                }

                if (canAllocate) {
                    for (k = 0; k < m; k++) {
                        avail[k] += alloc[i][k];
                    }
                    finish[i] = 1;
                    printf("P%d\t", i);
                    count++;
                    progress = 1;
                }
            }
        }

        if (!progress) {
            iterationCount++;
            if (iterationCount > n) {
                printf("\nNo safe sequence exists.\n");
                return;
            }
        } else {
            iterationCount = 0;
        }
    }
}

int main() {
    int i, j;

    printf("\nEnter number of processes:\t");
    scanf("%d", &n);

    printf("\nEnter number of resource instances:\t");
    scanf("%d", &m);

    printf("\n\nEnter maximum resources requirement of processes\n");
    for (i = 0; i < n; i++) {
        printf("\nProcess %d:\t\n", i);
        for (j = 0; j < m; j++) {
            printf("\tResource %d: ", j + 1);
            scanf("%d", &max[i][j]);
        }
    }

    printf("\n\nEnter allocated resources of processes\n");
    for (i = 0; i < n; i++) {
        printf("\nProcess %d:\t\n", i);
        for (j = 0; j < m; j++) {
            printf("\tResource %d: ", j + 1);
            scanf("%d", &alloc[i][j]);
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    printf("\n\nEnter available resources\n");
    for (j = 0; j < m; j++) {
        printf("\tResource %d: ", j + 1);
        scanf("%d", &avail[j]);
    }

    for (i = 0; i < n; i++) {
        finish[i] = 0;
    }

    printf("\n\nNeed Matrix:\n");
    for (i = 0; i < n; i++) {
        printf("\nProcess %d: ", i);
        for (j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
    }

    printf("\n\nSafety Sequence:\t");
    safety();
    printf("\n");

    return 0;
}

/* OUTPUT

Enter number of processes:      3

Enter number of resource instances:     2


Enter maximum resources requirement of processes

Process 0:
        Resource 1: 8
        Resource 2: 5

Process 1:
        Resource 1: 6
        Resource 2: 4

Process 2:
        Resource 1: 7
        Resource 2: 3


Enter allocated resources of processes

Process 0:
        Resource 1: 5
        Resource 2: 4

Process 1:
        Resource 1: 3
        Resource 2: 3

Process 2:
        Resource 1: 7 
        Resource 2: 0


Enter available resources
        Resource 1: 4
        Resource 2: 4


Need Matrix:

Process 0: 3 1
Process 1: 3 1
Process 2: 0 3

Safety Sequence:        P0      P1      P2

*/
