//
//  main.cpp
//  LoopQueue
//
//  Created by 余彬 on 16/4/19.
//  Copyright © 2016年 余彬. All rights reserved.
//

#include <iostream>
using namespace std;

template <class T>
class Node {
public:
    T data;
    Node<T> *pNext;
};


template <class T>
class Queue {
public:
    Queue();
    int shift(T data);
    T unshift();
    void show(int n);
    void clear();
private:
    Node<T> * pHead;
    Node<T> * pRear;
    int lenght;
};

template <class T>
Queue<T>::Queue(){
    this->pHead = this->pRear = new Node<T>;
    this->pRear->pNext = this->pHead;
    this->lenght = 0;
}

template <class T>
int Queue<T>::shift(T data){
    if(this->lenght == 0){
        this->pHead->data = data;
    }else{
        Node<T> *pNew = new Node<T>;
        pNew->pNext = this->pHead;
        pNew->data = data;
        this->pRear->pNext = pNew;
        this->pRear = pNew;
    }
    return ++this->lenght;
}

template <class T>
T Queue<T>::unshift(){
    T result;
    if(this->lenght > 0){
        Node<T> * pDel;
        result = this->pHead->data;
        pDel = this->pHead;
        this->pHead = this->pHead->pNext;
        this->pRear->pNext = this->pHead;
        delete pDel;
        this->lenght--;
        if(this->pHead == NULL){
            this->pHead = this->pRear;
        }
    }
    return result;
}

template <class T>
void Queue<T>::show(int n){
    Node<T> * p = this->pHead;
    cout<<"----"<<endl;
    if(this->lenght > 0){
        for(int i = 0;i < n;i++,p = p->pNext){
            cout<<p->data<<endl;
        }
    }
    cout<<"----"<<endl;
}

template <class T>
void Queue<T>::clear(){
    Node<T> *p = this->pHead->pNext,*p1;
    this->pHead = this->pRear;
    for(int i = 1;i < this->lenght;i++){
        p1 = p->pNext;
        delete p;
        p = p1;
    }
    this->lenght = 0;
}

int main(int argc, const char * argv[]) {
    Queue<int> q;
    int i;
    for(i = 0;i < 20;i++){
        q.shift(i);
    }
    q.show(20);
    
    for(i = 0;i < 20;i++){
        cout<<q.unshift()<<endl;
    }
    
    q.clear();
    q.unshift();
    
    for(i = 20;i > 0;i--){
        q.shift(i);
    }
    q.show(25);
    
    q.clear();
    
    q.show(20);
    
    return 0;
}
