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
        printf("The Cards have been inited!\n");
        return 0;
    }else {
        int i;
        pCard pNew,pOld;
        for(i=1;i<=41;i++){
            pNew=(pCard)malloc(sizeof(Card));
            if(pNew==NULL){
                printf("Inited Fail!\n");
                return 0;
            }else {
                pNew->pNext=NULL;
                if(i==1){
                    pC->pHead=pNew;
                    pOld=pNew;
                }else{
                    pOld->pNext=pNew;
                    pNew->pNext=NULL;
                    pOld=pNew;
                }
            }
            pNew->num=i;
        }
        pNew->pNext=pC->pHead;
        return 1;
    }
}

int KillOrder(pCards pC){
    if(pC->pHead==NULL){
        printf("The Cards have not been inited!\n");
        return 0;
    }else {
        pCard pTmp=pC->pHead,pTmp1;
        while(pTmp->pNext!=pTmp){
            pTmp=pTmp->pNext;
            pTmp1=pTmp->pNext;
            pTmp->pNext=pTmp1->pNext;
            printf("%d->",pTmp1->num);
            pTmp=pTmp->pNext;
            free(pTmp1);
        }	
        printf("%d\n",pTmp->num);
        return 1;
    }
}

int main(){
    Cards c;
    c.pHead=NULL;
    Init(&c);
    KillOrder(&c);
    return 1;
}
