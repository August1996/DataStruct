//
//  main.c
//  AM
//
//  Created by 余彬 on 15/7/10.
//  Copyright (c) 2015年 余彬. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>

typedef struct Card{
    int num;
    struct Card *pNext;
}Card,*pCard;

typedef struct Cards{
    pCard pHead;
}Cards,*pCards;

int Init(pCards pC){
    if(pC->pHead!=NULL){
        printf("The cards have been inited!\n");
        return 0;
    }else {
        pCard pNew,pOld;
        int i;
        for(i=1;i<=13;i++){
            pNew=(pCard)malloc(sizeof(Card));
            if(pNew==NULL){
                printf("Init Failed!\n");
                return 0;
            }else {
                pNew->pNext=NULL;
                pNew->num=0;
                if(i==1){
                    pC->pHead=pNew;
                    pOld=pNew;
                }else{
                    pOld->pNext=pNew;
                    pOld=pNew;
                }
            }
        }
        pNew->pNext=pC->pHead;
        return 1;
    }
}

int Order(pCards pC){
    if(pC->pHead==NULL){
        printf("The cards have not been inited!\n");
        return 0;
    }else {
        int i,j;
        pCard pTmp=pC->pHead;
        for(i=1;i<=13;i++){
            for(j=1;j<=i-1;pTmp=pTmp->pNext){
                if(pTmp->num==0)
                    j++;
            }
            while(pTmp->num!=0)
                pTmp=pTmp->pNext;
            pTmp->num=i;
            
        }
        return 1;
    }
}

int Show(pCards pC){
    if(pC->pHead==NULL){
        printf("The cards have not been inited!\n");
        return 0;
    }else {
        pCard pTmp=pC->pHead;
        printf("%d ",pTmp->num);
        pTmp=pTmp->pNext;
        while(pTmp!=pC->pHead){
            printf("%d ",pTmp->num);
            pTmp=pTmp->pNext;
        }
        printf("\n");
        return 1;
    }
}

int main(){
    Cards c;
    c.pHead=NULL;
    Init(&c);
    Order(&c);
    Show(&c);
    return 1;
}
