//Program for implementing FIFO page replacement algorithm

#include<stdio.h>
#include<stdlib.h>


void Read_Pages(int n, int pages[n]);
int FIFO(int n , int pages[n], int frames, int cq[frames], int *front, int *rear);
void Enqueue(int frames, int cq[frames],int *front, int *rear, int item);
void Dequeue(int frames, int cq[frames],int *front, int *rear);
int Search(int frames, int cq[frames], int item);
void Display(int frames, int cq[frames], int *front, int *rear);

void main(){

    int frames, n,rear = -1,front = -1, no_of_page_faults= 0;

    printf("\n Enter the number of pages: ");
    scanf("%d",&n);

    if(n == 0){
        printf("\n No pages! Exiting!");
        exit(0);
    }
    if(n < 0){
        printf("\n Invalid Number! Exiting!");
        exit(0);
    }

    int pages[n];

    printf("\n Enter the pages: ");;
    Read_Pages(n, pages);

    /*printf("\n The Entered pages are: ");
    for(int i = 0 ; i < n; i++){
        printf("\nPage%d: %d",i,pages[i]);
    }*/

    printf("\n Enter the number of frames: ");
    scanf("%d",&frames);

    if(frames <= 0){
        printf("\n Invalid Number for frames!");
    }

    int cq[frames];
    for(int j = 0; j < frames; j++){
        cq[j] = -1;
    }

    printf("\n Undergoing page replacement algorithm: ");
    no_of_page_faults = FIFO(n, pages, frames, cq, &front, &rear);

    printf("\n The number of page faults in FIFO algorithm are: %d",no_of_page_faults);


}

void Read_Pages(int n, int pages[n]){
    for(int i = 0 ; i < n; i++){
        printf("\nPage%d: ",i);
        scanf("%d",&pages[i]);
    }
}

int FIFO(int n , int pages[n], int frames, int cq[frames], int *front, int *rear){


    int no_of_frames = 0;
    for(int i = 0; i < n; i++){
        if(Search(frames,cq,pages[i])==0){
            if((*rear +1) % frames == *front ){
                Dequeue(frames,cq,front,rear);
            }
        
            Enqueue(frames,cq,front,rear,pages[i]);
            printf("\n");
            Display(frames,cq,front,rear);  
            
            no_of_frames++;    
        }
    }
    return no_of_frames;
}

void Enqueue(int frames, int cq[frames],int *front, int *rear, int item){

    if(*rear < frames){
        if(*front == -1){
            *front = 0;
            *rear = 0;
        }
        else{
            *rear = (*rear+1)%frames;
        }
        cq[*rear] = item;
    }
    else{
        printf("\n Exceeded limits!");
    }
}

void Dequeue(int frames, int cq[frames],int *front, int *rear){
    if(*front != -1){
        if(*front == *rear){
            *front = -1;
            *rear  = -1;
        }
        else{
            *front = (*front+1)%frames;
        }
    }
    else{
        printf("\n Empty Queue");
    }
}

int Search(int frames, int cq[frames], int item){
    for(int i = 0; i< frames; i++){
        if(cq[i] == item)
            return 1;
    }
    return 0;
}

void Display(int frames, int cq[frames], int *front, int *rear){

    for(int i = 0; i < frames; i++){
        if(cq[i] != -1){
            printf("|%d\t",cq[i]);
        }
        else{
            printf("\t");
        }
        
    }
}