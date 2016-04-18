//
//  main.c
//  AM
//
//  Created by 余彬 on 15/7/10.
//  Copyright (c) 2015年 余彬. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int num;
    char name[32];
}Node,*pNode;

typedef struct	Queue{
    pNode pBase;
    int cnt;
    int size;
    int is_init;
}Queue,*pQueue;

int Create(pQueue Queue){
    if(Queue->is_init==1){
        printf("The queue may has been inited");
        return 0;
    }else {
        Queue->pBase=(pNode)malloc(sizeof(Node)*Queue->size);
        if(Queue==NULL){
            printf("Fail!\n");
            return 0;
        }else {
            int i;
            printf("Please enter the data as follow:1,xiaoming\n");
            for(i=0;i<(Queue->size);i++)
                scanf("%d,%s",&Queue->pBase[i].num,Queue->pBase[i].name);
            Queue->is_init=1;
            Queue->cnt=0;
            return 1;
        }
    }
}

int Show(pQueue Queue){
    int i;
    printf("Num	Name\n");
    for(i=Queue->cnt;i<Queue->size;i++)
        printf("%d\t%s\n",Queue->pBase[i].num,Queue->pBase[i].name);
    for(i=0;i<(Queue->cnt);i++)
        printf("%d\t%s\n",Queue->pBase[i].num,Queue->pBase[i].name);
    return 1;
}

int Set_cnt(pQueue Queue,int cnt){
    if(cnt<0 || cnt>(Queue->size)){
        printf("Error\n");
        return 0;
    }else{
        Queue->cnt=cnt-1;
        return 1;
    }
}

int In(pQueue Queue){
    Queue->pBase=(pNode)realloc(Queue->pBase,Queue->size+1);
    if(Queue==NULL){
        printf("Fail!\n");
        return 0;
    }else {
        printf("Please enter the data as follows:1,xiaoming\n");
        scanf("%d,%s",&Queue->pBase[Queue->size].num,Queue->pBase[Queue->size].name);
        Queue->size=Queue->size+1;
        return 1;
    }
}

int Out(pQueue Queue){
    if(Queue->size==0){
        printf("The queue is empty!\n");
        return 0;
    }else {
        Queue->pBase=&(Queue->pBase[1]);
        Queue->size=Queue->size-1;
        if(Queue->size==0){
            Queue->cnt=0;
            printf("The queue has been empty,the current has been setted into zero!\n");
        }	
        Queue->size=(Queue->size-1);
        return 1;
    }
}
int main(){
    Queue q;
    q.size=3;
    Create(&q);	
    Show(&q);
    /*	Set_cnt(&q,-1);
     Set_cnt(&q,4);
     Set_cnt(&q,2);	
     */	In(&q);
    Show(&q);
    Out(&q);
    Show(&q);
    return 0;
}
