//Program to implement First_Fit, Best Fit and Worst Fit

#include<stdio.h>
#include<stdlib.h>
#define MAX 10

//The Structure for the memory available
struct Memory{
    int space;
    int occupied;
    int process_no;
};

void First_Fit(struct Memory **mem, int pro[], int n_mem, int n_pro);
void Best_Fit(struct Memory **mem, int pro[], int n_mem, int n_pro);
void Worst_Fit(struct Memory **mem, int pro[], int n_mem, int n_pro);
void Display(struct Memory *mem, int n_mem);

void main(){

    int op;
    struct Memory *mem;
    int n_mem, n_pro, pro[10];

    while(1){

        printf("\n Enter the Memory Allocation Process to be implemented:");
        printf("\n1. First Fit Allocation\n2. Best Fit Allocation\n3. Worst Fit Allocation\n4. Exit\n");
        scanf("%d",&op);

        //Exits the loop if the option selected is 4
        if(op == 4){
            printf("\n Exiting!!");
            break;
        }

        //Segmentation of memory

        printf("\n Enter the number of memory segments in your memory: ");
        scanf("%d",&n_mem);

        if(n_mem > MAX){
            printf("\n This is max number of segments!");
            break;
        }

        if(n_mem == 0){
            printf("\n No memory Allocated!");
            exit(0);
        }

        if(n_mem < 0){
            printf("\n InValid Value");
            exit(0);
        }
        

        
        mem = (struct Memory*)malloc(n_mem * sizeof(struct Memory));

        printf("\n Enter the space allocated to each of these segments: ");
        for(int i = 1; i <= n_mem; i++){
            printf("\n Space allocated to segment %d: ",i);
            scanf("%d",(&(mem[i].space)));

             if((mem[i].space)<0){
                printf("\n Ivalid Value for memory! ");
                exit(0);
            }
            
            mem[i].occupied = 0;
            mem[i].process_no = 0;
        }

        //Memory Allocated To the Processes
        printf("\n Enter the number of processes to be allocated in the memory: ");
        scanf("%d",&n_pro);

        if(n_pro > MAX){
            printf("\n This is has exceeded max number of segments!");
            break;
        }

        if(n_mem < 0){
            printf("\n InValid Value");
            exit(0);
        }

        

       //pro = (int*)malloc(10 * sizeof(int));

        printf("\n Enter the memory required by each of the processes: ");
        for(int i = 1; i <= n_pro; i++){
            printf("\n Enter the memory required for Process %d:  ",i);
            scanf("%d",&pro[i]);
            if(pro[i]<0){
                printf("\n Invalid Value for memory! ");
                exit(0);
            }
        }

        switch(op){

            case 1:
            {
                printf("\n First Fit Allocation \n");
                First_Fit(&mem,pro,n_mem,n_pro);

                printf("\n After First Fit Allocation: \n ");
                Display(mem, n_mem);

                free(mem);

                break;
            }

            case 2:
            {
                printf("\n Best Fit Allocation \n");
                Best_Fit(&mem,pro,n_mem,n_pro);

                printf("\n After Best Fit Allocation: \n ");
                Display(mem, n_mem);

                
                break;
            }
            case 3:
            {
                printf("\n Worst Fit Allocation \n");
                Worst_Fit(&mem,pro,n_mem,n_pro);

                printf("\n After Worst Fit Allocation: \n ");
                Display(mem, n_mem);

                break;
            }

            default:
            {
                printf("\n Invalid Option! Try Again! ");
                break;
            }
        }
    }
}

void Display(struct Memory *mem, int n_mem){

    for(int i = 1; i <= n_mem; i++){
        if(mem[i].occupied != 0){
            printf("\n | Process %d | Remaining Space: %d |",mem[i].process_no,mem[i].space);
        }
        else{
            printf("\n | Unoccupied Memory ! Space: %d |",(mem[i]).space);
        }
        printf("\n");
    }

}

void First_Fit(struct Memory **mem , int pro[], int n_mem, int n_pro){

    for(int j = 1; j <= n_pro; j++){
        int count = 0;
        for(int k = 1; k <= n_mem; k++){
            //Checking if the process fits in unoccupied memory block
            if((((*mem)[k]).space >= pro[j])&&(((*mem)[k]).occupied == 0)){
                
                ((*mem)[k]).space = ((*mem)[k]).space - pro[j];
                ((*mem)[k]).occupied = 1;
                ((*mem)[k]).process_no = j;
                
                count++;
                break;
            }
        }
        
        if(count == 0){
            printf("\n Process %d of size %d could not be allocated!\n",j,pro[j]);
            break;
        }
    }
}

void Best_Fit(struct Memory **mem, int pro[], int n_mem, int n_pro){

    int closest;
    for(int i = 1; i <= n_pro; i++){

        closest = 0;

        for(int j = 1; j <= n_mem; j++){
            
            //printf("\n ((*mem)[j]).space = %d pro[i]=%d ((*mem)[j]).occupied=%d",((*mem)[j]).space,pro[i],((*mem)[j]).occupied);
            if((((*mem)[j]).space >= pro[i])&&(((*mem)[j]).occupied == 0)){
                
                //printf("\n ((*mem)[j]).space=%d ((*mem)[closest]).space=%d closest=%d",((*mem)[j]).space,((*mem)[closest]).space,closest);
                if(closest != 0){
                    if(((*mem)[j]).space < ((*mem)[closest]).space){
                        closest = j;
                    }
                }
                else{
                   closest = j;
                }
            }
        }

        if(closest != 0){
            if((((*mem)[closest]).space >= pro[i])&&(((*mem)[closest]).occupied == 0)){
                ((*mem)[closest]).space = ((*mem)[closest]).space - pro[i];
                ((*mem)[closest]).occupied = 1;
                ((*mem)[closest]).process_no = i;
            }else{
                printf("\n Process %d cannot be allocated!\n",i);
            }
        }
        else{
            printf("\n Process %d cannot be allocated!\n",i);
        }

        
    }
}

void Worst_Fit(struct Memory **mem, int pro[], int n_mem, int n_pro){

    int largest;
    for(int i =1; i <= n_pro; i++){
        largest = 0;
        for( int j=1; j<= n_mem; j++){
            
            
            if((((*mem)[j]).space >= pro[i])&&(((*mem)[j]).occupied == 0)){  
                
                if(largest != 0){
                   
                    if(((*mem)[j].space) > (((*mem)[largest]).space)){
                        largest = j;
                        
                    }
                }
                else{
                    largest = j;
                }
            }

            
        }
        if(largest != 0){
                ((*mem)[largest]).space = ((*mem)[largest]).space - pro[i];
                ((*mem)[largest]).occupied = 1;
                ((*mem)[largest]).process_no = i;
            }
            else{
                printf("\n The Process %d could not be allocated!\n",i);
                break;
            }
    }
}