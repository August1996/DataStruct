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
    if(pS->pBase==NULL)
        return 0;
    else {
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
    char c,c1;
    Stack s;
    s.pBase=s.pOver=NULL;
    printf("Please enter an expression:\n");
    scanf("%c",&c);
    while(c!='$'){
        if(c>='0' && c<='9'){
            while(c>='0' && c<='9'){
                printf("%c",c);
                scanf("%c",&c);
            }
            printf(" ");
            continue;
        }else {
            switch (c) {
                case '+':
                case '-':
                    while(Pop(&s,&c1) && c1!='('){
                        printf("%c ",c1);
                    }
                    if(c1=='(')
                        Push(&s, '(');
                    Push(&s,c);
                    break;
                case '*':
                case '/':
                case '(':
                    Push(&s,c);
                    break;
                case ')':
                    Pop(&s,&c1);
                    while(c1!='('){
                        printf("%c ",c1);
                        Pop(&s, &c1);
                    }
                    break;
                default:
                    break;
            }
        }
        scanf("%c",&c);
        
    }
    while(Pop(&s, &c1))
        printf("%c ",c1);
    printf("\n");
    return 1;
}
