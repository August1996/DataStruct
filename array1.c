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
    pNode pHead;
    int size;
}Table,*pTable;

pNode Create(int num){
    pNode pNew,pOld,pReturn;
    int count;
    pOld=pReturn=pNew;
    for(count=0;count<num;count++)
    {
        pNew=(pNode)malloc(sizeof(Node));
        if(pNew==NULL){
            printf("Fail!\n");
            return NULL;
        }else{
            printf("Please enter the num and name as the following regulation:1,xiaoming:\n");
            scanf("%d,%s",&pNew->num,pNew->name);
            if(count==0)
                pReturn=pOld=pNew;
            else
                pOld->pNext=pNew;
            pOld=pNew;
        }
    }
    pNew->pNext=NULL;
    return pReturn;
}

int Show(pTable table){
    pNode pTmp;
    pTmp=table->pHead;
    printf("Num	name\n");
    while(pTmp!=NULL){
        printf("%d\t%s\n",pTmp->num,pTmp->name);
        pTmp=pTmp->pNext;
    }
    return 1;
}

int Insert(pTable table,int pos){
    pNode pTmp,pTmp1,pNew;
    int i;
    if(pos>table->size+1){
        printf("The num is too large!\n");
        return 0;
    }else {
        pNew=(pNode)malloc(sizeof(Node));
        if(pNew==NULL){
            printf("Fail!\n");
            return 0;
        }else {
            if(pos==1){
                pNew->pNext=table->pHead;
                table->pHead=pNew;
            }else {
                for(i=1,pTmp=table->pHead;i<pos;i++,pTmp1=pTmp,pTmp=pTmp->pNext);
                if(pos==table->size+1){
                    pNew->pNext=NULL;
                    pTmp->pNext=pNew;
                }else{
                    pNew->pNext=pTmp1->pNext;
                    pTmp1->pNext=pNew;
                }
            }
            printf("Please enter the num and name as the following regulation:1,xiaoming:\n");
            scanf("%d,%s",&pNew->num,pNew->name);
        }
        table->size=table->size+1;
        return 1;
    }
}

int Delete(pTable table,int pos){
    int i;
    pNode pTmp,pTmp1;
    if(pos>table->size){
        printf("The position is too large!\n");
        return 0;
    }else {
        if(pos==1){
            table->pHead=table->pHead->pNext;
            return 1;
            table->size=table->size-1;
        }else {
            for(i=1,pTmp=table->pHead;i<table->size-1;i++,pTmp1=pTmp,pTmp=pTmp->pNext);
            if(pos==table->size){
                pTmp->pNext=NULL;
                return 1;;
                table->size=table->size-1;
            }else {
                pTmp1->pNext=pTmp->pNext;
                table->size=table->size-1;
                return 1;	
            }
        }
    }
}

int main(){
    Table table;
    table.size=3;
    table.pHead=Create(table.size);	
    Show(&table);
    /*	Insert(&table,1);
     Show(&table);
     Insert(&table,4);
     Show(&table);
     Insert(&table,2);
     Show(&table);	
     */
    Delete(&table,2);
    Show(&table);	
    return 0;
}
