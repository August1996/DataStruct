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
    struct Node * pNext;
}Node,*pNode;

typedef struct Stack{
    pNode pBase;
    pNode pOver;
}Stack,*pStack;

int Show(pStack Stack){
    pNode pTmp;
    if(Stack->pBase==NULL){
        printf("The Stack is empty!\n");
        return 0;
    }else {
        pTmp=Stack->pBase;
        while(pTmp!=NULL){
            printf("%d ",pTmp->num);
            pTmp=pTmp->pNext;
        }
        printf("\n");
        return 1;
    }
}

int Push(pStack Stack,int i){
    pNode pNew;
    pNew=(pNode)malloc(sizeof(Node));
    if(pNew==NULL){
        printf("Fail!\n");
        return 0;
    }else {
        pNew->num=i;
        if(Stack->pBase==NULL){
            Stack->pBase=Stack->pOver=pNew;
        }
        else {
            Stack->pOver->pNext=pNew;
            Stack->pOver=pNew;
        }
    }
    pNew->pNext=NULL;
    return 1;
}

int Pop(pStack Stack){
    pNode pTmp;
    if(Stack->pBase==NULL){
        printf("The stack has been empty!\n");
        return 0;
    }else {
        pTmp=Stack->pBase;
        if(Stack->pBase!=Stack->pOver){
            printf("%d ",Stack->pOver->num);
            while(pTmp->pNext!=(Stack->pOver))
                pTmp=pTmp->pNext;
            Stack->pOver=pTmp;
        }
        else {
            
            printf("%d ",Stack->pBase->num);
            Stack->pBase=Stack->pOver=NULL;
        }
    }
    return 1;
}

int main(){
    Stack s;
    s.pBase=s.pOver=NULL;
    int i;
    printf("Please enter a number(10):");
    scanf("%d",&i);
    while((i/2)>0){
        Push(&s,i%2);
        //	printf("%d",i%2);
        i=i/2;
    }
    //	printf("%d\n",i%2);
    Push(&s,i%2);
    //	Show(&s);	
    while(s.pBase!=NULL)
        Pop(&s);
    printf("\n");
    return 1;
}
