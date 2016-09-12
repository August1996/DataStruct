//
//  main.cpp
//  MiddleExpress
//
//  Created by 余彬 on 16/9/7.
//  Copyright © 2016年 余彬. All rights reserved.
//

#include <iostream>
using namespace std;

int getRecentChar(char *stack,int *top){
    int index = -1;
    for(int i = *top - 1;i >= 0;i--){
        char c = *(stack + i);
        if(c == '(' || c == '+' || c == '-'){
            break;
        }else if(c == '*' || c == '/'){
            index = i;
            break;
        }
    }
    return index;
}


void countUntilLeftSign(char *stack,int *top){
    char c;
    char sign;
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    while (true) {
        c = stack[--(*top)];
        num2 = c - '0';
        sign = stack[--(*top)];
        c = stack[--(*top)];
        num1 = c - '0';
        if(sign == '+'){
            num3 = num1 + num2;
        }else if(sign == '-'){
            num3 = num1 - num2;
        }else if(sign == '*'){
            num3 = num1 * num2;
        }else if(sign == '/'){
            num3 = num1 / num2;
        }
        c = stack[(*top) - 1];
        if(c == '('){
            stack[(*top) - 1] = num3 + '0';
            break;
        }else{
            stack[(*top)++] = num3 + '0';
        }
    }
}

void countAllMutiAndDev(char *stack,int *top){
    char sign;
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    char c;
    sign = stack[getRecentChar(stack, top)];
    while ((sign == '/') || sign == '*') {
        c = stack[--(*top)];
        num2 = c - '0';
        --(*top);
        c = stack[--(*top)];
        num1 = c - '0';
        if(sign == '/'){
            num3 = num1 / num2;
        }else if(sign == '*'){
            num3 = num1 * num2;
        }
        stack[(*top)++] = num3 + '0';
        sign = stack[getRecentChar(stack, top)];
    }

}

int countAll(char *stack,int *top){
    char sign;
    int num1 = 0;
    int num2 = 0;
    int result = 0;
    char c;
    if(*top == 1){
        result = stack[--(*top)];
    }else{
        while (*top > 1) {
            c = stack[--(*top)];
            num2 = c - '0';
            sign = stack[--(*top)];
            c = stack[--(*top)];
            num1 = c - '0';
            if(sign == '+'){
                result = num1 + num2;
            }else if(sign == '-'){
                result = num1 - num2;
            }else if(sign == '*'){
                result = num1 * num2;
            }else if(sign == '/'){
                result = num1 / num2;
            }
            stack[(*top)++] = result + '0';
        }
    }
    return result;
}

int main(int argc, const char * argv[]) {
    
    char c;
    char stack[1024];
    int top = 0;
    int cntChar = -1;
    
    cout<<"请输入表达式并以#结束：";
    
    while ((cin>>c) && c != '#') {
        if((c >= '0' && c <= '9') || (c == '*' || c == '/' || c == '(')){
            stack[top++] = c;
        }else if(c == ')'){
            countUntilLeftSign(stack, &top);
        }else if(c == '+' || c == '-'){
            cntChar = getRecentChar(stack, &top);
            if(cntChar != -1){
                if(stack[cntChar] == '*' || stack[cntChar] == '/'){
                    countAllMutiAndDev(stack, &top);
                    stack[top++] = c;
                }
            }else{
                stack[top++] = c;
            }
        }
    }
    cout<<countAll(stack, &top)<<endl;
    return 0;
}


