//
//  main.c
//  AM
//
//  Created by 余彬 on 15/7/10.
//  Copyright (c) 2015年 余彬. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Vex{
    char data;
    int * point;
}Vex,*pVex;

typedef struct Box{
    int size;
    pVex *pVexs;
}Box,*pBox;

int Create(pBox pB){
    pB->pVexs=(pVex*)malloc(sizeof(Vex)*(pB->size));
    if(pB==NULL){
        return 0;
    }else {
        int i;
        for(i=0;i<pB->size;i++){
         
        }
    }
    
    
    return 1;
}

int main(int argc, const char * argv[]) {
    Box b;
    
    printf("Please enter the number of vexs:\n");
    scanf("%d",&(b.size));
    Create(&b);
    
    return 0;
}
