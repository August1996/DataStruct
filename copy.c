//
//  main.c
//  copy
//
//  Created by 余彬 on 15/7/24.
//  Copyright (c) 2015年 余彬. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int b;
    FILE *s,*d;
    
    if(argc!=3){
        fprintf(stderr, "请按照格式输入（copyfile source destination）：\n");
        return 0;
    }
    
    if(!(s=fopen(argv[1], "rb"))){
        fprintf(stderr, "Open file %s error!",argv[1]);
        return 0;
    }
    
    if(!(d=fopen(argv[2], "wb"))){
        fprintf(stderr, "Open file %s error!",argv[2]);
        return 0;
    }
    
    b=getc(s);
    
    while (b!=EOF) {
        putc(b, d);
        b=getc(s);
    }
    
    fclose(s);
    fclose(d);
    
    return 1;
    
}
