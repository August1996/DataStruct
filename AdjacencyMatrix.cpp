//
//  main.cpp
//  AdjacencyMatrix
//
//  Created by 余彬 on 16/9/9.
//  Copyright © 2016年 余彬. All rights reserved.
//

#include <iostream>
using namespace std;

const int MaxSize = 10;
template <class DataType>
class MGraph {
    
public:
    MGraph(DataType data[],int n,int e);
    void DFSTraverse(int v);
    void BFSTraverse(int v);
private:
    void BFSTraverse(int stack[],int &top,int v);
    DataType vertex[MaxSize];
    int visited[MaxSize];
    int arc[MaxSize][MaxSize];
    int vertexNum;
    int arcNum;
    
};

//创建一个图
template <class DataType>
MGraph<DataType>::MGraph(DataType data[],int n,int e){
    this->vertexNum = n;
    this->arcNum = e;
    for(int i = 0;i < this->vertexNum;i++){
        this->vertex[i] = data[i];
        this->visited[i] = 0;
    }
    int j,k;
    for(int i = 0;i < e;i++){
        cin>>j>>k;
        arc[j][k] = 1;
        arc[k][j] = 1;//有向图去掉此行
    }
}

//深度优先遍历算法
template <class DataType>
void MGraph<DataType>::DFSTraverse(int v){
    cout<<(this->vertex[v]);
    this->visited[v] = 1;
    for(int i = 0;i < (this->vertexNum);i++){
        if((this->arc[v][i]) == 1 && (this->visited[i]) == 0){
            this->DFSTraverse(i);
        }
    }
}

//广度优先遍历算法
template <class DataType>
void MGraph<DataType>::BFSTraverse(int v){
    int stack[MaxSize];
    int top = 0;
    BFSTraverse(stack,top,v);
}

//用作广度优先遍历算法递归的重载函数
template <class DataType>
void MGraph<DataType>::BFSTraverse(int stack[],int &top,int v){
    cout<<(this->vertex[v]);
    this->visited[v] = 1;
    stack[top++] = v;
    for(int i = 0;i < (this->vertexNum);i++){
        if(this->arc[v][i] == 1 && this->visited[i] == 0){
            stack[top++] = i;
            this->BFSTraverse(stack,top,i);
        }
    }
    top--;
    
}

int main(int argc, const char * argv[]) {
    char data[5] = {'A','B','C','D','E'};
    MGraph<char> mGraph(data,5,4);
    int v;
    cin>>v;
//    mGraph.DFSTraverse(v);
//    cout<<endl;
    mGraph.BFSTraverse(v);
    cout<<endl;
    
    return 0;
}
