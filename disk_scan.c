#include<stdio.h>
#include<stdlib.h>

int seeks = 0, req[30];

void main() {
    int i, j, n, head, cylinders, temp, pos;

    printf("\nEnter the number of Requests: ");
    scanf("%d", &n);

    printf("\nEnter the number of Cylinders: ");
    scanf("%d", &cylinders);

    printf("\nEnter the initial position of head: ");
    scanf("%d", &head);

    printf("\nEnter the Requests: ");
    for(i = 0; i < n; i++)
        scanf("%d", &req[i]);

    for(i=0;i<n-1;i++){
        for(j=i+1;j<n;j++){
            if(req[i]>req[j]){
                temp=req[j];
                req[j]=req[i];
                req[i]=temp;
            }
        }
    }
    for(i=0;i<n;i++){
        if(req[i]>head){
            pos=i;
            break;
        }
    }
    printf("\nOrder of execution is: ");
    for(i=pos;i<n;i++){
        printf("%d ", req[i]);
    }
    for(i=pos-1;i>=0;i--){
        printf("%d ", req[i]);
    }
    seeks = (cylinders-1-head) + (cylinders-1-req[0]);
    printf("\nTotal no.of seeks: %d", seeks);
}


/* OUTPUT

Enter the number of Requests: 7

Enter the number of Cylinders: 200

Enter the initial position of head: 55

Enter the Requests: 93 176 42 48 27 14 180

Order of execution is: 93 176 180 48 42 27 14
Total no.of seeks: 329

*/
