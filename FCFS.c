//Program to implement First Come First Serve Scheduling

#include<stdio.h>
#include<stdlib.h>
#define MAX 20

struct Process{
    int no;
    int at;
    int bt;
    int wt;
    int ct;
    int tat;
};

float avg_tat, avg_wt;

void Read_Process(struct Process **p, int n);

void Sort_Process(struct Process **p, int n);

void Gantt_Chart(struct Process **p, int n);

void TAT_WT(struct Process **p, int n);



void main(){

    int n;
    struct Process *p;

    p = (struct Process*)malloc(MAX * sizeof(struct Process));  
    

    printf("\n Enter the number of Processes: ");
    scanf("%d", &n);

    if(n > MAX){
        printf("\n Exceeded the maximum number of process!");
        exit(0);
    }
    if(n ==0){
        printf("\n No Resources!");
        exit(0);
    }

    Read_Process(&p, n);
    Sort_Process(&p,n);

    printf("\n Displaying the Gantt Chart: ");
    Gantt_Chart(&p, n);

    printf("\n The Total Average Time and Waiting Time of Process are: ");
    TAT_WT(&p, n);

}


void Read_Process(struct Process **p, int n){

    for(int i = 1; i <= n; i++){

        ((*p)[i]).no = i;
        ((*p)[i]).ct = 0;

        printf("\n Enter the Arrival Time and Burst Time of Process%d: " ,i);
        scanf("%d%d",&(((*p)[i]).at),&(((*p)[i]).bt));

    }
}

void Sort_Process(struct Process **p, int n){

    for(int i = n; i > 0; i--){
        for(int j = 1; j <= i-1; j++){
            if(((((*p)[j]).at)) > ((((*p)[j+1]).at))){

                int temp_no = (((*p)[j]).no);
                int temp_at = (((*p)[j]).at);
                int temp_bt = (((*p)[j]).bt);

                (((*p)[j]).no) = (((*p)[j+1]).no);
                (((*p)[j]).at) = (((*p)[j+1]).at);
                (((*p)[j]).bt) = (((*p)[j+1]).bt);

                (((*p)[j+1]).no) = temp_no;
                (((*p)[j+1]).at) = temp_at;
                (((*p)[j+1]).bt) = temp_bt;
            }
        }
    }

    printf("\n The Sorted Processes are: ");
    for(int i = 1;i <= n; i++){
        printf("\n Process%d : At: %d , Bt : %d",(((*p)[i]).no),(((*p)[i]).at),(((*p)[i]).bt));
    }
}

void Gantt_Chart(struct Process **p, int n){

    
    int temp = 0, sum_tat = 0, sum_wt = 0 ;
    printf("\n The Gantt chart of the FCFS Scheduling is:\n ");
    printf("\n|0");
    for(int i = 1; i <= n; i++){

        temp = temp + ((*p)[i]).bt;
        ((*p)[i]).ct = temp;

        printf("\t|Process%d\t|%d",(((*p)[i]).no),(((*p)[i]).ct));

        ((*p)[i]).tat = ((*p)[i]).ct - ((*p)[i]).at;
        sum_tat = sum_tat + ((*p)[i]).tat;

        ((*p)[i]).wt = ((*p)[i]).tat - ((*p)[i]).bt;
        sum_wt = sum_wt + ((*p)[i]).wt;


    }
    printf("|\n");

    avg_tat = sum_tat/(float)n;
  
    avg_wt = sum_wt/(float)n;

    //printf("\n Sum of TAT: %d Avg: %2f",sum_tat,avg_tat);
    //printf("\n Sum of WT: %d, Avg: %2f",sum_wt,avg_wt);
}

void TAT_WT(struct Process **p, int n){

    printf("\n Process\tTotal_Average_Time\tWaiting_Time\n");

    for(int i = 1; i <= n; i++){
        
        printf("\n Process%d\t\t%d\t\t%d",((*p)[i]).no,((*p)[i]).tat,((*p)[i]).wt);
    }
    printf("\n");
    printf("\n The Average Total_Average Time of the Processes is: %.2f",avg_tat);
    printf("\n The Average Waiting Time of the Processes is: %.2f",avg_wt);
}