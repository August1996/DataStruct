//
//  main.cpp
//  DoubleChainList
//
//  Created by 余彬 on 16/4/19.
//  Copyright © 2016年 余彬. All rights reserved.
//

#include <iostream>
using namespace std;


template<class T> class Node{
public:
    T data;
    Node * pBefore;
    Node * pNext;
};

template<class T> class List{
public:
    List();
    bool insert(int pos,T data);
    int append(T data);
    T remove(int pos);
    bool set(int pos,T data);
    T get(int pos);
    void show();
    void clear();
private:
    Node<T> * pHead;
    Node<T> * pTail;
    int lenght;
};

template<class T>
List<T>::List(){
    this->lenght = 0;
    this->pHead = new Node<T>;
    this->pTail = pHead;
    this->pHead->pNext = NULL;
    this->pHead->pBefore = NULL;
}

template<class T>
bool List<T>::insert(int pos,T data){
    if(this->pHead == NULL || pos >= this->lenght || pos < 0){
        return false;
    }
    
    Node<T> *pNew = new Node<T>;
    pNew->data = data;
    pNew->pNext = NULL;
    pNew->pBefore = NULL;
    if(pos == 0){
        pNew->pNext = this->pHead->pNext;
        this->pHead = pNew;
        if(this->pHead->pNext != NULL){
            this->pHead->pNext->pBefore = pNew;
        }
        this->lenght++;
        return true;
    }
    
    Node<T> *p = this->pHead;
    int i;
    if(pos <= this->lenght / 2){
        for(i = 0,p = this->pHead;i < pos;i++,p = p->pNext);
    }else{
        for(i = this->lenght - 1,p = this->pTail;i > pos;i--,p = p->pBefore);
    }
    pNew->pNext = p;
    pNew->pBefore = p->pBefore;
    p->pBefore->pNext = pNew;
    p->pBefore = pNew;
    this->lenght++;
    return true;
}

template<class T>
int List<T>::append(T data){
    Node<T> *p = this->pHead;
    Node<T> *pNew = new Node<T>;
    pNew->pNext = NULL;
    pNew->pBefore = NULL;
    pNew->data = data;
    if(this->lenght == 0){
        this->pHead->data = data;
    }else{
        while (p->pNext != NULL)
            p = p->pNext;
        p->pNext = pNew;
        pNew->pBefore = p;
        this->pTail = pNew;
    }
    return this->lenght++;
}

template<class T>
T List<T>::remove(int pos){
    T result;
    if(pos >= 0 && pos < this->lenght && this->pHead != NULL){
        Node<T> * p = this->pHead;
        if(pos == 0){
            this->pHead = this->pHead->pNext;
            if(this->pHead->pNext != NULL){
                this->pHead->pBefore = NULL;
                this->pHead->pNext->pBefore = this->pHead;
            }
            result = p->data;
            this->lenght--;
        }else{
            for(int i = 0;i < pos;i++,p = p->pNext);
            result = p->data;
            p->pBefore->pNext = p->pNext;
            if(p->pNext != NULL){
                p->pNext->pBefore = p->pBefore;
            }
            if(pos == this->lenght){
                this->pTail = p->pBefore;
            }
            delete p;
            this->lenght--;
        }
    }
    return result;
}

template<class T>
bool List<T>::set(int pos,T data){
    if(pos < 0 || pos >= this->lenght){
        return false;
    }else{
        Node<T> *p = NULL;
        int i;
        if(pos <= this->lenght / 2){
            for(i = 0,p = this->pHead;i < pos;i++,p = p->pNext);
            p->data = data;
        }else{
            for(i = this->lenght - 1,p = this->pTail;i > pos;i--,p = p->pBefore);
            p->data = data;
        }
        return true;
    }
}

template<class T>
T List<T>::get(int pos){
    T result;
    if(pos >= 0 || pos < this->lenght){
        Node<T> *p = NULL;
        int i;
        if(pos <= this->lenght / 2){
            for(i = 0,p = this->pHead;i < pos;i++,p = p->pNext);
            result = p->data;
        }else{
            for(i = this->lenght - 1,p = this->pTail;i > pos;i--,p = p->pBefore);
            result = p->data;
        }
    }
    return result;
}

template<class T>
void List<T>::show(){
    cout<<"----"<<endl;
    if(this->lenght > 0){
        Node<T> *p = this->pHead;
        while (p != NULL) {
            cout<<(p->data)<<endl;
            p = p->pNext;
        }
    }
    cout<<"----"<<endl;
}

template<class T>
void List<T>::clear(){
    Node<T> *pDel1 = this->pHead->pNext,*p1;
    Node<T> *pDel2 = this->pTail,*p2;
    this->pTail = this->pHead;
   
    for (int i = 0;i < (this->lenght - 1) / 2;i++) {
        p1 = pDel1->pNext;
        p2 = pDel2->pBefore;
        delete pDel1;
        delete pDel2;
        pDel1 = p1;
        pDel2 = p2;
    }
    
    if(this->lenght % 2 == 0){
        delete pDel1;
    }
    
    T random;
    this->pHead->data = random;
    this->pHead->pNext = NULL;
    this->pTail = this->pHead;
    this->lenght = 0;
}

int main(int argc, const char * argv[]) {
    List<int> list;
    int i;
    for(i = 0;i < 10;i += 2){
        list.append(i);
    }
    list.show();
    list.insert(1, 1);
    list.insert(3, 3);
    list.insert(6, 7);
    list.insert(5, 5);
    list.show();

    list.remove(1);
    list.remove(0);
    list.remove(5);
    list.remove(5);
    list.remove(7);
    list.show();

    cout<<list.get(0)<<endl;
    list.set(4, 666);
    cout<<list.get(4)<<endl;

    list.append(10);
    list.clear();
    list.show();
    
    return 0;
}
