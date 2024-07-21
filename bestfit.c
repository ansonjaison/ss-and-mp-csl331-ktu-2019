#include<stdio.h>

struct process {
    int pid, psize, alloc, bnum, bx;
} p[20];

struct block {
    int bnum, bsize;
} b[20], temp;

void main() {
    int n, m, i, j, k, l;

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
    j = 0;

    printf("\n-------------------------------------------------------------------");
    printf("\nPROCESS ID\tPROCESS SIZE\tBLOCK NUMBER\tFREE SPACE\n");
    printf("\n-------------------------------------------------------------------");

    while (i < n) {
        int best_fit_index = -1;
        int min_free_space = 99999;

        if (p[i].alloc == 0) {
            for (j = 0; j < m; j++) {
                if (p[i].psize <= b[j].bsize && b[j].bsize - p[i].psize < min_free_space) {
                    min_free_space = b[j].bsize - p[i].psize;
                    best_fit_index = j;
                }
            }

            if (best_fit_index != -1) {
                p[i].alloc = 1;
                p[i].bnum = b[best_fit_index].bnum;
                p[i].bx = best_fit_index;
                int free_space = b[best_fit_index].bsize - p[i].psize;
                printf("\n%d\t\t%d\t\t%d\t\t%d", p[i].pid, p[i].psize, p[i].bnum, free_space);
                b[best_fit_index].bsize -= p[i].psize;
            } else {
                printf("\n%d\t\t%d\t\t-\t\t-\t\t [NOT ALLOCATED]", p[i].pid, p[i].psize);
            }
        }
        i++;
    }

    printf("\n-------------------------------------------------------------------\n");
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
        Enter the Process Size: 50
Process 2 :
        Enter the Process Id:   2
        Enter the Process Size: 100
Process 3 :
        Enter the Process Id:   3
        Enter the Process Size: 150
Process 4 :
        Enter the Process Id:   4
        Enter the Process Size: 200

-------------------------------------------------------------------
PROCESS ID      PROCESS SIZE    BLOCK NUMBER    FREE SPACE

-------------------------------------------------------------------
1               50              1               50
2               100             3               50
3               150             2               50
4               200             -               -                [NOT ALLOCATED]
-------------------------------------------------------------------

*/
