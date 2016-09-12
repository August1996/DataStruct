//
//  main.cpp
//  AdjacencyList
//
//  Created by 余彬 on 16/9/9.
//  Copyright © 2016年 余彬. All rights reserved.
//

#include <iostream>
using namespace std;

//边节点
class ArcNode{
public:
    ArcNode(int index);
    int vertuxIndex;
    ArcNode *next;
};

ArcNode::ArcNode(int index){
    this->vertuxIndex = index;
    this->next = NULL;
}

//定点节点
template <class DataType>
class VertuxNode{
public:
    VertuxNode();
    void append(int vertuxIndex);
    DataType data;
    ArcNode *first;
};

template <class DataType>
VertuxNode<DataType>::VertuxNode(){
    this->first = NULL;
}

//在其边节点最后追加一个边节点
template <class DataType>
void VertuxNode<DataType>::append(int vertuxIndex){
    ArcNode *arcNode = new ArcNode(vertuxIndex);
    if(this->first == NULL){
        this->first = arcNode;
    }else{
        ArcNode *first = this->first;
        while (first->next != NULL) {
            first = first->next;
        }
        first->next = arcNode;
    }
}

//无向图
const int MaxSize = 10;
template <class DataType>
class MGraph {
public:
    MGraph(DataType data[],int n,int e);
    void DFSTraverse(int v);
    void BFSTravserse(int v);
    
private:
    VertuxNode<DataType> vertux[MaxSize];
    int vertuxNum;
    int arcNum;
    int visited[MaxSize];
    void DFSTravserse(int *quene,int &top,int v);
};

template <class DataType>
MGraph<DataType>::MGraph(DataType data[],int n,int e){
    this->vertuxNum = n;
    this->arcNum = e;
    for(int i = 0;i < this->vertuxNum;i++){
        VertuxNode<DataType> vertuxNode;
        vertuxNode.data = data[i];
        this->vertux[i] = vertuxNode;
        this->visited[i] = 0;
    }
    
    int j,k;
    for(int i = 0;i < this->arcNum;i++){
        cin>>j>>k;
        this->vertux[j].append(k);
        
        //有向图去掉下面一行代码
        this->vertux[k].append(j);
    }
}

//广度优先遍历算法
template <class DataType>
void MGraph<DataType>::BFSTravserse(int v){
    VertuxNode<DataType> vertuxNodeV = this->vertux[v];
    cout<<vertuxNodeV.data;
    this->visited[v] = 1;
    for(int i = 0;i < this->vertuxNum;i++){
        ArcNode *pArcNode = vertuxNodeV.first;
        while (pArcNode != NULL) {
            if(this->visited[pArcNode->vertuxIndex] == 0){
                BFSTravserse(pArcNode->vertuxIndex);
            }
            pArcNode = pArcNode->next;
        }
    }
}



//深度优先遍历算法
template <class DataType>
void MGraph<DataType>::DFSTraverse(int v){
    //    VertuxNode<DataType> stack[MaxSize];
    //    int top = 0;
    //    DFSTravserse(stack, top, v);
    int quene[MaxSize];
    int top = 0;
    DFSTravserse(quene, top, v);
}


//深度优先遍历算法递归重载函数
template <class DataType>
void MGraph<DataType>::DFSTravserse(int *queue, int &top,int v){
    VertuxNode<DataType> vertuxNodeV = this->vertux[v];
    cout<<vertuxNodeV.data;
    this->visited[v] = 1;
    queue[top++] = v;
    
    while (top != 0) {
        ArcNode *arcNode = this->vertux[v].first;
        while (arcNode != NULL) {
            v = arcNode->vertuxIndex;
            if(this->visited[v] == 0){
                cout<<this->vertux[v].data;
                this->visited[v] = 1;
                queue[top++] = v;
            }
            arcNode = arcNode->next;
        }
        v = queue[--top];
    }
    
    
}

int main(int argc, const char * argv[]) {
    char data[] = {'A','B','C','D','E'};
    MGraph<char> mGraph(data,5,4);
    int v;
    cin>>v;
//    mGraph.BFSTravserse(v);
    mGraph.DFSTraverse(v);
    cout<<endl;
    
}
