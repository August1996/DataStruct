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
    char c;
    struct Node *pNext;
}Node,*pNode;

typedef struct Stack{
    pNode pBase;
    pNode pOver;
}Stack,*pStack;

int Push(pStack pS,char c){
    pNode pNew;
    pNew=(pNode)malloc(sizeof(Node));
    if(pNew==NULL){
        printf("Fail!\n");
        return 0;
    }else {
        pNew->c=c;
        pNew->pNext=NULL;
        if(pS->pBase==NULL){
            pS->pBase=pS->pOver=pNew;
        }else{
            pS->pOver->pNext=pNew;
            pS->pOver=pNew;
        }
        return 1;
    }
}

int Pop(pStack pS,char *c){
    if(pS->pBase==NULL){
        return 0;
    }else {
        *c=pS->pOver->c;
        if(pS->pBase==pS->pOver){
            free(pS->pOver);
            pS->pBase=pS->pOver=NULL;
        }else {
            pNode pTmp=pS->pBase;
            while(pTmp->pNext!=pS->pOver)
                pTmp=pTmp->pNext;
            free(pS->pOver);
            pTmp->pNext=NULL;
            pS->pOver=pTmp;
        }
        return 1;
    }
}


int main(){
    char c;
    Stack s;
    s.pBase=s.pOver=NULL;
    printf()
    return 1;
}
