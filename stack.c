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

typedef struct Table{
    pNode pBase;
    pNode pOver;
    int size;
}Stack,*pStack;

int Create(pStack Stack){
    int i;
    pNode pNew,pOld,pTmp;
    if(Stack->size==0){
        printf("Please don't create an empty stack!\n");
        return 0;
    }else {
        for(i=0;i<Stack->size;i++){
            pNew=(pNode)malloc(sizeof(Node));
            if(pNew==NULL){
                printf("Fail!\n");
                return 0;
            }else {
                if(i==0)
                    Stack->pBase=pNew;
                else pOld->pNext=pNew;
                pOld=pNew;
                printf("Please enter the data as follow:1,xiaoming\n");
                scanf("%d,%s",&pNew->num,pNew->name);
            }
        }
        Stack->pOver=pNew;
        pNew->pNext=NULL;
        return 1;
    }
    
}

int Show(pStack Stack){
    pNode pTmp;
    if(Stack->size==0){
        printf("The Stack is empty!\n");
        return 0;
    }else {
        pTmp=Stack->pBase;
        printf("Num	Name\n");
        while(pTmp!=NULL){
            printf("%d\t%s\n",pTmp->num,pTmp->name);
            pTmp=pTmp->pNext;
        }
        printf("pStack:\npBase:%p\tpOver%p\tsize:%d\n",Stack->pBase,Stack->pOver,Stack->size);
        return 1;
    }
}

int Push(pStack Stack){
    pNode pNew;
    pNew=(pNode)malloc(sizeof(Node));
    if(pNew==NULL){
        printf("Fail!\n");
        return 0;
    }else {
        printf("Please enter the data as follow:1,xiaoming\n");
        scanf("%d,%s",&pNew->num,pNew->name);
        Stack->size=(Stack->size)+1;
        Stack->pOver->pNext=pNew;
        Stack->pOver=pNew;
    }
    pNew->pNext=NULL;
    return 1;
}

int Pop(pStack Stack){
    pNode pTmp;
    if(Stack->size==0){
        printf("The stack has been empty!\n");
        return 0;
    }else {
        pTmp=Stack->pBase;
        while(pTmp!=(Stack->pOver))
            pTmp=pTmp->pNext;
        Stack->pOver=pTmp;
        Stack->size=(Stack->size)-1;
    }
    return 1;
}

int main(){
    Stack s;
    s.size=3;
    Create(&s);
    Show(&s);
    
    Push(&s);
    Show(&s);
    
    Pop(&s);
    Pop(&s);
    Pop(&s);
    Show(&s);
    
    Pop(&s);
    Pop(&s);
    Show(&s);
    return 1;
}
