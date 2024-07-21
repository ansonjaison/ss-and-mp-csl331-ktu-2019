#include <stdio.h>

struct process
{
    int pid, psize, alloc, bnum, bx;
} p[20];

struct block
{
    int bnum, bsize;
} b[20];

void main()
{
    int n, m, i, j;

    printf("\nEnter the number of Memory Blocks:\t");
    scanf("%d", &m);

    for (i = 0; i < m; i++)
    {
        printf("Memory Block %d :\n\tEnter the Block Number:\t", i + 1);
        scanf("%d", &b[i].bnum);
        printf("\tEnter the Block Size:\t");
        scanf("%d", &b[i].bsize);
    }

    printf("\nEnter the number of processes:\t");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
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

    // First fit: i -> process, j -> block
    while (i < n)
    {
        if (p[i].alloc == 0)
        {
            for (j = 0; j < m; j++)
            {
                if (p[i].psize <= b[j].bsize)
                {
                    p[i].alloc = 1;
                    p[i].bnum = b[j].bnum;
                    p[i].bx = j;
                    // Update the remaining free space in the block before allocation
                    int free_space = b[j].bsize - p[i].psize;
                    printf("\n%d\t\t%d\t\t%d\t\t%d", p[i].pid, p[i].psize, p[i].bnum, free_space);
                    b[j].bsize -= p[i].psize;
                    break;
                }
            }
        }
        i++;
    }

    // Printing processes not allocated
    for (i = 0; i < n; i++)
    {
        if (p[i].alloc == 0)
            printf("\n%d\t\t%d\t\t-\t\t-\t\t [NOT ALLOCATED]", p[i].pid, p[i].psize);
    }
    printf("\n-------------------------------------------------------------------\n");
}

/* OUTPUT

Enter the number of Memory Blocks:      3
Memory Block 1 :
        Enter the Block Number: 1
        Enter the Block Size:   400
Memory Block 2 :
        Enter the Block Number: 2
        Enter the Block Size:   300
Memory Block 3 :
        Enter the Block Number: 3
        Enter the Block Size:   500

Enter the number of processes:  4
Process 1 :
        Enter the Process Id:   1
        Enter the Process Size: 200
Process 2 :
        Enter the Process Id:   2
        Enter the Process Size: 350
Process 3 :
        Enter the Process Id:   3
        Enter the Process Size: 150
Process 4 :
        Enter the Process Id:   4
        Enter the Process Size: 400

-------------------------------------------------------------------
PROCESS ID      PROCESS SIZE    BLOCK NUMBER    FREE SPACE

-------------------------------------------------------------------
1               200             1               200
2               350             3               150
3               150             1               50
4               400             -               -                [NOT ALLOCATED]
-------------------------------------------------------------------

 */   
    
