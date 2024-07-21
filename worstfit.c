#include <stdio.h>

struct process {
    int pid, psize, alloc, bnum, bx;
} p[20];

struct block {
    int bnum, bsize;
} b[20], temp;

int main() {
    int n, m, i, j;

    printf("\nEnter the number of Memory Blocks:\t");
    scanf("%d", &m);

    for (i = 0; i < m; i++) {
        printf("Memory Block %d :\n\tEnter the Block Number:\t", i + 1);
        scanf("%d", &b[i].bnum);
        printf("\tEnter the Block Size:\t");
        scanf("%d", &b[i].bsize);
    }

    printf("\nEnter the number of processes:\t");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Process %d :\n\tEnter the Process Id:\t", i + 1);
        scanf("%d", &p[i].pid);
        printf("\tEnter the Process Size:\t");
        scanf("%d", &p[i].psize);
        p[i].alloc = 0;
    }

    i = 0;

    printf("\n-------------------------------------------------------------------");
    printf("\nPROCESS ID\tPROCESS SIZE\tBLOCK NUMBER\tFREE SPACE\n");
    printf("\n-------------------------------------------------------------------");

    while (i < n) {
        int worst_fit_index = -1;
        int max_free_space = -1;

        if (p[i].alloc == 0) {
            for (j = 0; j < m; j++) {
                if (p[i].psize <= b[j].bsize && b[j].bsize - p[i].psize > max_free_space) {
                    max_free_space = b[j].bsize - p[i].psize;
                    worst_fit_index = j;
                }
            }

            if (worst_fit_index != -1) {
                p[i].alloc = 1;
                p[i].bnum = b[worst_fit_index].bnum;
                p[i].bx = worst_fit_index;
                int free_space = b[worst_fit_index].bsize - p[i].psize;
                printf("\n%d\t\t%d\t\t%d\t\t%d", p[i].pid, p[i].psize, p[i].bnum, free_space);
                b[worst_fit_index].bsize -= p[i].psize;
            } else {
                printf("\n%d\t\t%d\t\t-\t\t-\t\t [NOT ALLOCATED]", p[i].pid, p[i].psize);
            }
        }
        i++;
    }

    printf("\n-------------------------------------------------------------------\n");

    return 0;
}

/* OUTPUT

Enter the number of Memory Blocks:      3
Memory Block 1 :
        Enter the Block Number: 1
        Enter the Block Size:   100
Memory Block 2 :
        Enter the Block Number: 2
        Enter the Block Size:   200
Memory Block 3 :
        Enter the Block Number: 3
        Enter the Block Size:   150

Enter the number of processes:  4
Process 1 :
        Enter the Process Id:   1
        Enter the Process Size: 120
Process 2 :
        Enter the Process Id:   2
        Enter the Process Size: 80
Process 3 :
        Enter the Process Id:   3
        Enter the Process Size: 180
Process 4 :
        Enter the Process Id:   4
        Enter the Process Size: 100

-------------------------------------------------------------------
PROCESS ID      PROCESS SIZE    BLOCK NUMBER    FREE SPACE

-------------------------------------------------------------------
1               120             2               80
2               80              3               70
3               180             -               -                [NOT ALLOCATED]
4               100             1               0
-------------------------------------------------------------------

*/
