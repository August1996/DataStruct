//
//  main.cpp
//  BackExpression
//
//  Created by 余彬 on 16/9/8.
//  Copyright © 2016年 余彬. All rights reserved.
//

#include <iostream>
using namespace std;
int main(int argc, const char * argv[]) {
    
    char c;
    char stack[1024];
    int top = 0;
    cin>>c;
    while (c != '#') {
        
        if(c >= '0' &&c <= '9'){
            stack[top++] = c;
        }else{
            int num1,num2,num3;
            num2 = stack[--top] - '0';
            num1 = stack[--top] - '0';
            if(c == '+'){
                num3 = num1 + num2;
            }else if(c == '-'){
                num3 = num1 - num2;
            }else if(c == '*'){
                num3 = num1 * num2;
            }else if(c == '/'){
                num3 = num1 / num2;
            }
            stack[top++] = num3 + '0';
        }
        
        cin>>c;
    }
    int result = stack[0] - '0';
    cout<<result<<endl;
    return 0;
}
