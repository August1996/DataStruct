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
    struct Node * pNext;
}Node,*pNode;

typedef struct Queue{
    int size;
    pNode pBase;
}Queue,*pQueue;

int Create(pQueue Queue){
    pNode pNew,pOld;
    int i;
    if(Queue->size==0){
        printf("There is no need to create a queue.\n");
        return 0;
    }else {
        for(i=0;i<Queue->size;i++){
            pNew=(pNode)malloc(sizeof(Node));
            if(pNew==NULL){
                printf("Fail!\n");
                return 0;
            }else {
                if(i==0)
                    (Queue->pBase)=pOld=pNew;
                else pOld->pNext=pNew;
                pNew->pNext=NULL;
                pOld=pNew;
                printf("Please enter the data as follows:1,xiaoming\n");
                scanf("%d,%s",&pNew->num,pNew->name);
            }
        }
        pNew->pNext=NULL;
        return 1;
    }
}


int Show(pQueue Queue){
    pNode pTmp;
    pTmp=Queue->pBase;
    printf("Num	Name\n");
    while(pTmp!=NULL){
        printf("%d\t%s\n",pTmp->num,pTmp->name);
        pTmp=pTmp->pNext;
    }
    return 1;
}

int In(pQueue Queue){
    pNode pTmp,pNew;
    pTmp=Queue->pBase;
    while(pTmp->pNext!=NULL)
        pTmp=pTmp->pNext;
    pNew=(pNode)malloc(sizeof(Node));
    if(pNew==NULL){
        printf("Fail!\n");
        return 0;
    }else{
        pTmp->pNext=pNew;
        pNew->pNext=NULL;
        printf("Please enter the data as follows:1,xiaoming\n");
        scanf("%d,%s",&pNew->num,pNew->name);
    }
    return 1;
}

int Out(pQueue Queue){
    if(Queue->pBase==NULL){
        printf("There is no need to out a data");
        return 0;
    }else {
        Queue->pBase=Queue->pBase->pNext;
    }
    return 1;
}

int main(){
    Queue q;
    q.size=3;
    Create(&q);
    Show(&q);
    In(&q);
    Show(&q);
    Out(&q);
    Show(&q);
    return 0;
    return 0;
}
