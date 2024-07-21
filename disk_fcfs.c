#include<stdio.h>
#include<stdlib.h>

int seeks = 0, req[30];

void main() {
    int i, n, head, cylinders;

    printf("\nEnter the number of Requests: ");
    scanf("%d", &n);

    printf("\nEnter the number of Cylinders: ");
    scanf("%d", &cylinders);

    printf("\nEnter the initial position of head: ");
    scanf("%d", &head);

    printf("\nEnter the Requests: ");
    for(i = 0; i < n; i++)
        scanf("%d", &req[i]);

    seeks += abs(req[0] - head);

    for(i = 1; i < n; i++) {
        seeks += abs(req[i] - req[i - 1]);
    }

    printf("\nTotal No. of Seeks = %d", seeks);
}


/* OUTPUT

Enter the number of Requests: 7

Enter the number of Cylinders: 200

Enter the initial position of head: 55

Enter the Requests: 93 176 42 148 27 14 180

Total No. of Seeks = 661

*/
