//
//  main.c
//  AM
//
//  Created by 余彬 on 15/7/10.
//  Copyright (c) 2015年 余彬. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>

typedef struct BTNode{
    char data;
    struct BTNode * rChild;
    struct BTNode * lChild;
}BTNode,*pBTNode;

int Create(pBTNode *root){
    char c;
    scanf("%c",&c);
    if(c!=' '){
        (*root)=(pBTNode)malloc(sizeof(BTNode));
        if((*root)==NULL){
            printf("Error!\n");
            exit(0);
        }else{
            (*root)->data=c;
            Create((*root)->lChild);
            Create((*root)->rChild);
            return 1;
        }
    }else (*root)=NULL;
    return 1;
}

void PreVisit(pBTNode pN){
    printf("%c",pN->data);
    if(pN->lChild!=NULL)
        PreVisit(pN->lChild);
    if(pN->rChild!=NULL)
        PreVisit(pN->rChild);
}

int main(){
    pBTNode t;
    Create(t);
    PreVisit(t);
    return 1;
}
