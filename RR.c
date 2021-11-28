//Program to implement Round Robin Algorithm

#include<stdio.h>
#include<stdlib.h>
#define MAX 50

struct Process{
    int no, at, bt, ct, wt, tat;
}*q;

int rear = -1, front = -1, net_time = 0, avg_tat, avg_wt;

void Read_Process(struct Process **p, int n);
void Sort_Process(struct Process **p, struct Process **q, int n);
void Round_Robin(struct Process **p, int n, int t);
void Gantt_Chart(struct Process **p, int n, int t);
void TAT_WT(struct Process **p, int n);

void EnQueue(struct Process *p, int n){
    if(rear == MAX-1){
        printf("\n The Queue is full! The Operation Cannot be completed!");
        exit(0);
    }
    else{
        if(front == -1){
            front = 0;
        }
        if(((q)[rear]).no == (*p).no){
            ((q)[rear]).bt = ((q)[rear]).bt + (*p).bt;
        }
        else{
            rear = rear + 1;

            (q)[rear] = *p;
        }
             
    }
}

void main(){
    int n, t;
    struct Process *p;
    p = (struct Process*)malloc(MAX * sizeof(struct Process));
    q = (struct Process*)malloc(MAX * sizeof(struct Process));

    printf("\n Enter the number of Processes: ");
    scanf("%d",&n);

    Read_Process(&p, n);                                            //Function Call to Read Processes

    printf("\n Enter the Time Quantum: ");
    scanf("%d",&t);

    Sort_Process(&p, &q, n);                                            //Function call to Sort Processes
    Round_Robin(&p, n, t);

    printf("\n Presenting The Gantt chart of Round Robin Scheduling! ");
    Gantt_Chart(&p, n, t);                                             //Function Call to Display the Gantt Chart

    

}

//Reads the Arrival Time, Burst Time and Priority of Processes
void Read_Process(struct Process **p, int n){

    for(int i = 1; i <= n; i++){
        printf("\n Enter the Arrival Time and  Burst Time of the Process %d:  ",i);
        scanf("%d%d",&(((*p)[i]).at),&(((*p)[i]).bt));

        ((*p)[i]).no = i;

        net_time = net_time + (((*p)[i]).bt);
    }

}

void Sort_Process(struct Process **p, struct Process **q, int n){

    for(int i = 1; i <= n; i++){
        int min_at = i;

        for(int j = i+1; j <= n; j++){

            if(((*p)[min_at]).at > ((*p)[j]).at){
                min_at = j;
            }

            if(min_at != i){
                int temp_no = (((*p)[i]).no);
                int temp_at = (((*p)[i]).at);
                int temp_bt = (((*p)[i]).bt);
               

                (((*p)[i]).no) = (((*p)[min_at]).no);
                (((*p)[i]).at) = (((*p)[min_at]).at);
                (((*p)[i]).bt) = (((*p)[min_at]).bt);
                

                (((*p)[min_at]).no) = temp_no;
                (((*p)[min_at]).at) = temp_at;
                (((*p)[min_at]).bt) = temp_bt;
            }
        }
    }
   
}

void Round_Robin(struct Process **p, int n, int t){
     int count = 0, complete = 0;
    for(int i = 1; ; i = (i%n)+1){
        if(((*p)[i]).bt > 0){
            struct Process *new;
            new = (struct Process*)malloc(sizeof(struct Process));
            new->at = ((*p)[i]).at;
            new->no = ((*p)[i]).no;
            
            if((((*p)[i]).bt) >= t){
                new->bt = t;
                count = count + t;
                //complete = complete + ((*p)[i]).bt;
                ((*p)[i]).bt = ((*p)[i]).bt - t;
            }
            else{
                new->bt = ((*p)[i]).bt;
                count = count + ((*p)[i]).bt;
                //complete = complete + ((*p)[i]).bt;
                //((*p)[i]).ct = complete;
                ((*p)[i]).bt = 0;

            } 
            EnQueue(new, n);
            
            if(count == net_time){
                break;
            }

        }
    }
    printf("\n The Ready Queue is :");
    for(int j = front; j <= rear; j++){
        printf("\n Process %d  At: %d Bt: %d",(q[j]).no,(q[j]).at,(q[j]).bt);
    }

}

void Gantt_Chart(struct Process **p, int n, int t){

    int temp = 0, sum_tat = 0, sum_wt = 0 ;
    printf("\n The Gantt chart of the RR is:\n ");
    printf("\n|0");
    for(int i = front; i <= rear; i++){

        temp = temp + (q[i]).bt;
        (q[i]).ct = temp;

        printf("\t|Process%d\t|%d",((q[i]).no),((q[i]).ct));

        
    
    }
    printf("|\n");

    
    
}

