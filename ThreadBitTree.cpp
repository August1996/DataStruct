//
//  main.cpp
//  ThreadBitTree
//
//  Created by 余彬 on 16/4/19.
//  Copyright © 2016年 余彬. All rights reserved.
//

#include <iostream>
using namespace std;

typedef enum{
    LINK,
    THREAD
}NodeType;

typedef enum{
    PREVIOUS,
    MIDDLE,
    BACK
}ThreadType;

class Node{
public:
    char data;
    Node *lChild;
    NodeType lTag;
    Node *rChild;
    NodeType rTag;
};

class BitTree{
public:
    BitTree();
    int input(Node* &  node);
    int input();
    void preVisit();
    void preVisit(Node *pNode);
    void middleVisit();
    void middleVisit(Node *pNode);
    void backVisit();
    void backVisit(Node *pNode);
    void visit();
    void inOrderThread(ThreadType type);
    void inOrderThreadPre(Node* &  node);
    void inOrderThreadMiddle(Node* &  node);
    void inOrderThreadBack(Node* &  node);
    void visitOrderThread();
    void visitOrderThreadByPrevious(Node *pNode);
    void visitOrderThreadByMiddle(Node *pNode);
    void visitOrderThreadByBack(Node *pNode);
private:
    Node *root;
    int nodeCount;
    Node *threadingPreNode;
    Node *pHead;
    ThreadType threadType;
    int isThread;
};

BitTree::BitTree(){
    this->isThread = 0;
    this->threadType = ThreadType::PREVIOUS;
}

int BitTree::input(){
    input(this->root);
    return this->nodeCount;
}

int BitTree::input(Node* &  node){
    char c;
    
    cin.get(c);
    
    if(c != '\n'){
        if(c != ' '){
            node = new Node;
            node->data = c;
            node->rChild = node->lChild = NULL;
            node->rTag = node->lTag = NodeType::LINK;
            this->nodeCount++;
            input(node->lChild);
            input(node->rChild);
        }
    }
    return this->nodeCount;
}

void BitTree::preVisit(){
    preVisit(this->root);
    cout<<endl;
}

void BitTree::preVisit(Node *pNode){
    if(pNode != NULL){
        cout<<pNode->data<<" ";
        
        if(pNode->lTag == NodeType::LINK){
            preVisit(pNode->lChild);
        }
        if(pNode->rTag == NodeType::LINK){
            preVisit(pNode->rChild);
        }
    }
}


void BitTree::middleVisit(){
    middleVisit(this->root);
    cout<<endl;
}
void BitTree::middleVisit(Node *pNode){
    if(pNode != NULL){
        if(pNode->lTag == NodeType::LINK){
            middleVisit(pNode->lChild);
        }
        
        cout<<pNode->data<<" ";
        
        if(pNode->rTag == NodeType::LINK){
            middleVisit(pNode->rChild);
        }
    }
}


void  BitTree::backVisit(){
    backVisit(this->root);
    cout<<endl;
}
void  BitTree::backVisit(Node *pNode){
    if(pNode != NULL){
        if(pNode->lTag == NodeType::LINK){
            backVisit(pNode->lChild);
        }
        if(pNode->rTag == NodeType::LINK){
            middleVisit(pNode->rChild);
        }
        cout<<pNode->data<<" ";
    }
}
void BitTree::inOrderThread(ThreadType type){
    this->threadType = type;
    this->pHead = new Node;
    this->pHead->lTag = this->pHead->rTag = NodeType::THREAD;
    this->pHead->lChild = this->root;
    this->threadingPreNode = this->pHead;
    
    if(type == ThreadType::PREVIOUS){
        inOrderThreadPre(this->root);
    }else if(type == ThreadType::MIDDLE){
        inOrderThreadMiddle(this->root);
    }else if(type == ThreadType::BACK){
        inOrderThreadBack(this->root);
    }
    
    this->threadingPreNode->rChild = this->pHead;
    this->threadingPreNode->rTag = NodeType::THREAD;
    this->pHead->rChild = this->threadingPreNode;
}

void BitTree::inOrderThreadPre(Node* &  node){
    if(node != NULL){
        if(this->threadingPreNode->rChild == NULL || this->threadingPreNode->rTag == NodeType::THREAD){
            this->threadingPreNode->rChild = node;
             this->threadingPreNode->rTag = NodeType::THREAD;
        }
        if(node->lChild == NULL || node->lTag == NodeType::THREAD){
            node->lChild = this->threadingPreNode;
            node->lTag = NodeType::THREAD;
        }
        
        this->threadingPreNode = node;
        
        if(node->lTag == NodeType::LINK){
            inOrderThreadPre(node->lChild);
        }
        if(node->rTag == NodeType::LINK){
            inOrderThreadPre(node->rChild);
        }
    }
}
void BitTree::inOrderThreadMiddle(Node* &  node){
    if(node != NULL){
        if(node->lTag == NodeType::LINK){
            inOrderThreadPre(node->lChild);
        }
        
        if(this->threadingPreNode->rChild == NULL || this->threadingPreNode->rTag == NodeType::THREAD){
            this->threadingPreNode->rChild = node;
            this->threadingPreNode->rTag = NodeType::THREAD;
        }
        if(node->lChild == NULL || node->lTag == NodeType::THREAD){
            node->lChild = this->threadingPreNode;
            node->lTag = NodeType::THREAD;
        }
        
        this->threadingPreNode = node;

        if(node->rTag == NodeType::LINK){
            inOrderThreadPre(node->rChild);
        }
    }
}
void BitTree::inOrderThreadBack(Node* &  node){
    if(node != NULL){
        if(node->lTag == NodeType::LINK){
            inOrderThreadPre(node->lChild);
        }
        
        if(node->rTag == NodeType::LINK){
            inOrderThreadPre(node->rChild);
        }
        
        if(this->threadingPreNode->rChild == NULL || this->threadingPreNode->rTag == NodeType::THREAD){
            this->threadingPreNode->rChild = node;
            this->threadingPreNode->rTag = NodeType::THREAD;
        }
        if(node->lChild == NULL || node->rTag == NodeType::THREAD){
            node->lChild = this->threadingPreNode;
            node->lTag = NodeType::THREAD;
        }
        
        this->threadingPreNode = node;
    }
}

void BitTree::visitOrderThread(){
    if(this->threadType == ThreadType::PREVIOUS){
        visitOrderThreadByPrevious(this->pHead->lChild);
    }else if(this->threadType == ThreadType::MIDDLE){
        visitOrderThreadByMiddle(this->pHead->lChild);
    }else if(this->threadType == ThreadType::BACK){
        visitOrderThreadByBack(this->pHead->lChild);
    }
    cout<<endl;
}

void BitTree::visitOrderThreadByPrevious(Node *pNode){
//    if(pNode != this->pHead){
//        if(pNode->lTag == NodeType::LINK){
//            cout<<pNode->data<<" ";
//            visitOrderThreadByPrevious(pNode->lChild);
//        }else {
//            while (pNode->rTag == NodeType::THREAD) {
//                if(pNode == this->pHead){
//                    return;
//                }
//                cout<<pNode->data<<" ";
//                pNode = pNode->rChild;
//            }
//            cout<<pNode->data<<" ";
//            visitOrderThreadByPrevious(pNode->rChild);
//        }
//    }
}

void BitTree::visitOrderThreadByMiddle(Node *pNode){
    while (pNode->lTag == NodeType::LINK) {
        pNode=pNode->lChild;
    }
    
    if(pNode->rTag == NodeType::THREAD){
        while (pNode->rTag == NodeType::THREAD) {
            if(pNode == this->pHead){
                return;
            }
            cout<<pNode->data<<" ";
            pNode = pNode->rChild;
        }
    }
    cout<<pNode->data<<" ";
    visitOrderThreadByMiddle(pNode->rChild);
}

void BitTree::visitOrderThreadByBack(Node *pNode){
}

int main(int argc, const char * argv[]) {
    BitTree bt;
    bt.input();
    bt.preVisit();
    bt.middleVisit();
    bt.backVisit();
    bt.inOrderThread(ThreadType::MIDDLE);
    bt.visitOrderThread();
    
    
    return 0;
}
