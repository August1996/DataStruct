//
//  main.c
//  hfm
//
//  Created by 余彬 on 15/7/12.
//  Copyright (c) 2015年 余彬. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TYPE char
#define Input "abc"

typedef struct Node{
    TYPE data;
    int pri;
    struct Node *Right,*Left,*pNext;
}Node,*pNode;

typedef struct Queue{
    pNode pHead;
    int EleSize;
}Queue,*pQueue;


typedef struct TNode{
    char *code;
    TYPE data;
    struct TNode *pNext;
}TNode,*pTNode;

typedef struct TTable{
    int size;
    pTNode pHead;
}TTable,*pTTable;


int InOrder(pQueue pQ,TYPE data,int pri,pNode Left,pNode Right,int IsChange){
    if(pQ==NULL){
        printf("The pQueue is invalid!\n");
        return 0;
    }else {
        pNode pNew;
        pNew=(pNode)malloc(sizeof(Node));
        if(pNew==NULL){
            printf("Memory requestion is failed!\n");
            return 0;
        }else {
            pNew->data=data;
            pNew->Left=Left;
            pNew->Right=Right;
            pNew->pNext=NULL;
            pNew->pri=pri;
            if(pQ->pHead==NULL){
                pQ->pHead=pNew;
                if(IsChange==1)
                    pQ->EleSize=1;
            }else {
                pNode pQmp,pPre;
                pQmp=pPre=pQ->pHead;
                while(pQmp!=NULL && pNew->pri>pQmp->pri){
                    pPre=pQmp;
                    pQmp=pQmp->pNext;
                }
                if(pQmp==NULL)
                    pPre->pNext=pNew;
                else{
                    pNew->pNext=pQmp;
                    
                    if(pQmp==pPre)
                        pQ->pHead=pNew;
                    else pPre->pNext=pNew;
                }
                if(IsChange==1)
                    pQ->EleSize++;
            }
            return 1;
        }
    }
}

int Out(pQueue pQ,pNode *pR){
    (*pR)=NULL;
    if(pQ==NULL){
        printf("The pointer is invalid!\n");
        return 0;
    }else if(pQ->pHead==NULL){
        return 0;
    }else {
        (*pR)=pQ->pHead;
        if(pQ->pHead->pNext==NULL)
            pQ->pHead=NULL;
        else pQ->pHead=pQ->pHead->pNext;
        (*pR)->pNext=NULL;
        return 1;
    }
}

int BuildQueue(pQueue pQ,char *input){
    int i[128]={0},k;
    
    for(k=0;input[k];k++){
        i[input[k]]++;
    }
    
    for(k=0;k<=127;k++){
        if(i[k]!=0)
            InOrder(pQ,(unsigned char)k,i[k],NULL,NULL,1);
    }
    return 1;
}

int BuildTree(pQueue pQ){
    if(pQ==NULL){
        printf("The pointer is invalid!\n");
        return 0;
    }else {
        pNode pNew,pN1,pN2;
        while(pQ->pHead->pNext!=NULL){
            pNew=(pNode)malloc(sizeof(Node));
            if(pNew==NULL){
                printf("Memory requestion is failed!\n");
                return 0;
            }else {
                Out(pQ,&pN1);
                Out(pQ,&pN2);
                InOrder(pQ,'\0',pN1->pri+pN2->pri,pN1,pN2,0);
            }
        }
        return 1;
    }
}

int AddCode(char **code,char c){
    (*code)=(char *)realloc(*code,sizeof(**code)+sizeof(char)*1);
    (*code)[sizeof(**code)/sizeof(char)-2]=c;
    (*code)[sizeof(**code)/sizeof(char)-1]='\0';
    return 1;
}

int AddTNode(pTTable pTT,char *code,TYPE data){
    pTNode pNew,pTmp;
    if(pTT==NULL)
        return 0;
    else {
        pNew=(pTNode)malloc(sizeof(TNode));
        if(pNew==NULL)
            return 0;
        else {
            pNew->code=code;
            pNew->data=data;
            pNew->pNext=NULL;
            if(pTT->pHead==NULL)
                pTT->pHead=pNew;
            else {
                pTmp=pTT->pHead;
                while(pTmp->pNext!=NULL)
                    pTmp=pTmp->pNext;
                pTmp->pNext=pNew;
                
            }
        }
        return 1;
    }
}

int GetLen(char *code){
    if(code==NULL)
        return -1;
    else {
        char c;
        int len=0;
        c=code[0];
        while(c!='\0'){
            len++;
            c=code[len];
        }
        return len;
    }
}

int Travel(pNode p,pTTable pTT,char *code,char LoR){
    if(p==NULL)
        return 0;
    else {
        char *C_code;
        if(p->Left!=NULL){
            
            C_code=(char *)malloc(GetLen(code)+sizeof(char));
            strcpy(C_code,code);
            C_code[GetLen(code)]='0';
            C_code[GetLen(code)+1]='\0';
            Travel(p->Left,pTT,C_code,'0');
        }
        
        if(p->data!='\0')
            AddTNode(pTT,code,p->data);
        
        if(p->Right!=NULL){
            C_code=(char *)malloc(sizeof(*code)+sizeof(char));
            strcpy(C_code,code);
            C_code[GetLen(code)]='1';
            C_code[GetLen(code)+1]='\0';
            Travel(p->Right,pTT,C_code,'1');
        }
    }
    return 1;
}



int BuildTable(pQueue pQ,pTTable pTT){
    if(pQ==NULL || pTT==NULL)
        return 0;
    else {
        char *code;
        code=(char*)malloc(sizeof(char));
        code[0]='\0';
        pTT->size=pQ->EleSize;
        Travel(pQ->pHead,pTT,code,'0');
        return 1;
    }
    
}

char *GetCode(pTTable pTT,char c){
    pTNode pTmp;
    pTmp=pTT->pHead;
    while(pTmp->pNext!=NULL && pTmp->data!=c)
        pTmp=pTmp->pNext;
    if(pTmp->data!=c)
        return NULL;
    else return pTmp->code;
}

char * ComCode(char *input1,char *input2){
    int i,j,len1,len2;
    char *pR;
    len1=GetLen(input1);
    len2=GetLen(input2);
    pR=(char *)malloc(len1+len2+sizeof(char)*1);
    if(pR==NULL)
        return NULL;
    else{
        for(i=0,j=0;j<len1;j++,i++)
            pR[i]=input1[j];
        for(j=0;j<len2;j++,i++)
            pR[i]=input2[j];
        pR[i]='\0';
        return pR;
    }
}

char * Encode(pTTable pTT,char *input){
    char c,*code;
    int i=0;
    c=input[i++];
    code=GetCode(pTT, c);
    while(c!='\0'){
        c=input[i++];
        code=ComCode(code, GetCode(pTT, c));
    }
    return code;
}

char *Decode(pQueue pQ,char *code){
    char c,*d;
    int i=0,j=0;
    d=(char*)malloc(sizeof(char));
    d[j++]='\0';
    pNode pTmp=pQ->pHead;
    c=code[i];
    while (c!='\0' && pTmp!=NULL){
        c=code[i];
        if(pTmp->data!='\0'){
            d=ComCode(d, &pTmp->data);
            pTmp=pQ->pHead;
        }
        else if(c=='0'){
            pTmp=pTmp->Left;
            i++;
        }else if(c=='1'){
            pTmp=pTmp->Right;
            i++;
        }
        
    }
    return d;
}

int main(){
    
    Queue q;
    TTable tt;
    tt.pHead=NULL;
    q.pHead=NULL;
    printf("Building a queue for the input......\n\n");
    BuildQueue(&q,"abbccc");
    
    printf("Building a tree for the queue......\n\n");
    BuildTree(&q);
    
    printf("Building a table for tree......\n\n");
    BuildTable(&q,&tt);
    
    printf("Everything has been built.\n\n\n");
    
    printf("Source:%s\n",Input);
    printf("Encode:%s\n",Encode(&tt,Input));
    printf("Decode:%s\n",Decode(&q, Encode(&tt,Input)));
    
    
    return 0;
}
