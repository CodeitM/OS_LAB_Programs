//Program to implement LFU page replacement algorithm

#include<stdio.h>
#include<stdlib.h>

struct Page{
    int value;
    int frequency;
    int index;
};

int Search(int frames,struct Page queue[frames],int item){
    for(int i =0; i<frames;i++){
        if(queue[i].value == item){
            queue[i].frequency++;
            //queue[i].index = ind;
            return 1;
        }
            
    }
    return 0;
}

int Check_Capacity(int frames, struct Page queue[frames]){
    for(int i=0;i<frames;i++){
        if(queue[i].value == -1)
            return 1;
    }
    return 0;
}

int Least_Frequency(int frames, struct Page queue[frames]){
    int min= frames-1;

    for(int i = 0;i <frames;i++){

        if(queue[i].frequency < queue[min].frequency){
            min = i;
        }
        else if(queue[i].frequency == queue[min].frequency){
            if(queue[i].index < queue[min].index){
                min = i;            
            }
        }    
    }
    return min;
}

int Display(int frames, struct Page queue[frames]){

    for(int i = 0; i< frames; i++){
        if(queue[i].value != -1)
            printf("%d\t",queue[i].value);
        else
            printf("\t");
    }
}

int LFU(int n, int pages[n],int frames, struct Page queue[frames]){

    int page_faults = 0, k = 0;

    for(int i = 0; i<n; i++){
        if(Search(frames,queue,pages[i]) == 0){             //Checking if the value is already in
            if(Check_Capacity(frames,queue) == 0){          //Checking if capacity is not filled
                int ind = Least_Frequency(frames,queue);
                queue[ind].value = pages[i];
                queue[ind].frequency = 1;
                queue[ind].index= k++;
            }
            else{
                queue[k].value = pages[i];
                queue[k].frequency = 1;
                queue[k].index= k;
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

    int n,frames;

    printf("\n Enter the number of pages: ");
    scanf("%d",&n);

    int pages[n];

    printf("\n Enter the referential string: ");
    for(int i = 0; i<n;i++){
        scanf("%d",&pages[i]);
    }

    printf("\n Enter the number of frames: ");
    scanf("%d",&frames);+

    struct Page queue[frames];

    for(int i = 0;i<frames;i++){
        queue[i].value = -1;
        queue[i].frequency = 0;
        queue[i].index = -1;
    }

    int page_faults = LFU(n,pages,frames,queue);

    printf("\n The number of page faults are: %d",page_faults);
}