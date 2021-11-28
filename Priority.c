//Program to Implement Priority Scheduling

#include<stdio.h>
#include<stdlib.h>
#define MAX 20

struct Process{
    int no, at, bt, pr, ct, tat, wt;
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
    scanf("%d",&n);

    if(n == 0){
        printf("\n No resources! ");
        exit(0);
    }

    Read_Process(&p, n);                                            //Function Call to Read Processes

    Sort_Process(&p, n);                                            //Function call to Sort Processes

    printf("\n Presenting The Gantt chart of Priority Scheduling! ");
    Gantt_Chart(&p, n);                                             //Function Call to Display the Gantt Chart

    TAT_WT(&p, n);                                                  //Function Call to Calculate and Display TAT and WT
    


}

//Reads the Arrival Time, Burst Time and Priority of Processes
void Read_Process(struct Process **p, int n){

    for(int i = 1; i <= n; i++){
        printf("\n Enter the Arrival Time, Burst Time and Priority of the Process %d:  ",i);
        scanf("%d%d%d",&(((*p)[i]).at),&(((*p)[i]).bt),&(((*p)[i]).pr));

        ((*p)[i]).no = i;
    }

}

//Sorts Process according to Priority and Arrival Time in the Ready Queue
void Sort_Process(struct Process **p, int n){

    int track = 0;

    for(int i = 1; i <= n; i++){
        if((((*p)[i]).at) <= track){
            int min_priority = i;

            for(int j = i+1; j <= n; j++){
                if(((*p)[j]).pr < (((*p)[min_priority]).pr)){
                    min_priority = j;
                }
            }

            if(min_priority != i){

                int temp_no = (((*p)[i]).no);
                int temp_at = (((*p)[i]).at);
                int temp_bt = (((*p)[i]).bt);
                int temp_pr = (((*p)[i]).pr);

                (((*p)[i]).no) = (((*p)[min_priority]).no);
                (((*p)[i]).at) = (((*p)[min_priority]).at);
                (((*p)[i]).bt) = (((*p)[min_priority]).bt);
                (((*p)[i]).pr) = (((*p)[min_priority]).pr);

                (((*p)[min_priority]).no) = temp_no;
                (((*p)[min_priority]).at) = temp_at;
                (((*p)[min_priority]).bt) = temp_bt;
                (((*p)[min_priority]).pr) = temp_pr;
            }
        }
        else{

            int min_at = i;

            for(int j = i+1; j <= n; j++){
                if(((*p)[j]).at < (((*p)[min_at]).at)){
                    min_at = j;
                }
            }

            if(min_at != i){
                int temp_no = (((*p)[i]).no);
                int temp_at = (((*p)[i]).at);
                int temp_bt = (((*p)[i]).bt);
                int temp_pr = (((*p)[i]).pr);

                (((*p)[i]).no) = (((*p)[min_at]).no);
                (((*p)[i]).at) = (((*p)[min_at]).at);
                (((*p)[i]).bt) = (((*p)[min_at]).bt);
                (((*p)[i]).pr) = (((*p)[min_at]).pr);

                (((*p)[min_at]).no) = temp_no;
                (((*p)[min_at]).at) = temp_at;
                (((*p)[min_at]).bt) = temp_bt;
                (((*p)[min_at]).pr) = temp_pr;
            }
        }

        track = track + ((*p)[i]).bt;
    }



    printf("\n The Sorted Processes are: ");
    for(int i = 1;i <= n; i++){
        printf("\n Process%d : At: %d , Bt : %d",(((*p)[i]).no),(((*p)[i]).at),(((*p)[i]).bt));
    }
}

//This Function Creates the Gantt Chart of The Processes
void Gantt_Chart(struct Process **p, int n){

    int temp = 0, sum_tat = 0, sum_wt = 0 ;
    printf("\n The Gantt chart of the Priority Scheduling is:\n ");
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
}


//Function to Calculate Total_Average_time and Waiting_Time
void TAT_WT(struct Process **p, int n){

    printf("\n Process\tTotal_Average_Time\tWaiting_Time\n");

    for(int i = 1; i <= n; i++){
        
        printf("\n Process%d\t\t%d\t\t%d",((*p)[i]).no,((*p)[i]).tat,((*p)[i]).wt);
    }
    printf("\n");

    printf("\n The Average Total_Average Time of the Processes is: %.2f",avg_tat);
    printf("\n The Average Waiting Time of the Processes is: %.2f",avg_wt);

}