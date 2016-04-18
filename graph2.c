//
//  main.c
//  AM2
//
//  Created by 余彬 on 15/7/10.
//  Copyright (c) 2015年 余彬. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Box{
    int size;
    char *VexTable;
    int **VexsTable;
}Box,*pBox;

int Get(char *pVT,char c,int size){
    int i;
    for(i=0;i<=size;i++)
        if(pVT[i]==c)
            break;
    
    if(pVT[i]==c)
        return 1;
    else return -1;
}

int Create(pBox pB){
    int i,j;
    char c,c1,c2;
    
    
    pB->VexTable=(char *)malloc(sizeof(char));
    pB->VexsTable=(int **)malloc(sizeof(int *)*(pB->size));
    for(i=0;i<(pB->size);i++)
        (pB->VexsTable)[i]=(int *)malloc(sizeof(int)*(pB->size));
    
    printf("Please enter the vexs name(Like abc represent a,b,c vexs):\n");
    scanf("%c",&c);
    i=0;
    while (c!='\n') {
        (pB->VexTable)[i]=c;
        i++;
        scanf("%c",&c);
    }
    
    printf("Please enter the vexs relation(Like a,b c,d)type 2 times Space to finish!:\n");
    scanf("%c,%c ",&c1,&c2);
    
    while(c1!='\n'){
        
        i=Get(pB->VexTable,c1,pB->size);
        j=Get(pB->VexTable,c2,pB->size);
        pB->VexsTable[i][j]=1;
        pB->VexsTable[j][i]=1;
        printf("Please enter the vexs relation(Like a,b c,d):\n");
        scanf("%c,%c",&c1,&c2);
    }
    
    return 1;
}


int main(int argc, const char * argv[]) {
    Box b;
    
    printf("Please enter the size of vexs:\n");
    scanf("%d",&(b.size));
    getchar();
    
    Create(&b);
    
    
    return 0;
}
