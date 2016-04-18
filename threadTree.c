//
//  main.c
//  AM
//
//  Created by 余彬 on 15/7/10.
//  Copyright (c) 2015年 余彬. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef enum Type{
    Thread,
    Link,
}Type;

typedef struct Node{
    char data;
    struct Node *lChild,*rChild;
    Type rTag;
    Type lTag;

}Node,*pNode;

pNode Pre;

void BuildTree(pNode *pN){
    char c;
    pNode pNew;
    scanf("%c",&c);
    
    if(c==' '){
        pN=NULL;
    }else if(c!='\n'){
        pNew=(pNode)malloc(sizeof(Node));
        pNew->rChild=pNew->lChild=NULL;
        pNew->lTag=pNew->rTag=Link;
        pNew->data=c;
        (*pN)=pNew;
        BuildTree(&pNew->lChild);
        BuildTree(&pNew->rChild);
    }
}

void ThrTree(pNode *pN){
    if((*pN)->lChild!=NULL && (*pN)->lTag==Link){
        ThrTree(&((*pN)->lChild));
    }
    
    if(Pre->rChild==NULL){
        Pre->rChild=*pN;
        Pre->rTag=Thread;
    }
    
    if((*pN)->lChild==NULL){
        (*pN)->lChild=Pre;
        (*pN)->lTag=Thread;
    }
    
    Pre=(*pN);
    
    if((*pN)->rChild!=NULL && (*pN)->rTag==Link){
        ThrTree(&((*pN)->rChild));
    }
}

int main(){
    pNode pHead;
    
    printf("Please enter the expression:\n");
    
    BuildTree(&pHead);
    
    Pre=pHead;
    ThrTree(&pHead);
    Pre->rChild=pHead;
    
    return 1;
}