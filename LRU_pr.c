//Program to implement LRU page replacement algorithm

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 50

int Search(int frames, int queue[frames], int item){

    for(int i=0; i<frames;i++){
        if(queue[i] == item)
            return 1;
    }
    return 0;
}

int Check_Capacity(int frames,int queue[frames]){
    for(int i=0;i<frames;i++){
        if(queue[i] == -1)
            return 1;
    }
    return 0;
}

int Find(int frames,int queue[frames], int element){
    for(int i = 0;i< frames;i++){
        if(queue[i] == element)
            return i;
    }
    return 0;
}

int Replace_Index(int n,int pages[n],int frames,int queue[frames],int limit){

    int min = limit;
    for(int i = 0 ;i< frames; i++){
        for(int j = limit-1; j>=0;j--){
            int item = pages[j];
            if(queue[i] == item){
                int index = j;

                if(index < min){
                    min = index;
                }
                break;
            }
        }
    }
    int element = pages[min];
    int replace = Find(frames,queue,element);

    return replace;

}

int Display(int frames, int queue[frames]){

    for(int i = 0; i< frames; i++){
        if(queue[i] != -1)
            printf("%d\t",queue[i]);
        else
            printf("\t");
    }
}

int LRU(int n,int pages[n], int frames, int queue[frames]){

    int page_faults = 0, k=0;
    for(int i =0 ;i<n;i++){
        int pageno = pages[i];
        if(Search(frames,queue,pageno) == 0){                     //Checking whether element is present in frame
            if(Check_Capacity(frames,queue) == 0){                 //Checking if frame is filled upto capacity

                int index = Replace_Index(n,pages,frames,queue,i);      //Condition when frame is filled
                queue[index] = pageno;                
            }
            else{
                queue[k] = pageno;
                k++;
            }
            printf("\n");
            Display(frames,queue);
            page_faults++;                  
        }       
    }
    return page_faults;
}

void main(){

    int frames,n;
    
    printf("\n Enter the number of pages: ");
    scanf("%d",&n);

    int pages[n];
    printf("\n Enter the referential string: ");
    for(int i = 0;i<n;i++){
        scanf("%d",&pages[i]);
    }

    printf("\n Enter the number of frames: ");
    scanf("%d",&frames);

    if(frames <= 0){
        printf("\n Invalid Value!");
        exit(0);
    }

    int queue[frames];
    for(int i = 0; i< frames;i++)
        queue[i] = -1;

    int page_faults = LRU(n,pages,frames,queue);

    printf("\n\nThe number of page faults are: %d",page_faults);

}

