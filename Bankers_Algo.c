#include <stdio.h>
#include <stdlib.h>
#define SIZE 20
 
int q[SIZE], k = 0;

void Read_Resources(int p, int inst, int arr[p][inst])
{
    for (int i = 1; i <= p; i++)
    {
        printf("\n Enter the %d Resources for Process%d\n",inst, i);
        for (int j = 1; j <= inst; j++) {
            scanf("%d",&(arr[i][j]));
        }
    }
}

void Need_Mat(int p, int inst, int max[p][inst], int alloc[p][inst], int need[p][inst]){

    for(int i = 1; i <= p; i++ ){
        for(int j = 1; j <= inst; j++ ){
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    printf("\n The Need Matrix is: ");
    for(int i = 1; i <= p; i++ ){
        printf("\nProcess %d: ",i);
        for(int j = 1; j <= inst; j++ ){
            printf("\t%d",need[i][j]);
        }
        
    }
}


int Search(int item){
    for(int i=0;i<k;i++){
        if(q[i]==item){
            return 1;
        }
    }
    return 0;
}
int Safe(int p, int inst, int alloc[p][inst], int need[p][inst], int avail[inst]){
    int count = 0, temp = 0;
    for(int i = 1;; i=(i%p)+1){
        int track = 0;
        for(int j = 1; j <= inst; j++){
            if((avail[j] >= need[i][j])&&(need[i][j]!=-1)){
                track++;
            }
        }
       
        if((track == inst)&&(Search(i) == 0)){
            q[k++] = i;
            for(int j = 1; j<=inst; j++){
                need[i][j] = -1;
                avail[j] = avail[j] + alloc[i][j];
            }
            count++;
        }
        

        if(count == p){
            return 0;
        }
        temp++;
        if(temp > (p*p)){
            return 1;
        }
    }
}

int Request(int p, int inst, int req, int alloc[p][inst], int need[p][inst], int avail[inst]){

    int request[inst], track = 0;
    printf("\n Enter the request on Process%d: ",req);
    for(int i = 1; i<= inst; i++){
        scanf("%d",&(request[i]));
        if((need[req][i] >= request[i])&&(avail[i] >= request[i])){
            track++;
        }
    }
    if(track == inst){
        for(int i = 1; i <= inst; i++){
            alloc[req][i] = alloc[req][i] + request[i];
            need[req][i] = need[req][i] - request[i];
            avail[i] = avail[i] - request[i];
        }
        return 1;
    }
    else{
        return 0;
    }
}
 
// Program to pass the 2D array to a function in C
void main()
{
    int p,inst,req;
    char op;

    printf("\n Enter the number of processes: ");
    scanf("%d",&p);

    if(p == 0){
        printf("\n No Processes Present!");
        printf("\n Exiting....");
        exit(0);
    }
    else if(p < 0){
        printf("\n Invalid Value! Exiting");
        exit(0);
    }

    printf("\n Enter the number of instances for the processes: ");
    scanf("%d",&inst);

    int alloc[p][inst], max[p][inst], need[p][inst], avail[inst];
 

    printf("\n Enter the resources allocated: ");
    Read_Resources(p, inst, alloc);

    printf("\n Enter the maximum resources needed: ");
    Read_Resources(p, inst, max);
 

    printf("\n Finding the need matrix: ");
    Need_Mat(p, inst, max, alloc, need);

    printf("\n The Need Matrix: ");
    
    printf("\n Enter the available resources: ");
    for(int i= 1;i <= inst; i++){
        scanf("%d",&(avail[i]));
    }

    printf("\n Do you want to request any resources?(Y/N): ");
    getchar();
    scanf("%c",&op);

    if((op == 'Y')||(op == 'y')){
        printf("\n Enter the process you want to request on: ");
        scanf("%d",&req);

        if((req>0)&&(req<=p)){
            int response = Request(p,inst,req,alloc,need,avail);
            if(response != 1){
                printf("\n This request cannot be allocated!");
                exit(0);
            }
            else{
                printf("\n Request may be allocated!");
            }
        }
        else{
            printf("\n Invalid Process!\nExiting...");
            exit(0);
        }
    }

    printf("\n Checking if the system is safe!");
    int safe = Safe(p, inst, alloc, need, avail);

    if((safe == 0)&&((op=='Y')||(op=='y'))){
        printf("\n The Request Can be granted! The Safe Sequence is found!\n");
        for(int i = 0;i <p;i++ ){
            printf("\t Process%d",q[i]);
        }
    }
    else if(safe == 0){
        printf("\n The Safe sequence is Found!!");
        for(int i = 0;i <p;i++ ){
            printf("\t Process%d",q[i]);
        }
    }
    else if((safe == 1)&&((op=='Y')||(op=='y'))){
        printf("\n The System is UnSafe. No Safe Sequence Found! The Request Cannot be Granted!");
    }
    else{
         printf("\n The System is UnSafe. No Safe Sequence Found!");
    }

}